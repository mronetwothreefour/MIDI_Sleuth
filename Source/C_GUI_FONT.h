#pragma once

#include <JuceHeader.h>

namespace FONT
{

	struct Create_Font {
		static Font with_typeface_and_point_height(Typeface::Ptr typeface, float point_height) {
			Font font{ FontOptions{ typeface } };
			return font.withPointHeight(point_height * 1.33333f); // account for height discrepancy between Inkscape & Juce
		}
	};

	const Typeface::Ptr face_hvy{ Typeface::createSystemTypefaceFor(BinaryData::SEGUIBL_0_TTF, BinaryData::SEGUIBL_0_TTFSize) };
	const Typeface::Ptr face_reg{ Typeface::createSystemTypefaceFor(BinaryData::SEGOEUI_0_TTF, BinaryData::SEGOEUI_0_TTFSize) };
	const Typeface::Ptr face_sbld{ Typeface::createSystemTypefaceFor(BinaryData::SEGUISB_0_TTF, BinaryData::SEGUISB_0_TTFSize) };

	const Font btn{ Create_Font::with_typeface_and_point_height(face_sbld, 9.0f) };
	const Font dele_device{ Create_Font::with_typeface_and_point_height(face_sbld, 10.5f) };
	const Font table_cell{ Create_Font::with_typeface_and_point_height(face_reg, 9.0f) };
	const Font table_header{ Create_Font::with_typeface_and_point_height(face_sbld, 9.0f) };
	const Font table_header_byte{ Create_Font::with_typeface_and_point_height(face_sbld, 6.75) };
	const Font lbl_filter{ Create_Font::with_typeface_and_point_height(face_reg, 10.5f) };
	const Font lbl_jump_to_byte{ Create_Font::with_typeface_and_point_height(face_sbld, 11.25f) };
	const Font lbl_section{ Create_Font::with_typeface_and_point_height(face_sbld, 11.25f) };
	const Font popup_itm{ Create_Font::with_typeface_and_point_height(face_sbld, 9.0f) };
	const Font popup_shortcut{ Create_Font::with_typeface_and_point_height(face_sbld, 6.75f) };
	const Font tab{ Create_Font::with_typeface_and_point_height(face_reg, 8.25f) };
	const Font tips{ Create_Font::with_typeface_and_point_height(face_reg, 9.0f) };
	const Font txt_edit_jump_to_byte{ Create_Font::with_typeface_and_point_height(face_reg, 9.0f) };

}
