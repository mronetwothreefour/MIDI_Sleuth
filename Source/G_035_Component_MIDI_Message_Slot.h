#pragma once

#include <JuceHeader.h>

#include "D_100_Data_User.h"
#include "G_020_Component_MIDI_Devices.h"

class Component_MIDI_Message_Slot :
	public Component,
	public Data_User
{
private: const int slot_index;
private: Component_MIDI_Devices* devices;
private: TextButton btn_edit;
private: TextButton btn_send;

//==============================================================================
public: Component_MIDI_Message_Slot(int slot_index, Data_Hub* hub, Component_MIDI_Devices* devices);

public: void paint(Graphics& g) override;
private: void show_edit_window_for_slot();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Component_MIDI_Message_Slot)
};