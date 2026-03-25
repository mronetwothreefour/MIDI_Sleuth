#pragma once

#include <JuceHeader.h>

#include "G_005_MS_Look_And_Feel.h"
#include "G_010_Main_Component.h"

class Main_Window :
    public DocumentWindow
{
private: MS_Look_And_Feel look_and_feel;

//==============================================================================
public: Main_Window(String name, Data_Hub* hub);

public: void closeButtonPressed() override;
public: ~Main_Window();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Main_Window)
};
