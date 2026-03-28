#include <JuceHeader.h>

#include "G_010_Win_Main.h"

class Main_App :
    public JUCEApplication
{
private: std::unique_ptr<Data_Hub> hub;
private: std::unique_ptr<Win_Main> win_main;

//==============================================================================
public: Main_App() {}

public: const String getApplicationName() override { return ProjectInfo::projectName; }
public: const String getApplicationVersion() override { return ProjectInfo::versionString; }
public: bool moreThanOneInstanceAllowed() override { return true; }
public: void initialise(const String& /*cmd_line*/) override { 
                 hub.reset(new Data_Hub{});
                 win_main.reset(new Win_Main{ getApplicationName(), hub.get() });
             }
public: void shutdown() override { win_main = nullptr; }
public: void systemRequestedQuit() override { quit(); }
public: void anotherInstanceStarted(const String& /*cmd_line*/) override {}

public: ~Main_App() {
            win_main = nullptr;
            hub = nullptr;
        }
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION(Main_App)
