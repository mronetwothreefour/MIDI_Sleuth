#pragma once

#include <JuceHeader.h>

#include "D_000_Tree_MIDI_Messages.h"
#include "D_100_Data_User.h"
#include "G_020_Component_MIDI_Handler.h"
#include "G_400_Tabbed_Component_In_Out_Logs.h"

class Main_Component final :
    public Component,
    public Data_User
{
private: Component_MIDI_Handler handler;
private: Label lbl_msg_slot_1;
private: Label lbl_msg_log;
private: TextButton btn_edit_slot_1;
private: TextButton btn_transmit_slot_1;
private: Tabbed_Component_In_Out_Logs tabs_message_logs;
private: TooltipWindow tooltips;

//==============================================================================
public: explicit Main_Component(Data_Hub* hub);

private: void add_label_and_set_style(Label& label);
public: void resized() override;
public: bool keyPressed(const KeyPress& key) override;

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Main_Component)
};
