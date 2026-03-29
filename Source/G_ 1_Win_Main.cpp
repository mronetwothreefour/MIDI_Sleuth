#include "G_ 1_Win_Main.h"

Win_Main::Win_Main(String name, Data_Hub* hub) :
    DocumentWindow(name, COLOR::bkgrnd, DocumentWindow::allButtons)
{
    LookAndFeel::setDefaultLookAndFeel(&l_a_f);
    setUsingNativeTitleBar(true);
    setResizable(true, false);
    setContentOwned(new Comp_Main{ hub }, true);
    setVisible(true);
}

void Win_Main::closeButtonPressed() {
    JUCEApplication::getInstance()->systemRequestedQuit();
}

Win_Main::~Win_Main() {
    LookAndFeel::setDefaultLookAndFeel(nullptr);
}
