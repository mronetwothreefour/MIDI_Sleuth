#pragma once

#include <JuceHeader.h>

#include "D_Data_User.h"
#include "G_MIDI_Device_Lbox.h"

class MIDI_Handler :
	public Component,
	private MidiInputCallback,
	private AsyncUpdater,
	public Data_User,
	public ApplicationCommandTarget
{
// device list boxes are unique pointers so that
// they can be deleted before the tabbed component
// (if they aren't, an exception is thrown)
private: std::unique_ptr<MIDI_Device_Lbox> lbox_inputs;
private: std::unique_ptr<MIDI_Device_Lbox> lbox_outputs;
private: TabbedComponent tabs;
private: TextButton btn_reset;
private: CriticalSection monitor_lock;
private: Array<MidiMessage> list_received_messages;
private: ApplicationCommandTarget* next_cmd_target;

//==============================================================================
public: MIDI_Handler(Data_Hub* hub);

public: void paint(Graphics& g) override;
private: void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& msg) override;
private: void handleAsyncUpdate() override;
private: void send_msg(const MidiMessage& msg);
public: void send_msg_in_slot(const int slot_index);
public: void stop_and_reset_all();
public: void set_next_cmd_target(ApplicationCommandTarget* new_target);
public: ApplicationCommandTarget* getNextCommandTarget() override;
public: void getAllCommands(Array<int>& cmd_list) override;
public: void getCommandInfo(int cmd, ApplicationCommandInfo& info) override;
public: bool perform(const InvocationInfo& info) override;
public: ~MIDI_Handler();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MIDI_Handler)
};
