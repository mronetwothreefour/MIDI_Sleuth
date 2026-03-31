#pragma once

#include <JuceHeader.h>

#include "D_Data_User.h"
#include "G_MIDI_Handler.h"
#include "G_Msg_Filters.h"
#include "G_Table_Tabs.h"

class Main_Comp :
    public Component,
    public Data_User,
    public ApplicationCommandTarget
{
private: MIDI_Handler devices;
private: Msg_Filters filters;
private: Table_Tabs table_tabs;
private: TextButton btn_clear;
private: TextButton btn_reset;
private: TooltipWindow tooltips;

//==============================================================================
public: explicit Main_Comp(Data_Hub* hub);

public: void resized() override;
public: ApplicationCommandTarget* getNextCommandTarget() override;
public: void getAllCommands(Array<int>& cmd_list) override;
public: void getCommandInfo(int cmd, ApplicationCommandInfo& info) override;
public: bool perform(const InvocationInfo& info) override;
public: ~Main_Comp() override;

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Main_Comp)
};
