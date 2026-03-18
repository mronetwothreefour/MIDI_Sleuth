#include "G_130_Dialog_Jump_To_Byte.h"

#include "C_000_GUI_Constants.h"

Dialog_Jump_To_Byte::Dialog_Jump_To_Byte(Table_MIDI_Message_Log& table) :
	table{ table },
	btn_cancel{ "Cancel" },
	btn_jump{ "Jump" }
{
	edit_byte.setBounds(XYWH::jump_to_byte_edit);
	edit_byte.setFont(FONT::popup_menu);
	addAndMakeVisible(edit_byte);

	btn_cancel.setBounds(XYWH::jump_to_byte_btn_cancel);
	btn_cancel.onClick = [this] {
		if (DialogWindow* dw = findParentComponentOfClass<DialogWindow>()) {
			dw->exitModalState();
			dw->escapeKeyPressed();
		}
	};
	btn_cancel.addShortcut(KeyPress{ KeyPress::escapeKey });
	btn_cancel.addShortcut(KeyPress{ 'c', ModifierKeys::altModifier, 0 });
	addAndMakeVisible(btn_cancel);

	btn_jump.setBounds(XYWH::jump_to_byte_btn_jump);
	btn_jump.onClick = [this] { jump_to_byte_and_close(); };
	btn_jump.addShortcut(KeyPress{ KeyPress::returnKey });
	btn_jump.addShortcut(KeyPress{ 'j', ModifierKeys::altModifier, 0 });
	addAndMakeVisible(btn_jump);

	setSize(XYWH::jump_to_byte_w, XYWH::jump_to_byte_h);
}

void Dialog_Jump_To_Byte::paint(Graphics& g) {
	g.setColour(COLOR::text);
	g.setFont(FONT::msg_slot_header);
	g.drawText("Target byte", XYWH::jump_to_byte_lbl, Justification::topLeft, false);
}

void Dialog_Jump_To_Byte::jump_to_byte_and_close() {
	if (DialogWindow* dw = findParentComponentOfClass<DialogWindow>()) {
		auto num_text = edit_byte.getText();
		if (num_text.isNotEmpty()) {
			auto byte_num = num_text.getIntValue();
			table.scroll_table_to_byte(byte_num);
		}
		dw->exitModalState();
		dw->escapeKeyPressed();
	}
}
