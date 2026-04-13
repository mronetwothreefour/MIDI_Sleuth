#include "G_Table_Cell.h"

Table_Cell::Table_Cell(Data_Tree* tree, Data_Hub* hub) :
	Data_User{ hub },
	row_index{ -1 },
	col_id{ 0 },
	byte_index{ -1 },
	tree{ tree },
	table_type{ tree->table_type }
{
	setInterceptsMouseClicks(false, true);
	setFont(FONT::table_cell);
	setMinimumHorizontalScale(1.0f);
	setHasFocusOutline(false);
	onEditorShow = [this] {
		auto editor{ getCurrentTextEditor() };
		editor->setFont(FONT::table_cell);
		if (table_type >= msg_slot_1 && byte_index > -1)
			editor->setInputRestrictions(2, "0123456789abcdefABCDEF");
		editor->setText(current_txt);
		editor->selectAll();
	};
}

bool Table_Cell::should_be_hilited() const {
	if (tree->table_type == comparison && row_index > 0 && byte_index > -1) {
		auto this_cell_as_int = current_txt.getHexValue32();
		auto cell_above_this = compare->single_byte_in_msg(byte_index, row_index - 1);
		auto cell_above_this_as_int = cell_above_this.getHexValue32();
		return (this_cell_as_int != cell_above_this_as_int);
	}
	return false;
}

inline void Table_Cell::paint(Graphics& g) {
	if (should_be_hilited())
		g.fillAll(COLOR::hilite_byte_delta);
	auto w = getWidth();
	auto h = getHeight();
	if (!getCurrentTextEditor()) {
		g.setColour(COLOR::txt);
		g.setFont(FONT::table_cell);
		auto justify = Justification::centred;
		if ((tree->table_type >= msg_slot_1 && col_id == 1) ||
			(tree->table_type < comparison && col_id == 3))
			justify = Justification::left;
		g.drawText(getText(), 2, 0, w - 4, h, justify);
	}
	g.setColour(COLOR::outline);
	g.drawHorizontalLine(h - 1, 0.0f, w * 1.0f);
	g.drawVerticalLine(w - 1, 0.0f, h * 1.0f);
}

void Table_Cell::set_row_and_col(const int new_row_index, const int new_col_id) {
	row_index = new_row_index;
	col_id = new_col_id;
	byte_index = col_id - tree->non_byte_col_count() - 1;
	if (row_index > -1) {
		if (col_id == 1) {
			if (table_type < msg_slot_1)
				current_txt = String{ row_index + 1 };
			else
				current_txt = tree->msg_description();
		}
		if (table_type < comparison) {
			switch (col_id) {
			case 2:
				current_txt = String{ tree->msg_timestamp(row_index) };
				break;
			case 3:
				current_txt = tree->msg_description(row_index);
				break;
			case 4:
				current_txt = String{ tree->msg_length(row_index) };
				break;
			default:
				break;
			}
		}
		if (byte_index > -1) {
			current_txt = get_byte_string();
		}
		setText(current_txt, dontSendNotification);
	}
}

String Table_Cell::get_byte_string() {
	if (byte_index > -1)
		return tree->single_byte_in_msg(byte_index, row_index);
	return String{};
}

void Table_Cell::textWasEdited() {
	auto new_txt = getText();
	if (col_id == 1) {
		tree->set_msg_description(new_txt);
		current_txt = new_txt;
	}
	if (col_id > 1 && new_txt.length() == 2) {
		new_txt = new_txt.toLowerCase();
		tree->set_single_byte_in_msg(new_txt, byte_index);
		current_txt = new_txt;
	}
	setText(current_txt, dontSendNotification);
}
