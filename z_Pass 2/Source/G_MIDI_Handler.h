#pragma once

#include <JuceHeader.h>

#include "D_Data_User.h"
#include "G_MIDI_Device_Lbox.h"

class MIDI_Handler :
    public Component,
    private MidiInputCallback,
    private AsyncUpdater,
    public Data_User
{
private: std::unique_ptr<MIDI_Device_Lbox> lbox_inputs, lbox_outputs;
private: CriticalSection monitor_lock;
private: Array<MidiMessage> list_received_messages;

//==============================================================================
public: explicit MIDI_Handler(Data_Hub* hub);

public: void paint(Graphics& g) override;
public: void resized() override;
private: void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& msg) override;
private: void handleAsyncUpdate() override;
private: void send_msg(const MidiMessage& msg);
public: void send_msg_in_slot(const int slot_index);
public: void stop_and_reset_all();
public: ~MIDI_Handler();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MIDI_Handler)
};