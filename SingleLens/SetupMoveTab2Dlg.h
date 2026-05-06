// SetupMoveTab2Dlg.h : 헤더 파일
//
#pragma once

// CSetupMoveTab2Dlg 대화 상자입니다.

class CSetupMoveTab2Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupMoveTab2Dlg)

public:
	CSetupMoveTab2Dlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSetupMoveTab2Dlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SETUP_MOVE_TAB2_DLG };
	CGroupCS	m_Group[9];
	CLabelCS	m_Label[45];

	CStaticCS	m_stcTopInspectX[5];
	CStaticCS	m_stcTopInspectY[5];
	CStaticCS	m_stcTopInspectZ[5];
	CStaticCS	m_stcBtmInspectX[5];
	CStaticCS	m_stcBtmInspectY[5];
	CStaticCS	m_stcBtmInspectZ[5];
	CStaticCS	m_stcMarkUnitX[5];
	CStaticCS	m_stcMarkUnitY[5];
	CStaticCS	m_stcMarkUnitZ[5];
	
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnStcTopInspectXClick(UINT nID);
	afx_msg void OnStcTopInspectYClick(UINT nID);
	afx_msg void OnStcTopInspectZClick(UINT nID);
	afx_msg void OnStcBtmInspectXClick(UINT nID);
	afx_msg void OnStcBtmInspectYClick(UINT nID);
	afx_msg void OnStcBtmInspectZClick(UINT nID);
	afx_msg void OnStcMarkUnitXClick(UINT nID);
	afx_msg void OnStcMarkUnitYClick(UINT nID);
	afx_msg void OnStcMarkUnitZClick(UINT nID);
	
private:
	void Initial_Controls();
	void Display_MoveData();

public:
	void Save_MoveData();
	void Cancel_MoveData();
};

///////////////////////////////////////////////////////////////////////////////
