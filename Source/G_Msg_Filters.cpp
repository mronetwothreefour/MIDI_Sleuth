#include "G_Msg_Filters.h"

Msg_Filters::Msg_Filters(Data_Hub* hub) :
	Data_User{ hub }
{
	tgl_note_on_off.setToggleState(should_be_logged(note_on_off), dontSendNotification);
	tgl_note_on_off.onClick = [this] {
		set_should_be_logged(note_on_off, tgl_note_on_off.getToggleState());
	};
	addAndMakeVisible(tgl_note_on_off);

	tgl_aftertouch_bend.setToggleState(should_be_logged(aftertouch_pitch_bend), dontSendNotification);
	tgl_aftertouch_bend.onClick = [this] {
		set_should_be_logged(aftertouch_pitch_bend, tgl_aftertouch_bend.getToggleState());
	};
	addAndMakeVisible(tgl_aftertouch_bend);

	tgl_pgm_change.setToggleState(should_be_logged(pgm_change), dontSendNotification);
	tgl_pgm_change.onClick = [this] {
		set_should_be_logged(pgm_change, tgl_pgm_change.getToggleState());
	};
	addAndMakeVisible(tgl_pgm_change);

	tgl_ctrl_change.setToggleState(should_be_logged(ctrl_change), dontSendNotification);
	tgl_ctrl_change.onClick = [this] {
		set_should_be_logged(ctrl_change, tgl_ctrl_change.getToggleState());
	};
	addAndMakeVisible(tgl_ctrl_change);

	tgl_sysex.setToggleState(should_be_logged(sysex), dontSendNotification);
	tgl_sysex.onClick = [this] {
		set_should_be_logged(sysex, tgl_sysex.getToggleState());
	};
	addAndMakeVisible(tgl_sysex);
}

void Msg_Filters::paint(Graphics& g) {
	g.setColour(COLOR::txt);
	g.setFont(FONT::lbl_filter);
	g.drawText("Include:", XYWH::filters_lbl_include, Justification::centredLeft);
	g.drawText("Note On/Off", XYWH::filters_lbl_note_on_off, Justification::centredLeft);
	g.drawText("Aftertouch/Pitch Bend", XYWH::filters_lbl_aftertouch_bend, Justification::centredLeft);
	g.drawText("Program Change", XYWH::filters_lbl_pgm_change, Justification::centredLeft);
	g.drawText("Control Change", XYWH::filters_lbl_ctrl_change, Justification::centredLeft);
	g.drawText("System Exclusive", XYWH::filters_lbl_sysex, Justification::centredLeft);
}

void Msg_Filters::resized() {
	tgl_note_on_off.setBounds(XYWH::filters_tgl_note_on_off);
	tgl_aftertouch_bend.setBounds(XYWH::filters_tgl_aftertouch_bend);
	tgl_pgm_change.setBounds(XYWH::filters_tgl_pgm_change);
	tgl_ctrl_change.setBounds(XYWH::filters_tgl_ctrl_change);
	tgl_sysex.setBounds(XYWH::filters_tgl_sysex);
}

void Msg_Filters::mouseDown(const MouseEvent& e) {
	if (XYWH::filters_lbl_note_on_off.contains(e.getPosition()))
		tgl_note_on_off.triggerClick();
	if (XYWH::filters_lbl_aftertouch_bend.contains(e.getPosition()))
		tgl_aftertouch_bend.triggerClick();
	if (XYWH::filters_lbl_pgm_change.contains(e.getPosition()))
		tgl_pgm_change.triggerClick();
	if (XYWH::filters_lbl_ctrl_change.contains(e.getPosition()))
		tgl_ctrl_change.triggerClick();
	if (XYWH::filters_lbl_sysex.contains(e.getPosition()))
		tgl_sysex.triggerClick();
}
