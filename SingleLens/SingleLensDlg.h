// CME8000Dlg.h : 헤더 파일
//
#pragma once

#define TIMER_DATE_TIME		0
#define TIMER_TOWER_FLKR	1
#define TIMER_BUZZER_FLKR	2

#define TIMER_DOOR_LOCK			8

#define EXIT_SYSTEM_NONE	0
#define EXIT_SYSTEM_AJIN	1
#define EXIT_SYSTEM_BARCODE	2
#define EXIT_SYSTEM_MODEL	3


#define TIMER_LOAD_OPEN_FLKR	4
#define TIMER_LOAD_RUN_FLKR		5
#define TIMER_UNLOAD_OPEN_FLKR	6
#define TIMER_UNLOAD_RUN_FLKR	7


// CSingleLensDlg 대화 상자
class CSingleLensDlg : public CDialogEx
{
// 생성입니다.
public:
	CSingleLensDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CME8000_DIALOG };
	CPictureCS	m_imgLgLogo;
	CPictureCS	m_picMainLogo;
	CStaticCS	m_stcMainEquip;
	CStaticCS	m_stcMainMode;
	CStaticCS	m_stcMainOpEng;
	CStaticCS	m_stcMainDate;
	CStaticCS	m_stcMainTime;
	CStaticCS	m_stcMainVer;
	CStaticCS	m_stcMainTower[3];
	CPictureCS	m_picModeBack;
	CButtonCS	m_btnMainOperator;
	CRadioCS	m_rdoMainParm;
	CRadioCS	m_rdoMainWork;
	CRadioCS	m_rdoMainManual;
	CRadioCS	m_rdoMainSetup;
	CRadioCS	m_rdoMainProhibit;
	CButtonCS	m_btnMainMonitor;
	CButtonCS	m_btnMainExit;
	CButtonCS	m_btnMainIO;
	CButtonCS	m_btnMainAlarm;

	DWORD	m_dwSetTimer;	// 가동률 로그 삽입을 위해 추가

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnMainOperator();
	afx_msg void OnBnClickedRdoMainParam();
	afx_msg void OnBnClickedRdoMainWork();
	afx_msg void OnBnClickedRdoMainManual();
	afx_msg void OnBnClickedRdoMainSetup();
	afx_msg void OnBnClickedRdoMainProhibit();
	afx_msg void OnBnClickedBtnMainMonitor();
	afx_msg void OnBnClickedBtnMainIO();
	afx_msg void OnBnClickedBtnMainAlarm();
	afx_msg void OnBnClickedBtnMainExit();
	afx_msg void OnStnClickedStcMainVer();
	afx_msg void OnDblclkStcMainEquip();

private:
	CBitmap	m_bmpLgLogo;

	BOOL m_bInsideLight;	// Y0008 : Inside Light
	BOOL m_bTowerOn;
	BOOL m_bBuzzerOn;

	BOOL	m_bLampOnLdOpen;
	BOOL	m_bLampOnLdRun;
	BOOL	m_bLampOnUldOpen;
	BOOL	m_bLampOnUldRun;

	DWORD	m_dwEquipRunStart;
	DWORD	m_dwEquipProcTime;	// MachineERROR 로그 사용 (2018.06.05)
	CString m_strEquipEvent;	// MachineERROR 로그 사용 (2018.07.18)

	BOOL	m_bScreenOff;
	DWORD	m_dwScreenTime;

	BOOL	m_bNoWorkPopup;
	DWORD	m_dwNoWorkTime;

private:
	void Initial_Controls();
	void Hide_ModeWindows(int nMode, int nPreMode);

public:
	void Set_CurrentMode(int nMode);
	void Set_CurrentState(int nState);

	void Set_InsideLight();
	void Set_TowerFlicker(BOOL bEnable);
	void Set_BuzzerFlicker(BOOL bEnable);

	void Set_LampFlicker_LdOpen(BOOL bEnable);
	void Set_LampFlicker_LdRun(BOOL bEnable);
	void Set_LampFlicker_UldOpen(BOOL bEnable);
	void Set_LampFlicker_UldRun(BOOL bEnable);
	
	void Enable_ModeButton(BOOL bEnable);

	void Display_EquipName();
	void Display_DateTime();
	void Exit_System(int nExitNo);

	void Global_Initial();

	void Set_EquipRunStart();
	void Save_EquipRunTime();
	void Clear_EquipRunTime();

	

	void Set_LotErrorLog(CString sEvent, int nErrCode, CString sMessage, int nPNo=0);

	void Set_LotStateTime();
	void Set_DoorLock();
	void Set_NoWork();
};

///////////////////////////////////////////////////////////////////////////////
