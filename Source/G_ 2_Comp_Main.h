#pragma once

#include <JuceHeader.h>

#include "D_Data_User.h"
#include "G_Comp_Msg_Handler.h"

class Comp_Main :
    public Component,
    public Data_User
{
private: Comp_Msg_Handler devices;
private: TooltipWindow tooltips;

//==============================================================================
public: explicit Comp_Main(Data_Hub* hub);

public: void resized() override;
public: ~Comp_Main() override;

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Comp_Main)
};
