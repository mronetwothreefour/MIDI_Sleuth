#pragma once

#include <JuceHeader.h>

#include "D_Data_User.h"
#include "G_Table.h"

class Table_Tabs :
	public TabbedComponent,
	public Data_User,
	public ApplicationCommandTarget
{
private: Table tab_in_log;
private: Table tab_out_log;
private: Table tab_compare;

//==============================================================================
public: explicit Table_Tabs(Data_Hub* hub);

public: void clear_visible_table();
public: ApplicationCommandTarget* getNextCommandTarget() override;
public: void getAllCommands(Array<int>& cmd_list) override;
public: void getCommandInfo(int cmd, ApplicationCommandInfo& info) override;
public: bool perform(const InvocationInfo& info) override;

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Table_Tabs)
};
