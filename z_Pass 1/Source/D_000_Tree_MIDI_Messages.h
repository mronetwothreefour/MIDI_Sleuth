#pragma once

#include <JuceHeader.h>

class Tree_MIDI_Messages
{
private: std::unique_ptr<ValueTree> tree;

//==============================================================================
public: Tree_MIDI_Messages();

public: const int number_of_rows();
public: void log_message(const MidiMessage& msg);
public: const int entry_timestamp(const int entry_index);
public: const String entry_bytes(const int entry_index);
public: const int entry_length(const int entry_index);
public: const String entry_description(const int entry_index);
public: void clear_tree();
public: void add_listener(ValueTree::Listener* listener);
public: void remove_listener(ValueTree::Listener* listener);

public: ~Tree_MIDI_Messages();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Tree_MIDI_Messages)
};