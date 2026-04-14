#pragma once

namespace ENUM
{

	const enum Command {
		compare_messages = 1,
		copy_msg__log__no_sep,
		copy_msg__log__spc_sep,
		copy_msg__log__tab_sep,
		copy_msg__log__comma_sep,
		copy_msg__log__nl_sep,
		copy_msg__slot__no_sep,
		copy_msg__slot__spc_sep,
		copy_msg__slot__tab_sep,
		copy_msg__slot__comma_sep,
		copy_msg__slot__nl_sep,
		jump_to_byte__log,
		jump_to_byte__slot,
		msg_byte_delete,
		msg_byte_insert,
		msg_export,
		msg_import,
		msg_paste,
		show_tab__incoming,
		show_tab__outgoing,
		show_tab__compare,
		show_tab__slot_1,
		show_tab__slot_2,
		show_tab__slot_3,
		show_tab__slot_4,
		show_tab__slot_5,
		store_msg__slot_1,
		store_msg__slot_2,
		store_msg__slot_3,
		store_msg__slot_4,
		store_msg__slot_5,
		transmit_msg__slot_1,
		transmit_msg__slot_2,
		transmit_msg__slot_3,
		transmit_msg__slot_4,
		transmit_msg__slot_5,
		toggle_tab__devices
	};

	const enum Msg_Type {
		note_on_off = 1,
		aftertouch_bend = 2,
		ctrl_change = 4,
		pgm_change = 8,
		sysex = 16
	};

	const enum Byte_Separator {
		none = 0,
		space,
		tab,
		newline
	};

	const enum Tab__Devices {
		inputs = 0,
		outputs
	};

	const enum Tab__Log {
		incoming = 0,
		outgoing,
		compare
	};

	const enum Tab__Slot {
		slot_1 = 0,
		slot_2,
		slot_3,
		slot_4,
		slot_5
	};

	const enum Table_Type {
		log_in = 0,
		log_out,
		comparison,
		msg_slot_1,
		msg_slot_2,
		msg_slot_3,
		msg_slot_4,
		msg_slot_5
	};

}
