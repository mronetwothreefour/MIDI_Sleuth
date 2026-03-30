#pragma once

#include <JuceHeader.h>

#include "C_ENUM.h"
#include "D_Data_User.h"

using namespace ENUM;

class Table_Pop_Menu :
	public PopupMenu,
	public Data_User
{
//==============================================================================
public: Table_Pop_Menu(Data_Hub* hub) :
	Data_User{ hub }
{
	PopupMenu submenu_store_msg;
	for (int cmd_id = store_msg_in_slot_1; cmd_id <= store_msg_in_slot_5; ++cmd_id)
		submenu_store_msg.addCommandItem(&cmd_mngr, cmd_id);
	addSubMenu("Store last-selected message in", submenu_store_msg);
	addCommandItem(&cmd_mngr, copy_msg_no_sep);
	PopupMenu submenu_copy_msg;
	for (int cmd_id = copy_msg_spc_sep; cmd_id <= copy_msg_nl_sep; ++cmd_id)
		submenu_copy_msg.addCommandItem(&cmd_mngr, cmd_id);
	addSubMenu("Copy message bytes, separated by", submenu_copy_msg);
	addCommandItem(&cmd_mngr, compare_messages);
}

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Table_Pop_Menu)

};