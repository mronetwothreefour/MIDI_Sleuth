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

void Tree_MIDI_Message_Log::log_message(const MidiMessage& msg) {
	ValueTree row{ "ROW" };
	row.setProperty("Timestamp", msg.getTimeStamp(), nullptr);
	row.setProperty("Description", msg.getDescription(), nullptr);
	DBG(row.getProperty("Timestamp").toString() + " " + row.getProperty("Description").toString());
	body().addChild(row, -1, nullptr);
	DBG("Number of entries: " + String{ body().getNumChildren() });
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
