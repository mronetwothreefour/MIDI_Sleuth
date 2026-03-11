#pragma once

#include <JuceHeader.h>

#include "D_000_Tree_MIDI_Messages.h"

class Header_MIDI_Message_Log;

class Table_MIDI_Message_Log :
	public Component,
	public TableListBoxModel,
	private ValueTree::Listener
{
private: TableListBox table;
private: Tree_MIDI_Messages* message_log;
private: Header_MIDI_Message_Log* header;

//==============================================================================
public: explicit Table_MIDI_Message_Log(Tree_MIDI_Messages* message_log);

public: int getNumRows() override;
public: const String get_bytes_for_first_selected_row();
public: void scroll_to_row(const int row_num);
public: void paintRowBackground(Graphics& g, int row_num, int w, int h, bool is_selected) override;
public: void paintCell(Graphics& g, int row_num, int col_num, int w, int h, bool is_selected) override;
public: Component* refreshComponentForCell(int row_num, int col_num, bool is_selected, Component* c) override;
public: void resized() override;
private: void valueTreeChildAdded(ValueTree& parent_tree, ValueTree& new_row) override;
private: void valueTreeChildRemoved(ValueTree& parent_tree, ValueTree& row, int row_index) override;
public: ~Table_MIDI_Message_Log();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Table_MIDI_Message_Log)
};