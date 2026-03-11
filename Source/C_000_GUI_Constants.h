#pragma once

#include <JuceHeader.h>

namespace COLOR
{

const Colour background{ 0xff202020 };
const Colour button{ 0xff333333 };
const Colour button_down{ 0xff505050 };
const Colour highlight{ 0xff333333 };
const Colour list_background{ 0xff000000 };
const Colour outline{ 0xff808080 };
const Colour text{ 0xffffffff };
const Colour toggle_off{ 0xff000000 };
const Colour toggle_on{ 0xff606060 };

}

namespace FONT
{

struct Create_Font {
	static Font with_typeface_and_point_height(Typeface::Ptr typeface, float point_height) {
		Font font{ FontOptions{ typeface } };
		return font.withPointHeight(point_height);
	}
};

const Typeface::Ptr type_bold{ Typeface::createSystemTypefaceFor(BinaryData::SEGOEUIB_0_TTF, BinaryData::SEGOEUIB_0_TTFSize) };
const Typeface::Ptr type_regular{ Typeface::createSystemTypefaceFor(BinaryData::SEGOEUI_0_TTF, BinaryData::SEGOEUI_0_TTFSize) };
const Typeface::Ptr type_semibold{ Typeface::createSystemTypefaceFor(BinaryData::SEGUISB_0_TTF, BinaryData::SEGUISB_0_TTFSize) };

const Font button{ Create_Font::with_typeface_and_point_height(type_bold, 15.0f) };
const Font device_list{ Create_Font::with_typeface_and_point_height(type_semibold, 14.0f) };
const Font device_list_header{ Create_Font::with_typeface_and_point_height(type_bold, 17.0f) };
const Font filter_label{ Create_Font::with_typeface_and_point_height(type_bold, 14.0f) };
const Font msg_slot_header{ Create_Font::with_typeface_and_point_height(type_bold, 18.0f) };
const Font table{ Create_Font::with_typeface_and_point_height(type_regular, 12.0f) };
const Font table_header{ Create_Font::with_typeface_and_point_height(type_semibold, 12.0f) };
const Font table_byte_header{ Create_Font::with_typeface_and_point_height(type_semibold, 9.0f) };

}

namespace XYWH
{
	
constexpr int btn_clear_reset_w{ 80 }, btn_clear_reset_h{ 30 };
constexpr int device_list_min_w{ 395 }, device_list_h{ 100 };
constexpr int lbl_device_list_h{ 25 };
constexpr int lbl_msg_slot_w{ 130 }, lbl_msg_slot_h{ 25 };
constexpr int log_area_y{ 270 };
constexpr int log_area_min_w{ 810 }, log_area_min_h{ 325 };
constexpr int main_win_components_min_w{ 810 }, main_win_components_min_h{ 615 };
constexpr int main_win_init_w{ 850 }, main_win_init_h{ 655 };
constexpr int margin{ 20 };
constexpr int menu_h{ 30 };
constexpr int msg_slot_w{ 130 }, msg_slot_h{ 55 };
constexpr int msg_slots_y{ 163 };
constexpr int msg_slots_w{ 810 }, msg_slots_h{ 55 };
constexpr int filters_y{ 235 }, filters_w{ 810 }, filters_h{ 19 };

static const Rectangle<int> msg_slot_lbl       { 0  , 0  , 60 , 30  };
static const Rectangle<int> msg_slot_btn_edit  { 0  , 25 , 60 , 30  };
static const Rectangle<int> msg_slot_btn_send  { 70 , 25 , 60 , 30  };
	
static const Rectangle<int> filters_lbl_include         { 0  , 0  , 55 , 19  };
static const Rectangle<int> filters_tgl_note_on_off     { 64 , 2  , 15 , 15  };
static const Rectangle<int> filters_lbl_note_on_off     { 84 , 0  , 90 , 19 };
static const Rectangle<int> filters_tgl_aftertouch_bend { 186, 2  , 15 , 15  };
static const Rectangle<int> filters_lbl_aftertouch_bend { 206, 0  , 160, 19 };
static const Rectangle<int> filters_tgl_pgm_change      { 378, 2  , 15 , 15  };
static const Rectangle<int> filters_lbl_pgm_change      { 398, 0  , 120, 19 };
static const Rectangle<int> filters_tgl_ctrl_change     { 531, 2  , 15 , 15  };
static const Rectangle<int> filters_lbl_ctrl_change     { 551, 0  , 110, 19 };
static const Rectangle<int> filters_tgl_sysex           { 674, 2  , 15 , 15  };
static const Rectangle<int> filters_lbl_sysex           { 694, 0  , 120, 19 };

}