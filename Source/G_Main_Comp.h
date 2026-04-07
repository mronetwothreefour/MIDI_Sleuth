#pragma once

#include <JuceHeader.h>

class Main_Comp :
    public Component
{

//==============================================================================
public: Main_Comp();

public: void paint (Graphics&) override;
public: void resized() override;
public: ~Main_Comp() override;

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Main_Comp)
};
