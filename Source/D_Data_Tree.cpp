#include "D_Data_Tree.h"

Data_Tree::Data_Tree(Table_Type table_type) :
	table_type{ table_type },
	tree{ new ValueTree{ String{ table_type } } }
{
	if (table_type >= msg_slot_1) {
		ValueTree row{ "Message" };
		row.setProperty("Bytes", "", nullptr);
		row.setProperty("Description", "", nullptr);
		tree->addChild(row, 0, nullptr);
	}
}

const int Data_Tree::row_count() {
	if (table_type < msg_slot_1)
		return tree->getNumChildren();
	return 1;
}

const int Data_Tree::non_byte_col_count() const {
	if (table_type < Table_Type::comparison)
		return 4;
	return 1;
}

const int Data_Tree::first_byte_col_id() const {
	return non_byte_col_count() + 1;
}

void Data_Tree::add_msg(const MidiMessage& msg, String description) {
	if (table_type < msg_slot_1) {
		ValueTree row{ "Message" };
		auto bytes = Convert::MIDI_message_to_hex_string(msg);
		if (table_type < Table_Type::comparison) {
			row.setProperty("Timestamp", msg.getTimeStamp(), nullptr);
			if (description.isEmpty())
				description = Build_Description::from_hex_string(bytes);
			row.setProperty("Description", description, nullptr);
		}
		row.setProperty("Bytes", bytes, nullptr);
		tree->addChild(row, -1, nullptr);
	}
}

const int Data_Tree::msg_timestamp(const int msg_index) {
	if (table_type < Table_Type::comparison) {
		auto msg = tree->getChild(msg_index);
		double timestamp{ msg.getProperty("Timestamp") };
		return roundToInt(timestamp * 1000.0);
	}
	return 0;
}

const int Data_Tree::msg_length(const int msg_index) {
	return msg_bytes(msg_index).length() / 2;
}

const String Data_Tree::msg_description(const int msg_index) {
	auto msg = tree->getChild(msg_index);
	return msg.getProperty("Description").toString();
}

void Data_Tree::set_msg_description(const String& new_description) {
	if (table_type >= msg_slot_1) {
		auto msg = tree->getChild(0);
		msg.setProperty("Description", new_description, nullptr);
	}
}

const String Data_Tree::msg_bytes(const int msg_index) {
	auto msg = tree->getChild(msg_index);
	return msg.getProperty("Bytes").toString();
}

void Data_Tree::set_msg_bytes(const String& new_bytes) {
	if (table_type >= msg_slot_1) {
		auto msg = tree->getChild(0);
		msg.setProperty("Bytes", new_bytes, nullptr);
	}
}

const String Data_Tree::single_byte_in_msg(const int byte_index, const int msg_index) {
	auto i = byte_index * 2;
	return msg_bytes(msg_index).substring(i, i + 2);
}

void Data_Tree::set_single_byte_in_msg(const String& new_byte, const int byte_index) {
	if (table_type >= msg_slot_1 && new_byte.length() == 2) {
		auto i = byte_index * 2;
		auto bytes = msg_bytes();
		if (bytes.length() > i + 1) {
			bytes = bytes.replaceSection(i, 2, new_byte);
			set_msg_bytes(bytes);
		}
	}
}

void Data_Tree::clear_table() {
	if (table_type < msg_slot_1)
		tree->removeAllChildren(nullptr);
	else {
		set_msg_bytes("");
		set_msg_description("");
	}
}

void Data_Tree::add_listener(ValueTree::Listener* listener) {
	if (listener)
		tree->addListener(listener);
}

void Data_Tree::remove_listener(ValueTree::Listener* listener) {
	tree->removeListener(listener);
}

Data_Tree::~Data_Tree() {
	tree = nullptr;
}
