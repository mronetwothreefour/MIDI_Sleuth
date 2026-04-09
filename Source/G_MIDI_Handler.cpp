#include "G_MIDI_Handler.h"

#include "C_GUI_COLOR.h"
#include "C_GUI_XYWH.h"

MIDI_Handler::MIDI_Handler(Data_Hub* hub, MidiInputCallback* input_handler) :
	Data_User{ hub },
	tabs{ TabbedButtonBar::TabsAtBottom },
	lbox_inputs{ new MIDI_Device_Lbox{ "MIDI Inputs", true, input_handler } },
	lbox_outputs{ new MIDI_Device_Lbox{ "MIDI Outputs" } },
	btn_reset("Reset All")
{
	tabs.setTabBarDepth(XYWH::tab_h);
	tabs.addTab("Inputs", COLOR::lbox_bkgrnd, lbox_inputs.get(), true);
	tabs.addTab("Outputs", COLOR::lbox_bkgrnd, lbox_outputs.get(), true);
	String tip{ "Use Alt+D to toggle the visible tab." };
	auto& btn_bar = tabs.getTabbedButtonBar();
	btn_bar.getTabButton(Tab__Devices::inputs)->setTooltip(tip);
	btn_bar.getTabButton(Tab__Devices::outputs)->setTooltip(tip);
	btn_bar.getTabButton(1)->setTooltip(tip);
	tabs.setBounds(XYWH::devices_tabs);
	addAndMakeVisible(tabs);

	btn_reset.onClick = [this] { stop_and_reset_all(); };
	btn_reset.setBounds(XYWH::devices_btn_reset);
	btn_reset.addShortcut(KeyPress{ 'r', ModifierKeys::ctrlModifier, 0 });
	btn_reset.setTooltip("Send all notes off to all channels,\nthen stop and reset all devices.\nShortcut: Ctrl+R");
	addAndMakeVisible(btn_reset);

	cmd_mngr.registerAllCommandsForTarget(this);
	addKeyListener(cmd_mngr.getKeyMappings());
}

void MIDI_Handler::paint(Graphics& g) {
	g.setColour(COLOR::txt);
	g.setFont(FONT::lbl_section);
	g.drawText("MIDI Devices (select to open)", XYWH::devices_lbl_section, Justification::centredTop);
}

void MIDI_Handler::handleIncomingMidiMessage(MidiInput* /*source*/, const MidiMessage& msg) {
	// This is called on the MIDI thread
	const ScopedLock scoped_lock(monitor_lock);
	list_received_messages.add(msg);
	triggerAsyncUpdate();
}

void MIDI_Handler::handleAsyncUpdate() {
	// This is called on the message loop
	Array<MidiMessage> messages;
	{
		const ScopedLock scoped_lock(monitor_lock);
		messages.swapWith(list_received_messages);
	}
	String msg_text;
	for (auto& msg : messages) {
		if (msg.getRawData()[0] < 0xf8) {
			if ((msg.isNoteOn() || msg.isNoteOff()) && should_be_logged(Msg_Type::note_on_off) ||
				(msg.isAftertouch() || msg.isPitchWheel()) && should_be_logged(Msg_Type::aftertouch_bend) ||
				msg.isController() && should_be_logged(Msg_Type::ctrl_change) ||
				msg.isProgramChange() && should_be_logged(Msg_Type::pgm_change) ||
				msg.isSysEx() && should_be_logged(Msg_Type::sysex))
			{
				in_log->add_msg(msg);
			}
		}
	}
}

void MIDI_Handler::send_msg(const MidiMessage& msg) {
	lbox_outputs->pass_msg_to_open_outputs(msg);
}

void MIDI_Handler::send_msg_in_slot(const int slot_index) {
	if (slot_index > -1 && slot_index < 5) {
		auto slot_tree = msg_slot(slot_index);
		auto bytes = slot_tree->msg_bytes();
		auto description = slot_tree->msg_description();
		if (bytes.isNotEmpty()) {
			auto msg = Convert::hex_string_to_MIDI_message(bytes);
			send_msg(msg);
			out_log->add_msg(msg, description);
		}
	}
}

void MIDI_Handler::stop_and_reset_all() {
	for (auto chan = 1; chan < 17; ++chan)
		send_msg(MidiMessage::allNotesOff(chan));
	lbox_inputs->stop_and_reset_all_devices();
	lbox_outputs->stop_and_reset_all_devices();
}

void MIDI_Handler::set_next_cmd_target(ApplicationCommandTarget* new_target) {
	next_cmd_target = new_target;
}

ApplicationCommandTarget* MIDI_Handler::getNextCommandTarget() {
	return next_cmd_target;
}

void MIDI_Handler::getAllCommands(Array<int>& cmd_list) {
	cmd_list.add(toggle_tab__devices);
}

void MIDI_Handler::getCommandInfo(int cmd, ApplicationCommandInfo& info) {
	if (cmd == toggle_tab__devices) {
		info.setInfo("Toggle visible MIDI devices tab", 
					 "Toggle visible MIDI devices tab", 
					 "MIDI Devices", 0);
		info.addDefaultKeypress('d', ModifierKeys::altModifier);
	}
}

bool MIDI_Handler::perform(const InvocationInfo& info) {
	if (info.commandID == toggle_tab__devices) {
		tabs.setCurrentTabIndex(1 - tabs.getCurrentTabIndex());
		return true;
	}
	return false;
}

MIDI_Handler::~MIDI_Handler() {
	lbox_inputs.reset();
	lbox_outputs.reset();
	removeKeyListener(cmd_mngr.getKeyMappings());
}
