#pragma once

#include <JuceHeader.h>

#include "D_Data_User.h"

class Table_Cell :
	public Label,
	public Data_User
{
private: int row_index;
private: int col_id;
private: int byte_index;
private: Data_Tree* tree;
private: Table_Type table_type;
private: String current_txt;

//==============================================================================
public: Table_Cell(Data_Tree* tree, Data_Hub* hub);

private: bool should_be_hilited() const;
public: void paint(Graphics& g) override;
public: void set_row_and_col(const int new_row_index, const int new_col_id);
private: String get_byte_string();
private: String build_tooltip() const;
public: void textWasEdited() override;

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Table_Cell)
};