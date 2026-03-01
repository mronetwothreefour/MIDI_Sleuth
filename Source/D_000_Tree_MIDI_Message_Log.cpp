#include "D_000_Tree_MIDI_Message_Log.h"

Tree_MIDI_Message_Log::Tree_MIDI_Message_Log() :
	tree{ new ValueTree{ "MIDI Message Log" } }
{}

const int Tree_MIDI_Message_Log::number_of_rows() {
	return tree->getNumChildren();
}

void Tree_MIDI_Message_Log::log_message(const MidiMessage& msg) {
	ValueTree entry{ "Entry" };
	entry.setProperty("Timestamp", msg.getTimeStamp(), nullptr);
	entry.setProperty("Bytes", String::toHexString(msg.getRawData(), msg.getRawDataSize(), 0), nullptr);
	tree->addChild(entry, -1, nullptr);
}

const int Tree_MIDI_Message_Log::entry_timestamp(const int entry_index) {
	auto entry = tree->getChild(entry_index);
	double timestamp{ entry.getProperty("Timestamp") };
	return roundToInt(timestamp * 1000.0);
}

const String Tree_MIDI_Message_Log::entry_bytes(const int entry_index) {
	auto entry = tree->getChild(entry_index);
	return entry.getProperty("Bytes").toString();
}

const int Tree_MIDI_Message_Log::entry_length(const int entry_index) {
	return entry_bytes(entry_index).length() / 2;
}

const String Tree_MIDI_Message_Log::entry_description(const int entry_index) {
	auto length = entry_length(entry_index);
	auto msg = entry_bytes(entry_index);
	String description{ "Invalid Message" };

	if (length == 3) {
		if (msg.startsWith("8") || msg.startsWith("9") || msg.startsWith("A")) {
			description = msg.startsWith("A") ? "Aftertouch" : "Note";
			description += msg.startsWith("8") ? " Off" : msg.startsWith("9") ? " On" : "";
			description += " | Ch. ";
			description << msg.substring(1, 2).getIntValue() + 1;
			description += " | Key ";
			auto key_num = msg.substring(2, 4).getHexValue32();
			description << key_num;
			description += " (";
			description += MidiMessage::getMidiNoteName(key_num, true, true, 5);
			description += ")";
			if (msg.startsWith("9") || msg.startsWith("A")) {
				description += " | Velocity ";
				description << msg.substring(4, 6).getHexValue32();
			}
		}
	}

	if (msg.startsWith("F0") && msg.endsWith("F7"))
		description = "System Exclusive";

	return description;
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
