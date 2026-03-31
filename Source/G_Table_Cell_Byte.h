#pragma once

#include <JuceHeader.h>

#include "D_Data_User.h"

class Table_Cell_Byte :
	public Label,
	public Data_User
{
private: const int row_index, byte_index;
private: const Table_Type table_type;
private: String current_txt;

//==============================================================================
public: Table_Cell_Byte(const int row_index, const int byte_index, 
						const Table_Type table_type, Data_Hub* hub);

private: bool should_be_hilited() const;
public: void paint(Graphics& g) override;
private: String get_byte_string();
private: String build_tooltip() const;
public: void textWasEdited() override;

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Table_Cell_Byte)
};