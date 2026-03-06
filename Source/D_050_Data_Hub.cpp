#include "D_050_Data_Hub.h"

Data_Hub::Data_Hub() :
    tree_in_log{ new Tree_MIDI_Messages{} },
    tree_out_log{ new Tree_MIDI_Messages{} },
    tree_compare{ new Tree_MIDI_Messages{} }
{
    for (int i = 0; i < 5; ++i)
        message_slots.add("");
}

Tree_MIDI_Messages* Data_Hub::get_tree_in_log() {
    return tree_in_log.get();
}

Tree_MIDI_Messages* Data_Hub::get_tree_out_log() {
    return tree_out_log.get();
}

Tree_MIDI_Messages* Data_Hub::get_tree_compare() {
    return tree_compare.get();
}

StringArray& Data_Hub::get_message_slots() {
    return message_slots;
}

Data_Hub::~Data_Hub() {
    tree_in_log = nullptr;
    tree_out_log = nullptr;
    tree_compare = nullptr;
}
