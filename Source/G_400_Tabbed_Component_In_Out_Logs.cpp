#include "G_400_Tabbed_Component_In_Out_Logs.h"

Tabbed_Component_In_Out_Logs::Tabbed_Component_In_Out_Logs(Data_Hub* hub) :
	TabbedComponent{ TabbedButtonBar::TabsAtBottom },
	Data_User{ hub },
	tab_in_log{ in_log },
	tab_out_log{ out_log }
{
	setTabBarDepth(25);
	setOutline(1);
	addTab("Incoming", COLOR::background, &tab_in_log, true);
	addTab("Outgoing", COLOR::background, &tab_out_log, true);
	setColour(backgroundColourId, COLOR::background);
	setWantsKeyboardFocus(true);
}

void Tabbed_Component_In_Out_Logs::scroll_to_row(const bool scrolling_in_log, const int row_num) {
	if (scrolling_in_log)
		tab_in_log.scroll_to_row(row_num);
	else
		tab_out_log.scroll_to_row(row_num);
}

const String Tabbed_Component_In_Out_Logs::get_bytes_for_selected_row_in_current_tab() {
	auto tab_index = getCurrentTabIndex();
	if (tab_index == 0)
		return tab_in_log.get_bytes_for_first_selected_row();
	return tab_out_log.get_bytes_for_first_selected_row();
}


