#pragma once

#include <JuceHeader.h>

#include "G_020_Main_Component.h"

class Main_Window :
    public DocumentWindow
{
//==============================================================================
public: Main_Window(String name);

public: void closeButtonPressed() override;

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Main_Window)
};
