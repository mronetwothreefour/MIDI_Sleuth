#include "G_040_Component_Edit_MIDI_Message.h"

#include "G_045_Delegate_Edit_Byte.h"

Component_Edit_MIDI_Message::Component_Edit_MIDI_Message(const int slot_index, Data_Hub* hub) :
	slot_index{ slot_index },
	Data_User{ hub }
{
	table.setModel(this);
	table.setRowSelectedOnMouseDown(false);
	table.setBounds(XYWH::edit_msg_table);
	addAndMakeVisible(&table);
	add_columns_for_message_bytes();

	setSize(XYWH::edit_msg_w, XYWH::edit_msg_h);

	Timer::callAfterDelay(100, [this] { grabKeyboardFocus(); });
}

int Component_Edit_MIDI_Message::getNumRows() {
	return 1;
}

void Component_Edit_MIDI_Message::add_columns_for_message_bytes() {
	auto& msg = message_in_slot(slot_index);
	auto& header = table.getHeader();
	header.removeAllColumns();
	table.setHeaderHeight(18);
	if (msg.isNotEmpty()) {
		auto num_bytes = msg.length() / 2;
		if (num_bytes > 10)
			table.setHeaderHeight(num_bytes > 100 ? 42 : 30);
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

Component* Component_Edit_MIDI_Message::refreshComponentForCell(int /*row_num*/, int col_ID, 
																bool /*selected*/, 
																Component* c)
{
	auto* cell_data_byte{ static_cast<Delegate_Edit_Byte*>(c) };
	if (cell_data_byte == nullptr)
		cell_data_byte = new Delegate_Edit_Byte{ slot_index, col_ID, hub };
	return cell_data_byte;
}

bool Component_Edit_MIDI_Message::keyPressed(const KeyPress& key) {
	if (key == KeyPress{ 'v', ModifierKeys::ctrlModifier, 0 }) {
		auto msg = SystemClipboard::getTextFromClipboard();
		if (msg.isNotEmpty()) {
			msg = msg.removeCharacters(" ,\t\n\r");
			msg = msg.toLowerCase();
			if (msg.containsOnly("0123456789abcdef") && msg.length() % 2 == 0) {
				set_message_in_slot(msg, slot_index);
				add_columns_for_message_bytes();
			}
			return true;
		}
	}
	return false;
}
