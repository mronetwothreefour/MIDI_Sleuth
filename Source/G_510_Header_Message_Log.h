#pragma once

#include <JuceHeader.h>

class Header_Message_Log :
	public TableHeaderComponent
{
//==============================================================================
public: Header_Message_Log();

public: const int byte_column_count();
public: void add_data_byte_column(int byte_num);

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Header_Message_Log)
};