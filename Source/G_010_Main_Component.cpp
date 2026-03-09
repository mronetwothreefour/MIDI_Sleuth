#include "G_010_Main_Component.h"

Main_Component::Main_Component(Data_Hub* hub) :
    Data_User{ hub },
    devices{ hub },
    tabs_message_logs{ hub }
{
    addAndMakeVisible(devices);

    addAndMakeVisible(tabs_message_logs);

    addChildComponent(tooltips);
    tooltips.setMillisecondsBeforeTipAppears(2000);

    setSize(XYWH::main_win_init_w, XYWH::main_win_init_h);
}

void Main_Component::resized() {
    auto w = getWidth();
    auto h = getHeight();
    auto devices_w = 2 * XYWH::device_list_min_w + XYWH::margin;
    if (w > devices_w + 2 * XYWH::margin)
        devices_w = w - 2 * XYWH::margin;
    devices.setBounds(XYWH::margin, XYWH::margin, devices_w, XYWH::lbl_device_list_h + XYWH::device_list_h);
    auto gap = 20;
    auto keyboard_w = w - (2 * gap);
    auto monitor_y = (h / 4) + ((2 * 24) + (3 * gap) + 64);
    tabs_message_logs.setBounds(gap, monitor_y, keyboard_w, h - monitor_y - gap);
}

bool Main_Component::keyPressed(const KeyPress& key) {
    if (key == KeyPress{ 'i', ModifierKeys::altModifier, 0 })
        tabs_message_logs.setCurrentTabIndex(0);
    if (key == KeyPress{ 'o', ModifierKeys::altModifier, 0 })
        tabs_message_logs.setCurrentTabIndex(1);
    if (key == KeyPress{ '1', ModifierKeys::ctrlModifier, 0 }) {
        auto msg_bytes = tabs_message_logs.get_bytes_for_selected_row_in_current_tab();
        set_message_in_slot(msg_bytes, 0);
    }
    if (key == KeyPress{ '1', ModifierKeys::altModifier, 0 }) {
       devices.transmit_stored_message(0);
    }
    return false;
}

