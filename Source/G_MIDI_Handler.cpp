#include "G_MIDI_Handler.h"

using namespace XYWH;

MIDI_Handler::MIDI_Handler(Data_Hub* hub) :
    Data_User{ hub },
    lbox_inputs{ new MIDI_Device_Lbox{ "Midi Input Selector", true, this } },
    lbox_outputs{ new MIDI_Device_Lbox{ "Midi Output Selector" } }
{
    addAndMakeVisible(lbox_inputs.get());
    addAndMakeVisible(lbox_outputs.get());
}

void MIDI_Handler::paint(Graphics& g) {
    g.setFont(FONT::lbl_lbox_device);
    g.setColour(COLOR::txt);
    auto w = lbox_inputs->getWidth();
    Rectangle<int> lbl_input_area{ 0, 0, w, lbl_lbox_devices_h };
    g.drawText("MIDI Input Devices", lbl_input_area, Justification::centredTop);
    Rectangle<int> lbl_output_area{ w + win_main_inset, 0, w, lbl_lbox_devices_h };
    g.drawText("MIDI Output Devices", lbl_output_area, Justification::centredTop);
}

void MIDI_Handler::resized() {
    auto y = lbl_lbox_devices_h;
    auto w = lbox_devices_min_w;
    if (getWidth() > w + win_main_inset)
        w = (getWidth() / 2) - (win_main_inset / 2);
    auto h = lbox_devices_h;
    lbox_inputs->setBounds(0, y, w, h);
    lbox_outputs->setBounds(w + win_main_inset, y, w, h);
}

void MIDI_Handler::handleIncomingMidiMessage(MidiInput* /*source*/, const MidiMessage& msg) {
    // This is called on the MIDI thread
    const ScopedLock scoped_lock(monitor_lock);
    list_received_messages.add(msg);
    triggerAsyncUpdate();
}

void MIDI_Handler::handleAsyncUpdate() {
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

void MIDI_Handler::send_msg(const MidiMessage& msg) {
    lbox_outputs->pass_msg_to_open_outputs(msg);
}

void MIDI_Handler::send_msg_in_slot(const int slot_index) {
    if (slot_index > 0 && slot_index < 5) {
        auto msg_string = slots->msg_in_slot(slot_index);
        if (msg_string.isNotEmpty()) {
            auto msg = Convert::hex_string_to_MIDI_message(msg_string);
            send_msg(msg);
            out_log->add_msg(msg);
        }
    }
}

void MIDI_Handler::stop_and_reset_all() {
    for (auto chan = 1; chan < 17; ++chan)
        send_msg(MidiMessage::allNotesOff(chan));
    lbox_inputs->stop_and_reset_all_devices();
    lbox_outputs->stop_and_reset_all_devices();
}

MIDI_Handler::~MIDI_Handler() {
    lbox_inputs.reset();
    lbox_outputs.reset();
}
