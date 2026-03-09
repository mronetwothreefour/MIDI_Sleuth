#pragma once

#include <JuceHeader.h>

class MS_Look_And_Feel :
	public LookAndFeel_V4
{
//==============================================================================
public: MS_Look_And_Feel();

public: void drawTableHeaderColumn(Graphics& g, TableHeaderComponent& c, 
								   const String& col_name, int col_ID, int w, int h,
								   bool mouse_is_over, bool mouse_is_down, int col_flags) override;

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MS_Look_And_Feel)
};