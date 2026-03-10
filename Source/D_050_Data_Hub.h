#pragma once

#include <JuceHeader.h>

#include "D_000_Tree_MIDI_Messages.h"

class Data_Hub
{
private: std::unique_ptr<Tree_MIDI_Messages> tree_in_log;
private: std::unique_ptr<Tree_MIDI_Messages> tree_out_log;
private: std::unique_ptr<Tree_MIDI_Messages> tree_compare;
private: StringArray message_slots;
public: int msg_type_flags;

//==============================================================================
public: Data_Hub();

public: Tree_MIDI_Messages* get_tree_in_log();
public: Tree_MIDI_Messages* get_tree_out_log();
public: Tree_MIDI_Messages* get_tree_compare();
public: StringArray& get_message_slots();
public: ~Data_Hub();
	  
//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Data_Hub)
};