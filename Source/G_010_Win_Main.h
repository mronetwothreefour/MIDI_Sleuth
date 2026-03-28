#pragma once

#include <JuceHeader.h>

#include "G_000_Look_And_Feel.h"
#include "G_100_Comp_Main.h"

class Win_Main :
    public DocumentWindow
{
private: MS_Look_And_Feel l_a_f;

//==============================================================================
public: Win_Main(String name, Data_Hub* hub);

public: void closeButtonPressed() override;
public: ~Win_Main();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Win_Main)
};
