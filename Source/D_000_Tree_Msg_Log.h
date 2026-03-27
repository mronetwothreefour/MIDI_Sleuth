#pragma once

#include <JuceHeader.h>

#include "C_100_Util_Build_Description.h"
#include "C_110_Util_Convert.h"

class Tree_Msg_Log
{
private: std::unique_ptr<ValueTree> tree;

//==============================================================================
public: Tree_Msg_Log();

public: const int number_of_rows();
public: const int first_byte_col_id();
public: void add_msg(const MidiMessage& msg, String description = "");
public: const int msg_timestamp(const int msg_index);
public: const int msg_length(const int msg_index);
public: const String msg_description(const int msg_index);
public: const String msg_bytes(const int msg_index);
public: void clear_log();
public: void add_listener(ValueTree::Listener* listener);
public: void remove_listener(ValueTree::Listener* listener);
public: ~Tree_Msg_Log();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Tree_Msg_Log)
};
