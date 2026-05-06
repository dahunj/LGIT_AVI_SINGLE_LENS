// SetupMoveTab3Dlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "SingleLens.h"
#include "SetupMoveTab3Dlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "DataManager.h"
#include "Common.h"
#include "MESInterface.h"

#include "AJinDefine.h"

// CSetupMoveTab3Dlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetupMoveTab3Dlg, CDialogEx)

CSetupMoveTab3Dlg::CSetupMoveTab3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupMoveTab3Dlg::IDD, pParent)
{
}

CSetupMoveTab3Dlg::~CSetupMoveTab3Dlg()
{
}

void CSetupMoveTab3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 1; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_INDEX_R_0 + i, m_stcMainIndexR[i]);

	
	
}

BEGIN_MESSAGE_MAP(CSetupMoveTab3Dlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_INDEX_R_0, IDC_STC_INDEX_R_4, OnStcMainIndexRClick)
	//ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_TRANS_STAGE_Z_0, IDC_STC_TRANS_STAGE_Z_2, OnStcTransStageZClick)
	
END_MESSAGE_MAP()

// CSetupMoveTab3Dlg 메시지 처리기입니다.

void CSetupMoveTab3Dlg::Initial_Controls() 
{
	for (int i = 0; i < 1; i++) m_Group[i].Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	for (int i = 0; i < 5; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	for (int i = 0; i < 5; i++) m_stcMainIndexR[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xC0, 0xFF, 0xF0));
	
}

BOOL CSetupMoveTab3Dlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(NULL, 5, 65, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CSetupMoveTab3Dlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSetupMoveTab3Dlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

	Display_MoveData();

	g_objLogFile.Save_HandlerLog("[Setup Move] Show Window - Tab3");
}
//

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupMoveTab3Dlg::Display_MoveData()
{
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	CString strData;

	for (int i = 0; i < 5; i++) { strData.Format("%0.3lf", pMoveData->dMainIndexR[i]);		m_stcMainIndexR[i].SetWindowText(strData); }

}

void CSetupMoveTab3Dlg::Save_MoveData()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\MoveData" + ".ini");
	if (!INI.Check_File()) { AfxMessageBox("MoveData.ini File Not Found!!!"); return; }

	g_objCommon.Backup_File(gsCurrentDir + "\\System", "MoveData");
	
	CString strKey, strData;
	double dData;

	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcMainIndexR[i].GetWindowText(strData); dData = atof(strData); INI.Set_Double("14_MAIN_INDEX_R", strKey, dData, "%0.3lf"); }
	

	g_objLogFile.Save_HandlerLog("[Setup - MoveTab Dialog 3] save");

	Cancel_MoveData();
}

void CSetupMoveTab3Dlg::Cancel_MoveData()
{
	g_objDataManager.Read_MoveData();
	Display_MoveData();
}

///////////////////////////////////////////////////////////////////////////////



void CSetupMoveTab3Dlg::OnStcMainIndexRClick(UINT nID)
{
	int ID = nID - IDC_STC_INDEX_R_0;

	CString strOld, strNew;
	m_stcMainIndexR[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_MAIN_INDEX_R) != IDOK) return;

	m_stcMainIndexR[ID].SetWindowText(strNew);
}