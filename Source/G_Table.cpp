#include "G_Table.h"

#include "G_Table_Header.h"
#include "G_Table_Cell_Byte.h"
#include "G_Table_Pop_Menu.h"
#include "G_Table_Jump_To_Byte_Dialog.h"

Table::Table(const Table_Type table_type, Data_Hub* hub) :
	table_type{ table_type },
	Data_User{ hub },
	tree{ nullptr }
{
	table.setModel(this);
	table.setRowSelectedOnMouseDown(table_type < msg_slot_1);
	table.setMultipleSelectionEnabled(table_type < msg_slot_1);
	table.setHeader(std::unique_ptr<Table_Header>{ new Table_Header{ table_type } });
	table.setHeaderHeight(21);
	header = static_cast<Table_Header*>(&table.getHeader());
	addAndMakeVisible(table);

	if (table_type == log_in)
		tree = in_log;
	if (table_type == log_out)
		tree = out_log;
	if (table_type == compare_msg)
		tree = compare;
	if (table_type >= msg_slot_1 && table_type <= msg_slot_5) {
		auto slot_index = table_type - msg_slot_1;
		tree = msg_slot(slot_index);
		adjust_col_count(tree->msg_length(0));
		table.updateContent();
	}

	if (tree)
		tree->add_listener(this);

	cmd_mngr.registerAllCommandsForTarget(this);

}

void Table::resized() {
	table.setBounds(0, 0, getWidth(), getHeight());
}

void Table::paintRowBackground(Graphics& g, int /*row_index*/, int /*w*/, int /*h*/, bool is_selected) {
	if (is_selected)
		g.fillAll(COLOR::hilite);
}

void Table::paintCell(Graphics& g, int row_index, int col_id, int w, int h, bool /*is_selected*/) {
	if (tree && row_index > -1 && row_index < tree->row_count() &&
		col_id > 0 && col_id < tree->first_byte_col_id())
	{
		g.setColour(COLOR::txt);
		g.setFont(FONT::table_cell);
		String text{ "" };
		if (col_id == 1)
			text = String{ row_index + 1 };
		if (col_id == 2)
			text = String{ tree->msg_timestamp(row_index) };
		if (col_id == 3)
			text = tree->msg_description(row_index);
		if (col_id == 4)
			text = String{ tree->msg_length(row_index) };
		g.drawText(text, 2, 0, w - 4, h, col_id > 4 ? Justification::centred : Justification::centredLeft);
		g.setColour(COLOR::outline);
		g.drawHorizontalLine(h - 1, 0.0f, w * 1.0f);
		g.drawVerticalLine(w - 1, 0.0f, h * 1.0f);
	}
}

Component* Table::refreshComponentForCell(int row_index, int col_id, bool /*is_selected*/, Component* c) {
	if (col_id >= tree->first_byte_col_id()) {
		auto byte_index = col_id - tree->first_byte_col_id();
		auto* cell_byte{ static_cast<Table_Cell_Byte*>(c) };
		if (!cell_byte)
			cell_byte = new Table_Cell_Byte{ tree, hub };
		cell_byte->set_indexes(row_index, byte_index);
		return cell_byte;
	}
	return c;
}

int Table::getNumRows() {
	if (tree)
		return tree->row_count();
	return 0;
}

void Table::adjust_header_height(const int msg_length) {
	auto current_header_h = table.getHeaderHeight();
	if (msg_length > 100 && current_header_h != 45)
		table.setHeaderHeight(45);
	if (msg_length > 10 && current_header_h != 33)
		table.setHeaderHeight(33);
	if (msg_length <= 10 && current_header_h != 21)
		table.setHeaderHeight(21);
}

void Table::adjust_col_count(const int msg_length) {
	auto byte_col_count = header->byte_col_count();
	adjust_header_height(msg_length);
	if (byte_col_count != msg_length) {
		if (msg_length > byte_col_count) {
			for (int i = byte_col_count; i < msg_length; ++i)
				header->add_byte_col(i);
		}
		if (tree->table_type >= msg_slot_1 && msg_length < byte_col_count) {
			for (int i = byte_col_count; i > msg_length; --i)
					header->removeColumn(i);
		}
	}
}

int Table::active_col_id() const {
	return header->getSortColumnId();
}

void Table::reset_active_col_id() {
	header->setSortColumnId(0, true);
}

void Table::scroll_to_msg_row(const int row_index) {
	table.scrollToEnsureRowIsOnscreen(row_index);
}

void Table::scroll_to_byte_col(const int byte_index) {
	auto byte_col_id = tree->first_byte_col_id() + byte_index;
	auto num_cols = header->getNumColumns(true);
	if (byte_col_id >= num_cols)
		byte_col_id = num_cols - 1;
	table.scrollToEnsureColumnIsOnscreen(byte_col_id);
}

void Table::show_jump_to_byte_dialog() {
	auto* dialog = new Jump_To_Byte_Dialog{ this };
	DialogWindow::LaunchOptions o;
	o.content.setOwned(dialog);
	o.dialogTitle = "Jump to byte";
	o.dialogBackgroundColour = COLOR::bkgrnd;
	o.escapeKeyTriggersCloseButton = true;
	o.useNativeTitleBar = true;
	o.resizable = false;
	Component::SafePointer<DialogWindow> dialog_win;
	dialog_win = o.launchAsync();
	if (dialog_win)
		dialog_win->centreAroundComponent(this, XYWH::jump_to_byte_dialog_w, XYWH::jump_to_byte_dialog_h);
}

void Table::compare_selected_messages() {
	auto selection = table.getSelectedRows();
	if (selection.size() > 1) {
		if (tree) {
			for (int i = 0; i < selection.size(); ++i) {
				auto hex_string = tree->msg_bytes(selection[i]);
				auto description = tree->msg_description(selection[i]);
				auto msg = Convert::hex_string_to_MIDI_message(hex_string);
				compare->add_msg(msg, description);
			}
		}
	}
}

void Table::separate_msg_bytes(String& msg, const String& separator) {
	if (msg.isNotEmpty()) {
		String msg_separated{ msg.substring(0, 2) };
		for (int byte_index = 2; byte_index < msg.length(); byte_index += 2) {
			msg_separated += separator;
			msg_separated += msg.substring(byte_index, byte_index + 2);
		}
		msg.swapWith(msg_separated);
	}
}

void Table::valueTreePropertyChanged(ValueTree& /*parent_tree*/, const Identifier& property_id) {
	if (tree->table_type >= msg_slot_1 && property_id.toString() == "Bytes") {
		auto msg_length = tree->msg_length(0);
		adjust_col_count(msg_length);
		table.updateContent();
	}
}

void Table::valueTreeChildAdded(ValueTree& parent_tree, ValueTree& new_row) {
	auto msg_index = parent_tree.indexOf(new_row);
	auto msg_length = tree->msg_length(msg_index);
	adjust_col_count(msg_length);
	table.updateContent();
	scroll_to_msg_row(parent_tree.indexOf(new_row));
}

void Table::valueTreeChildRemoved(ValueTree& /*parent_tree*/, ValueTree& /*row*/, int /*row_index*/) {
	table.updateContent();
}

void Table::cellClicked(int row_index, int col_id, const MouseEvent& e) {
	if (e.mods == ModifierKeys::rightButtonModifier) {
		Table_Pop_Menu menu{ table_type, hub };
		menu.showMenuAsync(PopupMenu::Options{}.withTargetComponent(table.getCellComponent(col_id, row_index)));
	}
	else
		TableListBoxModel::cellClicked(row_index, col_id, e);
}

void Table::backgroundClicked(const MouseEvent& /*e*/) {
	reset_active_col_id();
}

ApplicationCommandTarget* Table::getNextCommandTarget() {
	return findFirstTargetParentComponent();
}

void Table::getAllCommands(Array<int>& cmd_list) {
	if (table_type < msg_slot_1) {
		cmd_list.add(store_msg_in_slot_1,
					 store_msg_in_slot_2,
					 store_msg_in_slot_3,
					 store_msg_in_slot_4,
					 store_msg_in_slot_5,
					 compare_messages);
	}
	cmd_list.add(copy_msg_no_sep,
				 copy_msg_spc_sep,
				 copy_msg_comma_sep,
				 copy_msg_tab_sep,
				 copy_msg_nl_sep,
				 jump_to_byte);
}

void Table::getCommandInfo(int cmd, ApplicationCommandInfo& info) {
	if (cmd >= store_msg_in_slot_1 && cmd <= store_msg_in_slot_5) {
		auto slot_num = cmd - store_msg_in_slot_1 + 1;
		String slot{ slot_num };
		info.setInfo("Slot " + slot, "Store last selected message in slot " + slot, "Store Messages", 0);
		info.addDefaultKeypress(0x30 + slot_num, ModifierKeys::ctrlModifier);
		info.setActive(table.getSelectedRows().size() > 0);
	}
	if (cmd == copy_msg_no_sep) {
		info.setInfo("Copy message bytes", "Copy last selected message, no separation between bytes", "Copy Message", 0);
		info.addDefaultKeypress('c', ModifierKeys::ctrlModifier);
		info.setActive(table.getSelectedRows().size() > 0);
	}
	if (cmd == copy_msg_spc_sep) {
		info.setInfo("Space", "Copy last selected message, bytes separated by spaces", "Copy Message", 0);
		info.addDefaultKeypress(' ', ModifierKeys::ctrlModifier);
		info.setActive(table.getSelectedRows().size() > 0);
	}
	if (cmd == copy_msg_tab_sep) {
		info.setInfo("Tab (\\t)", "Copy last selected message, bytes separated by tabs", "Copy Message", 0);
		info.addDefaultKeypress('t', ModifierKeys::ctrlModifier);
		info.setActive(table.getSelectedRows().size() > 0);
	}
	if (cmd == copy_msg_comma_sep) {
		info.setInfo("Comma", "Copy last selected message, bytes separated by commas", "Copy Message", 0);
		info.addDefaultKeypress(',', ModifierKeys::ctrlModifier);
		info.setActive(table.getSelectedRows().size() > 0);
	}
	if (cmd == copy_msg_nl_sep) {
		info.setInfo("Newline (\\n)", "Copy last selected message, bytes separated by newlines", "Copy Message", 0);
		info.addDefaultKeypress('n', ModifierKeys::ctrlModifier);
		info.setActive(table.getSelectedRows().size() > 0);
	}
	if (cmd == compare_messages) {
		info.setInfo("Compare messages", "Compare the selected messages", "Compare Messages", 0);
		info.addDefaultKeypress('=', ModifierKeys::ctrlModifier);
		info.setActive(table.getSelectedRows().size() > 0);
	}
	if (cmd == jump_to_byte) {
		info.setInfo("Jump to byte", "Scroll table to show specified byte", "Jump", 0);
		info.addDefaultKeypress('j', ModifierKeys::ctrlModifier);
		info.setActive(table.getHeader().getNumColumns(true) > 25);
	}
}

bool Table::perform(const InvocationInfo& info) {
	auto cmd = info.commandID;
	if (cmd >= store_msg_in_slot_1 && cmd <= store_msg_in_slot_5) {
		auto row_index = table.getLastRowSelected();
		if (row_index > -1) {
			auto slot_index = cmd - store_msg_in_slot_1;
			auto bytes = tree->msg_bytes(row_index);
			auto description = tree->msg_description(row_index);
			auto* slot_tree = msg_slot(slot_index);
			slot_tree->set_msg_bytes(bytes);
			slot_tree->set_msg_description(description);
			return true;
		}
	}
	if (cmd >= copy_msg_no_sep && cmd <= copy_msg_nl_sep) {
		auto row_index = table_type < msg_slot_1 ? table.getLastRowSelected() : 0;
		if (row_index > -1) {
			String msg{ tree->msg_bytes(row_index) };
			if (msg.isNotEmpty()) {
				if (cmd == copy_msg_spc_sep)
					separate_msg_bytes(msg, " ");
				if (cmd == copy_msg_tab_sep)
					separate_msg_bytes(msg, "\t");
				if (cmd == copy_msg_comma_sep)
					separate_msg_bytes(msg, ",");
				if (cmd == copy_msg_nl_sep)
					separate_msg_bytes(msg, "\n");
			}
			SystemClipboard::copyTextToClipboard(msg);
			return true;
		}
	}
	if (cmd == compare_messages) {
		compare_selected_messages();
		if (table_type == log_in || table_type == log_out)
			cmd_mngr.invokeDirectly(show_tab_compare, true);
		return true;
	}
	if (cmd == jump_to_byte) {
		show_jump_to_byte_dialog();
		return true;
	}
	return false;
}

Table::~Table() {
	if (tree)
		tree->remove_listener(this);
}
