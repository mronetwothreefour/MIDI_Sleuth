#pragma once

#include <JuceHeader.h>

#include "D_000_Tree_MIDI_Messages.h"

class Delegate_Data_Byte :
	public Component,
	public SettableTooltipClient
{
private: const int row_num, col_ID;
private: Tree_MIDI_Messages* message_log;
private: bool hilighted;

//==============================================================================
public: Delegate_Data_Byte(const int row_num, const int col_ID, Tree_MIDI_Messages* message_log);

public: void set_hilighted(const bool should_be_hilighted);
public: void paint(Graphics& g) override;

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Delegate_Data_Byte)
};