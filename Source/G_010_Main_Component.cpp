#include "G_010_Main_Component.h"

using namespace XYWH;

Main_Component::Main_Component(Data_Hub* hub) :
    Data_User{ hub },
    devices{ hub },
    msg_slots{ hub, &devices },
    filter_toggles{ hub },
    tabs_message_logs{ hub },
    btn_clear("Clear Log"),
    btn_reset("Reset All")
{
    addAndMakeVisible(devices);

    addAndMakeVisible(msg_slots);

    addAndMakeVisible(filter_toggles);

    addAndMakeVisible(tabs_message_logs);

    btn_clear.onClick = [this] { clear_visible_message_log();  };
    btn_clear.setSize(btn_clear_reset_w, btn_clear_reset_h);
    btn_clear.setTooltip("Clear all messages from\nthe current log.");
    addAndMakeVisible(btn_clear);

    btn_reset.onClick = [this] { devices.stop_and_reset_all();  };
    btn_reset.setSize(btn_clear_reset_w, btn_clear_reset_h);
    btn_reset.setTooltip("Send all notes off to all channels,\nthen stop and reset all devices.");
    addAndMakeVisible(btn_reset);

    addChildComponent(tooltips);
    tooltips.setMillisecondsBeforeTipAppears(2000);

    setSize(main_win_init_w, main_win_init_h);
}

void Main_Component::resized() {
    auto win_w = getWidth();
    auto win_h = getHeight();
    auto components_w = main_win_components_min_w;
    auto can_widen_components = components_w < win_w - 2 * margin;
    if (can_widen_components)
        components_w = win_w - 2 * margin;
    devices.setBounds(margin, margin, components_w, lbl_device_list_h + device_list_h);
    auto flex_x = margin;
    if (can_widen_components)
        flex_x = (win_w - main_win_components_min_w) / 2;
    msg_slots.setBounds(flex_x, msg_slots_y, msg_slots_w, msg_slots_h);
    filter_toggles.setBounds(flex_x, filters_y, filters_w, filters_h);
    auto log_area_h = log_area_min_h;
    auto components_h = main_win_components_min_h;
    if (components_h < win_h - 2 * margin)
        log_area_h += win_h - 2 * margin - components_h;
    tabs_message_logs.setBounds(margin, log_area_y, components_w, log_area_h);
    auto btn_clear_reset_y = log_area_y + log_area_h + 10;
    btn_clear.setTopLeftPosition(margin, btn_clear_reset_y);
    btn_reset.setTopRightPosition(tabs_message_logs.getRight(), btn_clear_reset_y);
}

void Main_Component::clear_visible_message_log() {
    auto tab = tabs_message_logs.getCurrentTabIndex();
    switch(tab) {
    case 0:
        in_log->clear_tree();
        break;
    case 1:
        out_log->clear_tree();
        break;
    case 2:
        compare->clear_tree();
        break;
    default:
        break;
    }
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
       devices.send_stored_message(0);
    }
    return false;
}

