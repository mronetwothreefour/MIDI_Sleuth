#include "G_Main_Comp.h"

using namespace XYWH;

Main_Comp::Main_Comp(Data_Hub* hub) :
    Data_User{ hub },
    devices{ hub },
    filters{ hub },
    table_tabs{ hub },
    btn_clear("Clear Log"),
    btn_reset("Reset All")
{
    addAndMakeVisible(devices);

    addAndMakeVisible(filters);

    addAndMakeVisible(table_tabs);

    btn_clear.onClick = [this] { table_tabs.clear_visible_table();  };
    btn_clear.setSize(btn_clear_reset_w, btn_h);
    btn_clear.setTooltip("Clear all messages in\nthe current tab.");
    addAndMakeVisible(btn_clear);

    btn_reset.onClick = [this] { devices.stop_and_reset_all();  };
    btn_reset.setSize(btn_clear_reset_w, btn_h);
    btn_reset.setTooltip("Send all notes off to all channels,\nthen stop and reset all devices.");
    addAndMakeVisible(btn_reset);

    cmd_mngr.registerAllCommandsForTarget(this);
    cmd_mngr.setFirstCommandTarget(&table_tabs);
    addKeyListener(cmd_mngr.getKeyMappings());

    addChildComponent(tooltips);
    tooltips.setMillisecondsBeforeTipAppears(2000);

    setSize(win_main_init_w, win_main_init_h);

    Timer::callAfterDelay(100, [this] { grabKeyboardFocus(); });
}

void Main_Comp::resized() {
    auto win_w = getWidth();
    auto win_h = getHeight();
    auto all_comp_w = win_main_comp_min_w;
    auto can_widen_comps = false;
    auto available_comp_w = win_w - 2 * win_main_inset;
    if (all_comp_w < available_comp_w) {
        all_comp_w = available_comp_w;
        can_widen_comps = true;
    }
    devices.setBounds(win_main_inset, win_main_inset, 
                      all_comp_w, lbl_lbox_devices_h + lbox_devices_h);
    auto flex_x = win_main_inset;
    if (can_widen_comps)
        flex_x = (win_w - win_main_comp_min_w) / 2;
    filters.setBounds(flex_x, filters_y, filters_w, filters_h);
    auto tables_h = tables_min_h;
    auto all_comp_h = win_main_comp_min_h;
    auto available_comp_h = win_h - 2 * win_main_inset;
    if (all_comp_h < available_comp_h)
        tables_h += available_comp_h - all_comp_h;
    table_tabs.setBounds(win_main_inset, tables_y, all_comp_w, tables_h);
    auto btn_clear_reset_y = tables_y + tables_h + 10;
    btn_clear.setTopLeftPosition(win_main_inset, btn_clear_reset_y);
    btn_reset.setTopRightPosition(table_tabs.getRight(), btn_clear_reset_y);
}

ApplicationCommandTarget* Main_Comp::getNextCommandTarget() {
    return nullptr;
}

void Main_Comp::getAllCommands(Array<int>& /*cmd_list*/) {}

void Main_Comp::getCommandInfo(int /*cmd*/, ApplicationCommandInfo& /*info*/) {}

bool Main_Comp::perform(const InvocationInfo& /*info*/) {
    return false;
}

Main_Comp::~Main_Comp() {
    removeKeyListener(cmd_mngr.getKeyMappings());
    cmd_mngr.setFirstCommandTarget(nullptr);
}
