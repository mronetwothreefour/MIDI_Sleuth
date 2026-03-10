#pragma once

#include <JuceHeader.h>

#include "D_000_Tree_MIDI_Messages.h"
#include "D_100_Data_User.h"
#include "G_020_Component_MIDI_Devices.h"
#include "G_050_Component_Filter_Toggles.h"
#include "G_060_Tabbed_Component_Tables.h"

class Main_Component final :
    public Component,
    public Data_User
{
private: Component_MIDI_Devices devices;
private: TextButton btn_edit_slot_1;
private: TextButton btn_transmit_slot_1;
private: Component_Filter_Toggles filter_toggles;
private: Tabbed_Component_Tables tabs_message_logs;
private: TooltipWindow tooltips;

//==============================================================================
public: explicit Main_Component(Data_Hub* hub);

public: void resized() override;
public: bool keyPressed(const KeyPress& key) override;

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Main_Component)
};
