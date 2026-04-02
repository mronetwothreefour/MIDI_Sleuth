#include "D_Data_User.h"

Data_User::Data_User(Data_Hub* hub) :
	hub{ hub },
	in_log{ hub->get_tree_in_log() },
	out_log{ hub->get_tree_out_log() },
	compare{ hub->get_tree_compare() },
	cmd_mngr{ hub->get_command_manager() }
{}

bool Data_User::should_be_logged(Message_Type msg_type) {
	return hub->msg_filter_flags & msg_type;
}

void Data_User::set_should_be_logged(Message_Type msg_type, bool should_log) {
	if (should_log)
		hub->msg_filter_flags |= msg_type;
	else
		hub->msg_filter_flags &= ~msg_type;
}

Data_Tree* Data_User::msg_slot(const int slot_index) {
	return hub->get_tree_msg_slot(slot_index);
}
