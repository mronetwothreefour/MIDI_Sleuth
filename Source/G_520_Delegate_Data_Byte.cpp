#include "G_520_Delegate_Data_Byte.h"

#include "C_000_GUI_Constants.h"

Delegate_Data_Byte::Delegate_Data_Byte(const int row_num, const int col_num, Tree_MIDI_Messages* message_log) :
	row_num{ row_num },
	col_num{ col_num },
	message_log{ message_log }
{
	auto i = (col_num - 5) * 2;
	auto bytes_string = message_log->entry_bytes(row_num);
	auto byte_int = bytes_string.substring(i, i + 2).getHexValue32();
	String tooltip{ "Byte " + String{ i / 2 } };
	tooltip += "\nDecimal: ";
	tooltip << byte_int;
	tooltip += "\nBinary: 0";
	tooltip += byte_int & 64 ? "1" : "0";
	tooltip += byte_int & 32 ? "1" : "0";
	tooltip += byte_int & 16 ? "1" : "0";
	tooltip += byte_int & 8 ? "1" : "0";
	tooltip += byte_int & 4 ? "1" : "0";
	tooltip += byte_int & 2 ? "1" : "0";
	tooltip += byte_int & 1 ? "1" : "0";
	setTooltip(tooltip);
}

inline void Delegate_Data_Byte::paint(Graphics& g) {
	auto i = (col_num - 5) * 2;
	auto bytes_string = message_log->entry_bytes(row_num);
	auto text = bytes_string.substring(i, i + 2);
	g.setColour(COLOR::text);
	g.setFont(FONT::table);
	auto w = getWidth();
	auto h = getHeight();
	g.drawText(text, 2, 0, w - 4, h, Justification::centred);
	g.setColour(COLOR::outline);
	g.drawHorizontalLine(h - 1, 0.0f, w * 1.0f);
	g.drawVerticalLine(w - 1, 0.0f, h * 1.0f);
}
