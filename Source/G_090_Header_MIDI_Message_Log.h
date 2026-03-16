#pragma once

#include <JuceHeader.h>

class Header_MIDI_Message_Log :
	public TableHeaderComponent
{
private: const bool not_compare_table;

//==============================================================================
public: explicit Header_MIDI_Message_Log(const bool not_compare_table);

public: const int byte_column_count();
public: void add_data_byte_column(int byte_num);

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Header_MIDI_Message_Log)
};