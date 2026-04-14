#pragma once

#include <JuceHeader.h>

#include "D_Data_User.h"
#include "G_Table.h"

class Msg_Slots :
	public Component,
	public Data_User,
	public ChangeListener,
	public ApplicationCommandTarget
{
private: std::unique_ptr<Table> slots[5];
private: TabbedComponent tabs;
private: TextButton btn_transmit;
private: TextButton btn_jump;
private: TextButton btn_copy;
private: TextButton btn_clear;

//==============================================================================
public: explicit Msg_Slots(Data_Hub* hub);

private: void match_btn_color_to_visible_tab();
public: void paint(Graphics& g) override;
public: void resized() override;
public: void clear_visible_slot();
private: void changeListenerCallback(ChangeBroadcaster* source) override;
public: ApplicationCommandTarget* getNextCommandTarget() override;
public: void getAllCommands(Array<int>& cmd_list) override;
public: void getCommandInfo(int cmd, ApplicationCommandInfo& info) override;
public: bool perform(const InvocationInfo& info) override;
public: ~Msg_Slots();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Msg_Slots)
};