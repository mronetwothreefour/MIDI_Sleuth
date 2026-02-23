#include "G_300_List_MIDI_Devices.h"

List_MIDI_Devices::List_MIDI_Devices(const String& name, Main_Component* parent, bool for_input_devices) :
	ListBox{ name },
	parent{ parent },
	for_input_devices{ for_input_devices }
{
}
