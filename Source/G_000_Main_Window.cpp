#include "G_000_Main_Window.h"

Main_Window::Main_Window(String name) :
    DocumentWindow(name, Colour{ 0xff202020 }, DocumentWindow::allButtons)
{
    setUsingNativeTitleBar(true);
    setContentOwned(new Main_Component(), true);
    setVisible(true);
}

void Main_Window::closeButtonPressed() {
    JUCEApplication::getInstance()->systemRequestedQuit();
}

