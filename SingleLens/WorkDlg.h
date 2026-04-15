// WorkDlg.h : 헤더 파일
//
#pragma once

#include "WorkInfoDlg.h"
#include "afxwin.h"

#define UM_UPDATE_MODEL			WM_USER+1
#define UM_UPDATE_TRAY_INFO		WM_USER+2
#define UM_UPDATE_BARCODE		WM_USER+3
#define UM_RESET_CYCLE_STOP		WM_USER+4
#define UM_UPDATE_UPH			WM_USER+5
#define UM_VISION_RESULT		WM_USER+6
#define UM_LOT_START_END		WM_USER+7
#define UM_INDEX_TACK			WM_USER+8
#define UM_SHOW_MSG				WM_USER+9
#define UM_UPDATE_LOADCELL		WM_USER+10

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
	CStaticCS		m_stcZigId[60];
	CStaticCS		m_stcLensCnt[60];



	//old 

	CGroupCS		m_Group[10];
	CLabelCS		m_Label[7];
	CGroupCS		m_grpLot[2];
	CLabelCS		m_lblLot[6];

	

	CPictureCS		m_imgEquipment;
	CPictureCS		m_picUphBack;
	CLedCS			m_ledEquipOption[7];
	CComboCS		m_cboStartIndexJig;
	CStaticCS		m_stcLoadNo[6];
	CStaticCS		m_stcAssyNo[6];
	CStaticCS		m_stcTransNo[6];
	CStaticCS		m_stcTStageNo[6];
	CStaticCS		m_stcUnloadNo[6];
	CLedCS			m_ledIndexDone[3];
	CStaticCS		m_stcIndexPos;

	CRadioCS		m_rdoWorkStart;
	CRadioCS		m_rdoWorkStop;
	CLedCS			m_ledInitComplete;
	CLedCS			m_ledLotLoadEnable;
	CCheckCS		m_chkCycleStop;
	CCheckCS		m_chkMesUse;
	CPictureCS		m_picTrayBack[6];

	CStaticCS		m_stcLoadTrayCount;
	CStaticCS		m_stcCapTrayCount;
	CStaticCS		m_stcShipTrayCount;
	CStaticCS		m_stcNGTrayCount;

	CGridCS			m_grdLoadTray;
	CGridCS			m_grdCapTray;
	CGridCS			m_grdShipTray;
	CGridCS			m_grdNGTray;
	CStaticCS		m_stcWorkCase[10];
	CStaticCS		m_stcPortNo[12];
	CStaticCS		m_stcTakt[4];
	CStaticCS		m_stcUph[4];
	CStaticCS		m_stcDay[2];
	CLedCS			m_ledVisionStatus[2];
	
	CButtonCS		m_btnMesCancel;



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	//new 
	afx_msg void OnStcLotIdClick(UINT nID);
	afx_msg void OnStcLensCountClick(UINT nID);

	

	//old 
	

	afx_msg void OnStnClickedLblLot0();
	afx_msg void OnStnClickedLblLot3();
	
	afx_msg void OnBnClickedRdoWorkStart();
	afx_msg void OnBnClickedRdoWorkStop();


	afx_msg void OnBnClickedChkCycleStop();
	afx_msg void OnBnClickedChkMesUse();
	afx_msg LRESULT OnUpdateModel(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateTrayInfo(WPARAM nTray, LPARAM lParam);
	afx_msg LRESULT OnUpdateBarcode(WPARAM wParam, LPARAM lParam);
	
	afx_msg LRESULT OnResetCycleStop(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateUph(WPARAM wParam, LPARAM lParam);
	
	afx_msg LRESULT OnLotStartEnd(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnIndexTack(WPARAM wParam, LPARAM lParam);	//AHN
	afx_msg LRESULT OnShowMsg(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedMesCancel();

private:


	CBitmap	m_bmpEquipment;

	BOOL	m_bAutoRunning;
	BOOL	m_bCycleStopRun;


	int		m_nGroupNo;

	int		m_nBuffChange;

	BOOL	m_bMesManual;

	int		m_nTimer;
	BOOL	m_bLoadSw3On;
	BOOL	m_bCapSw1On;
	BOOL	m_bCapSw2On;
	BOOL	m_bUnloadSw1On;


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

	void Get_LotInfo(int nPx);
	void Set_LotInfo(int nPx);

	


	void MachineStopLog(CString sType, CString sMsg="");
	void Change_Model();



	afx_msg void OnBnClickedBtnSimul1();
};

extern CWorkDlg g_dlgWork;

///////////////////////////////////////////////////////////////////////////////
