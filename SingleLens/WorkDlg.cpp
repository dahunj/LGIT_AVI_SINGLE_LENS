// WorkDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "SingleLens.h"
#include "WorkDlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "Common.h"
#include "Inspector.h"
#include "MesAgent.h"

#include "SequenceInit.h"
#include "SequenceMain.h"

#include "OperatorDlg.h"
#include "SingleLensDlg.h"



// CWorkDlg 대화 상자입니다.
CWorkDlg g_dlgWork;

IMPLEMENT_DYNAMIC(CWorkDlg, CDialogEx)

CWorkDlg::CWorkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWorkDlg::IDD, pParent)
{
	
}

CWorkDlg::~CWorkDlg()
{
}

void CWorkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	/*for (int i = 0; i < 10; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);	
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_LBL_LOT_0 + i, m_lblLot[i]);*/

	for (int i = 0; i <40; i++) DDX_Control(pDX, IDC_RDO_MZ_SLOT_NO_20 + i, m_rdoSelectNo[i]);

	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_STC_MZID_0 + i, m_stcMZID[i]);
	for (int i = 0; i < 60; i++) DDX_Control(pDX, IDC_STC_MZ_ZIGID_0 + i, m_stcZigID[i]);
	for (int i = 0; i < 60; i++) DDX_Control(pDX, IDC_STC_MZ_LENS_CNT_0+ i, m_stcLensCnt[i]);


	DDX_Control(pDX, IDC_PIC_UPH_BACK, m_picUphBack);

	DDX_Control(pDX, IDC_RDO_WORK_START, m_rdoWorkStart);
	DDX_Control(pDX, IDC_RDO_WORK_STOP, m_rdoWorkStop);
	DDX_Control(pDX, IDC_LED_INIT_COMPLETE, m_ledInitComplete);
	DDX_Control(pDX, IDC_CHK_CYCLE_STOP, m_chkCycleStop);
	DDX_Control(pDX, IDC_CHK_NO_TRAY, m_chkNoTrayMode);	

	for (int i = 0; i < AUTO_COUNT; i++) DDX_Control(pDX, IDC_STC_WORK_CASE_0 + i, m_stcWorkCase[i]);	
	for (int i = 0; i < 7; i++) DDX_Control(pDX, IDC_LED_INDEX_DONE_0 + i, m_ledIndexDone[i]);
	for (int i = 0; i < 11; i++) DDX_Control(pDX, IDC_LED_MZ_DETECT_0 + i, m_ledMZDetect[i]);
	DDX_Control(pDX, IDC_STC_MAIN_INDEX_POS, m_stcIndexPos);

	DDX_Control(pDX, IDC_GRD_LOAD_MZ, m_grdLoadMZ);
	DDX_Control(pDX, IDC_GRD_UNLOAD_MZ, m_grdRdyMZ);

	DDX_Control(pDX, IDC_GRD_TOP_VISION, m_grdTopVision);
	DDX_Control(pDX, IDC_GRD_BTM_VISION, m_grdBtmVision);
	DDX_Control(pDX, IDC_GRD_MARKING, m_grdMarking);
	

	for (int i = 0; i < 7; i++) DDX_Control(pDX, IDC_STC_TRAY_NO_0 + i, m_stcTrayNo[i]);

	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_TAKT_0 + i, m_stcTakt[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_UPH_0 + i, m_stcUph[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_STC_DAY_0 + i, m_stcDay[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_LED_VISION_STATUS_0 + i, m_ledVisionStatus[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_LED_EQUIP_OPTION_0 + i, m_ledEquipOption[i]);

	DDX_Control(pDX, IDC_LBL_OPER_ID, m_lblOperId);
	DDX_Control(pDX, IDC_STC_OPER_ID, m_stcOperId);
	DDX_Control(pDX, IDC_STC_MES_CONNECT, m_stcMesConnect);
	DDX_Control(pDX, IDC_STC_MES_ONLINE, m_stcMesOnline);

	m_pDY00 = g_objAJinAXL.Get_pDY00();
	m_pDY01 = g_objAJinAXL.Get_pDY01();
	m_pDY02 = g_objAJinAXL.Get_pDY02();
	m_pDY03 = g_objAJinAXL.Get_pDY03();

}

BEGIN_MESSAGE_MAP(CWorkDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_MZID_0, IDC_STC_MZID_5, OnStcMZIDClick )
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_MZ_ZIGID_0, IDC_STC_MZ_ZIGID_59, OnStcZigIDClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_MZ_LENS_CNT_0, IDC_STC_MZ_LENS_CNT_59, OnStcLensCountClick)
	
	ON_STN_CLICKED(IDC_LBL_LOT_0, &CWorkDlg::OnStnClickedLblLot0)
	ON_STN_CLICKED(IDC_LBL_LOT_3, &CWorkDlg::OnStnClickedLblLot3)
		
	ON_BN_CLICKED(IDC_RDO_WORK_START, &CWorkDlg::OnBnClickedRdoWorkStart)
	ON_BN_CLICKED(IDC_RDO_WORK_STOP, &CWorkDlg::OnBnClickedRdoWorkStop)
	ON_BN_CLICKED(IDC_CHK_CYCLE_STOP, &CWorkDlg::OnBnClickedChkCycleStop)

	ON_MESSAGE(UM_UPDATE_MODEL, &CWorkDlg::OnUpdateModel)
	ON_MESSAGE(UM_UPDATE_MZ_INFO, &CWorkDlg::OnUpdateMZInfo)
	ON_MESSAGE(UM_UPDATE_VISION_INFO, &CWorkDlg::OnUpdateVisionInfo)
	ON_MESSAGE(UM_UPDATE_BARCODE, &CWorkDlg::OnUpdateBarcode)
	
	ON_MESSAGE(UM_RESET_CYCLE_STOP, &CWorkDlg::OnResetCycleStop)
	ON_MESSAGE(UM_LOT_START_END, &CWorkDlg::OnLotStartEnd)
	ON_MESSAGE(UM_UPDATE_UPH, &CWorkDlg::OnUpdateUph)

	ON_MESSAGE(UM_INDEX_TACK, &CWorkDlg::OnIndexTack)
	ON_MESSAGE(UM_SHOW_MSG, &CWorkDlg::OnShowMsg)
	ON_BN_CLICKED(IDC_BUTTON1, &CWorkDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CWorkDlg::OnBnClickedButton2)
	
	ON_CONTROL_RANGE(STN_CLICKED, IDC_RDO_MZ_SLOT_NO_20, IDC_RDO_MZ_SLOT_NO_59, OnBnClickedRdoZigID)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_RDO_MZ_ID_0, IDC_RDO_MZ_ID_5, OnBnClickedRdoMZID)	

	ON_BN_CLICKED(IDC_BTN_SIMUL1, &CWorkDlg::OnBnClickedBtnSimul1)
	
	ON_STN_CLICKED(IDC_STC_HIDDEN, &CWorkDlg::OnStnClickedStcHidden)
	ON_BN_CLICKED(IDC_CHK_NO_TRAY, &CWorkDlg::OnBnClickedChkNoTray)
	ON_BN_CLICKED(IDC_BTN_LIGHT, &CWorkDlg::OnBnClickedBtnLight)
	ON_STN_CLICKED(IDC_STC_OPER_ID, &CWorkDlg::OnStnClickedStcOperId)
	ON_BN_CLICKED(IDC_BTN_MES_ONLINE, &CWorkDlg::OnBnClickedBtnMesOnline)
	ON_BN_CLICKED(IDC_BTN_MES_OFFLINE, &CWorkDlg::OnBnClickedBtnMesOffline)
	
	ON_BN_CLICKED(IDC_BTN_MES_CONNECT, &CWorkDlg::OnBnClickedBtnMesConnect)
	ON_BN_CLICKED(IDC_BTN_MES_DISCONNECT, &CWorkDlg::OnBnClickedBtnMesDisconnect)
	ON_BN_CLICKED(IDC_BTN_MES_ABORT, &CWorkDlg::OnBnClickedBtnMesAbort)
	ON_BN_CLICKED(IDC_BTN_IDLE_REPORT, &CWorkDlg::OnBnClickedBtnIdleReport)
END_MESSAGE_MAP()

// CWorkDlg 메시지 처리기입니다.

void CWorkDlg::Initial_Controls() 
{
	CString strText;
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	//for (int i = 0; i < 10; i++) m_Group[i].Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	//for (int i = 0; i < 4; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x80, 0x80, 0x80));

	//for (int i = 0; i < 2; i++) m_grpLot[i].Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	//for (int i = 0; i < 3; i++) m_lblLot[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x20, 0x20, 0x80));
	//for (int i = 3; i < 6; i++) m_lblLot[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x00, 0x80));
	
	Initial_Grid(&m_grdLoadMZ, SLOT_NO_MAX, 1);
	Initial_Grid(&m_grdRdyMZ, SLOT_NO_MAX, 1);

	Initial_Grid(&m_grdTopVision, gData.nLensCntY, gData.nLensCntX);
	Initial_Grid(&m_grdBtmVision, gData.nLensCntY, gData.nLensCntX);
	Initial_Grid(&m_grdMarking, gData.nLensCntY, gData.nLensCntX);
		
	for (int i = 0; i < 7; i++) m_stcTrayNo[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0xFF, 0x00), RGB(0x00, 0x00, 0x00));

	// 비트맵 로드
	m_bmpBg.LoadBitmap(IDB_EQUIP_WORK);

	// 리소스에 있는 static의 위치/크기 가져오기
	CWnd* pWndBg = GetDlgItem(IDC_STATIC_WORKIMAGE);
	if (pWndBg && ::IsWindow(pWndBg->GetSafeHwnd()))
	{
		pWndBg->GetWindowRect(&m_rcBgArea);
		ScreenToClient(&m_rcBgArea);

		// 기준용 static은 숨김
		pWndBg->ShowWindow(SW_HIDE);
	}
	else
	{
		m_rcBgArea.SetRectEmpty();
	}
	m_picUphBack.Init_Ctrl(COLOR_DEFAULT, COLOR_DEFAULT);	
	
	for (int i = 0; i < 7; i++) m_ledIndexDone[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em24);
	for (int i = 0; i < 11; i++) m_ledMZDetect[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em24);
	m_stcIndexPos.Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0xFF, 0x00), RGB(0x00, 0x00, 0x00));

	
	m_rdoWorkStart.Init_Ctrl("바탕", 20, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	m_rdoWorkStop.Init_Ctrl("바탕", 20, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	m_ledInitComplete.Init_Ctrl("바탕", 10, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em24);
	
	m_chkCycleStop.Init_Ctrl("바탕", 10, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
			
	for (int i = 0; i < AUTO_COUNT; i++) m_stcWorkCase[i].Init_Ctrl("바탕", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x40, 0x40));

	for (int i = 0; i < 4; i++) m_stcTakt[i].Init_Ctrl("Arial", 9, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 4; i++) m_stcUph[i].Init_Ctrl("Arial", 9, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 2; i++) m_stcDay[i].Init_Ctrl("Arial", 9, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 2; i++) m_ledVisionStatus[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	
	for (int i = 0; i < 2; i++) m_ledEquipOption[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);

	m_stcMesConnect.Init_Ctrl("바탕", 8, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00));
	m_stcMesOnline.Init_Ctrl("바탕", 10, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00));
	m_lblOperId.Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x20, 0x20, 0x80));
	m_stcOperId.Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, RGB(0xD0, 0xD0, 0xD0));

}

BOOL CWorkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 75, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();
	
	m_bShowWindow = FALSE;

	m_bAutoRunning = FALSE;
	m_nGroupNo = 0;

	gData.bLotEndBeep = FALSE;
	gData.bFirstLotStart = FALSE;


	m_rdoWorkStop.SetCheck(TRUE);
	m_rdoWorkStop.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);

	m_chkNoTrayMode.ShowWindow(SW_HIDE);

	if(gData.bDemoMode)
	{
		
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CWorkDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CWorkDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	
	KillTimer(0);
}

void CWorkDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) 
	{
		Change_Model();	
		
		EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
		CString strText;

		g_objCommon.Locking_MainDoor(FALSE);

		SetTimer(0, 100, NULL);
		SetTimer(1, 5000, NULL);

	}
	else 
	{
		KillTimer(0);	
	}
}

void CWorkDlg::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(0);
	 
	CSingleLensDlg *pMainDlg = (CSingleLensDlg*)AfxGetApp()->GetMainWnd();
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	
	DX_DATA_03 *pDX03 = g_objAJinAXL.Get_pDX03();

	if (pDX03->iStartSw && !m_rdoWorkStart.GetCheck()) 
	{
		g_objLogFile.Save_HandlerLog("[Work Mode] START S/W push");
		m_rdoWorkStart.SetCheck(TRUE);
		//pMainDlg->Set_LotErrorLog("START", 903, "Start");
		g_objLogFile.Save_EfficiencyLog(0, "Run", 903, "Run Start");	//Start

	} 
	else if (pDX03->iStopSw && !m_rdoWorkStop.GetCheck()) 
	{
		g_objLogFile.Save_HandlerLog("[Work Mode] STOP S/W push");
		MachineStopLog("STOP_BUTTON_PUSH");
		m_rdoWorkStop.SetCheck(TRUE);
		//pMainDlg->Set_LotErrorLog("STOP", 904, "Stop");
		g_objLogFile.Save_EfficiencyLog(0, "Stop", 903, "Stop Button Push");	//Stop
	}

	if (pDX03->iResetSw) g_objCommon.Show_Alarm("", STATE_ALARM, FALSE);

	Check_Lamp();
	Display_Status();

	if (m_rdoWorkStart.GetCheck()) {
		if (!m_bAutoRunning)  // First AutoRun
		{		
			if (!g_objSequenceInit.Get_InitComplete()) 
			{ 
				g_objCommon.Show_Error(50); SetTimer(0, 100, NULL); return; 
			}

			if (!Work_Start()) { m_rdoWorkStop.SetCheck(TRUE); SetTimer(0, 100, NULL); return; }

			m_bAutoRunning = TRUE;
			if (gData.bCycleStop && !m_bCycleStopRun) m_bCycleStopRun = TRUE;

		
			g_objMesAgent.Set_EquipState(eEquipState::RUN);	//Run

			g_objCommon.Locking_MainDoor(TRUE);
			pMainDlg->Enable_ModeButton(FALSE);
			pMainDlg->Set_CurrentState(STATE_RUN);
						
			//If it was running before Stop, then run again 
			if (m_bLoadCVRun ) g_objCommon.Set_LoadCVRunCW(); Sleep(5); 
			if (m_bUnloadCVRun) g_objCommon.Set_UnloadCVRunCW(); Sleep(5);
			m_bLoadCVRun = FALSE;
			m_bUnloadCVRun = FALSE;

			g_objSequenceMain.Begin_MainRunThread();
			//g_objInspector.Set_StatusUpdate(VISION_ALL, 2);

		} else {	// Auto Running
			if (!g_objSequenceMain.Is_MainThreadRun()) {
				g_objLogFile.Save_HandlerLog("[Work Mode] Auto STOP");
				pMainDlg->Set_CurrentState(STATE_STOP);
			}
		}

	} else if (m_rdoWorkStop.GetCheck()) {
		if (m_bAutoRunning) {	// First AutoStop
			m_bAutoRunning = FALSE;
			
			m_bLoadCVRun = m_pDY00->oLoadCVRun;
			m_bUnloadCVRun = m_pDY01->oUldCvRun;

			g_objCommon.Set_LoadCVStop();Sleep(5);
			g_objCommon.Set_ElevCVStop();Sleep(5);
			g_objSequenceMain.End_MainRunThread();

			g_objMesAgent.Set_EquipState(eEquipState::DOWN);	//Down
			
			int nState = theApp.Get_MainState();
			if (nState != STATE_ALARM && nState != STATE_ERROR) pMainDlg->Set_CurrentState(STATE_STOP);
			//g_objInspector.Set_StatusUpdate(VISION_ALL, 1);

			m_rdoWorkStart.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
			m_rdoWorkStop.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);

			g_objCommon.Save_MotionPos();

			pMainDlg->Enable_ModeButton(TRUE);
			g_objCommon.Locking_MainDoor(FALSE);

		} else {	// Stop
			int nState = theApp.Get_MainState();
			if (nState != STATE_ERROR) g_objCommon.Check_MainEmgAir();	// Emg & Main Air
		}
	}
	
	SetTimer(0, 100, NULL);
	
	CDialogEx::OnTimer(nIDEvent);
}



/////////////////

void CWorkDlg::OnStcMZIDClick(UINT nID)
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (pEquipData->bUseMES)
	{
		AfxMessageBox(_T("MES사용시 Lot정보 수정할 수 없습니다."));
		return;
	}

	int ID = nID - IDC_STC_MZID_0;

	if (m_rdoWorkStart.GetCheck()) 
	{
		if (gData.nLanguage == 0) g_objCommon.Show_MsgBox(1, "장비 Stop 상태에서 진행이 가능합니다.....");
		else					  g_objCommon.Show_MsgBox(1, "You can proceed with the equipment stopped.");
		return;
	}

	CString strKey, strNew, strMsg;
	if (g_objCommon.Show_KeyPad(strKey) != IDOK) return;

	m_stcMZID[ID].SetWindowText(strKey);

	//if Running, variable gets lensCnt/ if not  gets at Work_Start() 
	if (m_rdoWorkStart.GetCheck())
	{
		gData.sMZID[ID] = strKey;		
	}

	strNew.Format("[Work Mode] MZ ID Input(%d-%s)", ID, strKey);
	g_objLogFile.Save_HandlerLog(strNew);
}


void CWorkDlg::OnStcZigIDClick(UINT nID)
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (pEquipData->bUseMES)
	{
		AfxMessageBox(_T("MES사용시 Lot정보 수정할 수 없습니다."));
		return;
	}

	int ID = nID - IDC_STC_MZ_ZIGID_0;

	if (m_rdoWorkStart.GetCheck()) 
	{
		if (gData.nLanguage == 0) g_objCommon.Show_MsgBox(1, "장비 Stop 상태에서 진행이 가능합니다.....");
		else					  g_objCommon.Show_MsgBox(1, "You can proceed with the equipment stopped.");
		return;
	}

	CString strKey, strNew, strMsg;
	if (g_objCommon.Show_KeyPad(strKey) != IDOK) return;
	/*if (strKey.Find("_") >= 0) {
		if (gData.nLanguage == 0) strMsg.Format("[%s] Lot ID ( _ ) 입력불가...", strKey);
		else					  strMsg.Format("[%s] Lot ID Unable to endter(_)...", strKey);
		g_objCommon.Show_MsgBox(1, strMsg);
		return;
	}*/

	m_stcZigID[ID].SetWindowText(strKey);

	int nShare = 0, nRemainder = 0;
	nShare = ID / 10;
	nRemainder = ID %10;

	//if Running, variable gets lensCnt/ if not  gets at Work_Start() 
	if (m_rdoWorkStart.GetCheck())
	{
		gData.sZigID[nShare][nRemainder] = strKey;		
	}

	strNew.Format("[Work Mode] Zig ID Input(%d-%s)", ID, strKey);
	g_objLogFile.Save_HandlerLog(strNew);

	//OnStcCmsCountSClick(IDC_STC_CMS_COUNT_S_0+ID);	//2018.9.11+
}

void CWorkDlg::OnBnClickedRdoMZID(UINT nID)
{
	int ID = nID - IDC_RDO_MZ_ID_0;

	if (m_rdoWorkStart.GetCheck()) {
		if (gData.nLanguage == 0) AfxMessageBox(_T("장비 Stop 상태에서 진행이 가능합니다....."));
		else					  AfxMessageBox(_T("You can proceed with the equipment stopped."));
		m_rdoSelectNo[ID].SetCheck(FALSE);
		return;
	}

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (pEquipData->bUseMES)
	{
		AfxMessageBox(_T("MES사용시 Lot정보 수정할 수 없습니다."));
		m_rdoSelectNo[ID].SetCheck(FALSE);
		return;
	}

	static int nTotalClick = 0;

	nTotalClick++;
	if(nTotalClick == 1)
	{	
		if (g_objCommon.Show_MsgBox(2, "Data를 삭제 하시겠습니까?") != IDOK) return;
		m_stcMZID[ID].SetWindowText(""); nTotalClick = 0;
	}

	if(nTotalClick == 2)
	{
		if (g_objCommon.Show_MsgBox(2, "전체 Data를 삭제 하시겠습니까?") != IDOK) return;
		m_stcMZID[ID].SetWindowText(""); nTotalClick = 0;

		for(int i = 0; i < 10; i++)
		{
			m_stcZigID[ID*10 + i].SetWindowText("");
			m_stcLensCnt[ID*10 + i].SetWindowText("");
		}
	}
}

void CWorkDlg::OnBnClickedRdoZigID(UINT nID)
{
	CString strTemp, strLog;
	int ID = nID - IDC_RDO_MZ_SLOT_NO_0;
	
	if (m_rdoWorkStart.GetCheck()) {
		if (gData.nLanguage == 0) AfxMessageBox(_T("장비 Stop 상태에서 진행이 가능합니다....."));
		else					  AfxMessageBox(_T("You can proceed with the equipment stopped."));
		m_rdoSelectNo[ID].SetCheck(FALSE);
		return;
	}

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (pEquipData->bUseMES)
	{
		AfxMessageBox(_T("MES사용시 Lot정보 수정할 수 없습니다."));
		m_rdoSelectNo[ID].SetCheck(FALSE);
		return;
	}

	static int nTotalClick = 0;
	static int nClickNo[60] = {0,};

	nClickNo[ID]++;
	nTotalClick++;

	int j = 0, k = 0, m = 0;
	for(int i = 0; i < 60; i++)
	{
		if(nClickNo[i] == 2)
		{
			j = i;			
			break;
		}
		else if(nClickNo[i] == 1)
		{
			if(k != 0) m = i;
			if(k == 0) k = i;
			
			
		}
	}
	if(nTotalClick != 2) return;

	CString sID, sCnt, sTemp;
	if(k != 0 && k > m)
	{
		m_stcZigID[m].GetWindowText(sID);
		m_stcLensCnt[m].GetWindowText(sCnt);
		for(int i = m; i <= k; i++)
		{
			sTemp.Format("%s-%d",sID,i);
			m_stcZigID[i].SetWindowText(sTemp);
			m_stcLensCnt[i].SetWindowText(sCnt);
		}
		for(int i = 0; i < 60; i++) nClickNo[i] = 0;
		nTotalClick = 0;
	}
	else if(k != 0 && m > k)
	{
		m_stcZigID[k].GetWindowText(sID);
		m_stcLensCnt[k].GetWindowText(sCnt);
		for(int i = k; i <= m; i++)
		{
			sTemp.Format("%s-%d",sID,i);
			m_stcZigID[i].SetWindowText(sTemp);
			m_stcLensCnt[i].SetWindowText(sCnt);
		}
		for(int i = 0; i < 60; i++) nClickNo[i] = 0;
		nTotalClick = 0;
	}
	if(nClickNo[ID] !=2) return;


	if(nClickNo[ID] == 2) if (g_objCommon.Show_MsgBox(2, "Data를 삭제 하시겠습니까?") != IDOK) return;
	for(int i = 0; i < 60; i++) nClickNo[i] = 0;
	nTotalClick = 0;
	m_stcZigID[ID].SetWindowText("");
	m_stcLensCnt[ID].SetWindowText("");

}


void CWorkDlg::OnStcLensCountClick(UINT nID)
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (pEquipData->bUseMES) {
		AfxMessageBox(_T("MES 사용시 Lot정보 수정할 수 없습니다."));
		return;
	}

	int ID = nID - IDC_STC_MZ_LENS_CNT_0;

	/*if (m_rdoWorkStart.GetCheck()) {
	if (gData.nLanguage == 0) g_objCommon.Show_MsgBox(1, "장비 Stop 상태에서 진행이 가능합니다.....");
	else					  g_objCommon.Show_MsgBox(1, "You can proceed with the equipment stopped.");
	return;
	}*/

	CString strOld, strNew, strValue;

	m_stcLensCnt[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	int nLensCnt = atoi(strNew);
	if (nLensCnt < 1 || nLensCnt > ZIG_X*ZIG_Y) {
		m_stcLensCnt[ID].SetWindowText("");
		if (gData.nLanguage == 0) AfxMessageBox(_T("Zig당 Lens수량은 200개이상 입력할수 없습니다.........."));
		else					  AfxMessageBox(_T("Lens quantity per Zig cannot be entered more than 200."));
		return;
	}
	strValue.Format("%d", nLensCnt);
	m_stcLensCnt[ID].SetWindowText(strValue);
		
	int nShare = 0, nRemainder = 0;
	nShare = ID / 10;
	nRemainder = ID %10;

	//if Running variable gets lensCnt/ if not  gets at Work_Start() 
	if (m_rdoWorkStart.GetCheck())
	{		
		gData.nLensUseCnt[nShare][nRemainder] = nLensCnt;
	}
	
	strNew.Format("[Work Mode] Lens Count Input(%d-%d-%d)", ID, nLensCnt);
	g_objLogFile.Save_HandlerLog(strNew);
}




void CWorkDlg::OnStnClickedLblLot0()
{
	m_nGroupNo = 0;

	m_Group[0].Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	m_Group[1].Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_Group[6].Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_Group[9].Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);

}

void CWorkDlg::OnStnClickedLblLot3()
{
	m_nGroupNo = 1;

	m_Group[0].Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_Group[1].Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	m_Group[6].Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_Group[9].Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	
}



void CWorkDlg::OnBnClickedRdoWorkStart()
{
	g_objLogFile.Save_HandlerLog("[Work Mode] START button push");
	CSingleLensDlg *pMainDlg = (CSingleLensDlg*)AfxGetApp()->GetMainWnd();

	pMainDlg->Set_LotErrorLog("START", 903, "Start");
	g_objLogFile.Save_EfficiencyLog(0, "Run", 903, "Run Start");
}

void CWorkDlg::OnBnClickedRdoWorkStop()
{
	g_objLogFile.Save_HandlerLog("[Work Mode] STOP button push");
	MachineStopLog("STOP_BUTTON_PUSH");
	CSingleLensDlg *pMainDlg = (CSingleLensDlg*)AfxGetApp()->GetMainWnd();

	pMainDlg->Set_LotErrorLog("STOP", 904, "Stop");
	g_objLogFile.Save_EfficiencyLog(0, "Stop", 903, "Stop Button Push");

	
}

void CWorkDlg::OnBnClickedChkCycleStop()
{
	if (m_chkCycleStop.GetCheck()) {
		m_chkCycleStop.Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0xFF));
		if (g_objCommon.Show_MsgBox(2, "Are you sure you want to Cycle Stop?") == IDOK) {
			gData.bCycleStop = TRUE;
		} else {
			m_chkCycleStop.Set_Color(RGB(0x00, 0x00, 0x00), RGB(0xF0, 0xF0, 0xF0));
			m_chkCycleStop.SetCheck(FALSE);
		}
	} else {
		m_chkCycleStop.Set_Color(RGB(0x00, 0x00, 0x00), RGB(0xF0, 0xF0, 0xF0));
		gData.bCycleStop = FALSE;
	}
}


///////////////////////////////////////////////////////////////////////////////
// User Functions

BOOL CWorkDlg::Work_Start()
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	CString strTemp, strTemp2;

	int nState = theApp.Get_MainState();
	if (nState == STATE_ERROR || nState == STATE_ALARM) return FALSE;

	if (!g_objCommon.Check_MainDoor()) return FALSE;

	if (gData.sOperID == "") { g_objCommon.Show_MsgBox(1, "작업자 ID가 입력되지 않았습니다. 확인후 진행하여 주십시오."); return FALSE; }

	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();
	DX_DATA_03 *pDX03 = g_objAJinAXL.Get_pDX03();

	
	int nMotionNo = g_objCommon.Check_MotionPos();
	if (nMotionNo < 99) 
	{
		double dCurrentPos = g_objAJinAXL.Get_Position(nMotionNo);
		CString strName = g_objAJinAXL.Get_AxisName(nMotionNo);
		strTemp.Format("Motion(%s) 위치를 Check 하세요.\n이전위치(%0.3lf) != 현재위치(%0.3lf)", strName, gAlm.dMotionPos[nMotionNo], dCurrentPos);
		g_objLogFile.Save_HandlerLog(strTemp);

		g_objCommon.Show_MsgBox(1, strTemp);
		m_rdoWorkStop.SetCheck(TRUE);
		return FALSE;
	}

	if (g_objSequenceMain.Get_IsAutoRun()) return TRUE;	// If Auto Runnning, Skip 

	//Input Info Exist Check  
	if( SearchMZCVInfo() < 0 )
	{
		g_objCommon.Show_MsgBox(1, "Please Input MZ-ID."); return FALSE;
	}
	int nZigFlag = -1, nLensFlag = -1;
	for(int i = 2; i < 6; i++)
	{
		if( SearchZigInfo(i) > 0 )
		{
			nZigFlag = SearchZigInfo(i);
		}
		if( SearchLensCntInfo(i) > 0 )
		{
			nLensFlag = SearchLensCntInfo(i);
		}
	}

	if(nZigFlag < 0) {g_objCommon.Show_MsgBox(1, "Please Input Coating Zig ID."); return FALSE;}
	if(nLensFlag < 0) {g_objCommon.Show_MsgBox(1, "Please Input Lens Cnt."); return FALSE;}



	for(int i = 2; i < 6; i++)
	{
		gData.sMZID[i - 2].Empty();
		m_stcMZID[i].GetWindowText(strTemp);
		if(strTemp != "") gData.sMZID[i - 2] = strTemp;

	}

	int nShare = 0, nRemainder;
	for(int i = 0; i < 40; i++)
	{
		nShare = (i/10) + 2; nRemainder = i % 10;

		gData.sZigID[nShare][nRemainder].Empty();
		m_stcZigID[i].GetWindowText(strTemp);		// Lot ID
		if(strTemp == "") continue;

		if (strTemp.GetLength() < 2) { g_objCommon.Show_MsgBox(1, "Please Input Zig-ID."); return FALSE; }
				
		gData.sZigID[nShare][nRemainder] = strTemp;
		
		m_stcLensCnt[i].GetWindowText(strTemp);		// Lens 수량
		if(strTemp != "")
		{
			int nTempCnt = atoi(strTemp);
			if (nTempCnt < 1 || nTempCnt > ZIG_X*ZIG_Y) { g_objCommon.Show_MsgBox(1, "Lens 수량을 확인하여 주십시오."); return FALSE; }
			gData.nLensUseCnt[nShare][nRemainder] = nTempCnt;	
		}
	}
	
	gData.bFirstLotStart = TRUE;

	return TRUE;
}




void CWorkDlg::Initial_Grid(CGridCS *pGrid, int nRows, int nCols, int nNoDir)
{
	pGrid->Set_RowCount(nRows);
	pGrid->Set_ColCount(nCols);
	pGrid->Set_FixRowCount(0);
	pGrid->Set_FixColCount(0);

	long lTotalW = pGrid->Get_GridWidth();
	long lTotalH = pGrid->Get_GridHeight();
	long lCellW = lTotalW / nCols;
	long lCellH = lTotalH / nRows;

	CString str;
	for (int i = 0; i < nRows; i++) {
		pGrid->Set_RowHeight(i, lCellH);

		for (int j = 0; j < nCols; j++) {
			if (i == 0) pGrid->Set_ColWidth(j, lCellW);

			pGrid->Set_CellAlign(i, j, CELL_ALIGN_CENTER);
			if (nNoDir == 1) { str.Format(_T("%d"), (nCols-1-j) * nRows + i + 1); }
			else			 { str.Format(_T("%d"), i * nCols + j + 1); }
			
			pGrid->Set_CellText(i, j, str);
		}
	}
}

void CWorkDlg::Check_Lamp()
{
	CSingleLensDlg *pMainDlg = (CSingleLensDlg*)AfxGetApp()->GetMainWnd();
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00(); DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01(); DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02(); DY_DATA_02 *pDY02 = g_objAJinAXL.Get_pDY02();
	DX_DATA_03 *pDX03 = g_objAJinAXL.Get_pDX03(); DY_DATA_03 *pDY03 = g_objAJinAXL.Get_pDY03();

	//Before Auto Run, Door is opened 
	if (g_objSequenceMain.Get_IsAutoRun()) 
	{		
		if (pDX03->iLoadOpenSw) 
		{
			//if (!pEquipData->bUseDoorLock || !pDX03->iDoor08Unlock) // 안전 확인.
			{
				if (!gData.bLdMZWait && !m_bLdOpenSwOn) 
				{
					pMainDlg->Set_LampFlicker_LdOpen(TRUE);
					pMainDlg->Set_LampFlicker_LdRun(FALSE);	

					gData.bLdMZWait = TRUE;
					m_bLdOpenSwOn = TRUE; m_bLdRunSwOn = FALSE;

					if (pEquipData->bUseDoorLock) { pDY03->oDoor08Unlock = TRUE; g_objAJinAXL.Write_Output(3); }

				}
				else if (gData.bLdMZWait && m_bLdOpenSwOn)
				{
					pMainDlg->Set_LampFlicker_LdOpen(FALSE);
					pMainDlg->Set_LampFlicker_LdRun(TRUE);	
					if (pEquipData->bUseDoorLock) { pDY03->oDoor08Unlock = FALSE; g_objAJinAXL.Write_Output(33); }
					gData.bLdMZWait = FALSE;
					m_bLdOpenSwOn = FALSE; m_bLdRunSwOn = TRUE;
				}			
			}			
		} 	


		if (pDX03->iLoadRunSw) 
		{			
			//if (!pEquipData->bUseDoorLock || !pDX03->iDoor08Unlock) // 안전 확인.
			{
				if (gData.bLdMZWait && !m_bLdRunSwOn) 
				{
					pMainDlg->Set_LampFlicker_LdOpen(FALSE);
					pMainDlg->Set_LampFlicker_LdRun(TRUE);	
					if (pEquipData->bUseDoorLock) { pDY03->oDoor08Unlock = TRUE; g_objAJinAXL.Write_Output(3); }
					gData.bLdMZWait = FALSE;
					m_bLdOpenSwOn = FALSE; m_bLdRunSwOn = TRUE;
				}
				else if (!gData.bLdMZWait && m_bLdRunSwOn)
				{
					pMainDlg->Set_LampFlicker_LdOpen(TRUE);
					pMainDlg->Set_LampFlicker_LdRun(FALSE);	
					if (pEquipData->bUseDoorLock) { pDY03->oDoor08Unlock = FALSE; g_objAJinAXL.Write_Output(33); }
					gData.bLdMZWait = TRUE;
					m_bLdOpenSwOn = TRUE; m_bLdRunSwOn = FALSE;
				}	
			}				
		} 
		
		if (pDX03->iUnloadOpenSw) 
		{
			//if (!pEquipData->bUseDoorLock || !pDX03->iDoor03Unlock) // 안전 확인.
			{	
				if (!gData.bUldMZWait && !m_bUldOpenSwOn) 
				{
					pMainDlg->Set_LampFlicker_UldOpen(TRUE);
					pMainDlg->Set_LampFlicker_UldRun(FALSE);	
					if (pEquipData->bUseDoorLock) { pDY03->oDoor03Unlock = TRUE; g_objAJinAXL.Write_Output(3); }
					gData.bUldMZWait = TRUE;
					m_bUldOpenSwOn = TRUE; m_bUldRunSwOn = FALSE;
				}
				else if (gData.bLdMZWait && m_bLdOpenSwOn)
				{
					pMainDlg->Set_LampFlicker_LdOpen(FALSE);
					pMainDlg->Set_LampFlicker_LdRun(TRUE);	
					if (pEquipData->bUseDoorLock) { pDY03->oDoor03Unlock = FALSE; g_objAJinAXL.Write_Output(33); }
					gData.bUldMZWait = FALSE;
					m_bUldOpenSwOn = FALSE; m_bUldRunSwOn = TRUE;
				}
			}
		} 	


		if (pDX03->iUnloadRunSw) 
		{
			//if (!pEquipData->bUseDoorLock || pDX03->iDoor03Unlock) // 안전 확인.
			{	
				if (gData.bUldMZWait && !m_bUldRunSwOn) 
				{
					pMainDlg->Set_LampFlicker_UldOpen(FALSE);
					pMainDlg->Set_LampFlicker_UldRun(TRUE);	
					if (pEquipData->bUseDoorLock) { pDY03->oDoor03Unlock = FALSE; g_objAJinAXL.Write_Output(3); }
					gData.bUldMZWait = FALSE;
					m_bUldOpenSwOn = FALSE; m_bUldRunSwOn = TRUE;
				}
				else if (!gData.bLdMZWait && m_bLdRunSwOn)
				{
					pMainDlg->Set_LampFlicker_LdOpen(TRUE);
					pMainDlg->Set_LampFlicker_LdRun(FALSE);	
					if (pEquipData->bUseDoorLock) { pDY03->oDoor03Unlock = FALSE; g_objAJinAXL.Write_Output(3); }
					gData.bUldMZWait = TRUE;
					m_bUldOpenSwOn = TRUE; m_bUldRunSwOn = FALSE;
				}
			}
		} 	

	}
	
}

void CWorkDlg::Display_Status()
{
	CString strTemp, strText;
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (g_objMesAgent.Is_Connected()) { m_stcMesConnect.Set_Text("Connected"); m_stcMesConnect.Set_Color(RGB(0x00, 0x00, 0x00), RGB(0x00, 0xFF, 0x00)); }
	else { m_stcMesConnect.Set_Text("Disconnected"); m_stcMesConnect.Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00)); }

	if (g_objMesAgent.Is_HostOnline()) { m_stcMesOnline.Set_Text("Online"); m_stcMesOnline.Set_Color(RGB(0x00, 0x00, 0x00), RGB(0x00, 0xFF, 0x00)); }
	else { m_stcMesOnline.Set_Text("Offline"); m_stcMesOnline.Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00)); }

	BOOL bInitComplete = g_objSequenceInit.Get_InitComplete();
	m_ledInitComplete.Set_On(bInitComplete);


	int *pCase = g_objSequenceMain.Get_pMainRunCase();
	for (int i = 0; i < AUTO_COUNT; i++) { strText.Format("%02d", *(pCase + i)); m_stcWorkCase[i].Set_Text(strText); }

	for (int i = 0; i < 7; i++) m_ledIndexDone[i].Set_On(gData.bIndexDone[i]);


	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();

	m_ledMZDetect[0].Set_On(pDX00->iLdCVMZExist5);
	m_ledMZDetect[1].Set_On(pDX00->iLdCVMZExist4);
	m_ledMZDetect[2].Set_On(pDX00->iLdCVMZExist3);
	m_ledMZDetect[3].Set_On(pDX00->iLdCVMZExist2);
	m_ledMZDetect[4].Set_On(pDX00->iLdCVMZExist1R);

	m_ledMZDetect[5].Set_On(pDX00->iElvMZExist1);
	m_ledMZDetect[6].Set_On(pDX00->iElvMZExist2);

	m_ledMZDetect[7].Set_On(pDX01->iUldCvMZExist1L);
	m_ledMZDetect[8].Set_On(pDX01->iUldCvMZExist2);
	m_ledMZDetect[9].Set_On(pDX01->iUldCvMZExist3);
	m_ledMZDetect[10].Set_On(pDX01->iUldCvMZExist4);

	for (int i = 0; i < 7; i++) { strText.Format("%02d", gData.nSlotNoMainIndex[i]); m_stcTrayNo[i].Set_Text(strText); }
	
// 	if (g_objMesAgent.Is_Connected()) { m_stcMesConnect.Set_Text("Connected"); m_stcMesConnect.Set_Color(RGB(0x00, 0x00, 0x00), RGB(0x00, 0xFF, 0x00)); }
// 	else { m_stcMesConnect.Set_Text("Disconnected"); m_stcMesConnect.Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00)); }
// 
// 	if (g_objMesAgent.Is_HostOnline()) { m_stcMesOnline.Set_Text("Online"); m_stcMesOnline.Set_Color(RGB(0x00, 0x00, 0x00), RGB(0x00, 0xFF, 0x00)); }
// 	else { m_stcMesOnline.Set_Text("Offline"); m_stcMesOnline.Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00)); }

	

	//DX_DATA_11 *pDX11 = g_objAJinAXL.Get_pDX11();
	//int nIndexPos = pDX11->iIndexPosition0 + (pDX11->iIndexPosition1 << 1);
	//strText.Format("%d", nIndexPos + 1);
	//m_stcIndexPos.SetWindowText(strText);



	m_ledVisionStatus[0].Set_On(g_objInspector.Check_Connect(VISION_PC1));
	m_ledEquipOption[0].Set_On(pEquipData->bUseTopVision);
	m_ledEquipOption[1].Set_On(pEquipData->bUseBtmVision);
}

void CWorkDlg::Reset_AlarmLog()
{
	CString strLog, strErrNo;
	SYSTEMTIME time;

	gAlm.bBegin = FALSE;
	GetLocalTime(&time);

	gAlm.dwEndTime = GetTickCount();
	gAlm.sEndTime.Format("%04d%02d%02d_%02d%02d%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	gAlm.dwProcTime = gAlm.dwEndTime - gAlm.dwStartTime;
	
	gLot.dwErrorTime += gAlm.dwProcTime; gLot.nErrorCount++;

	strLog.Format("%s,%04d,%s,%s,%s,%d", gAlm.sLotID, gAlm.nAlmNo, gAlm.sAlmMsg, gAlm.sStartTime, gAlm.sEndTime, gAlm.dwProcTime);
	g_objLogFile.Save_AlarmResetLog(strLog);	// Alarm Reset

	strErrNo.Format("%04d", gAlm.nAlmNo);
	g_objMesAgent.Set_ErrorUpdate(0, strErrNo);

	g_objLogFile.Save_ECMLog(1, strLog);
}

void CWorkDlg::MachineStopLog(CString sType, CString sMsg)
{
	CString strLog, strErrNo;
	SYSTEMTIME time;

	GetLocalTime(&time);

	if (sType == "STOP_BUTTON_PUSH" || sType == "ALARM" || sType == "PROGRAM_BEGIN") {
		if (gData.dwMStopStartTime > 1) {
			gData.dwMStopEndTime = GetTickCount();
			gData.dwMStopProcTime = gData.dwMStopEndTime - gData.dwMStopStartTime;

			gData.dwMStopStartTime = GetTickCount();
			if (sType == "ALARM")	strLog.Format("%s: %s,%d", sType, sMsg, gData.dwMStopProcTime);
			else					strLog.Format("%s,%d", sType, gData.dwMStopProcTime);

		} else {
			gData.dwMStopStartTime = GetTickCount();
			if (sType == "ALARM")	strLog.Format("%s: %s", sType, sMsg);
			else					strLog.Format("%s", sType);
		}
	} else if (sType == "RUN_START" || sType == "PROGRAM_EXIT") {
		gData.dwMStopEndTime = GetTickCount();
		if (gData.dwMStopStartTime < 1) gData.dwMStopProcTime = 0;
		else							gData.dwMStopProcTime = gData.dwMStopEndTime - gData.dwMStopStartTime;

		strLog.Format("%s,%d", sType, gData.dwMStopProcTime);

		gData.dwMStopStartTime = 0;
	}

	g_objLogFile.Save_MachineStopLog(strLog);
}

void CWorkDlg::Set_AutoRun(BOOL bAutoRun)
{
	if (bAutoRun) m_rdoWorkStart.SetCheck(TRUE);
	else m_rdoWorkStop.SetCheck(TRUE);
}

void CWorkDlg::Set_State(int nState)
{
	switch (nState) {
	case STATE_NONE:
	case STATE_INIT:
	case STATE_STOP:	// Stop
		m_rdoWorkStart.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
		m_rdoWorkStop.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
		m_rdoWorkStop.SetCheck(TRUE);
		m_chkCycleStop.EnableWindow(TRUE);
		break;
	case STATE_RUN:		// Start
		m_rdoWorkStart.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
		m_rdoWorkStop.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
		m_chkCycleStop.EnableWindow(FALSE);
		break;
	case STATE_ALARM:
	case STATE_ERROR:	// Error
		m_rdoWorkStart.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
		m_rdoWorkStop.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
		m_rdoWorkStop.SetCheck(TRUE);
		break;
	}
}

void CWorkDlg::Enable_UserInput(int nNo, BOOL bEnable)
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	if (nNo == 1) {
	
	} 
	if (nNo == 2) {

	}
}

void CWorkDlg::Get_MZInfo(int nMZNo)
{
	int nZigNo = 0;
	CString sZigID, sLensCnt;

	for(int i = 0; i < 10; i++)
	{
		nZigNo = (nMZNo-1)*10 +i;
		m_stcZigID[nZigNo].GetWindowText(sZigID);
		gData.sZigID[nMZNo-1][i] = sZigID;

		m_stcLensCnt[nZigNo].GetWindowText(sLensCnt);
		gData.nLensUseCnt[nMZNo-1][i] = atoi(sLensCnt);
	}	
}

void CWorkDlg::Set_MZInfo(int nMZNo)
{
		
}

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Message

LRESULT CWorkDlg::OnUpdateModel(WPARAM wParam, LPARAM lParam)
{
	CString strText;

	return 0;
}

LRESULT CWorkDlg::OnUpdateMZInfo(WPARAM nTray, LPARAM lParam)
{
	CString strText;
	int nNo = (int)lParam;

	if (nTray == eMZ::Load)
	{		
		
		for (int i = 0; i < SLOT_NO_MAX; i++)
		{
			for (int j = 0; j < 1; j++) 
			{
				if		(g_objSequenceMain.Search_ZigSlotNo(eMZ::Load, i+1) > 0 ) m_grdLoadMZ.Set_CellBackClr(i, j, RGB(0xFF, 0xFF, 0x00));	// Reserve
				else if (g_objSequenceMain.Search_ZigSlotNo(eMZ::Load, i+1) < 0) m_grdLoadMZ.Set_CellBackClr(i, j, RGB(0xFF, 0xFF, 0xFF));	// Empty
				else									m_grdLoadMZ.Set_CellBackClr(i, j, RGB(0x80, 0x80, 0x80));	// Error

				if (g_objSequenceMain.Search_ZigSlotNo(eMZ::Unload, i+1) > 0 ) m_grdLoadMZ.Set_CellBackClr(i, j, RGB(0x00, 0xFF, 0xFF));	// Empty

			}
		}
		//g_dlgOperator.Update_TrayInfo(nTray);
	}

	if (nTray==eMZ::Unload)
	{		
		/*strText.Format("%d", gData.nTNoLoadTray[nNo]);
		m_stcLoadTrayCount.SetWindowText(strText);*/
		for (int i = 0; i < SLOT_NO_MAX; i++)
		{
			for (int j = 0; j < 1; j++) 
			{
				if (g_objSequenceMain.Search_ZigSlotNo(eMZ::Unload, i+1) > 0) m_grdLoadMZ.Set_CellBackClr(i, j, RGB(0x00, 0xFF, 0xFF));	// Empty
				else if (g_objSequenceMain.Search_ZigSlotNo(eMZ::Unload, i+1) < 0) m_grdLoadMZ.Set_CellBackClr(i, j, RGB(0xFF, 0xFF, 0xFF));	// Empty
			}
		}
		//g_dlgOperator.Update_TrayInfo(nTray);
	}


	if (nTray == eMZ::Ready)
	{		
		for (int i = 0; i < SLOT_NO_MAX; i++)
		{
			for (int j = 0; j < 1; j++) 
			{
				if		(g_objSequenceMain.Search_ZigSlotNo(eMZ::Ready, i+1) > 0) m_grdRdyMZ.Set_CellBackClr(i, j, RGB(0xFF, 0xFF, 0x00));	// Reserve
				else if (g_objSequenceMain.Search_ZigSlotNo(eMZ::Ready, i+1) < 0) m_grdRdyMZ.Set_CellBackClr(i, j, RGB(0xFF, 0xFF, 0xFF));	// Empty
				else									m_grdRdyMZ.Set_CellBackClr(i, j, RGB(0x80, 0x80, 0x80));	// Error
			}
		}
		//g_dlgOperator.Update_TrayInfo(nTray);
	}
	
	return 0;
}



LRESULT CWorkDlg::OnUpdateVisionInfo(WPARAM nVision, LPARAM lParam)
{
	if (nVision == eVision::TC)
	{	
		for (int i = 0; i < gData.nLensCntY; i++)
		{
			for (int j = 0; j < gData.nLensCntX; j++) 
			{
				if		(gData.InfoMainIndex[eMainIndex::Top][j][i] == eLensState::TopDone ) m_grdTopVision.Set_CellBackClr(i, j, RGB(0xFF, 0xFF, 0x00));	// Reserve
				else if (gData.InfoMainIndex[eMainIndex::Top][j][i] == eLensState::TopReady) m_grdTopVision.Set_CellBackClr(i, j, RGB(0xFF, 0xFF, 0xFF));	// Empty
				else				m_grdTopVision.Set_CellBackClr(i, j, RGB(0x80, 0x80, 0x80));	// Error

			}
		}
	}

	if (nVision == eVision::BC)
	{		
		for (int i = 0; i < gData.nLensCntY; i++)
		{
			for (int j = 0; j < gData.nLensCntX; j++) 
			{
				if		(gData.InfoMainIndex[eMainIndex::Btm][j][i] == eLensState::BtmDone ) m_grdBtmVision.Set_CellBackClr(i, j, RGB(0xFF, 0xFF, 0x00));	// Reserve
				else if (gData.InfoMainIndex[eMainIndex::Btm][j][i] == eLensState::BtmReady) m_grdBtmVision.Set_CellBackClr(i, j, RGB(0xFF, 0xFF, 0xFF));	// Empty
				else				m_grdBtmVision.Set_CellBackClr(i, j, RGB(0x80, 0x80, 0x80));	// Error

			}
		}
	}

	if (nVision == eVision::MARKING)
	{		
		for (int i = 0; i < gData.nLensCntY; i++)
		{
			for (int j = 0; j < gData.nLensCntX; j++) 
			{
			
				if		(gData.InfoMainIndex[eMainIndex::Mark][j][i] == eLensState::Marked ) m_grdMarking.Set_CellBackClr(i, j, RGB(0xFF, 0xFF, 0x00));	// Reserve
				else if (gData.InfoMainIndex[eMainIndex::Mark][j][i] == eLensState::NotMarked) m_grdMarking.Set_CellBackClr(i, j, RGB(0x00, 0xFF, 0xFF));	// Empty
				else if (gData.InfoMainIndex[eMainIndex::Mark][j][i] == eLensState::MarkReady) m_grdMarking.Set_CellBackClr(i, j, RGB(0xFF, 0xFF, 0xFF));	// Empty
				else				m_grdMarking.Set_CellBackClr(i, j, RGB(0x80, 0x80, 0x80));	// Error

				//if		(gData.nInspectInfo[gData.nMZNoMainIndex[eMainIndex::Mark]-1][j][i] == 2 ) m_grdMarking.Set_CellBackClr(i, j, RGB(0xFF, 0x00, 0x00));	// Reserve
				//else if (gData.nInspectInfo[gData.nMZNoMainIndex[eMainIndex::Mark]-1][j][i] != 2) m_grdMarking.Set_CellBackClr(i, j, RGB(0x00, 0x00, 0xFF));	// Empty
				//else				m_grdMarking.Set_CellBackClr(i, j, RGB(0x80, 0x80, 0x80));	// Error

			}
		}
	}

	return 0;
}

LRESULT CWorkDlg::OnUpdateBarcode(WPARAM wParam, LPARAM lParam)
{
	CString sBarcode;// = g_objBarcodeLot.Get_BarcodeLot();
	sBarcode.Replace("\r","");
	sBarcode.Replace("\n","");
	CString strTemp, strText;

	if (sBarcode.GetLength() < 2) return 0;


	return 0;
}



LRESULT CWorkDlg::OnResetCycleStop(WPARAM wParam, LPARAM lParam)
{
	gData.bCycleStop = FALSE;
	m_chkCycleStop.SetCheck(FALSE);
	m_chkCycleStop.Set_Color(RGB(0x00, 0x00, 0x00), RGB(0xF0, 0xF0, 0xF0));
	//if (wParam == 1) g_objSequenceInit.Set_InitComplete(FALSE);	// 초기화 필요

	return 0;
}

LRESULT CWorkDlg::OnUpdateUph(WPARAM wParam, LPARAM lParam)
{
	SYSTEMTIME time;
	GetLocalTime(&time);

	int nHour = time.wHour;
	double	dDispTakt[4] = { 0.0 };
	CString strText;

	dDispTakt[0] = gUph.dTaktTime;		// 현재 Lot

	int nCount = gUph.nLotCount[nHour];
	for (int i = 0; i < nCount; i++) dDispTakt[1] += gUph.dTakt[nHour][i];
	dDispTakt[1] /= nCount;				// 1시간

	int nTotalCount = 0;
	if (nHour >= 7 && nHour < 19) {
		for (int i = 7; i < 19; i++) {
			nCount = gUph.nLotCount[i];
			for (int j = 0; j < nCount; j++) dDispTakt[2] += gUph.dTakt[i][j];
			nTotalCount += nCount;
		}
	} else {
		for (int i = 0; i < 7; i++) {
			nCount = gUph.nLotCount[i];
			for (int j = 0; j < nCount; j++) dDispTakt[2] += gUph.dTakt[i][j];
			nTotalCount += nCount;
		}

		for (int i = 19; i < 24; i++) {
			nCount = gUph.nLotCount[i];
			for (int j = 0; j < nCount; j++) dDispTakt[2] += gUph.dTakt[i][j];
			nTotalCount += nCount;
		}
	}
	dDispTakt[2] /= nTotalCount;		// 12시간

	nTotalCount = 0;
	for (int i = 0; i < 24; i++) {
		nCount = gUph.nLotCount[i];
		for (int j = 0; j < nCount; j++) dDispTakt[3] += gUph.dTakt[i][j];
		nTotalCount += nCount;
	}
	dDispTakt[3] /= nTotalCount;		// 1일

	// Takt & UPH
	for (int i = 0; i < 4; i++) {
		if (dDispTakt[i] == 0) strText = "";
		else strText.Format("%0.5f", dDispTakt[i]);
		m_stcTakt[i].SetWindowText(strText);

		if (dDispTakt[i] == 0) strText = "";
		else strText.Format("%d", int(3600 / dDispTakt[i]));
		m_stcUph[i].SetWindowText(strText);
	}

	//생산량
	for (int i = 0; i < 2; i++) {
		if (gUph.nLensCount[i] == 0) strText = "";
		else strText.Format("%d", gUph.nLensCount[i]);
		m_stcDay[i].SetWindowText(strText);
	}

	return 0;
}


LRESULT CWorkDlg::OnLotStartEnd(WPARAM wParam, LPARAM lParam)
{
	CSingleLensDlg *pMainDlg = (CSingleLensDlg*)AfxGetApp()->GetMainWnd();
	int nNo = lParam;
	if (wParam == 1) {
		pMainDlg->Set_LotErrorLog("LOT START", 901, "Lot Start", nNo);
	} else if (wParam == 2) {
		pMainDlg->Set_LotErrorLog("LOT END", 902, "Lot End", nNo);
	}
	return 0;
}

LRESULT CWorkDlg::OnIndexTack(WPARAM wParam, LPARAM lParam)
{
	CString strTemp;
	
	return 0;
}

LRESULT CWorkDlg::OnShowMsg(WPARAM wParam, LPARAM lParam)
{
	//g_dlgWork.PostMessage(UM_LOT_END_MSG, NULL, NULL);
	//if(wParam == 1) g_objCommon.Show_MsgBox(1, "NG Tray Full 상태입니다.\nNG Tray 교체 해주십시오.");
	//else if(wParam == 2) g_objCommon.Show_MsgBox(1, "현재 Lot이 종료 되었습니다. Tray 배출 해주십시오.");
	//else if(wParam == 3) g_objCommon.Show_Alarm("Cap Tray 정보 입력 해주십시오.", STATE_CAPTRAY);
	//else if(wParam == 4) g_objCommon.Show_Alarm("Cap Tray 투입 해주십시오.", STATE_CAPTRAY);
	//else if(wParam == 5) g_objCommon.Show_Alarm("Ship Tray 투입 해주십시오.", STATE_SHIPTRAY);
	//else 	g_objCommon.Show_MsgBox(1, "Lot의 마지막 트레이 작업 중입니다.\n배출 준비 해주십시오.");

	return 0;
}

void CWorkDlg::Change_Model()
{


}

///////////////////////////////////////////////////////////////////////////////

void CWorkDlg::OnBnClickedButton1()
{
	//g_objSequenceMain.Job_LotStart(1);
}

void CWorkDlg::OnBnClickedButton2()
{
	g_objSequenceMain.Job_LotEnd(1);
	OnUpdateUph(NULL, NULL);

}


void CWorkDlg::OnBnClickedBtnSimul1()
{
	DX_DATA_00* m_pDX00 = g_objAJinAXL.Get_pDX00();
	m_pDX00->iLdCVMZExist5 = TRUE;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



BOOL CWorkDlg::OnEraseBkgnd(CDC* pDC)
{
	// 기본 배경 먼저 그림
	BOOL bRet = CDialogEx::OnEraseBkgnd(pDC);

	// 배경 이미지 영역 없으면 종료
	if (m_rcBgArea.IsRectEmpty())
		return bRet;

	// 비트맵 없으면 종료
	if (m_bmpBg.GetSafeHandle() == NULL)
		return bRet;

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	CBitmap* pOldBmp = memDC.SelectObject(&m_bmpBg);

	BITMAP bm;
	::ZeroMemory(&bm, sizeof(BITMAP));
	m_bmpBg.GetBitmap(&bm);

	pDC->SetStretchBltMode(HALFTONE);

	// IDC_STATIC_BG 크기에 맞춰 그림
	pDC->StretchBlt(
		m_rcBgArea.left,
		m_rcBgArea.top,
		m_rcBgArea.Width(),
		m_rcBgArea.Height(),
		&memDC,
		0,
		0,
		bm.bmWidth,
		bm.bmHeight,
		SRCCOPY);

	memDC.SelectObject(pOldBmp);

	return TRUE;
}

HBRUSH CWorkDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// static text 배경 투명 처리
	/*if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}*/

	return hbr;
}



int CWorkDlg::SearchMZElevInfo(int nNo)
{
	CString sMZInfo;

	m_stcMZID[nNo].GetWindowText(sMZInfo);
	if(sMZInfo != "")
	{
		return -1;
	}
	return nNo;
}

int CWorkDlg::SearchMZCVInfo()
{
	for(int i = 2; i < 6; i++) // start from 2 <-- Conveyor 1 pos
	{
		CString sMZInfo;
		m_stcMZID[i].GetWindowText(sMZInfo);
		if(sMZInfo != "")
		{
			return i;
		}
	}
	
	return -1;
}

void CWorkDlg::TransferMZInfo(int nFrom, int nTo, int nDir)
{
	CString sMZIDFrom, sMZIDTo, sZigIDFrom, sZigIDTo, sLensCntFrom, sLensCntTo;
	
	if(nTo == -1)
	{
		m_stcMZID[nFrom].SetWindowText("");
		gData.sMZID[nFrom] = "";

		for(int i = 0; i < 10; i++)
		{
			m_stcZigID[nFrom*10 +i].SetWindowText("");
			gData.sZigID[nFrom][i] = "";

			m_stcLensCnt[nFrom*10 +i].SetWindowText("");
			gData.nLensUseCnt[nFrom][i] = 0;
		}
		return ;
	}
	m_stcMZID[nFrom].GetWindowText(sMZIDFrom);
	sMZIDTo = sMZIDFrom;
	m_stcMZID[nTo].SetWindowText(sMZIDTo);
	m_stcMZID[nFrom].SetWindowText("");

	gData.sMZID[nTo] = sMZIDFrom; gData.sMZID[nFrom] = "";

	gData.nLensTotalCnt[nTo] = 0;
	gData.nCtZigTotalCnt[nTo] = 0;
	for(int i = 0; i < 10; i++)
	{
		m_stcZigID[nFrom*10 + i].GetWindowText(sZigIDFrom);
		sZigIDTo = sZigIDFrom;

		if(sZigIDTo != "") gData.nCtZigTotalCnt[nTo]++;
		m_stcZigID[nTo*10 + i].SetWindowText(sZigIDTo);
		m_stcZigID[nFrom*10 +i].SetWindowText("");

		gData.sZigID[nTo][i] = sZigIDTo; gData.sZigID[nFrom][i] = "";
				
		m_stcLensCnt[nFrom*10 + i].GetWindowText(sLensCntFrom);
		sLensCntTo = sLensCntFrom;
		m_stcLensCnt[nTo*10 +i].SetWindowText(sLensCntTo);
		m_stcLensCnt[nFrom*10 +i].SetWindowText("");

		gData.nLensUseCnt[nTo][i] = atoi(sLensCntTo);
		gData.nLensTotalCnt[nTo] += gData.nLensUseCnt[nTo][i];

		gData.nLensUseCnt[nFrom][i] = 0;
		
		//Init Lens State 
		int nCnt = 0;		

		if(nTo == eMZ::Load && nFrom != eMZ::Ready)
		{
			gData.nTNoPick[eMZ::Load] = 1;
			gData.ZigMap[eMZ::Load][i] = FALSE;
			
			if(nDir == eVDir::fixY)
			{
				for(int j = 0; j < gData.nLensCntY; j++)
				{
					for(int k = 0; k < gData.nLensCntX; k++)
					{
						nCnt++;
						if(nCnt <= gData.nLensUseCnt[nTo][i])
						{
							gData.ZigMap[eMZ::Load][i] = TRUE; // Zig 존재함 

							gData.InfoMZLoad[i][k][j] = (int)eLensState::Init;
							gData.LensMap[eMZ::Load][i][k][j] = eLensState::Init;
						}
						else
						{
							gData.InfoMZLoad[i][k][j] = eLensState::None;
							gData.LensMap[eMZ::Load][i][k][j] = eLensState::None;
						}
					}			
				}
			}
			else if(nDir == eVDir::fixX)
			{
				for(int j = 0; j < gData.nLensCntX; j++)
				{
					for(int k = 0; k < gData.nLensCntY; k++)
					{
						nCnt++;
						if(nCnt <= gData.nLensUseCnt[nTo][i])
						{
							gData.ZigMap[eMZ::Load][i] = TRUE; // Zig 존재함 

							gData.InfoMZLoad[i][j][k] = (int)eLensState::Init;
							gData.LensMap[eMZ::Load][i][j][k] = eLensState::Init;
						}
						else
						{
							gData.InfoMZLoad[i][j][k] = eLensState::None;
							gData.LensMap[eMZ::Load][i][j][k] = eLensState::None;
						}
					}			
				}
			}			
		}
		else if(nTo == eMZ::Ready)
		{
			gData.nTNoPick[eMZ::Ready] = 1;
			gData.ZigMap[eMZ::Ready][i] = FALSE;

			if(nDir == eVDir::fixY)
			{
				for(int j = 0; j < gData.nLensCntY; j++)
				{
					for(int k = 0; k < gData.nLensCntX; k++)
					{
						nCnt++;
						if(nCnt <= gData.nLensUseCnt[nTo][i])
						{
							gData.ZigMap[eMZ::Ready][i] = TRUE; // Zig 존재함 

							gData.InfoMZReady[i][k][j] = (int)eLensState::Init;
							gData.LensMap[eMZ::Ready][i][k][j] = eLensState::Init;
						}
						else
						{
							gData.InfoMZReady[i][k][j] = eLensState::None;
							gData.LensMap[eMZ::Ready][i][k][j] = eLensState::None;
						}
					}			
				}
			}
			else if(nDir == eVDir::fixX)
			{
				for(int j = 0; j < gData.nLensCntX; j++)
				{
					for(int k = 0; k < gData.nLensCntY; k++)
					{
						nCnt++;
						if(nCnt <= gData.nLensUseCnt[nTo][i])
						{
							gData.ZigMap[eMZ::Ready][i] = TRUE; // Zig 존재함 

							gData.InfoMZReady[i][j][k] = (int)eLensState::Init;
							gData.LensMap[eMZ::Ready][i][j][k] = eLensState::Init;
						}
						else
						{
							gData.InfoMZReady[i][j][k] = eLensState::None;
							gData.LensMap[eMZ::Ready][i][j][k] = eLensState::None;
						}
					}			
				}
			}

			
		}
		else if(nTo == eMZ::Load && nFrom == eMZ::Ready)
		{
			gData.nTNoPick[eMZ::Load] = gData.nTNoPick[eMZ::Ready];
			gData.ZigMap[eMZ::Load][i] = gData.ZigMap[eMZ::Ready][i];
			
			memcpy(gData.InfoMZLoad[i], gData.InfoMZReady[i], sizeof(int)*ZIG_X*ZIG_Y);
			memset(gData.InfoMZReady[i], 0x00, sizeof(int)*ZIG_X*ZIG_Y);
			memcpy(gData.LensMap[eMZ::Load][i], gData.LensMap[eMZ::Ready][i], sizeof(int)*ZIG_X*ZIG_Y);
			memset(gData.LensMap[eMZ::Ready][i], 0x00, sizeof(int)*ZIG_X*ZIG_Y);
		}		
	}

	

}

int CWorkDlg::SearchZigInfo(int nMZNo)
{
	for(int i = 0; i < 10; i++) // start from 2 <-- Conveyor 1 pos
	{
		CString sZigInfo;
		m_stcZigID[nMZNo*10 + i].GetWindowText(sZigInfo);
		if(sZigInfo != "")
		{
			return i + 1;
		}
	}	
	return -1;
}

int CWorkDlg::SearchLensCntInfo(int nMZNo)
{
	for(int i = 0; i < 10; i++) // start from 2 <-- Conveyor 1 pos
	{
		CString sLensCnt;
		m_stcLensCnt[nMZNo*10 + i].GetWindowText(sLensCnt);
		if(sLensCnt != "")
		{
			return i + 1;
		}
	}
	return -1;
}


int CWorkDlg::CheckZigExistInMZ(int nMZNo, int nSlot)
{
	CString sZigInfo;
	m_stcZigID[nMZNo*10 + (nSlot -1)].GetWindowText(sZigInfo);
	if(sZigInfo != "")
	{
		return nSlot;
	}
	return -1;
}


void CWorkDlg::OnStnClickedStcHidden()
{
	m_stcMZID[2].SetWindowText("TTTTT");
		m_stcZigID[20].SetWindowText("1111");
		m_stcZigID[21].SetWindowText("11112");
		m_stcZigID[22].SetWindowText("11113");
		m_stcZigID[23].SetWindowText("11114");
		m_stcZigID[24].SetWindowText("11115");
		m_stcZigID[25].SetWindowText("11116");
		m_stcZigID[26].SetWindowText("11117");
		m_stcZigID[27].SetWindowText("11118");
		m_stcZigID[28].SetWindowText("11119");
		m_stcZigID[29].SetWindowText("11120");
		
		m_stcLensCnt[20].SetWindowText("14");
		m_stcLensCnt[21].SetWindowText("14");
		m_stcLensCnt[22].SetWindowText("14");
		m_stcLensCnt[23].SetWindowText("14");
		m_stcLensCnt[24].SetWindowText("14");
		m_stcLensCnt[25].SetWindowText("14");
		m_stcLensCnt[26].SetWindowText("14");
		m_stcLensCnt[27].SetWindowText("14");
		m_stcLensCnt[28].SetWindowText("14");
		m_stcLensCnt[29].SetWindowText("14");
		
		m_stcMZID[3].SetWindowText("MMMMM");
		m_stcZigID[30].SetWindowText("1111");
		m_stcZigID[31].SetWindowText("11112");
		m_stcZigID[32].SetWindowText("11113");
		m_stcZigID[33].SetWindowText("11114");
		m_stcZigID[34].SetWindowText("11115");
		m_stcZigID[35].SetWindowText("11116");
		m_stcZigID[36].SetWindowText("11117");
		m_stcZigID[37].SetWindowText("11118");
		m_stcZigID[38].SetWindowText("11119");
		m_stcZigID[39].SetWindowText("11120");


		m_stcLensCnt[30].SetWindowText("14");
		m_stcLensCnt[31].SetWindowText("14");
		m_stcLensCnt[32].SetWindowText("14");
		m_stcLensCnt[33].SetWindowText("14");
		m_stcLensCnt[34].SetWindowText("14");
		m_stcLensCnt[35].SetWindowText("14");
		m_stcLensCnt[36].SetWindowText("14");
		m_stcLensCnt[37].SetWindowText("14");
		m_stcLensCnt[38].SetWindowText("14");
		m_stcLensCnt[39].SetWindowText("14");
		
		m_stcMZID[4].SetWindowText("MMMMM3");
		m_stcZigID[40].SetWindowText("1111");
		m_stcZigID[41].SetWindowText("11112");
		m_stcZigID[42].SetWindowText("11113");
		m_stcZigID[43].SetWindowText("11114");
		m_stcZigID[44].SetWindowText("11115");
		m_stcZigID[45].SetWindowText("11116");
		m_stcZigID[46].SetWindowText("11117");
		m_stcZigID[47].SetWindowText("11118");
		m_stcZigID[48].SetWindowText("11119");
		m_stcZigID[49].SetWindowText("11119");

		m_stcLensCnt[40].SetWindowText("14");
		m_stcLensCnt[41].SetWindowText("14");
		m_stcLensCnt[42].SetWindowText("14");
		m_stcLensCnt[43].SetWindowText("14");
		m_stcLensCnt[44].SetWindowText("14");
		m_stcLensCnt[45].SetWindowText("14");
		m_stcLensCnt[46].SetWindowText("14");
		m_stcLensCnt[47].SetWindowText("14");
		m_stcLensCnt[48].SetWindowText("14");
		m_stcLensCnt[49].SetWindowText("14");

	if(m_chkNoTrayMode.IsWindowVisible())
	{
		m_chkNoTrayMode.ShowWindow(SW_HIDE);		
	}
	else
	{
		m_chkNoTrayMode.ShowWindow(SW_SHOW);
		
	}
	
}


void CWorkDlg::OnBnClickedChkNoTray()
{
	gData.bDemoMode = m_chkNoTrayMode.GetCheck();
}


void CWorkDlg::OnBnClickedBtnLight()
{
	DY_DATA_03 *pDY03 = g_objAJinAXL.Get_pDY03();

	static int nOnOff = 0;

	if(nOnOff == 0)
	{
		nOnOff = 1;
		pDY03->oInsideLight = TRUE;
	}
	else if(nOnOff == 1)
	{
		nOnOff = 0;
		pDY03->oInsideLight = FALSE;
	}
	
	g_objAJinAXL.Write_Output(3);
}


void CWorkDlg::OnStnClickedStcOperId()
{
	CString strKey, sLog;
	if (g_objCommon.Show_KeyPad(strKey) != IDOK) return;

	m_stcOperId.SetWindowText(strKey);
	gData.sOperID = strKey;
	g_objMesAgent.Set_OperUpdate(gData.sOperID);
	g_dlgOperator.m_stcOperOperId.SetWindowText(strKey);

	sLog.Format("[Work Dialog] Oper ID Button Click. [%s]", gData.sOperID);
	g_objLogFile.Save_HandlerLog(sLog);
}


void CWorkDlg::OnBnClickedBtnMesOnline()
{
	if (gData.sOperID.GetLength() < 4) { AfxMessageBox("Input the Operator ID....."); return; }

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (!pEquipData->bUseMES) return;

	g_objMesAgent.Set_ControlState(1, gData.sOperID);

	g_objLogFile.Save_HandlerLog("[Work Dialog] MES Online Button Click.");
}


void CWorkDlg::OnBnClickedBtnMesOffline()
{
	if (gData.sOperID.GetLength() < 4) { AfxMessageBox("Input the Operator ID....."); return; }

	g_objMesAgent.Set_ControlState(2, gData.sOperID);

	g_objLogFile.Save_HandlerLog("[Work Dialog] MES Offline Button Click.");
}




void CWorkDlg::OnBnClickedBtnMesConnect()
{
	if (gData.sOperID.GetLength() < 4) { AfxMessageBox("Input the Operator ID....."); return; }

	g_objMesAgent.Initialize();
	g_objLogFile.Save_HandlerLog("[Work Dialog] MES Connect Button Click.");
}


void CWorkDlg::OnBnClickedBtnMesDisconnect()
{
	if (gData.sOperID.GetLength() < 4) { AfxMessageBox("Input the Operator ID....."); return; }

	g_objMesAgent.Terminate();
	g_objLogFile.Save_HandlerLog("[Work Dialog] MES Disconnect Button Click.");
}


void CWorkDlg::OnBnClickedBtnMesAbort()
{
	if (gData.sOperID.GetLength() < 4) { AfxMessageBox("Input the Operator ID....."); return; }

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (!pEquipData->bUseMES) return;

	if (!g_objMesAgent.Is_Connected()) { AfxMessageBox("MES Disconnect 상태에서는 처리를 할수 없습니다."); return; }
	if (!g_objMesAgent.Is_HostOnline()) { AfxMessageBox("MES Offline 상태에서는 처리를 할수 없습니다."); return; }
	if (gData.nSelectNo < 1 || gData.nSelectNo > 6) { AfxMessageBox("Abort Lot을 먼저 선택해 주세요."); return; }
	if (!m_rdoWorkStop.GetCheck()) { AfxMessageBox("장비 Stop상태에서 Abort처리 하세요."); return; }
	//if (gMes.nLotStatus[gData.nSelectNo-1] == 0) { AfxMessageBox("진행중인 Lot만 Abort처리가 가능합니다."); return; }

	//int nCase1 = g_objSequenceMain.Get_MainRunCase(AUTO_LOAD_STAGE_1);
	//int nCase2 = g_objSequenceMain.Get_MainRunCase(AUTO_LOAD_STAGE_2);
	//if ((nCase1 > 5 && nCase1 < 8) || (nCase2 > 5 && nCase2 < 8)) {

	//	CString sData;
	//	sData.Format("Are you want to cancel this Port[%d] Lot[%s]?", gData.nSelectNo, gLot.sLotID[gData.nSelectNo-1]);
	//	if (g_objCommon.Show_MsgBox(2, sData) != IDOK) return;

	//	gMes.nLotStatus[gData.nSelectNo-1] = 0;
	//	g_objMesAgent.Set_LotAbort(gLot.sLotID[gData.nSelectNo-1]);

	//	//	int nCase1 = g_objSequenceMain.Get_MainRunCase(AUTO_TRANSFER_1);
	//	//	if (nCase1 == 7) g_objSequenceMain.Set_MainRunCase(AUTO_TRANSFER_1, 0);
	//	if (nCase1 > 5 && nCase1 < 8) g_objSequenceMain.Set_MainRunCase(AUTO_LOAD_STAGE_1, 20);
	//	if (nCase2 > 5 && nCase2 < 8) g_objSequenceMain.Set_MainRunCase(AUTO_LOAD_STAGE_2, 20);

	//	m_stcLotsIdS[gData.nSelectNo-1].SetWindowText("");
	//	m_stcCmsCountS[gData.nSelectNo-1].SetWindowText("");
	//	g_objCommon.Set_LotDataClear(gData.nSelectNo-1);

	//	sData.Format("[Work Dialog] MES Abort Button Click. PortNo[%d] LotID[%s]", gData.nSelectNo, gLot.sLotID[gData.nSelectNo-1]);
	//	g_objLogFile.Save_HandlerLog(sData);
	//} else {
	//	AfxMessageBox("진행중인 Lot만 Abort처리가 가능합니다.");
	//}
}


void CWorkDlg::OnBnClickedBtnIdleReport()
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (!pEquipData->bUseMES) return;

	if (m_rdoWorkStart.GetCheck()) {
		if (gData.nLanguage == 0) AfxMessageBox(_T("장비 Stop 상태에서 진행이 가능합니다....."));
		else					  AfxMessageBox(_T("You can proceed with the equipment stopped."));
		return;
	}

	/*if (g_dlgNoWork.IsWindowVisible()) g_dlgNoWork.ShowWindow(SW_HIDE);
	else g_dlgNoWork.ShowWindow(SW_SHOW);	*/
}
