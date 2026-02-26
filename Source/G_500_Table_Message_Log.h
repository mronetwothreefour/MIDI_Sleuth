#pragma once

#include <JuceHeader.h>

class Table_Message_Log :
	public Component,
	public TableListBoxModel
{
private: TableListBox table;
private: int row_count;

//==============================================================================
public: Table_Message_Log();

public: int getNumRows() override;
public: void log_message(const MidiMessage& msg);
public: void paintRowBackground(Graphics& g, int /*row_num*/, int /*w*/, int /*h*/, bool /*is_selected*/) override;
public: void paintCell(Graphics& g, int row_num, int col_id, int w, int h, bool is_selected) override;
};