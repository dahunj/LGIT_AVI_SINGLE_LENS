// ManualIndexDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "SingleLens.h"
#include "ManualIndexDlg.h"
#include "afxdialogex.h"
#include "math.h"

#include "LogFile.h"
#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"
#include "SequenceMain.h"
#include "LoadCell.h"

// CManualIndexDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualIndexDlg, CDialogEx)

CManualIndexDlg::CManualIndexDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualIndexDlg::IDD, pParent)
{
}

CManualIndexDlg::~CManualIndexDlg()
{
}

void CManualIndexDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i <  9; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i <  6; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	
	
}

BEGIN_MESSAGE_MAP(CManualIndexDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	
END_MESSAGE_MAP()

// CManualIndexDlg 메시지 처리기입니다.

void CManualIndexDlg::Initial_Controls() 
{
	for (int i = 0; i <  3; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xD0, 0x10, 0x10), COLOR_DEFAULT);
	for (int i = 3; i <  4; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xD0, 0x10, 0xD0), COLOR_DEFAULT);
	for (int i = 4; i <  5; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);
	for (int i = 5; i <  9; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x00, 0x80, 0x40), COLOR_DEFAULT);
	for (int i = 0; i <  6; i++) m_Label[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, RGB(0xB0, 0xB0, 0xB0));
	

}

BOOL CManualIndexDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CManualIndexDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualIndexDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

	
	m_strLog.Format("[Manual Index] Show Window");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::Display_Status()
{
	
}

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
