#include "D_005_Build_Message_Description.h"

const String Build_Message_Description::channel(const String& msg) {
	return String{ msg.substring(1, 2).getHexValue32() + 1 };
}

const String Build_Message_Description::key(const String& msg) {
	auto note_num = msg.substring(2, 4).getHexValue32();
	return MidiMessage::getMidiNoteName(note_num, true, true, 5);
}

const String Build_Message_Description::value(const String& msg, const int byte_num) {
	auto i = (byte_num - 1) * 2;
	return String{ msg.substring(i, i + 2).getHexValue32() };
}

const String Build_Message_Description::note_off(const String& msg) {
	return "Note Off | Ch. " + channel(msg) + " | Key: " + key(msg) + " | Velocity: " + value(msg, 3);
}

const String Build_Message_Description::note_on(const String& msg) {
	return "Note On | Ch. " + channel(msg) + " | Key: " + key(msg) + " | Velocity: " + value(msg, 3);
}

const String Build_Message_Description::key_aftertouch(const String& msg) {
	return "Key Aftertouch | Ch. " + channel(msg) + " | Key: " + key(msg) + " | Pressure: " + value(msg, 3);
}

const String Build_Message_Description::control_change(const String& msg) {
	return "Control Change | Ch. " + channel(msg) + " | Controller #" + value(msg, 2) + " | Value: " + value(msg, 3);
}

const String Build_Message_Description::program_change(const String& msg) {
	return "Program Change | Ch. " + channel(msg) + " | Program #" + value(msg, 2);
}

const String Build_Message_Description::channel_aftertouch(const String& msg) {
	return "Channel Aftertouch | Ch. " + channel(msg) + " | Pressure: " + value(msg, 2);
}

const String Build_Message_Description::pitch_bend(const String& msg) {
	auto msb = msg.substring(4, 6).getHexValue32();
	auto lsb = msg.substring(2, 4).getHexValue32();
	String amount{ msb * 128 + lsb };
	return "Pitch Bend: | Ch. " + channel(msg) + " | Amount: " + amount;
}
