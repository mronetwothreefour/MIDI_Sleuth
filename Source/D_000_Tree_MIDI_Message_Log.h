#pragma once

#include <JuceHeader.h>

class Tree_MIDI_Message_Log
{
private: std::unique_ptr<ValueTree> tree;

//==============================================================================
public: Tree_MIDI_Message_Log();

private: ValueTree header();
private: ValueTree body();
public: void log_message(const MidiMessage& msg);
public: void add_listener(ValueTree::Listener* listener);
public: void remove_listener(ValueTree::Listener* listener);

public: ~Tree_MIDI_Message_Log();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Tree_MIDI_Message_Log)
};