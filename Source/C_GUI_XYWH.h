#pragma once

#include <JuceHeader.h>

namespace XYWH
{

	constexpr int btn_h{ 20 };
	constexpr int btn_logs_w{ 65 };
	constexpr int btn_slots_w{ 65 };
	constexpr int jump_to_byte_dialog_w{ 130 }, jump_to_byte_dialog_h{ 105 };
	constexpr int lbl_section_h{ 20 };
	constexpr int logs_x{ 15 }, logs_y{ 195 }, logs_min_w{ 730 }, logs_min_h{ 290 };
	constexpr int logs_tabs_min_h{ 270 };
	constexpr int slots_lbl_section_x{ 0 }, slots_lbl_section_y{ 0 };
	constexpr int slots_x{ 15 }, slots_min_w{ 730 }, slots_h{ 130 };
	constexpr int tips_max_w{ 400 };
	constexpr int tab_h{ 25 };
	constexpr int win_inset{ 15 };
	constexpr int win_main_tables_min_w{ 730 }, win_main_comp_min_h{ 630 };
	constexpr int win_main_init_w{ 760 }, win_main_init_h{ 660 };

	static const Rectangle<int> devices             { 15 , 15 , 385, 160 };
	static const Rectangle<int> devices_lbl_section { 0  , 0  , 385, 20  };
	static const Rectangle<int> devices_tabs        { 0  , 20 , 385, 140 };
	static const Rectangle<int> devices_btn_reset   { 325, 140, 60 , 20  };

	static const Rectangle<int> filters                 { 420, 15 , 175, 165 };
	static const Rectangle<int> filters_lbl_section     { 0  , 0  , 175, 20  };
	static const Rectangle<int> filters_tgl_note        { 0  , 25 , 15 , 15  };
	static const Rectangle<int> filters_lbl_note        { 22 , 24 , 153, 17  };
	static const Rectangle<int> filters_tgl_bend        { 0  , 55 , 15 , 15  };
	static const Rectangle<int> filters_lbl_bend        { 22 , 54 , 153, 17  };
	static const Rectangle<int> filters_tgl_pgm_change  { 0  , 85 , 15 , 15  };
	static const Rectangle<int> filters_lbl_pgm_change  { 22 , 84 , 153, 17  };
	static const Rectangle<int> filters_tgl_ctrl_change { 0  , 115, 15 , 15  };
	static const Rectangle<int> filters_lbl_ctrl_change { 22 , 114, 153, 17  };
	static const Rectangle<int> filters_tgl_sysex       { 0  , 145, 15 , 15  };
	static const Rectangle<int> filters_lbl_sysex       { 22 , 144, 153, 17  };

	static const Rectangle<int> jump_to_byte_lbl        { 15 , 10 , 100, 25 };
	static const Rectangle<int> jump_to_byte_txt_edit   { 15 , 35 , 100, 25 };
	static const Rectangle<int> jump_to_byte_btn_cancel { 15 , 70 , 45 , 20 };
	static const Rectangle<int> jump_to_byte_btn_jump   { 70 , 70 , 45 , 20 };

}