#include "G_Table_Header.h"

Table_Header::Table_Header(const Table_Type table_type) :
	table_type{ table_type },
	num_non_byte_cols{ table_type < comparison ? 4 : 1 }
{
	if (table_type < msg_slot_1) {
		addColumn("#", 1, 30);
		if (table_type < comparison) {
			addColumn("Timestamp", 2, 75);
			addColumn("Description", 3, 300);
			addColumn("Length", 4, 55);
		}
	}
	else {
		setComponentID("Message Slot");
		addColumn("Description", 1, 300);
	}
}

const int Table_Header::byte_col_count() {
	auto num_cols = getNumColumns(true);
	return  num_cols - num_non_byte_cols;
}

void Table_Header::add_byte_col(int byte_index) {
	auto col_id = byte_index + 1 + num_non_byte_cols;
	if (col_id > getNumColumns(true)) {
		String col_name{ byte_index };
		auto num_digits = col_name.length();
		String vertical_col_name{ "" };
		for (auto i = 0; i < num_digits; ++i) {
			vertical_col_name << col_name[i];
			if (i + 1 < num_digits)
				vertical_col_name << "\n";
		}
		addColumn(vertical_col_name, col_id, 30, 30, 30, ColumnPropertyFlags::visible);
	}
}

void Table_Header::columnClicked(int col_id, const ModifierKeys& /*mods*/) {
	setSortColumnId(col_id, true);
}
