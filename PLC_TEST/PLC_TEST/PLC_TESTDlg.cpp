
// PLC_TESTDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "PLC_TEST.h"
#include "PLC_TESTDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPLCTESTDlg 대화 상자



CPLCTESTDlg::CPLCTESTDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PLC_TEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPLCTESTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RETURN, m_return);
	DDX_Control(pDX, IDC_OUTPUT, m_output);
	DDX_Control(pDX, IDC_DEVICENAME, m_devicename);
	DDX_Control(pDX, IDC_DEVICEVALUE, m_devicevalue);
	DDX_Control(pDX, IDC_DEVICELENGTH, m_devicelength);
	DDX_Control(pDX, IDC_RADIO16BIT, m_radio16bit);
	DDX_Control(pDX, IDC_RADIO32BIT, m_radio32bit);
}

BEGIN_MESSAGE_MAP(CPLCTESTDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OEPN, &CPLCTESTDlg::OnBnClickedButtonOepn)
	ON_BN_CLICKED(IDC_BUTTON_WRITE, &CPLCTESTDlg::OnBnClickedButtonWrite)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CPLCTESTDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_READ, &CPLCTESTDlg::OnBnClickedButtonRead)
END_MESSAGE_MAP()


// CPLCTESTDlg 메시지 처리기

BOOL CPLCTESTDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	((CButton*)GetDlgItem(IDC_RADIO16BIT))->SetCheck(TRUE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CPLCTESTDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CPLCTESTDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CPLCTESTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPLCTESTDlg::OnBnClickedButtonOepn()
{
	bool bSimulation = false;
	int  nChannelNo = 1;

	m_PlcInterface.InitSetting(bSimulation, nChannelNo);
	long nRet = m_PlcInterface.OpenDevice();
	if (!nRet)
	{
		CString strreturn;
		strreturn.Format(_T("0x%08x"), nRet);
		m_return.SetWindowTextW(strreturn);
		AfxMessageBox(_T("OPEN 성공"));
	}
	else
	{
		AfxMessageBox(_T("OPEN 실패"));
	}
}

void CPLCTESTDlg::OnBnClickedButtonClose()
{
	long nRet = m_PlcInterface.CloseDevice();
	if (!nRet)
	{
		CString strreturn;
		strreturn.Format(_T("0x%08x"), nRet);
		m_return.SetWindowTextW(strreturn);
		AfxMessageBox(_T("Close 성공"));
	}
	else
	{
		AfxMessageBox(_T("Close 실패"));
	}
}

void CPLCTESTDlg::OnBnClickedButtonRead()
{
	if (m_PlcInterface.DeviceState())
	{
		CString szDeviceAddress, strlength, strreturn, stroutput;
		m_devicelength.GetWindowTextW(strlength);
		m_devicename.GetWindowText(szDeviceAddress);

		if (_ttoi(strlength) >= 100) { AfxMessageBox(_T("길이 초과\n다시 입력해주세요")); return; }
		else if (_ttoi(strlength) < 0) { AfxMessageBox(_T("출력할 수 없는 길이\n다시 입력해주세요")); return; }

		long nRet = 0;
		if (m_radio16bit.GetCheck() == 1)
		{
			if ((strlength == "") || (strlength == "0") || (strlength == "1"))
			{
				//WORD 1개 받기
				short sGetData;
				nRet = m_PlcInterface.GetDevice(szDeviceAddress, sGetData);
				stroutput.Format(_T("%c"), sGetData);
			}
			else
			{
				//WORD단위로 N개 받기
				char chBlockData[100] = { 0, };
				nRet = m_PlcInterface.GetDeviceBlock(szDeviceAddress, _ttoi(strlength), (byte*)chBlockData);

				stroutput = chBlockData;
			}
		}
		else if (m_radio32bit.GetCheck() == 1)
		{
			if ((strlength == "") || (strlength == "0") || (strlength == "1"))
			{
				//Double WORD 1개 받기
				long lGetData;
				nRet = m_PlcInterface.GetDeviceDword(szDeviceAddress, lGetData);
				stroutput.Format(_T("%c"), lGetData);
			}
			else
			{
				//Double WORD단위로 N개 받기
				char chBlockData[100] = { 0, };
				nRet = m_PlcInterface.GetDeviceBlockDword(szDeviceAddress, _ttoi(strlength), (byte*)chBlockData);

				stroutput = chBlockData;
			}
		}
		strreturn.Format(_T("0x%08x"), nRet);
		m_return.SetWindowTextW(strreturn);
		m_output.SetWindowTextW(stroutput);
	}
	else 
	{
		AfxMessageBox(_T("연결 실패"));
	}
}

void CPLCTESTDlg::OnBnClickedButtonWrite()
{
	if (m_PlcInterface.DeviceState())
	{
		CString szDeviceAddress, szDeviceValue;
		m_devicename.GetWindowText(szDeviceAddress);
		m_devicevalue.GetWindowText(szDeviceValue);
		int ilen = szDeviceValue.GetLength();
		char chBlockData[100] = { 0, };
		if (ilen >= 100) { AfxMessageBox(_T("출력 길이 초과\n다시 입력해주세요")); return; }
		if (m_radio16bit.GetCheck() == 1)
		{
			if (ilen < 2)
			{
				//WORD 1개 전송
				short sData = static_cast<short>(szDeviceValue[0]);
				m_PlcInterface.SetDevice(szDeviceAddress, sData);
			}
			else
			{
				//WORD단위로 N개 전송
				strcpy(chBlockData, CStringA(szDeviceValue));
				m_PlcInterface.SetDeviceBlock(szDeviceAddress, ilen, (byte*)chBlockData);
			}
		}
		else if (m_radio32bit.GetCheck() == 1)
		{
			if (ilen < 2)
			{
				//WORD 1개 전송
				m_PlcInterface.SetDeviceDword(szDeviceAddress, _ttoi(szDeviceValue));
			}
			else
			{
				//WORD단위로 N개 전송
				strcpy(chBlockData, CStringA(szDeviceValue));
				m_PlcInterface.SetDeviceBlockDword(szDeviceAddress, ilen , (byte*)chBlockData);
			}
		}
	}
	else
	{
		AfxMessageBox(_T("연결 실패"));
	}
}