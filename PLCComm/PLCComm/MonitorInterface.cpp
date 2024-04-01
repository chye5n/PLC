#include "pch.h"
#include "MonitorInterface.h"

#include "C:\MELSEC\Act\Include\ActUtlType_i.h"	// For ActUtlType Control
#include "C:\MELSEC\Act\Include\ActUtlType_i.c"	// For CustomInterface

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

MonitorInterface::MonitorInterface()
	: m_bIsOpen(false), m_nChannelNo(0), mp_IUtlType(NULL)
{
}

MonitorInterface::~MonitorInterface()
{
}

void MonitorInterface::InitSetting(int nChannelNo)
{
	m_nChannelNo = nChannelNo;
	HRESULT hr = CoCreateInstance(CLSID_ActUtlType, NULL, CLSCTX_INPROC_SERVER, IID_IActUtlType, (LPVOID*)&mp_IUtlType);
	if (!SUCCEEDED(hr)) 
	{
		AfxMessageBox(_T("CoCrateInstance() Failed."));
		exit(0);
	}
}

long MonitorInterface::OpenDevice()
{
	long	nRet = PLC_OK;
	HRESULT	hr;

	hr = mp_IUtlType->put_ActLogicalStationNumber(m_nChannelNo);	// Exec set-property method
	if (SUCCEEDED(hr))	// Compornent Communication is succeeded?
	{	
		mp_IUtlType->Open(&nRet);	// Exec Open Method
		m_bIsOpen = true;
	}
	else 				// Failed Compornent Communication
	{
		AfxMessageBox(_T("Open ½ÇÆÐ"));
	}
	return nRet;
}

long MonitorInterface::CloseDevice()
{
	long	nRet = PLC_OK;
	if (!m_bIsOpen)
		return PLC_NG;

	HRESULT	hr = mp_IUtlType->Close(&nRet);	// Exec Close Method
	m_bIsOpen = false;
	return nRet;
}

bool MonitorInterface::DeviceState()
{
	if (m_bIsOpen)	return true;
	else { return false; }
}

long MonitorInterface::GetDeviceBlock(CString szDeviceAddress, long lSize, short* bpGetData)
{
	long	nRet = PLC_OK;
	BSTR	szDevice = szDeviceAddress.AllocSysString();
	if (!m_bIsOpen)
		return PLC_NG;

	HRESULT	hr = mp_IUtlType->ReadDeviceBlock2(szDevice, lSize, bpGetData, &nRet);

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

long MonitorInterface::GetDevice(CString szDeviceAddress, short& sGetData)
{
	long	nRet = PLC_OK;
	BSTR	szDevice = NULL;

	if (!m_bIsOpen)
		return PLC_NG;

	szDevice = szDeviceAddress.AllocSysString();
	HRESULT	hr = mp_IUtlType->GetDevice2(szDevice, &sGetData, &nRet);

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

long MonitorInterface::SetDevice(CString szDeviceAddress, short sSetData)
{
	long	nRet = PLC_OK;
	if (!m_bIsOpen)
		return PLC_NG;

	BSTR szDevice = szDeviceAddress.AllocSysString();	// Allocate the BSTR-Type String area. 
	HRESULT hr = mp_IUtlType->SetDevice2(szDevice, sSetData, &nRet);
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