#pragma once

#include <JuceHeader.h>

#include "D_Data_User.h"
#include "G_MIDI_Handler.h"
#include "G_Msg_Filters.h"
#include "G_Msg_Logs.h"
#include "G_Msg_Slots.h"

class Main_Comp :
    public Component,
    public Data_User
{
private: MIDI_Handler midi_handler;
private: Msg_Filters msg_filters;
private: Msg_Logs msg_logs;
private: Msg_Slots msg_slots;
private: TooltipWindow tooltips;

//==============================================================================
public: explicit Main_Comp(Data_Hub* hub);

public: void resized() override;
public: ~Main_Comp() override;

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Main_Comp)
};
