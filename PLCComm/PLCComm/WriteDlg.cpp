// WriteDlg.cpp: 구현 파일
//

#include "pch.h"
#include "PLCComm.h"
#include "afxdialogex.h"
#include "WriteDlg.h"

// WriteDlg 대화 상자
IMPLEMENT_DYNAMIC(WriteDlg, CDialog)

WriteDlg::WriteDlg(CWnd* pParent)
{
}

//MonitorInterface의 생성자와 클릭한 주소값을 매개변수로 받음
WriteDlg::WriteDlg(MonitorInterface MonitorInterface, CString DeviceAdress, CWnd* pParent)
	: CDialog(IDD_WRITE_DIALOG, pParent), m_DeviceAddress("")
{
	m_MonitorInterface = MonitorInterface;	//받은 생성자 객체 저장
	m_DeviceAddress = DeviceAdress;			//클릭한 주소값 저장
}

WriteDlg::~WriteDlg()
{
}

void WriteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_BITDEVICE, m_edit_bitdevice);
	DDX_Control(pDX, IDC_EDIT_WORDDEVICE, m_edit_worddevice);
	DDX_Control(pDX, IDC_EDIT_VALUE, m_edit_value);
	DDX_Control(pDX, IDC_RADIO_DEC, m_radio_dec);
	DDX_Control(pDX, IDC_RADIO_STR, m_radio_str);
}

BOOL WriteDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_DeviceAddress[0] == WORD_DEVICE) { m_edit_worddevice.SetWindowText(m_DeviceAddress); }	//주소값이 'D'로 시작할 경우 Word Device에 주소값 입력
	if (m_DeviceAddress[0] == BIT_DEVICE) { m_edit_bitdevice.SetWindowText(m_DeviceAddress); }		//주소값이 'M'으로 시작할 경우 Bit Device에 주소값 입력
	((CButton*)GetDlgItem(IDC_RADIO_DEC))->SetCheck(TRUE);											//10진수 RadioButton 선택
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

BEGIN_MESSAGE_MAP(WriteDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_SET, &WriteDlg::OnBnClickedBtnSet)
	ON_BN_CLICKED(IDC_BTN_ON, &WriteDlg::OnBnClickedBtnOn)
	ON_BN_CLICKED(IDC_BTN_OFF, &WriteDlg::OnBnClickedBtnOff)
	ON_BN_CLICKED(IDC_BTN_TOGGLE, &WriteDlg::OnBnClickedBtnToggle)
END_MESSAGE_MAP()

// WriteInterface 메시지 처리기
//ON 버튼을 눌렀을 경우
void WriteDlg::OnBnClickedBtnOn()
{
	BitOn_Off(BIT_ON);		//값 1로 변환
}

//OFF 버튼을 눌렀을 경우
void WriteDlg::OnBnClickedBtnOff()
{
	BitOn_Off(BIT_OFF);		//값 0으로 변환
}

//Toggle 버튼을 눌렀을 경우
void WriteDlg::OnBnClickedBtnToggle()
{
	BitOn_Off(BIT_TOGGLE);	//값 Toggle
}

//Set 버튼을 눌렀을 경우
void WriteDlg::OnBnClickedBtnSet()
{
	CString strDeviceAddress, strValue;							//Word Device의 주소값, Value 값 가져오기
	m_edit_worddevice.GetWindowText(strDeviceAddress);
	m_edit_value.GetWindowText(strValue);
	if ((strDeviceAddress[0] != WORD_DEVICE) || (m_ConvertCount.AlphaCount(strDeviceAddress) > 1))
	{ AfxMessageBox(_T("주소값을 다시 확인해주세요")); return; }//주소값이 'D'로 시작하지 않거나 문자가 2개 이상일 경우 return
	short nData;
	if(m_radio_dec.GetCheck() == 1)								//Value값 int형으로 변환, 문자열일 경우에는 아스키 코드값으로 변환
	{
		if (m_ConvertCount.AlphaCount(strValue) > 0) { AfxMessageBox(_T("10진수 값으로 입력해주세요")); m_edit_value.SetWindowText(_T("")); return; }
		nData = _ttoi(strValue);
		if ((nData < 0) || (nData > 65535)) { AfxMessageBox(_T("0 ~ 65535의 숫자로 다시 입력해주세요")); m_edit_value.SetWindowText(_T("")); return; }
	}
	else
	{
		if (strValue.GetLength() > 2) { AfxMessageBox(_T("2글자까지만 입력해주세요")); m_edit_value.SetWindowText(_T("")); return; }
		BYTE upperByte = (strValue.GetLength() == 2) ? (BYTE)(strValue[1]) : (BYTE)(strValue[0]);
		BYTE lowerByte = (strValue.GetLength() == 2) ? (BYTE)(strValue[0]) : 0;

		nData = lowerByte * 256 + upperByte;
	}
	m_MonitorInterface.SetDevice(strDeviceAddress, nData);		//입력한 값 전달
	m_edit_value.SetWindowText(_T(""));
}

//Bit값 변환
void WriteDlg::BitOn_Off(short nbitData)
{
	CString strDeviceAddress;
	m_edit_bitdevice.GetWindowText(strDeviceAddress);	//Bit Device의 주소값 가져오기
	if (!(strDeviceAddress[0] == BIT_DEVICE) || (m_ConvertCount.AlphaCount(strDeviceAddress) > 1))
	{ AfxMessageBox(_T("주소값을 다시 확인해주세요")); return; }//주소값이 'M'로 시작하지 않거나 문자가 2개 이상일 경우 return

	if(nbitData == BIT_TOGGLE)
	{
		short nData;
		m_MonitorInterface.GetDevice(strDeviceAddress, nData);	//해당 주소값에 저장되어있는 값 가져오기
		nbitData = (nData == 0) ? 1 : 0;
	}
	m_MonitorInterface.SetDevice(strDeviceAddress, nbitData); 	//해당 주소값에 nbitData의 값 전달
}

BOOL WriteDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)	// Enter 키 입력시 실행
	{
		if (GetDlgItem(IDC_EDIT_VALUE) == GetFocus()) { OnBnClickedBtnSet(); }
		return false;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) // ESC 키 입력시 실행
	{
		EndDialog(IDCANCEL);
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
