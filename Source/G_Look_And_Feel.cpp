#include "G_Look_And_Feel.h"

MS_Look_And_Feel::MS_Look_And_Feel()
{
	setColour(DocumentWindow::backgroundColourId, COLOR::bkgrnd);
	setColour(ListBox::backgroundColourId, COLOR::list_bkgrnd);
	setColour(ListBox::outlineColourId, COLOR::outline);
	setColour(PopupMenu::backgroundColourId, COLOR::bkgrnd);
	setColour(TabbedComponent::backgroundColourId, COLOR::bkgrnd);
	setColour(TabbedComponent::outlineColourId, COLOR::outline);
	setColour(TableHeaderComponent::backgroundColourId, COLOR::list_bkgrnd);
	setColour(TableHeaderComponent::outlineColourId, COLOR::outline);
	setColour(TableHeaderComponent::textColourId, COLOR::txt);
	setColour(TableListBox::backgroundColourId, COLOR::list_bkgrnd);
	setColour(TableListBox::outlineColourId, COLOR::outline);
	setColour(TableListBox::textColourId, COLOR::txt);
	setColour(TextEditor::backgroundColourId, COLOR::txt_edit_bkgrnd);
	setColour(TextEditor::textColourId, COLOR::txt);
	setColour(TextEditor::highlightColourId, COLOR::hilite);
}

void MS_Look_And_Feel::drawButtonBackground(Graphics& g, Button& btn, 
											const Colour& /*bkgrnd*/, 
											bool /*hilited*/, bool down)
{
	if (btn.isEnabled())
		g.fillAll(down ? COLOR::btn_down : COLOR::btn);
	else
		g.fillAll(COLOR::btn_disabled);
	g.setColour(COLOR::outline);
	g.drawRect(0, 0, btn.getWidth(), btn.getHeight(), 1);
}

void MS_Look_And_Feel::drawButtonText(Graphics& g, TextButton& btn, bool /*hilited*/, bool /*down*/) {
	g.setFont(FONT::btn);
	g.setColour(btn.isEnabled() ? COLOR::txt : COLOR::btn_disabled_txt);
	g.drawText(btn.getButtonText(), 0, 0, btn.getWidth(), btn.getHeight(), Justification::centred);
}

void MS_Look_And_Feel::drawPopupMenuBackground(Graphics& g, int w, int h) {
	g.fillAll(COLOR::bkgrnd);
	g.setColour(COLOR::outline);
	g.drawRect(0, 0, w, h, 1);
}

void MS_Look_And_Feel::drawPopupMenuItem(Graphics& g, const Rectangle<int>& area, 
										 const bool /*separator*/, const bool active, 
										 const bool hilited, const bool /*ticked*/, 
										 const bool has_submenu, const String& txt, 
										 const String& shortcut_txt, const Drawable* /*icon*/, 
										 const Colour* const /*txt_color*/)
{
	auto txt_area = area.reduced(8, 6);
	if (hilited && active) {
		g.setColour(COLOR::hilite);
		g.fillRect(area.reduced(2, 0));
	}
	g.setColour(COLOR::txt);
	if (has_submenu) {
		txt_area.removeFromRight(5);
		auto arrow_x = (float)txt_area.getRight();
		Path path;
		path.startNewSubPath(arrow_x, 5.5f);
		path.lineTo(arrow_x + 4.0f, 10.5f);
		path.lineTo(arrow_x, 15.5f);
		g.strokePath(path, PathStrokeType(2.0f));
	}
	g.setFont(FONT::popup_itm);
	g.drawFittedText(txt, txt_area, Justification::centredLeft, 1);
	if (shortcut_txt.isNotEmpty()) {
		g.setFont(FONT::popup_shortcut);
		g.drawFittedText(shortcut_txt, txt_area, Justification::centredRight, 1);
	}
}

void MS_Look_And_Feel::getIdealPopupMenuItemSize(const String& txt, 
												 const bool /*separator*/, int /*h*/, 
												 int& ideal_w, int& ideal_h)
{
	ideal_w = GlyphArrangement::getStringWidthInt(FONT::popup_itm, txt) + 27;
	ideal_h = 21;
}

void MS_Look_And_Feel::drawToggleButton(Graphics& g, ToggleButton& tgl, 
										bool hilited, bool down)
{
	drawTickBox(g, tgl, 0.0f, 0.0f, (float)tgl.getWidth(), (float)tgl.getHeight(),
		tgl.getToggleState(), tgl.isEnabled(), hilited, down);
}

void MS_Look_And_Feel::drawTickBox(Graphics& g, Component& /*c*/, float x, float y, 
								   float w, float h, const bool ticked, 
								   const bool /*enabled*/, const bool /*hilited*/, 
								   const bool /*down*/)
{
	g.fillAll(ticked ? COLOR::tgl_on : COLOR::tgl_off);
	g.setColour(COLOR::outline);
	g.drawRect(x, y, w, h);
}

void MS_Look_And_Feel::drawTabButton(TabBarButton& btn, Graphics& g, 
									 bool /*mouse_over*/, bool /*mouse_down*/)
{
	g.fillAll(COLOR::list_bkgrnd);
	auto w = btn.getWidth();
	auto h = btn.getHeight();
	g.setColour(COLOR::outline);
	g.drawVerticalLine(0, 0.0f, (float)h);
	g.drawVerticalLine(w - 1, 0.0f, (float)h);
	g.drawHorizontalLine(h - 1, 0.0f, (float)w);
	g.setColour(btn.getToggleState() ? COLOR::txt : COLOR::txt.darker(0.3f));
	g.setFont(FONT::tab);
	g.drawText(btn.getButtonText(), 0, 0, w, h, Justification::centred);
}

void MS_Look_And_Feel::drawTableHeaderColumn(Graphics& g, TableHeaderComponent& /*c*/,
											 const String& col_name, int /*col_id*/,
											 int w, int h, bool /*mouse_over*/,
											 bool /*mouse_down*/, int /*col_flags*/)
{
	Rectangle<int> area{ w, h };
	area.reduce(3, 3);
	g.setColour(COLOR::txt);
	g.setFont(col_name.containsOnly("0123456789") ? FONT::header_byte : FONT::header);
	g.drawFittedText(col_name, area, Justification::centredBottom, 4);
}

Rectangle<int> MS_Look_And_Feel::getTooltipBounds(const String& txt, Point<int> pos, 
												  Rectangle<int> parent_area)
{
	const TextLayout layout(layoutTooltipText(txt, COLOR::txt));
	auto w = (int)(layout.getWidth() + 16.0f);
	auto h = (int)(layout.getHeight() + 14.0f);
	return Rectangle<int>(
				pos.x > parent_area.getCentreX() ? pos.x - (w + 12) : pos.x + 24,
				pos.y > parent_area.getCentreY() ? pos.y - (h + 6) : pos.y + 6, w, h)
				.constrainedWithin(parent_area);
}

void MS_Look_And_Feel::drawTooltip(Graphics& g, const String& txt, int w, int h) {
	Rectangle<float> bounds{ (float)w, (float)h };
	g.fillAll(COLOR::bkgrnd);
	g.setColour(COLOR::outline);
	g.drawRect(bounds, 1.0f);
	layoutTooltipText(txt, COLOR::txt).draw(g, bounds);
}

TextLayout MS_Look_And_Feel::layoutTooltipText(const String& txt, Colour color) noexcept {
	AttributedString a_s;
	a_s.setJustification(Justification::centred);
	a_s.append(txt, FONT::tips, color);
	TextLayout layout;
	layout.createLayout(a_s, XYWH::tips_max_w);
	return layout;
}
