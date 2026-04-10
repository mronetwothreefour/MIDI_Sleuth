#include "G_Table_Jump_To_Byte_Dialog.h"

#include "C_GUI_COLOR.h"
#include "C_GUI_FONT.h"
#include "C_GUI_XYWH.h"

Jump_To_Byte_Dialog::Jump_To_Byte_Dialog(Table* table) :
	table{ table },
	btn_cancel{ "Cancel", "Alt+C or Esc" },
	btn_jump{ "Jump", "Alt+J or Return" }
{
	edit_byte.setBounds(XYWH::jump_to_byte_txt_edit);
	edit_byte.setFont(FONT::txt_edit_jump_to_byte);
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
	btn_jump.setTooltip("The table will scroll horizontally\n so that the entered byte index is\nvisible (if it exists).");
	btn_jump.addShortcut(KeyPress{ 'j', ModifierKeys::altModifier, 0 });
	addAndMakeVisible(btn_jump);

	setSize(XYWH::jump_to_byte_dialog_w, XYWH::jump_to_byte_dialog_h);

	Timer::callAfterDelay(100, [this] { edit_byte.grabKeyboardFocus(); });
}

void Jump_To_Byte_Dialog::paint(Graphics& g) {
	g.setColour(COLOR::txt);
	g.setFont(FONT::lbl_jump_to_byte);
	g.drawText("Enter byte", XYWH::jump_to_byte_lbl, Justification::topLeft, false);
}

void Jump_To_Byte_Dialog::jump_to_byte_and_close() {
	if (DialogWindow* dw = findParentComponentOfClass<DialogWindow>()) {
		auto byte_index = edit_byte.getText().getIntValue();
		table->scroll_to_byte_col(byte_index);
		dw->exitModalState();
		dw->escapeKeyPressed();
	}
}

void Jump_To_Byte_Dialog::textEditorTextChanged(TextEditor& editor) {
	btn_jump.setEnabled(editor.getText().isNotEmpty());
}

void Jump_To_Byte_Dialog::textEditorReturnKeyPressed(TextEditor& /*editor*/) {
	btn_jump.triggerClick();
}

Jump_To_Byte_Dialog::~Jump_To_Byte_Dialog() {
	edit_byte.removeListener(this);
}
