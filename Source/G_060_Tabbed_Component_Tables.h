#pragma once

#include <JuceHeader.h>

#include "D_100_Data_User.h"
#include "G_070_Table_MIDI_Message_Log.h"

class Tree_MIDI_Messages;

class Tabbed_Component_Tables :
	public TabbedComponent,
	public Data_User,
	public ApplicationCommandTarget
{
private: Table_MIDI_Message_Log tab_in_log;
private: Table_MIDI_Message_Log tab_out_log;

//==============================================================================
public: explicit Tabbed_Component_Tables(Data_Hub* hub);

public: void scroll_to_row(const bool scrolling_in_log, const int row_num);
public: const String get_bytes_for_selected_row_in_current_tab();
public: ApplicationCommandTarget* getNextCommandTarget() override;
public: void getAllCommands(Array<int>& cmd_list) override;
public: void getCommandInfo(int cmd, ApplicationCommandInfo& info) override;
public: bool perform(const InvocationInfo& info) override;

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Tabbed_Component_Tables)
};