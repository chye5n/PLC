
// PLCCommDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "PLCComm.h"
#include "PLCCommDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPLCCommDlg 대화 상자
CPLCCommDlg::CPLCCommDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PLCCOMM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPLCCommDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_BUFFERMEMORY, m_list_buffermemory);
	DDX_Control(pDX, IDC_EDIT_DEVICE, m_edit_device);
	DDX_Control(pDX, IDC_COMBO_DISPLAY, m_combo_display);
	DDX_Control(pDX, IDC_BTN_START, m_btn_start);
	DDX_Control(pDX, IDC_BTN_STOP, m_btn_stop);
	DDX_Control(pDX, IDC_EDIT_UPDATECYCLE, m_edit_update);
	DDX_Control(pDX, IDC_BTN_OPEN, m_btn_open);
	DDX_Control(pDX, IDC_BTN_CLOSE, m_btn_close);
}

BEGIN_MESSAGE_MAP(CPLCCommDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_START, &CPLCCommDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CPLCCommDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CPLCCommDlg::OnBnClickedBtnClose)
	ON_BN_CLICKED(IDC_BTN_STOP, &CPLCCommDlg::OnBnClickedBtnStop)
	ON_WM_TIMER()
	ON_CBN_CLOSEUP(IDC_COMBO_DISPLAY, &CPLCCommDlg::OnCbnCloseupComboDisplay)
	ON_BN_CLICKED(IDC_BTN_CHANGE, &CPLCCommDlg::OnBnClickedBtnChange)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BUFFERMEMORY, &CPLCCommDlg::OnNMDblclkListBuffermemory)
END_MESSAGE_MAP()


// CPLCCommDlg 메시지 처리기
BOOL CPLCCommDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_list_buffermemory.InsertColumn(0, _T("Device"), LVCFMT_CENTER, 80);
	m_list_buffermemory.InsertColumn(1, _T("+F E D C +B A 9 8 +7 6 5 4 +3 2 1 0"), LVCFMT_CENTER, 250);
	m_list_buffermemory.InsertColumn(2, _T("Value"), LVCFMT_CENTER, 77);
	m_list_buffermemory.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);

	m_combo_display.SetCurSel(0);
	m_btn_close.EnableWindow(false);
	m_btn_stop.EnableWindow(false);
	GetDlgItem(IDC_STATIC_STATE)->ShowWindow(SW_HIDE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CPLCCommDlg::OnPaint()
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
HCURSOR CPLCCommDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPLCCommDlg::OnBnClickedBtnOpen()	//Open 버튼
{
	int  nChannelNo = 1;	//Channel 번호

	m_MonitorInterface.InitSetting(nChannelNo);		//Channel 번호설정
	long nRet = m_MonitorInterface.OpenDevice();	//연결
	if (nRet == 0) 
	{
		AfxMessageBox(_T("OPEN 성공")); 
		SetButtonStates(false, true);
	}
	else 
	{
		CString strFailMsg;	//Open을 실패했을 경우 오류코드 확인
		strFailMsg.Format(_T("OPEN 실패\n0x%08x"), nRet);
		AfxMessageBox(strFailMsg);
	}
}

void CPLCCommDlg::OnBnClickedBtnClose()	//Close 버튼
{
	long nRet = m_MonitorInterface.CloseDevice();
	if (nRet == 0) 
	{
		KillTimer(1); 
		AfxMessageBox(_T("Close 성공"));
		SetButtonStates(true, true);
		GetDlgItem(IDC_STATIC_STATE)->ShowWindow(SW_HIDE);
		m_edit_device.SetWindowText(_T(""));
		m_list_buffermemory.DeleteAllItems();	//List에 있는 모든 Item삭제
	}
	else 
	{
		CString strFailMsg;	//Close를 실패했을 경우 오류코드 확인
		strFailMsg.Format(_T("Close 실패\n0x%08x"), nRet);
		AfxMessageBox(strFailMsg); 
	}
}

void CPLCCommDlg::OnBnClickedBtnStart()	//Start Monitor 버튼을 눌렀을 경우
{
	if(!m_MonitorInterface.DeviceState())	//연결 여부 판단
	{
		AfxMessageBox(_T("연결이 되어있지 않습니다."));
		return;
	}
	CString strDeviceAddress;
	m_edit_device.GetWindowText(strDeviceAddress);
	//주소 여부 판단
	if ((strDeviceAddress[0] != BIT_DEVICE) && (strDeviceAddress[0] != WORD_DEVICE) || (m_ConvertCount.AlphaCount(strDeviceAddress) > 1))
	{	
		AfxMessageBox(_T("존재하지 않는 주소값입니다.\n다시 입력해주세요.")); 
		m_edit_device.SetWindowText(_T(""));
		return;
	}
	m_list_buffermemory.DeleteAllItems();	//List에 있는 모든 Item삭제
	m_strDeviceAddress = strDeviceAddress;
	ListItemInsert(m_strDeviceAddress);		//입력한 주소부터 List 추가
	if (m_list_buffermemory.GetItemCount() < 1) { return; }
	SetTimer(1, m_nTimerCycle, NULL);		//Timer 30ms로 시작
	SetButtonStates(false, false);
	m_bTimerRunning = true;					//Timer 시작 알림
}

void CPLCCommDlg::ListItemInsert(CString strDeviceAddress)	//List에 Item 추가
{
	int nAddress = _ttoi(m_strDeviceAddress.Mid(1));	//주소값의 'M'이나 'D'를 제외한 나머지 값을 int로 저장
	char strDeviceType(m_strDeviceAddress[0]);
	if ((strDeviceType == BIT_DEVICE) && (nAddress % 16 != 0))
	{
		nAddress -= (nAddress % 16); 
		CString strAddress;
		strAddress.Format(_T("%d"), nAddress);
		m_strDeviceAddress = strDeviceType + strAddress;
	}
	if (nAddress > 20000) 
	{
		AfxMessageBox(_T("존재하지 않는 주소값입니다.\n다시 입력해주세요.")); m_edit_device.SetWindowText(_T("")); 
		return; 
	}
	m_MonitorInterface.GetDeviceBlock(m_strDeviceAddress, 10, m_nBlockData);	//입력한 주소부터 10개의 데이터 가져오기
	for (int i = 0; i < 10; i++)	//아이템 10개 생성
	{
		CString nMonitorAddress, strNewDeviceAddress;
		if ((nAddress + i) > 20000) { break; }

		switch (strDeviceType)
		{
		case BIT_DEVICE: nMonitorAddress.Format(_T("%d"), nAddress + i * 16); break;	//주소값이 'M'으로 시작 할 경우 16씩 주소값 증가
		case WORD_DEVICE: nMonitorAddress.Format(_T("%d"), nAddress + i); break;		//주소값이 'D'로 시작 할 경우 1씩 주소값 증가
		}
		strNewDeviceAddress = strDeviceType + nMonitorAddress;		//'M', 'D'와 증가시킨 값 합치기

		m_list_buffermemory.InsertItem(i, strNewDeviceAddress);		//0번 Column의 값을 주소값으로 Item 추가
	}	
	UpdateListData();												//1, 2번 Column 값 Setting
}

void CPLCCommDlg::UpdateListData()	//UPDATE 데이터
{
	CString stroutput1, stroutput2;	//stroutput1 : binary변환값, stroutput2 : 10진수, 16진수, 문자열 값
	for (int i = 0; i < m_list_buffermemory.GetItemCount(); i++)	//ListControl에 추가되어있는 Item의 수 만큼 반복
	{
		stroutput1 = m_ConvertCount.ConvertBinary(m_nBlockData[i]);
		switch (m_iComboIndex)		//Display에 설정되어있는 값에 맞는 형식으로 Value값 형식 변환
		{
		case DEC_ITEM: stroutput2.Format(_T("%d"), m_nBlockData[i]);				break;
		case HEX_ITEM: stroutput2.Format(_T("%04x"), m_nBlockData[i]);			break;
		case STR_ITEM: stroutput2 = m_ConvertCount.ConvertChar(m_nBlockData[i]);	break;
		}
		m_list_buffermemory.SetItemText(i, 1, stroutput1);
		m_list_buffermemory.SetItemText(i, 2, stroutput2);
	}
}

void CPLCCommDlg::OnBnClickedBtnStop()	//Stop Monitor 버튼을 눌렀을 경우
{
	KillTimer(1);					//Timer 종료
	SetButtonStates(false, true);
	m_bTimerRunning = false;
	GetDlgItem(IDC_STATIC_STATE)->ShowWindow(SW_HIDE);
}

void CPLCCommDlg::OnTimer(UINT_PTR nIDEvent)	//Timer
{
	GetDlgItem(IDC_STATIC_STATE)->ShowWindow(m_bIsShowing ? SW_HIDE : SW_SHOW);
	m_bIsShowing = !m_bIsShowing;												//true <-> false 변환
	
	m_MonitorInterface.GetDeviceBlock(m_strDeviceAddress, m_list_buffermemory.GetItemCount(), m_nBlockData);		//아이템 10개의 값 다시 가져오기
	UpdateListData();															//list에 있는 값 Update
	CDialogEx::OnTimer(nIDEvent);
}

void CPLCCommDlg::OnNMDblclkListBuffermemory(NMHDR* pNMHDR, LRESULT* pResult)	//List의 Item이 더블클릭 되었을 경우
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int nListIndex = pNMItemActivate->iItem;									// 더블클릭한 아이템의 인덱스

	if (nListIndex != -1)
	{
		CString strSetAddress(m_list_buffermemory.GetItemText(nListIndex, 0));	//클릭한 Item의 0번째 열(주소값)을 가져오기
		WriteDlg writedlg(m_MonitorInterface, strSetAddress);
		writedlg.DoModal();														//WriteInterface의 Dialog를 모달로 열기
	}
	*pResult = 0;
}

void CPLCCommDlg::OnBnClickedBtnChange()				//Change 버튼이 눌렸을 경우
{
	if(!m_MonitorInterface.DeviceState()) { AfxMessageBox(_T("연결이 되어있지 않습니다.")); return; }

	CString szUpdateCycle;								//입력한 Update 주기 값 가져오기
	m_edit_update.GetWindowText(szUpdateCycle);
	if (szUpdateCycle.IsEmpty()) { szUpdateCycle = "30"; }	//입력이 안되어있을 경우 30ms로 설정
	m_nTimerCycle = _ttoi(szUpdateCycle);

	if (m_bTimerRunning) { KillTimer(1); }				//Timer가 설정되어있을 경우 Timer 종료
	SetTimer(1, m_nTimerCycle, NULL);			//입력한 Update 주기로 Timer시작
}

void CPLCCommDlg::OnCbnCloseupComboDisplay()	//ComboBox의 Index가 변경되었을 경우
{
	m_iComboIndex = m_combo_display.GetCurSel();
}

void CPLCCommDlg::SetButtonStates(bool openEnabled, bool startEnabled)	//버튼의 활성화 변환
{
	m_btn_open.EnableWindow(openEnabled);
	m_btn_close.EnableWindow(!openEnabled);
	m_btn_start.EnableWindow(startEnabled);
	m_btn_stop.EnableWindow(!startEnabled);
}

BOOL CPLCCommDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) // Enter 키 입력시 실행
	{
		if (GetDlgItem(IDC_EDIT_DEVICE) == GetFocus()) { OnBnClickedBtnStart(); }
		else if (GetDlgItem(IDC_EDIT_UPDATECYCLE) == GetFocus()) { OnBnClickedBtnChange(); }
		return false; 
	} 
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) // ESC 키 입력시 실행
	{
		SendMessage(WM_CLOSE, 0, 0);
	}
	return CDialog::PreTranslateMessage(pMsg);
}