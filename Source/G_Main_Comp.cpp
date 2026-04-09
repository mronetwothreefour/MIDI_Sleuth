#include "G_Main_Comp.h"

using namespace XYWH;

Main_Comp::Main_Comp(Data_Hub* hub) :
    Data_User{ hub },
    midi_handler{ hub }
{
    //TODO: midi_handler.set_next_cmd_target();
    addAndMakeVisible(midi_handler);

    addChildComponent(tooltips);
    tooltips.setMillisecondsBeforeTipAppears(2000);

    cmd_mngr.setFirstCommandTarget(&midi_handler);

    setSize(win_main_init_w, win_main_init_h);

    Timer::callAfterDelay(100, [this] { grabKeyboardFocus(); });
}

void Main_Comp::resized() {
    midi_handler.setBounds(devices);
}

Main_Comp::~Main_Comp() {
    cmd_mngr.setFirstCommandTarget(nullptr);
}
