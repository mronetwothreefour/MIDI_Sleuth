#pragma once

#include <JuceHeader.h>


struct Util_MIDI
{
public: static MidiMessage convert_hex_string_to_MIDI_message(const String& hex_string);
};