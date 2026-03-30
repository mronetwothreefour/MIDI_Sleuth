#pragma once

#include <JuceHeader.h>

struct MIDI_Device final :
    ReferenceCountedObject
{
public: MidiDeviceInfo device_info;
public: std::unique_ptr<MidiInput> input;
public: std::unique_ptr<MidiOutput> output;

//==============================================================================
public: explicit MIDI_Device(MidiDeviceInfo device_info) :
    device_info{ device_info }
{}

using Ptr = ReferenceCountedObjectPtr<MIDI_Device>;

public: void stop_and_reset() {
    if (input != nullptr)
        input->stop();
    input.reset();
    output.reset();
}

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MIDI_Device)
};
