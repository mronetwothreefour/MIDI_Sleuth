#include "G_Msg_Slots.h"

Msg_Slots::Msg_Slots(Data_Hub* hub) :
	Data_User{ hub },
	tabs{ TabbedButtonBar::TabsAtBottom },
	btn_transmit{ "Transmit" },
	btn_jump{ "Jump To..." },
	btn_clear{ "Clear Slot" }
{
	tabs.setTabBarDepth(XYWH::tab_h);
	auto& btn_bar = tabs.getTabbedButtonBar();
	for (int i = 0; i < 5; ++i) {
		auto slot_num = String{ i + 1 };
		slots[i].reset(new Table{ (Table_Type)(msg_slot_1 + i), hub, });
		Colour tab_color = COLOR::tab_bkgrnd_red;
		switch (i) {
		case 1:
			tab_color = COLOR::tab_bkgrnd_orange;
			break;
		case 2:
			tab_color = COLOR::tab_bkgrnd_yellow;
			break;
		case 3:
			tab_color = COLOR::tab_bkgrnd_green;
			break;
		case 4:
			tab_color = COLOR::tab_bkgrnd_blue;
			break;
		default:
			break;
		}
		tabs.addTab("Slot " + slot_num, tab_color, slots[i].get(), true, Tab__Slot::slot_1 + i);
		btn_bar.getTabButton(Tab__Slot::slot_1 + i)->setTooltip("Shortcut: Alt+" + slot_num);
	}
	btn_bar.addChangeListener(this);
	addAndMakeVisible(tabs);

	btn_transmit.onClick = [this] { 
		auto current_tab = tabs.getCurrentTabIndex();
		tabs.getTabContentComponent(current_tab)->grabKeyboardFocus();
		cmd_mngr.invokeDirectly(transmit_msg__slot_1 + current_tab, true);
	};
	btn_transmit.setTooltip("Transmit the message in the slot.\nShortcut: Alt+T");
	btn_transmit.setSize(XYWH::btn_slots_w, XYWH::btn_h);
	addAndMakeVisible(btn_transmit);

	btn_jump.onClick = [this] { 
		tabs.getTabContentComponent(tabs.getCurrentTabIndex())->grabKeyboardFocus();
		cmd_mngr.invokeDirectly(jump_to_byte, true); 
	};
	btn_jump.setTooltip("Scroll table horizontally to\nshow a specified byte index.\nShortcut: Alt+J");
	btn_jump.setSize(XYWH::btn_slots_w, XYWH::btn_h);
	addAndMakeVisible(btn_jump);

	btn_clear.onClick = [this] { clear_visible_slot(); };
	btn_clear.addShortcut(KeyPress{ 's', ModifierKeys::altModifier, 0 });
	btn_clear.setTooltip("Clear the message in the slot.\nShortcut: Alt+S");
	btn_clear.setSize(XYWH::btn_slots_w, XYWH::btn_h);
	addAndMakeVisible(btn_clear);

	match_btn_color_to_visible_tab();

	cmd_mngr.registerAllCommandsForTarget(this);
	addKeyListener(cmd_mngr.getKeyMappings());
}

void Msg_Slots::match_btn_color_to_visible_tab() {
	auto tab_color = COLOR::tab_bkgrnd_red;
	switch (tabs.getCurrentTabIndex()) {
	case 1: 
		tab_color = COLOR::tab_bkgrnd_orange;
		break;
	case 2: 
		tab_color = COLOR::tab_bkgrnd_yellow;
		break;
	case 3: 
		tab_color = COLOR::tab_bkgrnd_green;
		break;
	case 4: 
		tab_color = COLOR::tab_bkgrnd_blue;
		break;
	default:
		break;
	}
	btn_transmit.setColour(TextButton::buttonColourId, tab_color);
	btn_jump.setColour(TextButton::buttonColourId, tab_color);
	btn_clear.setColour(TextButton::buttonColourId, tab_color);
}

void Msg_Slots::paint(Graphics& g) {
	g.setColour(COLOR::txt);
	g.setFont(FONT::lbl_section);
	Rectangle<int> lbl_section_area{ 0, 0, getWidth(), XYWH::lbl_section_h };
	g.drawText("Message Storage Slots", lbl_section_area.translated(0, -3), Justification::centredTop);
}

void Msg_Slots::resized() {
	tabs.setBounds(0, XYWH::lbl_section_h, getWidth(), getHeight() - XYWH::lbl_section_h);
	auto btn_y = getHeight() - XYWH::btn_h;
	btn_clear.setTopRightPosition(getWidth(), btn_y);
	btn_jump.setTopRightPosition(btn_clear.getX() - 5, btn_y);
	btn_transmit.setTopRightPosition(btn_jump.getX() - 5, btn_y);
}

void Msg_Slots::clear_visible_slot() {
	auto slot_tree = msg_slot(tabs.getCurrentTabIndex());
	slot_tree->set_msg_bytes("");
	slot_tree->set_msg_description("");
}

void Msg_Slots::changeListenerCallback(ChangeBroadcaster* /*source*/) {
	match_btn_color_to_visible_tab();
}

ApplicationCommandTarget* Msg_Slots::getNextCommandTarget() {
	return slots[tabs.getCurrentTabIndex()].get();
}

void Msg_Slots::getAllCommands(Array<int>& cmd_list) {
	for (int i = 0; i < 5; ++i)
		cmd_list.add(show_tab__slot_1 + i);
}

void Msg_Slots::getCommandInfo(int cmd, ApplicationCommandInfo& info) {
	if (cmd >= show_tab__slot_1 && cmd <= show_tab__slot_5) {
		auto slot_index = cmd - show_tab__slot_1;
		auto slot_num = String{ slot_index + 1 };
		info.setInfo("Slot " + slot_num + " tab", "Show slot " + slot_num, "Slots", 0);
		info.addDefaultKeypress(0x31 + slot_index, ModifierKeys::altModifier);
	}
}

bool Msg_Slots::perform(const InvocationInfo& info) {
	auto cmd = info.commandID;
	if (cmd >= show_tab__slot_1 && cmd <= show_tab__slot_5) {
		tabs.setCurrentTabIndex(cmd - show_tab__slot_1);
		return true;
	}
	return false;
}

Msg_Slots::~Msg_Slots() {
	tabs.getTabbedButtonBar().removeChangeListener(this);
	for (int i = 0; i < 5; ++i)
		slots[i].reset();
	removeKeyListener(cmd_mngr.getKeyMappings());
}
