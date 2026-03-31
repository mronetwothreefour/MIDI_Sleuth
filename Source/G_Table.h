#pragma once

#include <JuceHeader.h>

#include "D_Data_User.h"

class Table_Header;

class Table :
	public Component,
	public TableListBoxModel,
	private ValueTree::Listener,
	public Data_User,
	public ApplicationCommandTarget
{
private: TableListBox table;
private: const Table_Type table_type;
private: Table_Header* header;
private: Tree_Msg_Log* tree;
private: const int slot_index;

//==============================================================================
public: Table(const Table_Type table_type, Data_Hub* hub);

public: int getNumRows() override;
public: void compare_selected_messages();
public: void separate_msg_bytes(String& msg, const String& separator);
public: void scroll_to_msg_row(const int row_index);
public: void scroll_to_byte_col(const int byte_index);
private: void show_jump_to_byte_dialog();
public: void paintRowBackground(Graphics& g, int row_index, int w, int h, bool is_selected) override;
public: void paintCell(Graphics& g, int row_index, int col_id, int w, int h, bool is_selected) override;
public: Component* refreshComponentForCell(int row_index, int col_id, bool is_selected, Component* c) override;
public: void resized() override;
private: void valueTreePropertyChanged(ValueTree& parent_tree, const Identifier& property_id) override;
private: void valueTreeChildAdded(ValueTree& parent_tree, ValueTree& new_row) override;
private: void valueTreeChildRemoved(ValueTree& parent_tree, ValueTree& row, int row_index) override;
private: void cellClicked(int row_index, int col_id, const MouseEvent& e) override;
public: ApplicationCommandTarget* getNextCommandTarget() override;
public: void getAllCommands(Array<int>& cmd_list) override;
public: void getCommandInfo(int cmd, ApplicationCommandInfo& info) override;
public: bool perform(const InvocationInfo& info) override;
public: ~Table();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Table)
};