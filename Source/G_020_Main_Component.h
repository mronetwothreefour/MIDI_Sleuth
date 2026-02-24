#pragma once

#include <JuceHeader.h>

#include "G_300_List_MIDI_Devices.h"
#include "G_305_MIDI_Device_List_Entry.h"

class Main_Component final :
    public Component,
    private MidiKeyboardState::Listener,
    private MidiInputCallback,
    private AsyncUpdater
{
private: Label lbl_input_devices{ "Midi Input Label",  "MIDI Input:" };
private: Label lbl_output_devices{ "Midi Output Label", "MIDI Output:" };
private: Label lbl_received{ "Received Midi Label", "Received MIDI messages:" };
private: Label lbl_keyboard{ "Keyboard Label", "Play the keyboard to send MIDI messages..." };
private: MidiKeyboardState keyboard_state;
private: MidiKeyboardComponent keyboard;
private: TextEditor editor_MIDI_monitor{ "MIDI Monitor" };
private: ReferenceCountedArray<MIDI_Device_List_Entry> array_MIDI_inputs, array_MIDI_outputs;
private: std::unique_ptr<List_MIDI_Devices> input_selector, output_selector;
private: CriticalSection monitor_lock;
private: Array<MidiMessage> array_incoming_messages;

//==============================================================================
public: Main_Component();

public: void open_device(bool is_input, int index);
public: void closeDevice(bool is_input, int index);
public: int count_MIDI_inputs() const noexcept;
public: int count_MIDI_outputs() const noexcept;
private: bool device_list_has_changed(const Array<MidiDeviceInfo>& available_devices, bool is_input);
public: MIDI_Device_List_Entry::Ptr get_device(int index, bool is_input) const noexcept;
private: MIDI_Device_List_Entry::Ptr find_device(MidiDeviceInfo device, bool is_input) const;
private: void close_unplugged_devices(const Array<MidiDeviceInfo>& plugged_in_devices, bool isInputDevice);
private: void update_device_list(bool is_input);
private: void update_device_lists();
private: void add_label_and_set_style(Label& label);
public: void paint(Graphics&) override {}
public: void resized() override;
public: void handleNoteOn(MidiKeyboardState* /*state*/, int channel, int note_num, float velocity) override;
public: void handleNoteOff(MidiKeyboardState*, int channel, int note_num, float velocity) override;
private: void handleIncomingMidiMessage(MidiInput* /*source*/, const MidiMessage& msg) override;
private: void handleAsyncUpdate() override;
private: void sendToOutputs(const MidiMessage& msg);
public: ~Main_Component() override;

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Main_Component)
};
