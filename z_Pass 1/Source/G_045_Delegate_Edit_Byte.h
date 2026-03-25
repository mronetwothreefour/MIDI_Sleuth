#pragma once

#include <JuceHeader.h>

#include "D_100_Data_User.h"

class Delegate_Edit_Byte :
	public Label,
	public Data_User
{
private: const int slot_index, byte_index;
private: String current_txt;

//==============================================================================
public: Delegate_Edit_Byte(const int slot_index, const int col_ID, Data_Hub* hub);

public: void paint(Graphics& g) override;
public: void textWasEdited() override;

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Delegate_Edit_Byte)
};