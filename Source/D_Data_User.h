#pragma once

#include <JuceHeader.h>

#include "C_ENUM.h"
#include "C_GUI_XYWH.h"
#include "C_GUI_COLOR.h"
#include "C_GUI_FONT.h"
#include "D_Data_Hub.h"

using namespace ENUM;

class Data_User
{
protected: Data_Hub* hub;
protected: Tree_Msg_Log* in_log;
protected: Tree_Msg_Log* out_log;
protected: Tree_Msg_Log* compare;
protected: Tree_Msg_Slots* slots;
protected: ApplicationCommandManager& cmd_mngr;

//==============================================================================
public: explicit Data_User(Data_Hub* hub);

protected: bool should_be_logged(Message_Type msg_type);
protected: void set_should_be_logged(Message_Type msg_type, bool should_log);

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Data_User)
};
