#pragma once

#include <JuceHeader.h>

#include "C_010_Enums.h"
#include "D_100_Data_User.h"

using namespace ENUM;

class Popup_Menu_Table :
	public PopupMenu,
	public Data_User
{
//==============================================================================
public: Popup_Menu_Table(Data_Hub* hub) :
	Data_User{ hub }
{
	PopupMenu submenu_store_msg;
	for (int i = 0; i < 5; ++i)
		submenu_store_msg.addCommandItem(&cmd_mngr, store_msg_in_slot_1 + i);
	addSubMenu("Store last-selected message in", submenu_store_msg);
	addCommandItem(&cmd_mngr, compare_messages);
}

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Popup_Menu_Table)

};