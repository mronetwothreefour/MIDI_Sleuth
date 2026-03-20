#pragma once

#include <JuceHeader.h>

#include "D_100_Data_User.h"

class Component_Edit_MIDI_Message :
	public Component,
	public TableListBoxModel,
	public Data_User
{
private: const int slot_index;
private: TableListBox table;

//==============================================================================
public: Component_Edit_MIDI_Message(const int slot_index, Data_Hub* hub);

public: int getNumRows() override;
public: void add_columns_for_message_bytes();
public: void paintRowBackground(Graphics& /*g*/, int /*row_num*/, int /*w*/, int /*h*/, bool /*selected*/) override {}
public: void paintCell(Graphics& /*g*/, int /*row_num*/, int /*col_ID*/, int /*w*/, int /*h*/, bool /*selected*/) override {}
public: Component* refreshComponentForCell(int row_num, int col_ID, bool selected, Component* c) override;
//public: void cellClicked(int row_num, int col_ID, const MouseEvent& e) override;
//public: bool keyPressed(const KeyPress& key) override;

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Component_Edit_MIDI_Message)
};