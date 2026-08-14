// SetupMoveTab2Dlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "SingleLens.h"
#include "SetupMoveTab2Dlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "DataManager.h"
#include "Common.h"


#include "AJinDefine.h"

// CSetupMoveTab2Dlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetupMoveTab2Dlg, CDialogEx)

CSetupMoveTab2Dlg::CSetupMoveTab2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupMoveTab2Dlg::IDD, pParent)
{
}

CSetupMoveTab2Dlg::~CSetupMoveTab2Dlg()
{
}

void CSetupMoveTab2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 9; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 45; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_TOP_INSPECT_X_0 + i, m_stcTopInspectX[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_TOP_INSPECT_Y_0 + i, m_stcTopInspectY[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_TOP_INSPECT_Z_0 + i, m_stcTopInspectZ[i]);

	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_BTM_INSPECT_X_0 + i, m_stcBtmInspectX[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_BTM_INSPECT_Y_0 + i, m_stcBtmInspectY[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_BTM_INSPECT_Z_0 + i, m_stcBtmInspectZ[i]);

	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_MARK_UNIT_X_0 + i, m_stcMarkUnitX[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_MARK_UNIT_Y_0 + i, m_stcMarkUnitY[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_MARK_UNIT_Z_0 + i, m_stcMarkUnitZ[i]);

}

BEGIN_MESSAGE_MAP(CSetupMoveTab2Dlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_TOP_INSPECT_X_0, IDC_STC_TOP_INSPECT_X_4, OnStcTopInspectXClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_TOP_INSPECT_Y_0, IDC_STC_TOP_INSPECT_Y_4, OnStcTopInspectYClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_TOP_INSPECT_Z_0, IDC_STC_TOP_INSPECT_Z_4, OnStcTopInspectZClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_BTM_INSPECT_X_0, IDC_STC_BTM_INSPECT_X_4, OnStcBtmInspectXClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_BTM_INSPECT_Y_0, IDC_STC_BTM_INSPECT_Y_4, OnStcBtmInspectYClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_BTM_INSPECT_Z_0, IDC_STC_BTM_INSPECT_Z_4, OnStcBtmInspectZClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_MARK_UNIT_X_0, IDC_STC_MARK_UNIT_X_4, OnStcMarkUnitXClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_MARK_UNIT_Y_0, IDC_STC_MARK_UNIT_Y_4, OnStcMarkUnitYClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_MARK_UNIT_Z_0, IDC_STC_MARK_UNIT_Z_4, OnStcMarkUnitZClick)
	
END_MESSAGE_MAP()

// CSetupMoveTab2Dlg 메시지 처리기입니다.

void CSetupMoveTab2Dlg::Initial_Controls() 
{
	for (int i = 0; i < 9; i++) m_Group[i].Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	for (int i = 0; i < 45; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));

	for (int i = 0; i < 5; i++)  m_stcTopInspectX[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 5; i++)  m_stcTopInspectY[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 5; i++)  m_stcTopInspectZ[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));

	for (int i = 0; i < 5; i++)  m_stcBtmInspectX[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 5; i++)  m_stcBtmInspectY[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 5; i++)  m_stcBtmInspectZ[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));

	for (int i = 0; i < 5; i++)  m_stcMarkUnitX[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 5; i++)  m_stcMarkUnitY[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 5; i++)  m_stcMarkUnitZ[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	//for (int i = 0; i < 1; i++) m_stcMainIndexR[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	
}

BOOL CSetupMoveTab2Dlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(NULL, 5, 65, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CSetupMoveTab2Dlg::PreTranslateMessage(MSG* pMsg) 
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

void CSetupMoveTab2Dlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

	Display_MoveData();

	g_objLogFile.Save_HandlerLog("[Setup Move] Show Window - Tab2");
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupMoveTab2Dlg::Display_MoveData()
{
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	CString strData;

	for (int i = 0; i < 5; i++) { strData.Format("%0.3lf", pMoveData->dTopInspectorX[i]);	m_stcTopInspectX[i].SetWindowText(strData); }
	for (int i = 0; i < 5; i++) { strData.Format("%0.3lf", pMoveData->dTopInspectorY[i]);	m_stcTopInspectY[i].SetWindowText(strData); }
	for (int i = 0; i < 5; i++) { strData.Format("%0.3lf", pMoveData->dTopInspectorZ[i]);	m_stcTopInspectZ[i].SetWindowText(strData); }
	for (int i = 0; i < 5; i++) { strData.Format("%0.3lf", pMoveData->dBtmInspectorX[i]);	m_stcBtmInspectX[i].SetWindowText(strData); }
	for (int i = 0; i < 5; i++) { strData.Format("%0.3lf", pMoveData->dBtmInspectorY[i]);	m_stcBtmInspectY[i].SetWindowText(strData); }
	for (int i = 0; i < 5; i++) { strData.Format("%0.3lf", pMoveData->dBtmInspectorZ[i]);	m_stcBtmInspectZ[i].SetWindowText(strData); }
	for (int i = 0; i < 5; i++) { strData.Format("%0.3lf", pMoveData->dMarkUnitX[i]);	m_stcMarkUnitX[i].SetWindowText(strData); }
	for (int i = 0; i < 5; i++) { strData.Format("%0.3lf", pMoveData->dMarkUnitY[i]);	m_stcMarkUnitY[i].SetWindowText(strData); }
	for (int i = 0; i < 5; i++) { strData.Format("%0.3lf", pMoveData->dMarkUnitZ[i]);	m_stcMarkUnitZ[i].SetWindowText(strData); }
	
}

void CSetupMoveTab2Dlg::Save_MoveData()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\MoveData" + ".ini");
	if (!INI.Check_File()) { AfxMessageBox("MoveData.ini File Not Found!!!"); return; }

	g_objCommon.Backup_File(gsCurrentDir + "\\System", "MoveData");

	CString strKey, strData;
	double dData;

	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcTopInspectX[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("05_TOP_INSPECTOR_X", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcTopInspectY[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("06_TOP_INSPECTOR_Y", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcTopInspectZ[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("07_TOP_INSPECTOR_Z", strKey, dData, "%0.3lf"); }
	
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcBtmInspectX[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("08_BTM_INSPECTOR_X", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcBtmInspectY[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("09_BTM_INSPECTOR_Y", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcBtmInspectZ[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("10_BTM_INSPECTOR_Z", strKey, dData, "%0.3lf"); }
	
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcMarkUnitX[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("11_MARK_UNIT_X", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcMarkUnitY[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("12_MARK_UNIT_Y", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcMarkUnitZ[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("13_MARK_UNIT_Z", strKey, dData, "%0.3lf"); }
	
	g_objLogFile.Save_HandlerLog("[Setup - MoveTab Dialog 2] save");

	Cancel_MoveData();
}

void CSetupMoveTab2Dlg::Cancel_MoveData()
{
	g_objDataManager.Read_MoveData();
	Display_MoveData();
}

///////////////////////////////////////////////////////////////////////////////

void CSetupMoveTab2Dlg::OnStcTopInspectXClick(UINT nID)
{
	int ID = nID - IDC_STC_TOP_INSPECT_X_0;

	CString strOld, strNew;
	m_stcTopInspectX[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_TOP_INSPECTOR_X) != IDOK) return;

	m_stcTopInspectX[ID].SetWindowText(strNew);
}

void CSetupMoveTab2Dlg::OnStcTopInspectYClick(UINT nID)
{
	int ID = nID - IDC_STC_TOP_INSPECT_Y_0;

	CString strOld, strNew;
	m_stcTopInspectY[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_TOP_INSPECTOR_Y) != IDOK) return;

	m_stcTopInspectY[ID].SetWindowText(strNew);
}

void CSetupMoveTab2Dlg::OnStcTopInspectZClick(UINT nID)
{
	int ID = nID - IDC_STC_TOP_INSPECT_Z_0;

	CString strOld, strNew;
	m_stcTopInspectZ[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_TOP_INSPECTOR_Z) != IDOK) return;

	m_stcTopInspectZ[ID].SetWindowText(strNew);
}


void CSetupMoveTab2Dlg::OnStcBtmInspectXClick(UINT nID)
{
	int ID = nID - IDC_STC_BTM_INSPECT_X_0;

	CString strOld, strNew;
	m_stcBtmInspectX[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_BTM_INSPECTOR_X) != IDOK) return;

	m_stcBtmInspectX[ID].SetWindowText(strNew);
}

void CSetupMoveTab2Dlg::OnStcBtmInspectYClick(UINT nID)
{
	int ID = nID - IDC_STC_BTM_INSPECT_Y_0;

	CString strOld, strNew;
	m_stcBtmInspectY[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_BTM_INSPECTOR_Y) != IDOK) return;

	m_stcBtmInspectY[ID].SetWindowText(strNew);
}

void CSetupMoveTab2Dlg::OnStcBtmInspectZClick(UINT nID)
{
	int ID = nID - IDC_STC_BTM_INSPECT_Z_0;

	CString strOld, strNew;
	m_stcBtmInspectZ[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_BTM_INSPECTOR_Z) != IDOK) return;

	m_stcBtmInspectZ[ID].SetWindowText(strNew);
}


void CSetupMoveTab2Dlg::OnStcMarkUnitXClick(UINT nID)
{
	int ID = nID - IDC_STC_MARK_UNIT_X_0;

	CString strOld, strNew;
	m_stcMarkUnitX[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_MARK_UNIT_X) != IDOK) return;

	m_stcMarkUnitX[ID].SetWindowText(strNew);
}

void CSetupMoveTab2Dlg::OnStcMarkUnitYClick(UINT nID)
{
	int ID = nID - IDC_STC_MARK_UNIT_Y_0;

	CString strOld, strNew;
	m_stcMarkUnitY[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_MARK_UNIT_Y) != IDOK) return;

	m_stcMarkUnitY[ID].SetWindowText(strNew);
}

void CSetupMoveTab2Dlg::OnStcMarkUnitZClick(UINT nID)
{
	int ID = nID - IDC_STC_MARK_UNIT_Z_0;

	CString strOld, strNew;
	m_stcMarkUnitZ[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_MARK_UNIT_Z) != IDOK) return;

	m_stcMarkUnitZ[ID].SetWindowText(strNew);
}
