#pragma once

#include <JuceHeader.h>

#include "D_050_Data_Hub.h"
#include "G_020_Component_MIDI_Devices.h"
#include "G_035_Component_MIDI_Message_Slot.h"

class Component_MIDI_Message_Slots :
	public Component
{
private: Component_MIDI_Message_Slot msg_slot_0;
private: Component_MIDI_Message_Slot msg_slot_1;
private: Component_MIDI_Message_Slot msg_slot_2;
private: Component_MIDI_Message_Slot msg_slot_3;
private: Component_MIDI_Message_Slot msg_slot_4;

//==============================================================================
public: Component_MIDI_Message_Slots(Data_Hub* hub, Component_MIDI_Devices* devices);

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Component_MIDI_Message_Slots)
};