#pragma once

#include <JuceHeader.h>

#include "D_Data_Tree.h"

class Data_Hub
{
private: std::unique_ptr<Data_Tree> tree_in_log;
private: std::unique_ptr<Data_Tree> tree_out_log;
private: std::unique_ptr<Data_Tree> tree_compare;
private: std::unique_ptr<Data_Tree> trees_msg_slot[5];
public: int msg_filter_flags;
private: ApplicationCommandManager command_manager;

//==============================================================================
public: Data_Hub();

public: Data_Tree* get_tree_in_log();
public: Data_Tree* get_tree_out_log();
public: Data_Tree* get_tree_compare();
public: Data_Tree* get_tree_msg_slot(const int slot_index);
public: ApplicationCommandManager& get_command_manager();
public: ~Data_Hub();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Data_Hub)
};