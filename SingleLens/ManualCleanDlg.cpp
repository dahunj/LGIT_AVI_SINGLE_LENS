// ManualCleanDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "SingleLens.h"
#include "ManualCleanDlg.h"
#include "afxdialogex.h"
#include "math.h"

#include "LogFile.h"
#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"
#include "SequenceMain.h"

// CManualCleanDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualCleanDlg, CDialogEx)

CManualCleanDlg::CManualCleanDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualCleanDlg::IDD, pParent)
{
}

CManualCleanDlg::~CManualCleanDlg()
{
}

void CManualCleanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//for (int i = 0; i < 14; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	//for (int i = 0; i <  8; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);

}

BEGIN_MESSAGE_MAP(CManualCleanDlg, CDialogEx)
	ON_WM_SHOWWINDOW()

	END_MESSAGE_MAP()

// CManualCleanDlg 메시지 처리기입니다.

void CManualCleanDlg::Initial_Controls() 
{
	//for (int i =  0; i <  2; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);
	//for (int i =  2; i <  5; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xD0, 0x10, 0x10), COLOR_DEFAULT);
	//for (int i =  5; i <  8; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xD0, 0x10, 0xD0), COLOR_DEFAULT);
	//for (int i =  8; i < 12; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xFF, 0x90, 0x00), COLOR_DEFAULT);
	//for (int i = 12; i < 14; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x30, 0x80, 0x00), COLOR_DEFAULT);
	//for (int i =  0; i <  8; i++) m_Label[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, RGB(0xB0, 0xB0, 0xB0));

}

BOOL CManualCleanDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CManualCleanDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualCleanDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

	Display_Status();
	
	m_strLog.Format("[Manual Clean & Top Vision] Show Window");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualCleanDlg::Display_Status()
{
	CString strPos;
	

	
}

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
