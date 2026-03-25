#include "G_050_Component_Filter_Toggles.h"

Component_Filter_Toggles::Component_Filter_Toggles(Data_Hub* hub) :
	Data_User{ hub }
{
	tgl_note_on_off.setToggleState(should_log(note_on_off), dontSendNotification);
	tgl_note_on_off.onClick = [this] {
		set_should_log(note_on_off, tgl_note_on_off.getToggleState());
	};
	addAndMakeVisible(tgl_note_on_off);

	tgl_aftertouch_bend.setToggleState(should_log(aftertouch_pitch_bend), dontSendNotification);
	tgl_aftertouch_bend.onClick = [this] {
		set_should_log(aftertouch_pitch_bend, tgl_aftertouch_bend.getToggleState());
	};
	addAndMakeVisible(tgl_aftertouch_bend);

	tgl_pgm_change.setToggleState(should_log(pgm_change), dontSendNotification);
	tgl_pgm_change.onClick = [this] {
		set_should_log(pgm_change, tgl_pgm_change.getToggleState());
	};
	addAndMakeVisible(tgl_pgm_change);

	tgl_ctrl_change.setToggleState(should_log(ctrl_change), dontSendNotification);
	tgl_ctrl_change.onClick = [this] {
		set_should_log(ctrl_change, tgl_ctrl_change.getToggleState());
	};
	addAndMakeVisible(tgl_ctrl_change);

	tgl_sysex.setToggleState(should_log(sysex), dontSendNotification);
	tgl_sysex.onClick = [this] {
		set_should_log(sysex, tgl_sysex.getToggleState());
	};
	addAndMakeVisible(tgl_sysex);
}

void Component_Filter_Toggles::paint(Graphics& g) {
	g.setColour(COLOR::text);
	g.setFont(FONT::filter_label);
	g.drawText("Include:", XYWH::filters_lbl_include, Justification::centredLeft);
	g.drawText("Note On/Off", XYWH::filters_lbl_note_on_off, Justification::centredLeft);
	g.drawText("Aftertouch/Pitch Bend", XYWH::filters_lbl_aftertouch_bend, Justification::centredLeft);
	g.drawText("Program Change", XYWH::filters_lbl_pgm_change, Justification::centredLeft);
	g.drawText("Control Change", XYWH::filters_lbl_ctrl_change, Justification::centredLeft);
	g.drawText("System Exclusive", XYWH::filters_lbl_sysex, Justification::centredLeft);
}

void Component_Filter_Toggles::resized() {
	tgl_note_on_off.setBounds(XYWH::filters_tgl_note_on_off);
	tgl_aftertouch_bend.setBounds(XYWH::filters_tgl_aftertouch_bend);
	tgl_pgm_change.setBounds(XYWH::filters_tgl_pgm_change);
	tgl_ctrl_change.setBounds(XYWH::filters_tgl_ctrl_change);
	tgl_sysex.setBounds(XYWH::filters_tgl_sysex);
}

void Component_Filter_Toggles::mouseDown(const MouseEvent& e) {
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
