#pragma once

#include <JuceHeader.h>

#include "D_100_Data_User.h"

class Component_Filter_Toggles :
	public Component,
	public Data_User
{
private: ToggleButton tgl_note_on_off;
private: ToggleButton tgl_aftertouch_bend;
private: ToggleButton tgl_pgm_change;
private: ToggleButton tgl_ctrl_change;
private: ToggleButton tgl_sysex;

//==============================================================================
public: Component_Filter_Toggles(Data_Hub* hub);

public: void paint(Graphics& g) override;
public: void resized() override;
public: void mouseDown(const MouseEvent& e) override;

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Component_Filter_Toggles)
};