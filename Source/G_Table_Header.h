#pragma once

#include <JuceHeader.h>

#include "C_ENUM.h"

using namespace ENUM;

class Table_Header :
	public TableHeaderComponent
{
private: const Table_Type table_type;
private: const int num_non_byte_cols;

//==============================================================================
public: explicit Table_Header(const Table_Type table_type);

public: const int byte_col_count();
public: void add_byte_col(int byte_index);
private: void columnClicked(int col_id, const ModifierKeys& mods) override;

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Table_Header)
};