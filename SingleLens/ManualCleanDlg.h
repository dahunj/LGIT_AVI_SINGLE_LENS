// ManualCleanDlg.h : 헤더 파일
//
#pragma once

// CManualCleanDlg 대화 상자입니다.

class CManualCleanDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualCleanDlg)

public:
	CManualCleanDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualCleanDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MANUAL_CLEAN_TOP_DLG };
	CGroupCS	m_Group[14];
	CLabelCS	m_Label[8];
	CStaticCS	m_stcAxisPos[3];

	CButtonCS	m_BtnCleanerIO[12];
	CLedCS		m_LedCleanerIO[8];

	CButtonCS	m_BtnTopInspectX[4];
	CButtonCS	m_BtnTopInspectY[4];
	CButtonCS	m_BtnTopInspectZ[4];
		
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnBtnCleanerIOClick(UINT nID);
	afx_msg void OnBtnTopInspectXClick(UINT nID);
	afx_msg void OnBtnTopInspectYClick(UINT nID);
	afx_msg void OnBtnTopInspectZClick(UINT nID);
	
private:
	CString m_strLog;
	void Initial_Controls();

public:
	void Display_Status();
};
