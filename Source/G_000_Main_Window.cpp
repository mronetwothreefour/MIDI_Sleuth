#include "G_000_Main_Window.h"

Main_Window::Main_Window(String name, Data_Hub* hub) :
    DocumentWindow(name, COLOR::background, DocumentWindow::allButtons)
{
    LookAndFeel::setDefaultLookAndFeel(&look_and_feel);
    setUsingNativeTitleBar(true);
    setResizable(true, false);
    setContentOwned(new Main_Component(hub), true);
    setVisible(true);
}

void Main_Window::closeButtonPressed() {
    JUCEApplication::getInstance()->systemRequestedQuit();
}

Main_Window::~Main_Window() {
    LookAndFeel::setDefaultLookAndFeel(nullptr);
}

