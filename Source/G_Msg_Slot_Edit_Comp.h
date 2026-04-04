#pragma once

#include <JuceHeader.h>

#include "D_Data_User.h"
#include "G_MIDI_Handler.h"
#include "G_Table.h"

class Msg_Slot_Edit_Comp :
	public Component,
	public Label::Listener,
	public Data_User
{
private: const int slot_index;
private: Data_Tree* slot_tree;
private: Table table;
private: Label edit_description;
private: TextButton btn_send;

//==============================================================================
public: Msg_Slot_Edit_Comp(const Table_Type table_type, Data_Hub* hub, MIDI_Handler* midi_handler);

public: void paint(Graphics& g) override;
private: void labelTextChanged(Label* lbl) override;
public: bool keyPressed(const KeyPress& key) override;
public: ~Msg_Slot_Edit_Comp();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Msg_Slot_Edit_Comp)
};