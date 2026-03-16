#include "D_010_Util_MIDI.h"

MidiMessage Util_MIDI::convert_hex_string_to_MIDI_message(const String& hex_string) {
    MidiMessage msg{};
    if (hex_string.isNotEmpty()) {
        std::vector<uint8> msg_data;
        for (auto i = 0; i < hex_string.length(); i += 2) {
            auto byte_string{ hex_string.substring(i, i + 2) };
            msg_data.push_back((uint8)byte_string.getHexValue32());
        }
        auto msg_size = msg_data.size();
        auto timestamp = Time::getMillisecondCounterHiRes() * 0.001;
        if (msg_size == 2)
            msg = MidiMessage{ msg_data[0], msg_data[1], timestamp };
        if (msg_size == 3)
            msg = MidiMessage{ msg_data[0], msg_data[1], msg_data[2], timestamp };
        if (msg_size > 3)
            msg = MidiMessage{ &msg_data, (int)msg_data.size(), timestamp };
    }
    return msg;
}
