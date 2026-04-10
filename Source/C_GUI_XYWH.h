#pragma once

#include <JuceHeader.h>

namespace XYWH
{

	constexpr int btn_h{ 20 };
	constexpr int btn_logs_w{ 65 };
	constexpr int btn_slots_w{ 65 };
	constexpr int jump_to_byte_dialog_w{ 160 }, jump_to_byte_dialog_h{ 115 };
	constexpr int lbl_section_h{ 20 };
	constexpr int logs_x{ 15 }, logs_y{ 180 }, logs_min_w{ 730 }, logs_min_h{ 315 };
	constexpr int logs_lbl_section_x{ 0 }, logs_lbl_section_y{ 0 };
	constexpr int logs_tabs_x{ 0 }, logs_tabs_y{ 20 }, logs_tabs_min_h{ 295 };
	constexpr int slots_x{ 15 }, slots_min_w{ 730 }, slots_h{ 315 };
	constexpr int slots_lbl_section_x{ 0 }, slots_lbl_section_y{ 0 };
	constexpr int slots_tabs_x{ 0 }, slots_tabs_y{ 20 }, slots_tabs_h{ 65 };
	constexpr int tips_max_w{ 400 };
	constexpr int tab_h{ 25 };
	constexpr int win_inset{ 15 };
	constexpr int win_main_comp_min_w{ 730 }, win_main_comp_min_h{ 615 };
	constexpr int win_main_init_w{ 760 }, win_main_init_h{ 645 };

	static const Rectangle<int> devices             { 15 , 15 , 385, 160 };
	static const Rectangle<int> devices_lbl_section { 0  , 0  , 385, 20  };
	static const Rectangle<int> devices_tabs        { 0  , 20 , 385, 140 };
	static const Rectangle<int> devices_btn_reset   { 325, 140, 60 , 20  };

	static const Rectangle<int> filters                 { 420, 15 , 170, 165 };
	static const Rectangle<int> filters_lbl_section     { 0  , 0  , 170, 20  };
	static const Rectangle<int> filters_tgl_note        { 0  , 25 , 15 , 15  };
	static const Rectangle<int> filters_lbl_note        { 25 , 24 , 145, 17  };
	static const Rectangle<int> filters_tgl_bend        { 0  , 55 , 15 , 15  };
	static const Rectangle<int> filters_lbl_bend        { 25 , 54 , 145, 17  };
	static const Rectangle<int> filters_tgl_pgm_change  { 0  , 85 , 15 , 15  };
	static const Rectangle<int> filters_lbl_pgm_change  { 25 , 84 , 145, 17  };
	static const Rectangle<int> filters_tgl_ctrl_change { 0  , 115, 15 , 15  };
	static const Rectangle<int> filters_lbl_ctrl_change { 25 , 114, 145, 17  };
	static const Rectangle<int> filters_tgl_sysex       { 0  , 145, 15 , 15  };
	static const Rectangle<int> filters_lbl_sysex       { 25 , 144, 145, 17  };

	static const Rectangle<int> jump_to_byte_lbl        { 15 , 10 , 130, 25 };
	static const Rectangle<int> jump_to_byte_txt_edit   { 15 , 35 , 130, 25 };
	static const Rectangle<int> jump_to_byte_btn_cancel { 15 , 70 , 60 , 30 };
	static const Rectangle<int> jump_to_byte_btn_jump   { 85 , 70 , 60 , 30 };

}