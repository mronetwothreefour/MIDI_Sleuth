#include "G_Msg_Slot_Edit_Comp.h"

Msg_Slot_Edit_Comp::Msg_Slot_Edit_Comp(const Table_Type table_type, Data_Hub* hub) :
	slot_index{ table_type - msg_slot_1 },
	Data_User{ hub },
	table{ table_type, hub }
{
	slot_tree = msg_slot(slot_index);

	table.setBounds(XYWH::edit_msg_table);
	addAndMakeVisible(table);

	edit_description.setFont(FONT::txt_edit_description);
	edit_description.setBounds(XYWH::edit_msg_edit_description);
	edit_description.setText(slot_tree->msg_description());
	edit_description.addListener(this);
	addAndMakeVisible(edit_description);

	setSize(XYWH::win_edit_msg_w, XYWH::win_edit_msg_h);

	Timer::callAfterDelay(100, [this] { grabKeyboardFocus(); });
}

void Msg_Slot_Edit_Comp::paint(Graphics& g) {
	g.setColour(COLOR::txt);
	g.setFont(FONT::lbl_description);
	g.drawText("Description", XYWH::edit_msg_lbl_description, Justification::centredLeft);
}

void Msg_Slot_Edit_Comp::textEditorTextChanged(TextEditor& /*editor*/) {
	auto description = edit_description.getText();
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
	return false;
}

Msg_Slot_Edit_Comp::~Msg_Slot_Edit_Comp() {
	edit_description.removeListener(this);
}
