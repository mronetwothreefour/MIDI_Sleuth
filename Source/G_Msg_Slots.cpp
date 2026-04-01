#include "G_Msg_Slots.h"

Msg_Slots::Msg_Slots(Data_Hub* hub, MIDI_Handler* midi_handler)
{
	auto gap = 2 * XYWH::win_main_inset;
	for (int slot_index = 0; slot_index < 5; ++slot_index) {
		msg_slots[slot_index].reset(new Msg_Slot{ slot_index, hub, midi_handler });
		auto slot_x = ((slot_index * XYWH::msg_slot_w) + (slot_index * gap));
		msg_slots[slot_index]->setBounds(slot_x, 0, XYWH::msg_slot_w, XYWH::msg_slot_h);
		addAndMakeVisible(msg_slots[slot_index].get());
	}

	setSize(XYWH::msg_slots_w, XYWH::msg_slots_h);
}

Msg_Slots::~Msg_Slots() {
	for (int slot_index = 0; slot_index < 5; ++slot_index)
		msg_slots[slot_index] = nullptr;
}
