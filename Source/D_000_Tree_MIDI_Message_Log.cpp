#include "D_000_Tree_MIDI_Message_Log.h"

#include "D_005_Build_Message_Description.h"

Tree_MIDI_Message_Log::Tree_MIDI_Message_Log() :
	tree{ new ValueTree{ "MIDI Message Log" } }
{}

const int Tree_MIDI_Message_Log::number_of_rows() {
	return tree->getNumChildren();
}

const int Tree_MIDI_Message_Log::log_message(const MidiMessage& msg) {
	ValueTree entry{ "Entry" };
	entry.setProperty("Timestamp", msg.getTimeStamp(), nullptr);
	entry.setProperty("Bytes", String::toHexString(msg.getRawData(), msg.getRawDataSize(), 0), nullptr);
	tree->addChild(entry, -1, nullptr);
	return number_of_rows() - 1;
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

	if (length == 2) {
		if (msg.startsWith("c"))
			return Build_Message_Description::program_change(msg);
		if (msg.startsWith("d"))
			return Build_Message_Description::channel_aftertouch(msg);
	}

	if (length == 3) {
		if (msg.startsWith("8"))
			return Build_Message_Description::note_off(msg);
		if (msg.startsWith("9"))
			return Build_Message_Description::note_on(msg);
		if (msg.startsWith("a"))
			return Build_Message_Description::key_aftertouch(msg);
		if (msg.startsWith("b"))
			return Build_Message_Description::control_change(msg);
		if (msg.startsWith("e"))
			return Build_Message_Description::pitch_bend(msg);
	}

	if (msg.startsWith("F0") && msg.endsWith("F7"))
		return "System Exclusive";

	return "Invalid Message";
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
