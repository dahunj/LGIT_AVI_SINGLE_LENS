// ManualNgDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "SingleLens.h"
#include "ManualBtmDlg.h"
#include "afxdialogex.h"
#include "math.h"

#include "LogFile.h"
#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"

// CManualNgDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualBtmDlg, CDialogEx)

CManualBtmDlg::CManualBtmDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualBtmDlg::IDD, pParent)
{
}

CManualBtmDlg::~CManualBtmDlg()
{
}

void CManualBtmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	/*for (int i = 0; i < 16; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 10; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);*/
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_STC_AXIS_POS_0 + i, m_stcAxisPos[i]);
	for (int i = 0; i <  4; i++) DDX_Control(pDX, IDC_BTN_BTM_INSPECT_X_0 + i, m_BtnBtmInspectX[i]);
	for (int i = 0; i <  4; i++) DDX_Control(pDX, IDC_BTN_BTM_INSPECT_Y_0 + i, m_BtnBtmInspectY[i]);
	for (int i = 0; i <  4; i++) DDX_Control(pDX, IDC_BTN_BTM_INSPECT_Z_0 + i, m_BtnBtmInspectZ[i]);
	for (int i = 0; i <  4; i++) DDX_Control(pDX, IDC_BTN_MARK_UNIT_X_0 + i, m_BtnMarkUnitX[i]);
	for (int i = 0; i <  4; i++) DDX_Control(pDX, IDC_BTN_MARK_UNIT_Y_0 + i, m_BtnMarkUnitY[i]);
	for (int i = 0; i <  4; i++) DDX_Control(pDX, IDC_BTN_MARK_UNIT_Z_0 + i, m_BtnMarkUnitZ[i]);

	for (int i = 0; i <  2; i++) DDX_Control(pDX, IDC_BTN_MARK_UNIT_IO_0 + i, m_BtnMarkUnitIO[i]);
	for (int i = 0; i <  3; i++) DDX_Control(pDX, IDC_LED_MARK_UNIT_IO_0 + i, m_LedMarkUnitIO[i]);
}

BEGIN_MESSAGE_MAP(CManualBtmDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_MARK_UNIT_IO_0, IDC_BTN_MARK_UNIT_IO_1, OnBtnMarkUnitIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_BTM_INSPECT_X_0, IDC_BTN_BTM_INSPECT_X_3, OnBtnBtmInspectXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_BTM_INSPECT_Y_0, IDC_BTN_BTM_INSPECT_Y_3, OnBtnBtmInspectYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_BTM_INSPECT_Z_0, IDC_BTN_BTM_INSPECT_Z_3, OnBtnBtmInspectZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_MARK_UNIT_X_0, IDC_BTN_MARK_UNIT_X_3, OnBtnMarkUnitXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_MARK_UNIT_Y_0, IDC_BTN_MARK_UNIT_Y_3, OnBtnMarkUnitYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_MARK_UNIT_Z_0, IDC_BTN_MARK_UNIT_Z_3, OnBtnMarkUnitZClick)
	ON_BN_CLICKED(IDC_BUTTON1, &CManualBtmDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CManualBtmDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CManualBtmDlg::OnBnClickedButton4)
END_MESSAGE_MAP()

// CManualBtmDlg 메시지 처리기입니다.

void CManualBtmDlg::Initial_Controls() 
{
	
}

BOOL CManualBtmDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	m_nScanCase = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CManualBtmDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualBtmDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

	Display_Status();
		
	m_strLog.Format("[Manual Unload] Show Window");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualBtmDlg::Display_Status()
{
	CString strPos;

	double dPos = g_objAJinAXL.Get_Position(AX_BTM_INSPECTOR_X);
	strPos.Format("%0.3lf", dPos);
	m_stcAxisPos[0].SetWindowText(strPos);

	dPos = g_objAJinAXL.Get_Position(AX_BTM_INSPECTOR_Y);
	strPos.Format("%0.3lf", dPos);
	m_stcAxisPos[1].SetWindowText(strPos);

	dPos = g_objAJinAXL.Get_Position(AX_BTM_INSPECTOR_Z);
	strPos.Format("%0.3lf", dPos);
	m_stcAxisPos[2].SetWindowText(strPos);

	dPos = g_objAJinAXL.Get_Position(AX_MARK_UNIT_X);
	strPos.Format("%0.3lf", dPos);
	m_stcAxisPos[3].SetWindowText(strPos);

	dPos = g_objAJinAXL.Get_Position(AX_MARK_UNIT_Y);
	strPos.Format("%0.3lf", dPos);
	m_stcAxisPos[4].SetWindowText(strPos);

	dPos = g_objAJinAXL.Get_Position(AX_MARK_UNIT_Z);
	strPos.Format("%0.3lf", dPos);
	m_stcAxisPos[5].SetWindowText(strPos);
		

	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();

	m_LedMarkUnitIO[0].Set_On(pDX02->IMarkPenDown);
	m_LedMarkUnitIO[1].Set_On(pDX02->IMarkPenUp);
	m_LedMarkUnitIO[2].Set_On(pDX02->IMarkPenExist);
	
}


void CManualBtmDlg::OnBtnBtmInspectXClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	int nIndex = nID - IDC_BTN_BTM_INSPECT_X_0;
	
	if(nIndex == eBtmInspect_X::Ready)
	{
		g_objCommon.Move_Position(AX_BTM_INSPECTOR_X, eTopInspect_X::Ready);
	}
	if(nIndex == eBtmInspect_X::ScanStart)
	{
		double dStart = pEquipData->dBtmStartX;
		g_objAJinAXL.Move_Absolute(AX_BTM_INSPECTOR_X, dStart);
	}
	if(nIndex == eBtmInspect_X::PitchP)
	{		
		double dPitch = pEquipData->dZigPitchX;
		g_objAJinAXL.Move_Relative(AX_BTM_INSPECTOR_X, dPitch);
	}
	if(nIndex == eBtmInspect_X::PitchM)
	{
		double dPitch = pEquipData->dZigPitchX;
		g_objAJinAXL.Move_Relative(AX_BTM_INSPECTOR_X, -dPitch);
	}
	m_strLog.Format("[Manual Btm Inspector X] X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualBtmDlg::OnBtnBtmInspectYClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	int nIndex = nID - IDC_BTN_BTM_INSPECT_Y_0;

	if(nIndex == eBtmInspect_Y::Ready)
	{
		g_objCommon.Move_Position(AX_BTM_INSPECTOR_Y, eBtmInspect_Y::Ready);
	}
	if(nIndex == eBtmInspect_Y::ScanStart)
	{
		double dStart = pEquipData->dBtmStartY;
		g_objAJinAXL.Move_Absolute(AX_BTM_INSPECTOR_Y, dStart);
	}
	if(nIndex == eBtmInspect_Y::PitchP)
	{		
		double dPitch = pEquipData->dZigPitchY;
		g_objAJinAXL.Move_Relative(AX_BTM_INSPECTOR_Y, dPitch);
	}
	if(nIndex == eBtmInspect_Y::PitchM)
	{
		double dPitch = pEquipData->dZigPitchY;
		g_objAJinAXL.Move_Relative(AX_BTM_INSPECTOR_Y, -dPitch);
	}
	m_strLog.Format("[Manual Btm Inspector Y] Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualBtmDlg::OnBtnBtmInspectZClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	int nIndex = nID - IDC_BTN_BTM_INSPECT_Z_0;

	if(nIndex == eBtmInspect_Z::Ready)
	{
		g_objCommon.Move_Position(AX_BTM_INSPECTOR_Z, eBtmInspect_Z::Ready);
	}
	if(nIndex == eBtmInspect_Z::ScanStart)
	{
		double dStart = pEquipData->dTopStartZ;
		g_objAJinAXL.Move_Absolute(AX_BTM_INSPECTOR_Z, dStart - (pEquipData->dBtmPeriod/4));		
	}
	if(nIndex == eBtmInspect_Z::ScanEnd)
	{
		/*double dEnd = pEquipData->dTopEnd;
		g_objAJinAXL.Move_Absolute(AX_TOP_INSPECTOR_Z, dEnd);*/		
	}
	if(nIndex == eBtmInspect_Z::Scan)
	{
		if (m_nScanCase == 0) m_nScanCase = 1;
		m_bThreadBtmScan = TRUE;
		m_pThreadBtmScan = AfxBeginThread(Thread_BtmScan, this);		
	}
	m_strLog.Format("[Manual Btm Inspector Z] Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}




void CManualBtmDlg::OnBtnMarkUnitXClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	int nIndex = nID - IDC_BTN_MARK_UNIT_X_0;
	
	if(nIndex == eMark_X::Ready)
	{
		g_objCommon.Move_Position(AX_MARK_UNIT_X, eMark_X::Ready);
	}
	if(nIndex == eMark_X::MarkStart)
	{
		g_objCommon.Move_Position(AX_MARK_UNIT_X, eMark_X::MarkStart);
	}
	if(nIndex == eMark_X::PitchP)
	{		
		double dPitch = g_objDataManager.Get_pMoveData()->dBtmInspectorZ[eMark_X::PitchP];
		g_objAJinAXL.Move_Relative(AX_MARK_UNIT_X, dPitch);
	}
	if(nIndex == eMark_X::PitchM)
	{
		double dPitch = g_objDataManager.Get_pMoveData()->dBtmInspectorZ[eMark_X::PitchP];
		g_objAJinAXL.Move_Relative(AX_MARK_UNIT_X, -dPitch);
	}
	m_strLog.Format("[Manual Mark Unit X] X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualBtmDlg::OnBtnMarkUnitYClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	int nIndex = nID - IDC_BTN_MARK_UNIT_Y_0;

	if(nIndex == eMark_Y::Ready)
	{
		g_objCommon.Move_Position(AX_MARK_UNIT_Y, eMark_Y::Ready);
	}
	if(nIndex == eMark_Y::MarkStart)
	{
		g_objCommon.Move_Position(AX_MARK_UNIT_Y, eMark_Y::MarkStart);
	}
	if(nIndex == eMark_Y::PitchP)
	{		
		double dPitch = g_objDataManager.Get_pMoveData()->dTopInspectorY[eMark_Y::PitchP];
		g_objAJinAXL.Move_Relative(AX_MARK_UNIT_Y, dPitch);
	}
	if(nIndex == eMark_Y::PitchM)
	{
		double dPitch = g_objDataManager.Get_pMoveData()->dTopInspectorY[eMark_Y::PitchP];
		g_objAJinAXL.Move_Relative(AX_MARK_UNIT_Y, -dPitch);
	}
	m_strLog.Format("[Manual Mark Unit Y] Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualBtmDlg::OnBtnMarkUnitZClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	int nIndex = nID - IDC_BTN_MARK_UNIT_Z_0;

	if(nIndex == eMark_Z::Ready)
	{
		g_objCommon.Move_Position(AX_MARK_UNIT_Z, eMark_Z::Ready);
	}
	if(nIndex == eMark_Z::MarkDown)
	{
		g_objCommon.Move_Position(AX_MARK_UNIT_Z, eMark_Z::MarkDown);
	}
	/*if(nIndex == eTopInspect_Z::Dummy1)
	{		
	double dPitch = g_objDataManager.Get_pMoveData()->dTopInspectorZ[eTopInspect_Z::Dummy1];
	g_objAJinAXL.Move_Relative(AX_TOP_INSPECTOR_Z, dPitch);
	}
	if(nIndex == eTopInspect_Z::Dummy2)
	{
	double dPitch = g_objDataManager.Get_pMoveData()->dTopInspectorZ[eTopInspect_Z::Dummy2];
	g_objAJinAXL.Move_Relative(AX_TOP_INSPECTOR_Z, dPitch);
	}*/
	m_strLog.Format("[Manual Mark Z] Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}



void CManualBtmDlg::OnBtnMarkUnitIOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	DY_DATA_02 *pDY02 = g_objAJinAXL.Get_pDY02();

	int nIndex = nID - IDC_BTN_MARK_UNIT_IO_0;

	if(nIndex == eMarkUnit::PenDown)
	{
		pDY02->oMarkPenDown = TRUE; pDY02->oMarkPenUp = FALSE;
	}
	if(nIndex == eMarkUnit::PenUp)
	{
		pDY02->oMarkPenDown = FALSE; pDY02->oMarkPenUp = TRUE;
	}
	
	g_objAJinAXL.Write_Output(2);

	m_strLog.Format("[Manual Mark Pen IO] Mark Pen (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}


UINT CManualBtmDlg::Thread_BtmScan(LPVOID lpVoid)
{
	CManualBtmDlg* pOwner = (CManualBtmDlg*)lpVoid;

	while (pOwner->m_bThreadBtmScan) {
		if (!pOwner->BtmScan_Run()) break;
		Sleep(5);
	}
	pOwner->m_bThreadBtmScan = FALSE;
	pOwner->m_pThreadBtmScan = NULL;

	return 0;
}
///////////////////////////////////////////////////////////////////////////////

BOOL CManualBtmDlg::BtmScan_Run()
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	static double dTopZ = 0.0;



	switch (m_nScanCase) {
	case 0:		// Start 시 1로 진행
		return TRUE;

	case 1:		// Move Frist
		if (g_objAJinAXL.Is_Done(AX_BTM_INSPECTOR_Z)) 
		{			
			m_nScanCase++;
		}
		break;
	case 2:		// Scan Move
		if (g_objAJinAXL.Is_Done(AX_BTM_INSPECTOR_Z)) 
		{
			double dPeriod = pEquipData->dBtmPeriod;	// 33mm
			double dTrigS = pEquipData->dBtmStartZ;				// Trigger Start
			double dTrigE = dTrigS + dPeriod * pEquipData->nBtmCount;	// Trigger End
			dTopZ = dTrigE + (dPeriod/4);								// Motion End (가감속)
			double dVelocity = pEquipData->dBtmVelocity;
			g_objAJinAXL.Start_Scan(eVision::BC, AX_BTM_INSPECTOR_Z, dTopZ, dTrigS, dTrigE, dPeriod, dPeriod/2, dVelocity);
			m_nScanCase++;
		}
		break;
	case 3:		// Scan End
		if (g_objAJinAXL.Is_Done(AX_BTM_INSPECTOR_Z)) 
		{
			g_objAJinAXL.Stop_Scan(AX_BTM_INSPECTOR_Z);
			m_nScanCase = 0;			
			return FALSE;
		}
		break;
	case 4:
		return FALSE;
		
	}
	return TRUE;
}

void CManualBtmDlg::OnBnClickedButton1()
{
	m_nScanCase = 0;
}


void CManualBtmDlg::OnBnClickedButton2()
{
	m_nScanCase = 4;
	m_bThreadBtmScan = FALSE;
	m_pThreadBtmScan = NULL;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CManualBtmDlg::OnBnClickedButton4()
{
	g_objAJinAXL.Clear_Scan(eVision::BC);
}
