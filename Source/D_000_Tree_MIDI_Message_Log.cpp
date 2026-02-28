#include "D_000_Tree_MIDI_Message_Log.h"

Tree_MIDI_Message_Log::Tree_MIDI_Message_Log() :
	tree{ new ValueTree{ "MIDI Message Log" } }
{}

const int Tree_MIDI_Message_Log::number_of_rows() {
	return tree->getNumChildren();
}

const int Tree_MIDI_Message_Log::log_message(const MidiMessage& msg) {
	ValueTree row{ "ROW" };

	ValueTree cell_1{ "#" };
	cell_1.setProperty("Value", tree->getNumChildren() + 1, nullptr);
	row.addChild(cell_1, -1, nullptr);

	ValueTree cell_2{ "Timestamp" };
	cell_2.setProperty("Value", roundToInt(msg.getTimeStamp() * 1000.0), nullptr);
	row.addChild(cell_2, -1, nullptr);

	ValueTree cell_3{ "Description" };
	cell_3.setProperty("Value", msg.getDescription(), nullptr);
	row.addChild(cell_3, -1, nullptr);

	ValueTree cell_4{ "Length" };
	cell_4.setProperty("Value", msg.getRawDataSize(), nullptr);
	row.addChild(cell_4, -1, nullptr);

	ValueTree cell_5{ "Bytes" };
	cell_5.setProperty("Value", String::toHexString(msg.getRawData(), msg.getRawDataSize(), 0), nullptr);
	row.addChild(cell_5, -1, nullptr);

	tree->addChild(row, -1, nullptr);
	return tree->getNumChildren() - 1;
}

const String Tree_MIDI_Message_Log::cell_value(const int row_index, const String& col_name) {
	auto row = tree->getChild(row_index);
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
