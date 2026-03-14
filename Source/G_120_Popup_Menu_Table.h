#pragma once

#include <JuceHeader.h>

#include "C_010_Enums.h"

using namespace ENUM;

class Popup_Menu_Table :
	public PopupMenu
{
//==============================================================================
public: Popup_Menu_Table()
{
	PopupMenu submenu_store_msg;
	for (int i = 0; i < 5; ++i)
		submenu_store_msg.addItem(Command::store_msg_in_slot_1 + i, "Slot " + String{ i + 1 });
	addSubMenu("Store last-clicked message in", submenu_store_msg);
}

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Popup_Menu_Table)

};