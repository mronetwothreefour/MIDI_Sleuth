#pragma once

#include <JuceHeader.h>

class Main_Component :
    public Component
{
//==============================================================================
public: Main_Component();

public: void paint(Graphics& g) override;
public: void resized() override;
public: ~Main_Component() override;

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Main_Component)
};
