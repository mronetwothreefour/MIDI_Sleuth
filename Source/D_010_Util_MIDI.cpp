#include "D_010_Util_MIDI.h"

MidiMessage Util_MIDI::convert_hex_string_to_MIDI_message(const String& hex_string) {
    MidiMessage msg{};
    if (hex_string.isNotEmpty()) {
        std::vector<uint8> msg_data;
        for (auto i = 0; i < hex_string.length(); i += 2) {
            auto byte_string{ hex_string.substring(i, i + 2) };
            msg_data.push_back((uint8)byte_string.getHexValue32());
        }
        auto timestamp = Time::getMillisecondCounterHiRes() * 0.001;
        msg = MidiMessage{ &msg_data[0], (int)msg_data.size(), timestamp};
    }
    return msg;
}
