#include "G_MIDI_Device_Lbox.h"

#include "C_GUI_COLOR.h"
#include "C_GUI_FONT.h"

MIDI_Device_Lbox::MIDI_Device_Lbox(const String& name, bool for_inputs, MidiInputCallback* input_handler) :
    ListBox{ name },
    for_inputs{ for_inputs },
    for_outputs{ !for_inputs },
    input_handler{ input_handler }
{
    setModel(this);
    setOutlineThickness(0);
    setMultipleSelectionEnabled(true);
    setClickingTogglesRowSelection(true);
    setTooltip("Select a device to open it.");
    ump::Endpoints::getInstance()->addListener(*this);
    update_list();
}

int MIDI_Device_Lbox::getNumRows() {
    return list_devices.size();
}

void MIDI_Device_Lbox::paintListBoxItem(int row, Graphics& g, int w, int h, bool row_selected) {
    if (row_selected)
        g.fillAll(COLOR::hilite);
    g.setColour(COLOR::txt);
    g.setFont(FONT::lbox_item);
    if (row < getNumRows()) {
        auto& device_name = list_devices[row]->device_info.name;
        g.drawText(device_name, 5, 0, w, h, Justification::centredLeft, true);
    }
}

void MIDI_Device_Lbox::open_device(int index) {
    auto device = list_devices[index];
    if (for_inputs) {
        jassert(device->input.get() == nullptr);
        auto& device_id = device->device_info.identifier;
        device->input = MidiInput::openDevice(device_id, input_handler);
        if (device->input.get() == nullptr) {
            DBG("Open input device (index " << index << ") failed!");
            return;
        }
        device->input->start();
    }
    else {
        jassert(device->output.get() == nullptr);
        auto& device_id = device->device_info.identifier;
        device->output = MidiOutput::openDevice(device_id);
        if (device->output.get() == nullptr) {
            DBG("Open input device (index " << index << ") failed!");
            return;
        }
    }
}

void MIDI_Device_Lbox::close_device(int index) {
    list_devices[index]->stop_and_reset();
}

void MIDI_Device_Lbox::endpointsChanged() {
    Timer::callAfterDelay(100, [this] { update_list(); });
}

bool MIDI_Device_Lbox::list_needs_update(const Array<MidiDeviceInfo>& available_devices) {
    if (available_devices.size() != list_devices.size())
        return true;
    for (auto i = 0; i < available_devices.size(); ++i)
        if (available_devices[i] != list_devices[i]->device_info)
            return true;
    return false;
}

void MIDI_Device_Lbox::update_list() {
    auto available_devices = for_inputs ? MidiInput::getAvailableDevices() : MidiOutput::getAvailableDevices();
    if (list_needs_update(available_devices)) {
        close_open_devices(available_devices);
        ReferenceCountedArray<MIDI_Device> new_list;
        for (auto& available_device : available_devices) {
            auto device = find_device(available_device);
            if (!device)
                device = new MIDI_Device{ available_device };
            new_list.add(device);
        }
        list_devices = new_list;
        sync_selection_with_device_list();
    }
}

MIDI_Device::Ptr MIDI_Device_Lbox::find_device(MidiDeviceInfo device_info) const {
    for (auto& device : list_devices)
        if (device->device_info == device_info)
            return device;
    return nullptr;
}

void MIDI_Device_Lbox::selectedRowsChanged(int /*last_row_selected*/) {
    auto selection = getSelectedRows();
    if (selection != prev_selection) {
        for (auto i = 0; i < prev_selection.size(); ++i) {
            if (!selection.contains(prev_selection[i]))
                close_device(prev_selection[i]);
        }
        for (auto i = 0; i < selection.size(); ++i) {
            if (!prev_selection.contains(selection[i]))
                open_device(selection[i]);
        }
        prev_selection = selection;
    }
}

void MIDI_Device_Lbox::sync_selection_with_device_list() {
    SparseSet<int> selection;
    for (auto i = 0; i < list_devices.size(); ++i)
        if (list_devices[i]->input != nullptr || list_devices[i]->output != nullptr)
            selection.addRange(Range<int>(i, i + 1));
    prev_selection = selection;
    updateContent();
    setSelectedRows(selection, dontSendNotification);
}

void MIDI_Device_Lbox::close_open_devices(const Array<MidiDeviceInfo>& open_devices) {
    for (auto i = list_devices.size(); --i >= 0;) {
        auto& device = *list_devices[i];
        if (!open_devices.contains(device.device_info)) {
            if (for_inputs ? device.input.get() != nullptr : device.output.get() != nullptr)
                close_device(i);
            list_devices.remove(i);
        }
    }
}

void MIDI_Device_Lbox::stop_and_reset_all_devices() {
    deselectAllRows();
    for (auto i = 0; i < list_devices.size(); ++i)
        list_devices[i]->stop_and_reset();
    if (for_inputs)
        sync_selection_with_device_list();
}

void MIDI_Device_Lbox::pass_msg_to_open_outputs(const MidiMessage& msg) {
    if (for_outputs) {
        for (auto device : list_devices)
            if (device->output != nullptr)
                device->output->sendMessageNow(msg);
    }
}

MIDI_Device_Lbox::~MIDI_Device_Lbox() {
    ump::Endpoints::getInstance()->removeListener(*this);
    list_devices.clear();
}

