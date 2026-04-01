#pragma once

#include <JuceHeader.h>

#include "G_Msg_Slot_Edit_Comp.h"

class Msg_Slot_Edit_Win :
	public DocumentWindow
{
//==============================================================================
public: Msg_Slot_Edit_Win(const Table_Type table_type, Data_Hub* hub) :
			DocumentWindow{ "Edit message in slot " + String{ table_type - msg_slot_1 + 1 }, COLOR::bkgrnd, closeButton }
		{
			setUsingNativeTitleBar(true);
			setResizable(false, false);
			setContentOwned(new Msg_Slot_Edit_Comp{ table_type, hub }, false);
			setSize(XYWH::win_edit_msg_w, XYWH::win_edit_msg_h);
		}

public: bool keyPressed(const KeyPress& key) override {
	if (key == KeyPress::escapeKey) {
		closeButtonPressed();
		return true;
	}
	return false;
}
public: void closeButtonPressed() override { setVisible(false); }

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Msg_Slot_Edit_Win)
};
