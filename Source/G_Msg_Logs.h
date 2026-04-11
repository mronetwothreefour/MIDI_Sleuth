#pragma once

#include <JuceHeader.h>

#include "D_Data_User.h"
#include "G_Table.h"

class Msg_Logs :
	public Component,
	public Data_User,
	public ApplicationCommandTarget
{
private: std::unique_ptr<Table> tab_incoming;
private: std::unique_ptr<Table> tab_outgoing;
private: std::unique_ptr<Table> tab_compare;
private: TabbedComponent tabs;
private: TextButton btn_jump;
private: TextButton btn_clear;

//==============================================================================
public: explicit Msg_Logs(Data_Hub* hub);

public: void paint(Graphics& g) override;
public: void resized() override;
public: void clear_visible_table();
public: void set_next_cmd_target_for_tabs(ApplicationCommandTarget* new_target);
public: ApplicationCommandTarget* getNextCommandTarget() override;
public: void getAllCommands(Array<int>& cmd_list) override;
public: void getCommandInfo(int cmd, ApplicationCommandInfo& info) override;
public: bool perform(const InvocationInfo& info) override;
public: ~Msg_Logs();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Msg_Logs)
};