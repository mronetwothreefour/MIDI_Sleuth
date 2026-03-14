#include "G_060_Tabbed_Component_Tables.h"

Tabbed_Component_Tables::Tabbed_Component_Tables(Data_Hub* hub) :
	TabbedComponent{ TabbedButtonBar::TabsAtBottom },
	Data_User{ hub },
	tab_in_log{ in_log },
	tab_out_log{ out_log }
{
	setTabBarDepth(XYWH::tab_h);
	addTab("Incoming", COLOR::list_background, &tab_in_log, true);
	addTab("Outgoing", COLOR::list_background, &tab_out_log, true);

	cmd_mngr.registerAllCommandsForTarget(this);
}

void Tabbed_Component_Tables::scroll_to_row(const bool scrolling_in_log, const int row_num) {
	if (scrolling_in_log)
		tab_in_log.scroll_to_row(row_num);
	else
		tab_out_log.scroll_to_row(row_num);
}

const String Tabbed_Component_Tables::get_bytes_for_selected_row_in_current_tab() {
	auto tab_index = getCurrentTabIndex();
	if (tab_index == 0)
		return tab_in_log.get_bytes_for_first_selected_row();
	return tab_out_log.get_bytes_for_first_selected_row();
}

ApplicationCommandTarget* Tabbed_Component_Tables::getNextCommandTarget() {
	return findFirstTargetParentComponent();
}

void Tabbed_Component_Tables::getAllCommands(Array<int>& cmd_list) {
	cmd_list.add(show_tab_incoming,
				 show_tab_outgoing,
				 show_tab_compare);
}

void Tabbed_Component_Tables::getCommandInfo(int cmd, ApplicationCommandInfo& info) {
	switch (cmd) {
	case show_tab_incoming:
		info.setInfo("Incoming tab", "Show incoming messages log", "Keystroke", 0);
		info.addDefaultKeypress('i', ModifierKeys::ctrlModifier);
		break;
	case show_tab_outgoing:
		info.setInfo("Outgoing tab", "Show outgoing messages log", "Keystroke", 0);
		info.addDefaultKeypress('o', ModifierKeys::ctrlModifier);
		break;
	case show_tab_compare:
		info.setInfo("Comparison tab", "Show message comparison", "Keystroke", 0);
		info.addDefaultKeypress('=', ModifierKeys::ctrlModifier);
		break;
	default:
		break;
	}
}

bool Tabbed_Component_Tables::perform(const InvocationInfo& info)
{
	switch (info.commandID) {
	case show_tab_incoming:
		setCurrentTabIndex(Tab::incoming);
		break;
	case show_tab_outgoing:
		setCurrentTabIndex(Tab::outgoing);
		break;
	case show_tab_compare:
		setCurrentTabIndex(Tab::compare);
		break;
	default:
		return false;
	}
	return true;
}


