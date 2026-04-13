#include "G_Table.h"

#include "G_Table_Header.h"
#include "G_Table_Cell.h"
#include "G_Table_Popup_Menu.h"
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
	table.setOutlineThickness(0);
	header = static_cast<Table_Header*>(&table.getHeader());
	addAndMakeVisible(table);

	if (table_type == log_in)
		tree = in_log;
	if (table_type == log_out)
		tree = out_log;
	if (table_type == comparison)
		tree = compare;
	if (table_type >= msg_slot_1 && table_type <= msg_slot_5) {
		auto slot_index = table_type - msg_slot_1;
		tree = msg_slot(slot_index);
		adjust_col_count(tree->msg_length(0));
		table.updateContent();
	}

	auto tab_color = COLOR::tab_bkgrnd_red;
	if (table_type == msg_slot_2)
		tab_color = COLOR::tab_bkgrnd_orange;
	if (table_type == msg_slot_3)
		tab_color = COLOR::tab_bkgrnd_yellow;
	if (table_type == msg_slot_4 || table_type == log_in)
		tab_color = COLOR::tab_bkgrnd_green;
	if (table_type == msg_slot_5 || table_type == comparison)
		tab_color = COLOR::tab_bkgrnd_blue;
	table.setColour(TableListBox::backgroundColourId, tab_color);
	header->setColour(TableHeaderComponent::backgroundColourId, tab_color);

	if (tree)
		tree->add_listener(this);

	cmd_mngr.registerAllCommandsForTarget(this);
	addKeyListener(cmd_mngr.getKeyMappings());
}

void Table::resized() {
	table.setBounds(0, 0, getWidth(), getHeight());
}

void Table::paintRowBackground(Graphics& g, int /*row_index*/, int /*w*/, int /*h*/, bool is_selected) {
	if (is_selected)
		g.fillAll(COLOR::hilite);
}

Component* Table::refreshComponentForCell(int row_index, int col_id, bool /*is_selected*/, Component* c) {
	auto* cell_byte{ static_cast<Table_Cell*>(c) };
	if (!cell_byte)
		cell_byte = new Table_Cell{ tree, hub };
	cell_byte->set_row_and_col(row_index, col_id);
	return cell_byte;
}

String Table::getCellTooltip(int row_index, int col_id) {
	auto byte_index = col_id - tree->non_byte_col_count() - 1;
	if (byte_index > -1) {
		auto byte_int = tree->single_byte_in_msg(byte_index, row_index).getHexValue32();
		String tooltip{ "Byte " + String{ byte_index } };
		tooltip += "\nDecimal: ";
		tooltip << byte_int;
		tooltip += "\nBinary: 0";
		tooltip += byte_int & 64 ? "1" : "0";
		tooltip += byte_int & 32 ? "1" : "0";
		tooltip += byte_int & 16 ? "1" : "0";
		tooltip += byte_int & 8 ?  "1" : "0";
		tooltip += byte_int & 4 ?  "1" : "0";
		tooltip += byte_int & 2 ?  "1" : "0";
		tooltip += byte_int & 1 ?  "1" : "0";
		return tooltip;
	}
	return String{};
}

int Table::getNumRows() {
	if (tree)
		return tree->row_count();
	return 0;
}

void Table::adjust_header_height(const int msg_length) {
	auto current_header_h = table.getHeaderHeight();
	if (msg_length > 100 && current_header_h != 45) {
		table.setHeaderHeight(45);
		return;
	}
	if (msg_length > 10 && msg_length <= 100 && current_header_h != 33) {
		table.setHeaderHeight(33);
		return;
	}
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
					header->removeColumn(i + 1);
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
	}
	table.updateContent();
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
	if (table_type >= msg_slot_1 && e.mods == ModifierKeys::leftButtonModifier) {
		table.deselectRow(row_index);
		auto c = static_cast<Table_Cell*>(table.getCellComponent(col_id, row_index));
		c->showEditor();
	}
	if (e.mods == ModifierKeys::rightButtonModifier) {
		Table_Popup_Menu menu{ table_type, hub };
		menu.showMenuAsync(PopupMenu::Options{}.withTargetComponent(table.getCellComponent(col_id, row_index)));
	}
	else
		TableListBoxModel::cellClicked(row_index, col_id, e);
}

void Table::backgroundClicked(const MouseEvent& e) {
	if (table_type >= msg_slot_1 && e.mods == ModifierKeys::leftButtonModifier)
		reset_active_col_id();
	if (e.mods == ModifierKeys::rightButtonModifier)
		show_jump_to_byte_dialog();
}

void Table::selectedRowsChanged(int /*last_row_selected*/) {
	cmd_mngr.commandStatusChanged();
}

void Table::set_next_cmd_target(ApplicationCommandTarget* new_target) {
	next_cmd_target = new_target;
}

ApplicationCommandTarget* Table::getNextCommandTarget() {
	return next_cmd_target;
}

void Table::getAllCommands(Array<int>& cmd_list) {
	cmd_list.add(copy_msg__no_sep,
				 copy_msg__spc_sep,
				 copy_msg__comma_sep,
				 copy_msg__tab_sep,
				 copy_msg__nl_sep);
	if (table_type < comparison)
		cmd_list.add(compare_messages);
	if (table_type < msg_slot_1) {
		cmd_list.add(jump_to_byte__log,
					 store_msg__slot_1,
					 store_msg__slot_2,
					 store_msg__slot_3,
					 store_msg__slot_4,
					 store_msg__slot_5);
	}
	if (table_type >= msg_slot_1) {
		cmd_list.add(jump_to_byte__slot,
					 msg_byte_delete,
					 msg_byte_insert,
					 msg_paste);
	}
}

void Table::getCommandInfo(int cmd, ApplicationCommandInfo& info) {
	if (cmd >= store_msg__slot_1 && cmd <= store_msg__slot_5) {
		auto slot_num = cmd - store_msg__slot_1 + 1;
		String slot{ slot_num };
		info.setInfo("Slot " + slot, "Store last selected message in slot " + slot, "Table", 0);
		info.addDefaultKeypress(0x30 + slot_num, ModifierKeys::shiftModifier);
		info.setActive(table.getSelectedRows().size() > 0);
	}
	if (cmd == compare_messages) {
		info.setInfo("Compare messages", "Compare the selected messages", "Compare Messages", 0);
		info.addDefaultKeypress('=', ModifierKeys::ctrlModifier);
		info.setActive(table.getSelectedRows().size() > 1);
	}
	if (cmd == jump_to_byte__log) {
		info.setInfo("Jump to byte", "Scroll table horizontally to show specified byte index", "Jump", 0);
		info.addDefaultKeypress('j', ModifierKeys::altModifier);
		info.setActive(hasKeyboardFocus(true));
	}
	if (cmd >= copy_msg__no_sep && cmd <= copy_msg__nl_sep)
		info.setActive(hasKeyboardFocus(true) && table.getSelectedRows().size() > 0);
	if (cmd == copy_msg__no_sep) {
		info.setInfo("Copy message bytes", "Copy last selected message, no separation between bytes", "Table", 0);
		info.addDefaultKeypress('c', ModifierKeys::ctrlModifier);
	}
	if (cmd == copy_msg__spc_sep) {
		info.setInfo("Space", "Copy last selected message, bytes separated by spaces", "Table", 0);
		info.addDefaultKeypress(' ', ModifierKeys::ctrlModifier);
		info.setActive(table.getSelectedRows().size() > 0);
	}
	if (cmd == copy_msg__tab_sep) {
		info.setInfo("Tab (\\t)", "Copy last selected message, bytes separated by tabs", "Table", 0);
		info.addDefaultKeypress('t', ModifierKeys::ctrlModifier);
	}
	if (cmd == copy_msg__comma_sep) {
		info.setInfo("Comma", "Copy last selected message, bytes separated by commas", "Table", 0);
		info.addDefaultKeypress(',', ModifierKeys::ctrlModifier);
	}
	if (cmd == copy_msg__nl_sep) {
		info.setInfo("Newline (\\n)", "Copy last selected message, bytes separated by newlines", "Table", 0);
		info.addDefaultKeypress('n', ModifierKeys::ctrlModifier);
	}
	if (cmd == jump_to_byte__log)
		info.setInfo("Jump to byte", "Scroll the log horizontally so that a specified byte is visible (if it exists)", "Table", 0);
	if (cmd == jump_to_byte__slot)
		info.setInfo("Jump to byte", "Scroll the message storage slot horizontally so that a specified byte is visible (if it exists)", "Table", 0);
	if (cmd == msg_byte_delete) {
		info.setInfo("Delete byte", "Delete the selected byte in the current message storage slot", "Slot", 0);
		info.addDefaultKeypress(KeyPress::deleteKey, ModifierKeys::noModifiers);
		info.addDefaultKeypress(KeyPress::backspaceKey, ModifierKeys::noModifiers);
	}
	if (cmd == msg_byte_insert) {
		info.setInfo("Insert byte", "Insert a byte at the end of the current message storage slot", "Slot", 0);
		info.addDefaultKeypress(KeyPress::insertKey, ModifierKeys::noModifiers);
	}
	if (cmd == msg_paste) {
		info.setInfo("Paste message", "Paste a message from the clipoard into the current message storage slot (if the message is validly formatted)", "Slot", 0);
		info.addDefaultKeypress('v', ModifierKeys::ctrlModifier);
	}
}

bool Table::perform(const InvocationInfo& info) {
	auto cmd = info.commandID;
	if (cmd >= store_msg__slot_1 && cmd <= store_msg__slot_5) {
		auto row_index = table.getLastRowSelected();
		if (row_index > -1) {
			auto slot_index = cmd - store_msg__slot_1;
			auto bytes = tree->msg_bytes(row_index);
			auto description = tree->msg_description(row_index);
			auto* slot_tree = msg_slot(slot_index);
			slot_tree->set_msg_bytes(bytes);
			slot_tree->set_msg_description(description);
			return true;
		}
	}
	if (cmd >= copy_msg__no_sep && cmd <= copy_msg__nl_sep) {
		auto row_index = table_type < msg_slot_1 ? table.getLastRowSelected() : 0;
		if (row_index > -1) {
			String msg{ tree->msg_bytes(row_index) };
			if (msg.isNotEmpty()) {
				if (cmd == copy_msg__spc_sep)
					separate_msg_bytes(msg, " ");
				if (cmd == copy_msg__tab_sep)
					separate_msg_bytes(msg, "\t");
				if (cmd == copy_msg__comma_sep)
					separate_msg_bytes(msg, ",");
				if (cmd == copy_msg__nl_sep)
					separate_msg_bytes(msg, "\n");
			}
			SystemClipboard::copyTextToClipboard(msg);
			return true;
		}
	}
	if (cmd == compare_messages) {
		compare_selected_messages();
		if (table_type < comparison)
			cmd_mngr.invokeDirectly(show_tab__compare, true);
		return true;
	}
	if (cmd == jump_to_byte__log || cmd == jump_to_byte__slot) {
		show_jump_to_byte_dialog();
		return true;
	}
	if (cmd == msg_byte_delete || cmd == msg_byte_insert) {
		auto byte_index = 0;
		if (active_col_id() > 1)
			byte_index = (active_col_id() - 2) * 2;
		if (cmd == msg_byte_delete) {
			auto msg = tree->msg_bytes();
			if (msg.isNotEmpty()) {
				if (active_col_id() < 2)
					tree->set_msg_bytes(msg.dropLastCharacters(2));
				else {
					msg = msg.replaceSection(byte_index, 2, "");
					tree->set_msg_bytes(msg);
				}
			}
		}
		if (cmd == msg_byte_insert) {
			auto msg = tree->msg_bytes();
			tree->set_msg_bytes(msg + "00");
		}
		return true;
	}
	if (cmd == msg_paste) {
		auto msg = SystemClipboard::getTextFromClipboard();
		if (msg.isNotEmpty()) {
			msg = msg.removeCharacters(" ,\t\n\r");
			msg = msg.toLowerCase();
			if (msg.containsOnly("0123456789abcdef") && msg.length() % 2 == 0)
				tree->set_msg_bytes(msg);
		}
		return true;
	}
	return false;
}

Table::~Table() {
	if (tree)
		tree->remove_listener(this);
	removeKeyListener(cmd_mngr.getKeyMappings());
}
