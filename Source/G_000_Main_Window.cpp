#include "G_000_Main_Window.h"

Main_Window::Main_Window(String name) :
    DocumentWindow(name, Colours::black, DocumentWindow::allButtons)
{
    setUsingNativeTitleBar(true);
    setContentOwned(new Main_Component(), true);
    setVisible(true);
}

void Main_Window::closeButtonPressed() {
    JUCEApplication::getInstance()->systemRequestedQuit();
}

