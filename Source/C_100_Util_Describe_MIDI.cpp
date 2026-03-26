#include "C_100_Util_Describe_MIDI.h"

const String Describe_MIDI::channel(const String& msg) {
	return String{ msg.substring(1, 2).getHexValue32() + 1 };
}

const String Describe_MIDI::note_name(const String& msg) {
	auto note_num = msg.substring(2, 4).getHexValue32();
	return MidiMessage::getMidiNoteName(note_num, true, true, 3);
}

const String Describe_MIDI::value(const String& msg, const int byte_index) {
	return String{ msg.substring(byte_index, byte_index + 2).getHexValue32() };
}

const String Describe_MIDI::note_off(const String& msg) {
	return "Note Off | Ch. " + channel(msg) + " | Key: " + note_name(msg) + " | Velocity: " + value(msg, 2);
}

const String Describe_MIDI::note_on(const String& msg) {
	return "Note On | Ch. " + channel(msg) + " | Key: " + note_name(msg) + " | Velocity: " + value(msg, 2);
}

const String Describe_MIDI::key_press(const String& msg) {
	return "Key Aftertouch | Ch. " + channel(msg) + " | Key: " + note_name(msg) + " | Pressure: " + value(msg, 2);
}

const String Describe_MIDI::ctrl_change(const String& msg) {
	return "Control Change | Ch. " + channel(msg) + " | Controller #" + value(msg, 1) + " | Value: " + value(msg, 2);
}

const String Describe_MIDI::pgm_change(const String& msg) {
	return "Program Change | Ch. " + channel(msg) + " | Program #" + value(msg, 1);
}

const String Describe_MIDI::chan_press(const String& msg) {
	return "Channel Aftertouch | Ch. " + channel(msg) + " | Pressure: " + value(msg, 1);
}

const String Describe_MIDI::pitch_bend(const String& msg) {
	auto msb = msg.substring(4, 6).getHexValue32();
	auto lsb = msg.substring(2, 4).getHexValue32();
	String amount{ msb * 128 + lsb };
	return "Pitch Bend: | Ch. " + channel(msg) + " | Amount: " + amount;
}
