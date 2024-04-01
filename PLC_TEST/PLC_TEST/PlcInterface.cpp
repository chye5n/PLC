
#include "pch.h"
#include "framework.h"

#include "PlcInterface.h"


#include "C:\MELSEC\Act\Include\ActUtlType_i.h"	// For ActUtlType Control
#include "C:\MELSEC\Act\Include\ActUtlType_i.c"	// For CustomInterface

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


PlcInterface::PlcInterface()
	: m_bIsOpen(false), m_nChannelNo(0), mp_IUtlType(NULL)
{

}

PlcInterface::~PlcInterface()
{
}

void PlcInterface::InitSetting(bool bSimulationMode, int nChannelNo)
{
	m_nChannelNo =		 nChannelNo;
	HRESULT hr = CoCreateInstance(	CLSID_ActUtlType,
									NULL,
									CLSCTX_INPROC_SERVER,
									IID_IActUtlType,
									(LPVOID*)&mp_IUtlType);
	if (!SUCCEEDED(hr)) {
		AfxMessageBox(_T("CoCrateInstance() Failed."));
		exit(0);
	}
}

long PlcInterface::OpenDevice()
{
	long	nRet = PLC_OK;
	HRESULT	hr;

	hr = mp_IUtlType->put_ActLogicalStationNumber(m_nChannelNo);	// Exec set-property method
	if (SUCCEEDED(hr)) {	// Compornent Communication is succeeded?
		mp_IUtlType->Open(&nRet);	// Exec Open Method
		m_bIsOpen = true;
	}
	else {	// Failed Compornent Communication
		AfxMessageBox(_T("X"));
	}
	return nRet;
}

long PlcInterface::CloseDevice()
{
	long	nRet = PLC_OK;
	HRESULT	hr;

	hr = mp_IUtlType->Close(&nRet);	// Exec Close Method
	return nRet;
}

bool PlcInterface::DeviceState()
{
	if (m_bIsOpen)	return true;
	else { return false; }
}

long PlcInterface::GetDevice(CString szDeviceAddress, short& sGetData)
{
	long	nRet = PLC_OK;
	BSTR	szDevice = NULL;

	if ( !m_bIsOpen )
		return PLC_NG;
	
	szDevice	= szDeviceAddress.AllocSysString();

	HRESULT	hr	= mp_IUtlType->GetDevice2(szDevice, &sGetData, &nRet);

	if( !SUCCEEDED(hr) )
		throw PLC_NG;

	if ( nRet != 0x00 )
		throw PLC_NG;

	if (szDevice != NULL)
	{
		::SysFreeString(szDevice);
	}

	return nRet;
}

long PlcInterface::SetDevice(CString szDeviceAddress, short sSetData)
{
	long	nRet = PLC_OK;
	BSTR szDev = NULL;
	if (!m_bIsOpen)
		return PLC_NG;

	szDev = szDeviceAddress.AllocSysString();	// Allocate the BSTR-Type String area. 
	HRESULT hr = mp_IUtlType->SetDevice2(szDev, sSetData, &nRet);
	::SysFreeString(szDev);
	return nRet;
}
//ASCII ÄÚµå °ª
long PlcInterface::GetDeviceBlock(CString szDeviceAddress, long lSize, byte* bpGetData)
{
	long	nRet = PLC_OK;
	BSTR	szDevice = szDeviceAddress.AllocSysString();
	short* sData = new short[lSize];
	if (!m_bIsOpen)
		return PLC_NG;

	HRESULT	hr = mp_IUtlType->ReadDeviceBlock2(szDevice, lSize, sData, &nRet);

	for (int i = 0; i < lSize; ++i) 
	{
		bpGetData[i] = sData[i];
	}

	if (!SUCCEEDED(hr))
		throw PLC_NG;

	if (nRet != 0x00)
		throw PLC_NG;

	if (szDevice != NULL)
	{
		::SysFreeString(szDevice);
	}
	delete[] sData;
	return nRet;
}

long PlcInterface::SetDeviceBlock(CString szDeviceAddress, long lSize, byte* bpSetData)
{
	long	nRet = PLC_OK;
	BSTR szDev = szDeviceAddress.AllocSysString();	// Allocate the BSTR-Type String area. 
	if (!m_bIsOpen)
		return PLC_NG;

	short* shortArray = new short[lSize];
	for (int i = 0; i < lSize; i++) 
	{
		shortArray[i] = static_cast<short>(bpSetData[i]) | static_cast<short>(bpSetData[i + 1] << 16);
	}

	HRESULT hr = mp_IUtlType->WriteDeviceBlock2(szDev, lSize, shortArray, &nRet);
	::SysFreeString(szDev);
	delete[] shortArray;
	return nRet;
}

long PlcInterface::GetDeviceDword(CString szDeviceAddress, long& lGetData)
{
	long	nRet = PLC_OK;
	BSTR	szDevice = szDeviceAddress.AllocSysString();

	if (!m_bIsOpen)
		return PLC_NG;

	HRESULT	hr = mp_IUtlType->GetDevice(szDevice, &lGetData, &nRet);

	if (!SUCCEEDED(hr))
		throw PLC_NG;

	if (nRet != 0x00)
		throw PLC_NG;

	if (szDevice != NULL)
	{
		::SysFreeString(szDevice);
	}

	return nRet;
}

long PlcInterface::SetDeviceDword(CString szDeviceAddress, long lSetData)
{
	long	nRet = PLC_OK;
	BSTR szDev = szDeviceAddress.AllocSysString();

	if (!m_bIsOpen)
		return PLC_NG;

	HRESULT hr = mp_IUtlType->SetDevice(szDev, lSetData, &nRet);
	::SysFreeString(szDev);
	return nRet;
}


long PlcInterface::GetDeviceBlockDword(CString szDeviceAddress, long lSize, byte* bpGetData)
{
	long	nRet = PLC_OK;
	BSTR	szDevice = szDeviceAddress.AllocSysString();
	long* Data = new long[lSize];

	if (!m_bIsOpen)
		return PLC_NG;

	HRESULT	hr = mp_IUtlType->ReadDeviceBlock(szDevice, lSize, Data, &nRet);

	for (int i = 0; i < lSize; ++i)
	{
		bpGetData[i] = Data[i];
	}

	if (!SUCCEEDED(hr))
		throw PLC_NG;

	if (nRet != 0x00)
		throw PLC_NG;

	if (szDevice != NULL)
	{
		::SysFreeString(szDevice);
	}
	delete[] Data;
	return nRet;
}

long PlcInterface::SetDeviceBlockDword(CString szDeviceAddress, long lSize, byte* bpSetData)
{
	long	nRet = PLC_OK;
	BSTR szDev = szDeviceAddress.AllocSysString();	// Allocate the BSTR-Type String area. 

	if (!m_bIsOpen)
		return PLC_NG;

	long* Data = new long[lSize];

	for (int i = 0; i < lSize; i++)
	{
		Data[i] = bpSetData[i];
	}

	HRESULT hr = mp_IUtlType->WriteDeviceBlock(szDev, lSize, Data, &nRet);
	::SysFreeString(szDev);
	delete[] Data;
	return nRet;
}




