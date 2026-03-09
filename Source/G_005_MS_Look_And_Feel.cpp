#include "G_005_MS_Look_And_Feel.h"

#include "C_000_GUI_Constants.h"

MS_Look_And_Feel::MS_Look_And_Feel()
{
	setColour(DocumentWindow::backgroundColourId, COLOR::background);
	setColour(ListBox::backgroundColourId, COLOR::list_background);
	setColour(ListBox::outlineColourId, COLOR::outline);
	setColour(TabbedComponent::backgroundColourId, COLOR::background);
	setColour(TabbedComponent::outlineColourId, COLOR::outline);
	setColour(TableHeaderComponent::backgroundColourId, COLOR::list_background);
	setColour(TableHeaderComponent::outlineColourId, COLOR::outline);
	setColour(TableHeaderComponent::textColourId, COLOR::text);
	setColour(TableListBox::backgroundColourId, COLOR::list_background);
	setColour(TableListBox::outlineColourId, COLOR::outline);
	setColour(TableListBox::textColourId, COLOR::text);
}

void MS_Look_And_Feel::drawTableHeaderColumn(Graphics& g, TableHeaderComponent& c,
											 const String& col_name, int col_ID,
											 int w, int h, bool /*mouse_is_over*/,
											 bool /*mouse_is_down*/, int /*col_flags*/)
{
	Rectangle<int> area{ w, h };
	area.reduce(3, 3);
	g.setColour(c.findColour(TableHeaderComponent::textColourId));
	g.setFont(FONT::table_header);
	g.drawFittedText(col_name, area, Justification::centredBottom, 1);
}
