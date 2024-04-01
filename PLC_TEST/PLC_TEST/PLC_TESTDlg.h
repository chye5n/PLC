
// PLC_TESTDlg.h: 헤더 파일
//
#include "PlcInterface.h"

#pragma once


// CPLCTESTDlg 대화 상자
class CPLCTESTDlg : public CDialogEx
{
// 생성입니다.
public:
	CPLCTESTDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PLC_TEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	PlcInterface	m_PlcInterface;
	


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOepn();
	afx_msg void OnBnClickedButtonWrite();
	CEdit m_return;
	afx_msg void OnBnClickedButtonClose();
	CEdit m_output;
	afx_msg void OnBnClickedButtonRead();
	CEdit m_devicename;
	CEdit m_devicevalue;
	CEdit m_devicelength;
	CButton m_radio16bit;
	CButton m_radio32bit;
};
