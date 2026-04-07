#pragma once

#include <JuceHeader.h>

#include "G_Main_Comp.h"

class Main_Win :
    public DocumentWindow
{
//private: MS_Look_And_Feel l_a_f;

//==============================================================================
public: Main_Win(String name/*, Data_Hub* hub*/);

public: void closeButtonPressed() override;
public: ~Main_Win();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Main_Win)
};
