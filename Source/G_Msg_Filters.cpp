#include "G_Msg_Filters.h"

Msg_Filters::Msg_Filters(Data_Hub* hub) :
	Data_User{ hub }
{
	tgl_note.setToggleState(should_be_logged(note_on_off), dontSendNotification);
	tgl_note.onClick = [this] {
		set_should_be_logged(note_on_off, tgl_note.getToggleState());
	};
	tgl_note.addShortcut(KeyPress{ 'n', ModifierKeys::altModifier, 0 });
	addAndMakeVisible(tgl_note);

	tgl_bend.setToggleState(should_be_logged(aftertouch_bend), dontSendNotification);
	tgl_bend.onClick = [this] {
		set_should_be_logged(aftertouch_bend, tgl_bend.getToggleState());
	};
	tgl_bend.addShortcut(KeyPress{ 'a', ModifierKeys::altModifier, 0 });
	addAndMakeVisible(tgl_bend);

	tgl_pgm_change.setToggleState(should_be_logged(pgm_change), dontSendNotification);
	tgl_pgm_change.onClick = [this] {
		set_should_be_logged(pgm_change, tgl_pgm_change.getToggleState());
	};
	tgl_pgm_change.addShortcut(KeyPress{ 'p', ModifierKeys::altModifier, 0 });
	addAndMakeVisible(tgl_pgm_change);

	tgl_ctrl_change.setToggleState(should_be_logged(ctrl_change), dontSendNotification);
	tgl_ctrl_change.onClick = [this] {
		set_should_be_logged(ctrl_change, tgl_ctrl_change.getToggleState());
	};
	tgl_ctrl_change.addShortcut(KeyPress{ 'r', ModifierKeys::altModifier, 0 });
	addAndMakeVisible(tgl_ctrl_change);

	tgl_sysex.setToggleState(should_be_logged(sysex), dontSendNotification);
	tgl_sysex.onClick = [this] {
		set_should_be_logged(sysex, tgl_sysex.getToggleState());
	};
	tgl_sysex.addShortcut(KeyPress{ 'y', ModifierKeys::altModifier, 0 });
	addAndMakeVisible(tgl_sysex);

	flag_alt_shortcuts("");
}

void Msg_Filters::paint(Graphics& g) {
	g.setFont(FONT::lbl_section);
	g.setColour(COLOR::txt);
	auto lbl_section_area = XYWH::devices_lbl_section.translated(0, -3);
	g.drawText("Include In Logs:", lbl_section_area, Justification::topLeft);
	auto note_txt = format_label_txt(alt_flag + "Note On / Note Off");
	note_txt.draw(g, XYWH::filters_lbl_note.toFloat());
	auto bend_txt = format_label_txt(alt_flag + "Aftertouch / Pitch Bend");
	bend_txt.draw(g, XYWH::filters_lbl_bend.toFloat());
	auto pgm_change_txt = format_label_txt(alt_flag + "Program Change");
	pgm_change_txt.draw(g, XYWH::filters_lbl_pgm_change.toFloat());
	auto ctrl_change_txt = format_label_txt("Cont" + alt_flag + "rol Change");
	ctrl_change_txt.draw(g, XYWH::filters_lbl_ctrl_change.toFloat());
	auto sysex_txt = format_label_txt("S" + alt_flag + "ysex");
	sysex_txt.draw(g, XYWH::filters_lbl_sysex.toFloat());
}

void Msg_Filters::flag_alt_shortcuts(const String flag) {
	alt_flag = flag;
	repaint();
}

AttributedString Msg_Filters::format_label_txt(String txt) {
	auto uline_index = -1;
	if (txt.contains("&"))
		uline_index = txt.indexOf("&");
	AttributedString att_txt{ uline_index > -1 ? txt.replaceSection(uline_index, 1, "") : txt };
	att_txt.setJustification(Justification::centredLeft);
	att_txt.setColour(COLOR::txt);
	att_txt.setFont(FONT::lbl_filter);
	if (uline_index > -1)
		att_txt.setFont(Range<int>(uline_index, uline_index + 1), FONT::lbl_filter_uline);
	return att_txt;
}

void Msg_Filters::resized() {
	tgl_note.setBounds(XYWH::filters_tgl_note);
	tgl_bend.setBounds(XYWH::filters_tgl_bend);
	tgl_pgm_change.setBounds(XYWH::filters_tgl_pgm_change);
	tgl_ctrl_change.setBounds(XYWH::filters_tgl_ctrl_change);
	tgl_sysex.setBounds(XYWH::filters_tgl_sysex);
}

void Msg_Filters::mouseDown(const MouseEvent& e) {
	if (XYWH::filters_lbl_note.contains(e.getPosition()))
		tgl_note.triggerClick();
	if (XYWH::filters_lbl_bend.contains(e.getPosition()))
		tgl_bend.triggerClick();
	if (XYWH::filters_lbl_pgm_change.contains(e.getPosition()))
		tgl_pgm_change.triggerClick();
	if (XYWH::filters_lbl_ctrl_change.contains(e.getPosition()))
		tgl_ctrl_change.triggerClick();
	if (XYWH::filters_lbl_sysex.contains(e.getPosition()))
		tgl_sysex.triggerClick();
}
