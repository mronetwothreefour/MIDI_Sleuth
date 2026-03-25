#include <JuceHeader.h>

#include "G_000_Main_Window.h"

class Main_Application :
    public JUCEApplication
{
private: std::unique_ptr<Data_Hub> hub;
private: std::unique_ptr<Main_Window> main_win;

//==============================================================================
public: Main_Application() {}

public: const String getApplicationName() override { return ProjectInfo::projectName; }
public: const String getApplicationVersion() override { return ProjectInfo::versionString; }
public: bool moreThanOneInstanceAllowed() override { return true; }
public: void initialise(const String& /*cmd_line*/) override { 
                 hub.reset(new Data_Hub{});
                 main_win.reset(new Main_Window{ getApplicationName(), hub.get() });
             }
public: void shutdown() override { main_win = nullptr; }
public: void systemRequestedQuit() override { quit(); }
public: void anotherInstanceStarted(const String& /*cmd_line*/) override {}

public: ~Main_Application() {
            main_win = nullptr;
            hub = nullptr;
        }
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION(Main_Application)
