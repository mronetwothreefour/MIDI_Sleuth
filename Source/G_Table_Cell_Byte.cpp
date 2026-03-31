#include "G_Table_Cell_Byte.h"

Table_Cell_Byte::Table_Cell_Byte(const int byte_index, const Table_Type table_type, Data_Hub* hub) :
	Data_User{ hub },
	row_index{ -1 },
	byte_index{ byte_index },
	table_type{ table_type }
{
	setEditable(table_type >= msg_slot_1);
	setMinimumHorizontalScale(1.0f);
	setHasFocusOutline(false);
	onEditorShow = [this] {
		auto editor{ getCurrentTextEditor() };
		editor->setFont(FONT::table_cell);
		editor->setInputRestrictions(2, "0123456789abcdefABCDEF");
		editor->setText(current_txt);
		editor->selectAll();
	};
}

bool Table_Cell_Byte::should_be_hilited() const {
	if (table_type == compare_msg && row_index > 0) {
		auto this_cell_as_int = current_txt.getHexValue32();
		auto cell_above_this = compare->msg_byte(row_index - 1, byte_index);
		auto cell_above_this_as_int = cell_above_this.getHexValue32();
		return (this_cell_as_int != cell_above_this_as_int);
	}
	return false;
}

inline void Table_Cell_Byte::paint(Graphics& g) {
	if (should_be_hilited())
		g.fillAll(COLOR::hilite_byte_delta);
	auto w = getWidth();
	auto h = getHeight();
	if (!getCurrentTextEditor()) {
		g.setColour(COLOR::txt);
		g.setFont(FONT::table_cell);
		g.drawText(getText(), 2, 0, w - 4, h, Justification::centred);
	}
	g.setColour(COLOR::outline);
	g.drawHorizontalLine(h - 1, 0.0f, w * 1.0f);
	g.drawVerticalLine(w - 1, 0.0f, h * 1.0f);
}

void Table_Cell_Byte::set_row_index(const int index) {
	row_index = index;
	current_txt = get_byte_string();
	setText(current_txt, dontSendNotification);
	setTooltip(build_tooltip());
}

String Table_Cell_Byte::get_byte_string() {
	String byte_string{ "" };
	if (table_type == log_in)
		byte_string = in_log->msg_byte(row_index, byte_index);
	if (table_type == log_out)
		byte_string = out_log->msg_byte(row_index, byte_index);
	if (table_type == compare_msg)
		byte_string = compare->msg_byte(row_index, byte_index);
	if (table_type >= msg_slot_1) {
		const int slot_index = table_type - msg_slot_1;
		byte_string = slots->msg_in_slot_byte(slot_index, byte_index);
	}
	return byte_string;
}

String Table_Cell_Byte::build_tooltip() const {
	auto byte_int = current_txt.getHexValue32();
	String tooltip{ "Byte " + String{ byte_index } };
	tooltip += "\nDecimal: ";
	tooltip << byte_int;
	tooltip += "\nBinary: 0";
	tooltip += byte_int & 64 ? "1" : "0";
	tooltip += byte_int & 32 ? "1" : "0";
	tooltip += byte_int & 16 ? "1" : "0";
	tooltip += byte_int & 8 ? "1" : "0";
	tooltip += byte_int & 4 ? "1" : "0";
	tooltip += byte_int & 2 ? "1" : "0";
	tooltip += byte_int & 1 ? "1" : "0";
	return tooltip;
}

void Table_Cell_Byte::textWasEdited() {
	auto new_txt = getText();
	if (new_txt.length() == 2) {
		new_txt = new_txt.toLowerCase();
		auto slot_index = table_type - msg_slot_1;
		slots->set_msg_in_slot_byte(new_txt, slot_index, byte_index);
		current_txt = new_txt;
	}
	setText(current_txt, dontSendNotification);
	setTooltip(build_tooltip());
}
