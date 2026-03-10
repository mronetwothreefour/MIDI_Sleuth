#include "G_090_Header_MIDI_Message_Log.h"

Header_MIDI_Message_Log::Header_MIDI_Message_Log()
{
	addColumn("#", 1, 30);
	addColumn("Timestamp", 2, 75);
	addColumn("Description", 3, 220);
	addColumn("Length", 4, 55);
}

const int Header_MIDI_Message_Log::byte_column_count() {
	return getNumColumns(true) - 4;
}

void Header_MIDI_Message_Log::add_data_byte_column(int byte_num) {
	auto col_id = byte_num + 5;
	if (col_id > getNumColumns(true)) {
		String col_name{ byte_num };
		auto num_digits = col_name.length();
		String vertical_col_name{ "" };
		for (auto i = 0; i < num_digits; ++i) {
			vertical_col_name << col_name[i];
			if (i + 1 < num_digits)
				vertical_col_name << "\n";
		}
		addColumn(vertical_col_name, col_id, 30);
	}
}

