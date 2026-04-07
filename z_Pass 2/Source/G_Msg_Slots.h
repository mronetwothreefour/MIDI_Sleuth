#pragma once

#include <JuceHeader.h>

#include "D_Data_Hub.h"
#include "G_MIDI_Handler.h"
#include "G_Msg_Slot.h"

using Msg_Slot_Ptr = std::unique_ptr<Msg_Slot>;

class Msg_Slots :
	public Component
{
private: Msg_Slot_Ptr msg_slots[5];

//==============================================================================
public: Msg_Slots(Data_Hub* hub, MIDI_Handler* midi_handler);

public: ~Msg_Slots();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Msg_Slots)
};