#include "D_Data_Hub.h"

Data_Hub::Data_Hub() :
    tree_in_log{ new Data_Tree{ Table_Type::log_in } },
    tree_out_log{ new Data_Tree{ Table_Type::log_out } },
    tree_compare{ new Data_Tree{ Table_Type::comparison } },
    msg_filter_flags{ 0 }
{
    PropertiesFile::Options o;
    o.applicationName = ProjectInfo::projectName;
    o.filenameSuffix = ".settings";

    app_properties.reset(new ApplicationProperties());
    app_properties->setStorageParameters(o);

    auto settings = app_properties->getUserSettings();
    msg_filter_flags = settings->getIntValue("msg_filter_flags", 31);

    for (int slot_index = 0; slot_index < 5; ++slot_index) {
        auto tree_type = (Table_Type)(msg_slot_1 + slot_index);
        trees_msg_slot[slot_index].reset(new Data_Tree{ tree_type });
        String slot_name{ "msg_slot_" +  String{ slot_index + 1 } };
        trees_msg_slot[slot_index]->set_msg_bytes(settings->getValue(slot_name + "_bytes", ""));
        trees_msg_slot[slot_index]->set_msg_description(settings->getValue(slot_name + "_description", ""));
    }

}

Data_Tree* Data_Hub::get_tree_in_log() {
    return tree_in_log.get();
}

Data_Tree* Data_Hub::get_tree_out_log() {
    return tree_out_log.get();
}

Data_Tree* Data_Hub::get_tree_compare() {
    return tree_compare.get();
}

Data_Tree* Data_Hub::get_tree_msg_slot(const int slot_index) {
    if (slot_index > -1 && slot_index < 5)
        return trees_msg_slot[slot_index].get();
    return nullptr;
}

ApplicationCommandManager& Data_Hub::get_command_manager() {
    return command_manager;
}

Data_Hub::~Data_Hub() {
    auto settings = app_properties->getUserSettings();
    settings->setValue("msg_filter_flags", msg_filter_flags);

    tree_in_log = nullptr;
    tree_out_log = nullptr;
    tree_compare = nullptr;
    for (int slot_index = 0; slot_index < 5; ++slot_index) {
        auto slot_tree = trees_msg_slot[slot_index].get();
        String slot_name{ "msg_slot_" + String{ slot_index + 1 } };
        settings->setValue(slot_name + "_bytes", slot_tree->msg_bytes());
        settings->setValue(slot_name + "_description", slot_tree->msg_description());
        trees_msg_slot[slot_index] = nullptr;
    }
    app_properties = nullptr;
}
