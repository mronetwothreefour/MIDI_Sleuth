#include "G_500_Table_Message_Log.h"

Table_Message_Log::Table_Message_Log() :
	row_count{ 0 }
{
	addAndMakeVisible(table);
	table.setModel(this);
	table.setColour(ListBox::outlineColourId, Colours::grey);
	table.setOutlineThickness(1);
	table.setMultipleSelectionEnabled(true);

	auto& header = table.getHeader();
	header.addColumn("Count", 1, 30);
	header.addColumn("Timestamp", 2, 50);
	header.addColumn("Description", 3, 150);
	header.addColumn("Length", 4, 30);
}

int Table_Message_Log::getNumRows() {
	return row_count;
}

void Table_Message_Log::paintRowBackground(Graphics& g, int /*row_num*/, int /*w*/, int /*h*/, bool is_selected) {
	if (is_selected)
		g.fillAll(Colour{ 0xff333333 });
}

void Table_Message_Log::paintCell(Graphics& g, int row_num, int col_id, int w, int h, bool is_selected)
{
}
