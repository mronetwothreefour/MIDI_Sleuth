#pragma once

namespace ENUM
{

	const enum Message_Type
	{
		note_on_off = 1,
		aftertouch_pitch_bend = 2,
		ctrl_change = 4,
		pgm_change = 8,
		sysex = 16
	};

}
