#pragma once

#include <JuceHeader.h>

namespace XYWH
{

	constexpr int btn_h{ 30 };
	constexpr int btn_clear_reset_w{ 80 };
	constexpr int filters_y{ 235 }, filters_w{ 810 }, filters_h{ 19 };
	constexpr int jump_to_byte_dialog_w{ 160 }, jump_to_byte_dialog_h{ 115 };
	constexpr int lbl_lbox_devices_h{ 25 };
	constexpr int lbox_devices_min_w{ 395 }, lbox_devices_h{ 100 };
	constexpr int msg_slot_w{ 130 }, msg_slot_h{ 55 };
	constexpr int msg_slots_w{ 810 }, msg_slots_h{ 55 };
	constexpr int msg_slots_y{ 163 };
	constexpr int tab_h{ 25 };
	constexpr int tables_min_w{ 810 }, tables_min_h{ 325 };
	constexpr int tables_y{ 270 };
	constexpr int tips_max_w{ 400 };
	constexpr int win_edit_msg_w{ 680 }, win_edit_msg_h{ 154 };
	constexpr int win_main_inset{ 20 };
	constexpr int win_main_comp_min_w{ 810 }, win_main_comp_min_h{ 615 };
	constexpr int win_main_init_w{ 850 }, win_main_init_h{ 655 };

	static const Rectangle<int> edit_msg_table{ 15 , 15 , 650, 84 };
	static const Rectangle<int> edit_msg_lbl_description{ 15 , 109 , 100, 30 };
	static const Rectangle<int> edit_msg_edit_description{ 115 , 109 , 480, 30 };
	static const Rectangle<int> edit_msg_btn_send{ 605 , 109 , 60 , 30 };

	static const Rectangle<int> jump_to_byte_lbl{ 15 , 10 , 130, 25 };
	static const Rectangle<int> jump_to_byte_txt_edit{ 15 , 35 , 130, 25 };
	static const Rectangle<int> jump_to_byte_btn_cancel{ 15 , 70 , 60 , 30 };
	static const Rectangle<int> jump_to_byte_btn_jump{ 85 , 70 , 60 , 30 };

	static const Rectangle<int> msg_slot_lbl{ 0  , 0  , 130, 30 };
	static const Rectangle<int> msg_slot_btn_edit{ 0  , 25 , 60 , 30 };
	static const Rectangle<int> msg_slot_btn_send{ 70 , 25 , 60 , 30 };

	static const Rectangle<int> filters_lbl_include{ 0  , 0  , 55 , 19 };
	static const Rectangle<int> filters_tgl_note_on_off{ 64 , 2  , 15 , 15 };
	static const Rectangle<int> filters_lbl_note_on_off{ 84 , 0  , 90 , 19 };
	static const Rectangle<int> filters_tgl_aftertouch_bend{ 186, 2  , 15 , 15 };
	static const Rectangle<int> filters_lbl_aftertouch_bend{ 206, 0  , 160, 19 };
	static const Rectangle<int> filters_tgl_pgm_change{ 378, 2  , 15 , 15 };
	static const Rectangle<int> filters_lbl_pgm_change{ 398, 0  , 120, 19 };
	static const Rectangle<int> filters_tgl_ctrl_change{ 531, 2  , 15 , 15 };
	static const Rectangle<int> filters_lbl_ctrl_change{ 551, 0  , 110, 19 };
	static const Rectangle<int> filters_tgl_sysex{ 674, 2  , 15 , 15 };
	static const Rectangle<int> filters_lbl_sysex{ 694, 0  , 120, 19 };

}
