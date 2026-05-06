// SetupMoveTab1Dlg.h : 헤더 파일
//
#pragma once

// CSetupMoveTab1Dlg 대화 상자입니다.

class CSetupMoveTab1Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupMoveTab1Dlg)

public:
	CSetupMoveTab1Dlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSetupMoveTab1Dlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SETUP_MOVE_TAB1_DLG };
	CGroupCS	m_Group[5];
	CLabelCS	m_Label[31];

	CStaticCS	m_stcElvZ[10];
	CStaticCS	m_FeedUnitX[5];
	CStaticCS	m_FeederY[5];
	CStaticCS	m_TrayPickerY[5];
	CStaticCS	m_TrayPickerZ[5];
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnStcElvZClick(UINT nID);
	afx_msg void OnStcFeederXClick(UINT nID);
	afx_msg void OnStcFeederYClick(UINT nID);
	afx_msg void OnStcTrayPickerYClick(UINT nID);
	afx_msg void OnStcTrayPickerZClick(UINT nID);


private:
	void Initial_Controls();
	void Display_MoveData();

public:
	void Save_MoveData();
	void Cancel_MoveData();
};

///////////////////////////////////////////////////////////////////////////////
