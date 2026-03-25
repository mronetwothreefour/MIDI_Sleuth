#pragma once

#include <JuceHeader.h>

#include "G_070_Table_MIDI_Message_Log.h"

class Component_Jump_To_Byte :
	public Component,
	public TextEditor::Listener
{
private: Table_MIDI_Message_Log& table;
private: TextEditor edit_byte;
private: TextButton btn_cancel;
private: TextButton btn_jump;

//==============================================================================
public: explicit Component_Jump_To_Byte(Table_MIDI_Message_Log& table);

public: void paint(Graphics& g) override;
private: void jump_to_byte_and_close();
private: void textEditorTextChanged(TextEditor& editor) override;
private: void textEditorReturnKeyPressed(TextEditor& editor) override;
public: ~Component_Jump_To_Byte();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Component_Jump_To_Byte)
};