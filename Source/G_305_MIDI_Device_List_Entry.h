#pragma once

#include <JuceHeader.h>

struct MIDI_Device_List_Entry final :
    ReferenceCountedObject
{
public: MidiDeviceInfo device_info;
public: std::unique_ptr<MidiInput> input_device;
public: std::unique_ptr<MidiOutput> output_device;

//==============================================================================
public: explicit MIDI_Device_List_Entry(MidiDeviceInfo device_info) :
            device_info(device_info)
        {}

using Ptr = ReferenceCountedObjectPtr<MIDI_Device_List_Entry>;

public: void stopAndReset() {
            if (input_device)
                input_device->stop();
            input_device.reset();
            output_device.reset();
        }

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MIDI_Device_List_Entry)
};
