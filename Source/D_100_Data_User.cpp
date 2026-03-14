#include "D_100_Data_User.h"

Data_User::Data_User(Data_Hub* hub) :
	hub{ hub },
	in_log{ hub->get_tree_in_log() },
	out_log{ hub->get_tree_out_log() },
	compare{ hub->get_tree_compare() },
	cmd_mngr{ hub->get_command_manager() }
{
}

const String& Data_User::message_in_slot(const int slot_index) {
	return hub->get_message_slots()[slot_index];
}

void Data_User::set_message_in_slot(const String& msg, const int slot_index) {
	if (slot_index > -1 && slot_index < 5)
		hub->get_message_slots().set(slot_index, msg);
}

bool Data_User::should_log(Message_Type msg_type) {
	return hub->msg_type_flags & msg_type;
}

void Data_User::set_should_log(Message_Type msg_type, bool should_log) {
	if (should_log)
		hub->msg_type_flags |= msg_type;
	else
		hub->msg_type_flags &= ~msg_type;
}

