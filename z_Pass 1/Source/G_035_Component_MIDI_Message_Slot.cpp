#include "G_035_Component_MIDI_Message_Slot.h"

Component_MIDI_Message_Slot::Component_MIDI_Message_Slot(int slot_index, Data_Hub* hub, Component_MIDI_Devices* devices) :
	Data_User{ hub },
	slot_index{ slot_index },
	devices{ devices },
	btn_edit{ "Edit" },
	btn_send{ "Send" }
{
	auto slot_string = String{ slot_index + 1 };
	btn_edit.setBounds(XYWH::msg_slot_btn_edit);
	btn_edit.onClick = [this] { show_message_editor(); };
	btn_edit.addShortcut(KeyPress{ 0x31 + slot_index, ModifierKeys::altModifier, 0 });
	btn_edit.setTooltip("Open an editor for the\nmessage stored in slot " + slot_string + ".\nShortcut: Alt + " + slot_string);
	addAndMakeVisible(btn_edit);

	btn_send.setBounds(XYWH::msg_slot_btn_send);
	btn_send.onClick = [this, devices, slot_index] { devices->send_stored_message(slot_index); };
	btn_send.addShortcut(KeyPress{ 0x31 + slot_index, ModifierKeys::noModifiers, 0 });
	btn_send.setTooltip("Send the message\nstored in slot " + slot_string + " to the\nselected outputs.\nShortcut: " + slot_string);
	addAndMakeVisible(btn_send);

	setSize(XYWH::msg_slot_w, XYWH::msg_slot_h);
}

void Component_MIDI_Message_Slot::paint(Graphics& g) {
	g.setColour(COLOR::text);
	g.setFont(FONT::msg_slot_header);
	g.drawText("Message Slot " + String{ slot_index + 1 }, XYWH::msg_slot_lbl, Justification::centredTop);
}

void Component_MIDI_Message_Slot::show_message_editor() {
	win_edit_msg.reset(new Window_Edit_MIDI_Message{ slot_index, hub });
	auto parent_bounds = getParentComponent()->getBounds();
	auto cntr_x = parent_bounds.getCentreX();
	auto cntr_y = parent_bounds.getCentreY() - XYWH::msg_slot_h;
	win_edit_msg->setCentrePosition(cntr_x, cntr_y);
	win_edit_msg->setVisible(true);
}

Component_MIDI_Message_Slot::~Component_MIDI_Message_Slot() {
	win_edit_msg = nullptr;
}
