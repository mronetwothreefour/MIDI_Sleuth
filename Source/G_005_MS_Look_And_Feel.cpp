#include "G_005_MS_Look_And_Feel.h"

#include "C_000_GUI_Constants.h"

MS_Look_And_Feel::MS_Look_And_Feel()
{
	setColour(DocumentWindow::backgroundColourId, COLOR::background);
	setColour(ListBox::backgroundColourId, COLOR::list_background);
	setColour(ListBox::outlineColourId, COLOR::outline);
	setColour(PopupMenu::backgroundColourId, COLOR::background);
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

void MS_Look_And_Feel::drawPopupMenuBackground(Graphics& g, int w, int h) {
	g.fillAll(COLOR::background);
	g.setColour(COLOR::outline);
	g.drawRect(0, 0, w, h, 1);
}

void MS_Look_And_Feel::drawPopupMenuItem(Graphics& g, const Rectangle<int>& area, 
										 const bool /*is_separator*/, const bool active, 
										 const bool hilighted, const bool /*ticked*/, 
										 const bool has_submenu, const String& txt, 
										 const String& shortcut_txt, const Drawable* /*icon*/, 
										 const Colour* const /*txt_color*/)
{
	auto txt_area = area.reduced(8, 6);
	if (hilighted && active) {
		g.setColour(COLOR::hilite);
		g.fillRect(area.reduced(2, 0));
	}
	g.setColour(COLOR::text);
	if (has_submenu) {
		txt_area.removeFromRight(5);
		auto arrow_x = (float)txt_area.getRight();
		Path path;
		path.startNewSubPath(arrow_x, 5.5f);
		path.lineTo(arrow_x + 4.0f, 10.5f);
		path.lineTo(arrow_x, 15.5f);
		g.strokePath(path, PathStrokeType(2.0f));
	}
	g.setFont(FONT::popup_menu);
	g.drawFittedText(txt, txt_area, Justification::centredLeft, 1);
	if (shortcut_txt.isNotEmpty()) {
		g.setFont(FONT::popup_menu_shortcut);
		g.drawFittedText(shortcut_txt, txt_area, Justification::centredRight, 1);
	}
}

void MS_Look_And_Feel::getIdealPopupMenuItemSize(const String& txt, 
												 const bool /*is_separator*/, int /*item_h*/, 
												 int& ideal_w, int& ideal_h)
{
	ideal_w = GlyphArrangement::getStringWidthInt(FONT::popup_menu, txt) + 27;
	ideal_h = 21;
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

void MS_Look_And_Feel::drawTabButton(TabBarButton& btn, Graphics& g, 
									 bool /*mouse_over*/, bool /*mouse_down*/)
{
	g.fillAll(COLOR::list_background);
	auto w = btn.getWidth();
	auto h = btn.getHeight();
	g.setColour(COLOR::outline);
	g.drawVerticalLine(0, 0.0f, (float)h);
	g.drawVerticalLine(w - 1, 0.0f, (float)h);
	g.drawHorizontalLine(h - 1, 0.0f, (float)w);
	g.setColour(btn.getToggleState() ? COLOR::text : COLOR::text.darker(0.3f));
	g.setFont(FONT::tab);
	g.drawText(btn.getButtonText(), 0, 0, w, h, Justification::centred);
}

void MS_Look_And_Feel::drawTableHeaderColumn(Graphics& g, TableHeaderComponent& /*c*/,
											 const String& col_name, int /*col_ID*/,
											 int w, int h, bool /*mouse_is_over*/,
											 bool /*mouse_is_down*/, int /*col_flags*/)
{
	Rectangle<int> area{ w, h };
	area.reduce(3, 3);
	g.setColour(COLOR::text);
	g.setFont(col_name.containsAnyOf("0123456789") ? FONT::table_byte_header : FONT::table_header);
	g.drawFittedText(col_name, area, Justification::centredBottom, 4);
}

Rectangle<int> MS_Look_And_Feel::getTooltipBounds(const String& text, Point<int> pos, 
												  Rectangle<int> parent_area)
{
	const TextLayout layout(layoutTooltipText(text, COLOR::text));
	auto w = (int)(layout.getWidth() + 16.0f);
	auto h = (int)(layout.getHeight() + 14.0f);
	return Rectangle<int>(
				pos.x > parent_area.getCentreX() ? pos.x - (w + 12) : pos.x + 24,
				pos.y > parent_area.getCentreY() ? pos.y - (h + 6) : pos.y + 6, w, h)
				.constrainedWithin(parent_area);
}

void MS_Look_And_Feel::drawTooltip(Graphics& g, const String& text, int w, int h) {
	Rectangle<float> bounds{ (float)w, (float)h };
	g.fillAll(COLOR::background);
	g.setColour(COLOR::outline);
	g.drawRect(bounds, 1.0f);
	layoutTooltipText(text, COLOR::text).draw(g, bounds);
}

TextLayout MS_Look_And_Feel::layoutTooltipText(const String& text, Colour color) noexcept {
	AttributedString a_s;
	a_s.setJustification(Justification::centred);
	a_s.append(text, FONT::tooltips, color);
	TextLayout layout;
	layout.createLayout(a_s, XYWH::tooltip_max_w);
	return layout;
}
