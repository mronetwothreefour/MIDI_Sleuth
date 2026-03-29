#pragma once

#include <JuceHeader.h>

#include "D_Data_User.h"
#include "G_Lbox_Device_Select.h"

class Comp_Msg_Handler :
    public Component,
    private MidiInputCallback,
    private AsyncUpdater,
    private ump::EndpointsListener,
    public Data_User
{
private: Device_Array list_inputs, list_outputs;
private: std::unique_ptr<Lbox_Device_Select> lbox_inputs, lbox_outputs;
private: CriticalSection monitor_lock;
private: Array<MidiMessage> list_received_messages;

//==============================================================================
public: explicit Comp_Msg_Handler(Data_Hub* hub);

public: void paint(Graphics& g) override;
public: void resized() override;
public: void open_device(bool input, int index);
public: void close_device(bool input, int index);
public: int count_inputs() const noexcept;
public: int count_outputs() const noexcept;
private: bool device_list_changed(const Array<MidiDeviceInfo>& connected_devices, bool inputs);
private: void endpointsChanged() override;
public: Dele_Device::Ptr get_device(int index, bool input) const noexcept;
private: Dele_Device::Ptr find_device(MidiDeviceInfo device_info, bool input) const;
private: void close_connected_devices(const Array<MidiDeviceInfo>& connected_devices, bool input);
private: void update_list(bool input);
private: void update_lists();
private: void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& msg) override;
private: void handleAsyncUpdate() override;
private: void send_msg(const MidiMessage& msg);
public: void send_msg_in_slot(const int slot_index);
public: void stop_and_reset_all();
public: ~Comp_Msg_Handler();

//==============================================================================
private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Comp_Msg_Handler)
};