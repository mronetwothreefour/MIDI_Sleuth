#pragma once

#include <JuceHeader.h>

namespace FONT
{

	const FontOptions regular{ Typeface::createSystemTypefaceFor(BinaryData::SEGOEUI_0_TTF, BinaryData::SEGOEUI_0_TTFSize) };
	const FontOptions semibold{ Typeface::createSystemTypefaceFor(BinaryData::SEGUISB_0_TTF, BinaryData::SEGUISB_0_TTFSize) };

	const float h_scaler{ 1.33333f }; // accounts for point height discrepancy between Inkscape & Juce
	const Font btn{ semibold.withPointHeight(8.25f * h_scaler) };
	const Font btn_uline{ semibold.withPointHeight(8.25f * h_scaler).withUnderline() };
	const Font lbl_filter{ semibold.withPointHeight(10.5f * h_scaler) };
	const Font lbl_filter_uline{ semibold.withPointHeight(10.5f * h_scaler).withUnderline() };
	const Font lbl_jump_to_byte{ semibold.withPointHeight(10.5f * h_scaler) };
	const Font lbl_section{ semibold.withPointHeight(11.25f * h_scaler) };
	const Font lbox_item{ semibold.withPointHeight(9.75f * h_scaler) };
	const Font popup_itm{ semibold.withPointHeight(9.0f * h_scaler) };
	const Font popup_shortcut{ semibold.withPointHeight(6.75f * h_scaler) };
	const Font tab{ semibold.withPointHeight(8.25f * h_scaler) };
	const Font table_cell{ regular.withPointHeight(9.0f * h_scaler) };
	const Font table_header{ semibold.withPointHeight(9.0f * h_scaler) };
	const Font table_header_byte{ semibold.withPointHeight(6.75f * h_scaler) };
	const Font tips{ regular.withPointHeight(9.0f * h_scaler) };
	const Font txt_edit_jump_to_byte{ regular.withPointHeight(9.0f * h_scaler) };

}
