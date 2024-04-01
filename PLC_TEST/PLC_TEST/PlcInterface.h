#pragma once

#include "C:\MELSEC\Act\Include\ActUtlType_i.h"
#include "cslock.h"

#define PLC_NG		1
#define PLC_OK		0


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class PlcInterface
{
public:
	PlcInterface();
	~PlcInterface();

	void InitSetting(bool bSimulationMode, int nChannelNo);
	long OpenDevice();
	long CloseDevice();

	// WORD 1개를 쓴다.
	long GetDevice				( CString szDeviceAddress, short& sGetData);
	long SetDevice				( CString szDeviceAddress, short sSetData);

	// WORD 단위로  N개를 Read/ Write 한다.
	long GetDeviceDword			(CString szDeviceAddress, long& lGetData);
	long SetDeviceDword			( CString szDeviceAddress, long sSetData);

	// Double WORD 단위로 1개를 읽고  쓴다 
	long GetDeviceBlock		( CString szDeviceAddress, long lSize, byte* bpGetData);
	long SetDeviceBlock		( CString szDeviceAddress, long lSize, byte* bpSetData);

	// Double WORD 단위로 N개를 읽고  쓴다 
	long GetDeviceBlockDword	( CString szDeviceAddress, long lSize, byte* bpGetData);
	long SetDeviceBlockDword	( CString szDeviceAddress, long lSize, byte* bpSetData);
	
	bool DeviceState();
private :

	IActUtlType*	mp_IUtlType;	// ACT Control (Custom Interface)

	cslock			m_csPlcInterfaceLock;


	int				m_nChannelNo;
	bool			m_bIsOpen;

};

