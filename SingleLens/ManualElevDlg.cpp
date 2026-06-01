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

#include "BarcodeLot_Cognex.h"

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
	DDX_Control(pDX, IDC_STC_MZ_BARCODE,m_stcBarcode);
	DDX_Control(pDX, IDC_STC_ZIG_BARCODE,m_stcZigBarcode);

	for (int i = 0; i < 1; i++) DDX_Control(pDX, IDC_STC_AXIS_POS_0 + i, m_stcAxisPos[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_LED_LD_CV_EXIST_0 + i, m_LedLdCVIO[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_CHK_LD_CV_R_0 + i, m_ChkLdCVIO[i]);
	
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LED_LD_CV_STOPPER_0 + i, m_LedLdCVStopper[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_BTN_LD_CV_STOPPER_0 + i, m_BtnLdCVStopper[i]);

	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_LED_ELEV_EXIST_0 + i, m_LedElevIO[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_CHK_ELEV_CV_R_0 + i, m_ChkElevIO[i]);

	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_LED_ELEV_CV_STOPPER_0 + i, m_LedElevStopper[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_BTN_ELEV_CV_STOPPER_0 + i, m_BtnElevStopper[i]);

	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_BTN_ELEV_Z_0 + i, m_BtnElevZ[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_BTN_ELEVREADY_Z_0 + i, m_BtnElevReadyZ[i]);

	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LED_ULD_CV_EXIST_0 + i, m_LedUldCVIO[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_CHK_ULD_CV_R_0 + i, m_ChkUldCVIO[i]);

	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_LED_ULD_CV_STOPPER_0 + i, m_LedUldCVStopper[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_ULD_CV_STOPPER_0 + i, m_BtnUldCVStopper[i]);
}

BEGIN_MESSAGE_MAP(CManualElevDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHK_LD_CV_R_0, IDC_CHK_LD_CV_R_2, OnChkLdCVIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LD_CV_STOPPER_0, IDC_BTN_LD_CV_STOPPER_3, OnBtnLdCVStopperClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHK_ELEV_CV_R_0, IDC_CHK_ELEV_CV_R_2, OnChkElevCVIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_ELEV_CV_STOPPER_0, IDC_BTN_ELEV_CV_STOPPER_7, OnBtnElevCVStopperClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_ELEV_Z_0, IDC_BTN_ELEV_Z_4, OnBtnElevZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_ELEVREADY_Z_0, IDC_BTN_ELEVREADY_Z_4, OnBtnElevReadyZClick)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHK_ULD_CV_R_0, IDC_CHK_ULD_CV_R_2, OnChkUldCVIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_ULD_CV_STOPPER_0, IDC_BTN_ULD_CV_STOPPER_1, OnBtnUldCVStopperClick)

	ON_BN_CLICKED(IDC_BTN_MZ_BARCODE, &CManualElevDlg::OnBnClickedBtnMzBarcode)
	ON_BN_CLICKED(IDC_BTN_MZ_BARCODE_INIT, &CManualElevDlg::OnBnClickedBtnMzBarcodeInit)
	ON_BN_CLICKED(IDC_BTN_ZIG_BARCODE, &CManualElevDlg::OnBnClickedBtnZigBarcode)
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

	for (int i = 0; i <  1; i++) m_stcAxisPos[i].Init_Ctrl("Arial", 10, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x10, 0x10, 0x60));
	
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
	
	CString strPos;
	double dPos = g_objAJinAXL.Get_Position(AX_MZ_ELEVATOR_Z);
	strPos.Format("%0.3lf", dPos);
	m_stcAxisPos[0].SetWindowText(strPos);
		
	m_LedLdCVIO[0].Set_On(pDX00->iLdCVMZExist1R);
	m_LedLdCVIO[1].Set_On(pDX00->iLdCVMZExist2);
	m_LedLdCVIO[2].Set_On(pDX00->iLdCVMZExist3);
	m_LedLdCVIO[3].Set_On(pDX00->iLdCVMZExist4);
	m_LedLdCVIO[4].Set_On(pDX00->iLdCVMZExist5);

	m_LedLdCVStopper[0].Set_On(pDX00->iLdCVLift1UpR);
	m_LedLdCVStopper[1].Set_On(pDX00->iLdCVLift1Dn);
	m_LedLdCVStopper[2].Set_On(pDX00->iLdCVLift2Up);
	m_LedLdCVStopper[3].Set_On(pDX00->iLdCVLift2Dn);

	m_LedElevIO[0].Set_On(pDX00->iElvMZExist1);
	m_LedElevIO[1].Set_On(pDX00->iElvMZExist2);

	m_LedElevStopper[0].Set_On(pDX00->iElvLift1UpL);
	m_LedElevStopper[1].Set_On(pDX00->iElvLift1Dn);
	m_LedElevStopper[2].Set_On(pDX00->iElvLift1In);
	m_LedElevStopper[3].Set_On(pDX00->iElvLift1Out);
	m_LedElevStopper[4].Set_On(pDX00->iElvLift2UpR);
	m_LedElevStopper[5].Set_On(pDX00->iElvLift2Dn);
	m_LedElevStopper[6].Set_On(pDX00->iElvLift2In);
	m_LedElevStopper[7].Set_On(pDX00->iElvLift2Out);

	m_LedUldCVStopper[0].Set_On(pDX01->iUldCvStprUp);
	m_LedUldCVStopper[1].Set_On(pDX01->iUldCvStprDn);

	m_LedLdCVIO[0].Set_On(pDX00->iLdCVMZExist1R);
	m_LedLdCVIO[1].Set_On(pDX00->iLdCVMZExist2);
	m_LedLdCVIO[2].Set_On(pDX00->iLdCVMZExist3);
	m_LedLdCVIO[3].Set_On(pDX00->iLdCVMZExist4);

	m_LedUldCVIO[0].Set_On(pDX01->iUldCvMZExist1L);
	m_LedUldCVIO[1].Set_On(pDX01->iUldCvMZExist2);
	m_LedUldCVIO[2].Set_On(pDX01->iUldCvMZExist3);
	m_LedUldCVIO[3].Set_On(pDX01->iUldCvMZExist4);

	
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
			pDY00->oLoadCVRun = TRUE; pDY00->oLoadCVDirCCW = TRUE;
			
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
			pDY00->oLoadCVRun = TRUE; pDY00->oLoadCVDirCCW = FALSE;

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

void CManualElevDlg::OnChkUldCVIOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();

	int nIndex = nID - IDC_CHK_ULD_CV_R_0;	

	if(nIndex == eUldCV_IO::CW)
	{
		if(m_ChkUldCVIO[eUldCV_IO::CW].GetCheck())
		{
			if(m_ChkUldCVIO[eUldCV_IO::CCW].GetCheck())
			{
				m_ChkUldCVIO[eUldCV_IO::CW].SetCheck(FALSE);
				AfxMessageBox("Ld CV CCW 회전중, Stop 필요합니다");
				return;
			}
			pDY01->oUldCvRun = TRUE; pDY01->oUldCvDirCCW = TRUE;

		}
		else
		{
			pDY01->oUldCvRun = FALSE; pDY01->oUldCvDirCCW = FALSE;
		}
	}

	if(nIndex == eLdCV_IO::CCW)
	{
		if(m_ChkUldCVIO[eUldCV_IO::CCW].GetCheck())
		{
			if(m_ChkUldCVIO[eUldCV_IO::CW].GetCheck())
			{
				m_ChkUldCVIO[eUldCV_IO::CCW].SetCheck(FALSE);
				AfxMessageBox("Ld CV CW 회전중, Stop 필요합니다");
				return;
			}
			pDY01->oUldCvRun = TRUE; pDY01->oUldCvDirCCW = FALSE;

		}
		else
		{
			pDY01->oUldCvRun = FALSE; pDY01->oUldCvDirCCW = FALSE;
		}
	}

	if(nIndex == eUldCV_IO::Stop)
	{
		m_ChkUldCVIO[eUldCV_IO::CW].SetCheck(FALSE);
		m_ChkUldCVIO[eUldCV_IO::CCW].SetCheck(FALSE);	
		pDY01->oUldCvRun = FALSE; pDY01->oUldCvDirCCW = FALSE;
	}
	g_objAJinAXL.Write_Output(1);

	m_strLog.Format("[Manual ULD CV] ULD CV CW/CCW IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualElevDlg::OnBtnLdCVStopperClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();

	int nIndex = nID - IDC_BTN_LD_CV_STOPPER_0;

	if(nIndex == eLdCVStpr::Up1)
	{
		pDY00->oLdCVStpr1UpR = TRUE; pDY00->oLdCVStpr1Dn = FALSE;
	}

	if(nIndex == eLdCVStpr::Down1)
	{
		pDY00->oLdCVStpr1UpR = FALSE; pDY00->oLdCVStpr1Dn = TRUE;
	}

	if(nIndex == eLdCVStpr::Up2)
	{
		pDY00->oLdCVStpr2Up = TRUE; pDY00->oLdCVStpr2Dn = FALSE;
	}

	if(nIndex == eLdCVStpr::Down2)
	{
		pDY00->oLdCVStpr2Up = FALSE; pDY00->oLdCVStpr2Dn = TRUE;
	}
	g_objAJinAXL.Write_Output(1);

	m_strLog.Format("[Manual LD CV] LD CV Stoppper (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);

}


void CManualElevDlg::OnBtnUldCVStopperClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();

	int nIndex = nID - IDC_BTN_ULD_CV_STOPPER_0;

	if(nIndex == eLdCVStpr::Up1)
	{
		pDY01->oUldCvStprUp = TRUE; pDY01->oUldCvStprDn = FALSE;
	}

	if(nIndex == eLdCVStpr::Down1)
	{
		pDY01->oUldCvStprUp = FALSE; pDY01->oUldCvStprDn = TRUE;
	}

	g_objAJinAXL.Write_Output(1);

	m_strLog.Format("[Manual ULD CV] ULD CV Stoppper (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);

}

void CManualElevDlg::OnChkElevCVIOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();

	int nIndex = nID - IDC_CHK_ELEV_CV_R_0;	

	if(nIndex == eElevIO::CW)
	{
		if(m_ChkElevIO[eElevIO::CW].GetCheck())
		{
			if(m_ChkElevIO[eElevIO::CCW].GetCheck())
			{
				m_ChkElevIO[eElevIO::CW].SetCheck(FALSE);
				AfxMessageBox("Elev CV CCW 회전중, Stop 필요합니다");
				return;
			}
			pDY00->oElvCvRun = TRUE; pDY00->oElvCvDirCCW = TRUE;
		}
		else
		{
			pDY00->oElvCvRun = FALSE; pDY00->oElvCvDirCCW = FALSE;
		}
	}

	if(nIndex == eElevIO::CCW)
	{
		if(m_ChkElevIO[eElevIO::CCW].GetCheck())
		{
			if(m_ChkElevIO[eElevIO::CW].GetCheck())
			{
				m_ChkElevIO[eElevIO::CCW].SetCheck(FALSE);
				AfxMessageBox("Elev CV CW 회전중, Stop 필요합니다");
				return;
			}
			pDY00->oElvCvRun = TRUE; pDY00->oElvCvDirCCW = FALSE;

		}
		else
		{
			pDY00->oElvCvRun = FALSE; pDY00->oElvCvDirCCW = FALSE;
		}
	}

	if(nIndex == eElevIO::Stop)
	{
		m_ChkElevIO[eElevIO::CW].SetCheck(FALSE);
		m_ChkElevIO[eElevIO::CCW].SetCheck(FALSE);	
		pDY00->oElvCvRun = FALSE; pDY00->oElvCvDirCCW = FALSE;
	}
	g_objAJinAXL.Write_Output(0);

	m_strLog.Format("[Manual Elev CV] Elevator CV CW/CCW IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualElevDlg::OnBtnElevCVStopperClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();

	int nIndex = nID - IDC_BTN_ELEV_CV_STOPPER_0;

	if(nIndex == eElvStpr::Up1)
	{
		pDY00->oElvStpr1UpL = TRUE; pDY00->oElvStpr1Dn = FALSE;
	}
	if(nIndex == eElvStpr::Down1)
	{
		pDY00->oElvStpr1UpL = FALSE; pDY00->oElvStpr1Dn = TRUE;
	}
	if(nIndex == eElvStpr::In1)
	{
		pDY00->oElvStpr1In = TRUE; pDY00->oElvStpr1Out = FALSE;
	}
	if(nIndex == eElvStpr::Out1)
	{
		pDY00->oElvStpr1In = FALSE; pDY00->oElvStpr1Out = TRUE;
	}


	if(nIndex == eElvStpr::Up2)
	{
		pDY00->oElvStpr2UpR = TRUE; pDY00->oElvStpr2Dn = FALSE;
	}
	if(nIndex == eElvStpr::Down2)
	{
		pDY00->oElvStpr2UpR = FALSE; pDY00->oElvStpr2Dn = TRUE;
	}
	if(nIndex == eElvStpr::In2)
	{
		pDY00->oElvStpr2In = TRUE; pDY00->oElvStpr2Out = FALSE;
	}
	if(nIndex == eElvStpr::Out2)
	{
		pDY00->oElvStpr2In = FALSE; pDY00->oElvStpr2Out = TRUE;
	}

	g_objAJinAXL.Write_Output(0);

	m_strLog.Format("[Manual Elevator Stopper] Elevator Stoppper (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}



void CManualElevDlg::OnBtnElevZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_MZ_ELEVATOR_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	if(!g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready))
	{
		AfxMessageBox("Feeder Y Ready 위치가 아닙니다. 확인 후 진행하세요."); return;
	}
	
	
	
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();

	int nIndex = nID - IDC_BTN_ELEV_Z_0;


	if(nIndex == eElv_Z::FromLdCV)
	{
		g_objCommon.Move_Position(AX_MZ_ELEVATOR_Z, eElv_Z::FromLdCV);
	}

	if(nIndex == eElv_Z::Down)
	{
		g_objCommon.Move_Position(AX_MZ_ELEVATOR_Z, eElv_Z::Down);
	}

	if(nIndex == eElv_Z::ToUldCV)
	{
		g_objCommon.Move_Position(AX_MZ_ELEVATOR_Z, eElv_Z::ToUldCV);
	}

	if(nIndex == eElv_Z::Pitch)
	{
		double dPitchZ = pEquipData->dElevPitchZ;//pMoveData->dMZElevZ[eElv_Z::Pitch];//
		g_objAJinAXL.Move_Relative(AX_MZ_ELEVATOR_Z, dPitchZ);		
	}

	if(nIndex == eElv_Z::PitchMinus)
	{
		double dPitchZ = pEquipData->dElevPitchZ;//pMoveData->dMZElevZ[eElv_Z::Pitch];
		g_objAJinAXL.Move_Relative(AX_MZ_ELEVATOR_Z, -dPitchZ);	
	}	

	m_strLog.Format("[Manual Elevator Z] Elevator Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}



void CManualElevDlg::OnBtnElevReadyZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_MZ_ELEVATOR_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	if(!g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready))
	{
		AfxMessageBox("Feeder Y Ready 위치가 아닙니다. 확인 후 진행하세요."); return;
	}
	if(!g_objCommon.Check_Position(AX_ZIG_FEEDER_X, eFeeder_X::MZLoad) 
		&& !g_objCommon.Check_Position(AX_ZIG_FEEDER_X, eFeeder_X::MZReady))
	{
		AfxMessageBox("Feeder Y Ready 위치가 아닙니다. 확인 후 진행하세요."); return;
	}


	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	int nIndex = nID - IDC_BTN_ELEV_Z_0;
	if(nIndex == eElevReady_Z::Ready)
	{
		g_objCommon.Move_Position(AX_MZ_ELEVATOR_Z, eElevReady_Z::Ready);
	}

	if(nIndex == eElevReady_Z::Down)
	{
		g_objCommon.Move_Position(AX_MZ_ELEVATOR_Z, eElevReady_Z::Down);
	}

	if(nIndex == eElevReady_Z::Up)
	{
		g_objCommon.Move_Position(AX_MZ_ELEVATOR_Z, eElevReady_Z::Up);
	}

	if(nIndex == eElevReady_Z::Pitch)
	{
		double dPitchZ = pEquipData->dElevPitchZReady;
		g_objAJinAXL.Move_Relative(AX_MZ_ELEVATOR_Z, dPitchZ);		
	}

	if(nIndex == eElevReady_Z::PitchMinus)
	{
		double dPitchZ = pEquipData->dElevPitchZReady;
		g_objAJinAXL.Move_Relative(AX_MZ_ELEVATOR_Z, -dPitchZ);	
	}	

	m_strLog.Format("[Manual Elevator Z] Elevator Ready Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

///////////////////////////////////////////////////////////////////////////////


//BOOL CManualElevDlg::Manual_ElevatorRun()
//{
//	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();
//
//	switch (m_nRunCase)
//	{
//	case 0:
//		m_tElevLoop.Set_LoopTime(5000);
//		break;
//	case 1:
//		m_nRunCase = 5; m_tElevLoop.Set_LoopTime(5000);
//		break;
//	case 5:
//		if(g_objAJinAXL.Is_Done(AX_MZ_ELEVATOR_Z))
//		{
//			m_nRunCase++; m_tElevLoop.Set_LoopTime(5000);
//		}
//		break;
//	case 6:
//		
//	}
//}



void CManualElevDlg::OnBnClickedBtnMzBarcode()
{
	m_stcBarcode.SetWindowText("");
	g_objBarcodeLot_Cognex.Set_Trigger(1, TRUE);

	CString strData = "";
	if (TRUE) {
		DWORD dwStart = GetTickCount();
		while (GetTickCount() - dwStart < 3000) {
			strData = g_objBarcodeLot_Cognex.Get_BarcodeLot(1);
			if (strData != "") break;
			theApp.DoEvents();
		}
		if (strData.GetLength() > 0) m_stcBarcode.SetWindowText(strData);
		if (strData.GetLength() < 1) { g_objBarcodeLot_Cognex.Set_Trigger(1, FALSE); AfxMessageBox("Reading Fail."); }
	}

	m_strLog.Format("[Manual MZ Load] Barcode Trigger (%d) Click - No:%d, Data:%s", 1, 1, strData);
	g_objLogFile.Save_HandlerLog(m_strLog);
}


void CManualElevDlg::OnBnClickedBtnMzBarcodeInit()
{
	DWORD dTemp = GetTickCount();
	g_objBarcodeLot_Cognex.Terminate(); 
	while (TRUE) { if (GetTickCount() - dTemp > 2000) break;}
	g_objBarcodeLot_Cognex.Initialize();	Sleep(5000);
}


void CManualElevDlg::OnBnClickedBtnZigBarcode()
{
	m_stcZigBarcode.SetWindowText("");
	g_objBarcodeLot_Cognex.Set_Trigger(2, TRUE);

	CString strData = "";
	if (TRUE) {
		DWORD dwStart = GetTickCount();
		while (GetTickCount() - dwStart < 3000) {
			strData = g_objBarcodeLot_Cognex.Get_BarcodeLot(2);
			if (strData != "") break;
			theApp.DoEvents();
		}
		if (strData.GetLength() > 0) m_stcZigBarcode.SetWindowText(strData);
		if (strData.GetLength() < 1) { g_objBarcodeLot_Cognex.Set_Trigger(2, FALSE); AfxMessageBox("Reading Fail."); }
	}

	m_strLog.Format("[Manual Tray Load] Barcode Trigger (%d) Click - No:%d, Data:%s", 2, 2, strData);
	g_objLogFile.Save_HandlerLog(m_strLog);
}
