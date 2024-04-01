#pragma once
#include "C:\MELSEC\Act\Include\ActUtlType_i.h"
#include "ConvertCount.h"

#define PLC_NG		1
#define PLC_OK		0

class MonitorInterface
{
public:
	MonitorInterface();
	~MonitorInterface();

	void InitSetting(int nChannelNo);
	long OpenDevice();
	long CloseDevice();
	bool DeviceState();
	long GetDeviceBlock(CString szDeviceAddress, long lSize, short* bpGetData);
	long GetDevice(CString szDeviceAddress, short& sGetData);
	long SetDevice(CString szDeviceAddress, short sSetData);

private:
	IActUtlType* mp_IUtlType;	// ACT Control (Custom Interface)
	ConvertCount m_ConvertCount;
	int		m_nChannelNo;
	bool	m_bIsOpen;
};

