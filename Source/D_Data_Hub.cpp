#include "D_Data_Hub.h"

Data_Hub::Data_Hub() :
    tree_in_log{ new Data_Tree{ Table_Type::log_in } },
    tree_out_log{ new Data_Tree{ Table_Type::log_out } },
    tree_compare{ new Data_Tree{ Table_Type::comparison } },
    msg_filter_flags{ 31 }
{
    for (int slot_index = 0; slot_index < 5; ++slot_index) {
        auto tree_type = (Table_Type)(msg_slot_1 + slot_index);
        trees_msg_slot[slot_index].reset(new Data_Tree{ tree_type });
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
    tree_in_log = nullptr;
    tree_out_log = nullptr;
    tree_compare = nullptr;
    for (int slot_index = 0; slot_index < 5; ++slot_index) {
        trees_msg_slot[slot_index] = nullptr;
    }
}
