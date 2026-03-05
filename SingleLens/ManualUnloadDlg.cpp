// ManualNgDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "SingleLens.h"
#include "ManualUnloadDlg.h"
#include "afxdialogex.h"
#include "math.h"

#include "LogFile.h"
#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"

// CManualNgDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualUnloadDlg, CDialogEx)

CManualUnloadDlg::CManualUnloadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualUnloadDlg::IDD, pParent)
{
}

CManualUnloadDlg::~CManualUnloadDlg()
{
}

void CManualUnloadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 16; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 10; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);

}

BEGIN_MESSAGE_MAP(CManualUnloadDlg, CDialogEx)
	ON_WM_SHOWWINDOW()

END_MESSAGE_MAP()

// CManualUnloadDlg 메시지 처리기입니다.

void CManualUnloadDlg::Initial_Controls() 
{
	
}

BOOL CManualUnloadDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CManualUnloadDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualUnloadDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

	Display_Status();

	
	m_strLog.Format("[Manual Unload] Show Window");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualUnloadDlg::Display_Status()
{
	

	
}

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
