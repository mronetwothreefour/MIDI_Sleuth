#pragma once

#include <JuceHeader.h>

#include "G_500_Table_Message_Log.h"

class Tree_MIDI_Messages;

class Tabbed_Component_In_Out_Logs :
	public TabbedComponent
{
private: Table_Message_Log tab_in_log;
private: Table_Message_Log tab_out_log;

//==============================================================================
public: explicit Tabbed_Component_In_Out_Logs(Tree_MIDI_Messages& in_log, Tree_MIDI_Messages& out_log);

public: void scroll_to_row(const bool scrolling_in_log, const int row_num);
public: const String get_bytes_for_selected_row_in_current_tab();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Tabbed_Component_In_Out_Logs)
};