#pragma once

#include <JuceHeader.h>

struct Dele_Device final :
    ReferenceCountedObject
{
public: MidiDeviceInfo device_info;
public: std::unique_ptr<MidiInput> in_device;
public: std::unique_ptr<MidiOutput> out_device;

//==============================================================================
public: explicit Dele_Device(MidiDeviceInfo device_info) :
    device_info{ device_info }
{}

using Ptr = ReferenceCountedObjectPtr<Dele_Device>;

public: void stop_and_reset() {
    if (in_device != nullptr)
        in_device->stop();
    in_device.reset();
    out_device.reset();
}

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Dele_Device)
};
