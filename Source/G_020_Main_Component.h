#pragma once

#include <JuceHeader.h>

#include "D_000_Tree_MIDI_Message_Log.h"
#include "G_100_List_MIDI_Devices.h"
#include "G_105_MIDI_Device_List_Entry.h"
#include "G_400_Tabbed_Component_In_Out_Logs.h"

class Main_Component final :
    public Component,
    private MidiInputCallback,
    private AsyncUpdater
{
private: Label lbl_input_devices;
private: Label lbl_output_devices;
private: Label lbl_msg_slot_1;
private: Label lbl_msg_log;
private: ReferenceCountedArray<MIDI_Device_List_Entry> array_MIDI_inputs, array_MIDI_outputs;
private: std::unique_ptr<List_MIDI_Devices> input_selector, output_selector;
private: CriticalSection monitor_lock;
private: Array<MidiMessage> array_incoming_messages;
private: Tree_MIDI_Message_Log in_log;
private: Tree_MIDI_Message_Log out_log;
private: TextButton btn_edit_slot_1;
private: TextButton btn_transmit_slot_1;
private: Tabbed_Component_In_Out_Logs tabs_message_logs;
private: TooltipWindow tooltips;
private: StringArray stored_messages;

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
public: void paint(Graphics& /*g*/) override {}
public: void resized() override;
private: void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& msg) override;
private: void handleAsyncUpdate() override;
private: void sendToOutputs(const MidiMessage& msg);
private: void transmit_stored_message(const int msg_index);
public: bool keyPressed(const KeyPress& key) override;
public: ~Main_Component() override;

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Main_Component)
};
