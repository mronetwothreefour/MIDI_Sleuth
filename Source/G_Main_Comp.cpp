#include "G_Main_Comp.h"

using namespace XYWH;

Main_Comp::Main_Comp(Data_Hub* hub) :
    Data_User{ hub },
    midi_handler{ hub },
    msg_filters{ hub },
    msg_logs{ hub }
{
    midi_handler.set_next_cmd_target(&msg_logs);
    addAndMakeVisible(midi_handler);

    addAndMakeVisible(msg_filters);

    // TODO: msg_logs.set_next_cmd_target_for_tabs();
    addAndMakeVisible(msg_logs);

    addChildComponent(tooltips);
    tooltips.setMillisecondsBeforeTipAppears(2000);

    cmd_mngr.setFirstCommandTarget(&midi_handler);

    setSize(win_main_init_w, win_main_init_h);

    Timer::callAfterDelay(100, [this] { grabKeyboardFocus(); });
}

void Main_Comp::resized() {
    midi_handler.setBounds(devices);
    msg_filters.setBounds(filters);
    auto tables_w = win_main_tables_min_w;
    auto available_w = getWidth() - 2 * win_inset;
    if (tables_w < available_w)
        tables_w = available_w;
    auto logs_h = logs_min_h;
    auto all_comp_h = win_main_comp_min_h;
    auto available_comp_h = getHeight() - 2 * win_inset;
    if (all_comp_h < available_comp_h)
        logs_h += available_comp_h - all_comp_h;
    msg_logs.setBounds(win_inset, logs_y, tables_w, logs_h);
}

Main_Comp::~Main_Comp() {
    cmd_mngr.setFirstCommandTarget(nullptr);
}
