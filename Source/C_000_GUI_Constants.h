#pragma once

#include <JuceHeader.h>

namespace COLOR
{

	Colour background{ 0xff202020 };
	Colour highlight{ 0xff333333 };
	Colour text{ 0xffffffff };

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
	const Font device_list{ Create_Font::with_typeface_and_point_height(type_regular, 15.0f) };
	const Font device_list_header{ Create_Font::with_typeface_and_point_height(type_bold, 18.0f) };
	const Font filter_label{ Create_Font::with_typeface_and_point_height(type_bold, 15.0f) };
	const Font msg_slot_header{ Create_Font::with_typeface_and_point_height(type_bold, 18.0f) };
	const Font table{ Create_Font::with_typeface_and_point_height(type_regular, 15.0f) };
	const Font table_header{ Create_Font::with_typeface_and_point_height(type_semibold, 15.0f) };

}