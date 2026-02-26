#pragma once

#include <JuceHeader.h>

class Tree_MIDI_Message_Log
{
private: std::unique_ptr<ValueTree> tree;

//==============================================================================
public: Tree_MIDI_Message_Log();

private: ValueTree header();
private: ValueTree body();
private: ValueTree row(int index);
private: ValueTree row(const String& id);
private: void add_data_byte_column();
public: const String log_message(const MidiMessage& msg);
public: const String cell_value(const String& row_id, const String& col_name);
public: void add_listener(ValueTree::Listener* listener);
public: void remove_listener(ValueTree::Listener* listener);

public: ~Tree_MIDI_Message_Log();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Tree_MIDI_Message_Log)
};