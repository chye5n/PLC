
// PLCCommDlg.h: 헤더 파일
//

#pragma once
#include "MonitorInterface.h"
#include "ConvertCount.h"
#include "WriteDlg.h"

#define DEC_ITEM	 0
#define HEX_ITEM	 1
#define STR_ITEM	 2
#define WORD_DEVICE 'D'
#define BIT_DEVICE	'M'

// CPLCCommDlg 대화 상자
class CPLCCommDlg : public CDialogEx
{
// 생성입니다.
public:
	CPLCCommDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PLCCOMM_DIALOG };
#endif

private:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	MonitorInterface m_MonitorInterface;
	ConvertCount m_ConvertCount;

// 구현입니다.
private:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	short m_nBlockData[11] = { 0, };
	bool m_bTimerRunning = false;
	bool m_bIsShowing = true;
	int m_iComboIndex = 0;
	int m_nTimerCycle = 30;
	CString m_strDeviceAddress;
	
public:
	afx_msg void OnBnClickedBtnOpen();			//Open 버튼
	afx_msg void OnBnClickedBtnClose();			//Close 버튼
	afx_msg void OnBnClickedBtnStart();			//Start 버튼
	afx_msg void OnBnClickedBtnStop();			//Stop 버튼
	afx_msg void OnTimer(UINT_PTR nIDEvent);	//Timer
	afx_msg void OnNMDblclkListBuffermemory(NMHDR* pNMHDR, LRESULT* pResult);	//List 더블 클릭
	afx_msg void OnBnClickedBtnChange();		//Change버튼
	afx_msg void OnCbnCloseupComboDisplay();	//Display ComboBox 닫았을때

	void ListItemInsert(CString strDeviceAddress);
	void UpdateListData();
	void SetButtonStates(bool openEnabled, bool startEnabled);
	
	CListCtrl m_list_buffermemory;
	CEdit m_edit_device;
	CEdit m_edit_update;
	CComboBox m_combo_display;
	CButton m_btn_start;
	CButton m_btn_stop;
	CButton m_btn_open;
	CButton m_btn_close;
};
