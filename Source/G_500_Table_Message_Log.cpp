#include "G_500_Table_Message_Log.h"

#include "G_510_Header_Message_Log.h"

Table_Message_Log::Table_Message_Log(Tree_MIDI_Message_Log& message_log) :
	message_log{ message_log }
{
	addAndMakeVisible(table);
	table.setModel(this);
	table.setColour(ListBox::outlineColourId, Colours::grey);
	table.setOutlineThickness(1);
	table.setMultipleSelectionEnabled(true);

	table.setHeader(std::unique_ptr<Header_Message_Log>{ new Header_Message_Log{} });
	header = static_cast<Header_Message_Log*>(&table.getHeader());
	message_log.add_listener(this);
}

int Table_Message_Log::getNumRows() {
	return message_log.number_of_rows();
}

void Table_Message_Log::scroll_to_row(const int row_num) {
	table.scrollToEnsureRowIsOnscreen(row_num);
}

void Table_Message_Log::paintRowBackground(Graphics& g, int /*row_num*/, int /*w*/, int /*h*/, bool is_selected) {
	if (is_selected)
		g.fillAll(Colour{ 0xff333333 });
}

void Table_Message_Log::paintCell(Graphics& g, int row_num, int col_num, int w, int h, bool /*is_selected*/) {
	if (row_num < message_log.number_of_rows() && col_num > 0 && col_num <= table.getHeader().getNumColumns(true)) {
		g.setColour(getLookAndFeel().findColour(ListBox::textColourId));
		g.setFont(Font{ FontOptions{ 13.0f } });
		String text{ "" };
		if (col_num == 1)
			text = message_log.entry_timestamp(row_num, "#");
		if (col_num == 2)
			text = message_log.entry_timestamp(row_num, "Timestamp");
		if (col_num == 3)
			text = message_log.entry_timestamp(row_num, "Description");
		if (col_num == 4)
			text = message_log.entry_timestamp(row_num, "Length");
		if (col_num > 4) {
			auto i = (col_num - 5) * 2;
			auto bytes_string = message_log.entry_timestamp(row_num, "Bytes");
			text = bytes_string.substring(i, i + 2);
		}
		g.drawText(text, 2, 0, w - 4, h, col_num > 4 ? Justification::centred : Justification::centredLeft);
		g.drawHorizontalLine(h - 1, 0.0f, w * 1.0f);
		g.drawVerticalLine(w - 1, 0.0f, h * 1.0f);
	}
}

void Table_Message_Log::resized() {
	table.setBounds(0, 0, getWidth(), getHeight());
}

void Table_Message_Log::valueTreeChildAdded(ValueTree& /*parent_tree*/, ValueTree& new_row) {
	int msg_length{ new_row.getChildWithName("Length").getProperty("Value") };
	auto num_byte_columns = header->byte_column_count();
	if (msg_length > num_byte_columns) {
		for (int i = num_byte_columns; i < msg_length; ++i)
			header->add_data_byte_column(i);
	}
	table.updateContent();
}

Table_Message_Log::~Table_Message_Log() {
	message_log.remove_listener(this);
}
