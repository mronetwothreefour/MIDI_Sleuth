#include "G_010_Main_Component.h"

Main_Component::Main_Component(Data_Hub* hub) :
    Data_User{ hub },
    lbl_input_devices{ "Midi Input Label",  "Input Devices" },
    lbl_output_devices{ "Midi Output Label", "Output Devices" },
    lbl_msg_slot_1{ "Storage Slot 1", "Storage Slot 1:" },
    lbl_msg_log{ "MIDI Messages", "MIDI Messages:" },
    input_selector{ new List_MIDI_Devices{ "Midi Input Selector", *this, true } },
    output_selector{ new List_MIDI_Devices{ "Midi Output Selector", *this, false } },
    tabs_message_logs{ hub }
{
    add_label_and_set_style(lbl_input_devices);
    add_label_and_set_style(lbl_output_devices);
    add_label_and_set_style(lbl_msg_log);

    addAndMakeVisible(input_selector.get());
    addAndMakeVisible(output_selector.get());

    addAndMakeVisible(tabs_message_logs);

    addChildComponent(tooltips);
    tooltips.setMillisecondsBeforeTipAppears(2000);

    setSize(960, 640);

    update_device_lists();
}

void Main_Component::open_device(bool is_input, int index) {
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

void Main_Component::closeDevice(bool is_input, int index) {
    auto& list = is_input ? array_MIDI_inputs : array_MIDI_outputs;
    list[index]->stop_and_reset();
}

int Main_Component::count_MIDI_inputs() const noexcept {
    return array_MIDI_inputs.size();
}

int Main_Component::count_MIDI_outputs() const noexcept {
    return array_MIDI_outputs.size();
}

inline bool Main_Component::device_list_has_changed(const Array<MidiDeviceInfo>& available_devices, bool is_input) {
    auto& list = is_input ? array_MIDI_inputs : array_MIDI_outputs;
    if (available_devices.size() != list.size())
        return true;
    for (auto i = 0; i < available_devices.size(); ++i)
        if (available_devices[i] != list[i]->device_info)
            return true;
    return false;
}

MIDI_Device_List_Entry::Ptr Main_Component::get_device(int index, bool is_input) const noexcept {
    return is_input ? array_MIDI_inputs[index] : array_MIDI_outputs[index];
}

inline MIDI_Device_List_Entry::Ptr Main_Component::find_device(MidiDeviceInfo device, bool is_input) const {
    const auto& list = is_input ? array_MIDI_inputs : array_MIDI_outputs;
    for (auto& entry : list)
        if (entry->device_info == device)
            return entry;
    return nullptr;
}

inline void Main_Component::close_unplugged_devices(const Array<MidiDeviceInfo>& plugged_in_devices, bool is_input) {
    auto& list = is_input ? array_MIDI_inputs : array_MIDI_outputs;
    for (auto i = list.size(); --i >= 0;) {
        auto& device = *list[i];
        if (!plugged_in_devices.contains(device.device_info)) {
            if (is_input ? device.in_device.get() != nullptr : device.out_device.get() != nullptr)
                closeDevice(is_input, i);
            list.remove(i);
        }
    }
}

inline void Main_Component::update_device_list(bool is_input) {
    auto available_devices = is_input ? MidiInput::getAvailableDevices() : MidiOutput::getAvailableDevices();
    if (device_list_has_changed(available_devices, is_input)) {
        auto& list = is_input ? array_MIDI_inputs : array_MIDI_outputs;
        close_unplugged_devices(available_devices, is_input);
        ReferenceCountedArray<MIDI_Device_List_Entry> new_list;
        for (auto& device : available_devices) {
            auto entry = find_device(device, is_input);
            if (!entry)
                entry = new MIDI_Device_List_Entry{ device };
            new_list.add(entry);
        }
        list = new_list;
        if (auto* device_selector = is_input ? input_selector.get() : output_selector.get())
            device_selector->sync_selection_with_device_list(list);
    }
}

inline void Main_Component::update_device_lists() {
    for (const auto is_input : { true, false })
        update_device_list(is_input);
}

inline void Main_Component::add_label_and_set_style(Label& label) {
    label.setFont(FONT::device_list_header);
    label.setJustificationType(Justification::centredLeft);
    label.setEditable(false, false, false);
    label.setColour(TextEditor::textColourId, Colours::black);
    label.setColour(TextEditor::backgroundColourId, Colours::transparentBlack);
    addAndMakeVisible(label);
}

void Main_Component::resized() {
    auto w = getWidth();
    auto h = getHeight();
    auto gap = 10;
    auto selector_y = (2 * gap) + 24;
    auto selector_w = (w / 2) - (2 * gap);
    auto selector_h = (h / 4) - ((4 * gap) + 14);
    lbl_input_devices.setBounds(gap, gap, selector_w, 24);
    lbl_output_devices.setBounds((w / 2) + gap, gap, selector_w, 24);
    input_selector->setBounds(gap, selector_y, selector_w, selector_h);
    output_selector->setBounds((w / 2) + gap, selector_y, selector_w, selector_h);
    auto keyboard_w = w - (2 * gap);
    lbl_msg_log.setBounds(gap, (h / 4) + (24 + (2 * gap) + 64), keyboard_w, 24);
    auto monitor_y = (h / 4) + ((2 * 24) + (3 * gap) + 64);
    tabs_message_logs.setBounds(gap, monitor_y, keyboard_w, h - monitor_y - gap);
}

inline void Main_Component::handleIncomingMidiMessage(MidiInput*, const MidiMessage& msg) {
    // This is called on the MIDI thread
    const ScopedLock scoped_lock(monitor_lock);
    array_incoming_messages.add(msg);
    triggerAsyncUpdate();
}

inline void Main_Component::handleAsyncUpdate() {
    // This is called on the message loop
    Array<MidiMessage> messages;
    {
        const ScopedLock scoped_lock(monitor_lock);
        messages.swapWith(array_incoming_messages);
    }
    String msg_text;
    for (auto& msg : messages) {
        auto row_num = in_log->log_message(msg);
        tabs_message_logs.scroll_to_row(true, row_num);
    }
}

inline void Main_Component::sendToOutputs(const MidiMessage& msg) {
    for (auto output : array_MIDI_outputs)
        if (output->out_device != nullptr)
            output->out_device->sendMessageNow(msg);
}

void Main_Component::transmit_stored_message(const int slot_index) {
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
                msg = MidiMessage{ msg_data[0], msg_data[1], timestamp};
            if (msg_size == 3)
                msg = MidiMessage{ msg_data[0], msg_data[1], msg_data[2], timestamp};
            if (msg_size > 3)
                msg = MidiMessage{ &msg_data, (int)msg_data.size(), timestamp };
            sendToOutputs(msg);
            auto row_num = out_log->log_message(msg);
            tabs_message_logs.scroll_to_row(false, row_num);
        }
    }
}

bool Main_Component::keyPressed(const KeyPress& key) {
    if (key == KeyPress{ 'i', ModifierKeys::altModifier, 0 })
        tabs_message_logs.setCurrentTabIndex(0);
    if (key == KeyPress{ 'o', ModifierKeys::altModifier, 0 })
        tabs_message_logs.setCurrentTabIndex(1);
    if (key == KeyPress{ '1', ModifierKeys::ctrlModifier, 0 }) {
        auto msg_bytes = tabs_message_logs.get_bytes_for_selected_row_in_current_tab();
        set_message_in_slot(msg_bytes, 0);
    }
    if (key == KeyPress{ '1', ModifierKeys::altModifier, 0 }) {
       transmit_stored_message(0);
    }
    return false;
}

Main_Component::~Main_Component() {
    array_MIDI_inputs.clear();
    array_MIDI_outputs.clear();
    input_selector.reset();
    output_selector.reset();
}
