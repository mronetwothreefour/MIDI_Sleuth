#pragma once

#include <JuceHeader.h>

#include "C_GUI_XYWH.h"
#include "C_GUI_COLOR.h"
#include "C_GUI_FONT.h"

class MS_Look_And_Feel :
	public LookAndFeel_V4
{
//==============================================================================
public: MS_Look_And_Feel();

public: void drawButtonBackground(Graphics& g, Button& btn, const Colour& bkgrnd,
								  bool hilited, bool down) override;
public: void drawButtonText(Graphics& g, TextButton& btn, bool hilited, bool down) override;

public: void drawPopupMenuBackground(Graphics& g, int w, int h) override;
public: void drawPopupMenuItem(Graphics& g, const Rectangle<int>& area, const bool separator,
							   const bool active, const bool hilited, const bool ticked,
							   const bool has_submenu, const String& txt, const String& shortcut_txt,
							   const Drawable* icon, const Colour* const txt_color) override;
public: void getIdealPopupMenuItemSize(const String& txt, const bool separator, 
									   int h, int& ideal_w, int& ideal_h) override;

public: void drawToggleButton(Graphics& g, ToggleButton& tgl, bool hilited, bool down) override;
public: void drawTickBox(Graphics& g, Component& c, float x, float y, 
						 float w, float h, const bool ticked, const bool enabled, 
						 const bool hilited, const bool down) override;


public: void drawTabButton(TabBarButton& btn, Graphics& g, bool mouse_over, bool mouse_down) override;
public: void drawTabButtonText(TabBarButton& btn, Graphics& g, bool mouse_over, bool mouse_down) override;

public: void drawTableHeaderColumn(Graphics& g, TableHeaderComponent& c,
								   const String& col_name, int col_id, int w, int h,
								   bool mouse_over, bool mouse_down, int col_flags) override;

public: void drawTextEditorOutline(Graphics&, int, int, TextEditor&) override {}

public: Rectangle<int> getTooltipBounds(const String& txt, Point<int> pos, Rectangle<int> parent_area) override;
public: void drawTooltip(Graphics& g, const String& txt, int w, int h) override;
public: TextLayout layoutTooltipText(const String& txt, Colour color) noexcept;

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MS_Look_And_Feel)
};