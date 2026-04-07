#pragma once

#include <JuceHeader.h>

#include "G_MIDI_Device.h"

using Device_List = ReferenceCountedArray<MIDI_Device>;

class MIDI_Handler;

class MIDI_Device_Lbox final :
    private ListBoxModel,
    public ListBox,
    private ump::EndpointsListener
{
private: MidiInputCallback* input_handler;
private: Device_List list_devices;
private: bool for_inputs;
private: bool for_outputs;
private: SparseSet<int> prev_selection;

//==============================================================================
public: MIDI_Device_Lbox(const String& name, bool for_inputs = false, MidiInputCallback* input_handler = nullptr);

public: int getNumRows() override;
private: void paintListBoxItem(int row, Graphics& g, int w, int h, bool row_selected) override;
private: void open_device(int index);
private: void close_device(int index);
private: void endpointsChanged() override;
private: bool list_needs_update(const Array<MidiDeviceInfo>& available_devices);
private: void update_list();
private: MIDI_Device::Ptr find_device(MidiDeviceInfo device_info) const;
private: void selectedRowsChanged(int last_row_selected) override;
private: void sync_selection_with_device_list();
private: void close_open_devices(const Array<MidiDeviceInfo>& open_devices);
public: void stop_and_reset_all_devices();
public: void pass_msg_to_open_outputs(const MidiMessage& msg);
public: ~MIDI_Device_Lbox();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MIDI_Device_Lbox)
};
