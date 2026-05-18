#include "StdAfx.h"
#include "SingleLens.h"
#include "SingleLensDlg.h"
#include "SequenceMain.h"
#include "Common.h"
#include "Inspector.h"
#include "LogFile.h"
#include "WorkDlg.h"


CSequenceMain g_objSequenceMain;


CSequenceMain::CSequenceMain(void)
{
	for (int i = 0; i < AXIS_COUNT; i++) m_pStatus[i] = g_objAJinAXL.Get_pStatus(i);
	for (int i = 0; i < AXIS_COUNT; i++) m_pParam[i] = g_objAJinAXL.Get_pParam(i);

	m_pDX00 = g_objAJinAXL.Get_pDX00();
	m_pDX01 = g_objAJinAXL.Get_pDX01();
	m_pDX02 = g_objAJinAXL.Get_pDX02();
	m_pDX03 = g_objAJinAXL.Get_pDX03();
	

	m_pDY00 = g_objAJinAXL.Get_pDY00();
	m_pDY01 = g_objAJinAXL.Get_pDY01();
	m_pDY02 = g_objAJinAXL.Get_pDY02();
	m_pDY03 = g_objAJinAXL.Get_pDY03();
	

	m_pEquipData = g_objDataManager.Get_pEquipData();
	//m_pModelData = g_objDataManager.Get_pModelData();
	m_pMoveData = g_objDataManager.Get_pMoveData();

	m_strLog = "";

	m_bThreadMainRun = FALSE;
	m_pThreadMainRun = NULL;
	gData.nSlotNoToPick[eMZ::Load] = 1;
	gData.nSlotNoToPick[eMZ::Ready] = 1;


	gData.nZigY = ZIG_Y;
	gData.nZigX = ZIG_X;

	

	Reset_MainRunCase();
}


CSequenceMain::~CSequenceMain(void)
{
}


void CSequenceMain::Reset_MainRunCase()
{
	m_nLoadConveyorCase	= 0;			
	m_nMZElevCase		= 0;			
	m_nFeederCase		= 0;
	m_nZigPickerCase	= 0;			
	m_nLensCleanerCase	= 0;			
	m_nTopInspectCase	= 0;			
	m_nBtmInspectCase	= 0;			
	m_nMarkUnitCase		= 0;			
	m_nMainIndexCase	= 0;	
	m_nUnloadConveyorCase = 0;
	
}

int *CSequenceMain::Get_pMainRunCase()
{
	static int nMainCase[10] = { 0 };

	nMainCase[0] = m_nLoadConveyorCase;	
	nMainCase[1] = m_nMZElevCase;			
	nMainCase[2] = m_nFeederCase;
	nMainCase[3] = m_nZigPickerCase;		
	nMainCase[4] = m_nLensCleanerCase;		
	nMainCase[5] = m_nTopInspectCase;	
	nMainCase[6] = m_nBtmInspectCase;	
	nMainCase[7] = m_nMarkUnitCase;		
	nMainCase[8] = m_nMainIndexCase;	
	nMainCase[9] = m_nUnloadConveyorCase;
	return nMainCase;
}

int CSequenceMain::Get_MainRunCase(int nRun)
{
	if		(nRun == AUTO_LD_CONVEYOR)			return m_nLoadConveyorCase;	
	else if (nRun == AUTO_MZ_ELEVATOR)		return m_nMZElevCase;	
	else if (nRun == AUTO_FEEDER)			return m_nFeederCase;		
	else if (nRun == AUTO_TRAY_PICKER)		return m_nZigPickerCase;		
	else if (nRun == AUTO_LENS_CLEANER)		return m_nLensCleanerCase;	
	else if (nRun == AUTO_TOP_INSPECT)		return m_nTopInspectCase;	
	else if (nRun == AUTO_BTM_INSPECT)		return m_nBtmInspectCase;		
	else if (nRun == AUTO_MARKER)			return m_nMarkUnitCase;		
	else if (nRun == AUTO_INDEX_TABLE)		return m_nMainIndexCase;	
	else if (nRun == AUTO_UL_CONVEYOR)		return m_nUnloadConveyorCase;

	return 0;
}

void CSequenceMain::Set_MainRunCase(int nRun, int nCase)
{
	if		(nRun == AUTO_LD_CONVEYOR)		m_nLoadConveyorCase	= nCase;	
	else if (nRun == AUTO_MZ_ELEVATOR)		m_nMZElevCase	= nCase;	
	else if (nRun == AUTO_FEEDER)			m_nFeederCase		= nCase;	
	else if (nRun == AUTO_TRAY_PICKER)		m_nZigPickerCase		= nCase;	
	else if (nRun == AUTO_LENS_CLEANER)		m_nLensCleanerCase	= nCase;	
	else if (nRun == AUTO_TOP_INSPECT)		m_nTopInspectCase	= nCase;	
	else if (nRun == AUTO_BTM_INSPECT)		m_nBtmInspectCase		= nCase;	
	else if (nRun == AUTO_MARKER)			m_nMarkUnitCase		= nCase;	
	else if (nRun == AUTO_INDEX_TABLE)		m_nMainIndexCase	= nCase;
	else if (nRun == AUTO_UL_CONVEYOR)		m_nUnloadConveyorCase	= nCase;	
}

void CSequenceMain::Set_MainRunLoop(int nRun, int nLoop)
{
	if		(nRun == AUTO_LD_CONVEYOR)			m_nLoadConveyorLoop.Set_LoopTime(nLoop);	
	else if (nRun == AUTO_MZ_ELEVATOR)		m_nMZElevLoop.Set_LoopTime(nLoop);	
	else if (nRun == AUTO_FEEDER)			m_nFeederLoop.Set_LoopTime(nLoop);		
	else if (nRun == AUTO_TRAY_PICKER)		m_nZigPickerLoop.Set_LoopTime(nLoop);		
	else if (nRun == AUTO_LENS_CLEANER)		m_nLensCleanerLoop.Set_LoopTime(nLoop);	
	else if (nRun == AUTO_TOP_INSPECT)		m_nTopInspectLoop.Set_LoopTime(nLoop);	
	else if (nRun == AUTO_BTM_INSPECT)		m_nBtmInspectLoop.Set_LoopTime(nLoop);		
	else if (nRun == AUTO_MARKER)			m_nMarkUnitLoop.Set_LoopTime(nLoop);		
	else if (nRun == AUTO_INDEX_TABLE)		m_nIndexTLoop.Set_LoopTime(nLoop);
	else if (nRun == AUTO_UL_CONVEYOR)		m_nUnloadConveyorLoop.Set_LoopTime(nLoop);
}



///////////////////////////////////////////////////////////////////////////////

BOOL CSequenceMain::Get_IsAutoRun()
{
	int *pCase = Get_pMainRunCase();
	for (int i = 0; i < AUTO_COUNT; i++) 
	{		
		if(i == AUTO_LD_CONVEYOR && m_nLoadConveyorCase == 1) continue;
		if(i == AUTO_UL_CONVEYOR && m_nUnloadConveyorCase == 1) continue;
		if(i == AUTO_MZ_ELEVATOR && m_nMZElevCase == 20) continue;
		if(i == AUTO_MZ_ELEVATOR && m_nMZElevCase == 20) continue;
		if(i == AUTO_INDEX_TABLE && m_nMainIndexCase == 5) continue;
		if (*(pCase + i) > 0) return TRUE;
	}

	if (!Check_IndexEmpty(-1)) return TRUE;
	if (Check_CtZigInMZ(eMZ::Load)) return TRUE;
	if (!Check_ZigPickerEmpty()) return TRUE;
	if (!Check_FeederEmpty()) return TRUE;
	if (Check_CVMZSensors() > 0) return TRUE;
	
	return FALSE;
}

BOOL CSequenceMain::Check_ElevEmpty(int nPos)
{
	if (g_dlgWork.SearchMZElevInfo(nPos) > 0) return FALSE;	

	return TRUE;
}

BOOL CSequenceMain::Check_ModuleLotEnd(int nLotNo)
{


	return TRUE;
}

void CSequenceMain::Set_ClearRunData(BOOL bInit)
{
	if(bInit)
	{
		for(int i = 0; i < 6; i++) gData.sMZID[i] = "";
		for(int i = 0; i < 6; i++) for(int j = 0; j < 10; j++) gData.sZigID[i][j] = "";
		for(int i = 0; i < 6; i++) gData.nMZNo[i];

		gData.nMZCnt = 0;
		for(int i = 0; i < 6; i++) for(int j = 0; j < 10; j++) gData.nLensUseCnt[i][j] = 0;
		gData.nLensMaxCnt = 0;

		gData.nSlotNoToPick[0] = 0;
		gData.nSlotNoToPick[1] = 0;

		memset(gData.InfoMZLoad, 0x00, sizeof(int)*10*ZIG_X*ZIG_Y);
		memset(gData.InfoMZReady, 0x00, sizeof(int)*10*ZIG_X*ZIG_Y);

		memset(gData.InfoFeeder, 0x00, sizeof(int)*ZIG_X*ZIG_Y);
		memset(gData.InfoRail, 0x00, sizeof(int)*ZIG_X*ZIG_Y);
		memset(gData.InfoZigPick, 0x00, sizeof(int)*ZIG_X*ZIG_Y);
		
		memset(gData.InfoMainIndex, 0x00, sizeof(int)*7*ZIG_X*ZIG_Y);
		memset(gData.InfoMZUnload, 0x00, sizeof(int)*10*ZIG_X*ZIG_Y);
	}




	g_dlgWork.PostMessage(UM_UPDATE_MZ_INFO, (int)eMZ::Load, NULL);
	g_dlgWork.PostMessage(UM_UPDATE_MZ_INFO, (int)eMZ::Ready, NULL);

	memset(gData.bIndexDone, 0x00, sizeof(BOOL) * 7);
}

void CSequenceMain::Set_ClearLotData(BOOL bInit, int nLotNo)
{
	
}

void CSequenceMain::Job_LotEnd()
{
	m_bLotEnd = TRUE;
}


///////////////////////////////////////////////////////////////////////////////



UINT CSequenceMain::Thread_Beep(LPVOID lpVoid)
{
	g_objSequenceMain.Beep_Post(0, (int)lpVoid);
	g_objSequenceMain.m_pThreadBeep = NULL;
	return 0;
}


BOOL CSequenceMain::LotEnd_Run()
{
	//if (!m_bUnloadLotEndAll) return FALSE;

	if (Get_IsAutoRun()) return FALSE;
	if (g_dlgWork.SearchMZCVInfo() < 0) return FALSE;
	if (g_dlgWork.SearchMZElevInfo(0) < 0 && g_dlgWork.SearchMZElevInfo(1) < 0 ) return FALSE;

	if (gData.bCycleStop) g_dlgWork.PostMessage(UM_RESET_CYCLE_STOP, NULL, NULL);

	gData.bFirstLotStart = FALSE;
	
	CSingleLensDlg *pMainDlg = (CSingleLensDlg*)AfxGetApp()->GetMainWnd();
	//pMainDlg->Set_LampFlicker_UldRun(FALSE);
	//pMainDlg->Set_LampFlicker_UldOpen(FALSE);
	

//	g_dlgWork.PostMessage(UM_UPDATE_LOT_INFO, (WPARAM)0, NULL);	// All Clear

//	if (m_nAssyPickCase == 1) m_nAssyPickCase = 0;

	Set_ClearRunData(FALSE);

	//int nPx = (gData.nULPNo < 1) ? 0 : gData.nULPNo - 1;	// 맨마지막 공정인 Good Tray Port No 활용.

	CString strMsg;
	strMsg.Format("Run End.\n\n");
	g_objCommon.Show_Alarm(strMsg, STATE_LOTEND);

	return TRUE;
}

UINT CSequenceMain::Thread_MainRun(LPVOID lpVoid)
{
	while (g_objSequenceMain.m_bThreadMainRun) {
		if (!g_objCommon.Check_MainEmgAir()) break;
		if (!g_objCommon.Check_MainDoor(TRUE)) break;
		if (!g_objCommon.Check_ServoOn()) break;
		if (!g_objCommon.Check_DirveAlarm()) break;
		if (!g_objCommon.Check_EndLimit()) break;
		if (!g_objCommon.Check_HomeDone()) break;

		if (!g_objSequenceMain.LoadConveyorRun()) break;	//  1. (Error : 3100)
		if (!g_objSequenceMain.MZElevRun()) break;	//  2. (Error : 3200)
		if (!g_objSequenceMain.FeederRun()) break;	//  3. (Error : 3300)
		if (!g_objSequenceMain.ZigPickerRun()) break;	//  4. (Error : 3400)
		if (!g_objSequenceMain.LensCleanerRun()) break;	//  5. (Error : 3500)
		if (!g_objSequenceMain.TopInspectorRun()) break;	//  6. (Error : 3600)
		if (!g_objSequenceMain.BtmInspectorRun()) break;	//  7. (Error : 3700)
		if (!g_objSequenceMain.MarkUnitRun()) break;	//  8. (Error : 3800)
		if (!g_objSequenceMain.MainIndexRun()) break;	//  9. (Error : 3900)
		if (!g_objSequenceMain.UnloadConveyorRun()) break;	// 10. (Error : 4000)
		if (!g_objSequenceMain.Run_Simulation()) break;

		if (g_objSequenceMain.LotEnd_Run()) break;
		

		Sleep(1);
	}

	g_objSequenceMain.m_bThreadMainRun = FALSE;
	g_objSequenceMain.m_pThreadMainRun = NULL;

	return 0;
}



void CSequenceMain::Beep_Post(int nState, int nTime)
{
	if (nTime < 500) nTime = 500;

	if (nState == 0) {	// Lot End (Alarm state)
		

	} else if (nState == 1) {	// NG Full
	
	}
	g_objAJinAXL.Write_Output(12);
	theApp.uSleep(nTime);

	g_objAJinAXL.Write_Output(12);
}

//  1. (Error : 3100)
BOOL CSequenceMain::LoadConveyorRun()
{
	static int nDetectCnt[6] = {0, 0, 0, 0, 0, 0}; 

	if(gData.bLdMZWait || gData.bElvLoadWait || gData.bFeederWorkWait)
	{
		g_objCommon.Set_LoadCVStop();
		return TRUE;
	}

	if(gData.bDemoMode)
	{
		if(m_pDX00->iLdCVMZExist5)
		{
			m_pDX00->iLdCVMZExist1R = TRUE; m_pDX00->iLdCVMZExist5 = FALSE;
		}
	}


	switch(m_nLoadConveyorCase)
	{
	case 0:
		m_nLoadConveyorLoop.Set_LoopTime(5000);
		return TRUE;
	case 1:		
		if(m_pDX00->iLdCVMZExist1R || m_pDX00->iLdCVMZExist2 )
		{
			nDetectCnt[0]++; nDetectCnt[1] = 0; nDetectCnt[2] = 0;
			if(nDetectCnt[0] < 5) return TRUE;

			g_objCommon.Set_LdStopper1Down();
			m_nLoadConveyorCase = 4; m_nLoadConveyorLoop.Set_LoopTime(5000);
		}
		else if(!m_pDX00->iLdCVMZExist1R &&
			( m_pDX00->iLdCVMZExist3 || m_pDX00->iLdCVMZExist4 || m_pDX00->iLdCVMZExist5))
		{
			nDetectCnt[1]++; nDetectCnt[0] = 0; nDetectCnt[2] = 0;
			if(nDetectCnt[1] < 5) return TRUE;

			g_objCommon.Set_LdStopper1Up();
			m_nLoadConveyorCase++; m_nLoadConveyorLoop.Set_LoopTime(5000);
		}		
		else
		{
			//case that all sensors not detected, think later 
			nDetectCnt[2]++;
			if(nDetectCnt[2] < 5) return TRUE;

			for(int i = 0; i < 5; i++) nDetectCnt[i] = 0;
		}
		return TRUE;
	case 2:	
		if(g_objCommon.Get_LdStopper1Up() )
		{
			if(!m_nLoadConveyorLoop.Waiting_Time(500)) break;

			g_objCommon.Set_LoadCVRunCW();
			m_nLoadConveyorCase++; m_nLoadConveyorLoop.Set_LoopTime(25000);
		}		
		break;
	case 3:
		if(m_pDX00->iLdCVMZExist2)
		{
			g_objCommon.Set_LoadCVStop();
			Sleep(5);
			g_objCommon.Set_LdStopper1Down();
			m_nLoadConveyorCase++; m_nLoadConveyorLoop.Set_LoopTime(5000);
		}		
		break;
	case 4:
		if(g_objCommon.Get_LdStopper1Down())
		{
			if(!m_nLoadConveyorLoop.Waiting_Time(500)) break;
			m_nLoadConveyorCase++; m_nLoadConveyorLoop.Set_LoopTime(5000);
		}		
		break;
	case 5:
		if(!m_pDX00->iElvMZExist1 || !m_pDX00->iElvMZExist2)
		{
			nDetectCnt[0]++;nDetectCnt[1] = 0; 
			if(nDetectCnt[0] < 5) return TRUE;
						
			g_objCommon.Move_Position(AX_MZ_ELEVATOR_Z, eElv_Z::Ready);
			m_nMZElevCase = ElvBranch::Start; 
			m_nLoadConveyorCase = 0; m_nLoadConveyorLoop.Set_LoopTime(5000);
		}		
		else if(m_pDX00->iElvMZExist1 && m_pDX00->iElvMZExist2)
		{
			nDetectCnt[1]++; nDetectCnt[0] = 0; 
			if(nDetectCnt[1] < 5) return TRUE;
						
			m_nLoadConveyorCase = 1; m_nLoadConveyorLoop.Set_LoopTime(5000);
		}
		else
		{
			for(int i = 0; i < 5; i++) nDetectCnt[i] = 0;
		}
		return TRUE;	
	}
	
	// 1. (Error : 3100)
	if (m_nLoadConveyorLoop.Over_LoopTime()) 
	{		
		g_objCommon.Show_Error(3100 + m_nLoadConveyorCase);
		return FALSE;
	}

	return TRUE;
}

//  2. (Error : 3400)
BOOL CSequenceMain::MZElevRun()
{
	static int  nMZCnt = 0;	
	static int	nMZDetectCnt[6] = {0,0,0,0,0,0};
	DWORD dwTick1 = 0, dwTick2 = 0;
	
	if(gData.bFeederWorkWait) return TRUE;	

	//Suppose MZ on Right of Elev
	switch(m_nMZElevCase)
	{
	case 0:
		m_nMZElevLoop.Set_LoopTime(5000);
		return TRUE;
	case ElvBranch::Start:

		//if(nMZCnt > 0 && !gData.bCycleStop)
		if(g_objCommon.Get_LdStopper1Down() && g_objCommon.Check_Position(AX_MZ_ELEVATOR_Z, eElv_Z::Ready))
		{
			if(!m_nMZElevLoop.Waiting_Time(500)) break;	
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
			m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Load MZ to Elev Start");
		}	
		return TRUE;
	case 2:
		if(!m_pDX00->iElvMZExist1 && !m_pDX00->iElvMZExist2)
		{				
			nMZDetectCnt[0]++;
			if(nMZDetectCnt[0] > 5)
			{
				for(int i = 0; i < 6; i++) nMZDetectCnt[i] = 0;
				g_objCommon.Set_ElevLift1Down(); Sleep(5);
				g_objCommon.Set_ElevStopper2Down(); Sleep(5);
				g_objCommon.Set_LoadCVRunCW();Sleep(15); //CW 회전하려면 CCW도 True 로 해야함  
				g_objCommon.Set_ElevCVRunCW();Sleep(15);
				m_nMZElevCase = ElvBranch::LoadMZ; m_nMZElevLoop.Set_LoopTime(30000);
				m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Load CV CW Start");	
			}
							
		}
		else if (!m_pDX00->iElvMZExist1 && m_pDX00->iElvMZExist2)
		{				
			nMZDetectCnt[1]++;
			if(nMZDetectCnt[1] > 5)
			{
				for(int i = 0; i < 6; i++) nMZDetectCnt[i] = 0;
				g_objCommon.Set_ElevLift1Down(); Sleep(10);
				g_objCommon.Set_ElevLift1Out(); Sleep(10);
				g_objCommon.Set_LoadCVRunCW();Sleep(5); //CW 회전하려면 CCW도 True 로 해야함 
				g_objCommon.Set_ElevCVRunCW();
				m_nMZElevCase = ElvBranch::RdyMZ; m_nMZElevLoop.Set_LoopTime(30000);
				m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Load CV CW Start");		
			}				
		}
		else if(m_pDX00->iElvMZExist1 && !m_pDX00->iElvMZExist2)
		{			
			nMZDetectCnt[2]++;
			if(nMZDetectCnt[2] > 5)
			{
				for(int i = 0; i < 6; i++) nMZDetectCnt[i] = 0;
				gData.bElvSlideOverWait = TRUE;
				m_nMZElevCase = ElvBranch::SlideOver; m_nMZElevLoop.Set_LoopTime(30000);
				m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Load CV CW Start");		
			}
				
		}
		else if(m_pDX00->iElvMZExist1 && m_pDX00->iElvMZExist2)
		{			
			nMZDetectCnt[3]++;
			if(nMZDetectCnt[3] > 5)
			{
				for(int i = 0; i < 6; i++) nMZDetectCnt[i] = 0;
				m_nMZElevCase = 20; m_nMZElevLoop.Set_LoopTime(30000);
				m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Load CV CW Start");	
			}					
		}		
		else 	
		{	
			nMZDetectCnt[5]++;
			if(nMZDetectCnt[5] > 5)
			{
				for(int i = 0; i < 6; i++) nMZDetectCnt[i] = 0;
				m_nMZElevCase = 0; m_nMZElevLoop.Set_LoopTime(5000);
				m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Elevator Full");
			}				
		}
		break;
	case ElvBranch::LoadMZ:	
		if(gData.bDemoMode)
		{
			if(m_pDX00->iLdCVMZExist1R)
			{
				m_pDX00->iElvMZExist1 = TRUE; m_pDX00->iLdCVMZExist1R = FALSE;
			}
		}
		
		if(m_pDX00->iElvMZExist1)
		{
			nMZDetectCnt[0]++; nMZDetectCnt[5] = 0;
			if(nMZDetectCnt[0] < 5) break;

			g_objCommon.Set_LoadCVStop(); Sleep(5);
			g_objCommon.Set_LoadCVRunCCW(); Sleep(5);
			g_objCommon.Set_ElevCVRunCW();
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(30000);
			m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Load CV CW Stop & Elev CV CW Start");
		}
		else
		{
			nMZDetectCnt[5]++;
			if(nMZDetectCnt[5] < 8) break;
			m_nMZElevCase = 0; m_nMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 4:
		if(gData.bDemoMode)
		{
			if(m_pDX00->iElvMZExist1)
			{
				m_pDX00->iElvMZExist2 = TRUE; m_pDX00->iElvMZExist1 = FALSE;
			}
		}

		if(m_pDX00->iElvMZExist2)
		{
			g_objCommon.Set_ElevCVStop(); Sleep(5);
			g_objCommon.Set_LoadCVStop(); Sleep(5);
			
			g_objCommon.Set_ElevStopper2Out();
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
			m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Elev CV CW Stop & Stopper2 Out");
		}
		break;
	case 5:
		if(g_objCommon.Get_ElevStopper2Out() && g_objCommon.Get_ElevStopper2Down())
		{
			if(!m_nMZElevLoop.Waiting_Time(1500)) break;
			g_objCommon.Set_ElevStopper2Up();						
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
			m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Elev Stopper2 Up");
		}
		break;
	case 6:
		if(g_objCommon.Get_ElevStopper2Out() && g_objCommon.Get_ElevStopper2Up())
		{
			if(!m_nMZElevLoop.Waiting_Time(1500)) break;
			g_objCommon.Set_ElevStopper2In();
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
			m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Elev Stopper2 In");
		}
		break;
	case 7:
		if(g_objCommon.Get_ElevStopper2In() && g_objCommon.Get_ElevStopper2Up())
		{
			//Info Processing 
			//Check MZ ID if Exist Move Infomation to Loading MZ UI
			int nFrom = g_dlgWork.SearchMZCVInfo();
			int nTo = g_dlgWork.SearchMZElevInfo(eMZ::Load);

			if(nTo != -1)
			{
				g_dlgWork.TransferMZInfo(nFrom, eMZ::Load);
				gData.sMZIDElevLoad = gData.sMZID[eMZ::Load];

				for(int i = 0; i < 10; i++)
				{
					gData.sZigIDElevLoad[i] = gData.sZigID[eMZ::Load][i];
				}				
				g_dlgWork.PostMessage(UM_UPDATE_MZ_INFO, (int)eMZ::Load, NULL);

				m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
				m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Elev Stopper2 In Done");
			}			
		}
		break;
	case 8:
		m_nLoadConveyorCase = 1;
		m_nMZElevCase = 20;	m_nMZElevLoop.Set_LoopTime(5000);	
		break;
	

	case ElvBranch::RdyMZ:
		if(gData.bDemoMode)
		{
			if(m_pDX00->iLdCVMZExist1R)
			{
				m_pDX00->iElvMZExist1 = TRUE; m_pDX00->iLdCVMZExist1R = FALSE;
			}
		}
		
		if(m_pDX00->iElvMZExist1)
		{
			g_objCommon.Set_ElevCVStop();Sleep(5);
			g_objCommon.Set_LoadCVRunCCW();Sleep(5);
			
			g_objCommon.Set_ElevLift1Out();
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(10000);
			m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Load CV CW Stop & Elev CV CW Start");
		}
		break;	
	case 12:
		if(g_objCommon.Get_ElevLift1Out() && g_objCommon.Get_ElevLift1Down())
		{
			if(!m_nMZElevLoop.Waiting_Time(1000)) break;

			g_objCommon.Set_LoadCVStop();Sleep(5);
			g_objCommon.Set_ElevLift1Up();

			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
			m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Elev Stopper2 Up");
		}
		break;
	case 13:		
		m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		break;
	case 14:
		if(g_objCommon.Get_ElevLift1Out() && g_objCommon.Get_ElevLift1Up())
		{
			if(!m_nMZElevLoop.Waiting_Time(1000)) break;
			g_objCommon.Set_ElevLift1In();			

			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(10000);
			m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Elev Stopper2 In");
		}
		break;
	case 15:
		if(g_objCommon.Get_ElevLift1In() && g_objCommon.Get_ElevLift1Up())
		{
			if(!m_nMZElevLoop.Waiting_Time(1000)) break;
			//Info Processing 
			//Check MZ ID if Exist Move Infomation to Loading MZ UI
			int nFrom = g_dlgWork.SearchMZCVInfo();
			int nTo = g_dlgWork.SearchMZElevInfo(eMZ::Ready);

			if(nTo != -1)
			{
				g_dlgWork.TransferMZInfo(nFrom, eMZ::Ready);
				gData.sMZIDElevReady = gData.sMZID[eMZ::Ready];

				for(int i = 0; i < 10; i++)
				{
					gData.sZigIDElevReady[i] = gData.sZigID[eMZ::Ready][i];
				}				
				g_dlgWork.PostMessage(UM_UPDATE_MZ_INFO, (int)eMZ::Ready, NULL);

				m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
				m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Elev Stopper2 In Done");
			}
		}
		break;
	case 16:
		m_nLoadConveyorCase = 1;
		m_nMZElevCase = 20;	m_nMZElevLoop.Set_LoopTime(5000);	
		break;

	case 20: // working 
		//If additional M/Z added from operator with UI, case can be changed 
		gData.bElvLoadWait = FALSE;
		return TRUE;

	case ElvBranch::Unload:
		{
			int nMZCnt = 0;
			m_nMZElevCase++;m_nMZElevLoop.Set_LoopTime(5000);
		}			
		break;
	case 32:		
		if(m_pDX01->iUldCvMZExist1L)
		{
			nMZDetectCnt[0]++;
			if(nMZDetectCnt[0] > 5){ nMZCnt++; for(int i = 0; i < 5; i++) nMZDetectCnt[i] = 0;}
		}
		if(m_pDX01->iUldCvMZExist2)
		{
			nMZDetectCnt[1]++;
			if(nMZDetectCnt[1] > 5){ nMZCnt++; for(int i = 0; i < 5; i++) nMZDetectCnt[i] = 0;}
		}
		if(m_pDX01->iUldCvMZExist3)
		{
			nMZDetectCnt[2]++;
			if(nMZDetectCnt[2] > 5){ nMZCnt++; for(int i = 0; i < 5; i++) nMZDetectCnt[i] = 0;}
		}
		if(m_pDX01->iUldCvMZExist4)
		{
			nMZDetectCnt[3]++;
			if(nMZDetectCnt[3] > 5){ nMZCnt++; for(int i = 0; i < 5; i++) nMZDetectCnt[i] = 0;}
		}
		nMZDetectCnt[5]++;
		if(nMZDetectCnt[5] > 8)
		{
			for(int i = 0; i < 6; i++) nMZDetectCnt[i] = 0;
			m_nMZElevCase++;m_nMZElevLoop.Set_LoopTime(5000);
		}		
		break;
	case 33:
		if(nMZCnt >= 4)
		{
			nMZDetectCnt[5] = 0;
			m_nMZElevCase = ElvBranch::Unload;			
		}
		else if(nMZCnt < 4 && m_pDX01->iUldCvMZExist1L)
		{
			nMZDetectCnt[5] = 0; // Wait 
			m_nMZElevCase = ElvBranch::Unload;	
		}
		else if(nMZCnt < 4 && !m_pDX01->iUldCvMZExist1L )
		{
			nMZDetectCnt[5]++;
			if(nMZDetectCnt[5] > 5) // over 5 times 
			{
				m_nMZElevCase++;m_nMZElevLoop.Set_LoopTime(5000);
			}					
		}		
		else
		{
			nMZDetectCnt[5] = 0;
		}
		return TRUE;				
	case 34:
		if(gData.bDemoMode)
		{
			if(m_pDX00->iElvMZExist2 )
			{
				gData.bElvUnloadWait = TRUE;
				g_objCommon.Set_ElevStopper2Down();

				m_nMZElevCase++;m_nMZElevLoop.Set_LoopTime(5000);
			}
		}
		else
		{
			if(m_pDX00->iElvMZExist2 && g_objCommon.Get_ElevStopper2Up() && g_objCommon.Get_ElevStopper2In())
			{
				gData.bElvUnloadWait = TRUE;
				g_objCommon.Set_ElevStopper2Down();

				m_nMZElevCase++;m_nMZElevLoop.Set_LoopTime(5000);
			}
		}		
		break;
	case 35:
		m_nMZElevCase++;m_nMZElevLoop.Set_LoopTime(5000);
		break;
	case 36:
		if(g_objCommon.Get_ElevStopper2Down())
		{
			g_objCommon.Set_ElevStopper2Out();
			m_nMZElevCase++;m_nMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 37:
		m_nMZElevCase++;m_nMZElevLoop.Set_LoopTime(5000);
		break;
	case 38:
		if(g_objCommon.Get_ElevStopper2Out())
		{
			g_objCommon.Set_ElevCVRunCW();
			Sleep(5);
			g_objCommon.Set_UnloadCVRunCW();
			m_nMZElevCase++;m_nMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 39:
		if(gData.bDemoMode)
		{
			if(m_pDX00->iElvMZExist2)
			{
				m_pDX01->iUldCvMZExist1L = TRUE; m_pDX00->iElvMZExist2 = FALSE;
			}
		}


		if(m_pDX01->iUldCvMZExist1L)
		{
			g_objCommon.Set_ElevCVStop();
			Sleep(5);
			g_objCommon.Set_UnloadCVStop();	
			gData.bElvUnloadWait = FALSE;
			m_nMZElevCase = 51;m_nMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case ElvBranch::SlideOver:		
		if(m_pDX00->iElvMZExist1)
		{
			nMZDetectCnt[0]++; nMZDetectCnt[1] = 0; 
			if(nMZDetectCnt[0] < 5) break;

			g_objCommon.Set_ElevLift1Out();
			m_nMZElevCase++;m_nMZElevLoop.Set_LoopTime(5000);
		}
		else if(!m_pDX00->iElvMZExist1)
		{
			nMZDetectCnt[1]++; nMZDetectCnt[0] = 0;
			if(nMZDetectCnt[1] < 5) break;

			m_nMZElevCase = 20; m_nMZElevLoop.Set_LoopTime(5000);
		}	
		break;
	case 52:
		m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		break;
	case 53:
		if(g_objCommon.Get_ElevLift1Out())
		{
			g_objCommon.Set_ElevLift1Down();
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		}		
		break;
	case 54:
		m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(15000);
		break;
	case 55:
		if(g_objCommon.Get_ElevLift1Down() && g_objCommon.Get_ElevLift1Out()
			&& g_objCommon.Get_ElevStopper2Down() && g_objCommon.Get_ElevStopper2Out())
		{
			g_objCommon.Set_ElevCVRunCW();
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		}	
		break; 
	case 56:
		m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		break;
	case 57:
		if(gData.bDemoMode)
		{
			if(m_pDX00->iElvMZExist1)
			{
				m_pDX00->iElvMZExist2 = TRUE; m_pDX00->iElvMZExist1 = FALSE;
			}
		}

		if(!m_pDX00->iElvMZExist1 && m_pDX00->iElvMZExist2)
		{
			g_objCommon.Set_ElevCVStop();
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		}		
		break;
	case 58:
		m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		break;
	case 59:
		g_objCommon.Set_ElevStopper2Up();
		m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		break;
	case 60:
		if(g_objCommon.Get_ElevStopper2Up())
		{
			if (!m_nMZElevLoop.Waiting_Time(200)) break;			
			g_objCommon.Set_ElevStopper2In();
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		}		
		break;
	case 61:
		if(g_objCommon.Get_ElevStopper2In())
		{
			if (!m_nMZElevLoop.Waiting_Time(200)) break;

			//Info Processing 
			//Check MZ ID if Exist Move Infomation to Loading MZ UI
			int nFrom = g_dlgWork.SearchMZElevInfo(eMZ::Ready);
			int nTo = g_dlgWork.SearchMZElevInfo(eMZ::Load);

			if(nTo != -1)
			{
				g_dlgWork.TransferMZInfo(eMZ::Ready, eMZ::Load);
				gData.sMZIDElevLoad = gData.sMZIDElevReady; gData.sMZIDElevReady.Empty();
				
				for(int i = 0; i < 10; i++)
				{
					gData.sZigIDElevLoad[i] = gData.sZigID[eMZ::Load][i];
					gData.sZigIDElevReady[i].Empty();
				}				
				g_dlgWork.PostMessage(UM_UPDATE_MZ_INFO, (int)eMZ::Load, NULL);
				g_dlgWork.PostMessage(UM_UPDATE_MZ_INFO, (int)eMZ::Ready, NULL);

				m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
				m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Elev Stopper2 In Done");
			}

			gData.bElvSlideOverWait = FALSE;
			m_nMZElevCase = 20; m_nMZElevLoop.Set_LoopTime(5000);
		}		
		break;
	}

	// 2. (Error : 3400)
	if (m_nMZElevLoop.Over_LoopTime()) 
	{		
		g_objCommon.Show_Error(3400 + m_nMZElevCase);
		return FALSE;
	}

	return TRUE;
}
// 3. (Error : 3700)
BOOL CSequenceMain::FeederRun()
{	
	static double dPosZ = 0.0;

	
	if(gData.bElvLoadWait || gData.bElvSlideOverWait || gData.bElvUnloadWait) return TRUE;
	
	switch(m_nFeederCase)
	{
	case 0:
		m_nFeederLoop.Set_LoopTime(5000);
		return TRUE;

	case (int) FeederBranch::LoadSearch:	
		if(!gData.bElvLoadWait)
		{
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		return TRUE;
	case 2:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready))
		{
			//아래 부터 검사 
			dPosZ = m_pMoveData->dMZElevZ[eElv_Z::Down] - m_pEquipData->dElevPitchZ * (gData.nSlotNoToPick[eMZ::Load] - 1) ;
			g_objAJinAXL.Move_Absolute(AX_MZ_ELEVATOR_Z, dPosZ);

			g_objCommon.Move_Position(AX_ZIG_FEEDER_X, eFeeder_X::MZLoad);

			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Elev Z pitch Move, SlotNo : %d", gData.nSlotNoToPick); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}		
		break;
	case 3:
		if(g_objAJinAXL.Is_MoveDone(AX_MZ_ELEVATOR_Z, dPosZ) && g_objCommon.Check_Position(AX_ZIG_FEEDER_X, eFeeder_X::MZLoad))
		{
			
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("FeederUnit X Move (MZ2), %d"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 4:
		m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		m_strLog.Format("Feeder Y Move (Zig Exist) "); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		break;
	case 5:
		//if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::CheckExist))
		{
			gData.bFeederWorkWait = TRUE; // load Start

			int nExist = -1;
			nExist = g_dlgWork.CheckZigExistInMZ(0, gData.nSlotNoToPick[eMZ::Load]);


			if((m_pDX01->iMagazineZigExist|| gData.bDemoMode) 
				&& nExist == gData.nSlotNoToPick[eMZ::Load])
			{				
				g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::MZLoad);
				m_nFeederCase = 10; m_nFeederLoop.Set_LoopTime(5000);
				m_strLog.Format("Feeder Y Move (Grip Zig)"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
			}
			else
			{
				//Z Pitch Move 
				//g_objAJinAXL.Move_Relative(AX_MZ_ELEVATOR_Z, -m_pEquipData->dMZPitchRightZ*(1.0)); 

				if(gData.nSlotNoToPick[eMZ::Load] > 10) 
				{	
					gData.nSlotNoToPick[eMZ::Load] = 1;
					m_nFeederCase = 0; m_nFeederLoop.Set_LoopTime(5000);
					m_strLog.Format("Elev Z Move to search Finish"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
				}
				else
				{
					gData.nSlotNoToPick[eMZ::Load]++;
					m_nFeederCase = FeederBranch::LoadSearch; m_nFeederLoop.Set_LoopTime(5000);
					m_strLog.Format("Elev Z Move to search Zig"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
				}
				
			}
		}
		break;

	case 10:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::MZLoad))
		{
			m_pDY01->oFeederGripClose = TRUE; m_pDY01->oFeederGripOpen = FALSE;
			g_objAJinAXL.Write_Output(1);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Feeder Grip Close"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 11:
		if(m_pDX01->iFeederGripClose && !m_pDX01->iFeederGripOpen)
		{
			
//#ifndef AJIN_BOARD_USE
//			m_strLog.Format("%d", gData.nSlotNoElev++);
//			gData.sZigIDElev = m_strLog;
//#endif
			//gData.sZigIDElev = Get barcode 
			g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::TrayGrip);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Feeder Y Move (PickUp)"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 12:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::TrayGrip))
		{
			gData.bFeederWorkWait = FALSE;
			//Info Processing 		
			gData.sMZIDFeeder = gData.sMZIDElevLoad; gData.sMZIDElevLoad = "";
			gData.sZigIDFeeder = gData.sZigIDElevLoad[gData.nSlotNoToPick[eMZ::Load] -1]; gData.sZigIDElevLoad[gData.nSlotNoToPick[eMZ::Load] -1] = "";
			gData.nSlotNoFeeder = gData.nSlotNoToPick[eMZ::Load]; 
			memcpy(gData.InfoFeeder, gData.InfoMZLoad[gData.nSlotNoToPick[eMZ::Load] -1], sizeof(int)*ZIG_X*ZIG_Y );
			memset(gData.InfoMZLoad[gData.nSlotNoToPick[eMZ::Load] -1], 0x00, sizeof(int)*ZIG_X*ZIG_Y );

			g_dlgWork.PostMessage(UM_UPDATE_MZ_INFO,eMZ::Load, NULL);

			g_objCommon.Move_Position(AX_ZIG_FEEDER_X, eFeeder_X::TrayGrip);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Feeder X Move (PickUp)"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 13:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_X, eFeeder_X::TrayGrip))
		{
			m_pDY01->oFeederGripClose = FALSE; m_pDY01->oFeederGripOpen = TRUE;
			g_objAJinAXL.Write_Output(1);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Feeder Open"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 14:
		if(m_pDX01->iFeederGripOpen && !m_pDX01->iFeederGripClose)
		{
			g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Feeder Y Move (Ready)"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 15:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready))
		{
			//Info Processing 
			gData.sMZIDRail = gData.sMZIDFeeder; gData.sMZIDFeeder.Empty();
			gData.sZigIDRail = gData.sZigIDFeeder; gData.sZigIDFeeder.Empty();
			gData.nSlotNoRail = gData.nSlotNoFeeder; gData.nSlotNoFeeder = 0;
			memcpy( gData.InfoRail, gData.InfoFeeder,  sizeof(int)*ZIG_X*ZIG_Y);
			memset( gData.InfoFeeder, 0x00, sizeof(int)*ZIG_X*ZIG_Y);	

			gData.nSlotNoToPick[eMZ::Load]++;
			if(gData.nSlotNoToPick[eMZ::Load] > 10) gData.nSlotNoToPick[eMZ::Load] = 1;
			m_nZigPickerCase = ZigPickBranch::Load; // Tray Picker load Start 			
			m_nFeederCase = 0; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Zig Picker load Start "); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 20: // Tray Pick working 
		return TRUE;

	case FeederBranch::Unload:
		
		m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		return TRUE;
	case 31:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready) 
			&& g_objCommon.Check_Position(AX_ZIG_FEEDER_X, eFeeder_X::TrayGrip)
			&& g_objCommon.Get_FeederOpen())
		{
			g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::TrayGrip);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Feeder Y Move (To Pick) "); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 32:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::TrayGrip) && g_objCommon.Get_FeederOpen())
		{
			g_objCommon.Set_FeederClose();
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Feeder Close "); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 33:
		m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		break;
	case 34:
		if(g_objCommon.Get_FeederClose() && (m_pDX01->iFeederZigExist || gData.bDemoMode))
		{
			if(!m_nFeederLoop.Waiting_Time(m_pEquipData->nDelayAdd[eDelay::FeederGrip])) break;
				
			//Info Processing
			gData.sMZIDFeeder = gData.sMZIDRail; gData.sMZIDRail.Empty();
			gData.sZigIDFeeder = gData.sZigIDRail; gData.sZigIDRail.Empty();
			gData.nSlotNoFeeder = gData.nSlotNoRail; gData.nSlotNoRail = 0;
			memcpy( gData.InfoFeeder, gData.InfoRail,  sizeof(int)*ZIG_X*ZIG_Y);
			memset( gData.InfoRail, 0x00, sizeof(int)*ZIG_X*ZIG_Y);	
			
			
			g_objCommon.Move_Position(AX_ZIG_FEEDER_X, eFeeder_X::MZLoad);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Rail X Move (Unload)"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 35:
		if(!gData.bElvLoadWait)
		{
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		return TRUE;

	case 36:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_X, eFeeder_X::MZLoad))
		{				
			gData.bFeederWorkWait = TRUE; // unload Start 
			g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::MZLoad);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Feeder Y Move (Unload)"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);			
		}
		break;
	case 37:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::MZLoad) && (m_pDX01->iFeederZigExist || gData.bDemoMode))
		{
			g_objCommon.Set_FeederOpen();
			m_strLog.Format("Feeder Open"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
			m_nFeederCase = 38; m_nFeederLoop.Set_LoopTime(5000);			
		}
		break;
	case 38:
		if(g_objCommon.Get_FeederOpen() )
		{
			if(!m_nFeederLoop.Waiting_Time(m_pEquipData->nDelayAdd[eDelay::FeederUnGrip])) break;

			//Info Processing
			gData.sMZIDElevUnload = gData.sMZIDFeeder; gData.sMZIDFeeder.Empty();
			gData.sZigIDElevUnload[gData.nSlotNoFeeder - 1] = gData.sZigIDFeeder; gData.sZigIDFeeder.Empty();
						
			memcpy( gData.InfoMZUnload[gData.nSlotNoFeeder-1], gData.InfoFeeder,  sizeof(int)*ZIG_X*ZIG_Y);
			memset( gData.InfoFeeder, 0x00, sizeof(int)*ZIG_X*ZIG_Y);	

			gData.nSlotNoFeeder = 0;

			g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready);

			g_dlgWork.PostMessage(UM_UPDATE_MZ_INFO,eMZ::Load, NULL);

			m_strLog.Format("Feeder Open"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
			m_nFeederCase = 40; m_nFeederLoop.Set_LoopTime(5000);			
		}
		break;
	case 40:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready) && (!m_pDX01->iFeederZigExist || gData.bDemoMode))
		{
			gData.bFeederWorkWait = FALSE;

			if(CheckCtZigAllReturn())
			{
				m_nMZElevCase = ElvBranch::Unload;
			}
			m_strLog.Format("Back to Branch"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
			m_nFeederCase = 0; m_nFeederLoop.Set_LoopTime(5000);			
		}		
		break;


	case (int) FeederBranch::RdySearch:	
		if(!gData.bElvLoadWait)
		{
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		return TRUE;
	case 52:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready))
		{
			//아래 부터 검사 
			dPosZ = m_pMoveData->dMZElevZ[eElv_Z::Down] - m_pEquipData->dElevPitchZ * (gData.nSlotNoToPick[eMZ::Ready] - 1) ;
			g_objAJinAXL.Move_Absolute(AX_MZ_ELEVATOR_Z, dPosZ);

			g_objCommon.Move_Position(AX_ZIG_FEEDER_X, eFeeder_X::MZReady);

			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Elev Z pitch Move, SlotNo : %d", gData.nSlotNoToPick); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}		
		break;
	case 53:
		if(g_objAJinAXL.Is_MoveDone(AX_MZ_ELEVATOR_Z, dPosZ) && g_objCommon.Check_Position(AX_ZIG_FEEDER_X, eFeeder_X::MZReady))
		{
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("FeederUnit X Move (MZ2), %d"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 54:
		m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		m_strLog.Format("Feeder Y Move (Zig Exist) "); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		break;
	case 55:
		//if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::CheckExist))
		{
			gData.bFeederWorkWait = TRUE; // load Start

			int nExist = -1;
			nExist = g_dlgWork.CheckZigExistInMZ(eMZ::Ready, gData.nSlotNoToPick[eMZ::Ready]);

			if( (m_pDX01->iMagazineZigExist || gData.bDemoMode) && nExist == gData.nSlotNoToPick[eMZ::Ready])
			{				
				g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::MZReady);
				m_nFeederCase = 60; m_nFeederLoop.Set_LoopTime(5000);
				m_strLog.Format("Feeder Y Move (Grip Zig)"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
			}
			else
			{
				//Z Pitch Move 
				//g_objAJinAXL.Move_Relative(AX_MZ_ELEVATOR_Z, -m_pEquipData->dMZPitchRightZ*(1.0)); 

				if(gData.nSlotNoToPick[eMZ::Ready] > 10) 
				{	
					gData.nSlotNoToPick[eMZ::Ready] = 1;
					m_nFeederCase = 0; m_nFeederLoop.Set_LoopTime(5000);
					m_strLog.Format("Elev Z Move to search Finish"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
				}
				else
				{
					gData.nSlotNoToPick[eMZ::Ready]++;
					m_nFeederCase = FeederBranch::RdySearch; m_nFeederLoop.Set_LoopTime(5000);
					m_strLog.Format("Elev Z Move to search Zig"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
				}
			}
		}
		break;

	case 60:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::MZReady))
		{
			m_pDY01->oFeederGripClose = TRUE; m_pDY01->oFeederGripOpen = FALSE;
			g_objAJinAXL.Write_Output(1);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Feeder Grip Close"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 61:
		if(m_pDX01->iFeederGripClose && !m_pDX01->iFeederGripOpen)
		{
			//#ifndef AJIN_BOARD_USE
			//			m_strLog.Format("%d", gData.nSlotNoElev++);
			//			gData.sZigIDElev = m_strLog;
			//#endif
			//gData.sZigIDElev = Get barcode 
			g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::TrayGrip);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Feeder Y Move (PickUp)"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 62:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::TrayGrip))
		{
			gData.bFeederWorkWait = FALSE;	
		
			//Info Processing 		
			gData.sMZIDFeeder = gData.sMZIDElevReady; gData.sMZIDElevReady = "";
			gData.sZigIDFeeder = gData.sZigIDElevReady[gData.nSlotNoToPick[eMZ::Ready] -1]; gData.sZigIDElevReady[gData.nSlotNoToPick[eMZ::Ready] -1] = "";
			gData.nSlotNoFeeder = gData.nSlotNoToPick[eMZ::Ready]; 
			memcpy(gData.InfoFeeder, gData.InfoMZReady[gData.nSlotNoToPick[eMZ::Ready] -1], sizeof(int)*ZIG_X*ZIG_Y );
			memset(gData.InfoMZReady[gData.nSlotNoToPick[eMZ::Ready] -1], 0x00, sizeof(int)*ZIG_X*ZIG_Y );

			g_dlgWork.PostMessage(UM_UPDATE_MZ_INFO,eMZ::Ready, NULL);

			g_objCommon.Move_Position(AX_ZIG_FEEDER_X, eFeeder_X::TrayGrip);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Feeder X Move (PickUp)"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 63:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_X, eFeeder_X::TrayGrip))
		{
			m_pDY01->oFeederGripClose = FALSE; m_pDY01->oFeederGripOpen = TRUE;
			g_objAJinAXL.Write_Output(1);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Feeder Open"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 64:
		if(m_pDX01->iFeederGripOpen && !m_pDX01->iFeederGripClose)
		{
			g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Feeder Y Move (Ready)"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 65:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready))
		{
			//Info Processing 
			gData.sMZIDRail = gData.sMZIDFeeder; gData.sMZIDFeeder.Empty();
			gData.sZigIDRail = gData.sZigIDFeeder; gData.sZigIDFeeder.Empty();
			gData.nSlotNoRail = gData.nSlotNoFeeder; gData.nSlotNoFeeder = 0;
			memcpy( gData.InfoRail, gData.InfoFeeder,  sizeof(int)*ZIG_X*ZIG_Y);
			memset( gData.InfoFeeder, 0x00, sizeof(int)*ZIG_X*ZIG_Y);	

			gData.nSlotNoToPick[eMZ::Ready]++;
			if(gData.nSlotNoToPick[eMZ::Ready] > 10) gData.nSlotNoToPick[eMZ::Ready] = 1;
			m_nZigPickerCase = ZigPickBranch::Load; // Tray Picker load Start 			
			m_nFeederCase = 0; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Zig Picker load Start "); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	}
	
	// 3. (Error : 3700)
	if (m_nFeederLoop.Over_LoopTime()) 
	{		
		g_objCommon.Show_Error(3700 + m_nFeederCase);
		return FALSE;
	}

	return TRUE;
}
// 4. (Error : 4000)
BOOL CSequenceMain::ZigPickerRun()
{
	switch(m_nZigPickerCase)
	{
	case 0:
		m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		return TRUE;
	case (int) ZigPickBranch::Load:
			if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready) 
				&& (!m_pDX01->iZigPickerExist || gData.bDemoMode))
			{
				g_objCommon.Move_Position(AX_ZIG_PICKER_Y, eZigPicker_Y::Load);
				m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
				m_strLog.Format("Zig Picker Y Move (Rail)"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
			}
		
		break;
	case 2:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Y, eZigPicker_Y::Load))
		{
			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::LoadDown);
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("ZigPicker Z Move (Pickup)"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 3:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::LoadDown))
		{
			g_objCommon.Set_TrayPickMasterIn();
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Picker Master In"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 4:
		if(g_objCommon.Get_TrayPickMasterIn())
		{
			if(!m_nFeederLoop.Waiting_Time(m_pEquipData->nDelayAdd[eDelay::TrayPickGrip])) break;
			g_objCommon.Set_TrayPickSlaveIn();
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Picker Slave In"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;	
	case 5:
		if(g_objCommon.Get_TrayPickMasterSlaveIn())
		{
			if(!m_nFeederLoop.Waiting_Time(m_pEquipData->nDelayAdd[eDelay::TrayPickGrip])) break;
			//Info Processing
			gData.sMZIDTrayPick = gData.sMZIDRail; gData.sMZIDRail = "";
			gData.sZigIDTrayPick =  gData.sZigIDRail; gData.sZigIDRail = "";
			gData.nSlotNoTrayPick = gData.nSlotNoRail; gData.nSlotNoRail = 0;
			memcpy(gData.InfoZigPick, gData.InfoRail, sizeof(int)*ZIG_X*ZIG_Y);
			memset( gData.InfoRail, 0, sizeof(int)*ZIG_X*ZIG_Y);
			
			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready);
			m_nZigPickerCase = 10; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Picker Z Move (Ready)"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 10:
		if( m_nFeederCase == 0 ) 
		{
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Feeder Search restart"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}		
		return TRUE;
	case 11:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready) 
			&& (m_pDX01->iRailZigExist || gData.bDemoMode))
		{				
			g_objCommon.Move_Position(AX_ZIG_PICKER_Y, eZigPicker_Y::Index);
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Picker Y Move (Index)"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 12:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Y, eZigPicker_Y::Index))
		{
			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Index);
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Picker Z Move Down"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 13:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Index))
		{
			g_objCommon.Set_TrayPickSlaveOut();
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Picker Slave Out"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 14:
		if(g_objCommon.Get_TrayPickSlaveOut())
		{
			if(!m_nFeederLoop.Waiting_Time(m_pEquipData->nDelayAdd[eDelay::TrayPickUnGrip])) break;
			g_objCommon.Set_TrayPickMasterOut();
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Picker Master Out"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 15:
		if(g_objCommon.Get_TrayPickMasterSlaveOut())
		{
			if(!m_nFeederLoop.Waiting_Time(m_pEquipData->nDelayAdd[eDelay::TrayPickUnGrip])) break;
			//Info Processing 
			gData.sMZIDMainIdex[eMainIndex::Load] = gData.sMZIDTrayPick; gData.sMZIDTrayPick = "";
			gData.sZigIDMainIndex[eMainIndex::Load] =  gData.sZigIDTrayPick; gData.sZigIDTrayPick = "";
			gData.nSlotNoMainIndex[eMainIndex::Load] = gData.nSlotNoTrayPick; gData.nSlotNoTrayPick = 0;

			memcpy(gData.InfoMainIndex[eMainIndex::Load], gData.InfoZigPick, sizeof(int)*ZIG_X*ZIG_Y);
			memset(gData.InfoZigPick, 0x00, sizeof(int)*ZIG_X*ZIG_Y);
			gData.bIndexDone[eMainIndex::Load] = TRUE;

			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready);
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Picker Z Move (Ready Up)"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 16:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready) && (!m_pDX01->iZigPickerExist || gData.bDemoMode))
		{
			//Load Done		
			m_nZigPickerCase = 0; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Picker Load Done"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
		//Unload 
	case (int) ZigPickBranch::Unload:
		m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		return TRUE;
	case 21:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready) && (!m_pDX01->iZigPickerExist || gData.bDemoMode))
		{
			g_objCommon.Move_Position(AX_ZIG_PICKER_Y, eZigPicker_Y::Index);
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Picker Y Move (Index)"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 22:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Y, eZigPicker_Y::Index))
		{
			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Index);
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Picker Z Move (Pick Up)"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 23:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Index))
		{
			g_objCommon.Set_TrayPickMasterIn();
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Picker Master In"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 24:
		if(g_objCommon.Get_TrayPickMasterIn())
		{
			if(!m_nFeederLoop.Waiting_Time(m_pEquipData->nDelayAdd[eDelay::TrayPickGrip])) break;
			g_objCommon.Set_TrayPickSlaveIn();
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Picker Slave In"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 25:
		if(g_objCommon.Get_TrayPickMasterSlaveIn())
		{
			if(!m_nFeederLoop.Waiting_Time(m_pEquipData->nDelayAdd[eDelay::TrayPickGrip])) break;
			//Info Processing
			gData.sMZIDTrayPick = gData.sMZIDMainIdex[eMainIndex::Unload]; gData.sMZIDMainIdex[eMainIndex::Unload] = "";
			gData.sZigIDTrayPick = gData.sZigIDMainIndex[eMainIndex::Unload]; gData.sZigIDMainIndex[eMainIndex::Unload] = "";
			gData.nSlotNoTrayPick = gData.nSlotNoMainIndex[eMainIndex::Unload]; gData.nSlotNoMainIndex[eMainIndex::Unload] = 0;

			memcpy(gData.InfoZigPick, gData.InfoMainIndex[eMainIndex::Unload], sizeof(int)*ZIG_X*ZIG_Y);
			memset( gData.InfoMainIndex[eMainIndex::Unload], 0x00, sizeof(int)*ZIG_X*ZIG_Y);

			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready);
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Picker Z Move (Ready)"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 26:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready) && (m_pDX01->iZigPickerExist || gData.bDemoMode))
		{
			gData.bIndexDone[eMainIndex::Unload] = TRUE; // Index Unload Done 	

			g_objCommon.Move_Position(AX_ZIG_PICKER_Y, eZigPicker_Y::Load);
			g_objCommon.Move_Position(AX_ZIG_FEEDER_X, eFeeder_X::TrayGrip);
			g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready);

			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Picker Y Move (Rail)"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 27:		
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Y, eZigPicker_Y::Load)
			&& g_objCommon.Check_Position(AX_ZIG_FEEDER_X, eFeeder_X::TrayGrip)
			&& g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready))
		{
			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::LoadDown);
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Picker Z Move Pick Down"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 28:		
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::LoadDown))
		{
			g_objCommon.Set_TrayPickSlaveOut(); 
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Picker Slave Out"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 29:
		if(g_objCommon.Get_TrayPickSlaveOut())
		{
			if(!m_nFeederLoop.Waiting_Time(m_pEquipData->nDelayAdd[eDelay::TrayPickUnGrip])) break;
			g_objCommon.Set_TrayPickMasterOut();
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Picker Master Out"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 30:
		if(g_objCommon.Get_TrayPickMasterSlaveOut())
		{
			if(!m_nFeederLoop.Waiting_Time(m_pEquipData->nDelayAdd[eDelay::TrayPickUnGrip])) break;
			//Info Processing 
			gData.sMZIDRail = gData.sMZIDTrayPick; gData.sMZIDTrayPick.Empty();
			gData.sZigIDRail = gData.sZigIDTrayPick; gData.sZigIDTrayPick.Empty();
			gData.nSlotNoRail = gData.nSlotNoTrayPick; gData.nSlotNoTrayPick = 0;
			memcpy( gData.InfoRail, gData.InfoZigPick,  sizeof(int)*ZIG_X*ZIG_Y);
			memset( gData.InfoZigPick, 0x00, sizeof(int)*ZIG_X*ZIG_Y);			

			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready);
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Picker Z Move (Ready)"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 31:		
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready) && (!m_pDX01->iZigPickerExist || gData.bDemoMode))
		{			
			m_nFeederCase = (int) FeederBranch::Unload;
					
			m_nZigPickerCase = 0; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Feeder and Rail Start (Unload)"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	/*case 32:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Index))
		{
			g_objCommon.Set_TrayPickMasterIn();
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Picker Master In"); m_nFeederLoop.Takt_Save(4, m_nFeederCase, m_strLog);
		}
		break;
	case 33:
		if(g_objCommon.Get_TrayPickMasterIn())
		{
			g_objCommon.Set_TrayPickSlaveIn();
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Elev Z pitch Move, SlotNo"); m_nFeederLoop.Takt_Save(4, m_nFeederCase, m_strLog);
		}
		break;
	case 34:
		if(g_objCommon.Get_TrayPickMasterSlaveIn())
		{
			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Ready);
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Elev Z pitch Move, SlotNo"); m_nFeederLoop.Takt_Save(4, m_nFeederCase, m_strLog);
		}
		break;
	case 35:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Ready))
		{
			g_objCommon.Move_Position(AX_ZIG_PICKER_Y, Tray_Picker_Y::Rail);
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Elev Z pitch Move, SlotNo"); m_nFeederLoop.Takt_Save(4, m_nFeederCase, m_strLog);
		}
		break;
	case 36:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Y, Tray_Picker_Y::Rail))
		{
			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Rail);
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Elev Z pitch Move, SlotNo"); m_nFeederLoop.Takt_Save(4, m_nFeederCase, m_strLog);
		}
		break;
	case 37:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Rail))
		{
			g_objCommon.Set_TrayPickSlaveOut();
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Elev Z pitch Move, SlotNo"); m_nFeederLoop.Takt_Save(4, m_nFeederCase, m_strLog);
		}
		break;
	case 38:
		if(g_objCommon.Get_TrayPickSlaveOut())
		{
			g_objCommon.Set_TrayPickMasterOut();
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Elev Z pitch Move, SlotNo"); m_nFeederLoop.Takt_Save(4, m_nFeederCase, m_strLog);
		}
		break;
	case 39:
		if(g_objCommon.Get_TrayPickMasterSlaveOut())
		{
			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Ready);
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Elev Z pitch Move, SlotNo"); m_nFeederLoop.Takt_Save(4, m_nFeederCase, m_strLog);
		}
		break;
	case 40:
		m_nMainIndexCase = (int)MainIndexBranch::CheckInOut;
		m_nZigPickerCase = 0; m_nZigPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		m_strLog.Format("Elev Z pitch Move, SlotNo"); m_nFeederLoop.Takt_Save(4, m_nFeederCase, m_strLog);
		break;*/

	}

	// 4. (Error : 4000)
	if (m_nZigPickerLoop.Over_LoopTime()) 
	{		
		g_objCommon.Show_Error(4000 + m_nZigPickerCase);
		return FALSE;
	}
	return TRUE;
}

// 5. (Error : 4300)
BOOL CSequenceMain::LensCleanerRun()
{
	switch(m_nLensCleanerCase)
	{
	case 0:
		m_nLensCleanerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		return TRUE;
	case 1:
		if(!gData.bIndexDone[eMainIndex::Clean] && !Check_IndexEmpty(eMainIndex::Clean))
		{
			m_nLensCleanerCase++;  m_nLensCleanerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Lens Cleanner Start"); m_nLensCleanerLoop.Takt_Save(5, m_nLensCleanerCase, m_strLog);
		}
		else if(!gData.bIndexDone[eMainIndex::Clean] && Check_IndexEmpty(eMainIndex::Clean) )
		{
			gData.bIndexDone[eMainIndex::Clean] = TRUE;
			m_nLensCleanerCase = 0; m_nLensCleanerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);	
			m_strLog.Format("Lens Cleanner Done"); m_nLensCleanerLoop.Takt_Save(5, m_nLensCleanerCase, m_strLog);
		}
		return TRUE;
	case 2:
		g_objCommon.Set_CleanerClose();
		m_nLensCleanerCase++; m_nLensCleanerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		m_strLog.Format("Lens Cleanner Close"); m_nLensCleanerLoop.Takt_Save(5, m_nLensCleanerCase, m_strLog);
		break;
	case 3:
		if(g_objCommon.Get_CleanerClose())
		{
			g_objCommon.Set_CleanerForward();
			m_nLensCleanerCase++; m_nLensCleanerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Lens Cleanner Forward"); m_nLensCleanerLoop.Takt_Save(5, m_nLensCleanerCase, m_strLog);
		}		
		break;
	case 4:
		if(g_objCommon.Get_CleanerForwardDone())
		{
			g_objCommon.Set_CleanerOpen();
			m_nLensCleanerCase++; m_nLensCleanerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Lens Cleanner Open"); m_nLensCleanerLoop.Takt_Save(5, m_nLensCleanerCase, m_strLog);
		}
		break;
	case 5:
		if(g_objCommon.Get_CleanerOpen())
		{
			g_objCommon.Set_CleanerBackward();
			m_nLensCleanerCase++; m_nLensCleanerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Lens Cleanner Backward"); m_nLensCleanerLoop.Takt_Save(5, m_nLensCleanerCase, m_strLog);
		}
	case 6:
		if(g_objCommon.Get_CleanerBackwardDone())
		{
			gData.bIndexDone[eMainIndex::Clean] = TRUE;
			m_nLensCleanerCase = 0; m_nLensCleanerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);	
			m_strLog.Format("Lens Cleanner Done"); m_nLensCleanerLoop.Takt_Save(5, m_nLensCleanerCase, m_strLog);
		}
		break;
	}


	// 5. (Error : 4300)
	if (m_nLensCleanerLoop.Over_LoopTime()) 
	{		
		g_objCommon.Show_Error(4300 + m_nLensCleanerCase);
		return FALSE;
	}
	return TRUE;
}

// 6. (Error : 4600)
BOOL CSequenceMain::TopInspectorRun()
{
	static int nTopXPos = 0, nTopYPos = 0;
	static double	dTopUnitX, dTopUnitY, dTopUnitZ = 0.0;

	switch(m_nTopInspectCase)
	{
	case 0:
		m_nTopInspectLoop.Set_LoopTime(5000);
		return TRUE;
	case 1:
		if(!gData.bIndexDone[eMainIndex::Top] && !Check_IndexEmpty(eMainIndex::Top)  )
		{
			m_nTopInspectCase++;
			m_nTopInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Top Vision Start"); m_nTopInspectLoop.Takt_Save(6, m_nTopInspectCase, m_strLog);
		}
		else if(!gData.bIndexDone[eMainIndex::Top] && Check_IndexEmpty(eMainIndex::Top)  )
		{
			gData.bIndexDone[eMainIndex::Top] = TRUE;
			m_nTopInspectCase = 0; m_nTopInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);	
			m_strLog.Format("Top Vision Done"); m_nTopInspectLoop.Takt_Save(5, m_nTopInspectCase, m_strLog);
		}		
		return TRUE;
	case 2:
		if(g_objAJinAXL.Is_Done(AX_TOP_INSPECTOR_Z))
		{
			Init_TopZig();
			nTopXPos = 1; nTopYPos = 1;
			m_nTopInspectCase++; m_nTopInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Top Vision Use"); m_nTopInspectLoop.Takt_Save(6, m_nTopInspectCase, m_strLog);

			/*if(m_pEquipData->bUseTopVision)
			{
				Init_TopZig();
				nTopXPos = 1; nTopYPos = 1;
				m_nTopInspectCase++; m_nTopInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
				m_strLog.Format("Top Vision Use"); m_nTopInspectLoop.Takt_Save(6, m_nTopInspectCase, m_strLog);
			}
			else
			{
				m_nTopInspectCase = 15; m_nTopInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
				m_strLog.Format("Top Vision Skip"); m_nTopInspectLoop.Takt_Save(6, m_nTopInspectCase, m_strLog);
			}*/
		}
		break;
	case 3:
		if(Select_TopScanPos(nTopXPos, nTopYPos))
		{
			int nIdx = (nTopYPos - 1) * gData.nZigX + nTopXPos;
			dTopUnitY = m_pMoveData->dTopInspectorY[eTopInspect_Y::ScanStart] + (m_pEquipData->dZigPitchY * (nTopYPos - 1));
			dTopUnitX = m_pMoveData->dTopInspectorX[eTopInspect_X::ScanStart] + (m_pEquipData->dZigPitchX * (nTopXPos - 1));
			dTopUnitZ = m_pMoveData->dTopInspectorZ[eTopInspect_Z::ScanStart];
			
			g_objAJinAXL.Move_Absolute(AX_TOP_INSPECTOR_Y, dTopUnitY);
			g_objAJinAXL.Move_Absolute(AX_TOP_INSPECTOR_X, dTopUnitX);
			g_objAJinAXL.Move_Absolute(AX_TOP_INSPECTOR_Z, dTopUnitZ);

			m_nTopInspectCase++; m_nTopInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]); 
		}
		else
		{
			//Done
			m_nTopInspectCase = 15; m_nTopInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 4:
		if (g_objAJinAXL.Is_MoveDone(AX_TOP_INSPECTOR_Y, dTopUnitY) &&
			g_objAJinAXL.Is_MoveDone(AX_TOP_INSPECTOR_X, dTopUnitX) &&
			g_objAJinAXL.Is_MoveDone(AX_TOP_INSPECTOR_Z, dTopUnitZ))
		{

			if (!m_pEquipData->bUseTopVision)
			{
				if (gData.InfoMainIndex[eMainIndex::Top][nTopXPos-1][nTopYPos-1] == eLensState::TopReady)
					gData.InfoMainIndex[eMainIndex::Top][nTopXPos-1][nTopYPos-1] = eLensState::TopDone;	//Scan Done
			
				m_nTopInspectCase = 10; m_nTopInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Scan]);
			} 
			else 
			{
				int nLensNo = (gData.nZigY - nTopYPos) * gData.nZigX + nTopXPos;	// Tray 하단부터 모듈 적재한다.
				//g_objInspector.Set_LoadComplete(VISION_PC1, "T1", gData.sZigIDMainIndex[eMainIndex::Top] , gData.sMZIDMainIdex[eMainIndex::Top], gData.nSlotNoMainIndex[eMainIndex::Top], nLensNo);
				m_nTopInspectCase = (int)TopBranch::VisionWait; m_nTopInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Scan]);			
			}
		}
		break;
	case (int)TopBranch::VisionWait:
		if (!m_pEquipData->bUseTopVision)
		{
			m_nTopInspectCase = 10; m_nTopInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Scan]);
		}
		break;
	case 6:	// Top1 Z Focus Move
		if (g_objAJinAXL.Is_Done(AX_TOP_INSPECTOR_Z)) 
		{
			g_objAJinAXL.Move_Absolute(AX_TOP_INSPECTOR_Z, m_dTop1Z);
					
			m_nTopInspectCase++; m_nTopInspectLoop.Set_LoopTime(5000);
		}
		break;
	case 7:	// Send Move Complete
		if (g_objAJinAXL.Is_Done(AX_TOP_INSPECTOR_Z)) 
		{			
			CString strLog;
			//g_objInspector.Set_ZMoveComplete(VISION_PC1, "T1");
			m_nTopInspectCase = 5; m_nTopInspectLoop.Set_LoopTime(30000);	// 90초		
		}
		break;
	case 10:
		nTopYPos++;
		if(nTopYPos > gData.nZigY) 
		{
			nTopXPos++; nTopYPos = 1;
		}
		m_nTopInspectCase = 3; m_nTopInspectLoop.Set_LoopTime(5000);
		break;	
	case 15:
		g_objCommon.Move_Position(AX_TOP_INSPECTOR_Z, eTopInspect_Z::Ready);
		gData.bIndexDone[eMainIndex::Top] = TRUE;
		m_nTopInspectCase = 0; m_nTopInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		m_strLog.Format("Top Vision Done"); m_nTopInspectLoop.Takt_Save(6, m_nTopInspectCase, m_strLog);
		break;

	}

	// 6. (Error : 4600)
	if (m_nTopInspectLoop.Over_LoopTime()) 
	{		
		g_objCommon.Show_Error(4600 + m_nTopInspectCase);
		return FALSE;
	}
	return TRUE;
}

// 7. (Error : 4900)
BOOL CSequenceMain::BtmInspectorRun()
{
	static int nBtmXPos = 0, nBtmYPos = 0;
	static double	dBtmUnitX, dBtmUnitY, dBtmUnitZ = 0.0;

	switch(m_nBtmInspectCase)
	{
	case 0:
		m_nBtmInspectLoop.Set_LoopTime(5000);
		return TRUE;
	case 1:
		if(!gData.bIndexDone[eMainIndex::Btm] && !Check_IndexEmpty(eMainIndex::Btm) )
		{
			m_nBtmInspectCase++;
			m_nBtmInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Btm Vision Start"); m_nBtmInspectLoop.Takt_Save(7, m_nBtmInspectCase, m_strLog);
		}
		else if(!gData.bIndexDone[eMainIndex::Btm] && Check_IndexEmpty(eMainIndex::Btm) )
		{
			gData.bIndexDone[eMainIndex::Btm] = TRUE;
			m_nBtmInspectCase = 0; m_nBtmInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);	
			m_strLog.Format("Btm Vision Done"); m_nBtmInspectLoop.Takt_Save(5, m_nBtmInspectCase, m_strLog);
		}		
		return TRUE;
	case 2:
		if(g_objCommon.Check_Position(AX_BTM_INSPECTOR_Z, eBtmInspect_Z::Ready))
		{
			Init_TopZig();
			nBtmXPos = 1; nBtmYPos = 1;
			m_nBtmInspectCase++; m_nBtmInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Btm Vision Use"); m_nBtmInspectLoop.Takt_Save(7, m_nBtmInspectCase, m_strLog);

			/*if(m_pEquipData->bUseBtmVision)
			{
			Init_TopZig();
			nBtmXPos = 1; nBtmYPos = 1;
			m_nBtmInspectCase++; m_nBtmInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Btm Vision Use"); m_nBtmInspectLoop.Takt_Save(7, m_nBtmInspectCase, m_strLog);
			}
			else
			{
			m_nBtmInspectCase = 15; m_nBtmInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Btm Vision Skip"); m_nBtmInspectLoop.Takt_Save(7, m_nBtmInspectCase, m_strLog);
			}*/
		}
		break;
	case 3:
		if(Select_BtmScanPos(nBtmXPos, nBtmYPos))
		{
			int nIdx = (nBtmYPos - 1) * gData.nZigX + nBtmXPos;
			dBtmUnitY = m_pMoveData->dBtmInspectorY[eTopInspect_Y::ScanStart] + (m_pEquipData->dZigPitchY * (nBtmYPos - 1));
			dBtmUnitX = m_pMoveData->dBtmInspectorX[eTopInspect_X::ScanStart] + (m_pEquipData->dZigPitchX * (nBtmXPos - 1));
			dBtmUnitZ = m_pMoveData->dBtmInspectorZ[eTopInspect_Z::ScanStart];

			g_objAJinAXL.Move_Absolute(AX_BTM_INSPECTOR_Y, dBtmUnitY);
			g_objAJinAXL.Move_Absolute(AX_BTM_INSPECTOR_X, dBtmUnitX);
			g_objAJinAXL.Move_Absolute(AX_BTM_INSPECTOR_Z, dBtmUnitZ);

			m_nBtmInspectCase++; m_nBtmInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		else
		{
			//Done
			m_nBtmInspectCase = 15; m_nBtmInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 4:
		if (g_objAJinAXL.Is_MoveDone(AX_BTM_INSPECTOR_Y, dBtmUnitY) &&
			g_objAJinAXL.Is_MoveDone(AX_BTM_INSPECTOR_X, dBtmUnitX) &&
			g_objAJinAXL.Is_MoveDone(AX_BTM_INSPECTOR_Z, dBtmUnitZ))
		{

			if (!m_pEquipData->bUseTopVision)
			{
				if (gData.InfoMainIndex[eMainIndex::Btm][nBtmYPos-1][nBtmXPos-1] == eLensState::BtmReady)
					gData.InfoMainIndex[eMainIndex::Btm][nBtmYPos-1][nBtmXPos-1] = eLensState::BtmDone;	//Scan Done
				
				m_nBtmInspectCase = 10; m_nBtmInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Scan]);
			} 
			else 
			{
				int nLensNo = (gData.nZigY - nBtmYPos) * gData.nZigX + nBtmXPos;	// Tray 하단부터 모듈 적재한다.
				//g_objInspector.Set_LoadComplete(VISION_PC1, "B1", gData.sZigIDMainIndex[eMainIndex::Btm] , gData.sMZIDMainIdex[eMainIndex::Btm], gData.nSlotNoMainIndex[eMainIndex::Btm], nLensNo);
				m_nBtmInspectCase = (int)BtmBranch::VisionWait; m_nBtmInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Scan]);			
			}
		}
		break;
	case (int)BtmBranch::VisionWait:
		if (!m_pEquipData->bUseBtmVision)
		{
			m_nBtmInspectCase = 10; m_nBtmInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Scan]);
		}
		break;
	case 6:	// Top1 Z Focus Move
		if (g_objAJinAXL.Is_Done(AX_BTM_INSPECTOR_Z)) 
		{
			g_objAJinAXL.Move_Absolute(AX_BTM_INSPECTOR_Z, m_dTop1Z);

			m_nBtmInspectCase++; m_nBtmInspectLoop.Set_LoopTime(5000);
		}
		break;
	case 7:	// Send Move Complete
		if (g_objAJinAXL.Is_Done(AX_BTM_INSPECTOR_Z)) 
		{			
			CString strLog;
			//g_objInspector.Set_ZMoveComplete(VISION_PC1, "B1");
			m_nBtmInspectCase = (int)BtmBranch::VisionWait; m_nBtmInspectLoop.Set_LoopTime(30000);	// 90초		
		}
		break;
	case 10:
		nBtmXPos++;
		if(nBtmXPos > gData.nZigX) 
		{
			nBtmXPos = 1; nBtmYPos++;
		}
		m_nBtmInspectCase = 2; m_nBtmInspectLoop.Set_LoopTime(5000);
		break;	
	case 15:
		gData.bIndexDone[eMainIndex::Btm] = TRUE;
		m_nBtmInspectCase = 0; m_nBtmInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		m_strLog.Format("Btm Vision Done"); m_nBtmInspectLoop.Takt_Save(7, m_nBtmInspectCase, m_strLog);
		break;

	}


	// 7. (Error : 4900)
	if (m_nBtmInspectLoop.Over_LoopTime()) 
	{		
		g_objCommon.Show_Error(4900 + m_nBtmInspectCase);
		return FALSE;
	}
	return TRUE;
}

// 8. (Error : 5200)
BOOL CSequenceMain::MarkUnitRun()
{
	BOOL	bInspectFail = FALSE;

	static int nMarkXPos = 0, nMarkYPos = 0, nLensNo = 0;
	static double	dMarkUnitX, dMarkUnitY, dMarkUnitZ = 0.0;
	static DWORD	dwTick = 0;
		

	switch(m_nMarkUnitCase)
	{
	case 0:
		m_nMarkUnitLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);	
		return TRUE;
	case 1:
		if(!gData.bIndexDone[eMainIndex::Mark] && !Check_IndexEmpty(eMainIndex::Mark))
		{
			m_nMarkUnitCase++; m_nMarkUnitLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			m_strLog.Format("Marking Start"); m_nMarkUnitLoop.Takt_Save(8, m_nMarkUnitCase, m_strLog);
		}
		else if(!gData.bIndexDone[eMainIndex::Mark] && Check_IndexEmpty(eMainIndex::Mark))
		{
			gData.bIndexDone[eMainIndex::Mark] = TRUE;
			m_nMarkUnitCase = 0; m_nMarkUnitLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);	
			m_strLog.Format("Marking Done"); m_nMarkUnitLoop.Takt_Save(5, m_nMarkUnitCase, m_strLog);
		}	
		return TRUE;
	case 2:
		if(g_objCommon.Check_Position(AX_MARK_UNIT_Z, eMark_Z::Ready))
		{
			if(m_pEquipData->bUseMark)
			{
				//Init_TopZig();
				dwTick = GetTickCount();
				nMarkXPos = 1; nMarkYPos = 1;
				nLensNo = 1;
				m_nMarkUnitCase = 2; m_nMarkUnitLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
				m_strLog.Format("Marking Use"); m_nMarkUnitLoop.Takt_Save(8, m_nMarkUnitCase, m_strLog);
			}
			else
			{
				m_nMarkUnitCase = 15; m_nMarkUnitLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
				m_strLog.Format("Marking Skip"); m_nMarkUnitLoop.Takt_Save(8, m_nMarkUnitCase, m_strLog);
			}
		}
		break;
	case 3:
		if(Select_MarkScanPos(nMarkXPos, nMarkYPos))
		{
			int nIdx = (nMarkYPos - 1) * gData.nZigX + nMarkXPos;
			dMarkUnitY = m_pMoveData->dMarkUnitY[eMark_Y::MarkStart] + (m_pEquipData->dZigPitchY * (nMarkYPos - 1));
			dMarkUnitX = m_pMoveData->dMarkUnitX[eMark_X::MarkStart] + (m_pEquipData->dZigPitchX * (nMarkXPos - 1));
			dMarkUnitZ = m_pMoveData->dMarkUnitZ[eMark_Z::MarkStart];

			g_objAJinAXL.Move_Absolute(AX_MARK_UNIT_Y, dMarkUnitY);
			g_objAJinAXL.Move_Absolute(AX_MARK_UNIT_X, dMarkUnitX);
			g_objAJinAXL.Move_Absolute(AX_MARK_UNIT_Z, dMarkUnitZ);

			nLensNo = (gData.nZigY - nMarkYPos) * gData.nZigX + nMarkXPos;	// Tray 하단부터 모듈 적재한다.
			m_nMarkUnitCase++; m_nMarkUnitLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		else
		{
			m_nMarkUnitCase = 15; m_nMarkUnitLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;

	case 4:
		if (g_objAJinAXL.Is_MoveDone(AX_MARK_UNIT_Y, dMarkUnitY) &&
			g_objAJinAXL.Is_MoveDone(AX_MARK_UNIT_X, dMarkUnitX) &&
			g_objAJinAXL.Is_MoveDone(AX_MARK_UNIT_Z, dMarkUnitZ))
		{
			m_nMarkUnitCase++; m_nMarkUnitLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}		
		break;
	case 6:
		if (!m_pEquipData->bUseMark)
		{
			g_objCommon.Move_Position(AX_MARK_UNIT_Z, eMark_Z::Ready);
			if (gData.InfoMainIndex[eMainIndex::Mark][nMarkYPos-1][nMarkXPos-1] == 9)
				gData.InfoMainIndex[eMainIndex::Mark][nMarkYPos-1][nMarkXPos-1] = eLensState::Marked;	//Scan Done

			m_nMarkUnitCase = 15; m_nMarkUnitLoop.Set_LoopTime(gData.nTime[LoopTime::Scan]);
		} 
		else
		{
			bInspectFail = FALSE;
			if(!Check_InspectDone(gData.sZigIDMainIndex[eMainIndex::Mark], gData.nMZNo[eMainIndex::Mark], gData.nSlotNoMainIndex[eMainIndex::Mark], nLensNo, dwTick)) 
			{
				bInspectFail = TRUE;
				break;
			}
			if(bInspectFail) break; //Not Complete

			g_objCommon.Move_Position(AX_MARK_UNIT_Z, eMark_Z::MarkDown);
			m_nMarkUnitCase++; m_nMarkUnitLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}		
	case 7:
		if(g_objCommon.Check_Position(AX_MARK_UNIT_Z, eMark_Z::MarkDown))
		{
			g_objCommon.Move_Position(AX_MARK_UNIT_Z, eMark_Z::Ready);
			m_nMarkUnitCase = 2; m_nMarkUnitLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}		
		break;	
case 15:
		gData.bIndexDone[eMainIndex::Mark] = TRUE;
		m_nMarkUnitCase = 0; m_nMarkUnitLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		m_strLog.Format("Marking Done"); m_nMarkUnitLoop.Takt_Save(8, m_nMarkUnitCase, m_strLog);
		break;

	}
	
	// 8. (Error : 5200)
	if (m_nMarkUnitLoop.Over_LoopTime()) 
	{		
		g_objCommon.Show_Error(5200 + m_nMarkUnitCase);
		return FALSE;
	}
	return TRUE;
}

// 9. (Error : 5500)
BOOL CSequenceMain::MainIndexRun()
{	
	switch(m_nMainIndexCase)
	{
	case 0:
		m_nIndexTLoop.Set_LoopTime(5000);
		return TRUE;
	case 1:		
		m_nMainIndexCase++; m_nIndexTLoop.Set_LoopTime(5000);
		m_strLog.Format("MainIdex Start"); m_nIndexTLoop.Takt_Save(9, m_nMainIndexCase, m_strLog);
		break;
	case 2:
		g_objCommon.Set_IndexLoadAlignOut();
	 	m_nMainIndexCase++; m_nIndexTLoop.Set_LoopTime(5000);
		m_strLog.Format("Load Align Out"); m_nIndexTLoop.Takt_Save(9, m_nMainIndexCase, m_strLog);
		break;
	case 3:
		if(g_objCommon.Get_IndexLoadAlignOut())
		{
			m_nMainIndexCase++; m_nIndexTLoop.Set_LoopTime(5000);
			m_strLog.Format("In or Out Branch"); m_nIndexTLoop.Takt_Save(9, m_nMainIndexCase, m_strLog);
		}
		break;
	case 4:
		if(Check_IndexEmpty(-1) && !Check_CtZigInMZ(eMZ::Load) && Check_FeederEmpty() && Check_ZigPickerEmpty()) return TRUE;
				
		if(!gData.bIndexDone[eMainIndex::Clean]) m_nLensCleanerCase = 1;		
		if(!gData.bIndexDone[eMainIndex::Top]) m_nTopInspectCase = 1;			
		if(!gData.bIndexDone[eMainIndex::Btm]) m_nBtmInspectCase = 1;		
		if(!gData.bIndexDone[eMainIndex::Mark]) m_nMarkUnitCase = 1;
		
		//Unload Check 
		if( m_nMZElevCase == 20 && m_nFeederCase == 0 && m_nZigPickerCase == 0
			&& !Check_IndexEmpty(eMainIndex::Unload) && !gData.bIndexDone[eMainIndex::Unload] ) // 
		{ 
			m_nZigPickerCase = ZigPickBranch::Unload; // ZigPicker 부터 			
			m_strLog.Format("Zig Picker Unload"); m_nIndexTLoop.Takt_Save(9, m_nMainIndexCase, m_strLog);
		}
		else
		{
			gData.bIndexDone[eMainIndex::Unload] = TRUE;
		}
		gData.bIndexDone[eMainIndex::None] = TRUE;
		m_nMainIndexCase ++; m_nIndexTLoop.Set_LoopTime(25000);
		return TRUE;
	case (int) MainIndexBranch::CheckInOut:		
		if(Check_IndexEmpty(eMainIndex::Load) 
			&& m_nMZElevCase == 20 && m_nFeederCase == 0 && m_nZigPickerCase == 0
			&& !gData.bIndexDone[eMainIndex::Load] && Check_CtZigInMZ(eMZ::Load) )// Unload 가 비워지면 다시 Load 
		{			
			m_nFeederCase = FeederBranch::LoadSearch; // Feeder  부터			
			m_strLog.Format("Feeder LoadSearch"); m_nIndexTLoop.Takt_Save(9, m_nMainIndexCase, m_strLog);
		}
		else if(Check_IndexEmpty(eMainIndex::Load) 
			&& m_nMZElevCase == 20 && m_nFeederCase == 0 && m_nZigPickerCase == 0
			&& !gData.bIndexDone[eMainIndex::Load] && Check_CtZigInMZ(eMZ::Ready) )// Unload 가 비워지면 다시 Load 
		{				
			m_nFeederCase = FeederBranch::RdySearch; // Feeder  부터			
			m_strLog.Format("Feeder Ready Search"); m_nIndexTLoop.Takt_Save(9, m_nMainIndexCase, m_strLog);
		}
		else if(Check_IndexEmpty(eMainIndex::Load) &&  !gData.bIndexDone[eMainIndex::Load]
			&& m_nMZElevCase == 20 && m_nFeederCase == 0 && m_nZigPickerCase == 0 && !Check_IndexEmpty(-1))
		{
			gData.bIndexDone[eMainIndex::Load] = TRUE;
			m_nMainIndexCase = 10;
		}
		else if(Check_IndexDone())
		{
			m_nMainIndexCase = 10;			
		}

		if(Check_IndexEmpty(-1) && !Check_CtZigInMZ(eMZ::Load) && Check_CVMZSensors() <= 0 )
		{
			Job_LotEnd();
			//Lot End;
		}
		break;
	case 10:
		
		if(Check_IndexDone()) // && g_objCommon.Get_IndexLoadAlignIn()
		{
			if (Check_IndexEmpty(-1) && m_nMZElevCase == 20 && m_nFeederCase == 0 && m_nZigPickerCase == 0) 
			{ 
				Set_IndexEnd();
				m_nMainIndexCase = 5;

				return TRUE;
			}

			if ( g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready) 
				&& g_objCommon.Get_CleanerOpen()
				&& g_objCommon.Check_Position(AX_TOP_INSPECTOR_Z, eTopInspect_Z::Ready)
				&& g_objCommon.Check_Position(AX_BTM_INSPECTOR_Z, eBtmInspect_Z::Ready)
				&& g_objCommon.Check_Position(AX_MARK_UNIT_Z, eMark_Z::Ready))				 
			{
				g_objAJinAXL.Move_Relative(AX_MAIN_INDEX_R, m_pMoveData->dMainIndexR[eIndex_R::MoveP]);
				m_nMainIndexCase++; m_nIndexTLoop.Set_LoopTime(10000);
			}
		}
		return TRUE;
	case 11:
		if (g_objAJinAXL.Is_MoveDone(AX_MAIN_INDEX_R, m_pMoveData->dMainIndexR[0])) 
		{			
			Set_IndexEnd();
			m_nMainIndexCase = 4; m_nIndexTLoop.Set_LoopTime(5000);
		}
		break;
		// Lot End Home
	case 50:		// Index R Home

		if ((g_objAJinAXL.Get_Position(AX_ZIG_PICKER_Y) <= 200.0 && g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready)) 
			&& g_objCommon.Get_CleanerOpen()
			&& g_objCommon.Check_Position(AX_TOP_INSPECTOR_Z, eTopInspect_Z::Ready)
			&& g_objCommon.Check_Position(AX_BTM_INSPECTOR_Z, eBtmInspect_Z::Ready)
			&& g_objCommon.Check_Position(AX_MARK_UNIT_Z, eMark_Z::Ready))				 
		{
			g_objAJinAXL.Home_Search(AX_MAIN_INDEX_R);
			m_nMainIndexCase++; m_nIndexTLoop.Set_LoopTime(10000);
		}
		break;
	case 51:		// Check R Home Done
		if (g_objAJinAXL.Is_Home(AX_MAIN_INDEX_R)) 
		{
			m_nMainIndexCase = 0;
		}
		break;
	}
	// 9. (Error : 5500)
	if (m_nIndexTLoop.Over_LoopTime()) 
	{		
		g_objCommon.Show_Error(5500 + m_nMainIndexCase);
		return FALSE;
	}
	return TRUE;
}

BOOL CSequenceMain::UnloadConveyorRun()
{
	static int nDetectCnt[5] = {0,0,0,0,0};

	if(gData.bUldMZWait || gData.bElvUnloadWait)
	{
		g_objCommon.Set_UnloadCVStop();
		return TRUE;
	}

	switch(m_nUnloadConveyorCase)
	{
	case 0:
		m_nUnloadConveyorLoop.Set_LoopTime(5000);
		return TRUE;
	case 1:
		if(gData.bDemoMode) m_pDX01->iUldCvMZExist4 = FALSE;
		
		if((m_pDX01->iUldCvMZExist1L || m_pDX01->iUldCvMZExist2 || m_pDX01->iUldCvMZExist3) && !m_pDX01->iUldCvMZExist4 )
		{
			nDetectCnt[0]++;
			if(nDetectCnt[0] > 5)
			{
				nDetectCnt[0] = 0;
				m_nUnloadConveyorCase++; m_nUnloadConveyorLoop.Set_LoopTime(5000);
			}
		}
		else
		{
			nDetectCnt[0] = 0;
		}
		return TRUE;;
	case 2:
		g_objCommon.Set_UnloadCVRunCW();
		m_nUnloadConveyorCase++; m_nUnloadConveyorLoop.Set_LoopTime(5000);
		break;
	case 3:
		m_nUnloadConveyorCase++; m_nUnloadConveyorLoop.Set_LoopTime(5000);
		break;
	case 4:
		if(gData.bDemoMode)
		{
			if(m_pDX01->iUldCvMZExist1L)
			{
				m_pDX01->iUldCvMZExist4 = TRUE; m_pDX01->iUldCvMZExist1L = FALSE;
			}
		}

		if(m_pDX01->iUldCvMZExist4)
		{
			//Info Processing
			gData.sMZIDElevUnload.Empty();

			for(int i = 0; i < 10; i++) gData.sZigIDElevUnload[i].Empty();
			memset( gData.InfoMZUnload, 0x00, sizeof(int)*10*ZIG_X*ZIG_Y);	
			
			g_dlgWork.TransferMZInfo(eMZ::Load, -1); // From Load To Out(-1)
			g_dlgWork.PostMessage(UM_UPDATE_MZ_INFO,eMZ::Unload, NULL);
			

			g_objCommon.Set_LdStopper1Down();
			g_objCommon.Move_Position(AX_MZ_ELEVATOR_Z, eElv_Z::Ready);
			m_nMZElevCase = ElvBranch::Start; // Slide over Check 

			g_objCommon.Set_UnloadCVStop();
			m_nUnloadConveyorCase++; m_nUnloadConveyorLoop.Set_LoopTime(5000);
		}
		else
		{
			m_nUnloadConveyorCase++; m_nUnloadConveyorLoop.Set_LoopTime(5000);
		}
		break;
	case 5:
		if(gData.bDemoMode)
		{
			if(m_pDX01->iUldCvMZExist4)
			{
				m_pDX01->iUldCvMZExist4 = FALSE; 
			}	
		}
	
		m_nUnloadConveyorCase = 1; m_nUnloadConveyorLoop.Set_LoopTime(5000);
		break;	

	}

	// 10. (Error : 5800)
	if (m_nUnloadConveyorLoop.Over_LoopTime()) 
	{		
		g_objCommon.Show_Error(5800 + m_nUnloadConveyorCase);
		return FALSE;
	}
	return TRUE;
}

void CSequenceMain::Begin_MainRunThread()
{
	if (m_nMainIndexCase == 0 )		m_nMainIndexCase = 1;
	if (m_nLoadConveyorCase == 0)	m_nLoadConveyorCase = 1;
	if (m_nUnloadConveyorCase == 0) m_nUnloadConveyorCase = 1;
	/*if (m_nMZElevCase == 0)			m_nMZElevCase = 1;
	if (m_nFeederCase == 0)			m_nFeederCase = 1;
	if (m_nZigPickerCase == 0)		m_nZigPickerCase = 1;
	if (m_nLensCleanerCase == 0)	m_nLensCleanerCase = 1;
	if (m_nTopInspectCase == 0)		m_nTopInspectCase = 1;
	if (m_nBtmInspectCase == 0 )	m_nBtmInspectCase = 1;
	if (m_nMarkUnitCase == 0)			m_nMarkUnitCase = 1;
	if (m_nMainIndexCase == 0 )		m_nMainIndexCase = 1;
	;*/

	if (m_pThreadMainRun) End_MainRunThread();
	m_bThreadMainRun = TRUE;
	m_pThreadMainRun = AfxBeginThread(Thread_MainRun, NULL);
}

void CSequenceMain::End_MainRunThread()
{
	if (m_pThreadMainRun) {
		m_bThreadMainRun = FALSE;
		WaitForSingleObject(m_pThreadMainRun->m_hThread, INFINITE);
	}
}


int CSequenceMain::Check_CVMZSensors()
{
	int nMZCnt = 0;
	
	int nSensingCnt[6] = {0,0,0,0,0,0};

	while (TRUE)
	{
		theApp.DoEvents();
		if (m_pDX00->iLdCVMZExist1R )
		{
			nSensingCnt[0]++;
			if(nSensingCnt[0] > 5)
			{
				nMZCnt++;for(int i = 0; i < 6; i++) nSensingCnt[i] = 0;
				break;
			}			
		}
		else if (m_pDX00->iLdCVMZExist2)
		{
			nSensingCnt[1]++;
			if(nSensingCnt[1] > 5)
			{
				nMZCnt++;for(int i = 0; i < 6; i++) nSensingCnt[i] = 0;
				break;
			}			
		}
		else if (m_pDX00->iLdCVMZExist3 )
		{
			nSensingCnt[2]++;
			if(nSensingCnt[2] > 5)
			{
				nMZCnt++;for(int i = 0; i < 6; i++) nSensingCnt[i] = 0;
				break;
			}			
		}
		else if (m_pDX00->iLdCVMZExist4 )
		{
			nSensingCnt[3]++;
			if(nSensingCnt[3] > 5)
			{
				nMZCnt++;for(int i = 0; i < 6; i++) nSensingCnt[i] = 0;
				break;
			}			
		}
		else if (m_pDX00->iLdCVMZExist5 )
		{
			nSensingCnt[4]++;
			if(nSensingCnt[4] > 5)
			{
				nMZCnt++;for(int i = 0; i < 6; i++) nSensingCnt[i] = 0;
				break;
			}			
		}
		else
		{
			nSensingCnt[5]++;
			if(nSensingCnt[5] < 8) continue;
			for(int i = 0; i < 6; i++) nSensingCnt[i] = 0;
			break;
		}		
	}
	
	return nMZCnt;	
}

BOOL CSequenceMain::Check_IndexDone()
{
	for(int i = 0 ; i < 7; i++)
	{
		//if(!gData.bIndexDone[i] && !Check_IndexEmpty(i))
		if(!gData.bIndexDone[i])
		{
			return FALSE;
		}
	}
	return TRUE;	
}


BOOL CSequenceMain::Check_IndexEmpty(int nPos)
{
	// nPos (0:Load, 1:clean, 2:top, 3:empty, 4:btm, 5:Mark, 6:Unload  -1:All)
	int nS = (nPos == -1 ? 0 : nPos);
	int nE = (nPos == -1 ? 6 : nPos);

	for (int i = nS; i < nE + 1; i++) 
	{
		for (int j = 0; j < ZIG_X; j++) 
		{
			for (int k = 0; k < ZIG_Y; k++) 
			{
				if (gData.InfoMainIndex[i][j][k] > 0) return FALSE;
			}			
		}
	}
	return TRUE;
}

BOOL CSequenceMain::Check_ZigPickerEmpty()
{
	for (int i = 0; i < ZIG_X; i++) 
	{
		for(int j = 0; j < ZIG_Y; j++)
		{
			if (gData.InfoZigPick[i][j] > 0)
			{
				return FALSE;
			}
		}		
	}
	return TRUE;
}

BOOL CSequenceMain::Check_FeederEmpty()
{
	for (int i = 0; i < ZIG_X; i++) 
	{
		for(int j = 0; j < ZIG_Y; j++)
		{
			if (gData.InfoFeeder[i][j] > 0) return FALSE; 
		}		
	}

	for (int i = 0; i < ZIG_X; i++) 
	{
		for(int j = 0; j < ZIG_Y; j++)
		{
			if (gData.InfoRail[i][j] > 0) return FALSE; 
		}		
	}
	return TRUE;
}




void CSequenceMain::Set_IndexEnd()
{
	gData.nSlotNoMainIndex[eMainIndex::Unload] = gData.nSlotNoMainIndex[eMainIndex::Mark];
	gData.nSlotNoMainIndex[eMainIndex::Mark] = gData.nSlotNoMainIndex[eMainIndex::Btm];
	gData.nSlotNoMainIndex[eMainIndex::Btm] = gData.nSlotNoMainIndex[eMainIndex::None];
	gData.nSlotNoMainIndex[eMainIndex::None] = gData.nSlotNoMainIndex[eMainIndex::Top];
	gData.nSlotNoMainIndex[eMainIndex::Top] = gData.nSlotNoMainIndex[eMainIndex::Clean];
	gData.nSlotNoMainIndex[eMainIndex::Clean] = gData.nSlotNoMainIndex[eMainIndex::Load];
	gData.nSlotNoMainIndex[eMainIndex::Load] = 0;
	
	gData.sMZIDMainIdex[eMainIndex::Unload] = gData.sMZIDMainIdex[eMainIndex::Mark];
	gData.sMZIDMainIdex[eMainIndex::Mark] = gData.sMZIDMainIdex[eMainIndex::Btm];
	gData.sMZIDMainIdex[eMainIndex::Btm] = gData.sMZIDMainIdex[eMainIndex::None];
	gData.sMZIDMainIdex[eMainIndex::None] = gData.sMZIDMainIdex[eMainIndex::Top];
	gData.sMZIDMainIdex[eMainIndex::Top] = gData.sMZIDMainIdex[eMainIndex::Clean];
	gData.sMZIDMainIdex[eMainIndex::Clean] = gData.sMZIDMainIdex[eMainIndex::Load];
	gData.sMZIDMainIdex[eMainIndex::Load] = "";

	gData.sZigIDMainIndex[eMainIndex::Unload] = gData.sZigIDMainIndex[eMainIndex::Mark];
	gData.sZigIDMainIndex[eMainIndex::Mark] = gData.sZigIDMainIndex[eMainIndex::Btm];
	gData.sZigIDMainIndex[eMainIndex::Btm] = gData.sZigIDMainIndex[eMainIndex::None];
	gData.sZigIDMainIndex[eMainIndex::None] = gData.sZigIDMainIndex[eMainIndex::Top];
	gData.sZigIDMainIndex[eMainIndex::Top] = gData.sZigIDMainIndex[eMainIndex::Clean];
	gData.sZigIDMainIndex[eMainIndex::Clean] = gData.sZigIDMainIndex[eMainIndex::Load];
	gData.sZigIDMainIndex[eMainIndex::Load] = "";

	memmove(gData.InfoMainIndex[eMainIndex::Unload], gData.InfoMainIndex[eMainIndex::Mark], sizeof(int)*ZIG_X*ZIG_Y);
	memmove(gData.InfoMainIndex[eMainIndex::Mark], gData.InfoMainIndex[eMainIndex::Btm], sizeof(int)*ZIG_X*ZIG_Y);
	memmove(gData.InfoMainIndex[eMainIndex::Btm], gData.InfoMainIndex[eMainIndex::None], sizeof(int)*ZIG_X*ZIG_Y);
	memmove(gData.InfoMainIndex[eMainIndex::None], gData.InfoMainIndex[eMainIndex::Top], sizeof(int)*ZIG_X*ZIG_Y);
	memmove(gData.InfoMainIndex[eMainIndex::Top], gData.InfoMainIndex[eMainIndex::Clean], sizeof(int)*ZIG_X*ZIG_Y);
	memmove(gData.InfoMainIndex[eMainIndex::Clean], gData.InfoMainIndex[eMainIndex::Load], sizeof(int)*ZIG_X*ZIG_Y);
	memset(gData.InfoMainIndex[eMainIndex::Load], 0x00, sizeof(int)*ZIG_X*ZIG_Y);
	
	memset(gData.bIndexDone, 0x00, sizeof(BOOL) * 7);
}

void CSequenceMain::Init_TopZig()
{
	for(int i = 0; i < ZIG_X; i++)
	{
		for(int j = 0; j < ZIG_Y; j++)
		{
			if(gData.InfoMainIndex[eMainIndex::Top][i][j] == eLensState::Init)
			{
				gData.InfoMainIndex[eMainIndex::Top][i][j] = eLensState::TopReady;
			}
		}
	}
}



BOOL CSequenceMain::Select_TopScanPos(int &nTopPosX, int &nTopPosY)
{
	// Module만 Scan

	nTopPosX = nTopPosY = 0;

	//Y 기준 X 증가하면서 찍는 방법 
	//for(int j= (gData.nZigY - 1); j>=0; j--) 
	for(int i= 0; i < gData.nZigX; i++) 
	{
		if (i==1 || i==3 || i==5 || i==7 || i==9 || i==11)
		{
			for(int j = gData.nZigY - 1; j >= 0; j--) 
			{
				if (gData.InfoMainIndex[eMainIndex::Top][i][j] == eLensState::TopReady)  
				{
					
					nTopPosY = j + 1;
					nTopPosX = i + 1;
					
					break;
				}
			}
		}
		else
		{
			for(int j = 0 ; j < gData.nZigY ; j++)
			{
				if (gData.InfoMainIndex[eMainIndex::Top][i][j] == eLensState::TopReady) 
				{
					
					nTopPosY = j + 1;
					nTopPosX = i + 1;
					
					break;
				}
			}
		}
		
		if (nTopPosY > 0) break;
	}

	if (nTopPosX > gData.nZigX) return FALSE;
	if (nTopPosY == 0 || nTopPosX == 0) return FALSE;
	return TRUE;
}


void CSequenceMain::Init_BtmZig()
{
	for(int i = 0; i < ZIG_X; i++)
	{
		for(int j = 0; j < ZIG_Y; j++)
		{
			if(gData.InfoMainIndex[eMainIndex::Btm][i][j] == eLensState::Init
				|| gData.InfoMainIndex[eMainIndex::Btm][i][j] == eLensState::TopDone)
			{
				gData.InfoMainIndex[eMainIndex::Btm][i][j] = eLensState::BtmReady;
			}
		}
	}
}




BOOL CSequenceMain::Select_BtmScanPos(int &nBtmPosX, int &nBtmPosY)
{
	// Module만 Scan

	nBtmPosX = nBtmPosY = 0;

	//Y 기준 X 증가하면서 찍는 방법 
	for(int i= 0; i < gData.nZigX; i++) 
	{
		if (i==1 || i==3 || i==5 || i==7 || i==9 || i==11)
		{
			for(int j = gData.nZigY - 1; j >= 0; j--) 
			{
				if (gData.InfoMainIndex[eMainIndex::Btm][i][j] == eLensState::BtmReady)  
				{
					nBtmPosY = j + 1;
					nBtmPosX = i + 1;
					break;
				}
			}
		}
		else
		{
			for(int j = 0 ; j < gData.nZigY ; j++)
			{
				if (gData.InfoMainIndex[eMainIndex::Btm][i][j] == eLensState::BtmReady) 
				{

					nBtmPosY = j + 1;
					nBtmPosX = i + 1;

					break;
				}
			}
		}

		if (nBtmPosY > 0) break;
	}

	if (nBtmPosX > gData.nZigX) return FALSE;
	if (nBtmPosY == 0 || nBtmPosX == 0) return FALSE;
	return TRUE;
}



BOOL CSequenceMain::Select_MarkScanPos(int &nMarkPosX, int &nMarkPosY)
{
	// Module만 Scan
	return TRUE;
}


BOOL CSequenceMain::Check_InspectDone(const CString& sZigID, int nMZNo, int nTNo, int nLNo, DWORD dwStart)
{
	int nSlot = nTNo - 1;
	int nLens = nLNo - 1;

	if (((gData.byInspectDone[nMZNo][nSlot][nLens] >> 7) & 1) == 1) return TRUE;	// 판정 완료 (2번 판정하지 않기 위해)

	
	BOOL bDone = TRUE;
	if (m_pEquipData->bUseTopVision && ((gData.byInspectDone[nMZNo-1][nSlot][nLens] >> 0) & 1) == 0)
		bDone = FALSE;	// return FALSE;	// Angle
	if (m_pEquipData->bUseBtmVision  && ((gData.byInspectDone[nMZNo-1][nSlot][nLens] >> 1) & 1) == 0) 
		bDone = FALSE;


	DWORD dwTick = GetTickCount();
	if (!bDone) 
	{
		if (m_pEquipData->bUseInspectSkip || ((dwTick - dwStart)  > m_pEquipData->nDelayAdd[delay::InspectionWait]))
		{
			gData.nInspectInfo[nMZNo][nSlot][nLens] = eLensState::NG;
			m_strLog.Format("Judge Time Over, SlotNo(%d), LensNo(%d)", nSlot+1, nLens+1);
			g_objLogFile.Save_HandlerLog(m_strLog);
		}
		else
		{
			return FALSE;
		}

	}


	if (m_pEquipData->bResultTestUse) 
	{
		/*int nRand = g_objCommon.Get_Random(0, 99);
		int nNg1 = m_pEquipData->nResultTestN1;
		int nNg2 = m_pEquipData->nResultTestN2 + nNg1;
		int nNg3 = m_pEquipData->nResultTestN3 + nNg2;
		int nNg4 = m_pEquipData->nResultTestN4 + nNg3;

		int nJudge = (nRand < nNg1 ? 4 : (nRand < nNg2 ? 5 : (nRand < nNg3 ? 6 : (nRand < nNg4 ? 8 : 1))));
		nInfo = gData.nInspectInfo[nPx][nTx][nCx] = nJudge;
		if (nInfo == 9) { nInfo = gData.nInspectInfo[nPx][nTx][nCx] = 1; }
		strLog.Format("ResultTest_Use : %d,%d,%d",nInfo, nTx+1, nCx+1);
		g_objLogFile.Save_TestLog(strLog);*/

	} 
	else
	{
		//if (gData.bCycleStop && !Get_VisionInspectUse()) nInfo = gData.nInspectInfo[nPx][nTx][nCx] = 1;	//Good
		//else if (Get_VisionInspectUse())  nInfo = gData.nInspectInfo[nPx][nTx][nCx];

		//if (nInfo == 9) nInfo = gData.nInspectInfo[nPx][nTx][nCx] = 1;
	}
	
	gData.byInspectDone[nMZNo-1][nSlot][nLens] |= (1 << 7);	// 판정 완료 (2번 판정하지 않기 위해)
	return TRUE;	// All Inspect Done
}
//
//BOOL CSequenceMain::Check_MainIndexInfo(int nNo)
//{
//	if(nNo == -1)
//	{
//		for(int k = 0; k < 7; k++)
//		{
//			for(int i = 0; i < ZIG_X; i++)
//			{
//				for(int j = 0; j < ZIG_Y; j++)
//				{
//					if(gData.InfoMainIndex[nNo][i][j] > 0) return TRUE; 
//				}		
//			}
//		}
//		return FALSE;
//	}
//
//	for(int i = 0; i < ZIG_X; i++)
//	{
//		for(int j = 0; j < ZIG_Y; j++)
//		{
//			if(gData.InfoMainIndex[nNo][i][j] > 0) return TRUE; 
//		}		
//	}
//	return FALSE;
//}

void CSequenceMain::Init_MZSlot(int nSlotNo, int nX, int nY)
{

}

BOOL CSequenceMain::Check_CtZigInMZ(int nPos)
{
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0;  j < ZIG_X; j++)
		{
			for(int k = 0; k < ZIG_Y; k++)
			{
				 if(nPos == eMZ::Load)  if(gData.InfoMZLoad[i][j][k] > 0 )  return TRUE; 
				 if(nPos == eMZ::Ready)  if(gData.InfoMZReady[i][j][k] > 0 )  return TRUE; 
				 if(nPos == eMZ::Unload)  if(gData.InfoMZUnload[i][j][k] > 0 )  return TRUE;
			}
		}		
	}
	return FALSE;
}




int CSequenceMain::Search_ZigSlotNo(int nPos, int nSlot)
{

	for(int j = 0;  j < ZIG_X; j++)
	{
		for(int k = 0; k < ZIG_Y; k++)
		{
			if(nPos == eMZ::Load)  if(gData.InfoMZLoad[nSlot-1][j][k] > 0 )  return nSlot; 
			if(nPos == eMZ::Ready)  if(gData.InfoMZReady[nSlot-1][j][k] > 0 )  return nSlot; 
			if(nPos == eMZ::Unload)  if(gData.InfoMZUnload[nSlot-1][j][k] > 0 )  return nSlot;
		}
	}		

	return -1;
}

BOOL CSequenceMain::CheckCtZigAllReturn()
{
	for(int i = 0; i < 10; i++ )
	{
		if(gData.ZigMap[eMZ::Load][i])
		{
			if(Search_ZigSlotNo(eMZ::Unload, i + 1) < 0)
			{
				return FALSE;
			}
		}					
	}
	return TRUE;
}



BOOL CSequenceMain::Run_Simulation()
{
#ifdef AJIN_BOARD_USE
	return TRUE;
#endif
	Sleep(SIM_WAITTIMES);

	
	if(m_nFeederCase == 34)
	{
		m_pDX01->iFeederZigExist = TRUE;
	}

	if(m_nZigPickerCase == 11)
	{
		m_pDX01->iRailZigExist = TRUE;
	}

	if(m_nZigPickerCase == 26)
	{
		m_pDX01->iZigPickerExist = TRUE;
	}

	if(m_nZigPickerCase == 31)
	{
		m_pDX01->iZigPickerExist = FALSE;
	}

	if(m_nFeederCase == 36)
	{
		m_pDX01->iFeederZigExist = TRUE;
	}

	if(m_nFeederCase == 38)
	{
		m_pDX01->iFeederZigExist = FALSE;
	}

	return TRUE;
}


