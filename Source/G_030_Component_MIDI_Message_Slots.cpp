#include "G_030_Component_MIDI_Message_Slots.h"

inline Component_MIDI_Message_Slots::Component_MIDI_Message_Slots(Data_Hub* hub, Component_MIDI_Devices* devices) :
	msg_slot_0{ 0, hub, devices},
	msg_slot_1{ 1, hub, devices},
	msg_slot_2{ 2, hub, devices},
	msg_slot_3{ 3, hub, devices},
	msg_slot_4{ 4, hub, devices}
{
	auto gap = 2 * XYWH::margin;

	msg_slot_0.setBounds(0, 0, XYWH::msg_slot_w, XYWH::msg_slot_h);
	addAndMakeVisible(msg_slot_0);

	msg_slot_1.setBounds(msg_slot_0.getRight() + gap, 0, XYWH::msg_slot_w, XYWH::msg_slot_h);
	addAndMakeVisible(msg_slot_1);

	msg_slot_2.setBounds(msg_slot_1.getRight() + gap, 0, XYWH::msg_slot_w, XYWH::msg_slot_h);
	addAndMakeVisible(msg_slot_2);

	msg_slot_3.setBounds(msg_slot_2.getRight() + gap, 0, XYWH::msg_slot_w, XYWH::msg_slot_h);
	addAndMakeVisible(msg_slot_3);

	msg_slot_4.setBounds(msg_slot_3.getRight() + gap, 0, XYWH::msg_slot_w, XYWH::msg_slot_h);
	addAndMakeVisible(msg_slot_4);

	setSize(XYWH::msg_slots_w, XYWH::msg_slots_h);
}
