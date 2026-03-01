#pragma once

#include <JuceHeader.h>

struct Build_Message_Description
{
private: static const String channel(const String& msg);
private: static const String key(const String& msg);
private: static const String value(const String& msg, const int byte_num);

public: static const String note_off(const String& msg);
public: static const String note_on(const String& msg);
public: static const String key_aftertouch(const String& msg);
public: static const String control_change(const String& msg);
public: static const String program_change(const String& msg);
public: static const String channel_aftertouch(const String& msg);
public: static const String pitch_bend(const String& msg);
};