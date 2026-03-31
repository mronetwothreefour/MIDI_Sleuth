#pragma once

#include <JuceHeader.h>

class Tree_Msg_Slots
{
private: std::unique_ptr<ValueTree> tree;

//==============================================================================
public: Tree_Msg_Slots();

public: String msg_in_slot(const int slot_index);
public: String msg_in_slot_byte(const int slot_index, const int byte_index);
public: void set_msg_in_slot(String& new_msg, const int slot_index);
public: void set_msg_in_slot_byte(String& new_byte, const int slot_index, const int byte_index);
public: String description_in_slot(const int slot_index);
public: void set_description_in_slot(String& description, const int slot_index);
public: void add_listener_to_slot(ValueTree::Listener* listener, const int slot_index);
public: void remove_listener_from_slot(ValueTree::Listener* listener, const int slot_index);
public: ~Tree_Msg_Slots();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Tree_Msg_Slots)
};