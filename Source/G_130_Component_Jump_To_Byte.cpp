#include "G_130_Component_Jump_To_Byte.h"

#include "C_000_GUI_Constants.h"

Component_Jump_To_Byte::Component_Jump_To_Byte(Table_MIDI_Message_Log& table) :
	table{ table },
	btn_cancel{ "Cancel", "Alt+C or Esc" },
	btn_jump{ "Jump", "Alt+J or Return" }
{
	edit_byte.setBounds(XYWH::jump_to_byte_edit);
	edit_byte.setFont(FONT::jump_to_byte_edit);
	edit_byte.setInputRestrictions(4, "0123456789");
	addAndMakeVisible(edit_byte);
	edit_byte.addListener(this);

	btn_cancel.setBounds(XYWH::jump_to_byte_btn_cancel);
	btn_cancel.onClick = [this] {
		if (DialogWindow* dw = findParentComponentOfClass<DialogWindow>()) {
			dw->exitModalState();
			dw->escapeKeyPressed();
		}
	};
	btn_cancel.addShortcut(KeyPress{ KeyPress::escapeKey });
	addAndMakeVisible(btn_cancel);

	btn_jump.setBounds(XYWH::jump_to_byte_btn_jump);
	btn_jump.onClick = [this] { jump_to_byte_and_close(); };
	btn_jump.setEnabled(false);
	addAndMakeVisible(btn_jump);

	setSize(XYWH::jump_to_byte_w, XYWH::jump_to_byte_h);

	Timer::callAfterDelay(100, [this] { edit_byte.grabKeyboardFocus(); });
}

void Component_Jump_To_Byte::paint(Graphics& g) {
	g.setColour(COLOR::text);
	g.setFont(FONT::jump_to_byte_lbl);
	g.drawText("Enter byte", XYWH::jump_to_byte_lbl, Justification::topLeft, false);
}

void Component_Jump_To_Byte::jump_to_byte_and_close() {
	if (DialogWindow* dw = findParentComponentOfClass<DialogWindow>()) {
		auto byte_num = edit_byte.getText().getIntValue();
		table.scroll_table_to_byte(byte_num);
		dw->exitModalState();
		dw->escapeKeyPressed();
	}
}

void Component_Jump_To_Byte::textEditorTextChanged(TextEditor& editor) {
	btn_jump.setEnabled(editor.getText().isNotEmpty());
}

void Component_Jump_To_Byte::textEditorReturnKeyPressed(TextEditor& /*editor*/) {
	btn_jump.triggerClick();
}

Component_Jump_To_Byte::~Component_Jump_To_Byte() {
	edit_byte.removeListener(this);
}
