#pragma once

#include <JuceHeader.h>

struct Describe_MIDI
{
private: static const String channel(const String& msg);
private: static const String note_name(const String& msg);
private: static const String value(const String& msg, const int byte_index);

public: static const String note_off(const String& msg);
public: static const String note_on(const String& msg);
public: static const String key_press(const String& msg);
public: static const String ctrl_change(const String& msg);
public: static const String pgm_change(const String& msg);
public: static const String chan_press(const String& msg);
public: static const String pitch_bend(const String& msg);
};
