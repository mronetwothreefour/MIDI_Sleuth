#pragma once

#include <JuceHeader.h>

class Header_Message_Log :
	public TableHeaderComponent
{
//==============================================================================
public: Header_Message_Log();

public: const int byte_column_count();
public: void add_data_byte_column(int byte_num);
};