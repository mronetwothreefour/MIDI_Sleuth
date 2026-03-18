#pragma once

#include <JuceHeader.h>

class MS_Look_And_Feel :
	public LookAndFeel_V4
{
//==============================================================================
public: MS_Look_And_Feel();

public: void drawButtonBackground(Graphics& g, Button& btn, const Colour& background, 
								  bool hilighted, bool down) override;
public: void drawButtonText(Graphics& g, TextButton& btn, bool hilighted, bool down) override;

public: void drawPopupMenuBackground(Graphics& g, int w, int h) override;
public: void drawPopupMenuItem(Graphics& g, const Rectangle<int>& area, const bool is_separator,
							   const bool active, const bool hilighted, const bool ticked,
							   const bool has_submenu, const String& txt, const String& shortcut_txt,
							   const Drawable* icon, const Colour* const txt_color) override;
public: void getIdealPopupMenuItemSize(const String& txt, const bool is_separator, 
									   int item_h, int& ideal_w, int& ideal_h) override;

public: void drawToggleButton(Graphics& g, ToggleButton& tgl, bool hilighted, bool down) override;
public: void drawTickBox(Graphics& g, Component& c, float x, float y, 
						 float w, float h, const bool ticked, const bool enabled, 
						 const bool hilighted, const bool down) override;


public: void drawTabButton(TabBarButton& btn, Graphics& g, bool mouse_over, bool mouse_down) override;

public: void drawTableHeaderColumn(Graphics& g, TableHeaderComponent& c,
								   const String& col_name, int col_ID, int w, int h,
								   bool mouse_is_over, bool mouse_is_down, int col_flags) override;

public: void drawTextEditorOutline(Graphics& /*g*/, int /*w*/, int /*h*/, TextEditor& /*e*/) override {}

public: Rectangle<int> getTooltipBounds(const String& text, Point<int> pos, Rectangle<int> parent_area) override;
public: void drawTooltip(Graphics& g, const String& text, int w, int h) override;
public: TextLayout layoutTooltipText(const String& text, Colour color) noexcept;

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MS_Look_And_Feel)
};