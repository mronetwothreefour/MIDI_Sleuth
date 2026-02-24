#pragma once

#include <JuceHeader.h>

#include "G_305_MIDI_Device_List_Entry.h"

class Main_Component;

struct List_MIDI_Devices final :
    private ListBoxModel,
    public ListBox
{
private: Main_Component& parent;
private: bool is_input_list;
private: SparseSet<int> last_selected_devices;

//==============================================================================
public: List_MIDI_Devices(const String& name, Main_Component& parent, bool is_input_list);

public: int getNumRows() override;
private: void paintListBoxItem(int row, Graphics& g, int w, int h, bool row_is_selected) override;
private: void selectedRowsChanged(int /*last_row_selected*/) override;
public: void sync_selection_with_device_list(const ReferenceCountedArray<MIDI_Device_List_Entry>& device_list);
};
