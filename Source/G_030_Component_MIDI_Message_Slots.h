#pragma once

#include <JuceHeader.h>

#include "D_050_Data_Hub.h"
#include "G_020_Component_MIDI_Devices.h"
#include "G_035_Component_MIDI_Message_Slot.h"

using Msg_Slot_Ptr = std::unique_ptr<Component_MIDI_Message_Slot>;

class Component_MIDI_Message_Slots :
	public Component
{
private: Msg_Slot_Ptr msg_slots[5];

//==============================================================================
public: Component_MIDI_Message_Slots(Data_Hub* hub, Component_MIDI_Devices* devices);

public: ~Component_MIDI_Message_Slots();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Component_MIDI_Message_Slots)
};