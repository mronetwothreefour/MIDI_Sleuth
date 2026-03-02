#include "G_400_Tabbed_Component_In_Out_Logs.h"

Tabbed_Component_In_Out_Logs::Tabbed_Component_In_Out_Logs(Tree_MIDI_Message_Log& in_log, Tree_MIDI_Message_Log& out_log) :
	TabbedComponent{ TabbedButtonBar::TabsAtBottom },
	tab_in_log{ in_log },
	tab_out_log{ out_log }
{
	setTabBarDepth(25);
	setOutline(1);
	Colour background_color{ 0xff202020 };
	addTab("Incoming", background_color, &tab_in_log, true);
	addTab("Outgoing", background_color, &tab_out_log, true);
	setColour(backgroundColourId, background_color);
	setWantsKeyboardFocus(true);
}

void Tabbed_Component_In_Out_Logs::scroll_to_row(const bool scrolling_in_log, const int row_num) {
	if (scrolling_in_log)
		tab_in_log.scroll_to_row(row_num);
	else
		tab_out_log.scroll_to_row(row_num);
}

bool Tabbed_Component_In_Out_Logs::keyPressed(const KeyPress& key) {
	if (key == KeyPress{ 'i', ModifierKeys::altModifier, 0 })
		setCurrentTabIndex(0);
	if (key == KeyPress{ 'o', ModifierKeys::altModifier, 0 })
		setCurrentTabIndex(1);
	return false;
}
