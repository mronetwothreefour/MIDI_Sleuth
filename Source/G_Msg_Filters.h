#pragma once

#include <JuceHeader.h>

#include "D_Data_User.h"

class Msg_Filters :
	public Component,
	public Data_User
{
private: ToggleButton tgl_note;
private: ToggleButton tgl_bend;
private: ToggleButton tgl_pgm_change;
private: ToggleButton tgl_ctrl_change;
private: ToggleButton tgl_sysex;

//==============================================================================
public: Msg_Filters(Data_Hub* hub);

public: void paint(Graphics& g) override;
public: void resized() override;
public: void mouseDown(const MouseEvent& e) override;

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Msg_Filters)
};