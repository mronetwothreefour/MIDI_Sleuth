#pragma once

#include <JuceHeader.h>

#include "D_000_Tree_MIDI_Messages.h"
#include "D_100_Data_User.h"
#include "G_020_Component_MIDI_Devices.h"
#include "G_030_Component_MIDI_Message_Slots.h"
#include "G_050_Component_Filter_Toggles.h"
#include "G_060_Tabbed_Component_Tables.h"

class Main_Component final :
    public Component,
    public Data_User,
    public ApplicationCommandTarget
{
private: Component_MIDI_Devices devices;
private: Component_MIDI_Message_Slots msg_slots;
private: Component_Filter_Toggles filter_toggles;
private: Tabbed_Component_Tables tabs_message_logs;
private: TextButton btn_clear;
private: TextButton btn_reset;
private: TooltipWindow tooltips;

//==============================================================================
public: explicit Main_Component(Data_Hub* hub);

public: void resized() override;
private: void clear_visible_message_log();
public: bool keyPressed(const KeyPress& key) override;
public: ApplicationCommandTarget* getNextCommandTarget() override;
public: void getAllCommands(Array<int>& cmd_list) override;
public: void getCommandInfo(int cmd, ApplicationCommandInfo& info) override;
public: bool perform(const InvocationInfo& info) override;
public: ~Main_Component();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Main_Component)
};
