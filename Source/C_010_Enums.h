#pragma once

namespace ENUM
{

	const enum Command {
		show_tab_incoming = 1,
		show_tab_outgoing,
		show_tab_compare,
		store_msg_in_slot_1,
		store_msg_in_slot_2,
		store_msg_in_slot_3,
		store_msg_in_slot_4,
		store_msg_in_slot_5,
		export_messages,
		compare_messages,
		jump_to_byte
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

}
