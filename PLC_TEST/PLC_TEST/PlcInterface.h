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

	// WORD 1���� ����.
	long GetDevice				( CString szDeviceAddress, short& sGetData);
	long SetDevice				( CString szDeviceAddress, short sSetData);

	// WORD ������  N���� Read/ Write �Ѵ�.
	long GetDeviceDword			(CString szDeviceAddress, long& lGetData);
	long SetDeviceDword			( CString szDeviceAddress, long sSetData);

	// Double WORD ������ 1���� �а�  ���� 
	long GetDeviceBlock		( CString szDeviceAddress, long lSize, byte* bpGetData);
	long SetDeviceBlock		( CString szDeviceAddress, long lSize, byte* bpSetData);

	// Double WORD ������ N���� �а�  ���� 
	long GetDeviceBlockDword	( CString szDeviceAddress, long lSize, byte* bpGetData);
	long SetDeviceBlockDword	( CString szDeviceAddress, long lSize, byte* bpSetData);
	
	bool DeviceState();
private :

	IActUtlType*	mp_IUtlType;	// ACT Control (Custom Interface)

	cslock			m_csPlcInterfaceLock;


	int				m_nChannelNo;
	bool			m_bIsOpen;

};

