#include "G_Comp_Devices.h"

using namespace XYWH;

Comp_Devices::Comp_Devices(Data_Hub* hub) :
    Data_User{ hub },
    lbox_inputs{ new Lbox_Devices{ "Midi Input Selector", this, true } },
    lbox_outputs{ new Lbox_Devices{ "Midi Output Selector", this, false } }
{
    addAndMakeVisible(lbox_inputs.get());
    addAndMakeVisible(lbox_outputs.get());
    update_lists();
    ump::Endpoints::getInstance()->addListener(*this);
}

void Comp_Devices::paint(Graphics& g) {
    g.setFont(FONT::title_device);
    g.setColour(COLOR::txt);
    auto w = lbox_inputs->getWidth();
    Rectangle<int> lbl_input_area{ 0, 0, w, lbl_lbox_devices_h };
    g.drawText("MIDI Input Devices", lbl_input_area, Justification::centredTop);
    Rectangle<int> lbl_output_area{ w + win_main_comp_inset, 0, w, lbl_lbox_devices_h };
    g.drawText("MIDI Output Devices", lbl_output_area, Justification::centredTop);
}

void Comp_Devices::resized() {
    auto y = lbl_lbox_devices_h;
    auto w = lbox_devices_min_w;
    if (getWidth() > w + win_main_comp_inset)
        w = (getWidth() / 2) - (win_main_comp_inset / 2);
    auto h = lbox_devices_h;
    lbox_inputs->setBounds(0, y, w, h);
    lbox_outputs->setBounds(w + win_main_comp_inset, y, w, h);
}

void Comp_Devices::open_device(bool input, int index) {
    if (input) {
        auto device = list_inputs[index];
        jassert(device->in_device.get() == nullptr);
        auto& device_id = device->device_info.identifier;
        device->in_device = MidiInput::openDevice(device_id, this);
        if (device->in_device.get() == nullptr) {
            DBG("Main_Component::openDevice: open input device for index = " << index << " failed!");
            return;
        }
        device->in_device->start();
    }
    else {
        auto device = list_outputs[index];
        jassert(device->out_device.get() == nullptr);
        auto& device_id = device->device_info.identifier;
        device->out_device = MidiOutput::openDevice(device_id);
        if (device->out_device.get() == nullptr) {
            DBG("Main_Component::openDevice: open output device for index = " << index << " failed!");
            return;
        }
    }
}

void Comp_Devices::close_device(bool input, int index) {
    auto& list = input ? list_inputs : list_outputs;
    list[index]->stop_and_reset();
}

int Comp_Devices::count_inputs() const noexcept {
    return list_inputs.size();
}

int Comp_Devices::count_outputs() const noexcept {
    return list_outputs.size();
}

bool Comp_Devices::device_list_changed(const Array<MidiDeviceInfo>& connected_devices, bool inputs) {
    auto& list = inputs ? list_inputs : list_outputs;
    if (connected_devices.size() != list.size())
        return true;
    for (auto i = 0; i < connected_devices.size(); ++i)
        if (connected_devices[i] != list[i]->device_info)
            return true;
    return false;
}

void Comp_Devices::endpointsChanged() {
    update_lists();
}

Dele_Device::Ptr Comp_Devices::get_device(int index, bool input) const noexcept {
    return input ? list_inputs[index] : list_outputs[index];
}

Dele_Device::Ptr Comp_Devices::find_device(MidiDeviceInfo device_info, bool input) const {
    const auto& list = input ? list_inputs : list_outputs;
    for (auto& device : list)
        if (device->device_info == device_info)
            return device;
    return nullptr;
}

void Comp_Devices::close_connected_devices(const Array<MidiDeviceInfo>& connected_devices, bool input) {
    auto& list = input ? list_inputs : list_outputs;
    for (auto i = list.size(); --i >= 0;) {
        auto& device = *list[i];
        if (!connected_devices.contains(device.device_info)) {
            if (input ? device.in_device.get() != nullptr : device.out_device.get() != nullptr)
                close_device(input, i);
            list.remove(i);
        }
    }
}

void Comp_Devices::update_list(bool input) {
    auto available_devices = input ? MidiInput::getAvailableDevices() : MidiOutput::getAvailableDevices();
    if (device_list_changed(available_devices, input)) {
        auto& list = input ? list_inputs : list_outputs;
        close_connected_devices(available_devices, input);
        ReferenceCountedArray<Dele_Device> new_list;
        for (auto& available_device : available_devices) {
            auto device = find_device(available_device, input);
            if (!device)
                device = new Dele_Device{ available_device };
            new_list.add(device);
        }
        list = new_list;
        if (auto* lbox_device = input ? lbox_inputs.get() : lbox_outputs.get())
            lbox_device->sync_selection_with_device_list(list);
    }
}

void Comp_Devices::update_lists() {
    for (const auto input : { true, false })
        update_list(input);
}

void Comp_Devices::handleIncomingMidiMessage(MidiInput* /*source*/, const MidiMessage& msg) {
    // This is called on the MIDI thread
    const ScopedLock scoped_lock(monitor_lock);
    list_received_messages.add(msg);
    triggerAsyncUpdate();
}

void Comp_Devices::handleAsyncUpdate() {
    // This is called on the message loop
    Array<MidiMessage> messages;
    {
        const ScopedLock scoped_lock(monitor_lock);
        messages.swapWith(list_received_messages);
    }
    String msg_text;
    for (auto& msg : messages) {
        if (msg.getRawData()[0] < 0xf8) {
            if ((msg.isNoteOn() || msg.isNoteOff()) && should_be_logged(Message_Type::note_on_off) ||
                (msg.isAftertouch() || msg.isPitchWheel()) && should_be_logged(Message_Type::aftertouch_pitch_bend) ||
                msg.isController() && should_be_logged(Message_Type::ctrl_change) ||
                msg.isProgramChange() && should_be_logged(Message_Type::pgm_change) ||
                msg.isSysEx() && should_be_logged(Message_Type::sysex))
            {
                in_log->add_msg(msg);
            }
        }
    }
}

void Comp_Devices::send_msg(const MidiMessage& msg) {
    for (auto output : list_outputs)
        if (output->out_device != nullptr)
            output->out_device->sendMessageNow(msg);
}

void Comp_Devices::send_msg_in_slot(const int slot_index) {
    if (slot_index > 0 && slot_index < 5) {
        auto msg_string = slots->msg_in_slot(slot_index);
        if (msg_string.isNotEmpty()) {
            auto msg = Convert::hex_string_to_MIDI_message(msg_string);
            send_msg(msg);
            out_log->add_msg(msg);
        }
    }
}

void Comp_Devices::stop_and_reset_all() {
    for (auto chan = 1; chan < 17; ++chan)
        send_msg(MidiMessage::allNotesOff(chan));
    lbox_inputs->stop_and_reset_all_devices(list_inputs);
    lbox_outputs->stop_and_reset_all_devices(list_outputs);
    lbox_inputs->sync_selection_with_device_list(list_inputs);
}

Comp_Devices::~Comp_Devices() {
    ump::Endpoints::getInstance()->removeListener(*this);
    list_inputs.clear();
    list_outputs.clear();
    lbox_inputs.reset();
    lbox_outputs.reset();
}
