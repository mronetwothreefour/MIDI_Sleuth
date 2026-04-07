#pragma once

#include <JuceHeader.h>

#include "D_Data_User.h"
#include "G_MIDI_Handler.h"
#include "G_Msg_Slot_Edit_Win.h"

class Msg_Slot :
	public Component,
	public Data_User
{
private: const int slot_index;
private: MIDI_Handler* midi_handler;
private: TextButton btn_edit;
private: TextButton btn_send;
private: std::unique_ptr<Msg_Slot_Edit_Win> win_edit_msg;

//==============================================================================
public: Msg_Slot(int slot_index, Data_Hub* hub, MIDI_Handler* midi_handler);

public: void paint(Graphics& g) override;
private: void show_message_editor();
public: ~Msg_Slot();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Msg_Slot)
};