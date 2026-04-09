#pragma once

#include <JuceHeader.h>

#include "C_ENUM.h"
#include "C_Util_Build_Description.h"
#include "C_Util_Convert.h"

using namespace ENUM;

class Data_Tree
{
public: const Table_Type table_type;
private: std::unique_ptr<ValueTree> tree;

//==============================================================================
public: explicit Data_Tree(const Table_Type table_type);

public: const int row_count();
public: const int non_byte_col_count() const;
public: const int first_byte_col_id() const;
public: void add_msg(const MidiMessage& msg, String description = "");
public: const int msg_timestamp(const int msg_index);
public: const int msg_length(const int msg_index);
public: const String msg_description(const int msg_index = 0);
public: void set_msg_description(const String& new_description);
public: const String msg_bytes(const int msg_index = 0);
public: void set_msg_bytes(const String& new_bytes);
public: const String single_byte_in_msg(const int byte_index, const int msg_index = 0);
public: void set_single_byte_in_msg(const String& new_byte, const int byte_index);
public: void clear_table();
public: void add_listener(ValueTree::Listener* listener);
public: void remove_listener(ValueTree::Listener* listener);
public: ~Data_Tree();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Data_Tree)
};
