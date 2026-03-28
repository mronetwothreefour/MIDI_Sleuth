#include "D_Data_Hub.h"

Data_Hub::Data_Hub() :
    tree_in_log{ new Tree_Msg_Log{} },
    tree_out_log{ new Tree_Msg_Log{} },
    tree_compare{ new Tree_Msg_Log{} },
    tree_msg_slots{ new Tree_Msg_Slots{} },
    msg_filter_flags{ 31 }
{}

Tree_Msg_Log* Data_Hub::get_tree_in_log() {
    return tree_in_log.get();
}

Tree_Msg_Log* Data_Hub::get_tree_out_log() {
    return tree_out_log.get();
}

Tree_Msg_Log* Data_Hub::get_tree_compare() {
    return tree_compare.get();
}

Tree_Msg_Slots* Data_Hub::get_tree_msg_slots() {
    return tree_msg_slots.get();
}

ApplicationCommandManager& Data_Hub::get_command_manager() {
    return command_manager;
}

Data_Hub::~Data_Hub() {
    tree_in_log = nullptr;
    tree_out_log = nullptr;
    tree_compare = nullptr;
    tree_msg_slots = nullptr;
}
