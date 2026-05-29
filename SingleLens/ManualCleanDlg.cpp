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
#include "Inspector.h"

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
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_AXIS_POS_0 + i, m_stcAxisPos[i]);
	for (int i = 0; i <  12; i++) DDX_Control(pDX, IDC_BTN_CLEANER_IO_0 + i, m_BtnCleanerIO[i]);
	for (int i = 0; i <  8; i++) DDX_Control(pDX, IDC_LED_CLEANER_IO_0 + i, m_LedCleanerIO[i]);
	for (int i = 0; i <  4; i++) DDX_Control(pDX, IDC_BTN_TOP_INSPECT_X_0 + i, m_BtnTopInspectX[i]);
	for (int i = 0; i <  4; i++) DDX_Control(pDX, IDC_BTN_TOP_INSPECT_Y_0 + i, m_BtnTopInspectY[i]);
	for (int i = 0; i <  4; i++) DDX_Control(pDX, IDC_BTN_TOP_INSPECT_Z_0 + i, m_BtnTopInspectZ[i]);
}

BEGIN_MESSAGE_MAP(CManualCleanDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_CLEANER_IO_0, IDC_BTN_CLEANER_IO_11, OnBtnCleanerIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TOP_INSPECT_X_0, IDC_BTN_TOP_INSPECT_X_3, OnBtnTopInspectXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TOP_INSPECT_Y_0, IDC_BTN_TOP_INSPECT_Y_3, OnBtnTopInspectYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TOP_INSPECT_Z_0, IDC_BTN_TOP_INSPECT_Z_3, OnBtnTopInspectZClick)
	ON_BN_CLICKED(IDC_BUTTON1, &CManualCleanDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BTN_CASERESET, &CManualCleanDlg::OnBnClickedBtnCasereset)
	ON_BN_CLICKED(IDC_BTN_AMOVE, &CManualCleanDlg::OnBnClickedBtnAmove)
	ON_BN_CLICKED(IDC_BTN_CASERESET2, &CManualCleanDlg::OnBnClickedBtnCasereset2)
	ON_BN_CLICKED(IDC_BUTTON2, &CManualCleanDlg::OnBnClickedButton2)
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

	m_nScanCase = 0;

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
	
	double dPos = g_objAJinAXL.Get_Position(AX_TOP_INSPECTOR_X);
	strPos.Format("%0.3lf", dPos);
	m_stcAxisPos[0].SetWindowText(strPos);
	
	dPos = g_objAJinAXL.Get_Position(AX_TOP_INSPECTOR_Y);
	strPos.Format("%0.3lf", dPos);
	m_stcAxisPos[1].SetWindowText(strPos);

	dPos = g_objAJinAXL.Get_Position(AX_TOP_INSPECTOR_Z);
	strPos.Format("%0.3lf", dPos);
	m_stcAxisPos[2].SetWindowText(strPos);

	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();

	m_LedCleanerIO[0].Set_On(pDX02->iCleanerTopDn);
	m_LedCleanerIO[1].Set_On(pDX02->iCleanerTopUp);
	m_LedCleanerIO[2].Set_On(pDX02->iCleanerTopFwd);
	m_LedCleanerIO[3].Set_On(pDX02->iCleanerTopBwd);
	m_LedCleanerIO[4].Set_On(pDX02->iCleanerBtmDn);
	m_LedCleanerIO[5].Set_On(pDX02->iCleanerBtmUp);
	m_LedCleanerIO[6].Set_On(pDX02->iCleanerBtmFwd);
	m_LedCleanerIO[7].Set_On(pDX02->iCleanerBtmBwd);
}



void CManualCleanDlg::OnBtnCleanerIOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	DY_DATA_02 *pDY02 = g_objAJinAXL.Get_pDY02();

	int nIndex = nID - IDC_BTN_CLEANER_IO_0;

	if(nIndex == eCleanerIO::TopDn)
	{
		pDY02->oCleanerTopDn = TRUE; pDY02->oCleanerTopUp = FALSE;
	}
	if(nIndex == eCleanerIO::TopUp)
	{
		pDY02->oCleanerTopDn = FALSE; pDY02->oCleanerTopUp = TRUE;
	}
	if(nIndex == eCleanerIO::TopFwd)
	{
		pDY02->oCleanerTopFwd = TRUE; pDY02->oCleanerTopBwd = FALSE;
	}
	if(nIndex == eCleanerIO::TopBwd)
	{
		pDY02->oCleanerTopFwd = FALSE; pDY02->oCleanerTopBwd = TRUE;
	}
	if(nIndex == eCleanerIO::BtmDn)
	{
		pDY02->oCleanerBtmDn = TRUE; pDY02->oCleanerBtmUp = FALSE;
	}
	if(nIndex == eCleanerIO::BtmUp)
	{
		pDY02->oCleanerBtmDn = FALSE; pDY02->oCleanerBtmUp = TRUE;
	}
	if(nIndex == eCleanerIO::BtmFwd)
	{
		pDY02->oCleanerBtmFwd = TRUE; pDY02->oCleanerBtmBwd = FALSE;
	}
	if(nIndex == eCleanerIO::BtmBwd)
	{
		pDY02->oCleanerBtmFwd = FALSE; pDY02->oCleanerBtmBwd = TRUE;
	}
	g_objAJinAXL.Write_Output(2);

	m_strLog.Format("[Manual Cleaner IO] Cleaner IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualCleanDlg::OnBtnTopInspectXClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	int nIndex = nID - IDC_BTN_TOP_INSPECT_X_0;
	
	if(nIndex == eTopInspect_X::Ready)
	{
		g_objCommon.Move_Position(AX_TOP_INSPECTOR_X, eTopInspect_X::Ready);
	}
	if(nIndex == eTopInspect_X::ScanStart)
	{
		double dStart = pEquipData->dTopStartX;
		g_objAJinAXL.Move_Absolute(AX_TOP_INSPECTOR_X, dStart);
	}
	if(nIndex == eTopInspect_X::PitchP)
	{		
		double dPitch = pEquipData->dZigPitchX;
		g_objAJinAXL.Move_Absolute(AX_TOP_INSPECTOR_X, dPitch);
	}
	if(nIndex == eTopInspect_X::PitchM)
	{
		double dPitch = pEquipData->dZigPitchX;
		g_objAJinAXL.Move_Absolute(AX_TOP_INSPECTOR_X, -dPitch);
	}
	m_strLog.Format("[Manual Top Inspector X] X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualCleanDlg::OnBtnTopInspectYClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	int nIndex = nID - IDC_BTN_TOP_INSPECT_Y_0;

	if(nIndex == eTopInspect_Y::Ready)
	{
		g_objCommon.Move_Position(AX_TOP_INSPECTOR_Y, eTopInspect_Y::Ready);
	}
	if(nIndex == eTopInspect_Y::ScanStart)
	{
		double dStart = pEquipData->dTopStartY;
		g_objAJinAXL.Move_Absolute(AX_TOP_INSPECTOR_Y, dStart);
	}
	if(nIndex == eTopInspect_Y::PitchP)
	{		
		double dPitch = pEquipData->dZigPitchY;
		g_objAJinAXL.Move_Absolute(AX_TOP_INSPECTOR_Y, dPitch);
	}
	if(nIndex == eTopInspect_Y::PitchM)
	{
		double dPitch = pEquipData->dZigPitchY;
		g_objAJinAXL.Move_Absolute(AX_TOP_INSPECTOR_Y, -dPitch);
	}
	m_strLog.Format("[Manual Top Inspector Y] Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualCleanDlg::OnBtnTopInspectZClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	int nIndex = nID - IDC_BTN_TOP_INSPECT_Z_0;

	if(nIndex == eTopInspect_Z::Ready)
	{
		g_objCommon.Move_Position(AX_TOP_INSPECTOR_Z, eTopInspect_Z::Ready);
	}
	if(nIndex == eTopInspect_Z::ScanStart)
	{
		double dStart = pEquipData->dTopStartZ;
		g_objAJinAXL.Move_Absolute(AX_TOP_INSPECTOR_Z, dStart - (pEquipData->dTopPeriod/4));		
	}
	if(nIndex == eTopInspect_Z::ScanEnd)
	{
		/*double dEnd = pEquipData->dTopEnd;
		g_objAJinAXL.Move_Absolute(AX_TOP_INSPECTOR_Z, dEnd);*/		
	}
	if(nIndex == eTopInspect_Z::Scan)
	{
		if (m_nScanCase == 0) m_nScanCase = 1;
		m_bThreadTopScan = TRUE;
		m_pThreadTopScan = AfxBeginThread(Thread_TopScan, this);		
	}

	m_strLog.Format("[Manual Top Inspector Z] Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}


///////////////////////////////////////////////////////////////////////////////

UINT CManualCleanDlg::Thread_TopScan(LPVOID lpVoid)
{
	CManualCleanDlg* pOwner = (CManualCleanDlg*)lpVoid;

	while (pOwner->m_bThreadTopScan) {
		if (!pOwner->TopScan_Run()) break;
		Sleep(5);
	}
	pOwner->m_bThreadTopScan = FALSE;
	pOwner->m_pThreadTopScan = NULL;

	return 0;
}
///////////////////////////////////////////////////////////////////////////////

BOOL CManualCleanDlg::TopScan_Run()
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	static double dTopZ = 0.0;	

	switch (m_nScanCase) {
	case 0:		// Start 시 1로 진행
		return TRUE;

	case 1:		// Move Frist
		if (g_objAJinAXL.Is_Done(AX_TOP_INSPECTOR_Z)) 
		{			
			m_nScanCase++;
		}
		break;
	case 2:		// Scan Move
		if (g_objAJinAXL.Is_Done(AX_TOP_INSPECTOR_Z)) 
		{
			m_nScanCase = 3;
			double dPeriod = pEquipData->dTopPeriod;	// 33mm
			double dTrigS = pEquipData->dTopStartZ;				// Trigger Start
			double dTrigE = dTrigS + dPeriod * pEquipData->nTopCount;	// Trigger End
			dTopZ = dTrigE + (dPeriod/4);								// Motion End (가감속)
			double dVelocity = pEquipData->dTopVelocity;
			g_objAJinAXL.Start_Scan(eVision::TC, AX_TOP_INSPECTOR_Z, dTopZ, dTrigS, dTrigE, dPeriod, dPeriod/2, dVelocity);
			
		}
		break;
	case 3:		// Scan End
		if (g_objAJinAXL.Is_MoveDone(AX_TOP_INSPECTOR_Z, dTopZ)) 
		{
			g_objAJinAXL.Stop_Scan(AX_TOP_INSPECTOR_Z);
			m_nScanCase = 0;			
			return FALSE;
		}
		break;
	case 4:
		return FALSE;
	}
	return TRUE;
}

void CManualCleanDlg::OnBnClickedButton1()
{

}


void CManualCleanDlg::OnBnClickedBtnCasereset()
{
	m_nScanCase = 0;
}


void CManualCleanDlg::OnBnClickedBtnAmove()
{
	double m_dTopZ = 30.9;
	if(theApp.Get_MainMode() == MODE_MANUAL)
	{
		g_objAJinAXL.Move_Absolute(AX_TOP_INSPECTOR_Z, m_dTopZ);		
		while (1)
		{
			theApp.DoEvents();
			if(g_objAJinAXL.Is_MoveDone(AX_TOP_INSPECTOR_Z, m_dTopZ))
			{
				break;
			}
		}
	}
}


void CManualCleanDlg::OnBnClickedBtnCasereset2()
{
	m_nScanCase = 4;	
	m_bThreadTopScan = FALSE;
	m_pThreadTopScan = NULL;
}


void CManualCleanDlg::OnBnClickedButton2()
{
	g_objAJinAXL.Clear_Scan(eVision::TC);
}
