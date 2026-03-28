#pragma once

#include <JuceHeader.h>

#include "D_110_Data_User.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class Comp_Main :
    public Component,
    public Data_User
{
public:
    //==============================================================================
    Comp_Main(Data_Hub* hub);
    ~Comp_Main() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Comp_Main)
};
