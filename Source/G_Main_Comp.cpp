#include "G_Main_Comp.h"

using namespace XYWH;

Main_Comp::Main_Comp(Data_Hub* hub) :
    Data_User{ hub },
    devices{ hub }
{
    addAndMakeVisible(devices);

    addChildComponent(tooltips);
    tooltips.setMillisecondsBeforeTipAppears(2000);

    setSize(win_main_init_w, win_main_init_h);

    Timer::callAfterDelay(100, [this] { grabKeyboardFocus(); });
}

void Main_Comp::resized() {
    auto win_w = getWidth();
    auto win_h = getHeight();
    auto components_w = win_main_comp_min_w;
    auto can_widen_components = components_w < win_w - 2 * win_main_comp_inset;
    if (can_widen_components)
        components_w = win_w - 2 * win_main_comp_inset;
    devices.setBounds(win_main_comp_inset, win_main_comp_inset, 
                      components_w, lbl_lbox_devices_h + lbox_devices_h);
}

Main_Comp::~Main_Comp() {
}
