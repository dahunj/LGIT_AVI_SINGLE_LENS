// ManualElevDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "SingleLens.h"
#include "ManualElevDlg.h"
#include "afxdialogex.h"
#include "math.h"

#include "LogFile.h"
#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"
#include "SequenceMain.h"

// CManualElevDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualElevDlg, CDialogEx)

CManualElevDlg::CManualElevDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualElevDlg::IDD, pParent)
{
}

CManualElevDlg::~CManualElevDlg()
{
}

void CManualElevDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	//for (int i = 0; i < 17; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	//for (int i = 0; i < 11; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);

	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_LED_LD_CV_EXIST_0 + i, m_LedLdCVIO[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_CHK_LD_CV_R_0 + i, m_ChkLdCVIO[i]);

	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LED_LD_CV_STOPPER_0 + i, m_LedLdCVStopper[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_BTN_LD_CV_STOPPER_0 + i, m_BtnLdCVStopper[i]);
	

}

BEGIN_MESSAGE_MAP(CManualElevDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHK_LD_CV_R_0, IDC_CHK_LD_CV_R_2, OnChkLdCVIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LD_CV_STOPPER_0, IDC_BTN_LD_CV_STOPPER_3, OnBtnLdCVStopperClick)
	//ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LD_CV_STOPPER_0, IDC_BTN_LD_CV_STOPPER_3, OnBtnLdCVIOClick)
END_MESSAGE_MAP()

// CManualElevDlg 메시지 처리기입니다.

void CManualElevDlg::Initial_Controls() 
{
	/*for (int i =  0; i < 4; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x30, 0x80, 0x00), COLOR_DEFAULT);
	for (int i =  4; i < 7; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xD0, 0x10, 0x10), COLOR_DEFAULT);
	for (int i =  7; i < 10; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xD0, 0x10, 0xD0), COLOR_DEFAULT);
	for (int i = 10; i < 13; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);
	for (int i = 13; i < 17; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x30, 0x80, 0x00), COLOR_DEFAULT);
	for (int i = 0; i < 11; i++) m_Label[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, RGB(0xB0, 0xB0, 0xB0));*/
	
}

BOOL CManualElevDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CManualElevDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualElevDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

	Display_Status();

	m_strLog.Format("[Manual Load] Show Window");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualElevDlg::Display_Status()
{
	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	
	m_LedLdCVIO[0].Set_On(pDX00->iLoadCVMZExist1Right);
	m_LedLdCVIO[1].Set_On(pDX00->iLoadCVMZExist2);
	m_LedLdCVIO[2].Set_On(pDX00->iLoadCVMZExist3);
	m_LedLdCVIO[3].Set_On(pDX00->iLoadCVMZExist4);
	m_LedLdCVIO[4].Set_On(pDX00->iLoadCVMZExist5);

	m_LedLdCVStopper[0].Set_On(pDX00->iLoadCVStopper1UpRight);
	m_LedLdCVStopper[1].Set_On(pDX00->iLoadCVStopper1Down);
	m_LedLdCVStopper[2].Set_On(pDX00->iLoadCVStopper2Up);
	m_LedLdCVStopper[3].Set_On(pDX00->iLoadCVStopper2Down);
}

///////////////////////////////////////////////////////////////////////////////
void CManualElevDlg::OnChkLdCVIOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();
	
	int nIndex = nID - IDC_CHK_LD_CV_R_0;	

	if(nIndex == eLdCV_IO::CW)
	{
		if(m_ChkLdCVIO[eLdCV_IO::CW].GetCheck())
		{
			if(m_ChkLdCVIO[eLdCV_IO::CCW].GetCheck())
			{
				m_ChkLdCVIO[eLdCV_IO::CW].SetCheck(FALSE);
				AfxMessageBox("Ld CV CCW 회전중, Stop 필요합니다");
				return;
			}
			pDY00->oLoadCVRun = TRUE; pDY00->oLoadCVDirCCW = FALSE;
			
		}
		else
		{
			pDY00->oLoadCVRun = FALSE; pDY00->oLoadCVDirCCW = FALSE;
		}
	}

	if(nIndex == eLdCV_IO::CCW)
	{
		if(m_ChkLdCVIO[eLdCV_IO::CCW].GetCheck())
		{
			if(m_ChkLdCVIO[eLdCV_IO::CW].GetCheck())
			{
				m_ChkLdCVIO[eLdCV_IO::CCW].SetCheck(FALSE);
				AfxMessageBox("Ld CV CW 회전중, Stop 필요합니다");
				return;
			}
			pDY00->oLoadCVRun = TRUE; pDY00->oLoadCVDirCCW = TRUE;

		}
		else
		{
			pDY00->oLoadCVRun = FALSE; pDY00->oLoadCVDirCCW = FALSE;
		}
	}

	if(nIndex == eLdCV_IO::Stop)
	{
		m_ChkLdCVIO[eLdCV_IO::CW].SetCheck(FALSE);
		m_ChkLdCVIO[eLdCV_IO::CCW].SetCheck(FALSE);	
		pDY00->oLoadCVRun = FALSE; pDY00->oLoadCVDirCCW = FALSE;
	}
	g_objAJinAXL.Write_Output(0);
	
	m_strLog.Format("[Manual LD CV] LD CV CW/CCW IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualElevDlg::OnBtnLdCVStopperClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();

	int nIndex = nID - IDC_BTN_LD_CV_STOPPER_0;

	if(nIndex == eLdCV_Stopper::Up1)
	{
		pDY00->oLoadCVStopper1UpRight = TRUE; pDY00->oLoadCVStopper1Down = FALSE;
	}

	if(nIndex == eLdCV_Stopper::Down1)
	{
		pDY00->oLoadCVStopper1UpRight = FALSE; pDY00->oLoadCVStopper1Down = TRUE;
	}

	if(nIndex == eLdCV_Stopper::Up2)
	{
		pDY00->oLoadCVStopper2Up = TRUE; pDY00->oLoadCVStopper2Down = FALSE;
	}

	if(nIndex == eLdCV_Stopper::Down2)
	{
		pDY00->oLoadCVStopper2Up = FALSE; pDY00->oLoadCVStopper2Down = TRUE;
	}
	g_objAJinAXL.Write_Output(0);

	m_strLog.Format("[Manual LD CV] LD CV Stoppper (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);

}


///////////////////////////////////////////////////////////////////////////////
