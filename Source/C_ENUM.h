#pragma once

namespace ENUM
{

	const enum Command {
		compare_messages = 1,
		copy_msg_no_sep,
		copy_msg_spc_sep,
		copy_msg_tab_sep,
		copy_msg_comma_sep,
		copy_msg_nl_sep,
		edit_msg_in_slot_1,
		edit_msg_in_slot_2,
		edit_msg_in_slot_3,
		edit_msg_in_slot_4,
		edit_msg_in_slot_5,
		export_messages,
		jump_to_byte_in_log,
		jump_to_byte_in_slot,
		show_tab_incoming,
		show_tab_outgoing,
		show_tab_compare,
		store_msg_in_slot_1,
		store_msg_in_slot_2,
		store_msg_in_slot_3,
		store_msg_in_slot_4,
		store_msg_in_slot_5
	};

	const enum Message_Type {
		note_on_off = 1,
		aftertouch_pitch_bend = 2,
		ctrl_change = 4,
		pgm_change = 8,
		sysex = 16
	};

	const enum Separators {
		none = 0,
		space,
		tab,
		newline
	};

	const enum Tab {
		incoming = 0,
		outgoing,
		compare
	};

	const enum Table_Type {
		log_in = 0,
		log_out,
		compare_msg,
		msg_slot_1,
		msg_slot_2,
		msg_slot_3,
		msg_slot_4,
		msg_slot_5
	};

}
