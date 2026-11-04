// ManualDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "SingleLens.h"
#include "ManualDlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "Common.h"
#include "DataManager.h"

// CManualDlg 대화 상자입니다.

CManualDlg g_dlgManual;

IMPLEMENT_DYNAMIC(CManualDlg, CDialogEx)

CManualDlg::CManualDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualDlg::IDD, pParent)
{
}

CManualDlg::~CManualDlg()
{
}

void CManualDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_MANUAL_BACK, m_picManualBack);
	DDX_Control(pDX, IDC_RDO_MANUAL_ELEVATOR, m_rdoManualElev);
	DDX_Control(pDX, IDC_RDO_MANUAL_LOAD, m_rdoManualLoad);
	DDX_Control(pDX, IDC_RDO_MANUAL_CLEAN_TOP, m_rdoManualClean);
	DDX_Control(pDX, IDC_RDO_MANUAL_BTM_MARK, m_rdoManualBtm);
	DDX_Control(pDX, IDC_RDO_MANUAL_REPEAT, m_rdoManualIndex);
	DDX_Control(pDX, IDC_RDO_MANUAL_DOOR_LOCK, m_rdoManualDoorLock);
	DDX_Control(pDX, IDC_RDO_MANUAL_DOOR_UNLOCK, m_rdoManualDoorUnlock);
}

BEGIN_MESSAGE_MAP(CManualDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RDO_MANUAL_ELEVATOR, &CManualDlg::OnBnClickedRdoManualElev)
	ON_BN_CLICKED(IDC_RDO_MANUAL_LOAD, &CManualDlg::OnBnClickedRdoManualLoad)
	ON_BN_CLICKED(IDC_RDO_MANUAL_CLEAN_TOP, &CManualDlg::OnBnClickedRdoManualClean)
	ON_BN_CLICKED(IDC_RDO_MANUAL_BTM_MARK, &CManualDlg::OnBnClickedRdoManualBtm)
	ON_BN_CLICKED(IDC_RDO_MANUAL_REPEAT, &CManualDlg::OnBnClickedRdoManualIndex)
	ON_BN_CLICKED(IDC_RDO_MANUAL_DOOR_LOCK, &CManualDlg::OnBnClickedRdoManualDoorLock)
	ON_BN_CLICKED(IDC_RDO_MANUAL_DOOR_UNLOCK, &CManualDlg::OnBnClickedRdoManualDoorUnlock)
END_MESSAGE_MAP()

// CManualDlg 메시지 처리기입니다.

void CManualDlg::Initial_Controls() 
{
	m_picManualBack.Init_Ctrl(COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xF0));

	m_rdoManualElev.Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	m_rdoManualLoad.Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	m_rdoManualClean.Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	m_rdoManualBtm.Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	m_rdoManualDoorLock.Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	m_rdoManualDoorUnlock.Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	m_rdoManualIndex.Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
}

BOOL CManualDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 75, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	pMainDlg = (CSingleLensDlg*)AfxGetApp()->GetMainWnd();

	m_pManualElevDlg = new CManualElevDlg(this);
	m_pManualElevDlg->Create(IDD_MANUAL_ELEV_DLG, this);

	m_pManualLoadDlg = new CManualLoadDlg(this);
	m_pManualLoadDlg->Create(IDD_MANUAL_LOAD_DLG, this);

	m_pManualCleanDlg = new CManualCleanDlg(this);
	m_pManualCleanDlg->Create(IDD_MANUAL_CLEAN_TOP_DLG, this);

	m_pManualBtmDlg = new CManualBtmDlg(this);
	m_pManualBtmDlg->Create(IDD_MANUAL_BTM_MARK_DLG, this);

	m_pManualIndexDlg = new CManualIndexDlg(this);
	m_pManualIndexDlg->Create(IDD_MANUAL_MAIN_INDEX_DLG, this);

		// Load Dlg Visible
	m_rdoManualElev.SetCheck(TRUE);
	m_rdoManualElev.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CManualDlg::PreTranslateMessage(MSG* pMsg) 
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

void CManualDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();

	m_pManualBtmDlg->DestroyWindow();
	m_pManualCleanDlg->DestroyWindow();
	m_pManualLoadDlg->DestroyWindow();
	m_pManualElevDlg->DestroyWindow();
	m_pManualIndexDlg->DestroyWindow();

	if (m_pManualBtmDlg) delete m_pManualBtmDlg;
	if (m_pManualCleanDlg) delete m_pManualCleanDlg;
	if (m_pManualLoadDlg) delete m_pManualLoadDlg;
	if (m_pManualElevDlg) delete m_pManualElevDlg;
	if (m_pManualIndexDlg) delete m_pManualIndexDlg;
	
	m_pManualBtmDlg = NULL;
	m_pManualCleanDlg = NULL;
	m_pManualLoadDlg = NULL;
	m_pManualElevDlg = NULL;
	m_pManualIndexDlg = NULL;
}

void CManualDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) 
	{
		

		if (m_rdoManualElev.GetCheck()) m_pManualElevDlg->ShowWindow(SW_SHOW);
		if (m_rdoManualLoad.GetCheck()) m_pManualLoadDlg->ShowWindow(SW_SHOW);
		if (m_rdoManualClean.GetCheck()) m_pManualCleanDlg->ShowWindow(SW_SHOW);
		if (m_rdoManualBtm.GetCheck()) m_pManualBtmDlg->ShowWindow(SW_SHOW);
		if (m_rdoManualIndex.GetCheck()) m_pManualIndexDlg->ShowWindow(SW_SHOW);

		EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
		if (pEquipData->bUseDoorLock) {
			g_objCommon.Locking_MainDoor(TRUE);
			m_rdoManualDoorLock.SetCheck(TRUE);
			m_rdoManualDoorLock.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
			m_rdoManualDoorUnlock.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
		} else {
			g_objCommon.Locking_MainDoor(FALSE);
			m_rdoManualDoorUnlock.SetCheck(TRUE);
			m_rdoManualDoorUnlock.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
			m_rdoManualDoorLock.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
		}

		SetTimer(0, 100, NULL);

	} else {
		KillTimer(0);

		g_objCommon.Locking_MainDoor(FALSE);

		if (m_rdoManualElev.GetCheck()) m_pManualElevDlg->ShowWindow(SW_HIDE);
		if (m_rdoManualLoad.GetCheck()) m_pManualLoadDlg->ShowWindow(SW_HIDE);
		if (m_rdoManualClean.GetCheck()) m_pManualCleanDlg->ShowWindow(SW_HIDE);
		if (m_rdoManualBtm.GetCheck()) m_pManualBtmDlg->ShowWindow(SW_HIDE);
		if (m_rdoManualIndex.GetCheck()) m_pManualIndexDlg->ShowWindow(SW_HIDE);
	}
}

void CManualDlg::OnTimer(UINT_PTR nIDEvent) 
{
	KillTimer(0);

	int nState = theApp.Get_MainState();
	if (nState != STATE_ERROR) g_objCommon.Check_MainEmgAir();	// Emg & Main Air

	if (m_pManualElevDlg->IsWindowVisible()) m_pManualElevDlg->Display_Status();
	else if (m_pManualLoadDlg->IsWindowVisible()) m_pManualLoadDlg->Display_Status();
	else if (m_pManualCleanDlg->IsWindowVisible()) m_pManualCleanDlg->Display_Status();
	else if (m_pManualBtmDlg->IsWindowVisible()) m_pManualBtmDlg->Display_Status();

	SetTimer(0, 100, NULL);
	CDialogEx::OnTimer(nIDEvent);
}

void CManualDlg::OnBnClickedRdoManualElev()
{
	if (m_pManualElevDlg->IsWindowVisible()) return;
	Hide_Windows();
	g_objLogFile.Save_HandlerLog("[Manual - Elevator] Start");
	m_rdoManualElev.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoManualElev.SetCheck(TRUE);
	m_pManualElevDlg->ShowWindow(SW_SHOW);
}

void CManualDlg::OnBnClickedRdoManualLoad()
{
	if (m_pManualLoadDlg->IsWindowVisible()) return;
	Hide_Windows();
	g_objLogFile.Save_HandlerLog("[Manual - Index] Start");
	m_rdoManualLoad.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoManualLoad.SetCheck(TRUE);
	m_pManualLoadDlg->ShowWindow(SW_SHOW);
}

void CManualDlg::OnBnClickedRdoManualClean()
{
	if (m_pManualCleanDlg->IsWindowVisible()) return;
	Hide_Windows();
	g_objLogFile.Save_HandlerLog("[Manual - Clean] Start");
	m_rdoManualClean.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoManualClean.SetCheck(TRUE);
	m_pManualCleanDlg->ShowWindow(SW_SHOW);
}

void CManualDlg::OnBnClickedRdoManualBtm()
{
	if (m_pManualBtmDlg->IsWindowVisible()) return;
	Hide_Windows();
	g_objLogFile.Save_HandlerLog("[Manual - Btm & Mark] Start");
	m_rdoManualBtm.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoManualBtm.SetCheck(TRUE);
	m_pManualBtmDlg->ShowWindow(SW_SHOW);
}

void CManualDlg::OnBnClickedRdoManualIndex()
{
	if (m_pManualIndexDlg->IsWindowVisible()) return;
	Hide_Windows();
	g_objLogFile.Save_HandlerLog("[Manual - Repeat] Start");
	m_rdoManualIndex.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	m_pManualIndexDlg->ShowWindow(SW_SHOW);
	m_rdoManualIndex.SetCheck(TRUE);
}


void CManualDlg::OnBnClickedRdoManualDoorLock()
{
	if (!m_rdoManualDoorLock.GetCheck()) return;
	m_rdoManualDoorLock.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoManualDoorUnlock.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	g_objCommon.Locking_MainDoor(TRUE);
}

void CManualDlg::OnBnClickedRdoManualDoorUnlock()
{
	if (!m_rdoManualDoorUnlock.GetCheck()) return;
	m_rdoManualDoorUnlock.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoManualDoorLock.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	g_objCommon.Locking_MainDoor(FALSE);
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CManualDlg::Hide_Windows()
{
	m_pManualElevDlg->ShowWindow(SW_HIDE);
	m_pManualLoadDlg->ShowWindow(SW_HIDE);
	m_pManualCleanDlg->ShowWindow(SW_HIDE);
	m_pManualBtmDlg->ShowWindow(SW_HIDE);
	m_pManualIndexDlg->ShowWindow(SW_HIDE);

	m_rdoManualElev.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoManualLoad.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoManualClean.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoManualBtm.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoManualIndex.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);

	m_rdoManualElev.SetCheck(FALSE);
	m_rdoManualLoad.SetCheck(FALSE);
	m_rdoManualClean.SetCheck(FALSE);
	m_rdoManualBtm.SetCheck(FALSE);
	m_rdoManualIndex.SetCheck(FALSE);
}

void CManualDlg::Set_ManualPos(int nPos)
{
	m_rdoManualElev.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoManualLoad.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoManualClean.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoManualBtm.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoManualIndex.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);

	if (nPos == 1) { m_rdoManualElev.SetCheck(TRUE);    m_rdoManualElev.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT); }
	if (nPos == 2) { m_rdoManualLoad.SetCheck(TRUE);   m_rdoManualLoad.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT); }
	if (nPos == 3) { m_rdoManualClean.SetCheck(TRUE);   m_rdoManualClean.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT); }
	if (nPos == 4) { m_rdoManualBtm.SetCheck(TRUE);  m_rdoManualBtm.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT); }
	if (nPos == 5) { m_rdoManualIndex.SetCheck(TRUE);  m_rdoManualIndex.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT); }
}

///////////////////////////////////////////////////////////////////////////////
