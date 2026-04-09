#include "G_Main_Win.h"

Main_Win::Main_Win(String name, Data_Hub* hub) :
    DocumentWindow(name, COLOR::bkgrnd, DocumentWindow::allButtons)
{
    LookAndFeel::setDefaultLookAndFeel(&l_a_f);
    setUsingNativeTitleBar(true);
    setResizable(true, false);
    setContentOwned(new Main_Comp{ hub }, true);
    setVisible(true);
}

void Main_Win::closeButtonPressed() {
    JUCEApplication::getInstance()->systemRequestedQuit();
}

Main_Win::~Main_Win() {
    LookAndFeel::setDefaultLookAndFeel(nullptr);
}
