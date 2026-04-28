// ManualElevDlg.h : 헤더 파일
//
#pragma once

#include "LoopTimer.h"
// CManualElevDlg 대화 상자입니다.

class CManualElevDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualElevDlg)

public:
	CManualElevDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualElevDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MANUAL_ELEV_DLG };
	
	
	CGroupCS	m_Group[17];
	CLabelCS	m_Label[11];

	CStaticCS	m_stcAxisPos[1];

	CLedCS		m_LedLdCVIO[5];
	CCheckCS	m_ChkLdCVIO[3];
	
	CLedCS		m_LedLdCVStopper[4];
	CButtonCS	m_BtnLdCVStopper[4];

	CLedCS		m_LedElevIO[2];
	CCheckCS	m_ChkElevIO[3];

	CLedCS		m_LedElevStopper[8];
	CButtonCS	m_BtnElevStopper[8];

	CButtonCS	m_BtnElevZ[5];
	CButtonCS	m_BtnElevReadyZ[5];

		

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnChkLdCVIOClick(UINT nID);
	afx_msg void OnBtnLdCVStopperClick(UINT nID);

	afx_msg void OnChkElevCVIOClick(UINT nID);
	afx_msg void OnBtnElevCVStopperClick(UINT nID);

	afx_msg void OnBtnElevZClick(UINT nID);
	afx_msg void OnBtnElevReadyZClick(UINT nID);
		 

private:
	CString m_strLog;
	void Initial_Controls();


	/*int				m_nRunCase;
	CLoopTimer		m_tElevLoop;
	BOOL			Manual_ElevatorRun();*/

public:
	void Display_Status();
};
