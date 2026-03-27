#pragma once

#include <JuceHeader.h>

#include "D_000_Tree_Msg_Log.h"
#include "D_010_Tree_Msg_Slots.h"

class Data_Hub
{
private: std::unique_ptr<Tree_Msg_Log> tree_in_log;
private: std::unique_ptr<Tree_Msg_Log> tree_out_log;
private: std::unique_ptr<Tree_Msg_Log> tree_compare;
private: std::unique_ptr<Tree_Msg_Slots> tree_msg_slots;
public: int msg_filter_flags;
private: ApplicationCommandManager command_manager;

//==============================================================================
public: Data_Hub();

public: Tree_Msg_Log* get_tree_in_log();
public: Tree_Msg_Log* get_tree_out_log();
public: Tree_Msg_Log* get_tree_compare();
public: Tree_Msg_Slots* get_tree_msg_slots();
public: ApplicationCommandManager& get_command_manager();
public: ~Data_Hub();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Data_Hub)
};