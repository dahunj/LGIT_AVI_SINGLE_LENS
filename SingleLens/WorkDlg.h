// WorkDlg.h : 헤더 파일
//
#pragma once

#include "WorkInfoDlg.h"
#include "afxwin.h"
#include "AJinDefine.h"


#define UM_UPDATE_MODEL			WM_USER+1
#define UM_UPDATE_MZ_INFO		WM_USER+2
#define UM_UPDATE_BARCODE		WM_USER+3
#define UM_RESET_CYCLE_STOP		WM_USER+4
#define UM_UPDATE_UPH			WM_USER+5
#define UM_VISION_RESULT		WM_USER+6
#define UM_LOT_START_END		WM_USER+7
#define UM_INDEX_TACK			WM_USER+8
#define UM_SHOW_MSG				WM_USER+9
#define UM_UPDATE_LOADCELL		WM_USER+10
#define UM_UPDATE_VISION_INFO		WM_USER+11

// CWorkDlg 대화 상자입니다.

class CWorkDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWorkDlg)

public:
	CWorkDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CWorkDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_WORK_DLG };

	//new 
	CPictureCS		m_picUphBack;
	
	CRadioCS		m_rdoSelectNo[40]; // 20 ~ 59 
	CStaticCS		m_stcMZID[6];
	CStaticCS		m_stcZigID[60];
	CStaticCS		m_stcLensCnt[60];

	CGridCS			m_grdLoadMZ;
	CGridCS			m_grdRdyMZ;

	CGridCS			m_grdTopVision;
	CGridCS			m_grdBtmVision;
	CGridCS			m_grdMarking;


	CGroupCS		m_Group[10];
	CLabelCS		m_Label[7];
	CGroupCS		m_grpLot[2];
	CLabelCS		m_lblLot[6];	
	
	CComboCS		m_cboStartIndexJig;

	CLedCS			m_ledIndexDone[7];
	CStaticCS		m_stcIndexPos;

	CRadioCS		m_rdoWorkStart;
	CRadioCS		m_rdoWorkStop;
	CLedCS			m_ledInitComplete;

	CCheckCS		m_chkCycleStop;

	CPictureCS		m_picTrayBack[6];
		
	CStaticCS		m_stcWorkCase[10];
	CStaticCS		m_stcPortNo[12];
	CStaticCS		m_stcTakt[4];
	CStaticCS		m_stcUph[4];
	CStaticCS		m_stcDay[2];
	CLedCS			m_ledVisionStatus[2];
	CLedCS			m_ledEquipOption[2];
	
	CButtonCS		m_btnMesCancel;

	CStaticCS		m_stcTrayNo[7];
	CLedCS			m_ledMZDetect[11];
	
	CStaticCS		m_stcHidden;
	CCheckCS		m_chkNoTrayMode;
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnStcMZIDClick(UINT nID);
	afx_msg void OnStcZigIDClick(UINT nID);
	afx_msg void OnStcLensCountClick(UINT nID);	

	afx_msg void OnBnClickedRdoZigID(UINT nID);
	afx_msg void OnBnClickedRdoMZID(UINT nID);

	afx_msg void OnStnClickedLblLot0();
	afx_msg void OnStnClickedLblLot3();
	
	afx_msg void OnBnClickedRdoWorkStart();
	afx_msg void OnBnClickedRdoWorkStop();


	afx_msg void OnBnClickedChkCycleStop();

	afx_msg LRESULT OnUpdateModel(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateMZInfo(WPARAM nTray, LPARAM lParam);
	afx_msg LRESULT OnUpdateVisionInfo(WPARAM nVision, LPARAM lParam);
	afx_msg LRESULT OnUpdateBarcode(WPARAM wParam, LPARAM lParam);
	
	afx_msg LRESULT OnResetCycleStop(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateUph(WPARAM wParam, LPARAM lParam);
	
	afx_msg LRESULT OnLotStartEnd(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnIndexTack(WPARAM wParam, LPARAM lParam);	//AHN
	afx_msg LRESULT OnShowMsg(WPARAM wParam, LPARAM lParam);
	
	CBitmap m_bmpBg;
	CRect   m_rcBgArea;   // IDC_STATIC_BG의 위치/크기 저장

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

private:

	BOOL	m_bShowWindow;

	BOOL	m_bAutoRunning;
	BOOL	m_bCycleStopRun;

	int		m_nGroupNo;
	int		m_nBuffChange;
	BOOL	m_bMesManual;

	int		m_nTimer;
	BOOL	m_bLdOpenSwOn;
	BOOL	m_bLdRunSwOn;
	BOOL	m_bUldOpenSwOn;
	BOOL	m_bUldRunSwOn;

	BOOL	m_bLoadCVRun;
	BOOL	m_bUnloadCVRun;
	

	DY_DATA_00 *m_pDY00;
	DY_DATA_01 *m_pDY01;
	DY_DATA_02 *m_pDY02;
	DY_DATA_03 *m_pDY03;


private:
	BOOL Work_Start();
	void Initial_Controls();
	void Initial_Grid(CGridCS *pGrid, int nRows, int nCols, int nNoDir=0);
	void Check_Lamp();
	void Display_Status();
	void Reset_AlarmLog();

public:
	void Set_AutoRun(BOOL bAutoRun);
	void Set_AutoRunStatus(BOOL bAutoRun) { m_bAutoRunning = bAutoRun; }
	void Set_State(int nState);
	void Enable_UserInput(int nNo, BOOL bEnable);
	
	int		SearchMZElevInfo(int nNo);
	int		SearchMZCVInfo();
	void	TransferMZInfo(int nFrom, int nTo, int nDir);
		
	int 	SearchZigInfo(int nMZNo);
	int		SearchLensCntInfo(int nMZNo);

	int		CheckZigExistInMZ(int nMZ, int nSlot);
	
	void Get_MZInfo(int nMZNo);
	void Set_MZInfo(int nMZNo);
	
	void MachineStopLog(CString sType, CString sMsg="");
	void Change_Model();

	afx_msg void OnBnClickedBtnSimul1();	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnStnClickedStcHidden();
	afx_msg void OnBnClickedChkNoTray();
	afx_msg void OnBnClickedBtnLight();
};



extern CWorkDlg g_dlgWork;

///////////////////////////////////////////////////////////////////////////////
