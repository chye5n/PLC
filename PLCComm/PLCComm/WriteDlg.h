#pragma once
#include "afxdialogex.h"
#include "MonitorInterface.h"
#include "ConvertCount.h"

#define BIT_OFF		0
#define BIT_ON		1
#define BIT_TOGGLE	2
#define WORD_DEVICE 'D'
#define BIT_DEVICE 'M'

// WriteInterface 대화 상자
class WriteDlg : public CDialog
{
	DECLARE_DYNAMIC(WriteDlg)

public:
	WriteDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	WriteDlg(MonitorInterface MonitorInterface, CString DeviceAdress, CWnd* pParent = nullptr);
	virtual ~WriteDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WRITE_DIALOG };
#endif
private:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	
	MonitorInterface m_MonitorInterface;		//MonitorInterface의 생성자 객체
	ConvertCount m_ConvertCount;
	CString m_DeviceAddress;					//들어온 주소값

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedBtnOn();
	afx_msg void OnBnClickedBtnOff();
	afx_msg void OnBnClickedBtnToggle();
	afx_msg void OnBnClickedBtnSet();
	
	void BitOn_Off(short nbitData);

	CEdit m_edit_worddevice;
	CEdit m_edit_bitdevice;
	CEdit m_edit_value;
	CButton m_radio_dec;
	CButton m_radio_str;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
