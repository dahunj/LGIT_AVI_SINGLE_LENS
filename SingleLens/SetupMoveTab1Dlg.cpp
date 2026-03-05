// SetupMoveTab1Dlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "SingleLens.h"
#include "SetupMoveTab1Dlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "DataManager.h"
#include "Common.h"
#include "MESInterface.h"

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
	for (int i = 0; i < 10; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 35; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);

}

BEGIN_MESSAGE_MAP(CSetupMoveTab1Dlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	
END_MESSAGE_MAP()

// CSetupMoveTab1Dlg 메시지 처리기입니다.

void CSetupMoveTab1Dlg::Initial_Controls() 
{
	for (int i = 0; i < 10; i++) m_Group[i].Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	for (int i = 0; i < 35; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	
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


}

void CSetupMoveTab1Dlg::Save_MoveData()
{
 	CIniFileCS INI(gsCurrentDir + "\\System\\MoveData_" + gData.sVendor + ".ini");
	if (!INI.Check_File()) { AfxMessageBox("MoveData.ini File Not Found!!!"); return; }

	g_objCommon.Backup_File(gsCurrentDir + "\\System", "MoveData_" + gData.sVendor);

	


	g_objLogFile.Save_HandlerLog("[Setup - MoveTab Dialog 1] save");

	Cancel_MoveData();
}

void CSetupMoveTab1Dlg::Cancel_MoveData()
{
	g_objDataManager.Read_MoveData();
	Display_MoveData();
}

///////////////////////////////////////////////////////////////////////////////
