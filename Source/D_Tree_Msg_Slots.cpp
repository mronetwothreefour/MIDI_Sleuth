#include "D_Tree_Msg_Slots.h"

Tree_Msg_Slots::Tree_Msg_Slots() :
	tree{ new ValueTree{ "MIDI Message Slots" } }
{
	for (int slot_index = 0; slot_index < 5; ++slot_index) {
		ValueTree slot{ "Slot " + String{ slot_index} };
		slot.setProperty("Message", "", nullptr);
		slot.setProperty("Description", "", nullptr);
		tree->addChild(slot, -1, nullptr);
	}
}

String Tree_Msg_Slots::msg_in_slot(const int slot_index) {
	auto slot = tree->getChildWithName("Slot " + String{ slot_index });
	return slot.getProperty("Message").toString();
}

String Tree_Msg_Slots::msg_in_slot_byte(const int slot_index, const int byte_index) {
	return msg_in_slot(slot_index).substring(byte_index, byte_index + 2);
}

void Tree_Msg_Slots::set_msg_in_slot(String& new_msg, const int slot_index) {
	new_msg = new_msg.removeCharacters(" ,\t\n\r");
	new_msg = new_msg.toLowerCase();
	if (new_msg.containsOnly("0123456789abcdef")) {
		auto slot = tree->getChildWithName("Slot " + String{ slot_index });
		slot.setProperty("Message", new_msg, nullptr);
	}
}

void Tree_Msg_Slots::set_msg_in_slot_byte(String& new_byte, const int slot_index, const int byte_index) {
	if (new_byte.length() == 2) {
		auto msg = msg_in_slot(slot_index);
		msg = msg.replaceSection(byte_index, 2, new_byte);
		set_msg_in_slot(msg, slot_index);
	}
}

String Tree_Msg_Slots::description_in_slot(const int slot_index) {
	auto slot = tree->getChildWithName("Slot " + String{ slot_index });
	return slot.getProperty("Description").toString();
}

void Tree_Msg_Slots::set_description_in_slot(String& description, const int slot_index) {
	auto slot = tree->getChildWithName("Slot " + String{ slot_index });
	slot.setProperty("Description", description, nullptr);
}

void Tree_Msg_Slots::add_listener_to_slot(ValueTree::Listener* listener, const int slot_index) {
	auto slot = tree->getChildWithName("Slot " + String{ slot_index });
	slot.addListener(listener);
}

void Tree_Msg_Slots::remove_listener_from_slot(ValueTree::Listener* listener, const int slot_index) {
	auto slot = tree->getChildWithName("Slot " + String{ slot_index });
	slot.removeListener(listener);
}

Tree_Msg_Slots::~Tree_Msg_Slots() {
	tree = nullptr;
}
