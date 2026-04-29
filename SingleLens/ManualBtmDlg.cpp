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

	m_LedMarkUnitIO[0].Set_On(pDX02->IMarkPenIn);
	m_LedMarkUnitIO[1].Set_On(pDX02->IMarkPenOut);
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
		g_objCommon.Move_Position(AX_BTM_INSPECTOR_X, eTopInspect_X::ScanStart);
	}
	if(nIndex == eBtmInspect_X::PitchP)
	{		
		double dPitch = g_objDataManager.Get_pMoveData()->dBtmInspectorZ[eTopInspect_X::PitchP];
		g_objAJinAXL.Move_Relative(AX_BTM_INSPECTOR_X, dPitch);
	}
	if(nIndex == eBtmInspect_X::PitchM)
	{
		double dPitch = g_objDataManager.Get_pMoveData()->dBtmInspectorZ[eTopInspect_X::PitchM];
		g_objAJinAXL.Move_Relative(AX_BTM_INSPECTOR_X, dPitch);
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
		g_objCommon.Move_Position(AX_BTM_INSPECTOR_Y, eBtmInspect_Y::ScanStart);
	}
	if(nIndex == eBtmInspect_Y::PitchP)
	{		
		double dPitch = g_objDataManager.Get_pMoveData()->dTopInspectorY[eBtmInspect_Y::PitchP];
		g_objAJinAXL.Move_Relative(AX_BTM_INSPECTOR_Y, dPitch);
	}
	if(nIndex == eBtmInspect_Y::PitchM)
	{
		double dPitch = g_objDataManager.Get_pMoveData()->dTopInspectorY[eBtmInspect_Y::PitchM];
		g_objAJinAXL.Move_Relative(AX_BTM_INSPECTOR_Y, dPitch);
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
		g_objCommon.Move_Position(AX_BTM_INSPECTOR_Z, eBtmInspect_Z::ScanStart);
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
	if(nIndex == eMark_X::ScanStart)
	{
		g_objCommon.Move_Position(AX_MARK_UNIT_X, eMark_X::ScanStart);
	}
	if(nIndex == eMark_X::PitchP)
	{		
		double dPitch = g_objDataManager.Get_pMoveData()->dBtmInspectorZ[eMark_X::PitchP];
		g_objAJinAXL.Move_Relative(AX_MARK_UNIT_X, dPitch);
	}
	if(nIndex == eMark_X::PitchM)
	{
		double dPitch = g_objDataManager.Get_pMoveData()->dBtmInspectorZ[eMark_X::PitchM];
		g_objAJinAXL.Move_Relative(AX_MARK_UNIT_X, dPitch);
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
	if(nIndex == eMark_Y::ScanStart)
	{
		g_objCommon.Move_Position(AX_MARK_UNIT_Y, eMark_Y::ScanStart);
	}
	if(nIndex == eMark_Y::PitchP)
	{		
		double dPitch = g_objDataManager.Get_pMoveData()->dTopInspectorY[eMark_Y::PitchP];
		g_objAJinAXL.Move_Relative(AX_MARK_UNIT_Y, dPitch);
	}
	if(nIndex == eMark_Y::PitchM)
	{
		double dPitch = g_objDataManager.Get_pMoveData()->dTopInspectorY[eMark_Y::PitchM];
		g_objAJinAXL.Move_Relative(AX_MARK_UNIT_Y, dPitch);
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
	if(nIndex == eMark_Z::ScanStart)
	{
		g_objCommon.Move_Position(AX_MARK_UNIT_Z, eMark_Z::ScanStart);
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

	if(nIndex == eMarkUnit::PenIn)
	{
		pDY02->oMarkPenIn = TRUE; pDY02->oMarkPenOut = FALSE;
	}
	if(nIndex == eMarkUnit::PenOut)
	{
		pDY02->oMarkPenIn = FALSE; pDY02->oMarkPenOut = TRUE;
	}
	
	g_objAJinAXL.Write_Output(2);

	m_strLog.Format("[Manual Mark Pen IO] Mark Pen (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}


///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
