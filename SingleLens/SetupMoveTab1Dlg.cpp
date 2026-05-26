// SetupMoveTab1Dlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "SingleLens.h"
#include "SetupMoveTab1Dlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "DataManager.h"
#include "Common.h"


#include "AJinDefine.h"

// CSetupMoveTab1Dlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetupMoveTab1Dlg, CDialogEx)

CSetupMoveTab1Dlg::CSetupMoveTab1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupMoveTab1Dlg::IDD, pParent)
{
}

CSetupMoveTab1Dlg::~CSetupMoveTab1Dlg()
{
}

void CSetupMoveTab1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 31; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 10; i++) DDX_Control(pDX, IDC_STC_ELV_Z_0 + i, m_stcElvZ[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_FEEDER_X_0 + i, m_FeedUnitX[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_FEEDER_Y_0 + i, m_FeederY[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_TRAY_PICKER_Y_0 + i, m_TrayPickerY[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_TRAY_PICKER_Z_0 + i, m_TrayPickerZ[i]);

}

BEGIN_MESSAGE_MAP(CSetupMoveTab1Dlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_ELV_Z_0, IDC_STC_ELV_Z_9, OnStcElvZClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_FEEDER_X_0, IDC_STC_FEEDER_X_4, OnStcFeederXClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_FEEDER_Y_0, IDC_STC_FEEDER_Y_4, OnStcFeederYClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_TRAY_PICKER_Y_0, IDC_STC_TRAY_PICKER_Y_4, OnStcTrayPickerYClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_TRAY_PICKER_Z_0, IDC_STC_TRAY_PICKER_Z_4, OnStcTrayPickerZClick)
END_MESSAGE_MAP()

// CSetupMoveTab1Dlg 메시지 처리기입니다.

void CSetupMoveTab1Dlg::Initial_Controls() 
{
	for (int i = 0; i < 5; i++) m_Group[i].Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	for (int i = 0; i < 30; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	for (int i = 0; i < 10; i++) m_stcElvZ[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 5; i++)	 m_FeedUnitX[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 5; i++)	 m_FeederY[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 5; i++)	 m_TrayPickerY[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));
	for (int i = 0; i < 5; i++)	 m_TrayPickerZ[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));
}

BOOL CSetupMoveTab1Dlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(NULL, 5, 65, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CSetupMoveTab1Dlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSetupMoveTab1Dlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

	Display_MoveData();

	g_objLogFile.Save_HandlerLog("[Setup Move] Show Window - Tab1");
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupMoveTab1Dlg::Display_MoveData()
{
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	CString strData;

	for (int i = 0; i < 10; i++) { strData.Format("%0.3lf", pMoveData->dMZElevZ[i]);		m_stcElvZ[i].SetWindowText(strData); }
	for (int i = 0; i < 5; i++) { strData.Format("%0.3lf", pMoveData->dFeederX[i]);		m_FeedUnitX[i].SetWindowText(strData); }
	for (int i = 0; i < 5; i++) { strData.Format("%0.3lf", pMoveData->dFeederY[i]);		m_FeederY[i].SetWindowText(strData); }
	for (int i = 0; i < 5; i++) { strData.Format("%0.3lf", pMoveData->dTrayPickerY[i]);		m_TrayPickerY[i].SetWindowText(strData); }
	for (int i = 0; i < 5; i++) { strData.Format("%0.3lf", pMoveData->dTrayPickerZ[i]);		m_TrayPickerZ[i].SetWindowText(strData); }
}

void CSetupMoveTab1Dlg::Save_MoveData()
{
 	CIniFileCS INI(gsCurrentDir + "\\System\\MoveData" + ".ini");
	if (!INI.Check_File()) { AfxMessageBox("MoveData.ini File Not Found!!!"); return; }

	g_objCommon.Backup_File(gsCurrentDir + "\\System", "MoveData");

	CString strKey, strData;
	double dData;

	for (int i = 0; i < 10; i++) { strKey.Format("%02d", i);	m_stcElvZ[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("00_MZ_ELEVATOR_Z", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_FeedUnitX[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("01_ZIG_FEEDER_X", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_FeederY[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("02_ZIG_FEEDER_Y", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_TrayPickerY[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("03_ZIG_PICKER_Y", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_TrayPickerZ[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("04_ZIG_PICKER_Z", strKey, dData, "%0.3lf"); }
	

	g_objLogFile.Save_HandlerLog("[Setup - MoveTab Dialog 1] save");

	Cancel_MoveData();
}

void CSetupMoveTab1Dlg::Cancel_MoveData()
{
	g_objDataManager.Read_MoveData();
	Display_MoveData();
}

///////////////////////////////////////////////////////////////////////////////



void CSetupMoveTab1Dlg::OnStcElvZClick(UINT nID)
{
	int ID = nID - IDC_STC_ELV_Z_0;

	CString strOld, strNew;
	m_stcElvZ[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_MZ_ELEVATOR_Z) != IDOK) return;

	m_stcElvZ[ID].SetWindowText(strNew);
}

void CSetupMoveTab1Dlg::OnStcFeederXClick(UINT nID)
{
	int ID = nID - IDC_STC_FEEDER_X_0;

	CString strOld, strNew;
	m_FeedUnitX[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_ZIG_FEEDER_X) != IDOK) return;

	m_FeedUnitX[ID].SetWindowText(strNew);
}

void CSetupMoveTab1Dlg::OnStcFeederYClick(UINT nID)
{
	int ID = nID - IDC_STC_FEEDER_Y_0;

	CString strOld, strNew;
	m_FeederY[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_ZIG_FEEDER_Y) != IDOK) return;

	m_FeederY[ID].SetWindowText(strNew);
}

void CSetupMoveTab1Dlg::OnStcTrayPickerYClick(UINT nID)
{
	int ID = nID - IDC_STC_TRAY_PICKER_Y_0;

	CString strOld, strNew;
	m_TrayPickerY[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_ZIG_PICKER_Y) != IDOK) return;

	m_TrayPickerY[ID].SetWindowText(strNew);
}

void CSetupMoveTab1Dlg::OnStcTrayPickerZClick(UINT nID)
{
	int ID = nID - IDC_STC_TRAY_PICKER_Z_0;

	CString strOld, strNew;
	m_TrayPickerZ[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_ZIG_PICKER_Z) != IDOK) return;

	m_TrayPickerZ[ID].SetWindowText(strNew);
}