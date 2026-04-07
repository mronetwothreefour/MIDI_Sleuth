#pragma once

#include <JuceHeader.h>

struct Build_Description
{
public: static const String from_hex_string(const String& hex_string);

private: static const String channel(const String& hex_string);
private: static const String note_name(const String& hex_string);
private: static const String value(const String& hex_string, const int byte_index);

private: static const String note_off(const String& hex_string);
private: static const String note_on(const String& hex_string);
private: static const String key_press(const String& hex_string);
private: static const String ctrl_change(const String& hex_string);
private: static const String pgm_change(const String& hex_string);
private: static const String chan_press(const String& hex_string);
private: static const String pitch_bend(const String& hex_string);
};
