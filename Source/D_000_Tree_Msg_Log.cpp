#include "D_000_Tree_Msg_Log.h"

Tree_Msg_Log::Tree_Msg_Log() :
	tree{ new ValueTree{ "MIDI Message Log" } }
{}

const int Tree_Msg_Log::number_of_rows() {
	return tree->getNumChildren();
}

const int Tree_Msg_Log::first_byte_col_id() {
	return 4;
}

void Tree_Msg_Log::add_msg(const MidiMessage& msg, String description) {
	ValueTree entry{ "Entry" };
	entry.setProperty("Timestamp", msg.getTimeStamp(), nullptr);
	auto bytes = Convert::MIDI_message_to_hex_string(msg);
	if (description.isEmpty())
		description = Build_Description::from_hex_string(bytes);
	entry.setProperty("Description", description, nullptr);
	entry.setProperty("Bytes", bytes, nullptr);
	tree->addChild(entry, -1, nullptr);
}

const int Tree_Msg_Log::msg_timestamp(const int msg_index) {
	auto msg = tree->getChild(msg_index);
	double timestamp{ msg.getProperty("Timestamp") };
	return roundToInt(timestamp * 1000.0);
}

const int Tree_Msg_Log::msg_length(const int msg_index) {
	return msg_bytes(msg_index).length() / 2;
}

const String Tree_Msg_Log::msg_description(const int msg_index) {
	auto msg = tree->getChild(msg_index);
	return msg.getProperty("Description").toString();
}

const String Tree_Msg_Log::msg_bytes(const int msg_index) {
	auto msg = tree->getChild(msg_index);
	return msg.getProperty("Bytes").toString();
}

void Tree_Msg_Log::clear_log() {
	tree->removeAllChildren(nullptr);
}

void Tree_Msg_Log::add_listener(ValueTree::Listener* listener) {
	if (listener)
		tree->addListener(listener);
}

void Tree_Msg_Log::remove_listener(ValueTree::Listener* listener) {
	tree->removeListener(listener);
}

Tree_Msg_Log::~Tree_Msg_Log() {
	tree = nullptr;
}
