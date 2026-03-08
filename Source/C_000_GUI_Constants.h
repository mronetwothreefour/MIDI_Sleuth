#pragma once

#include <JuceHeader.h>

namespace COLOR
{

const Colour background{ 0xff202020 };
const Colour highlight{ 0xff333333 };
const Colour list_background{ 0xff000000 };
const Colour table_background{ 0xff000000 };
const Colour text{ 0xffffffff };

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

const Font button{ Create_Font::with_typeface_and_point_height(type_bold, 17.0f) };
const Font device_list{ Create_Font::with_typeface_and_point_height(type_semibold, 14.0f) };
const Font device_list_header{ Create_Font::with_typeface_and_point_height(type_bold, 18.0f) };
const Font filter_label{ Create_Font::with_typeface_and_point_height(type_bold, 15.0f) };
const Font msg_slot_header{ Create_Font::with_typeface_and_point_height(type_bold, 18.0f) };
const Font table{ Create_Font::with_typeface_and_point_height(type_regular, 15.0f) };
const Font table_header{ Create_Font::with_typeface_and_point_height(type_semibold, 15.0f) };

}

namespace XYWH
{
	
constexpr int chkbox_w{ 15 }, chkbox_h{ 15 };
constexpr int device_list_min_w{ 395 }, device_list_h{ 100 };
constexpr int lbl_device_list_h{ 25 };
constexpr int lbl_msg_slot_w{ 130 }, lbl_msg_slot_h{ 25 };
constexpr int log_area_y{ 270 };
constexpr int log_area_min_w{ 810 }, log_area_min_h{ 320 };
constexpr int main_win_init_w{ 850 }, main_win_init_h{ 655 };
constexpr int margin{ 20 };
constexpr int menu_h{ 30 };
constexpr int msg_slot_w{ 130 }, msg_slot_h{ 55 };
constexpr int msg_slots_y{ 163 };
constexpr int msg_slots_w{ 810 }, msg_slots_h{ 55 };
	
static const Rectangle<int> btn_msg_slot_label {   0,   0,  60,  30 };
static const Rectangle<int> btn_msg_slot_edit  {   0,  25,  60,  30 };
static const Rectangle<int> btn_msg_slot_send  {  70,  25,  60,  30 };

}