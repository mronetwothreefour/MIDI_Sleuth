#include "G_010_Main_Component.h"

Main_Component::Main_Component(Data_Hub* hub) :
    Data_User{ hub },
    devices{ hub },
    filter_toggles{ hub },
    tabs_message_logs{ hub }
{
    addAndMakeVisible(devices);

    addAndMakeVisible(filter_toggles);

    addAndMakeVisible(tabs_message_logs);

    addChildComponent(tooltips);
    tooltips.setMillisecondsBeforeTipAppears(2000);

    setSize(XYWH::main_win_init_w, XYWH::main_win_init_h);
}

void Main_Component::resized() {
    auto w = getWidth();
    auto h = getHeight();
    auto subcomponent_w = 2 * XYWH::device_list_min_w + XYWH::margin;
    if (w > subcomponent_w + 2 * XYWH::margin)
        subcomponent_w = w - 2 * XYWH::margin;
    devices.setBounds(XYWH::margin, XYWH::margin, subcomponent_w, XYWH::lbl_device_list_h + XYWH::device_list_h);
    filter_toggles.setBounds(XYWH::margin, XYWH::filters_y, XYWH::filters_w, XYWH::filters_h);
    auto log_area_h = XYWH::log_area_min_h;
    if (h > 6 * XYWH::margin + XYWH::device_list_h + XYWH::msg_slots_h + XYWH::filters_h + XYWH::log_area_min_h)
        log_area_h = h - 6 * XYWH::margin - XYWH::device_list_h - XYWH::msg_slots_h - XYWH::filters_h;
    tabs_message_logs.setBounds(XYWH::margin, XYWH::log_area_y, subcomponent_w, log_area_h);
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

