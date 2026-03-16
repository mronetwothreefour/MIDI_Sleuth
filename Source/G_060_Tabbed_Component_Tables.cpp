#include "G_060_Tabbed_Component_Tables.h"

Tabbed_Component_Tables::Tabbed_Component_Tables(Data_Hub* hub) :
	TabbedComponent{ TabbedButtonBar::TabsAtBottom },
	Data_User{ hub },
	tab_in_log{ hub, in_log, true },
	tab_out_log{ hub, out_log, true },
	tab_compare{ hub, compare, false }
{
	setTabBarDepth(XYWH::tab_h);
	addTab("Incoming", COLOR::list_background, &tab_in_log, true);
	addTab("Outgoing", COLOR::list_background, &tab_out_log, true);
	addTab("Compare", COLOR::list_background, &tab_compare, true);

	cmd_mngr.registerAllCommandsForTarget(this);
}

void Tabbed_Component_Tables::scroll_to_row(const Tab visible_tab, const int row_num) {
	switch (visible_tab) {
	case Tab::incoming:
		tab_in_log.scroll_to_row(row_num);
		break;
	case Tab::outgoing:
		tab_out_log.scroll_to_row(row_num);
		break;
	case Tab::compare:
		tab_compare.scroll_to_row(row_num);
		break;
	default:
		break;
	}
}

const String Tabbed_Component_Tables::get_bytes_for_selected_row_in_current_tab() {
	switch (getCurrentTabIndex()) {
	case Tab::incoming:
		return tab_in_log.get_bytes_for_first_selected_row();
	case Tab::outgoing:
		return tab_out_log.get_bytes_for_first_selected_row();
	case Tab::compare:
		return tab_compare.get_bytes_for_first_selected_row();
	default:
		return String{};
	}
}

ApplicationCommandTarget* Tabbed_Component_Tables::getNextCommandTarget() {
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

void Tabbed_Component_Tables::getAllCommands(Array<int>& cmd_list) {
	cmd_list.add(show_tab_incoming,
				 show_tab_outgoing,
				 show_tab_compare);
}

void Tabbed_Component_Tables::getCommandInfo(int cmd, ApplicationCommandInfo& info) {
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

bool Tabbed_Component_Tables::perform(const InvocationInfo& info) {
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


