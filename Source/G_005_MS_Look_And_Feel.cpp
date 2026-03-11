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

void MS_Look_And_Feel::drawButtonBackground(Graphics& g, Button& btn, 
											const Colour& /*background*/, 
											bool /*hilighted*/, bool down)
{
	g.fillAll(down ? COLOR::button_down : COLOR::button);
	g.setColour(COLOR::outline);
	g.drawRect(0, 0, btn.getWidth(), btn.getHeight(), 1);
}

void MS_Look_And_Feel::drawButtonText(Graphics& g, TextButton& btn, bool /*hilighted*/, bool /*down*/) {
	g.setFont(FONT::button);
	g.setColour(COLOR::text);
	g.drawText(btn.getButtonText(), 0, 0, btn.getWidth(), btn.getHeight(), Justification::centred);
}

void MS_Look_And_Feel::drawToggleButton(Graphics& g, ToggleButton& tgl, 
										bool hilighted, bool down)
{
	drawTickBox(g, tgl, 0.0f, 0.0f, (float)tgl.getWidth(), (float)tgl.getHeight(),
		tgl.getToggleState(), tgl.isEnabled(), hilighted, down);
}

void MS_Look_And_Feel::drawTickBox(Graphics& g, Component& /*c*/, float x, float y, 
								   float w, float h, const bool ticked, 
								   const bool /*enabled*/, const bool /*hilighted*/, 
								   const bool /*down*/)
{
	g.fillAll(ticked ? COLOR::toggle_on : COLOR::toggle_off);
	g.setColour(COLOR::outline);
	g.drawRect(x, y, w, h);
}

void MS_Look_And_Feel::drawTableHeaderColumn(Graphics& g, TableHeaderComponent& c,
											 const String& col_name, int col_ID,
											 int w, int h, bool /*mouse_is_over*/,
											 bool /*mouse_is_down*/, int /*col_flags*/)
{
	Rectangle<int> area{ w, h };
	area.reduce(3, 3);
	g.setColour(c.findColour(TableHeaderComponent::textColourId));
	g.setFont(col_ID < 5 ? FONT::table_header : FONT::table_byte_header);
	g.drawFittedText(col_name, area, Justification::centredBottom, 4);
}
