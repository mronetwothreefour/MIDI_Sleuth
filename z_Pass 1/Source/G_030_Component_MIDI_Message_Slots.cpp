#include "G_030_Component_MIDI_Message_Slots.h"

#include "C_000_GUI_Constants.h"

Component_MIDI_Message_Slots::Component_MIDI_Message_Slots(Data_Hub* hub, Component_MIDI_Devices* devices)
{
	auto gap = 2 * XYWH::margin;
	for (int slot_index = 0; slot_index < 5; ++slot_index) {
		msg_slots[slot_index].reset(new Component_MIDI_Message_Slot{ slot_index, hub, devices });
		auto slot_x = ((slot_index * XYWH::msg_slot_w) + (slot_index * gap));
		msg_slots[slot_index]->setBounds(slot_x, 0, XYWH::msg_slot_w, XYWH::msg_slot_h);
		addAndMakeVisible(msg_slots[slot_index].get());
	}

	setSize(XYWH::msg_slots_w, XYWH::msg_slots_h);
}

Component_MIDI_Message_Slots::~Component_MIDI_Message_Slots() {
	for (int slot_index = 0; slot_index < 5; ++slot_index)
		msg_slots[slot_index] = nullptr;
}
