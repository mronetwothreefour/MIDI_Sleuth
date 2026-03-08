#pragma once

#include <JuceHeader.h>

#include "D_100_Data_User.h"
#include "G_025_List_MIDI_Devices.h"
#include "G_027_MIDI_Device.h"

class Component_MIDI_Handler :
    public Component,
    private MidiInputCallback,
    private AsyncUpdater,
    public Data_User
{
private: ReferenceCountedArray<MIDI_Device_List_Entry> array_MIDI_inputs, array_MIDI_outputs;
private: std::unique_ptr<List_MIDI_Devices> in_selector, out_selector;
private: CriticalSection monitor_lock;
private: Array<MidiMessage> array_incoming_messages;

//==============================================================================
public: explicit Component_MIDI_Handler(Data_Hub* hub);

public: void paint(Graphics& g) override;
public: void resized() override;
public: void open_device(bool is_input, int index);
public: void close_device(bool is_input, int index);
public: int count_MIDI_inputs() const noexcept;
public: int count_MIDI_outputs() const noexcept;
private: bool device_list_has_changed(const Array<MidiDeviceInfo>& available_devices, bool is_input);
public: MIDI_Device_List_Entry::Ptr get_device(int index, bool is_input) const noexcept;
private: MIDI_Device_List_Entry::Ptr find_device(MidiDeviceInfo device, bool is_input) const;
private: void close_unplugged_devices(const Array<MidiDeviceInfo>& plugged_in_devices, bool is_input);
private: void update_device_list(bool is_input);
private: void update_device_lists();
private: void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& msg) override;
private: void handleAsyncUpdate() override;
private: void send_to_outputs(const MidiMessage& msg);
public: void transmit_stored_message(const int slot_index);
public: ~Component_MIDI_Handler();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Component_MIDI_Handler)
};