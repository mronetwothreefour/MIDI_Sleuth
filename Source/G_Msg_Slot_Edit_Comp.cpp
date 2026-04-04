#include "G_Msg_Slot_Edit_Comp.h"

Msg_Slot_Edit_Comp::Msg_Slot_Edit_Comp(const Table_Type table_type, Data_Hub* hub, MIDI_Handler* midi_handler) :
	slot_index{ table_type - msg_slot_1 },
	Data_User{ hub },
	table{ table_type, hub },
	btn_send{ "Send" }
{
	slot_tree = msg_slot(slot_index);

	table.setBounds(XYWH::edit_msg_table);
	addAndMakeVisible(table);

	edit_description.setEditable(true);
	edit_description.setColour(Label::backgroundColourId, COLOR::txt_edit_bkgrnd);
	edit_description.setFont(FONT::txt_edit_description);
	edit_description.setBounds(XYWH::edit_msg_edit_description);
	edit_description.setText(slot_tree->msg_description(), dontSendNotification);
	edit_description.onEditorShow = [this] {
		auto e = edit_description.getCurrentTextEditor();
		e->setFont(FONT::txt_edit_description);
		e->selectAll();
	};
	edit_description.addListener(this);
	addAndMakeVisible(edit_description);

	btn_send.setBounds(XYWH::edit_msg_btn_send);
	btn_send.onClick = [this, midi_handler] { midi_handler->send_msg_in_slot(slot_index); };
	btn_send.addShortcut(KeyPress{ 0x31 + slot_index, ModifierKeys::noModifiers, 0 });
	auto slot_string = String{ slot_index + 1 };
	btn_send.setTooltip("Send the message\nstored in slot " + slot_string + " to the\nselected outputs.\nShortcut: " + slot_string);
	addAndMakeVisible(btn_send);

	setSize(XYWH::win_edit_msg_w, XYWH::win_edit_msg_h);

	Timer::callAfterDelay(100, [this] { grabKeyboardFocus(); });
}

void Msg_Slot_Edit_Comp::paint(Graphics& g) {
	g.setColour(COLOR::txt);
	g.setFont(FONT::lbl_description);
	g.drawText("Description", XYWH::edit_msg_lbl_description, Justification::centredLeft);
}

void Msg_Slot_Edit_Comp::labelTextChanged(Label* lbl) {
	auto description = lbl->getText();
	slot_tree->set_msg_description(description);
}

bool Msg_Slot_Edit_Comp::keyPressed(const KeyPress& key) {
	if (key == KeyPress{ 'v', ModifierKeys::ctrlModifier, 0 }) {
		auto msg = SystemClipboard::getTextFromClipboard();
		if (msg.isNotEmpty()) {
			msg = msg.removeCharacters(" ,\t\n\r");
			msg = msg.toLowerCase();
			if (msg.containsOnly("0123456789abcdef") && msg.length() % 2 == 0)
				slot_tree->set_msg_bytes(msg);
			return true;
		}
	}
	auto active_col_id = table.active_col_id();
	auto byte_index = 0;
	if (active_col_id > 0)
		byte_index = (table.active_col_id() - 1) * 2;
	if (key == KeyPress::backspaceKey || key == KeyPress::deleteKey) {
		auto msg = slot_tree->msg_bytes();
		if (msg.isNotEmpty()) {
			if (active_col_id < 1)
				slot_tree->set_msg_bytes(msg.dropLastCharacters(2));
			else {
				msg = msg.replaceSection(byte_index, 2, "");
				slot_tree->set_msg_bytes(msg);
			}
			return true;
		}
	}
	if (key == KeyPress::insertKey) {
		auto msg = slot_tree->msg_bytes();
		slot_tree->set_msg_bytes(msg + "00");
		return true;
	}
	return false;
}

Msg_Slot_Edit_Comp::~Msg_Slot_Edit_Comp() {
	edit_description.removeListener(this);
}
