#include "G_2_Comp_Main.h"

using namespace XYWH;

Comp_Main::Comp_Main(Data_Hub* hub) :
    Data_User{ hub }
{
    addChildComponent(tooltips);
    tooltips.setMillisecondsBeforeTipAppears(2000);

    setSize(win_main_init_w, win_main_init_h);

    Timer::callAfterDelay(100, [this] { grabKeyboardFocus(); });
}

void Comp_Main::resized() {
}

Comp_Main::~Comp_Main() {
}
