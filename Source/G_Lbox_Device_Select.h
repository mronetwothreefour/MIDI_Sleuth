#pragma once

#include <JuceHeader.h>

#include "G_Dele_Device.h"

using Device_Array = ReferenceCountedArray<Dele_Device>;

class Comp_Msg_Handler;

class Lbox_Device_Select final :
    private ListBoxModel,
    public ListBox
{
private: Comp_Msg_Handler* comp_devices;
private: bool showing_inputs;
private: SparseSet<int> prev_selection;

//==============================================================================
public: Lbox_Device_Select(const String& name, Comp_Msg_Handler* comp_devices, bool showing_inputs);

public: int getNumRows() override;
private: void paintListBoxItem(int row, Graphics& g, int w, int h, bool row_selected) override;
private: void selectedRowsChanged(int last_row_selected) override;
public: void sync_selection_with_device_list(const Device_Array& device_list);
public: void stop_and_reset_all_devices(const Device_Array& device_list);

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Lbox_Device_Select)
};
