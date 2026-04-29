#pragma once


// CManualIndexDlg 대화 상자입니다.

class CManualIndexDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualIndexDlg)

public:
	CManualIndexDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualIndexDlg();

	CGroupCS	m_Group[1];
	CStaticCS	m_stcAxisPos[2];
	CButtonCS	m_BtnIndexR[4];

	CLedCS		m_LedIndexPos[3];

	CButtonCS	m_BtnIndexIO[2];
	CLedCS		m_LedIndexIO[2];

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MANUAL_MAIN_INDEX_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	CString m_strLog;
	void Initial_Controls();

protected:
	CString m_strTemp;
	
public:
	

public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	
};
