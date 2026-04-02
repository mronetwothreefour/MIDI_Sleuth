#pragma once

#include <JuceHeader.h>

#include "D_Data_User.h"
#include "G_Table.h"

class Msg_Slot_Edit_Comp :
	public Component,
	public TextEditor::Listener,
	public Data_User
{
private: const int slot_index;
private: Data_Tree* slot_tree;
private: Table table;
private: TextEditor edit_description;

//==============================================================================
public: Msg_Slot_Edit_Comp(const Table_Type table_type, Data_Hub* hub);

public: void paint(Graphics& g) override;
private: void textEditorTextChanged(TextEditor& editor) override;
public: bool keyPressed(const KeyPress& key) override;
public: ~Msg_Slot_Edit_Comp();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Msg_Slot_Edit_Comp)
};