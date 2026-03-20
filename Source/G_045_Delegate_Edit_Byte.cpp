#include "G_045_Delegate_Edit_Byte.h"

Delegate_Edit_Byte::Delegate_Edit_Byte(const int slot_index, const int col_ID, Data_Hub* hub) :
	slot_index{ slot_index },
	byte_index{ (col_ID - 1) * 2 },
	Data_User{ hub }
{
	setEditable(true);
	setMinimumHorizontalScale(1.0f);
	setHasFocusOutline(false);
	current_txt = message_in_slot(slot_index).substring(byte_index, byte_index + 2);
	onEditorShow = [this] {
		auto editor{ getCurrentTextEditor() };
		editor->setFont(FONT::table);
		editor->setInputRestrictions(2, "0123456789abcdefABCDEF");
		editor->setText(current_txt);
		editor->selectAll();
	};
	setText(current_txt, dontSendNotification);
}

void Delegate_Edit_Byte::paint(Graphics& g) {
	g.setColour(COLOR::text);
	g.setFont(FONT::table);
	auto w = getWidth();
	auto h = getHeight();
	g.drawText(getText(), 2, 0, w - 4, h, Justification::centred);
	g.setColour(COLOR::outline);
	g.drawHorizontalLine(h - 1, 0.0f, w * 1.0f);
	g.drawVerticalLine(w - 1, 0.0f, h * 1.0f);
}

void Delegate_Edit_Byte::textWasEdited() {
	auto new_txt = getText();
	if (new_txt.length() == 2) {
		new_txt = new_txt.toLowerCase();
		auto& slot_txt = message_in_slot(slot_index);
		set_message_in_slot(slot_txt.replaceSection(byte_index, 2, new_txt), slot_index);
		current_txt = new_txt;
	}
	setText(current_txt, dontSendNotification);
}
