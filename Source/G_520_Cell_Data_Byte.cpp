#include "G_520_Cell_Data_Byte.h"

Cell_Data_Byte::Cell_Data_Byte(const int row_num, const int col_num, Tree_MIDI_Message_Log& message_log) :
	row_num{ row_num },
	col_num{ col_num },
	message_log{ message_log }
{
	auto i = (col_num - 5) * 2;
	auto bytes_string = message_log.entry_bytes(row_num);
	auto byte_int = bytes_string.substring(i, i + 2).getHexValue32();
	String tooltip{ "Decimal: " };
	tooltip << byte_int;
	tooltip += "\n Binary: 0";
	tooltip += byte_int & 64 ? "1" : "0";
	tooltip += byte_int & 32 ? "1" : "0";
	tooltip += byte_int & 16 ? "1" : "0";
	tooltip += byte_int & 8 ? "1" : "0";
	tooltip += byte_int & 4 ? "1" : "0";
	tooltip += byte_int & 2 ? "1" : "0";
	tooltip += byte_int & 1 ? "1" : "0";
	setTooltip(tooltip);
}

inline void Cell_Data_Byte::paint(Graphics& g) {
	auto i = (col_num - 5) * 2;
	auto bytes_string = message_log.entry_bytes(row_num);
	auto text = bytes_string.substring(i, i + 2);
	g.setColour(getLookAndFeel().findColour(ListBox::textColourId));
	g.setFont(Font{ FontOptions{ 13.0f } });
	auto w = getWidth();
	auto h = getHeight();
	g.drawText(text, 2, 0, w - 4, h, Justification::centred);
	g.drawHorizontalLine(h - 1, 0.0f, w * 1.0f);
	g.drawVerticalLine(w - 1, 0.0f, h * 1.0f);
}
