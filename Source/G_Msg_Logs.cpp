#include "G_Msg_Logs.h"

Msg_Logs::Msg_Logs(Data_Hub* hub) :
	Data_User{ hub },
	tabs{ TabbedButtonBar::TabsAtBottom },
	tab_incoming{ new Table{ log_in, hub } },
	tab_outgoing{ new Table{ log_out, hub } },
	tab_compare{ new Table{ comparison, hub } },
	btn_jump{ "Jump To..." },
	btn_clear{ "Clear Log" }
{
	tabs.setTabBarDepth(XYWH::tab_h);
	tabs.addTab("Incoming", COLOR::tab_bkgrnd_green, tab_incoming.get(), true, Tab__Log::incoming);
	tabs.addTab("Outgoing", COLOR::tab_bkgrnd_red, tab_outgoing.get(), true, Tab__Log::outgoing);
	tabs.addTab("Compare", COLOR::tab_bkgrnd_blue, tab_compare.get(), true, Tab__Log::compare);
	auto& btn_bar = tabs.getTabbedButtonBar();
	btn_bar.getTabButton(Tab__Log::incoming)->setTooltip("Shortcut: Alt+I");
	btn_bar.getTabButton(Tab__Log::outgoing)->setTooltip("Shortcut: Alt+O");
	btn_bar.getTabButton(Tab__Log::compare)->setTooltip("Shortcut: Alt+=");
	btn_bar.addChangeListener(this);
	addAndMakeVisible(tabs);

	btn_jump.onClick = [this] { 
		tabs.getTabContentComponent(tabs.getCurrentTabIndex())->grabKeyboardFocus();
		cmd_mngr.invokeDirectly(jump_to_byte, true); 
	};
	btn_jump.setTooltip("Scroll table horizontally to\nshow a specified byte index.\nShortcut: Alt+J");
	btn_jump.setSize(XYWH::btn_logs_w, XYWH::btn_h);
	addAndMakeVisible(btn_jump);

	btn_clear.onClick = [this] { clear_visible_table(); };
	btn_clear.addShortcut(KeyPress{ 'l', ModifierKeys::altModifier, 0 });
	btn_clear.setTooltip("Remove all messages from the log.\nShortcut: Alt+L");
	btn_clear.setSize(XYWH::btn_logs_w, XYWH::btn_h);
	addAndMakeVisible(btn_clear);

	match_btn_color_to_visible_tab();

	cmd_mngr.registerAllCommandsForTarget(this);
	addKeyListener(cmd_mngr.getKeyMappings());
}

void Msg_Logs::match_btn_color_to_visible_tab() {
	auto tab_color = COLOR::tab_bkgrnd_green;
	if (tabs.getCurrentTabIndex() == 1)
		tab_color = COLOR::tab_bkgrnd_red;
	if (tabs.getCurrentTabIndex() == 2)
		tab_color = COLOR::tab_bkgrnd_blue;
	btn_jump.setColour(TextButton::buttonColourId, tab_color);
	btn_clear.setColour(TextButton::buttonColourId, tab_color);
}

void Msg_Logs::paint(Graphics& g) {
	g.setColour(COLOR::txt);
	g.setFont(FONT::lbl_section);
	Rectangle<int> lbl_section_area{ 0, 0, getWidth(), XYWH::lbl_section_h };
	g.drawText("Message Logs", lbl_section_area.translated(0, -3), Justification::centredTop);
}

void Msg_Logs::resized() {
	tabs.setBounds(0, XYWH::lbl_section_h, getWidth(), getHeight() - XYWH::lbl_section_h);
	btn_clear.setTopRightPosition(getWidth(), getHeight() - XYWH::btn_h);
	btn_jump.setTopRightPosition(btn_clear.getX() - 5, btn_clear.getY());
}

void Msg_Logs::clear_visible_table() {
	switch (tabs.getCurrentTabIndex()) {
	case Tab__Log::incoming:
		in_log->clear_table();
		return;
	case Tab__Log::outgoing:
		out_log->clear_table();
		return;
	case Tab__Log::compare:
		compare->clear_table();
		return;
	default:
		return;
	}
}

void Msg_Logs::set_next_cmd_target_for_tabs(ApplicationCommandTarget* new_target) {
	tab_incoming->set_next_cmd_target(new_target);
	tab_outgoing->set_next_cmd_target(new_target);
	tab_compare->set_next_cmd_target(new_target);
}

void Msg_Logs::changeListenerCallback(ChangeBroadcaster* /*source*/) {
	match_btn_color_to_visible_tab();
}

ApplicationCommandTarget* Msg_Logs::getNextCommandTarget() {
	switch (tabs.getCurrentTabIndex()) {
	case Tab__Log::incoming:
		return tab_incoming.get();
	case Tab__Log::outgoing:
		return tab_outgoing.get();
	case Tab__Log::compare:
		return tab_compare.get();
	default:
		return nullptr;
	}
}

void Msg_Logs::getAllCommands(Array<int>& cmd_list) {
	cmd_list.add(show_tab__incoming,
				 show_tab__outgoing,
				 show_tab__compare);
}

void Msg_Logs::getCommandInfo(int cmd, ApplicationCommandInfo& info) {
	switch (cmd) {
	case show_tab__incoming:
		info.setInfo("Incoming tab", "Show incoming messages log", "Logs", 0);
		info.addDefaultKeypress('i', ModifierKeys::altModifier);
		break;
	case show_tab__outgoing:
		info.setInfo("Outgoing tab", "Show outgoing messages log", "Logs", 0);
		info.addDefaultKeypress('o', ModifierKeys::altModifier);
		break;
	case show_tab__compare:
		info.setInfo("Compare tab", "Show message comparison", "Logs", 0);
		info.addDefaultKeypress('=', ModifierKeys::altModifier);
		break;
	default:
		break;
	}
}

bool Msg_Logs::perform(const InvocationInfo& info) {
	switch (info.commandID) {
	case show_tab__incoming:
		tabs.setCurrentTabIndex(Tab__Log::incoming);
		return true;
	case show_tab__outgoing:
		tabs.setCurrentTabIndex(Tab__Log::outgoing);
		return true;
	case show_tab__compare:
		tabs.setCurrentTabIndex(Tab__Log::compare);
		return true;
	default:
		break;
	}
	return false;
}

Msg_Logs::~Msg_Logs() {
	tabs.getTabbedButtonBar().removeChangeListener(this);
	tab_incoming.reset();
	tab_outgoing.reset();
	tab_compare.reset();
	removeKeyListener(cmd_mngr.getKeyMappings());
}
