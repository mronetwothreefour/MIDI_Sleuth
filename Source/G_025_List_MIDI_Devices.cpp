#include "G_025_List_MIDI_Devices.h"

#include "G_020_Component_MIDI_Handler.h"

List_MIDI_Devices::List_MIDI_Devices(const String& name, Component_MIDI_Handler* parent, bool is_input_list) :
    ListBox{ name },
    parent{ parent },
    is_input_list{ is_input_list }
{
    setModel(this);
    setColour(ListBox::backgroundColourId, COLOR::list_background);
    setOutlineThickness(1);
    setMultipleSelectionEnabled(true);
    setClickingTogglesRowSelection(true);
}

int List_MIDI_Devices::getNumRows() {
    return is_input_list ? parent->count_MIDI_inputs() : parent->count_MIDI_outputs();
}

void List_MIDI_Devices::paintListBoxItem(int row, Graphics& g, int w, int h, bool row_is_selected) {
    if (row_is_selected)
        g.fillAll(COLOR::highlight);
    g.setColour(COLOR::text);
    g.setFont(FONT::device_list);
    if (is_input_list) {
        if (row < parent->count_MIDI_inputs()) {
            auto& device_name = parent->get_device(row, true)->device_info.name;
            g.drawText(device_name, 5, 0, w, h, Justification::centredLeft, true);
        }
    }
    else {
        if (row < parent->count_MIDI_outputs()) {
            auto& device_name = parent->get_device(row, false)->device_info.name;
            g.drawText(device_name, 5, 0, w, h, Justification::centredLeft, true);
        }
    }
}

void List_MIDI_Devices::selectedRowsChanged(int /*last_row_selected*/) {
    auto selected_devices = getSelectedRows();
    if (selected_devices != last_selected_devices)
    {
        for (auto i = 0; i < last_selected_devices.size(); ++i) {
            if (!selected_devices.contains(last_selected_devices[i]))
                parent->close_device(is_input_list, last_selected_devices[i]);
        }
        for (auto i = 0; i < selected_devices.size(); ++i) {
            if (!last_selected_devices.contains(selected_devices[i]))
                parent->open_device(is_input_list, selected_devices[i]);
        }
        last_selected_devices = selected_devices;
    }
}

void List_MIDI_Devices::sync_selection_with_device_list(const ReferenceCountedArray<MIDI_Device_List_Entry>& device_list) {
    SparseSet<int> selected_rows;
    for (auto i = 0; i < device_list.size(); ++i)
        if (device_list[i]->in_device != nullptr || device_list[i]->out_device != nullptr)
            selected_rows.addRange(Range<int>(i, i + 1));

    last_selected_devices = selected_rows;
    updateContent();
    setSelectedRows(selected_rows, dontSendNotification);
}
