#pragma once

#include <JuceHeader.h>

#include "D_000_Tree_MIDI_Messages.h"

class Cell_Data_Byte :
	public Component,
	public SettableTooltipClient
{
private: const int row_num, col_num;
private: Tree_MIDI_Messages* message_log;

//==============================================================================
public: Cell_Data_Byte(const int row_num, const int col_num, Tree_MIDI_Messages* message_log);

public: void paint(Graphics& g) override;

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Cell_Data_Byte)
};