#pragma once

#include <JuceHeader.h>

class MS_Look_And_Feel :
	public LookAndFeel_V4
{
//==============================================================================
public: MS_Look_And_Feel();

public: void drawButtonBackground(Graphics& g, Button& btn, const Colour& background, 
								  bool hilighted, bool down) override;
public: void drawButtonText(Graphics& g, TextButton& btn, bool hilighted, bool down) override;

public: void drawToggleButton(Graphics& g, ToggleButton& tgl, bool hilighted, bool down) override;
public: void drawTickBox(Graphics& g, Component& c, float x, float y, 
						 float w, float h, const bool ticked, const bool enabled, 
						 const bool hilighted, const bool down) override;


public: void drawTableHeaderColumn(Graphics& g, TableHeaderComponent& c, 
								   const String& col_name, int col_ID, int w, int h,
								   bool mouse_is_over, bool mouse_is_down, int col_flags) override;

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MS_Look_And_Feel)
};