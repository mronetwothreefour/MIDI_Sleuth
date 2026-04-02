#pragma once

#include <JuceHeader.h>

namespace FONT
{

	struct Create_Font {
		static Font with_typeface_and_point_height(Typeface::Ptr typeface, float point_height) {
			Font font{ FontOptions{ typeface } };
			return font.withPointHeight(point_height);
		}
	};

	const Typeface::Ptr face_bld{ Typeface::createSystemTypefaceFor(BinaryData::SEGOEUIB_0_TTF, BinaryData::SEGOEUIB_0_TTFSize) };
	const Typeface::Ptr face_reg{ Typeface::createSystemTypefaceFor(BinaryData::SEGOEUI_0_TTF, BinaryData::SEGOEUI_0_TTFSize) };
	const Typeface::Ptr face_sbld{ Typeface::createSystemTypefaceFor(BinaryData::SEGUISB_0_TTF, BinaryData::SEGUISB_0_TTFSize) };

	const Font btn{ Create_Font::with_typeface_and_point_height(face_bld, 15.0f) };
	const Font dele_device{ Create_Font::with_typeface_and_point_height(face_sbld, 14.0f) };
	const Font table_cell{ Create_Font::with_typeface_and_point_height(face_reg, 12.0f) };
	const Font header{ Create_Font::with_typeface_and_point_height(face_sbld, 12.0f) };
	const Font header_byte{ Create_Font::with_typeface_and_point_height(face_sbld, 9.0f) };
	const Font lbl_filter{ Create_Font::with_typeface_and_point_height(face_bld, 14.0f) };
	const Font lbl_lbox_device{ Create_Font::with_typeface_and_point_height(face_bld, 17.0f) };
	const Font lbl_msg_slot{ Create_Font::with_typeface_and_point_height(face_bld, 17.0f) };
	const Font lbl_description{ Create_Font::with_typeface_and_point_height(face_bld, 17.0f) };
	const Font lbl_jump_to_byte{ Create_Font::with_typeface_and_point_height(face_sbld, 15.0f) };
	const Font popup_itm{ Create_Font::with_typeface_and_point_height(face_sbld, 12.0f) };
	const Font popup_shortcut{ Create_Font::with_typeface_and_point_height(face_sbld, 9.0f) };
	const Font tab{ Create_Font::with_typeface_and_point_height(face_bld, 12.0f) };
	const Font tips{ Create_Font::with_typeface_and_point_height(face_reg, 12.0f) };
	const Font txt_edit_description{ Create_Font::with_typeface_and_point_height(face_sbld, 14.0f) };
	const Font txt_edit_jump_to_byte{ Create_Font::with_typeface_and_point_height(face_reg, 12.0f) };

}
