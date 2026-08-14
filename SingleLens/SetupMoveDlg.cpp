// SetupMoveDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "SingleLens.h"
#include "SetupMoveDlg.h"
#include "afxdialogex.h"

// CSetupMoveDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetupMoveDlg, CDialogEx)

CSetupMoveDlg::CSetupMoveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupMoveDlg::IDD, pParent)
{
}

CSetupMoveDlg::~CSetupMoveDlg()
{
}

void CSetupMoveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_SETUP_MOVE, m_tabSetupMove);
}

BEGIN_MESSAGE_MAP(CSetupMoveDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_SETUP_MOVE, &CSetupMoveDlg::OnTcnSelchangingTabSetupMove)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SETUP_MOVE, &CSetupMoveDlg::OnTcnSelchangeTabSetupMove)
END_MESSAGE_MAP()

// CSetupMoveDlg 메시지 처리기입니다.

void CSetupMoveDlg::Initial_Controls() 
{
	m_tabSetupMove.InsertItem(0, "Elv / Feeder / Picker");
	m_tabSetupMove.InsertItem(1, "Top / Btm / Mark");
	m_tabSetupMove.InsertItem(2, "Main Index");

	m_tabSetupMove.SetItemSize(CSize(560, 60));
	m_tabSetupMove.Init_Ctrl("바탕", 14, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);
}

BOOL CSetupMoveDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	m_pSetupMoveTab1Dlg = new CSetupMoveTab1Dlg(&m_tabSetupMove);
	m_pSetupMoveTab1Dlg->Create(IDD_SETUP_MOVE_TAB1_DLG, &m_tabSetupMove);

	m_pSetupMoveTab2Dlg = new CSetupMoveTab2Dlg(&m_tabSetupMove);
	m_pSetupMoveTab2Dlg->Create(IDD_SETUP_MOVE_TAB2_DLG, &m_tabSetupMove);

	m_pSetupMoveTab3Dlg = new CSetupMoveTab3Dlg(&m_tabSetupMove);
	m_pSetupMoveTab3Dlg->Create(IDD_SETUP_MOVE_TAB3_DLG, &m_tabSetupMove);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CSetupMoveDlg::PreTranslateMessage(MSG* pMsg) 
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

void CSetupMoveDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();

	m_pSetupMoveTab3Dlg->DestroyWindow();
	m_pSetupMoveTab2Dlg->DestroyWindow();
	m_pSetupMoveTab1Dlg->DestroyWindow();

	if (m_pSetupMoveTab3Dlg) delete m_pSetupMoveTab3Dlg;
	if (m_pSetupMoveTab2Dlg) delete m_pSetupMoveTab2Dlg;
	if (m_pSetupMoveTab1Dlg) delete m_pSetupMoveTab1Dlg;

	m_pSetupMoveTab3Dlg = NULL;
	m_pSetupMoveTab2Dlg = NULL;
	m_pSetupMoveTab1Dlg = NULL;
}

void CSetupMoveDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	int nTab = m_tabSetupMove.GetCurSel();
	if (bShow) {
		if (nTab == 0) m_pSetupMoveTab1Dlg->ShowWindow(SW_SHOW);
		if (nTab == 1) m_pSetupMoveTab2Dlg->ShowWindow(SW_SHOW);
		if (nTab == 2) m_pSetupMoveTab3Dlg->ShowWindow(SW_SHOW);
	} else {
		if (nTab == 0) m_pSetupMoveTab1Dlg->ShowWindow(SW_HIDE);
		if (nTab == 1) m_pSetupMoveTab2Dlg->ShowWindow(SW_HIDE);
		if (nTab == 2) m_pSetupMoveTab3Dlg->ShowWindow(SW_HIDE);
	}
}

void CSetupMoveDlg::OnTcnSelchangingTabSetupMove(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nTab = m_tabSetupMove.GetCurSel();
	if (nTab == 0) m_pSetupMoveTab1Dlg->ShowWindow(SW_HIDE);
	if (nTab == 1) m_pSetupMoveTab2Dlg->ShowWindow(SW_HIDE);
	if (nTab == 2) m_pSetupMoveTab3Dlg->ShowWindow(SW_HIDE);
	*pResult = 0;
}

void CSetupMoveDlg::OnTcnSelchangeTabSetupMove(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nTab = m_tabSetupMove.GetCurSel();
	if (nTab == 0) m_pSetupMoveTab1Dlg->ShowWindow(SW_SHOW);
	if (nTab == 1) m_pSetupMoveTab2Dlg->ShowWindow(SW_SHOW);
	if (nTab == 2) m_pSetupMoveTab3Dlg->ShowWindow(SW_SHOW);
	*pResult = 0;
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupMoveDlg::Save_MoveData() 
{
	int nTab = m_tabSetupMove.GetCurSel();
	if (nTab == 0) m_pSetupMoveTab1Dlg->Save_MoveData();
	if (nTab == 1) m_pSetupMoveTab2Dlg->Save_MoveData();
	if (nTab == 2) m_pSetupMoveTab3Dlg->Save_MoveData();
}

void CSetupMoveDlg::Cancel_MoveData() 
{
	int nTab = m_tabSetupMove.GetCurSel();
	if (nTab == 0) m_pSetupMoveTab1Dlg->Cancel_MoveData();
	if (nTab == 1) m_pSetupMoveTab2Dlg->Cancel_MoveData();
	if (nTab == 2) m_pSetupMoveTab3Dlg->Cancel_MoveData();
}

///////////////////////////////////////////////////////////////////////////////
