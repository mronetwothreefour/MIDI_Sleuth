#include "G_020_Main_Component.h"

Main_Component::Main_Component() :
    keyboard{ keyboard_state, MidiKeyboardComponent::horizontalKeyboard },
    input_selector{ new List_MIDI_Devices{ "Midi Input Selector", *this, true } },
    output_selector{ new List_MIDI_Devices{ "Midi Output Selector", *this, false } }
{
    addLabelAndSetStyle(lbl_input_devices);
    addLabelAndSetStyle(lbl_output_devices);
    addLabelAndSetStyle(lbl_received);
    addLabelAndSetStyle(lbl_keyboard);

    keyboard.setName("MIDI Keyboard");
    addAndMakeVisible(keyboard);

    editor_MIDI_monitor.setMultiLine(true);
    editor_MIDI_monitor.setReturnKeyStartsNewLine(false);
    editor_MIDI_monitor.setReadOnly(true);
    editor_MIDI_monitor.setScrollbarsShown(true);
    editor_MIDI_monitor.setCaretVisible(false);
    editor_MIDI_monitor.setPopupMenuEnabled(false);
    editor_MIDI_monitor.setText({});
    addAndMakeVisible(editor_MIDI_monitor);

    keyboard_state.addListener(this);

    addAndMakeVisible(input_selector.get());
    addAndMakeVisible(output_selector.get());

    setSize(732, 520);

    updateDeviceLists();
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

inline MIDI_Device_List_Entry::Ptr Main_Component::findDevice(MidiDeviceInfo device, bool is_input) const {
    const auto& list = is_input ? array_MIDI_inputs : array_MIDI_outputs;
    for (auto& entry : list)
        if (entry->device_info == device)
            return entry;
    return nullptr;
}

void Main_Component::resized() {
    auto margin = 10;

    lbl_input_devices.setBounds(margin, margin,
        (getWidth() / 2) - (2 * margin), 24);

    lbl_output_devices.setBounds((getWidth() / 2) + margin, margin,
        (getWidth() / 2) - (2 * margin), 24);

    input_selector->setBounds(margin, (2 * margin) + 24,
        (getWidth() / 2) - (2 * margin),
        (getHeight() / 2) - ((4 * margin) + 24 + 24));

    output_selector->setBounds((getWidth() / 2) + margin, (2 * margin) + 24,
        (getWidth() / 2) - (2 * margin),
        (getHeight() / 2) - ((4 * margin) + 24 + 24));

    lbl_keyboard.setBounds(margin, getHeight() / 2, getWidth() - (2 * margin), 24);
    keyboard.setBounds(margin, (getHeight() / 2) + (24 + margin), getWidth() - (2 * margin), 64);

    lbl_received.setBounds(margin, (getHeight() / 2) + (24 + (2 * margin) + 64),
        getWidth() - (2 * margin), 24);

    auto y = (getHeight() / 2) + ((2 * 24) + (3 * margin) + 64);
    editor_MIDI_monitor.setBounds(margin, y,
        getWidth() - (2 * margin), getHeight() - y - margin);
}

void Main_Component::handleNoteOn(MidiKeyboardState* /*state*/, int channel, int note_num, float velocity) {
    MidiMessage msg{ MidiMessage::noteOn(channel, note_num, velocity) };
    msg.setTimeStamp(Time::getMillisecondCounterHiRes() * 0.001);
    sendToOutputs(msg);
}

void Main_Component::handleNoteOff(MidiKeyboardState* /*state*/, int channel, int note_num, float velocity) {
    MidiMessage msg(MidiMessage::noteOff(channel, note_num, velocity));
    msg.setTimeStamp(Time::getMillisecondCounterHiRes() * 0.001);
    sendToOutputs(msg);
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
    for (auto& msg : messages)
        msg_text << msg.getDescription() << "\n";
    editor_MIDI_monitor.insertTextAtCaret(msg_text);
}

inline void Main_Component::sendToOutputs(const MidiMessage& msg) {
    for (auto output : array_MIDI_outputs)
        if (output->out_device != nullptr)
            output->out_device->sendMessageNow(msg);
}

Main_Component::~Main_Component() {
    array_MIDI_inputs.clear();
    array_MIDI_outputs.clear();
    keyboard_state.removeListener(this);
    input_selector.reset();
    output_selector.reset();
}
