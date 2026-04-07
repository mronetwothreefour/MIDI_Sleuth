#pragma once

#include <JuceHeader.h>

#include "G_Table.h"

class Jump_To_Byte_Dialog :
	public Component,
	public TextEditor::Listener
{
private: Table* table;
private: TextEditor edit_byte;
private: TextButton btn_cancel;
private: TextButton btn_jump;

//==============================================================================
public: explicit Jump_To_Byte_Dialog(Table* table);

public: void paint(Graphics& g) override;
private: void jump_to_byte_and_close();
private: void textEditorTextChanged(TextEditor& editor) override;
private: void textEditorReturnKeyPressed(TextEditor& editor) override;
public: ~Jump_To_Byte_Dialog();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Jump_To_Byte_Dialog)
};