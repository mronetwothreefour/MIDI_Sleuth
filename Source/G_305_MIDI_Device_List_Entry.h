#pragma once

#include <JuceHeader.h>

struct MIDI_Device_List_Entry final :
    ReferenceCountedObject
{
public: MidiDeviceInfo device_info;
public: std::unique_ptr<MidiInput> in_device;
public: std::unique_ptr<MidiOutput> out_device;

//==============================================================================
public: explicit MIDI_Device_List_Entry(MidiDeviceInfo device_info) :
            device_info{ device_info }
        {}

using Ptr = ReferenceCountedObjectPtr<MIDI_Device_List_Entry>;

public: void stop_and_reset() {
            if (in_device != nullptr)
                in_device->stop();

            in_device.reset();
            out_device.reset();
        }
};
