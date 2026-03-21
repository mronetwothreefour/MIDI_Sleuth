#pragma once

#include <JuceHeader.h>

#include "G_040_Component_Edit_MIDI_Message.h"

class Window_Edit_MIDI_Message :
	public DocumentWindow
{
//==============================================================================
public: Window_Edit_MIDI_Message(const int slot_index, Data_Hub* hub) :
			DocumentWindow{ "Edit message in slot " + String{ slot_index + 1 }, COLOR::background, closeButton }
		{
			setUsingNativeTitleBar(true);
			setResizable(false, false);
			setContentOwned(new Component_Edit_MIDI_Message{ slot_index, hub }, false);
		}

public: bool keyPressed(const KeyPress& key) override {
	if (key == KeyPress::escapeKey) {
		closeButtonPressed();
		return true;
	}
	return false;
}
public: void closeButtonPressed() override { delete this; }
public: ~Window_Edit_MIDI_Message() { setLookAndFeel(nullptr); }

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Window_Edit_MIDI_Message)
};
