#include "D_000_Tree_MIDI_Message_Log.h"

Tree_MIDI_Message_Log::Tree_MIDI_Message_Log() :
	tree{ new ValueTree{ "MIDI Message Log" } }
{
	ValueTree table_header{ "HEADER" };

	ValueTree col_1{ "COLUMN" };
	col_1.setProperty("COLUMN_NUM", 1, nullptr);
	col_1.setProperty("NAME", "Timestamp", nullptr);
	col_1.setProperty("WIDTH", 50, nullptr);
	table_header.addChild(col_1, 1, nullptr);

	ValueTree col_2{ "COLUMN" };
	col_2.setProperty("COLUMN_NUM", 2, nullptr);
	col_2.setProperty("NAME", "Description", nullptr);
	col_2.setProperty("WIDTH", 100, nullptr);
	table_header.addChild(col_2, 2, nullptr);

	ValueTree col_3{ "COLUMN" };
	col_3.setProperty("COLUMN_NUM", 3, nullptr);
	col_3.setProperty("NAME", "Length", nullptr);
	col_3.setProperty("WIDTH", 50, nullptr);
	table_header.addChild(col_3, 3, nullptr);

	tree->addChild(table_header, 1, nullptr);

	ValueTree table_body{ "BODY" };

	tree->addChild(table_body, 2, nullptr);
}

ValueTree Tree_MIDI_Message_Log::header() {
	return tree->getChildWithName("HEADER");
}

ValueTree Tree_MIDI_Message_Log::body() {
	return tree->getChildWithName("BODY");
}

ValueTree Tree_MIDI_Message_Log::row(int index) {
	return body().getChild(index);
}

void Tree_MIDI_Message_Log::add_data_byte_column() {
	auto column_num = header().getNumChildren() + 1;
	auto byte_num = column_num - 4;
	ValueTree new_col{ "COLUMN" };
	new_col.setProperty("COLUMN_NUM", column_num, nullptr);
	new_col.setProperty("NAME", String{ byte_num }, nullptr);
	new_col.setProperty("WIDTH", 15, nullptr);
	header().addChild(new_col, column_num, nullptr);
}

const int Tree_MIDI_Message_Log::log_message(const MidiMessage& msg) {
	ValueTree row{ "ROW" };

	ValueTree cell_1{ "Timestamp" };
	cell_1.setProperty("Value", msg.getTimeStamp(), nullptr);
	row.addChild(cell_1, 1, nullptr);

	ValueTree cell_2{ "Description" };
	cell_2.setProperty("Value", msg.getDescription(), nullptr);
	row.addChild(cell_2, 2, nullptr);

	ValueTree cell_3{ "Length" };
	cell_3.setProperty("Value", msg.getRawDataSize(), nullptr);
	row.addChild(cell_3, 3, nullptr);

	body().addChild(row, -1, nullptr);
	return body().getNumChildren() - 1;
}

const String Tree_MIDI_Message_Log::cell_value(const int row_index, const String& col_name) {
	auto row = body().getChild(row_index);
	auto cell = row.getChildWithName(col_name);
	return cell.getProperty("Value").toString();
}

void Tree_MIDI_Message_Log::add_listener(ValueTree::Listener* listener) {
	if (listener)
		tree->addListener(listener);
}

void Tree_MIDI_Message_Log::remove_listener(ValueTree::Listener* listener) {
	tree->removeListener(listener);
}

Tree_MIDI_Message_Log::~Tree_MIDI_Message_Log() {
	tree = nullptr;
}
