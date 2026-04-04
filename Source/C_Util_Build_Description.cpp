#include "C_Util_Build_Description.h"

const String Build_Description::from_hex_string(const String& hex_string) {
	String description{ "Invalid MIDI Message" };
	auto length = hex_string.length() / 2;

	if (length == 2) {
		if (hex_string.startsWith("c"))
			return Build_Description::pgm_change(hex_string);
		if (hex_string.startsWith("d"))
			return Build_Description::chan_press(hex_string);
	}

	if (length == 3) {
		if (hex_string.startsWith("8"))
			return Build_Description::note_off(hex_string);
		if (hex_string.startsWith("9"))
			return Build_Description::note_on(hex_string);
		if (hex_string.startsWith("a"))
			return Build_Description::key_press(hex_string);
		if (hex_string.startsWith("b"))
			return Build_Description::ctrl_change(hex_string);
		if (hex_string.startsWith("e"))
			return Build_Description::pitch_bend(hex_string);
	}

	if (hex_string.startsWith("f0") && hex_string.endsWith("f7"))
		return "System Exclusive";

	return description;
}

const String Build_Description::channel(const String& hex_string) {
	return String{ hex_string.substring(1, 2).getHexValue32() + 1 };
}

const String Build_Description::note_name(const String& hex_string) {
	auto note_num = hex_string.substring(2, 4).getHexValue32();
	return MidiMessage::getMidiNoteName(note_num, true, true, 3);
}

const String Build_Description::value(const String& hex_string, const int byte_index) {
	auto i = byte_index * 2;
	return String{ hex_string.substring(i, i + 2).getHexValue32() };
}

const String Build_Description::note_off(const String& hex_string) {
	return "Note Off | Ch. " + channel(hex_string) + " | Key: " + note_name(hex_string) + " | Velocity: " + value(hex_string, 2);
}

const String Build_Description::note_on(const String& hex_string) {
	return "Note On | Ch. " + channel(hex_string) + " | Key: " + note_name(hex_string) + " | Velocity: " + value(hex_string, 2);
}

const String Build_Description::key_press(const String& hex_string) {
	return "Key Aftertouch | Ch. " + channel(hex_string) + " | Key: " + note_name(hex_string) + " | Pressure: " + value(hex_string, 2);
}

const String Build_Description::ctrl_change(const String& hex_string) {
	return "Control Change | Ch. " + channel(hex_string) + " | Controller #" + value(hex_string, 1) + " | Value: " + value(hex_string, 2);
}

const String Build_Description::pgm_change(const String& hex_string) {
	return "Program Change | Ch. " + channel(hex_string) + " | Program #" + value(hex_string, 1);
}

const String Build_Description::chan_press(const String& hex_string) {
	return "Channel Aftertouch | Ch. " + channel(hex_string) + " | Pressure: " + value(hex_string, 1);
}

const String Build_Description::pitch_bend(const String& hex_string) {
	auto msb = hex_string.substring(4, 6).getHexValue32();
	auto lsb = hex_string.substring(2, 4).getHexValue32();
	String amount{ msb * 128 + lsb };
	return "Pitch Bend: | Ch. " + channel(hex_string) + " | Amount: " + amount;
}
