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
#include "BarcodeLot_Cognex.h"

#include "SequenceInit.h"
#include "SequenceMain.h"

#include "OperatorDlg.h"
#include "NoWorkDlg.h"

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
	//for (int i = 0; i < 10; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	//for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);	
	//for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_LBL_LOT_0 + i, m_lblLot[i]);
	for (int i = 0; i <6; i++) DDX_Control(pDX, IDC_GRP_MZ_0 + i, m_grpMZ[i]);
	for (int i = 0; i <6; i++) DDX_Control(pDX, IDC_RDO_MZ_ID_0 + i, m_rdoMZID[i]);
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
	DDX_Control(pDX, IDC_CHK_SIMUL, m_chkSimulMode);	

	for (int i = 0; i < AUTO_COUNT; i++) DDX_Control(pDX, IDC_STC_WORK_CASE_0 + i, m_stcWorkCase[i]);	
	for (int i = 0; i < 7; i++) DDX_Control(pDX, IDC_LED_INDEX_DONE_0 + i, m_ledIndexDone[i]);
	for (int i = 0; i < 11; i++) DDX_Control(pDX, IDC_LED_MZ_DETECT_0 + i, m_ledMZDetect[i]);
	DDX_Control(pDX, IDC_STC_MAIN_INDEX_POS, m_stcIndexPos);

	DDX_Control(pDX, IDC_GRD_LOAD_MZ, m_grdLoadMZ);
	DDX_Control(pDX, IDC_GRD_UNLOAD_MZ, m_grdRdyMZ);

	DDX_Control(pDX, IDC_GRD_TOP_VISION, m_grdTopVision);
	DDX_Control(pDX, IDC_GRD_BTM_VISION, m_grdBtmVision);
	DDX_Control(pDX, IDC_GRD_MARKING, m_grdMarking);

	DDX_Control(pDX, IDC_STC_BARCODE_MGZ, m_stcBarcodeMGZ);	
	DDX_Control(pDX, IDC_STC_BARCODE_CTZIG, m_stcBarcodeCtZig);


	for (int i = 0; i < 7; i++) DDX_Control(pDX, IDC_STC_TRAY_NO_0 + i, m_stcTrayNo[i]);

	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_TAKT_0 + i, m_stcTakt[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_UPH_0 + i, m_stcUph[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_STC_DAY_0 + i, m_stcDay[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_LED_VISION_STATUS_0 + i, m_ledVisionStatus[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LED_EQUIP_OPTION_0 + i, m_ledEquipOption[i]);

	DDX_Control(pDX, IDC_LBL_OPER_ID, m_lblOperId);
	DDX_Control(pDX, IDC_STC_OPER_ID, m_stcOperId);
	DDX_Control(pDX, IDC_STC_MES_CONNECT, m_stcMesConnect);
	DDX_Control(pDX, IDC_STC_MES_ONLINE, m_stcMesOnline);

	m_pDY00 = g_objAJinAXL.Get_pDY00();
	m_pDY01 = g_objAJinAXL.Get_pDY01();
	m_pDY02 = g_objAJinAXL.Get_pDY02();
	m_pDY03 = g_objAJinAXL.Get_pDY03();

	DDX_Control(pDX, IDC_BUTTON1, m_Btn1);
	DDX_Control(pDX, IDC_BUTTON2, m_Btn2);
	DDX_Control(pDX, IDC_BTN_SIMUL1, m_Btn_Simul);

	for (int i = 0; i < _countof(m_rdoSwitchUI); i++) DDX_Control(pDX, IDC_RDO_SWITCH_UI_0 + i, m_rdoSwitchUI[i]);
	DDX_Control(pDX, IDC_GRD_LOG, m_grdLog);
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
	ON_MESSAGE(UM_UPDATE_DAILY_RESULT, &CWorkDlg::OnUpdateDailyResult)

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
	ON_BN_CLICKED(IDC_CHK_SIMUL, &CWorkDlg::OnBnClickedChkSimul)
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_RDO_SWITCH_UI_0, &CWorkDlg::OnBnClickedRdoSwitchUi0)
	ON_BN_CLICKED(IDC_RDO_SWITCH_UI_1, &CWorkDlg::OnBnClickedRdoSwitchUi1)
END_MESSAGE_MAP()

// CWorkDlg 메시지 처리기입니다.

void CWorkDlg::Initial_Controls() 
{
	pMainDlg = (CSingleLensDlg*)AfxGetApp()->GetMainWnd();

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
	m_stcBarcodeMGZ.Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0xFF, 0x00), RGB(0x00, 0x00, 0x00));
	m_stcBarcodeCtZig.Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0xFF, 0x00), RGB(0x00, 0x00, 0x00));
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
	
	for (int i = 0; i < 4; i++) m_ledEquipOption[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);

	m_stcMesConnect.Init_Ctrl("바탕", 8, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00));
	m_stcMesOnline.Init_Ctrl("바탕", 10, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00));
	m_lblOperId.Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x20, 0x20, 0x80));
	m_stcOperId.Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, RGB(0xD0, 0xD0, 0xD0));

	for (int i = 0; i < _countof(m_rdoSwitchUI); i++) m_rdoSwitchUI[i].Init_Ctrl("바탕", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT/*RGB(0xC0, 0xC0, 0xC0)*/, CRadioCS::emBlue, 0);

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
	m_chkSimulMode.ShowWindow(SW_HIDE);

#ifndef AJIN_BOARD_USE
	m_Btn_Simul.ShowWindow(SW_SHOW);
	m_Btn1.ShowWindow(SW_SHOW);
	m_Btn2.ShowWindow(SW_SHOW);
#else
	m_Btn_Simul.ShowWindow(SW_HIDE);
	m_Btn1.ShowWindow(SW_HIDE);
	m_Btn2.ShowWindow(SW_HIDE);
#endif
	
	//Top Grid 
	 CRect rectTop(1254, 642, 1454, 889);
	 m_wndTopGrid.Create( this, rectTop, IDC_GRID_TOPVISION, 16, 9);
	 	
	 for (int i = 0; i < 144; ++i)
	 {
		 m_wndTopGrid.SetCellNumber(i, g_objCommon.ConvertToMESNo(i+1));
	 }

	 //Btm Grid 
	 CRect rectBtm(1475, 642, 1675, 889);
	 m_wndBtmGrid.Create( this, rectBtm, IDC_GRID_BTMVISION, 16, 9);
	 for (int i = 0; i < 144; ++i)
	 {
		 m_wndBtmGrid.SetCellNumber(i, g_objCommon.ConvertToMESNo(i+1));
	 }

	 //Marking Grid 
	  CRect rectMark(1700, 642, 1900, 889);
	  m_wndMarkGrid.Create( this, rectMark, IDC_GRID_MARKING, 16, 9);
	  for (int i = 0; i < 144; ++i)
	 {
		 m_wndMarkGrid.SetCellNumber(i, g_objCommon.ConvertToMESNo(i+1));
	 }
	 
	  Set_ChangeRdo(1);
	  OnUpdateDailyResult(NULL, NULL);
	 
	 //Example - 0번 셀: 빨간색
	// m_wndTopGrid.SetCellBackgroundColor( 0, RGB(255, 100, 100));
	  
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CWorkDlg::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
		gData.dwTouched = GetTickCount();
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEMOVE:
	case WM_MOUSEWHEEL:	
		gData.dwTouched = GetTickCount();
		break;
	}

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
		EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

		m_strLog.Format("[Work] OnShowWindow - bShow");
		g_objLogFile.Save_HandlerLog(m_strLog);
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

		m_bmpBg.DeleteObject();

		if(pEquipData->bUseDoorLock) m_bmpBg.LoadBitmap(IDB_EQUIP_WORK);
		else m_bmpBg.LoadBitmap(IDB_EQUIP_DOOR);

	

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
	 
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	
	DX_DATA_03 *pDX03 = g_objAJinAXL.Get_pDX03();

	if (pDX03->iStartSw && !m_rdoWorkStart.GetCheck()) 
	{
		g_objLogFile.Save_HandlerLog("[Work Mode] START S/W push");
		m_rdoWorkStart.SetCheck(TRUE);
		//pMainDlg->Set_LotErrorLog("START", 903, "Start");
		g_objLogFile.Save_EfficiencyLog(0, "Run", 903, "Run Start");	//Start
		SetTimer(0, 100, NULL); return;
	} 
	else if (pDX03->iStopSw && !m_rdoWorkStop.GetCheck()) 
	{
		g_objLogFile.Save_HandlerLog("[Work Mode] STOP S/W push");
		MachineStopLog("STOP_BUTTON_PUSH");
		m_rdoWorkStop.SetCheck(TRUE);
		//pMainDlg->Set_LotErrorLog("STOP", 904, "Stop");
		g_objLogFile.Save_EfficiencyLog(0, "Stop", 903, "Stop Button Push");	//Stop
		SetTimer(0, 100, NULL); return;
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

			if (!Work_Start()) { m_rdoWorkStop.SetCheck(TRUE); SetTimer(0, 100, NULL); m_rdoWorkStart.SetCheck(FALSE); return; }

			m_bAutoRunning = TRUE;
			if (gData.bCycleStop && !m_bCycleStopRun) m_bCycleStopRun = TRUE;
			
			if(pEquipData->bUseDoorLock) g_objCommon.Locking_MainDoor(TRUE);
			else g_objCommon.Locking_MainDoor(FALSE);
				
			if (gAlm.bBegin)
			{
				g_objMesAgent.Reset_AlarmLog();
			}
			pMainDlg->Enable_ModeButton(FALSE);
			pMainDlg->Set_CurrentState(STATE_RUN);
						
			//If it was running before Stop, then run again 
			if (m_bLoadCVRun ) g_objCommon.Set_LoadCVRunCW(); theApp.uSleep(5);
			if (m_bUnloadCVRun) g_objCommon.Set_UnloadCVRunCW(); theApp.uSleep(5);
			m_bLoadCVRun = FALSE;
			m_bUnloadCVRun = FALSE;


			m_pDY03->oDustPowerOn = TRUE; g_objAJinAXL.Write_Output(3);

			g_objLogFile.Save_HandlerLog("[Work Mode] Main Thread Start");
			g_objSequenceMain.Begin_MainRunThread();

			if(pEquipData->bUseMES) g_objMesAgent.Set_EquipState(eEquipState::RUN);	//Run
			//g_objInspector.Set_StatusUpdate(VISION_ALL, 2);

		} 
		else
		{	// Auto Running
			if (!g_objSequenceMain.Is_MainThreadRun())
			{
				g_objLogFile.Save_HandlerLog("[Work Mode] Auto STOP");
				pMainDlg->Set_CurrentState(STATE_STOP);
			}
		}

	} 
	else if (m_rdoWorkStop.GetCheck()) 
	{
		

		if (m_bAutoRunning) // First AutoStop 
		{	
			m_chkNoTrayMode.SetCheck(FALSE);
			gData.bAgingMode = FALSE;

			m_bAutoRunning = FALSE;
			
			m_bLoadCVRun = m_pDY00->oLoadCVRun;
			m_bUnloadCVRun = m_pDY01->oUldCvRun;

			g_objCommon.Set_LoadCVStop(); theApp.uSleep(5);
			g_objCommon.Set_ElevCVStop(); theApp.uSleep(5);

			m_pDY03->oDustPowerOn = FALSE; g_objAJinAXL.Write_Output(3);

			g_objSequenceMain.End_MainRunThread(2000);
			theApp.uSleep(5);

			if(pEquipData->bUseMES) g_objMesAgent.Set_EquipState(eEquipState::DOWN);	//Down
			
			int nState = theApp.Get_MainState();
			if (nState != STATE_ALARM && nState != STATE_ERROR) pMainDlg->Set_CurrentState(STATE_STOP);
			//g_objInspector.Set_StatusUpdate(VISION_ALL, 1);

			m_rdoWorkStart.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
			m_rdoWorkStop.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);

			if(gData.bSimulMode )
			{
				//pass
			}
			else if(gData.bAgingMode)
			{
				//pass
			}
			else
			{
				g_objCommon.Save_MotionPos();
			}

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
		m_strLog.Format("[Work Mode]MGZ ID Deleted - %d", ID);
		g_objLogFile.Save_HandlerLog(m_strLog);

	}

	if(nTotalClick == 2)
	{
		if (g_objCommon.Show_MsgBox(2, "전체 Data를 삭제 하시겠습니까?") != IDOK) return;
		
		m_strLog.Format("[Work Mode]ALL MGZ ID Deleted - %d", ID);
		g_objLogFile.Save_HandlerLog(m_strLog);
		
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


	strLog.Format("[Work Mode]ZIG ID Rdo Clicked - %d", ID);
	g_objLogFile.Save_HandlerLog(strLog);
	

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

	strLog.Format("[Work Mode]ZIG ID Deleted - %d", ID);
	g_objLogFile.Save_HandlerLog(strLog);

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
	
	pMainDlg->Set_LotErrorLog("START", 903, "Start");
	g_objLogFile.Save_EfficiencyLog(0, "Run", 903, "Run Start");

	if(gLot.dwStopStart != 0)
	{	
		gLot.dwStopEnd = GetTickCount() - gLot.dwStopStart;
		for(int i = 0; i < 3; i++) 
		{
			gLot.dwStopTime[i] += gLot.dwStopEnd;
			for(int j = 0; j < 10; j++) gLot.dwStopTimeZig[i][j] += gLot.dwStopEnd;
		}
		gLot.dwStopStart = 0;
		gLot.dwStopEnd = 0;
	}

}

void CWorkDlg::OnBnClickedRdoWorkStop()
{
	g_objLogFile.Save_HandlerLog("[Work Mode] STOP button push");
	MachineStopLog("STOP_BUTTON_PUSH");
	
	pMainDlg->Set_LotErrorLog("STOP", 904, "Stop");
	g_objLogFile.Save_EfficiencyLog(0, "Stop", 903, "Stop Button Push");

	for(int i = 0; i < 3; i++) 
	{
		gLot.nStopCount[i]++;
		for(int j = 0; j < 10; j++) gLot.nStopCountZig[i][j]++;
	}

	gLot.dwErrorStart = 0;
	gLot.dwStopStart = 0;
	gLot.dwStopStart = GetTickCount();
	
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

	if(pEquipData->bUseMES)
	{
		if(!g_objMesAgent.Is_Connected() || !g_objMesAgent.Is_HostOnline())
		{
			g_objCommon.Show_MsgBox(1, "MES가 연결되지 않았습니다."); return FALSE; 
		}		
	}
	
	if(!pEquipData->bUseAutoRecipeChange)
	{
		if(g_objCommon.Show_MsgBox(2, "Auto Recipe Change 설정되어 있지 않습니다. 진행하시겠습니까?") != IDOK)
		{
			return FALSE;
		}
	}

	if(!pEquipData->bUseBtmVision || !pEquipData->bUseTopVision)
	{
		if(g_objCommon.Show_MsgBox(2, "Btm or Top Vision 설정되어 있지 않습니다. 진행하시겠습니까?") != IDOK)
		{
			return FALSE;
		}
	}

	if(pEquipData->bUseBtmVision || pEquipData->bUseTopVision)
	{
		BOOL ret =	g_objInspector.Check_Connect(VISION_PC1);
		if(!ret)
		{
			g_objCommon.Show_MsgBox(1, "Vision PC와 연결되지 않았습니다."); return FALSE; 
		}
	}


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
	if( SearchMZCVInfo() < 0 && !pEquipData->bUseMES )
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

	if(nZigFlag < 0 && !pEquipData->bUseMES) {g_objCommon.Show_MsgBox(1, "Please Input Coating Zig ID."); return FALSE;}
	if(nLensFlag < 0 && !pEquipData->bUseMES) {g_objCommon.Show_MsgBox(1, "Please Input Lens Cnt."); return FALSE;}



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

		if (strTemp.GetLength() < 2 && !pEquipData->bUseMES) { g_objCommon.Show_MsgBox(1, "Please Input Zig-ID."); return FALSE; }
				
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
					if (pEquipData->bUseDoorLock) { pDY03->oDoor08Unlock = FALSE; g_objAJinAXL.Write_Output(3); }
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
					if (pEquipData->bUseDoorLock) { pDY03->oDoor08Unlock = FALSE; g_objAJinAXL.Write_Output(3); }
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

	//m_stcBarcodeMGZ.SetWindowText(g_objBarcodeLot_Cognex.Get_BarcodeLot(eBarcode::MZ));
	//m_stcBarcodeCtZig.SetWindowText(g_objBarcodeLot_Cognex.Get_BarcodeLot(eBarcode::CtZig));
	
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
	m_ledEquipOption[2].Set_On(pEquipData->bUseMark);
	m_ledEquipOption[3].Set_On(pEquipData->bUseMES);
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
	int nLensNo = 0;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	if (nVision == eVision::TC)
	{	
		for (int i = 0; i < gData.nLensCntY; i++)
		{
			for (int j = 0; j < gData.nLensCntX; j++) 
			{

				if(pEquipData->nVisionDir == eVDir::fixY)
				{
					nLensNo = (gData.nLensCntX * i) + (j + 1);	
				}
				else if(pEquipData->nVisionDir == eVDir::fixX)
				{
					nLensNo = (gData.nLensCntY * j) + ( i+1 );
				}				

				if		(gData.InfoMainIndex[eMainIndex::Top][j][i] == eLensState::TopDone ) m_wndTopGrid.SetCellBackgroundColor(nLensNo-1, RGB(0xFF, 0xFF, 0x00));	// Reserve
				else if (gData.InfoMainIndex[eMainIndex::Top][j][i] == eLensState::TopReady) m_wndTopGrid.SetCellBackgroundColor(nLensNo-1, RGB(0xFF, 0xFF, 0xFF));	// Empty
				else				m_wndTopGrid.SetCellBackgroundColor(nLensNo-1, RGB(0x80, 0x80, 0x80));	// Error

			}
		}
	}

	if (nVision == eVision::BC)
	{		
		for (int i = 0; i < gData.nLensCntY; i++)
		{
			for (int j = 0; j < gData.nLensCntX; j++) 
			{
				if(pEquipData->nVisionDir == eVDir::fixY)
				{
					nLensNo = (gData.nLensCntX * i) + (j + 1);	
				}
				else if(pEquipData->nVisionDir == eVDir::fixX)
				{
					nLensNo = (gData.nLensCntY * j) + ( i + 1 );
				}				
				
				if		(gData.InfoMainIndex[eMainIndex::Btm][j][i] == eLensState::BtmDone ) m_wndBtmGrid.SetCellBackgroundColor(nLensNo-1, RGB(0xFF, 0xFF, 0x00));	// Reserve
				else if (gData.InfoMainIndex[eMainIndex::Btm][j][i] == eLensState::BtmReady) m_wndBtmGrid.SetCellBackgroundColor(nLensNo-1, RGB(0xFF, 0xFF, 0xFF));	// Empty
				else				m_wndBtmGrid.SetCellBackgroundColor(nLensNo-1, RGB(0x80, 0x80, 0x80));	// Error

			}
		}
	}

	if (nVision == eVision::MARKING)
	{		
		for (int i = 0; i < gData.nLensCntY; i++)
		{
			for (int j = 0; j < gData.nLensCntX; j++) 
			{
			
				if(pEquipData->nVisionDir == eVDir::fixY)
				{
					nLensNo = (gData.nLensCntX * i) + (j + 1);	
				}
				else if(pEquipData->nVisionDir == eVDir::fixX)
				{
					nLensNo = (gData.nLensCntY * j) + ( i + 1 );
				}				
				
				if		(gData.InfoMainIndex[eMainIndex::Mark][j][i] == eLensState::Marked ) m_wndMarkGrid.SetCellBackgroundColor(nLensNo-1, RGB(0xFF, 0x00, 0x00));	// Reserve
				else if (gData.InfoMainIndex[eMainIndex::Mark][j][i] == eLensState::NotMarked) m_wndMarkGrid.SetCellBackgroundColor(nLensNo-1, RGB(0x05, 0xFF, 0x05));	// Empty
				else if (gData.InfoMainIndex[eMainIndex::Mark][j][i] == eLensState::MarkReady) m_wndMarkGrid.SetCellBackgroundColor(nLensNo-1, RGB(0xFF, 0xFF, 0xFF));	// Empty
				else if (gData.InfoMainIndex[eMainIndex::Mark][j][i] == eLensState::Empty) m_wndMarkGrid.SetCellBackgroundColor(nLensNo-1, RGB(0x10, 0x10, 0x80));	// Error
				else				m_wndMarkGrid.SetCellBackgroundColor(nLensNo-1, RGB(0x80, 0x80, 0x80));	// Error
				
				
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

	/*if(wParam == 1 && gData.dUPHTray != 0)
	{
		strText.Format("%0.2lf", (3600.0 / gData.dUPHTray));
		m_stcTakt[0].SetWindowText(strText);

		strText.Format("%0.2lf", gData.dUPHTray);
		m_stcUph[0].SetWindowText(strText);
	}
	else*/ if(wParam == NULL)
	{
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

	}	
	return 0;
}


LRESULT CWorkDlg::OnLotStartEnd(WPARAM wParam, LPARAM lParam)
{
	
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


///////////////////////////////////////////////////////////////////////////////

void CWorkDlg::OnBnClickedButton1()
{
	DX_DATA_03 *pDX03 = g_objAJinAXL.Get_pDX03();
	pDX03->iUnloadOpenSw = TRUE;
	//CString strTemp;
	//for(int i = 1; i <= 141; i++)
	//{
	//	strTemp.Format("%d - %d", i, g_objCommon.ConvertToAVINo(i));

	//	g_objLogFile.Save_HandlerLog(strTemp);
	//}

	//g_objLogFile.Save_HandlerLog("End~~~~~~~~~~~~~~~");

	//for(int i = 1; i <= 144; i++)
	//{
	//	strTemp.Format("%d - %d", i, g_objCommon.ConvertToMESNo(i));

	//	g_objLogFile.Save_HandlerLog(strTemp);
	//}

	//g_objSequenceMain.Job_LotStart(1);
}

void CWorkDlg::OnBnClickedButton2()
{
	DX_DATA_03 *pDX03 = g_objAJinAXL.Get_pDX03();
	pDX03->iLoadOpenSw = TRUE;
	/*g_objSequenceMain.Job_LotEnd(1);
	OnUpdateUph(NULL, NULL);*/

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

void CWorkDlg::Init_TempLensMap(int nPos)
{
	int nCnt = 0;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	
	for(int i = 0; i < 10; i++)
	{
		gData.nTNoPick[nPos] = 1;
		gData.ZigMap[nPos][i] = FALSE;

		if(pEquipData->nVisionDir == eVDir::fixY)
		{
			Set_TempSlot(nPos, i+1, TRUE);			
		}
		else if(pEquipData->nVisionDir == eVDir::fixX)
		{
			Set_TempSlot(nPos, i+1, TRUE);			
		}	
	}
}

void CWorkDlg::Set_TempSlot(int nPos, int nSlot, BOOL bExist)
{
	if(nPos == eMZ::Load)
	{
		if(bExist)
		{
			gData.ZigMap[nPos][nSlot-1] = TRUE; // Zig 존재함 
			gData.InfoMZLoad[nSlot-1][0][0] = (int)eLensState::Init;
			gData.LensMap[nPos][nSlot-1][0][0] = eLensState::Init;
		}
		else
		{
			gData.ZigMap[nPos][nSlot-1] = FALSE; // Zig 존재함 
			gData.InfoMZLoad[nSlot-1][0][0] = (int)eLensState::None;
			gData.LensMap[nPos][nSlot-1][0][0] = eLensState::None;
		}

	}
	else if(nPos == eMZ::Ready)
	{
		if(bExist)
		{
			gData.ZigMap[nPos][nSlot-1] = TRUE; // Zig 존재함 
			gData.InfoMZReady[nSlot-1][0][0] = (int)eLensState::Init;
			gData.LensMap[nPos][nSlot-1][0][0] = eLensState::Init;
		}
		else
		{
			gData.ZigMap[nPos][nSlot-1] = FALSE; // Zig 존재함 
			gData.InfoMZReady[nSlot-1][0][0] = (int)eLensState::None;
			gData.LensMap[nPos][nSlot-1][0][0] = eLensState::None;
		}
	}	
	PostMessage(UM_UPDATE_MZ_INFO, eMZ::Load, NULL);
	PostMessage(UM_UPDATE_MZ_INFO, eMZ::Ready, NULL);
}



void CWorkDlg::init_LensMap()
{
	int nCnt = 0;

	int nXPos = 0, nYPos = 0;
	int nLNo = 0, nMESNo = 0;
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	
	//1. 전수 검사 
	/*	
	for (int i = 0; i < 144; i++)
	{
		nLNo = i+1;
		
		if(pEquipData->nVisionDir == eVDir::fixY)
		{
			nYPos = ((nLNo-1) / gData.nLensCntX);
			nXPos = (nLNo-1) % gData.nLensCntX;
		}
		else
		{
			nXPos = ((nLNo-1) / gData.nLensCntY);
			nYPos = (nLNo-1) % gData.nLensCntY;
		}	

		if(nLNo == 32 || nLNo == 68 || nLNo == 113)
		{
			gData.InfoFeeder[nXPos][nYPos] = eLensState::None;
			continue;
		}
		//if(gMes.sResult[i] == "OK") gData.InfoFeeder[nXPos][nYPos] = eLensState::Init;
				
		gData.InfoFeeder[nXPos][nYPos] = eLensState::Init;
	}
	*/

	//2. MES 갯수, 번호 기준 검사 
	for (int i = 0; i < 144; i++)
	{
		nLNo = i+1;
		nMESNo = g_objCommon.ConvertToMESNo(nLNo);

		if(pEquipData->nVisionDir == eVDir::fixY)
		{
			nYPos = ((nLNo-1) / gData.nLensCntX);
			nXPos = (nLNo-1) % gData.nLensCntX;
		}
		else
		{
			nXPos = ((nLNo-1) / gData.nLensCntY);
			nYPos = (nLNo-1) % gData.nLensCntY;
		}		

		if(nLNo == 32 || nLNo == 68 || nLNo == 113)
		{
			gData.InfoFeeder[nXPos][nYPos] = eLensState::None;			
		}
		else if(nMESNo > gMes.nPocketCnt) 
		{
			gData.InfoFeeder[nXPos][nYPos] = eLensState::None;
		}
		else if(nMESNo <= gMes.nPocketCnt)
		{
			gData.InfoFeeder[nXPos][nYPos] = eLensState::Init;
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
	if (!g_objSequenceMain.Get_IsAutoRun()) { AfxMessageBox("진행중인 Lot이 없어 처리를 할수 없습니다."); return; }
	if (m_rdoWorkStart.GetCheck() || !m_rdoWorkStop.GetCheck()) { AfxMessageBox("진행중인 Lot이 Stop되어 있어야 처리가 가능합니다."); return; }

	if (g_objCommon.Show_MsgBox(2, "If there were the modules in the machine, Please remove the modules by the CycleStop. Are you want to cancel this Lot?") != IDOK) return;

	g_objMesAgent.Set_LotAbort(gData.sLotID[eMZBuffer::Load], gMes.sHostRecipe[eMZ::Load]);
	g_objMesAgent.Set_EquipState(4);	// Idle

	g_objLogFile.Save_HandlerLog("[Work Mode] MES Abort Button Click.");
		
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

	if (g_dlgNoWork.IsWindowVisible()) return;
	g_dlgNoWork.Set_NoWorkAuto(FALSE);
	g_dlgNoWork.ShowWindow(SW_SHOW);

	m_strLog.Format("[Work Mode] Idle Report btn Click");
	g_objLogFile.Save_HandlerLog(m_strLog);
	
	/*if (g_dlgNoWork.IsWindowVisible()) g_dlgNoWork.ShowWindow(SW_HIDE);
	else g_dlgNoWork.ShowWindow(SW_SHOW);	*/
}

void CWorkDlg::Set_MZInfo(int nMZPos, CString sID)
{
	m_stcMZID[nMZPos].SetWindowText(sID);
	m_stcBarcodeMGZ.SetWindowText(sID);
}

void CWorkDlg::Set_CtZigInfo(int nMZPos, int nSlotNo, CString sID)
{
	int nNo = nMZPos*10 + (nSlotNo-1);
	m_stcZigID[nNo].SetWindowText(sID);
	m_stcBarcodeCtZig.SetWindowText(sID);
}

void CWorkDlg::Set_BmpDoorLock(BOOL bLock)
{
	m_bmpBg.DeleteObject();
	if(bLock) m_bmpBg.LoadBitmap(IDB_EQUIP_WORK);
	else m_bmpBg.LoadBitmap(IDB_EQUIP_DOOR);

	Invalidate();
}

void CWorkDlg::InsertMGZTestInfo(int nLensCnt)
{
	static int nIndex;
	CString strMGZID;

	CString sLensCnt;
	sLensCnt.Format("%d",nLensCnt);

	if(nIndex > 1000) nIndex = 0; 

	strMGZID.Format("Test-%d", nIndex++);

	m_stcMZID[2].SetWindowText(strMGZID);
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

	m_stcLensCnt[20].SetWindowText(sLensCnt);
	m_stcLensCnt[21].SetWindowText(sLensCnt);
	m_stcLensCnt[22].SetWindowText(sLensCnt);
	m_stcLensCnt[23].SetWindowText(sLensCnt);
	m_stcLensCnt[24].SetWindowText(sLensCnt);
	m_stcLensCnt[25].SetWindowText(sLensCnt);
	m_stcLensCnt[26].SetWindowText(sLensCnt);
	m_stcLensCnt[27].SetWindowText(sLensCnt);
	m_stcLensCnt[28].SetWindowText(sLensCnt);
	m_stcLensCnt[29].SetWindowText(sLensCnt);

	strMGZID.Format("Test-%d", nIndex++);

	m_stcMZID[3].SetWindowText(strMGZID);
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
	
	m_stcLensCnt[30].SetWindowText(sLensCnt);
	m_stcLensCnt[31].SetWindowText(sLensCnt);
	m_stcLensCnt[32].SetWindowText(sLensCnt);
	m_stcLensCnt[33].SetWindowText(sLensCnt);
	m_stcLensCnt[34].SetWindowText(sLensCnt);
	m_stcLensCnt[35].SetWindowText(sLensCnt);
	m_stcLensCnt[36].SetWindowText(sLensCnt);
	m_stcLensCnt[37].SetWindowText(sLensCnt);
	m_stcLensCnt[38].SetWindowText(sLensCnt);
	m_stcLensCnt[39].SetWindowText(sLensCnt);

	strMGZID.Format("Test-%d", nIndex++);

	m_stcMZID[4].SetWindowText(strMGZID);
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

	m_stcLensCnt[40].SetWindowText(sLensCnt);
	m_stcLensCnt[41].SetWindowText(sLensCnt);
	m_stcLensCnt[42].SetWindowText(sLensCnt);
	m_stcLensCnt[43].SetWindowText(sLensCnt);
	m_stcLensCnt[44].SetWindowText(sLensCnt);
	m_stcLensCnt[45].SetWindowText(sLensCnt);
	m_stcLensCnt[46].SetWindowText(sLensCnt);
	m_stcLensCnt[47].SetWindowText(sLensCnt);
	m_stcLensCnt[48].SetWindowText(sLensCnt);
	m_stcLensCnt[49].SetWindowText(sLensCnt);
}


void CWorkDlg::OnStnClickedStcHidden()
{
	if(m_chkNoTrayMode.IsWindowVisible())
	{
		m_chkNoTrayMode.ShowWindow(SW_HIDE);		
	}
	else
	{
		m_chkNoTrayMode.ShowWindow(SW_SHOW);		
	}	

	if(m_chkSimulMode.IsWindowVisible())
	{
		m_chkSimulMode.ShowWindow(SW_HIDE);		
	}
	else
	{
		m_chkSimulMode.ShowWindow(SW_SHOW);		
	}	
}


void CWorkDlg::OnBnClickedChkNoTray()
{
	g_objLogFile.Save_HandlerLog("[Work] Idle Run checked");
	
	gData.bAgingMode = m_chkNoTrayMode.GetCheck();
	InsertMGZTestInfo(144);
}



void CWorkDlg::OnBnClickedChkSimul()
{
	g_objLogFile.Save_HandlerLog("[Work] Simul Mode checked");

	gData.bSimulMode = m_chkSimulMode.GetCheck();
}


void CWorkDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	CString strLog;
	strLog.Format("%d, %d", (int)point.x, (int)point.y);
	if(gData.bSimulMode)
	{
		AfxMessageBox(strLog);
	}	



	CDialogEx::OnRButtonDown(nFlags, point);
}


void CWorkDlg::OnBnClickedRdoSwitchUi0()
{
	Set_ChangeRdo(0);
}


void CWorkDlg::OnBnClickedRdoSwitchUi1()
{
	Set_ChangeRdo(1);
}


void CWorkDlg::Set_ChangeRdo(int nSel)
{
	int nVisible = nSel == 0 ? SW_SHOW : SW_HIDE;
	if(nSel == 0)
	{
		m_grdLog.ShowWindow(SW_HIDE);
		for(int i = 2; i < 6; i++) m_grpMZ[i].ShowWindow(nVisible);
		for(int i = 2; i < 6; i++) m_rdoMZID[i].ShowWindow(nVisible);
		for(int i = 2; i < _countof(m_stcMZID); i++) m_stcMZID[i].ShowWindow(nVisible);
		for(int i = 20; i < _countof(m_stcZigID); i++) m_stcZigID[i].ShowWindow(nVisible);
		for(int i = 20; i < _countof(m_stcLensCnt); i++) m_stcLensCnt[i].ShowWindow(nVisible);
		for(int i = 0; i < _countof(m_rdoSelectNo); i++) m_rdoSelectNo[i].ShowWindow(nVisible);
		for(int i = 0; i < _countof(m_rdoSelectNo); i++) m_rdoSelectNo[i].ShowWindow(nVisible);
	}	
	
	if (nSel == 1) 
	{
		m_grdLog.ShowWindow(SW_SHOW);
		for(int i = 2; i < 6; i++) m_grpMZ[i].ShowWindow(nVisible);
		for(int i = 2; i < 6; i++) m_rdoMZID[i].ShowWindow(nVisible);
		for(int i = 2; i < _countof(m_stcMZID); i++) m_stcMZID[i].ShowWindow(nVisible);
		for(int i = 20; i < _countof(m_stcZigID); i++) m_stcZigID[i].ShowWindow(nVisible);
		for(int i = 20; i < _countof(m_stcLensCnt); i++) m_stcLensCnt[i].ShowWindow(nVisible);
		for(int i = 0; i < _countof(m_rdoSelectNo); i++) m_rdoSelectNo[i].ShowWindow(nVisible);
		for(int i = 0; i < _countof(m_rdoSelectNo); i++) m_rdoSelectNo[i].ShowWindow(nVisible);
		OnUpdateDailyResult(NULL, NULL);
	}
}



LRESULT CWorkDlg::OnUpdateDailyResult(WPARAM wParam, LPARAM lParam)
{
	m_grdLog.SetRedraw(FALSE);

	// 그리드 리셋 후 재구성
	const int nRowMax = 30;
	const int nColMax = 19;
	m_grdLog.Set_RowCount(1);
	m_grdLog.Set_ColCount(nColMax);
	COLORREF crBack;

	// Title
	m_grdLog.Set_ColWidth(0, 30);
	m_grdLog.Set_CellText(0, 0, "No.");
	m_grdLog.Set_ColWidth(1, 110);
	m_grdLog.Set_CellText(0, 1, "LotNum");
	m_grdLog.Set_ColWidth(2, 115);
	m_grdLog.Set_CellText(0, 2, "MGZ_ID");
	m_grdLog.Set_ColWidth(3, 115);
	m_grdLog.Set_CellText(0, 3, "Tray_ID");
	m_grdLog.Set_ColWidth(4, 55);
	m_grdLog.Set_CellText(0, 4, "Tray_No");
	m_grdLog.Set_ColWidth(5, 40);
	m_grdLog.Set_CellText(0, 5, "Cnt");
	m_grdLog.Set_ColWidth(6, 40);
	m_grdLog.Set_CellText(0, 6, "OK");
	m_grdLog.Set_ColWidth(7, 40);
	m_grdLog.Set_CellText(0, 7, "NG");
	m_grdLog.Set_ColWidth(8, 40);
	m_grdLog.Set_CellText(0, 8, "Yield");
	m_grdLog.Set_ColWidth(9, 105);
	m_grdLog.Set_CellText(0, 9, "Start_Time");
	m_grdLog.Set_ColWidth(10, 105);
	m_grdLog.Set_CellText(0,10, "End_Time");
	m_grdLog.Set_ColWidth(11, 50);
	m_grdLog.Set_CellText(0,11, "Tack1");
	m_grdLog.Set_CellText(0,12, "UPH1");
	m_grdLog.Set_ColWidth(13, 60);
	m_grdLog.Set_CellText(0,13, "Interval");
	m_grdLog.Set_ColWidth(14, 50);
	m_grdLog.Set_CellText(0,14, "Tack2");
	m_grdLog.Set_CellText(0,15, "UPH2");
	m_grdLog.Set_ColWidth(16, 40);
	m_grdLog.Set_CellText(0,16, "Stop");
	m_grdLog.Set_ColWidth(17, 80);
	m_grdLog.Set_CellText(0,17, "DownTime");
	m_grdLog.Set_ColWidth(18, 40);
	m_grdLog.Set_CellText(0,18, "GF");

	crBack = RGB(240, 240, 240);
	for (int col=0; col < nColMax; col++) { 
		m_grdLog.Set_CellFont(0, col, "Arial", 9, TRUE);
		m_grdLog.Set_CellBackClr(0, col, crBack) ;
	}

	/*SYSTEMTIME time;
	GetLocalTime(&time);
	CString strPath1 = "D:\\EVMS\\TP\\Log";
	CString strLastFile;
	strLastFile.Format("%s\\%04d%02d%02d_Assy_DailyResult.csv", strPath1, time.wYear, time.wMonth, time.wDay);
*/
	
	int  nOrder = 1;
	BOOL bOver = FALSE;
	CString strFilePath;
	CStringArray saDailyResult, saResult;
	while(TRUE)
	{
		g_objCommon.GetLatestFileName(gsCurrentDir+"\\LOG\\DailyResult", nOrder, strFilePath);
		g_objCommon.Get_Lines(30, strFilePath, saResult);

		for (int i = 0; i < (int)saResult.GetSize() / 2; i++)
		{
			CString strTemp = saResult[i];
			saResult[i] = saResult[(int)saResult.GetSize() - 1 - i];
			saResult[(int)saResult.GetSize() - 1 - i] = strTemp;
		}
		
		saDailyResult.Append(saResult);		
		
		if(saDailyResult.GetSize() > 30)
		{
			saDailyResult.RemoveAt(30, saDailyResult.GetSize()-30);
			break;
		}
		nOrder++;
	}	

	m_grdLog.Set_RowCount(saDailyResult.GetCount()+1);

	CString sText;
	crBack = RGB(204, 236, 255);

	int nCount = saDailyResult.GetCount();
	for (int i=0; i < nCount; i++) {
		int nRow = i+1;
		for (int col=0; col < nColMax; col++) {
			m_grdLog.Set_CellFont(nRow, col, "Arial", 7, FALSE);
			if (i % 2 == 0) m_grdLog.Set_CellBackClr(nRow, col, crBack) ;
		}

		sText.Format("%d", i+1);
		m_grdLog.Set_CellText(nRow, 0, sText);	// No

		sText = g_objCommon.Get_DataFromLine(saDailyResult[i], 6);//LotNum
 		m_grdLog.Set_CellText(nRow, 1, sText);	

		sText = g_objCommon.Get_DataFromLine(saDailyResult[i], 8); // MGZ_ID
		m_grdLog.Set_CellText(nRow, 2, sText);	

		sText = g_objCommon.Get_DataFromLine(saDailyResult[i], 9); // Tray_ID
		m_grdLog.Set_CellText(nRow, 3, sText);	

		sText = g_objCommon.Get_DataFromLine(saDailyResult[i],11); // Tray_No
		m_grdLog.Set_CellText(nRow, 4, sText);	

		sText = g_objCommon.Get_DataFromLine(saDailyResult[i],12); // Cnt
		m_grdLog.Set_CellText(nRow, 5, sText);	

		sText = g_objCommon.Get_DataFromLine(saDailyResult[i],13); // OK
		m_grdLog.Set_CellText(nRow, 6, sText);	

		sText = g_objCommon.Get_DataFromLine(saDailyResult[i],14); // NG
		m_grdLog.Set_CellText(nRow, 7, sText);	

		sText = g_objCommon.Get_DataFromLine(saDailyResult[i],15); // Yield
		m_grdLog.Set_CellText(nRow, 8, sText);	

		sText = g_objCommon.Get_DataFromLine(saDailyResult[i],16); // Start_Time
		sText.Delete(sText.GetLength()-4, 4);
		m_grdLog.Set_CellText(nRow, 9, sText);	

		sText = g_objCommon.Get_DataFromLine(saDailyResult[i],17); // End_Time
		sText.Delete(sText.GetLength()-4, 4);
		m_grdLog.Set_CellText(nRow,10, sText);	

		sText = g_objCommon.Get_DataFromLine(saDailyResult[i],18); // Tack1
		m_grdLog.Set_CellText(nRow,11, sText);	

		sText = g_objCommon.Get_DataFromLine(saDailyResult[i],19); // UPH1
		m_grdLog.Set_CellText(nRow,12, sText);	

		sText = g_objCommon.Get_DataFromLine(saDailyResult[i],20);
		m_grdLog.Set_CellText(nRow,13, sText);	// Interval
		sText = g_objCommon.Get_DataFromLine(saDailyResult[i],21);
		m_grdLog.Set_CellText(nRow,14, sText);	// Tack2
		sText = g_objCommon.Get_DataFromLine(saDailyResult[i],22);
		m_grdLog.Set_CellText(nRow,15, sText);	// UPH2

		sText = g_objCommon.Get_DataFromLine(saDailyResult[i],23);
		int nAlmCnt = atoi(sText);
		sText = g_objCommon.Get_DataFromLine(saDailyResult[i],25);
		int nStopCnt = atoi(sText);

		sText.Format("%d", nAlmCnt+nStopCnt);
		m_grdLog.Set_CellText(nRow,16, sText);	// Stop Cnt + Alm Cnt

		sText = g_objCommon.Get_DataFromLine(saDailyResult[i],24); // DownTime
		double dAlmTime = atof(sText);
		sText = g_objCommon.Get_DataFromLine(saDailyResult[i],26); // DownTime
		double dStopTime = atof(sText);

		sText.Format("%0.1lf", dAlmTime+dStopTime);
		m_grdLog.Set_CellText(nRow,17, sText);	

		sText = g_objCommon.Get_DataFromLine(saDailyResult[i],32);
		m_grdLog.Set_CellText(nRow,18, sText);	// GF
	}

	// 화면 다시 그리기 허용
	m_grdLog.SetRedraw(TRUE);

	// 완성된 화면을 한 번에 다시 그림
	m_grdLog.Invalidate(FALSE);
	m_grdLog.UpdateWindow();
	return 0;
}