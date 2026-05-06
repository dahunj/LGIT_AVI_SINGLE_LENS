// SetupMoveTab3Dlg.h : 헤더 파일
//
#pragma once

// CSetupMoveTab3Dlg 대화 상자입니다.

class CSetupMoveTab3Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupMoveTab3Dlg)

public:
	CSetupMoveTab3Dlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSetupMoveTab3Dlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SETUP_MOVE_TAB3_DLG };
	CGroupCS	m_Group[1];
	CLabelCS	m_Label[5];

	CStaticCS	m_stcMainIndexR[5];
	//CStaticCS	m_stcTransStageX[2];
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	
	afx_msg void OnStcMainIndexRClick(UINT nID);
	//afx_msg void OnStcTransStageZClick(UINT nID);
	

private:
	void Initial_Controls();
	void Display_MoveData();

public:
	void Save_MoveData();
	void Cancel_MoveData();
};

///////////////////////////////////////////////////////////////////////////////
