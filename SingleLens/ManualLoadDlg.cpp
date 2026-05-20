// ManualLoadDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "SingleLens.h"
#include "ManualLoadDlg.h"
#include "afxdialogex.h"
#include "math.h"

#include "LogFile.h"
#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"
#include "SequenceMain.h"


// CManualLoadDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualLoadDlg, CDialogEx)

	CManualLoadDlg::CManualLoadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualLoadDlg::IDD, pParent)
{
}

CManualLoadDlg::~CManualLoadDlg()
{
}

void CManualLoadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//for (int i = 0; i <  9; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	//for (int i = 0; i <  6; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i <  4; i++) DDX_Control(pDX, IDC_STC_AXIS_POS_0 + i, m_stcAxisPos[i]);

	for (int i = 0; i <  4; i++) DDX_Control(pDX, IDC_BTN_FEEDER_X_0 + i, m_BtnFeederX[i]);
	for (int i = 0; i <  4; i++) DDX_Control(pDX, IDC_BTN_FEEDER_Y_0 + i, m_BtnFeederY[i]);
	for (int i = 0; i <  4; i++) DDX_Control(pDX, IDC_BTN_FEEDER_IO_0 + i, m_BtnFeederIO[i]);
	for (int i = 0; i <  7; i++) DDX_Control(pDX, IDC_LED_FEEDER_IO_0 + i, m_LedFeederIO[i]);

	for (int i = 0; i <  3; i++) DDX_Control(pDX, IDC_BTN_PICKER_Y_0 + i, m_BtnPickerY[i]);
	for (int i = 0; i <  3; i++) DDX_Control(pDX, IDC_BTN_PICKER_Z_0 + i, m_BtnPickerZ[i]);
	for (int i = 0; i <  4; i++) DDX_Control(pDX, IDC_BTN_PICKER_IO_0 + i, m_BtnPickerIO[i]);
	for (int i = 0; i <  5; i++) DDX_Control(pDX, IDC_LED_PICKER_IO_0 + i, m_LedPickerIO[i]);
}

BEGIN_MESSAGE_MAP(CManualLoadDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_FEEDER_X_0, IDC_BTN_FEEDER_X_3, OnBtnFeederXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_FEEDER_Y_0, IDC_BTN_FEEDER_Y_3, OnBtnFeederYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_FEEDER_IO_0, IDC_BTN_FEEDER_IO_3, OnBtnFeederIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_PICKER_Y_0, IDC_BTN_PICKER_Y_2, OnBtnPickerYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_PICKER_Z_0, IDC_BTN_PICKER_Z_3, OnBtnPickerZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_PICKER_IO_0, IDC_BTN_PICKER_IO_3, OnBtnPickerIOClick)
END_MESSAGE_MAP()

// CManualLoadDlg 메시지 처리기입니다.

void CManualLoadDlg::Initial_Controls() 
{
	/*for (int i = 0; i <  3; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xD0, 0x10, 0x10), COLOR_DEFAULT);
	for (int i = 3; i <  4; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xD0, 0x10, 0xD0), COLOR_DEFAULT);
	for (int i = 4; i <  5; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);
	for (int i = 5; i <  9; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x00, 0x80, 0x40), COLOR_DEFAULT);
	for (int i = 0; i <  6; i++) m_Label[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, RGB(0xB0, 0xB0, 0xB0));*/
}

BOOL CManualLoadDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CManualLoadDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualLoadDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;
	
	m_strLog.Format("[Manual Index] Show Window");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualLoadDlg::Display_Status()
{
	CString strPos;
	double dPos = g_objAJinAXL.Get_Position(AX_ZIG_FEEDER_X);
	strPos.Format("%0.3lf", dPos);
	m_stcAxisPos[0].SetWindowText(strPos);

	dPos = g_objAJinAXL.Get_Position(AX_ZIG_FEEDER_Y);
	strPos.Format("%0.3lf", dPos);
	m_stcAxisPos[1].SetWindowText(strPos);

	dPos = g_objAJinAXL.Get_Position(AX_ZIG_PICKER_Y);
	strPos.Format("%0.3lf", dPos);
	m_stcAxisPos[2].SetWindowText(strPos);

	dPos = g_objAJinAXL.Get_Position(AX_ZIG_PICKER_Z);
	strPos.Format("%0.3lf", dPos);
	m_stcAxisPos[3].SetWindowText(strPos);

	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	
	m_LedFeederIO[0].Set_On(pDX01->iFeederGripOpen);
	m_LedFeederIO[1].Set_On(pDX01->iFeederGripClose);
	m_LedFeederIO[2].Set_On(pDX01->iRailZigAlignIn);
	m_LedFeederIO[3].Set_On(pDX01->iRailZigAlignOut);
	m_LedFeederIO[4].Set_On(pDX01->iFeederZigExist);
	m_LedFeederIO[5].Set_On(pDX01->iRailZigExist);
	m_LedFeederIO[6].Set_On(pDX01->iMagazineZigExist);

	m_LedPickerIO[0].Set_On(pDX01->iZigPickerMasterIn);
	m_LedPickerIO[1].Set_On(pDX01->iZigPickerMasterOut);
	m_LedPickerIO[2].Set_On(pDX01->iZigPickerSlaveIn);
	m_LedPickerIO[3].Set_On(pDX01->iZigPickerSlaveOut);
	m_LedPickerIO[4].Set_On(pDX01->iZigPickerExist);
}


void CManualLoadDlg::OnBtnFeederXClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	
	if(!g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready))
	{
		AfxMessageBox("Feeder Y Ready 위치가 아닙니다. 확인 후 진행하세요."); return;
	}
	if(!g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready))
	{
		AfxMessageBox("Feeder Y Ready 위치가 아닙니다. 확인 후 진행하세요."); return;
	}

	int nIndex = nID - IDC_BTN_FEEDER_X_0;
	
	if(nIndex == eFeeder_X::Ready)
	{
		g_objCommon.Move_Position(AX_ZIG_FEEDER_X, eFeeder_X::Ready);
	}
	if(nIndex == eFeeder_X::MZReady)
	{
		g_objCommon.Move_Position(AX_ZIG_FEEDER_X, eFeeder_X::MZReady);
	}
	if(nIndex == eFeeder_X::MZLoad)
	{
		g_objCommon.Move_Position(AX_ZIG_FEEDER_X, eFeeder_X::MZLoad);
	}
	if(nIndex == eFeeder_X::TrayGrip)
	{
		g_objCommon.Move_Position(AX_ZIG_FEEDER_X, eFeeder_X::TrayGrip);
	}	

	m_strLog.Format("[Manual Feeder X] LD CV Stoppper (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualLoadDlg::OnBtnFeederYClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
		
	if(!g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready))
	{
		AfxMessageBox("Feeder Y Ready 위치가 아닙니다. 확인 후 진행하세요."); return;
	}

	int nIndex = nID - IDC_BTN_FEEDER_Y_0;

	if(nIndex == eFeeder_Y::Ready)
	{
		g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready);
	}
	if(nIndex == eFeeder_Y::MZReady)
	{
		g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::MZReady);
	}	
	if(nIndex == eFeeder_Y::MZLoad)
	{
		g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::MZLoad);
	}
	if(nIndex == eFeeder_Y::TrayGrip)
	{
		g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::TrayGrip);
	}	

	m_strLog.Format("[Manual Feeder Y] Feeder Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualLoadDlg::OnBtnFeederIOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();

	int nIndex = nID - IDC_BTN_FEEDER_IO_0;

	if(nIndex == eFeeder_IO::GripOpen)
	{
		pDY01->oFeederGripOpen = TRUE; pDY01->oFeederGripClose = FALSE;
	}
	if(nIndex == eFeeder_IO::GripClose)
	{
		pDY01->oFeederGripOpen = FALSE; pDY01->oFeederGripClose = TRUE;
	}
	if(nIndex == eFeeder_IO::RailAlignIn)
	{
		pDY01->oRailZigAlignIn = TRUE; pDY01->oRailZigAlignOut = FALSE;
	}
	if(nIndex == eFeeder_IO::RailAlignOut)
	{
		pDY01->oRailZigAlignIn = FALSE; pDY01->oRailZigAlignOut = TRUE;
	}	
	g_objAJinAXL.Write_Output(1);

	m_strLog.Format("[Manual Feeder I/O] Feeder I/O (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);

}

void CManualLoadDlg::OnBtnPickerYClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	if(!g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready))
	{
		AfxMessageBox("Feeder Y Ready 위치가 아닙니다. 확인 후 진행하세요."); return;
	}

	int nIndex = nID - IDC_BTN_PICKER_Y_0;

	if(nIndex == eZigPicker_Y::Ready)
	{
		g_objCommon.Move_Position(AX_ZIG_PICKER_Y, eZigPicker_Y::Ready);
	}
	if(nIndex == eZigPicker_Y::Load)
	{
		g_objCommon.Move_Position(AX_ZIG_PICKER_Y, eZigPicker_Y::Load);
	}	
	if(nIndex == eZigPicker_Y::Index)
	{
		g_objCommon.Move_Position(AX_ZIG_PICKER_Y, eZigPicker_Y::Index);
	}

	m_strLog.Format("[Manual Zig Picker Y] Zig Picker Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualLoadDlg::OnBtnPickerZClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	
	int nIndex = nID - IDC_BTN_PICKER_Z_0;

	if(nIndex == eZigPicker_Z::Ready)
	{
		g_objCommon.Move_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready);
	}
	if(nIndex == eZigPicker_Z::LoadDown)
	{
		g_objCommon.Move_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::LoadDown);
	}	
	if(nIndex == eZigPicker_Z::IndexLoad)
	{
		g_objCommon.Move_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::IndexLoad);
	}
	if(nIndex == eZigPicker_Z::IndexUnload)
	{
		g_objCommon.Move_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::IndexUnload);
	}

	m_strLog.Format("[Manual Zig Picker Z] Zig Picker Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualLoadDlg::OnBtnPickerIOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();

	int nIndex = nID - IDC_BTN_PICKER_IO_0;

	if(nIndex == ePicker_IO::MasterIn)
	{
		pDY01->oZigPickerMasterIn = TRUE; pDY01->oZigPickerMasterOut = FALSE;
	}
	if(nIndex == ePicker_IO::MasterOut)
	{
		pDY01->oZigPickerMasterIn = FALSE; pDY01->oZigPickerMasterOut = TRUE;
	}
	if(nIndex == ePicker_IO::SlaveIn)
	{
		pDY01->oZigPickerSlaveIn = TRUE; pDY01->oZigPickerSlaveOut = FALSE;
	}
	if(nIndex == ePicker_IO::SlaveOut)
	{
		pDY01->oZigPickerSlaveIn = FALSE; pDY01->oZigPickerSlaveOut = TRUE;
	}	
	g_objAJinAXL.Write_Output(1);

	m_strLog.Format("[Manual Zig Picker I/O] Zig Picker I/O (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}


///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
