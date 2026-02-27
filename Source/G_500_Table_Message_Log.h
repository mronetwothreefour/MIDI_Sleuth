#pragma once

#include <JuceHeader.h>

#include "D_000_Tree_MIDI_Message_Log.h"

class Table_Message_Log :
	public Component,
	public TableListBoxModel,
	private ValueTree::Listener
{
private: TableListBox table;
private: Tree_MIDI_Message_Log& message_log;

//==============================================================================
public: Table_Message_Log() = delete;
public: explicit Table_Message_Log(Tree_MIDI_Message_Log& message_log);

public: int getNumRows() override;
public: void scroll_to_row(const int row_num);
public: void paintRowBackground(Graphics& g, int row_num, int w, int h, bool is_selected) override;
public: void paintCell(Graphics& g, int row_num, int col_num, int w, int h, bool is_selected) override;
public: void resized() override;
private: void valueTreeChildAdded(ValueTree& parent_tree, ValueTree& new_row) override;
public: ~Table_Message_Log();
};