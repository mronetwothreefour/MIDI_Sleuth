#include "G_070_Table_MIDI_Message_Log.h"

#include "C_000_GUI_Constants.h"
#include "D_010_Util_MIDI.h"
#include "G_090_Header_MIDI_Message_Log.h"
#include "G_110_Delegate_Data_Byte.h"
#include "G_120_Popup_Menu_Table.h"

Table_MIDI_Message_Log::Table_MIDI_Message_Log(Data_Hub* hub, Tree_MIDI_Messages* message_log, const bool not_compare_table) :
	Data_User{ hub },
	message_log{ message_log },
	not_compare_table{ not_compare_table }
{
	addAndMakeVisible(table);
	table.setModel(this);
	table.setMultipleSelectionEnabled(true);
	table.setHeader(std::unique_ptr<Header_MIDI_Message_Log>{ new Header_MIDI_Message_Log{ not_compare_table } });
	table.setHeaderHeight(21);
	header = static_cast<Header_MIDI_Message_Log*>(&table.getHeader());
	message_log->add_listener(this);
	cmd_mngr.registerAllCommandsForTarget(this);
}

int Table_MIDI_Message_Log::getNumRows() {
	return message_log->number_of_rows();
}

void Table_MIDI_Message_Log::compare_selected_messages() {
	auto selection = table.getSelectedRows();
	if (selection.size() > 1) {
		Array<MidiMessage> messages{};
		for (int i = 0; i < selection.size(); ++i) {
			auto bytes_string = message_log->entry_bytes(selection[i]);
			messages.add(Util_MIDI::convert_hex_string_to_MIDI_message(bytes_string));
		}
		compare->clear_tree();
		for (auto& msg : messages) {
			compare->log_message(msg);
		}
	}
}

const String Table_MIDI_Message_Log::get_bytes_for_first_selected_row() {
	auto row_num = table.getSelectedRow(0);
	return message_log->entry_bytes(row_num);
}

void Table_MIDI_Message_Log::scroll_to_row(const int row_num) {
	table.scrollToEnsureRowIsOnscreen(row_num);
}

void Table_MIDI_Message_Log::paintRowBackground(Graphics& g, int /*row_num*/, int /*w*/, int /*h*/, bool is_selected) {
	if (is_selected)
		g.fillAll(COLOR::hilite);
}

void Table_MIDI_Message_Log::paintCell(Graphics& g, int row_num, int col_num, int w, int h, bool /*is_selected*/) {
	if (row_num > -1 && row_num < message_log->number_of_rows() &&
		col_num > 0 && col_num <= table.getHeader().getNumColumns(true))
	{
		g.setColour(COLOR::text);
		g.setFont(Font{ FontOptions{ 13.0f } });
		String text{ "" };
		if (col_num == 1)
			text = String{ row_num + 1 };
		if (col_num == 2)
			text = String{ message_log->entry_timestamp(row_num) };
		if (col_num == 3)
			text = message_log->entry_description(row_num);
		if (col_num == 4)
			text = String{ message_log->entry_length(row_num) };
		g.drawText(text, 2, 0, w - 4, h, col_num > 4 ? Justification::centred : Justification::centredLeft);
		g.setColour(COLOR::outline);
		g.drawHorizontalLine(h - 1, 0.0f, w * 1.0f);
		g.drawVerticalLine(w - 1, 0.0f, h * 1.0f);
	}
}

Component* Table_MIDI_Message_Log::refreshComponentForCell(int row_num, int col_num, bool /*is_selected*/, Component* c) {
	auto byte_col_num = col_num;
	byte_col_num -= not_compare_table ? 4 : 1;
	if (byte_col_num > 0) {
		auto* cell_data_byte{ static_cast<Delegate_Data_Byte*>(c) };
		if (cell_data_byte == nullptr)
			cell_data_byte = new Delegate_Data_Byte{ row_num, byte_col_num, message_log };
		if (!not_compare_table && row_num > 0) {
			auto entry_bytes = compare->entry_bytes(row_num);
			auto prev_entry_bytes = compare->entry_bytes(row_num - 1);
			if (prev_entry_bytes.length() == entry_bytes.length()) {
				auto byte_index = (byte_col_num - 1) * 2;
				auto byte_val = entry_bytes.substring(byte_index, byte_index + 2).getHexValue32();
				auto prev_byte_val = prev_entry_bytes.substring(byte_index, byte_index + 2).getHexValue32();
				cell_data_byte->set_hilighted(byte_val != prev_byte_val);
			}
		}
		return cell_data_byte;
	}
	return c;
}

void Table_MIDI_Message_Log::resized() {
	table.setBounds(0, 0, getWidth(), getHeight());
}

void Table_MIDI_Message_Log::valueTreeChildAdded(ValueTree& parent_tree, ValueTree& new_row) {
	int msg_length{ new_row.getProperty("Bytes").toString().length() / 2 };
	auto num_byte_columns = header->byte_column_count();
	if (msg_length > num_byte_columns) {
		auto current_header_h = table.getHeaderHeight();
		if (msg_length > 299 && current_header_h < 63)
			table.setHeaderHeight(63);
		if (msg_length > 199 && current_header_h < 42)
			table.setHeaderHeight(42);
		for (int i = num_byte_columns; i < msg_length; ++i)
			header->add_data_byte_column(i);
	}
	table.updateContent();
	scroll_to_row(parent_tree.indexOf(new_row));
}

void Table_MIDI_Message_Log::valueTreeChildRemoved(ValueTree& /*parent_tree*/, ValueTree& /*row*/, int /*row_index*/) {
	table.updateContent();
}

void Table_MIDI_Message_Log::cellClicked(int row_num, int col_num, const MouseEvent& e) {
	if (e.mods == ModifierKeys::rightButtonModifier) {
		Popup_Menu_Table menu{ hub };
		menu.showMenuAsync(PopupMenu::Options{}.withTargetComponent(table.getCellComponent(col_num, row_num)));
	}
	else
		TableListBoxModel::cellClicked(row_num, col_num, e);
}

ApplicationCommandTarget* Table_MIDI_Message_Log::getNextCommandTarget() {
	return findFirstTargetParentComponent();
}

void Table_MIDI_Message_Log::getAllCommands(Array<int>& cmd_list) {
	cmd_list.add(store_msg_in_slot_1,
				 store_msg_in_slot_2,
				 store_msg_in_slot_3,
				 store_msg_in_slot_4,
				 store_msg_in_slot_5,
				 compare_messages);
}

void Table_MIDI_Message_Log::getCommandInfo(int cmd, ApplicationCommandInfo& info) {
	if (cmd >= store_msg_in_slot_1 && cmd <= store_msg_in_slot_5) {
		auto slot_num = cmd - 3;
		String slot{ slot_num };
		info.setInfo("Slot " + slot, "Store last selected message in slot " + slot, "Store Messages", 0);
		info.addDefaultKeypress(0x30 + slot_num, ModifierKeys::ctrlModifier | ModifierKeys::shiftModifier);
	}
	if (cmd == compare_messages) {
		info.setInfo("Compare messages", "Compare the selected messages", "Compare Messages", 0);
		info.addDefaultKeypress('=', ModifierKeys::ctrlModifier);
	}
}

bool Table_MIDI_Message_Log::perform(const InvocationInfo& info) {
	auto cmd = info.commandID;
	if (cmd >= store_msg_in_slot_1 && cmd <= store_msg_in_slot_5) {
		auto row_num = table.getLastRowSelected();
		if (row_num > -1) {
			auto slot_num = cmd - 4;
			auto msg = message_log->entry_bytes(row_num);
			set_message_in_slot(msg, slot_num);
			return true;
		}
	}
	if (cmd == compare_messages) 	{
		compare_selected_messages();
		if (not_compare_table)
			cmd_mngr.invokeDirectly(show_tab_compare, true);
		return true;
	}
	return false;
}

Table_MIDI_Message_Log::~Table_MIDI_Message_Log() {
	message_log->remove_listener(this);
}
