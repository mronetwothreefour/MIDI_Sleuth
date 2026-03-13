#pragma once

#include <JuceHeader.h>

#include "C_000_GUI_Constants.h"
#include "C_010_Enums.h"
#include "D_050_Data_Hub.h"

using namespace ENUM;

class Data_User
{
protected: Data_Hub* hub;
protected: Tree_MIDI_Messages* in_log;
protected: Tree_MIDI_Messages* out_log;
protected: Tree_MIDI_Messages* compare;

//==============================================================================
public: explicit Data_User(Data_Hub* hub);

protected: const String& message_in_slot(const int slot_index);
protected: void set_message_in_slot(const String& msg, const int slot_index);
protected: bool should_log(Message_Type msg_type);
protected: void set_should_log(Message_Type msg_type, bool should_log);

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Data_User)
};