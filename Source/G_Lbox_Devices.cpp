#include "G_Lbox_Devices.h"

#include "G_Comp_Devices.h"

Lbox_Devices::Lbox_Devices(const String& name, Comp_Devices* comp_devices, bool showing_inputs) :
    ListBox{ name },
    comp_devices{ comp_devices },
    showing_inputs{ showing_inputs }
{
    setModel(this);
    setOutlineThickness(1);
    setMultipleSelectionEnabled(true);
    setClickingTogglesRowSelection(true);
    setTooltip("Select a device to open it.");
}

int Lbox_Devices::getNumRows() {
    return showing_inputs ? comp_devices->count_inputs() : comp_devices->count_outputs();
}

void Lbox_Devices::paintListBoxItem(int row, Graphics& g, int w, int h, bool row_selected) {
    if (row_selected)
        g.fillAll(COLOR::hilite);
    g.setColour(COLOR::txt);
    g.setFont(FONT::dele_device);
    if (row < getNumRows()) {
        if (showing_inputs) {
            auto& device_name = comp_devices->get_device(row, true)->device_info.name;
            g.drawText(device_name, 5, 0, w, h, Justification::centredLeft, true);
        }
        else {
            auto& device_name = comp_devices->get_device(row, false)->device_info.name;
            g.drawText(device_name, 5, 0, w, h, Justification::centredLeft, true);
        }
    }
}

void Lbox_Devices::selectedRowsChanged(int /*last_row_selected*/) {
    auto selection = getSelectedRows();
    if (selection != prev_selection) {
        for (auto i = 0; i < prev_selection.size(); ++i) {
            if (!selection.contains(prev_selection[i]))
                comp_devices->close_device(showing_inputs, prev_selection[i]);
        }
        for (auto i = 0; i < selection.size(); ++i) {
            if (!prev_selection.contains(selection[i]))
                comp_devices->open_device(showing_inputs, selection[i]);
        }
        prev_selection = selection;
    }
}

void Lbox_Devices::sync_selection_with_device_list(const Device_Array& device_list) {
    SparseSet<int> selection;
    for (auto i = 0; i < device_list.size(); ++i)
        if (device_list[i]->in_device != nullptr || device_list[i]->out_device != nullptr)
            selection.addRange(Range<int>(i, i + 1));

    prev_selection = selection;
    updateContent();
    setSelectedRows(selection, dontSendNotification);
}

void Lbox_Devices::stop_and_reset_all_devices(const Device_Array& device_list) {
    deselectAllRows();
    for (auto i = 0; i < device_list.size(); ++i)
        device_list[i]->stop_and_reset();
}

