// ErrorDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "SingleLens.h"
#include "ErrorDlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "Common.h"
#include "MesAgent.h"

#include "SequenceInit.h"
#include "SequenceMain.h"

#include "WorkDlg.h"
#include "ManualDlg.h"
#include "SingleLensDlg.h"

// CErrorDlg 대화 상자입니다.
CErrorDlg g_dlgError;

IMPLEMENT_DYNAMIC(CErrorDlg, CDialogEx)

CErrorDlg::CErrorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CErrorDlg::IDD, pParent)
{
}

CErrorDlg::~CErrorDlg()
{
}

void CErrorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_ERR_BACK_0 + i, m_stcErrBack[i]);
	DDX_Control(pDX, IDC_STC_ERR_TITLE, m_stcErrTitle);
	DDX_Control(pDX, IDC_IMAGE_0, m_Image);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_LED_MAIN_AIR_0 + i, m_ledMainAir[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LED_EMG_SW_0 + i, m_ledEmgSw[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_LED_DOOR_OPEN_0 + i, m_ledDoorOpen[i]);
	for (int i = 0; i < 14; i++) DDX_Control(pDX, IDC_STC_ERR_POS_0 + i, m_stcErrPos[i]);
	DDX_Control(pDX, IDC_STC_ERR_NO, m_stcErrNo);
	DDX_Control(pDX, IDC_STC_MSG_BACK, m_stcMsgBack);
	DDX_Control(pDX, IDC_STC_ERR_MSG, m_stcErrMsg);
	DDX_Control(pDX, IDC_BTN_ERR_BUZZ_OFF, m_btnErrBuzzOff);
	DDX_Control(pDX, IDC_BTN_ERR_SKIP, m_btnErrSkip);
	DDX_Control(pDX, IDC_BTN_ERR_RETRY, m_btnErrRetry);
	DDX_Control(pDX, IDC_BTN_ERR_OK, m_btnErrOK);
	DDX_Control(pDX, IDC_BTN_ERR_SYSTEM_EXIT, m_btnErrSystemExit);
	DDX_Control(pDX, IDC_BTN_ERR_TO_MANUAL, m_btnErrToManual);
}

BEGIN_MESSAGE_MAP(CErrorDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_ERR_BUZZ_OFF, &CErrorDlg::OnBnClickedBtnErrBuzzOff)
	ON_BN_CLICKED(IDC_BTN_ERR_SKIP, &CErrorDlg::OnBnClickedBtnErrSkip)
	ON_BN_CLICKED(IDC_BTN_ERR_RETRY, &CErrorDlg::OnBnClickedBtnErrRetry)
	ON_BN_CLICKED(IDC_BTN_ERR_OK, &CErrorDlg::OnBnClickedBtnErrOk)
	ON_BN_CLICKED(IDC_BTN_ERR_SYSTEM_EXIT, &CErrorDlg::OnBnClickedBtnErrSystemExit)
	ON_BN_CLICKED(IDC_BTN_ERR_TO_MANUAL, &CErrorDlg::OnBnClickedBtnErrToManual)
END_MESSAGE_MAP()

// CErrorDlg 메시지 처리기입니다.

void CErrorDlg::Initial_Controls() 
{
	for (int i = 0; i < 4; i++) m_Group[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);
	for (int i = 0; i < 8; i++) m_Label[i].Init_Ctrl("바탕", 20, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	for (int i = 0; i < 4; i++) m_stcErrBack[i].Set_Color(COLOR_DEFAULT, RGB(0x00, 0x00, 0xFF));

	m_stcErrTitle.Init_Ctrl("바탕", 24, TRUE, RGB(0xFF, 0xFF, 0xFF),RGB(0xFF, 0x00, 0x00));

	m_bmpImage.LoadBitmap(IDB_EQUIP_ERROR);
	m_Image.SetBitmap(m_bmpImage);
// 	m_Image.SetWindowPos(NULL, 0, 0, 1060, 600, SWP_NOZORDER | SWP_NOMOVE);	// 원본 960x540 (1680x945)
	m_Image.SetWindowPos(NULL, 0, 0, 933, 677, SWP_NOZORDER | SWP_NOMOVE);	// 533x387 : 원본 800x580 (933x677)

	for (int i = 0; i < 2; i++) m_ledMainAir[i].Init_Ctrl("바탕", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em24);
	for (int i = 0; i < 4; i++) m_ledEmgSw[i].Init_Ctrl("바탕", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emRed, CLedCS::em24);
	for (int i = 0; i < 8; i++) m_ledDoorOpen[i].Init_Ctrl("바탕", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em24);

	for (int i = 0; i < 14; i++) m_stcErrPos[i].Init_Ctrl("바탕", 12, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00));

	m_stcErrNo.Init_Ctrl("바탕", 30, TRUE, RGB(0x00, 0x00, 0xFF), RGB(0xFF, 0xF0, 0xE0));
	m_stcMsgBack.Init_Ctrl("바탕", 16, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xE0, 0xF0, 0xF0));
	m_stcErrMsg.Init_Ctrl("바탕", 16, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xE0, 0xF0, 0xF0));

	m_btnErrBuzzOff.Init_Ctrl("바탕", 16, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnErrSkip.Init_Ctrl("바탕", 16, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnErrRetry.Init_Ctrl("바탕", 16, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnErrOK.Init_Ctrl("바탕", 16, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, IDI_OK, CButtonCS::emLeft);
	m_btnErrSystemExit.Init_Ctrl("바탕", 16, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnErrToManual.Init_Ctrl("바탕", 18, TRUE, RGB(0xFF, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);
}

BOOL CErrorDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	Initial_Controls();

	m_nErrNo = 0;
	m_nErrCode = BASE_ERR_CODE;	// Cap Attach Type Error Code 변경 10000 ~ 19999
	m_nBackColorLoop = 0;
	m_nErrorPos = 0;
	m_strErrSubMsg = "";

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CErrorDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CErrorDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	CSingleLensDlg *pMainDlg = (CSingleLensDlg*)AfxGetApp()->GetMainWnd();
	if (bShow) {
		BringWindowToTop();	// 화면 위로...

		CString strErrNo, strErrCode, strErrMsg, strShow, strLog;
		CString strMes = "";
		
		pMainDlg->Set_CurrentState(STATE_ERROR);

		g_objMesAgent.Set_ErrorUpdate(1, strErrNo);

		strErrNo.Format("%04d", m_nErrNo);
		strErrCode.Format("%05d", m_nErrCode);
		m_stcErrNo.SetWindowText(strErrCode);
		
		CIniFileCS INI(gsCurrentDir + "\\System\\ErrorList.ini");
		if (!INI.Check_File()) { AfxMessageBox("ErrorList.ini File Not Found!!!"); return; }
		strErrMsg = INI.Get_String("ERROR", strErrNo, "");

		CString strErrPick = "";		
			
		if (m_nErrNo > 10 && m_nErrNo < 20) g_objSequenceInit.Set_InitComplete(FALSE);	// 3,4,5,6


		int nZoneNo = (m_nErrNo - 3000) / 100;
		if (nZoneNo >= 0 && nZoneNo <= 30) g_objLogFile.Save_EfficiencyLog(nZoneNo, "Down", m_nErrNo, m_strErrMsg);


		m_strErrMsg = strErrMsg + strErrPick + strMes + m_strErrSubMsg;

		if (m_nErrNo == 3408 ||
			m_nErrNo == 4605 || m_nErrNo == 4905 // vision 
			|| m_nErrNo == 3472 || m_nErrNo == 3474) //barcode 
		{
			m_btnErrRetry.EnableWindow(TRUE);
			m_btnErrRetry.ShowWindow(SW_SHOW);
		}
		else
		{
			m_btnErrRetry.EnableWindow(FALSE);
			m_btnErrRetry.ShowWindow(SW_HIDE);
		}


		strShow = m_strErrMsg;
		if (strShow.Left(1) == "#") strShow.Delete(0);
		strShow.Replace("#", "\n\n");
		m_stcErrMsg.SetWindowText(strShow);

		SYSTEMTIME time;
		GetLocalTime(&time);
		for (int i = 2; i > 0; i--) gData.sAlarmTime[i] = gData.sAlarmTime[i - 1];
		for (int i = 2; i > 0; i--) gData.sAlarmList[i] = gData.sAlarmList[i - 1];
		gData.sAlarmTime[0].Format("%02d:%02d:%02d", time.wHour, time.wMinute, time.wSecond);
		gData.sAlarmList[0].Format("[%s] %s", strErrNo, m_strErrMsg);

		strLog.Format("%s,%s,%s", gData.sMZID[eMZ::Load], strErrNo, m_strErrMsg);
		g_objLogFile.Save_AlarmLog(strLog);
		
		Set_AlarmLog(m_nErrCode, m_strErrMsg);

		strLog.Format("[Error Mode] Error No ==> %s", strErrNo);
		g_objLogFile.Save_HandlerLog(strLog);

		pMainDlg->Set_LotErrorLog("ERROR", m_nErrCode, m_strErrMsg);

		m_nBackColorLoop = 0;
		
		m_stcErrPos[m_nErrorPos].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0x00, 0x00));

		SetTimer(0, 100, NULL);

	} else {
		KillTimer(0);

		m_strErrSubMsg = "";
		for (int i = 0; i < 12; i++) m_stcErrPos[i].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00));

		pMainDlg->Set_BuzzerFlicker(FALSE);
		if (g_objSequenceInit.Get_InitComplete()) pMainDlg->Set_CurrentState(STATE_STOP);
		else pMainDlg->Set_CurrentState(STATE_NONE);

		pMainDlg->Set_LotErrorLog("RESET", 905, "Error Reset");

		int nZoneNo = (m_nErrNo - 3000) / 100;
		if (nZoneNo >= 0 && nZoneNo <= 30) g_objLogFile.Save_EfficiencyLog(nZoneNo, "Reset", 905, "Error Reset");

		g_objLogFile.Save_HandlerLog("[Error Mode] Close Error");

		
	}
}

void CErrorDlg::OnTimer(UINT_PTR nIDEvent) 
{
	KillTimer(0);

	//DX_DATA_12 *pDX12 = g_objAJinAXL.Get_pDX12();
	//DX_DATA_13 *pDX13 = g_objAJinAXL.Get_pDX13();

	//if (pDX12->iResetSw) {
	//	OnBnClickedBtnErrOk();
	//	return;
	//}

	//if (m_nBackColorLoop == 1) {
	//	for (int i = 0; i < 4; i++) m_stcErrBack[i].Set_Color(COLOR_DEFAULT, RGB(0x00, 0x00, 0xFF));
	//} else if (m_nBackColorLoop == 6) {
	//	for (int i = 0; i < 4; i++) m_stcErrBack[i].Set_Color(COLOR_DEFAULT, RGB(0xFF, 0xFF, 0x00));
	//} else if (m_nBackColorLoop == 10) m_nBackColorLoop = 0;
	//m_nBackColorLoop++;

	//m_ledMainAir[0].Set_On(pDX12->iMainAir1);
	//m_ledMainAir[1].Set_On(pDX12->iMainAir2);

	//m_ledEmgSw[0].Set_On(pDX12->iEmgSw1);
	//m_ledEmgSw[1].Set_On(pDX12->iEmgSw2);
	//m_ledEmgSw[2].Set_On(pDX12->iEmgSw3);

	//for (int i = 0; i < 13; i++) m_ledDoorOpen[i].Set_On((pDX13->nValue >> (i + 18)) & 1);

	SetTimer(0, 100, NULL);
	CDialogEx::OnTimer(nIDEvent);
}

void CErrorDlg::OnBnClickedBtnErrBuzzOff()
{
	CSingleLensDlg *pMainDlg = (CSingleLensDlg*)AfxGetApp()->GetMainWnd();
	pMainDlg->Set_BuzzerFlicker(FALSE);
}

void CErrorDlg::OnBnClickedBtnErrSkip()
{
// 	g_objLogFile.Save_HandlerLog("[Error Mode] SKIP button push");
// 
// 	if (m_nErrNo == 3325) {		// Inspection Not Complete
// 	}
// 
// 	g_dlgWork.Set_AutoRun(TRUE);
// 
// 	ShowWindow(SW_HIDE);
}

void CErrorDlg::OnBnClickedBtnErrRetry()
{
	g_objLogFile.Save_HandlerLog("[Error Mode] RETRY button push");

	switch (m_nErrNo) 
	{
	case 3408:
		g_objSequenceMain.Set_MainRunCase(AUTO_MZ_ELEVATOR, 9);
		break;
	case 4605:
		g_objSequenceMain.Set_MainRunCase(AUTO_TOP_INSPECT, 3);
		break;
	case 4905:
		g_objSequenceMain.Set_MainRunCase(AUTO_BTM_INSPECT, 3);
		break;

	case 3472:
		g_objSequenceMain.Set_MainRunCase(AUTO_MZ_ELEVATOR, 3);
		break;
	case 3473:
		g_objSequenceMain.Set_MainRunCase(AUTO_MZ_ELEVATOR, 74);
		break;

	}

	ShowWindow(SW_HIDE);
	g_dlgWork.Set_AutoRun(TRUE);
}

void CErrorDlg::OnBnClickedBtnErrOk()
{
	
	ShowWindow(SW_HIDE);
	g_objLogFile.Save_HandlerLog("[Error Mode] OK button push");
}

void CErrorDlg::OnBnClickedBtnErrSystemExit()
{
	if (g_objCommon.Show_MsgBox(2, "Do you want to exit the program?") != IDOK) return;
	CSingleLensDlg *pMainDlg = (CSingleLensDlg*)AfxGetApp()->GetMainWnd();
	pMainDlg->Exit_System(EXIT_SYSTEM_AJIN);
}

void CErrorDlg::OnBnClickedBtnErrToManual()
{
	CString strLog;
// 	if (m_nErrNo == 3606) {
// 		gData.bCmAlignSkip = TRUE;
// 		ShowWindow(SW_HIDE);
// 
// 		strLog.Format("[Error Mode] CM Skip button push");
// 		g_objLogFile.Save_HandlerLog(strLog);
// 
// 	} else if (m_nErrNo == 3706 || m_nErrNo == 6220) {
// 		gData.bCapDirSkip = TRUE; gData.bCapDirRetry = FALSE;
// 		ShowWindow(SW_HIDE);
// 
// 		strLog.Format("[Error Mode] Cap Skip button push");
// 		g_objLogFile.Save_HandlerLog(strLog);
// 
// 	} else {
		int nManualPos = 0;
		if (m_nErrorPos >   0 && m_nErrorPos <=   3) nManualPos = 1;	// Load 1, 2, 3
		if (m_nErrorPos ==  4 || m_nErrorPos ==   8) nManualPos = 2;	// Index 4, 8
		if (m_nErrorPos >=  5 && m_nErrorPos <    8) nManualPos = 3;	// Cap 5, 6, 7
		if (m_nErrorPos >   8 && m_nErrorPos <=  13) nManualPos = 4;	// Unload 9, 10, 11
		if (nManualPos == 0) return;

		ShowWindow(SW_HIDE);

		g_dlgManual.Set_ManualPos(nManualPos);
		CSingleLensDlg *pMainDlg = (CSingleLensDlg*)AfxGetApp()->GetMainWnd();
		pMainDlg->Set_CurrentMode(MODE_MANUAL);

		strLog.Format("[Error Mode] Manual button push - Pos[%d]", nManualPos);
		g_objLogFile.Save_HandlerLog(strLog);
// 	}
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CErrorDlg::Set_AlarmLog(int nErrNo, CString sErrMsg)
{
	
	
}

///////////////////////////////////////////////////////////////////////////////
