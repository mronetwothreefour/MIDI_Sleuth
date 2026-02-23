#pragma once

#include <JuceHeader.h>

#include "G_020_Main_Component.h"

struct List_MIDI_Devices final :
	private ListBoxModel,
	public ListBox
{
private: Main_Component* parent;
private: bool for_input_devices;
private: SparseSet<int> last_selected;

//==============================================================================
public: List_MIDI_Devices(const String& name, Main_Component* parent, bool for_input_devices);

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(List_MIDI_Devices)
};
