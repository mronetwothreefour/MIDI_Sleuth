#include "D_Tree_Msg_Slots.h"

Tree_Msg_Slots::Tree_Msg_Slots() :
	tree{ new ValueTree{ "MIDI Message Slots" } }
{
	for (int slot_num = 1; slot_num < 6; ++slot_num) {
		ValueTree slot{ "Slot " + String{ slot_num} };
		slot.setProperty("Message", "", nullptr);
		slot.setProperty("Description", "", nullptr);
		tree->addChild(slot, -1, nullptr);
	}
}

String Tree_Msg_Slots::msg_in_slot(const int slot_num) {
	auto slot = tree->getChildWithName("Slot " + String{ slot_num });
	return slot.getProperty("Message").toString();
}

void Tree_Msg_Slots::set_msg_in_slot(String& msg, const int slot_num) {
	msg = msg.removeCharacters(" ,\t\n\r");
	msg = msg.toLowerCase();
	if (msg.containsOnly("0123456789abcdef")) {
		auto slot = tree->getChildWithName("Slot " + String{ slot_num });
		slot.setProperty("Message", msg, nullptr);
	}
}

String Tree_Msg_Slots::description_in_slot(const int slot_num) {
	auto slot = tree->getChildWithName("Slot " + String{ slot_num });
	return slot.getProperty("Description").toString();
}

void Tree_Msg_Slots::set_description_in_slot(String& description, const int slot_num) {
	auto slot = tree->getChildWithName("Slot " + String{ slot_num });
	slot.setProperty("Description", description, nullptr);
}

void Tree_Msg_Slots::add_listener_to_slot(ValueTree::Listener* listener, const int slot_num) {
	auto slot = tree->getChildWithName("Slot " + String{ slot_num });
	slot.addListener(listener);
}

void Tree_Msg_Slots::remove_listener_from_slot(ValueTree::Listener* listener, const int slot_num) {
	auto slot = tree->getChildWithName("Slot " + String{ slot_num });
	slot.removeListener(listener);
}

Tree_Msg_Slots::~Tree_Msg_Slots() {
	tree = nullptr;
}
