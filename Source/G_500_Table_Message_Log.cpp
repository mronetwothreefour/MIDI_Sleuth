#include "G_500_Table_Message_Log.h"

Table_Message_Log::Table_Message_Log(Tree_MIDI_Message_Log& message_log) :
	message_log{ message_log }
{
	addAndMakeVisible(table);
	table.setModel(this);
	table.setColour(ListBox::outlineColourId, Colours::grey);
	table.setOutlineThickness(1);
	table.setMultipleSelectionEnabled(true);

	auto& header = table.getHeader();
	header.addColumn("#", 1, 30);
	header.addColumn("Timestamp", 2, 75);
	header.addColumn("Description", 3, 200);
	header.addColumn("Length", 4, 75);

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
		g.setFont(Font{ FontOptions{ 12.0f } });
		String col_name{ "#" };
		if (col_num == 2)
			col_name = "Timestamp";
		if (col_num == 3)
			col_name = "Description";
		if (col_num == 4)
			col_name = "Length";
		auto text = message_log.cell_value(row_num, col_name);
		g.drawText(text, 2, 0, w - 4, h, Justification::centredLeft);
		g.drawHorizontalLine(h - 1, 0.0f, w * 1.0f);
		g.drawVerticalLine(w - 1, 0.0f, h * 1.0f);
	}
}

void Table_Message_Log::resized() {
	table.setBounds(0, 0, getWidth(), getHeight());
}

void Table_Message_Log::valueTreeChildAdded(ValueTree& /*parent_tree*/, ValueTree& /*new_row*/) {
	table.updateContent();
}

Table_Message_Log::~Table_Message_Log() {
	message_log.remove_listener(this);
}
