#include "G_Table_Tabs.h"

Table_Tabs::Table_Tabs(Data_Hub* hub) :
	TabbedComponent{ TabbedButtonBar::TabsAtBottom },
	Data_User{ hub },
	tab_in_log{ log_in, hub },
	tab_out_log{ log_out, hub },
	tab_compare{ compare_msg, hub }
{
	setTabBarDepth(XYWH::tab_h);
	addTab("Incoming", COLOR::table_bkgrnd, &tab_in_log, true);
	addTab("Outgoing", COLOR::table_bkgrnd, &tab_out_log, true);
	addTab("Compare", COLOR::table_bkgrnd, &tab_compare, true);

	cmd_mngr.registerAllCommandsForTarget(this);
}

void Table_Tabs::clear_visible_table() {
	switch (getCurrentTabIndex()) {
	case Tab::incoming:
		in_log->clear_log();
		return;
	case Tab::outgoing:
		out_log->clear_log();
		return;
	case Tab::compare:
		compare->clear_log();
		return;
	default:
		return;
	}
}

ApplicationCommandTarget* Table_Tabs::getNextCommandTarget() {
	switch (getCurrentTabIndex()) {
	case Tab::incoming:
		return &tab_in_log;
	case Tab::outgoing:
		return &tab_out_log;
	case Tab::compare:
		return &tab_compare;
	default:
		return findFirstTargetParentComponent();
	}
}

void Table_Tabs::getAllCommands(Array<int>& cmd_list) {
	cmd_list.add(show_tab_incoming,
				 show_tab_outgoing,
				 show_tab_compare);
}

void Table_Tabs::getCommandInfo(int cmd, ApplicationCommandInfo& info) {
	switch (cmd) {
	case show_tab_incoming:
		info.setInfo("Incoming tab", "Show incoming messages log", "Show Tab", 0);
		info.addDefaultKeypress('i', ModifierKeys::altModifier);
		break;
	case show_tab_outgoing:
		info.setInfo("Outgoing tab", "Show outgoing messages log", "Show Tab", 0);
		info.addDefaultKeypress('o', ModifierKeys::altModifier);
		break;
	case show_tab_compare:
		info.setInfo("Comparison tab", "Show message comparison", "Keystroke", 0);
		info.addDefaultKeypress('=', ModifierKeys::altModifier);
		break;
	default:
		break;
	}
}

bool Table_Tabs::perform(const InvocationInfo& info) {
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
