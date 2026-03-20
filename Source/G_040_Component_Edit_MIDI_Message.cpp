#include "G_040_Component_Edit_MIDI_Message.h"

#include "G_045_Delegate_Edit_Byte.h"

Component_Edit_MIDI_Message::Component_Edit_MIDI_Message(const int slot_index, Data_Hub* hub) :
	slot_index{ slot_index },
	Data_User{ hub }
{
	table.setModel(this);
	table.setRowSelectedOnMouseDown(false);
	table.setBounds(15, 15, 800, 84);
	addAndMakeVisible(&table);
	add_columns_for_message_bytes();

	setSize(XYWH::edit_msg_w, XYWH::edit_msg_h);
}

int Component_Edit_MIDI_Message::getNumRows() {
	return 1;
}

void Component_Edit_MIDI_Message::add_columns_for_message_bytes() {
	auto& msg = message_in_slot(slot_index);
	auto& header = table.getHeader();
	header.removeAllColumns();
	if (msg.isNotEmpty()) {
		auto num_bytes = msg.length() / 2;
		table.setHeaderHeight(num_bytes > 99 ? 63 : num_bytes > 9 ? 42 : 21);
		for (int byte_num = 0; byte_num < num_bytes; ++byte_num) {
			String col_name{ byte_num };
			auto num_digits = col_name.length();
			String vertical_col_name{ "" };
			for (auto i = 0; i < num_digits; ++i) {
				vertical_col_name << col_name[i];
				if (i + 1 < num_digits)
					vertical_col_name << "\n";
			}
			header.addColumn(vertical_col_name, byte_num + 1, 30);
		}
	}
	table.updateContent();
}

Component* Component_Edit_MIDI_Message::refreshComponentForCell(int row_num, int col_ID, 
																bool /*selected*/, 
																Component* c)
{
	auto* cell_data_byte{ static_cast<Delegate_Edit_Byte*>(c) };
	if (cell_data_byte == nullptr)
		cell_data_byte = new Delegate_Edit_Byte{ slot_index, col_ID, hub };
	return cell_data_byte;
}

//void Window_Edit_MIDI_Message::cellClicked(int row_num, int col_ID, const MouseEvent& e) {
//}
//
//bool Window_Edit_MIDI_Message::keyPressed(const KeyPress& key) {
//	return false;
//}
