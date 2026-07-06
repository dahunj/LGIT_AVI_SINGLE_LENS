// ManualBtmDlg.h : 헤더 파일
//
#pragma once
#include "afxwin.h"

// CManualNgDlg 대화 상자입니다.

class CManualBtmDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualBtmDlg)

public:
	CManualBtmDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualBtmDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_MANUAL_BTM_MARK_DLG };
	CGroupCS	m_Group[16];
	CLabelCS	m_Label[10];

	CStaticCS	m_stcAxisPos[6];

	CButtonCS	m_BtnBtmInspectX[4];
	CButtonCS	m_BtnBtmInspectY[4];
	CButtonCS	m_BtnBtmInspectZ[4];

	CButtonCS	m_BtnMarkUnitX[4];
	CButtonCS	m_BtnMarkUnitY[4];
	CButtonCS	m_BtnMarkUnitZ[4];

	CButtonCS	m_BtnMarkUnitIO[2];
	CLedCS		m_LedMarkUnitIO[3];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	
	afx_msg void OnBtnBtmInspectXClick(UINT nID);
	afx_msg void OnBtnBtmInspectYClick(UINT nID);
	afx_msg void OnBtnBtmInspectZClick(UINT nID);

	afx_msg void OnBtnMarkUnitXClick(UINT nID);
	afx_msg void OnBtnMarkUnitYClick(UINT nID);
	afx_msg void OnBtnMarkUnitZClick(UINT nID);

	afx_msg void OnBtnMarkUnitIOClick(UINT nID);


private:
	CString m_strLog;
	void Initial_Controls();

public:
	void Display_Status();


protected:
	int	 m_nScanCase;
	BOOL BtmScan_Run();

	BOOL		m_bThreadBtmScan;
	CWinThread *m_pThreadBtmScan;
	static UINT	Thread_BtmScan(LPVOID lpVoid);
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	CEdit m_Edit_LensNo;
	afx_msg void OnBnClickedBtnLensMoveBtm();
	afx_msg void OnBnClickedBtnLensMoveMark();
};
