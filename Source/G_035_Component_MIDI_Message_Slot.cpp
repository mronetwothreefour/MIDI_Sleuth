#include "G_035_Component_MIDI_Message_Slot.h"

Component_MIDI_Message_Slot::Component_MIDI_Message_Slot(int slot_num, Data_Hub* hub, Component_MIDI_Devices* devices) :
	Data_User{ hub },
	slot_num{ slot_num },
	devices{ devices },
	btn_edit{ "Edit" },
	btn_send{ "Send" }
{
	btn_edit.setBounds(XYWH::msg_slot_btn_edit);
	btn_edit.addShortcut(KeyPress{ 0x31 + slot_num, ModifierKeys::ctrlAltCommandModifiers, 0 });
	addAndMakeVisible(btn_edit);

	btn_send.setBounds(XYWH::msg_slot_btn_send);
	btn_send.onClick = [this, devices, slot_num] { devices->send_stored_message(slot_num); };
	btn_send.addShortcut(KeyPress{ 0x31 + slot_num, ModifierKeys::ctrlModifier, 0 });
	addAndMakeVisible(btn_send);

	setSize(XYWH::msg_slot_w, XYWH::msg_slot_h);
}

void Component_MIDI_Message_Slot::paint(Graphics& g) {
	g.setColour(COLOR::text);
	g.setFont(FONT::msg_slot_header);
	g.drawText("Message Slot " + String{ slot_num + 1 }, XYWH::msg_slot_lbl, Justification::centredTop);
}
