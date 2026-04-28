// ManualLoadDlg.h : 헤더 파일
//
#pragma once

// CManualLoadDlg 대화 상자입니다.

class CManualLoadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualLoadDlg)

public:
	CManualLoadDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualLoadDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MANUAL_LOAD_DLG };
	CGroupCS	m_Group[9];
	CLabelCS	m_Label[6];
	
	CStaticCS	m_stcAxisPos[4];

	CButtonCS	m_BtnFeederX[4];
	CButtonCS	m_BtnFeederY[4];
	CButtonCS	m_BtnFeederIO[4];
	CLedCS		m_LedFeederIO[7];
	
	CButtonCS	m_BtnPickerY[3];
	CButtonCS	m_BtnPickerZ[3];
	CButtonCS	m_BtnPickerIO[4];
	CLedCS		m_LedPickerIO[5];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	
	afx_msg void OnBtnFeederXClick(UINT nID);
	afx_msg void OnBtnFeederYClick(UINT nID);
	afx_msg void OnBtnFeederIOClick(UINT nID);

	afx_msg void OnBtnPickerYClick(UINT nID);
	afx_msg void OnBtnPickerZClick(UINT nID);
	afx_msg void OnBtnPickerIOClick(UINT nID);
	
	private:
	CString m_strLog;
	void Initial_Controls();

public:
	void Display_Status();
};
