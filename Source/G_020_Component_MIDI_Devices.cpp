#include "G_020_Component_MIDI_Devices.h"

Component_MIDI_Devices::Component_MIDI_Devices(Data_Hub* hub) :
	Data_User{ hub },
    in_selector{ new List_MIDI_Devices{ "Midi Input Selector", this, true } },
    out_selector{ new List_MIDI_Devices{ "Midi Output Selector", this, false } }
{
    addAndMakeVisible(in_selector.get());
    addAndMakeVisible(out_selector.get());

    update_device_lists();

    ump::Endpoints::getInstance()->addListener(*this);
}

void Component_MIDI_Devices::paint(Graphics& g) {
    g.setFont(FONT::device_list_header);
    g.setColour(COLOR::text);
    auto w = in_selector->getWidth();
    Rectangle<int> lbl_input_area{ 0, 0, w, XYWH::lbl_device_list_h};
    g.drawText("MIDI Input Devices", lbl_input_area, Justification::centredTop);
    Rectangle<int> lbl_output_area{ w + XYWH::margin, 0, w, XYWH::lbl_device_list_h };
    g.drawText("MIDI Output Devices", lbl_output_area, Justification::centredTop);
}

void Component_MIDI_Devices::resized() {
    auto y = XYWH::lbl_device_list_h;
    auto w = XYWH::device_list_min_w;
    if (getWidth() > w + XYWH::margin)
        w = (getWidth() / 2) - (XYWH::margin / 2);
    auto h = XYWH::device_list_h;
    in_selector->setBounds(0, y, w, h);
    out_selector->setBounds(w + XYWH::margin, y, w, h);
}

void Component_MIDI_Devices::open_device(bool is_input, int index) {
    if (is_input) {
        jassert(array_MIDI_inputs[index]->in_device.get() == nullptr);
        auto& device_id = array_MIDI_inputs[index]->device_info.identifier;
        array_MIDI_inputs[index]->in_device = MidiInput::openDevice(device_id, this);
        if (array_MIDI_inputs[index]->in_device.get() == nullptr) {
            DBG("Main_Component::openDevice: open input device for index = " << index << " failed!");
            return;
        }
        array_MIDI_inputs[index]->in_device->start();
    }
    else {
        jassert(array_MIDI_outputs[index]->out_device.get() == nullptr);
        auto& device_id = array_MIDI_outputs[index]->device_info.identifier;
        array_MIDI_outputs[index]->out_device = MidiOutput::openDevice(device_id);
        if (array_MIDI_outputs[index]->out_device.get() == nullptr)
            DBG("Main_Component::openDevice: open output device for index = " << index << " failed!");
    }
}

void Component_MIDI_Devices::close_device(bool is_input, int index) {
    auto& list = is_input ? array_MIDI_inputs : array_MIDI_outputs;
    list[index]->stop_and_reset();
}

int Component_MIDI_Devices::count_MIDI_inputs() const noexcept {
    return array_MIDI_inputs.size();
}

int Component_MIDI_Devices::count_MIDI_outputs() const noexcept {
    return array_MIDI_outputs.size();
}

bool Component_MIDI_Devices::device_list_has_changed(const Array<MidiDeviceInfo>& available_devices, bool is_input) {
    auto& list = is_input ? array_MIDI_inputs : array_MIDI_outputs;
    if (available_devices.size() != list.size())
        return true;
    for (auto i = 0; i < available_devices.size(); ++i)
        if (available_devices[i] != list[i]->device_info)
            return true;
    return false;
}

void Component_MIDI_Devices::endpointsChanged() {
    update_device_lists();
}

Delegate_MIDI_Device::Ptr Component_MIDI_Devices::get_device(int index, bool is_input) const noexcept {
    return is_input ? array_MIDI_inputs[index] : array_MIDI_outputs[index];
}

Delegate_MIDI_Device::Ptr Component_MIDI_Devices::find_device(MidiDeviceInfo device, bool is_input) const {
    const auto& list = is_input ? array_MIDI_inputs : array_MIDI_outputs;
    for (auto& entry : list)
        if (entry->device_info == device)
            return entry;
    return nullptr;
}

void Component_MIDI_Devices::close_unplugged_devices(const Array<MidiDeviceInfo>& plugged_in_devices, bool is_input) {
    auto& list = is_input ? array_MIDI_inputs : array_MIDI_outputs;
    for (auto i = list.size(); --i >= 0;) {
        auto& device = *list[i];
        if (!plugged_in_devices.contains(device.device_info)) {
            if (is_input ? device.in_device.get() != nullptr : device.out_device.get() != nullptr)
                close_device(is_input, i);
            list.remove(i);
        }
    }
}

void Component_MIDI_Devices::update_device_list(bool is_input) {
    auto available_devices = is_input ? MidiInput::getAvailableDevices() : MidiOutput::getAvailableDevices();
    if (device_list_has_changed(available_devices, is_input)) {
        auto& list = is_input ? array_MIDI_inputs : array_MIDI_outputs;
        close_unplugged_devices(available_devices, is_input);
        ReferenceCountedArray<Delegate_MIDI_Device> new_list;
        for (auto& device : available_devices) {
            auto entry = find_device(device, is_input);
            if (!entry)
                entry = new Delegate_MIDI_Device{ device };
            new_list.add(entry);
        }
        list = new_list;
        if (auto* device_selector = is_input ? in_selector.get() : out_selector.get())
            device_selector->sync_selection_with_device_list(list);
    }
}

void Component_MIDI_Devices::update_device_lists() {
    for (const auto is_input : { true, false })
        update_device_list(is_input);
}

void Component_MIDI_Devices::handleIncomingMidiMessage(MidiInput* /*source*/, const MidiMessage& msg) {
    // This is called on the MIDI thread
    const ScopedLock scoped_lock(monitor_lock);
    array_incoming_messages.add(msg);
    triggerAsyncUpdate();
}

void Component_MIDI_Devices::handleAsyncUpdate() {
    // This is called on the message loop
    Array<MidiMessage> messages;
    {
        const ScopedLock scoped_lock(monitor_lock);
        messages.swapWith(array_incoming_messages);
    }
    String msg_text;
    for (auto& msg : messages) {
        if (msg.getRawData()[0] < 0xf8) {
            if ((msg.isNoteOn() || msg.isNoteOff()) && should_log(Message_Type::note_on_off) ||
                (msg.isAftertouch() || msg.isPitchWheel()) && should_log(Message_Type::aftertouch_pitch_bend) ||
                msg.isController() && should_log(Message_Type::ctrl_change) ||
                msg.isProgramChange() && should_log(Message_Type::pgm_change) ||
                msg.isSysEx() && should_log(Message_Type::sysex))
            {
                in_log->log_message(msg);
            }
        }
    }
}

void Component_MIDI_Devices::send_to_outputs(const MidiMessage& msg) {
    for (auto output : array_MIDI_outputs)
        if (output->out_device != nullptr)
            output->out_device->sendMessageNow(msg);
}

void Component_MIDI_Devices::send_stored_message(const int slot_index) {
    if (slot_index < 5) {
        auto& msg_string = message_in_slot(slot_index);
        if (msg_string.isNotEmpty()) {
            std::vector<uint8> msg_data;
            for (auto i = 0; i < msg_string.length(); i += 2) {
                auto byte_string{ msg_string.substring(i, i + 2) };
                msg_data.push_back((uint8)byte_string.getHexValue32());
            }
            auto msg_size = msg_data.size();
            auto timestamp = Time::getMillisecondCounterHiRes() * 0.001;
            MidiMessage msg{};
            if (msg_size == 2)
                msg = MidiMessage{ msg_data[0], msg_data[1], timestamp };
            if (msg_size == 3)
                msg = MidiMessage{ msg_data[0], msg_data[1], msg_data[2], timestamp };
            if (msg_size > 3)
                msg = MidiMessage{ &msg_data, (int)msg_data.size(), timestamp };
            send_to_outputs(msg);
            out_log->log_message(msg);
        }
    }
}

void Component_MIDI_Devices::stop_and_reset_all() {
    for (auto channel = 1; channel < 17; ++channel)
        send_to_outputs(MidiMessage::allNotesOff(channel));
    in_selector->stop_and_reset_all_devices(array_MIDI_inputs);
    out_selector->stop_and_reset_all_devices(array_MIDI_outputs);    in_selector->sync_selection_with_device_list(array_MIDI_inputs);
}

Component_MIDI_Devices::~Component_MIDI_Devices() {
    ump::Endpoints::getInstance()->removeListener(*this);
    array_MIDI_inputs.clear();
    array_MIDI_outputs.clear();
    in_selector.reset();
    out_selector.reset();
}

