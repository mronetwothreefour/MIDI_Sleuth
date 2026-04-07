#include <JuceHeader.h>

#include "G_Main_Win.h"

class Main_App :
    public juce::JUCEApplication
{
private: std::unique_ptr<Main_Win> win_main;

//==============================================================================
public: Main_App() {}

public: const String getApplicationName() override { return ProjectInfo::projectName; }
public: const String getApplicationVersion() override { return ProjectInfo::versionString; }
public: bool moreThanOneInstanceAllowed() override { return true; }
public: void initialise (const juce::String& /*cmd_line*/) override {
                 win_main.reset (new Main_Win (getApplicationName()));
             }
public: void anotherInstanceStarted(const String& /*cmd_line*/) override {}
public: void systemRequestedQuit() override { quit(); }
public: void shutdown() override { win_main = nullptr; }
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION(Main_App)
