#include "StdAfx.h"
#include "SingleLens.h"
#include "SingleLensDlg.h"
#include "SequenceMain.h"

#include "Common.h"
#include "Inspector.h"
#include "LogFile.h"
#include "BarcodeLot_Cognex.h"
#include "MesAgent.h"

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
	
	if (!Check_IndexEmpty(-1)) return TRUE;
	if (Check_CtZigInMZ(eMZ::Load)) return TRUE;
	if (!Check_ZigPickerEmpty()) return TRUE;
	if (!Check_FeederEmpty()) return TRUE;
	//if (Check_CVMZSensors() > 0) return TRUE;

	if(gData.bCycleStop) return FALSE;

	int *pCase = Get_pMainRunCase();
	for (int i = 0; i < AUTO_COUNT; i++) 
	{		
		if(i == AUTO_LD_CONVEYOR && m_nLoadConveyorCase == 1) continue;
		if(i == AUTO_UL_CONVEYOR && m_nUnloadConveyorCase == 1) continue;
		if(i == AUTO_MZ_ELEVATOR && m_nMZElevCase == 20) continue;		
		if(i == AUTO_INDEX_TABLE && m_nMainIndexCase == 5) continue;
		if (*(pCase + i) > 0)
		{
			return TRUE;
		}
	}

	
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
	}
	for(int i = 0; i < 7; i++) gData.sMZID[i] = "";
	for(int i = 0; i < 7; i++) for(int j = 0; j < 10; j++) gData.sZigID[i][j] = "";
	for(int i = 0; i < 7; i++) gData.nMZNo[i];

	gData.nMZCnt = 0;
	for(int i = 0; i < 7; i++) for(int j = 0; j < 10; j++) gData.nLensUseCnt[i][j] = 0;
	gData.nLensMaxCnt = 0;

	memset(gData.InfoMZLoad, 0x00, sizeof(int)*10*ZIG_X*ZIG_Y);
	memset(gData.InfoMZReady, 0x00, sizeof(int)*10*ZIG_X*ZIG_Y);
	memset(gData.InfoFeeder, 0x00, sizeof(int)*ZIG_X*ZIG_Y);
	memset(gData.InfoRail, 0x00, sizeof(int)*ZIG_X*ZIG_Y);
	memset(gData.InfoZigPick, 0x00, sizeof(int)*ZIG_X*ZIG_Y);
	memset(gData.InfoMainIndex, 0x00, sizeof(int)*7*ZIG_X*ZIG_Y);
	memset(gData.InfoMZUnload, 0x00, sizeof(int)*10*ZIG_X*ZIG_Y);

	memset(gData.InfoCtZigLoad, 0x00, sizeof(int)*10);
	memset(gData.InfoCtZigRdy, 0x00, sizeof(int)*10);
	memset(gData.InfoCtZigUnload, 0x00, sizeof(int)*10);

	memset(gData.cJudgeCode, 0x00, sizeof(char)*7*10*ZIG_X*ZIG_Y*2);
	memset(gData.nInspectInfo, 0x00, sizeof(int)*7*10*ZIG_X*ZIG_Y);
	memset(gData.byInspectDone, 0x00, sizeof(BYTE)*7*10*ZIG_X*ZIG_Y);

	memset(gData.bIndexDone, 0x00, sizeof(BOOL) * 7);		


	gData.nTNoPick[0] = 0;
	gData.nTNoPick[1] = 0;

	
	gData.bElvUnloadWait = FALSE;
	gData.bElvSlideOverWait = FALSE;
	gData.bFeederWorkWait = FALSE;
	gData.bLdMZWait = FALSE;
	gData.bUldMZWait = FALSE;
	
	g_dlgWork.TransferMZInfo(eMZ::Load, -1, m_pEquipData->nVisionDir);
	g_dlgWork.TransferMZInfo(eMZ::Ready, -1, m_pEquipData->nVisionDir);
	
	g_dlgWork.PostMessage(UM_UPDATE_MZ_INFO, (int)eMZ::Load, NULL);
	g_dlgWork.PostMessage(UM_UPDATE_MZ_INFO, (int)eMZ::Ready, NULL);
	
	gData.bCycleStop = FALSE;

	if(gData.bAgingMode || gData.bSimulMode)
	{
		m_pDX00->iElvMZExist1 = FALSE;
		m_pDX00->iElvMZExist2 = FALSE;
		m_pDX01->iUldCvMZExist4 = FALSE;
	}	
}

void CSequenceMain::Set_ClearLotData(BOOL bInit, int nLotNo)
{
	
}

void CSequenceMain::Job_LotStart(int nMZNo, int nPos)
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	int nMNo = nMZNo - 1;;

	gLot.sStartTime[nMNo].Format("%04d%02d%02d_%02d%02d%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	gLot.dwLotStart[nMNo] = GetTickCount();
	
	g_objLogFile.Save_EfficiencyLog(0, "Start", 903, "Lot Start");	//Lot Start 
}

void CSequenceMain::Job_LotEnd(int nMZNo)
{
	int nMNo = nMZNo -1 ;

	memset(gData.cJudgeCode[nMNo], 0x00, sizeof(char)*10*ZIG_X*ZIG_Y*2);
	memset(gData.nInspectInfo[nMNo], 0x00, sizeof(int)*10*ZIG_X*ZIG_Y);
	memset(gData.byInspectDone[nMNo], 0x00, sizeof(BYTE)*10*ZIG_X*ZIG_Y);


	SYSTEMTIME time;
	GetLocalTime(&time);
	gLot.dwLotEnd[nMNo] = GetTickCount();
	gLot.sEndTime[nMNo].Format("%04d%02d%02d_%02d%02d%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);

	DWORD dwTime = gLot.dwLotEnd[nMNo] - gLot.dwLotStart[nMNo];
	gLot.dTackTime = dwTime / 1000.0 / gLot.nLensCount[nMNo];

	/*strLog.Format("LotID,%s,Start_Time,%s,End_Time,%s,Time,%d,Tray_Count,%02d,CM_Count,%04d,Tack,%0.7lf",
		gData.sMZID[nMNo], gLot.sStartTime[nMNo], gLot.sEndTime[nMNo], dwTime, gData.nCtZigTotalCnt[nMNo], nCmCnt, gLot.dTackTime);
	g_objLogFile.Save_JobListLog(strLog);
*/
	gUph.dTaktTime = gLot.dTackTime;

	if (time.wHour >= 7 && time.wHour < 19) gUph.nLensCount[0] += gLot.nLensCount[nMNo];
	else gUph.nLensCount[1] += gLot.nLensCount[nMNo];

	int i = (int)time.wHour;
	int j = gUph.nLotCount[i];
	if (j > 49) return;		// 1시간에 LOT 수량 MAX 50개

	gUph.dTakt[i][j] = gLot.dTackTime;
	gUph.nLotCount[i] = j + 1;

	CSingleLensDlg *pMainDlg = (CSingleLensDlg*)AfxGetApp()->GetMainWnd();
	pMainDlg->Set_LotStateTime();
	pMainDlg->Set_CurrentState(STATE_LOTEND);
	
	g_dlgWork.PostMessage(UM_UPDATE_UPH, NULL, NULL);
		
	m_bLotEnd = TRUE;

	g_objLogFile.Save_EfficiencyLog(0, "Stop", 903, "Lot End");	//Lot End
}


///////////////////////////////////////////////////////////////////////////////

UINT CSequenceMain::Thread_UnloadCV(LPVOID lpVoid)
{
	g_objCommon.Set_UnloadCVRunCW();

	DWORD dwTick = GetTickCount();
	while(TRUE)
	{
		theApp.DoEvents();
		if(GetTickCount() - dwTick > 5000)
		{
			g_objCommon.Set_UnloadCVStop();
			break;
		}
	}
	g_objSequenceMain.m_pThreadUnloadCV = NULL;
	return 0;
}



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
	if (g_dlgWork.SearchMZCVInfo() >= 0) return FALSE;
	if (g_dlgWork.SearchMZElevInfo(0) < 0 && g_dlgWork.SearchMZElevInfo(1) < 0 ) return FALSE;

	if(gData.bAgingMode)
	{
		g_dlgWork.InsertMGZTestInfo();
		return FALSE;
	}


	if (gData.bCycleStop) g_dlgWork.PostMessage(UM_RESET_CYCLE_STOP, NULL, NULL);

	gData.bFirstLotStart = FALSE;

	g_objCommon.Set_LoadCVStop();
	g_objCommon.Set_UnloadCVStop();
		
	CSingleLensDlg *pMainDlg = (CSingleLensDlg*)AfxGetApp()->GetMainWnd();
	//pMainDlg->Set_LampFlicker_UldRun(FALSE);
	//pMainDlg->Set_LampFlicker_UldOpen(FALSE);	

	g_dlgWork.PostMessage(UM_UPDATE_MZ_INFO, (WPARAM)0, NULL);	// All Clear
	
	Set_ClearRunData(FALSE);
	Reset_MainRunCase();


	


	m_pThreadUnloadCV = AfxBeginThread(Thread_UnloadCV, NULL);

	g_objMesAgent.Set_EquipState(eEquipState::IDLE);	

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
	static DWORD dwTick = 0;

	if(gData.bLdMZWait )
	{
		g_objCommon.Set_LoadCVStop();
		return TRUE;
	}
	if(gData.bCycleStop || gData.bElvLoadWait || gData.bFeederWorkWait || gData.bElvSlideOverWait || gData.bElvUnloadWait)
	{
		m_nLoadConveyorCase = 0; //eLoadCVBr::Check
		return TRUE;
	}

	if(gData.bAgingMode)	
	{
		if(( g_dlgWork.SearchMZElevInfo(0) > 0 || g_dlgWork.SearchMZElevInfo(1) > 0 ) 
			&& g_dlgWork.SearchMZCVInfo() > 0 
			&& GetTickCount() - dwTick > 5000 )
		{
			dwTick = GetTickCount();
			m_pDX00->iLdCVMZExist5 = TRUE;			
		}

		if(m_pDX00->iLdCVMZExist5)
		{
			m_pDX00->iLdCVMZExist1R = TRUE; m_pDX00->iLdCVMZExist5 = FALSE;
		}
	}

	if(gData.bSimulMode)
	{
		if( GetTickCount() - dwTick > 5000 )
		{
			dwTick = GetTickCount();
			m_pDX00->iLdCVMZExist5 = TRUE;			
		}

		if(m_pDX00->iLdCVMZExist5)
		{
			m_pDX00->iLdCVMZExist1R = TRUE; m_pDX00->iLdCVMZExist5 = FALSE;
		}
	}

	if(m_nLoadConveyorCase == eLoadCVBr::Check && 
		(m_pDX00->iLdCVMZExist1R || m_pDX00->iLdCVMZExist2 || m_pDX00->iLdCVMZExist3 || m_pDX00->iLdCVMZExist4 || m_pDX00->iLdCVMZExist5)
		&& g_dlgWork.SearchMZCVInfo() > 0)
	{
		m_nLoadConveyorCase = 1; m_nLoadConveyorLoop.Set_LoopTime(5000);
	}
	else if(m_nLoadConveyorCase == eLoadCVBr::Check && 
		!m_pDX00->iLdCVMZExist1R && !m_pDX00->iLdCVMZExist2 && !m_pDX00->iLdCVMZExist3 && !m_pDX00->iLdCVMZExist4 && !m_pDX00->iLdCVMZExist5)
	{
		g_objCommon.Set_LoadCVStop();
		return TRUE;
	}

	switch(m_nLoadConveyorCase)
	{
	case eLoadCVBr::Check:
		m_nLoadConveyorLoop.Set_LoopTime(5000);
		return TRUE;
	case 1:		
		g_objCommon.Set_LdStopper1Up();
		m_nLoadConveyorCase++; m_nLoadConveyorLoop.Set_LoopTime(25000);
		break;
	case 2:	
		if(g_objCommon.Get_LdStopper1Up())
		{
			dwTick = GetTickCount();
			if(!m_pDX00->iLdCVMZExist1R )
			{
				g_objCommon.Set_LoadCVRunCW();
				m_nLoadConveyorCase++; m_nLoadConveyorLoop.Set_LoopTime(25000);
			}
			else if(m_pDX00->iLdCVMZExist1R)
			{
				m_nLoadConveyorCase++; m_nLoadConveyorLoop.Set_LoopTime(25000);
			}
		}		
		break;
	case 3:
		if(m_pDX00->iLdCVMZExist1R )
		{
			g_objCommon.Set_LoadCVStop();			
			m_nLoadConveyorCase++; m_nLoadConveyorLoop.Set_LoopTime(5000);
		}		
		else if(GetTickCount() - dwTick > 10000)
		{
			g_objCommon.Set_LoadCVStop();
			m_nLoadConveyorCase = 0; m_nLoadConveyorLoop.Set_LoopTime(5000);
		}
		break;
	case 4:
		m_nLoadConveyorCase++; m_nLoadConveyorLoop.Set_LoopTime(5000);		
		break;
	case 5:
		if(!m_pDX00->iElvMZExist1 || !m_pDX00->iElvMZExist2)
		{
			nDetectCnt[0]++;nDetectCnt[1] = 0; 
			if(nDetectCnt[0] < 5) return TRUE;
						
			g_objCommon.Set_LdStopper1Down();
			g_objCommon.Move_Position(AX_MZ_ELEVATOR_Z, eElv_Z::FromLdCV);
			m_nMZElevCase = ElvBranch::Start; 

			m_nLoadConveyorCase++; m_nLoadConveyorLoop.Set_LoopTime(5000);
		}		
		else if(m_pDX00->iElvMZExist1 && m_pDX00->iElvMZExist2)
		{
			nDetectCnt[1]++; nDetectCnt[0] = 0; 
			if(nDetectCnt[1] < 5) return TRUE;
						
			m_nLoadConveyorCase = 0; m_nLoadConveyorLoop.Set_LoopTime(5000);
		}
		else
		{
			for(int i = 0; i < 5; i++) nDetectCnt[i] = 0;
		}
		return TRUE;
	case 6:
		if(g_objCommon.Get_LdStopper1Down())
		{
			m_nLoadConveyorCase = eLoadCVBr::ElvWait; m_nLoadConveyorLoop.Set_LoopTime(5000);
		}
		break;
	case eLoadCVBr::ElvWait: //wait 
		m_nLoadConveyorLoop.Set_LoopTime(5000);
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
	static int  nMZNo = 0;
	static int  nMZCnt = 0;
	static int	nMZDetectCnt[6] = {0,0,0,0,0,0};
	static DWORD dwTick1 = 0, dwTick2 = 0;
	

	if(gData.bFeederWorkWait) return TRUE;	

	//Suppose MZ on Right of Elev
	switch(m_nMZElevCase)
	{
	case 0:
		m_nMZElevLoop.Set_LoopTime(5000);
		return TRUE;
	case ElvBranch::Start:
		if(g_objCommon.Get_LdStopper1Down() && g_objCommon.Check_Position(AX_MZ_ELEVATOR_Z, eElv_Z::FromLdCV))
		{					
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

				dwTick1 = GetTickCount();

				g_objCommon.Set_ElevLift1Down(); Sleep(5);
				g_objCommon.Set_ElevLift2Down(); Sleep(5);
				g_objCommon.Set_LoadCVRunCW();Sleep(15);
				g_objCommon.Set_ElevCVRunCW();Sleep(15);

				gData.bElvLoadWait = TRUE;	
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

				dwTick1 = GetTickCount();

				g_objCommon.Set_ElevLift1Down(); Sleep(10);
				g_objCommon.Set_ElevLift1Out(); Sleep(10);
				g_objCommon.Set_LoadCVRunCW();Sleep(5); //CW E¸AuCI·A¸e CCWμμ True ·I CØ¾ßCO 
				g_objCommon.Set_ElevCVRunCW();

				gData.bElvLoadWait = TRUE;	
				m_nMZElevCase = ElvBranch::RdyMZ; m_nMZElevLoop.Set_LoopTime(30000);
				m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Load CV CW Start");		
			}				
		}
		else if(m_pDX00->iElvMZExist1 && !m_pDX00->iElvMZExist2)
		{			
			nMZDetectCnt[2]++;
			if(nMZDetectCnt[2] > 5)
			{
				dwTick1 = GetTickCount();

				for(int i = 0; i < 6; i++) nMZDetectCnt[i] = 0;
				gData.bElvSlideOverWait = TRUE;
				m_nLoadConveyorCase = eLoadCVBr::Check;
								
				m_nMZElevCase = ElvBranch::SlideOver; m_nMZElevLoop.Set_LoopTime(30000);
				m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Load CV CW Start");		
			}
				
		}
		else if(m_pDX00->iElvMZExist1 && m_pDX00->iElvMZExist2)
		{			
			nMZDetectCnt[3]++;
			if(nMZDetectCnt[3] > 5)
			{
				dwTick1 = GetTickCount();
				m_nLoadConveyorCase = eLoadCVBr::Check;
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
				

				m_nMZElevCase = 0; m_nMZElevLoop.Set_LoopTime(30000);
				m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Elevator Full");
			}				
		}
		return TRUE;
	case ElvBranch::LoadMZ:	
		if(gData.bAgingMode || gData.bSimulMode)
		{
			if(m_pDX00->iLdCVMZExist1R)
			{
				m_pDX00->iElvMZExist1 = TRUE; m_pDX00->iLdCVMZExist1R = FALSE;
			}
		}
		
		if(m_pEquipData->bUseMES || m_pEquipData->bUseBarcodeMGZ)
		{
			if(m_pDX00->iElvMZExist1)
			{
				m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Elev Exist 1 Detect");	

				g_objCommon.Set_LoadCVStop(); Sleep(5);
				g_objCommon.Set_ElevCVStop(); Sleep(5);
				
			

				m_nMZElevCase = 71; m_nMZElevLoop.Set_LoopTime(gData.nLTime[eLT::CV]);						
			}	
		}
		else
		{
			if(m_pDX00->iElvMZExist1)
			{
				m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Load CV CW Stop & Elev CV CW Start");
				g_objCommon.Set_LoadCVStop(); Sleep(5);
				g_objCommon.Set_LoadCVRunCCW(); Sleep(5);
				g_objCommon.Set_ElevCVRunCW();
				m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(10000);							
			}	
		}
		break;
	case 71:
		if(m_nMZElevLoop.Waiting_Time(500))
		{
			dwTick1 = GetTickCount();
			m_strBarcode.Empty(); g_objBarcodeLot_Cognex.Set_Trigger(eBarcode::MZ,TRUE);
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(10000);		
		}		
		break;
	case 72:
		if(GetTickCount() - dwTick1 < 3000)
		{
			m_strBarcode = g_objBarcodeLot_Cognex.Get_BarcodeLot(eBarcode::MZ);
			if (m_strBarcode != "") 
			{
				gMes.sMGZID[eMZ::Load] = m_strBarcode; gMes.bMGZIDReported = FALSE;
				gMes.nElevPos = eMZ::Load;
				if(m_pEquipData->bUseMES) g_objMesAgent.Set_MGZIDReport(1, gMes.sMGZID[eMZ::Load]);
				m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(10000);
			}			
		}			 
		break;
	case 73:		
		if(gMes.bMGZIDReported || m_pEquipData->bUseBarcodeMGZ)
		{
			g_objCommon.Set_LoadCVStop(); Sleep(5);
			g_objCommon.Set_LoadCVRunCCW(); Sleep(5);
			g_objCommon.Set_ElevCVRunCW();

			gMes.bMGZIDReported = FALSE;
			m_nMZElevCase = 75; m_nMZElevLoop.Set_LoopTime(10000);
		}
		break;
	case 74: //  retry 
		gMes.nElevPos = eMZ::Load;
		g_objMesAgent.Set_MGZIDReport(1, gMes.sMGZID[eMZ::Load]);
		m_nMZElevCase = 73; m_nMZElevLoop.Set_LoopTime(10000);
		break;
	case 75:
		gMes.bPPConfirm = FALSE;		
		if(m_pEquipData->bUseMES) g_objMesAgent.Set_PPSelectedReport(gMes.sHostLotID[eMZ::Load], gMes.sMGZID[eMZ::Load], gMes.sHostRecipe[eMZ::Load]);
		m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(10000);
		break;
	case 76:

		if(gMes.bPPConfirm || m_pEquipData->bUseBarcodeMGZ)
		{
			if(m_pEquipData->bUseMES) g_objMesAgent.Set_PPUploadCompletedReport(gMes.sHostLotID[eMZ::Load], gMes.sMGZID[eMZ::Load], gMes.sHostRecipe[eMZ::Load]);
			m_nMZElevCase = 4; m_nMZElevLoop.Set_LoopTime(10000);
		}
		break;
	case 4:
		if(gData.bAgingMode || gData.bSimulMode)
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
			g_objCommon.Set_ElevLift2Out();
			
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(gData.nLTime[eLT::CV]);
			m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Elev CV CW Stop & Stopper2 Out");
		}
		return TRUE;
	case 5:
		if(g_objCommon.Get_ElevLift2Out() && g_objCommon.Get_ElevLift2Down())
		{
			if(!m_nMZElevLoop.Waiting_Time(1000)) break;
			g_objCommon.Set_ElevLift2Up();						
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(gData.nLTime[eLT::CV]);
			m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Elev Stopper2 Up");
		}
		break;
	case 6:
		if(g_objCommon.Get_ElevLift2Out() && g_objCommon.Get_ElevLift2Up())
		{
			if(!m_nMZElevLoop.Waiting_Time(1000)) break;
			g_objCommon.Set_ElevLift2In();
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(gData.nLTime[eLT::CV]);
			m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Elev Stopper2 In");
		}
		break;
	case 7:
		if(g_objCommon.Get_ElevLift2In() && g_objCommon.Get_ElevLift2Up())
		{
			if(m_pEquipData->bUseMES)
			{
				nMZNo++; if(nMZNo > 3) nMZNo =1;
				g_dlgWork.Init_TempLensMap(eMZ::Load);

				for(int i = 0; i < 10; i++)
				{
					gData.sLotIDElevLoad[i] = gMes.sHostLotID[eMZ::Load];
					gData.sMZIDElevLoad[i] = gData.sMZID[eMZ::Load];
					gData.nMZNoMZLoad[i] = nMZNo;
					gData.sZigIDElevLoad[i] = gData.sZigID[eMZ::Load][i];
					gData.sRecipeElevLoad[i] = gMes.sHostRecipe[eMZ::Load];
				}	
			}
			else
			{
				//Info Processing 
				//Check MZ ID if Exist Move Infomation to Loading MZ UI
				int nFrom = g_dlgWork.SearchMZCVInfo();
				int nTo = g_dlgWork.SearchMZElevInfo(eMZ::Load);

				if(nTo != -1)
				{
					nMZNo++; if(nMZNo > 3) nMZNo =1;
					g_dlgWork.TransferMZInfo(nFrom, eMZ::Load, m_pEquipData->nVisionDir);

					for(int i = 0; i < 10; i++)
					{
						gData.sLotIDElevLoad[i] = gMes.sHostLotID[eMZ::Load];
						gData.sMZIDElevLoad[i] = gData.sMZID[eMZ::Load];
						gData.nMZNoMZLoad[i] = nMZNo;
						gData.sZigIDElevLoad[i] = gData.sZigID[eMZ::Load][i];
						gData.sRecipeElevLoad[i] = gMes.sHostRecipe[eMZ::Load];
					}				
					g_dlgWork.PostMessage(UM_UPDATE_MZ_INFO, (int)eMZ::Load, NULL);	
				}
			}
			Job_LotStart(nMZNo, eMZ::Load);
			if(m_pEquipData->bUseMES) 
			{
				gData.nCtZigTotalCnt[eMZ::Load] = 0;
				gData.nLensTotalCnt[eMZ::Load] = 0;
				g_objMesAgent.Set_LotStartedReport(gMes.sHostLotID[eMZ::Load], gMes.sHostMGZID[eMZ::Load], gMes.sHostRecipe[eMZ::Load]);
				g_objInspector.Set_LotStart(gData.sMZIDElevLoad[gData.nTNoPick[eMZ::Load]-1], nMZNo, gData.nCtZigTotalCnt[eMZ::Load] , gData.nLensTotalCnt[eMZ::Load], gMes.sHostRecipe[eMZ::Load]);
			}
			else
			{
				gLot.nTrayCount[nMZNo-1] = gData.nCtZigTotalCnt[nMZNo-1];
				gLot.nLensCount[nMZNo-1] = gData.nLensTotalCnt[eMZ::Load];
				g_objInspector.Set_LotStart(gData.sMZIDElevLoad[gData.nTNoPick[eMZ::Load]-1], nMZNo, gData.nCtZigTotalCnt[eMZ::Load] , gData.nLensTotalCnt[eMZ::Load], m_pEquipData->sModelName);
			}

			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
			m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Elev Stopper2 In Done");
					
		}
		break;
	case 8:
		if(!g_objInspector.Check_LotReady()) break;
		gData.bElvLoadWait = FALSE;	
		m_nLoadConveyorCase = eLoadCVBr::Check;
		m_nMZElevCase = 20;	m_nMZElevLoop.Set_LoopTime(5000);	
		break;
	case 9:
		g_objInspector.Set_LotStart(gData.sMZIDElevLoad[gData.nTNoPick[eMZ::Load]-1], nMZNo, gData.nCtZigTotalCnt[eMZ::Load] , gData.nLensTotalCnt[eMZ::Load],"Model");
		m_nMZElevCase = 8;	m_nMZElevLoop.Set_LoopTime(5000);	
		break;
	

	case ElvBranch::RdyMZ:
		if(gData.bAgingMode || gData.bSimulMode)
		{
			if(m_pDX00->iLdCVMZExist1R)
			{
				m_pDX00->iElvMZExist1 = TRUE; m_pDX00->iLdCVMZExist1R = FALSE;
			}
		}
		
		if(m_pEquipData->bUseMES || m_pEquipData->bUseBarcodeMGZ)
		{
			if(m_pDX00->iElvMZExist1)
			{
				g_objCommon.Set_ElevCVStop();Sleep(5);
				g_objCommon.Set_LoadCVStop();Sleep(5);
				
				
				g_objCommon.Set_ElevLift1Out();
				m_nMZElevCase = 81; m_nMZElevLoop.Set_LoopTime(10000);
				m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Load CV CW Stop & Elev CV CW Start");
			}
		}
		else
		{
			if(m_pDX00->iElvMZExist1)
			{
				m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Load CV CW Stop & Elev CV CW Start");

				g_objCommon.Set_LoadCVStop(); Sleep(5);
				g_objCommon.Set_LoadCVRunCCW(); Sleep(5);
				g_objCommon.Set_ElevCVStop();
				m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(10000);

			}	
		}
		break;
	case 81:
		if(m_nMZElevLoop.Waiting_Time(500))
		{
			dwTick1 = GetTickCount();
			m_strBarcode.Empty(); g_objBarcodeLot_Cognex.Set_Trigger(eBarcode::MZ,TRUE);
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(10000);
		}		
		break;
	case 82:
		if(GetTickCount() - dwTick1 < 3000)
		{
			m_strBarcode = g_objBarcodeLot_Cognex.Get_BarcodeLot(eBarcode::MZ);
			if (m_strBarcode != "") 
			{
				
			
				gMes.nElevPos = eMZ::Ready;
				gMes.sMGZID[eMZ::Ready] = m_strBarcode; gMes.bMGZIDReported = FALSE;

				gMes.nElevPos = eMZ::Ready;
				if(m_pEquipData->bUseMES)g_objMesAgent.Set_MGZIDReport(1, gMes.sMGZID[eMZ::Ready]);
				m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(10000);
			}			
		}			 
		break;	
	case 83:
		if(gMes.bMGZIDReported || m_pEquipData->bUseBarcodeMGZ)
		{
			g_objCommon.Set_ElevCVStop(); Sleep(5);
			g_objCommon.Set_LoadCVRunCCW(); Sleep(5);
			gMes.bMGZIDReported = FALSE;
			m_nMZElevCase = 85; m_nMZElevLoop.Set_LoopTime(10000);
		}
		break;
	case 84: //  retry
		gMes.nElevPos = eMZ::Ready;
		if(m_pEquipData->bUseMES) g_objMesAgent.Set_MGZIDReport(1, gMes.sMGZID[eMZ::Ready]);
		m_nMZElevCase = 83; m_nMZElevLoop.Set_LoopTime(10000);
		break;
	case 85:
		gMes.bPPConfirm = FALSE;		
		if(m_pEquipData->bUseMES) g_objMesAgent.Set_PPSelectedReport(gMes.sHostLotID[eMZ::Ready], gMes.sMGZID[eMZ::Ready], gMes.sHostRecipe[eMZ::Ready]);
		m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(10000);
		break;
	case 86:
		if(gMes.bPPConfirm || m_pEquipData->bUseBarcodeMGZ)
		{
			if(m_pEquipData->bUseMES) g_objMesAgent.Set_PPUploadCompletedReport(gMes.sHostLotID[eMZ::Ready], gMes.sMGZID[eMZ::Ready], gMes.sHostRecipe[eMZ::Ready]);
			m_nMZElevCase = 12; m_nMZElevLoop.Set_LoopTime(10000);
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
			if(m_pEquipData->bUseMES)
			{
				nMZNo++;if(nMZNo > 3) nMZNo =1;
				g_dlgWork.Init_TempLensMap(eMZ::Ready);
				for(int i = 0; i < 10; i++)
				{
					gData.sLotIDElevRdy[i] = gMes.sHostLotID[eMZ::Ready];
					gData.sMZIDElevReady[i] = gData.sMZID[eMZ::Ready];
					gData.sRecipeElevReady[i] = gMes.sHostRecipe[eMZ::Ready];
					gData.nMZNoMZRdy[i] = nMZNo;
					gData.sZigIDElevReady[i] = gData.sZigID[eMZ::Ready][i];
				}			
			}
			else
			{
				//Info Processing 
				//Check MZ ID if Exist Move Infomation to Loading MZ UI
				int nFrom = g_dlgWork.SearchMZCVInfo();
				int nTo = g_dlgWork.SearchMZElevInfo(eMZ::Ready);

				if(nTo != -1)
				{
					nMZNo++;if(nMZNo > 3) nMZNo =1;
					g_dlgWork.TransferMZInfo(nFrom, eMZ::Ready, m_pEquipData->nVisionDir);

					for(int i = 0; i < 10; i++)
					{
						gData.sLotIDElevRdy[i] = gData.sMZID[eMZ::Ready];
						gData.sMZIDElevReady[i] = gData.sMZID[eMZ::Ready];
						gData.sRecipeElevReady[i] = gMes.sHostRecipe[eMZ::Ready];
						gData.nMZNoMZRdy[i] = nMZNo;
						gData.sZigIDElevReady[i] = gData.sZigID[eMZ::Ready][i];
					}				
					g_dlgWork.PostMessage(UM_UPDATE_MZ_INFO, (int)eMZ::Ready, NULL);
				}
			}

			Job_LotStart(nMZNo, eMZ::Ready);

			if(m_pEquipData->bUseMES) 
			{					
				gData.nCtZigTotalCnt[eMZ::Ready] = 0;
				gData.nLensTotalCnt[eMZ::Ready] = 0;
				g_objMesAgent.Set_LotStartedReport(gMes.sHostLotID[eMZ::Ready], gMes.sHostMGZID[eMZ::Ready], gMes.sHostRecipe[eMZ::Ready]);
				g_objInspector.Set_LotStart(gData.sMZIDElevReady[gData.nTNoPick[eMZ::Ready] - 1], nMZNo, gData.nCtZigTotalCnt[eMZ::Ready] , gData.nLensTotalCnt[eMZ::Ready],gMes.sHostRecipe[eMZ::Ready]);
			}
			else
			{
				gLot.nTrayCount[nMZNo-1] = gData.nCtZigTotalCnt[nMZNo-1];
				gLot.nLensCount[nMZNo-1] = gData.nLensTotalCnt[eMZ::Ready];
				g_objInspector.Set_LotStart(gData.sMZIDElevReady[gData.nTNoPick[eMZ::Ready] - 1], nMZNo, gData.nCtZigTotalCnt[eMZ::Ready] , gData.nLensTotalCnt[eMZ::Ready], m_pEquipData->sModelName);
			}			

			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
			m_nMZElevLoop.Takt_Save(2, m_nMZElevCase, "Elev Stopper2 In Done");

		}
		break;
	case 16:
		if(!g_objInspector.Check_LotReady()) break;
		gData.bElvLoadWait = FALSE;
		m_nLoadConveyorCase = eLoadCVBr::Check;
		m_nMZElevCase = 20;	m_nMZElevLoop.Set_LoopTime(5000);	
		break;
	case 17:
		g_objInspector.Set_LotStart(gData.sMZIDElevReady[gData.nTNoPick[eMZ::Ready] - 1], nMZNo, gData.nCtZigTotalCnt[eMZ::Ready] , gData.nLensTotalCnt[eMZ::Ready],gMes.sHostRecipe[eMZ::Ready]);
		m_nMZElevCase = 16;	m_nMZElevLoop.Set_LoopTime(5000);	
		break;


	case 20: // working 
		//If additional M/Z added from operator with UI, case can be changed 
		return TRUE;

	case ElvBranch::Unload:
		{
			nMZCnt = 0;
			g_objCommon.Move_Position(AX_MZ_ELEVATOR_Z, eElv_Z::ToUldCV);
			m_nMZElevCase++;m_nMZElevLoop.Set_LoopTime(25000);
		}			
		break;
	case 32:		
		if(gData.bAgingMode || gData.bSimulMode)
		{
			m_pDX01->iUldCvMZExist1L = FALSE;
			m_pDX01->iUldCvMZExist2 = FALSE;
			m_pDX01->iUldCvMZExist3 = FALSE;
			m_pDX01->iUldCvMZExist4 = FALSE;
		}
		if(!g_objCommon.Check_Position(AX_MZ_ELEVATOR_Z, eElv_Z::ToUldCV)) break; 
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
		if(nMZCnt >= 4) //If it's full, wait until one becomes available.
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
		if(gData.bAgingMode || gData.bSimulMode)
		{
			if(m_pDX00->iElvMZExist2 )
			{
				gData.bElvUnloadWait = TRUE;
				g_objCommon.Set_ElevLift2Down();

				m_nMZElevCase++;m_nMZElevLoop.Set_LoopTime(5000);
			}
		}
		else
		{
			if(m_pDX00->iElvMZExist2 && g_objCommon.Get_ElevLift2Up() && g_objCommon.Get_ElevLift2In())
			{
				gData.bElvUnloadWait = TRUE;
				g_objCommon.Set_ElevLift2Down();

				m_nMZElevCase++;m_nMZElevLoop.Set_LoopTime(5000);
			}
		}		
		break;
	case 35:
		m_nMZElevCase++;m_nMZElevLoop.Set_LoopTime(5000);
		break;
	case 36:
		if(g_objCommon.Get_ElevLift2Down())
		{
			g_objCommon.Set_ElevLift2Out();
			m_nMZElevCase++;m_nMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 37:
		m_nMZElevCase++;m_nMZElevLoop.Set_LoopTime(5000);
		break;
	case 38:
		if(g_objCommon.Get_ElevLift2Out())
		{
			Job_LotEnd(Find_UnloadMZNo());
			g_objInspector.Set_LotEnd(gData.sMZIDElevUnload, Find_UnloadMZNo());
			g_objMesAgent.Set_MGZIDReport(2, gData.sMZIDElevUnload);

			g_dlgWork.TransferMZInfo(eMZ::Load, -1, m_pEquipData->nVisionDir); // From Load To Out(-1)
			//Info Processing
			gData.sLotIDElevUnload.Empty();
			gData.sMZIDElevUnload.Empty();
			
			for(int i = 0; i < 10; i++) gData.sRecipeElevUnload[i].Empty();
			for(int i = 0; i < 10; i++) gData.sZigIDElevUnload[i].Empty();
			memset( gData.InfoMZUnload, 0x00, sizeof(int)*10*ZIG_X*ZIG_Y);

			g_dlgWork.PostMessage(UM_UPDATE_MZ_INFO,eMZ::Unload, NULL);

			g_objCommon.Set_ElevCVRunCW();
			Sleep(5);
			g_objCommon.Set_UnloadCVRunCW();

			m_nMZElevCase++;m_nMZElevLoop.Set_LoopTime(gData.nLTime[eLT::CV]);
		}
		break;
	case 39:
		if(gData.bAgingMode || gData.bSimulMode)
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
									
			m_nUnloadConveyorCase = eUnloadCVBr::start; //Unload CV Start 
			m_nMZElevCase = ElvBranch::SlideOver; //Check Slide Over
			m_nMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case ElvBranch::SlideOver:		
		if(m_pDX00->iElvMZExist1)
		{
			nMZDetectCnt[0]++; nMZDetectCnt[1] = 0; 
			if(nMZDetectCnt[0] < 5) return TRUE;

			g_objCommon.Set_ElevLift1Out();
			m_nMZElevCase++;m_nMZElevLoop.Set_LoopTime(5000);
		}
		else if(!m_pDX00->iElvMZExist1)
		{
			nMZDetectCnt[1]++; nMZDetectCnt[0] = 0;
			if(nMZDetectCnt[1] < 5) return TRUE;

			m_nMZElevCase = 20; m_nMZElevLoop.Set_LoopTime(5000);
		}	
		return TRUE;
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
			&& g_objCommon.Get_ElevLift2Down() && g_objCommon.Get_ElevLift2Out())
		{
			g_objCommon.Set_ElevCVRunCW();
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(25000);
		}	
		break; 
	case 56:
		m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(25000);
		break;
	case 57:
		if(gData.bAgingMode || gData.bSimulMode)
		{
			if(m_pDX00->iElvMZExist1)
			{
				m_pDX00->iElvMZExist2 = TRUE; m_pDX00->iElvMZExist1 = FALSE;
			}
		}

		if(!m_pDX00->iElvMZExist1 && m_pDX00->iElvMZExist2)
		{
			g_objCommon.Set_ElevCVStop();
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(25000);
		}		
		break;
	case 58:
		m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(25000);
		break;
	case 59:
		g_objCommon.Set_ElevLift2Up();
		m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(25000);
		break;
	case 60:
		if(g_objCommon.Get_ElevLift2Up())
		{
			if (!m_nMZElevLoop.Waiting_Time(200)) break;			
			g_objCommon.Set_ElevLift2In();
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(gData.nLTime[eLT::CV]);
		}		
		break;
	case 61:
		if(g_objCommon.Get_ElevLift2In())
		{
			if (!m_nMZElevLoop.Waiting_Time(200)) break;

			//Info Processing 
			//Check MZ ID if Exist Move Infomation to Loading MZ UI
			int nFrom = g_dlgWork.SearchMZElevInfo(eMZ::Ready);
			int nTo = g_dlgWork.SearchMZElevInfo(eMZ::Load);

			if(nTo != -1)
			{
				g_dlgWork.TransferMZInfo(eMZ::Ready, eMZ::Load, m_pEquipData->nVisionDir);
				gData.sLotIDElevLoad[gData.nTNoPick[eMZ::Load]-1] = gData.sLotIDElevRdy[gData.nTNoPick[eMZ::Ready]-1]; gData.sLotIDElevRdy[gData.nTNoPick[eMZ::Ready]-1].Empty();
				gData.sMZIDElevLoad[gData.nTNoPick[eMZ::Load]-1] = gData.sMZIDElevReady[gData.nTNoPick[eMZ::Ready]-1]; 	gData.sMZIDElevReady[gData.nTNoPick[eMZ::Ready]-1].Empty();
				gData.sRecipeElevLoad[gData.nTNoPick[eMZ::Load]-1] = gData.sRecipeElevReady[gData.nTNoPick[eMZ::Ready]-1]; 	gData.sRecipeElevReady[gData.nTNoPick[eMZ::Ready]-1].Empty();
				for(int i = 0; i < 10; i++)
				{
					gData.nMZNoMZLoad[i] = gData.nMZNoMZRdy[i]; gData.nMZNoMZRdy[i] = 0;

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
	static double dPosZ, dPosY = 0.0;
	static DWORD dwTick = 0;
	static int	nMZDetectCnt[6] = {0,0,0,0,0,0}; 
	
	
	if( gData.bElvSlideOverWait || gData.bElvLoadWait || gData.bElvUnloadWait) return TRUE;
	
	switch(m_nFeederCase)
	{
	case 0:
		m_nFeederLoop.Set_LoopTime(5000);
		return TRUE;

	case (int) eFeederBr::LoadSearch:	
		if(gData.bElvLoadWait || gData.bElvSlideOverWait || gData.bElvUnloadWait) return TRUE;
		m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		
		return TRUE;
	case 2:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready) || g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::MZLoad)  )
		{
			gData.bFeederWorkWait = TRUE; // load Start

			dPosZ = m_pMoveData->dMZElevZ[eElv_Z::Down] + m_pEquipData->dElevPitchZ * (gData.nTNoPick[eMZ::Load] - 1);
			g_objAJinAXL.Move_Absolute(AX_MZ_ELEVATOR_Z, dPosZ);

			g_objCommon.Move_Position(AX_ZIG_FEEDER_X, eFeeder_X::MZLoad);

			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Elev Z pitch Move, SlotNo : %d", gData.nTNoPick); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}		
		break;
	case 3:
		if(g_objAJinAXL.Is_MoveDone(AX_MZ_ELEVATOR_Z, dPosZ) && g_objCommon.Check_Position(AX_ZIG_FEEDER_X, eFeeder_X::MZLoad))
		{						
			g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::MZLoad);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("FeederUnit X Move (MZ2), %d"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 4:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::MZLoad))
		{
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(65000);
			m_strLog.Format("Feeder Y Move (Zig Exist) "); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		
		break;
	case 5:
		if(gData.bAgingMode || gData.bSimulMode)
		{
			m_pDX01->iFeederZigExist = TRUE;
		}

		if(m_pDX01->iFeederZigExist)
		{
			nMZDetectCnt[0]++;
			nMZDetectCnt[1] = 0;

			if(nMZDetectCnt[0] > 5)
			{
				nMZDetectCnt[0] = 0; nMZDetectCnt[1] = 0;

				if(m_pEquipData->bUseMES)
				{
					m_nFeederCase = 10; m_nFeederLoop.Set_LoopTime(5000);
				}
				else
				{
					int nExist = -1;
					nExist = g_dlgWork.CheckZigExistInMZ(0, gData.nTNoPick[eMZ::Load]);

					if(nExist == gData.nTNoPick[eMZ::Load])					
					{							
						m_nFeederCase = 10; m_nFeederLoop.Set_LoopTime(5000);
						m_strLog.Format("Feeder Y Move (Grip Zig)"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
					}
				}
				
			}
		}
		else
		{
			nMZDetectCnt[1]++;
			nMZDetectCnt[0] = 0;

			if(nMZDetectCnt[1] > 5)
			{
				nMZDetectCnt[0] = 0; nMZDetectCnt[1] = 0;
				m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			}
		}
		break;
	case 6:
		gData.nTNoPick[eMZ::Load]++;
		if(gData.nTNoPick[eMZ::Load] > 10)
		{
			gData.nTNoPick[eMZ::Load] = 1;
			m_nFeederCase = 0; m_nFeederLoop.Set_LoopTime(5000);
			break;
		}

		dPosY = m_pMoveData->dFeederY[eFeeder_Y::MZLoad] - 100;
		g_objAJinAXL.Move_Absolute(AX_ZIG_FEEDER_Y, dPosY);
		m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		break;
	case 7:
		if(g_objAJinAXL.Is_MoveDone(AX_ZIG_FEEDER_Y, dPosY))
		{
			dPosZ = m_pMoveData->dMZElevZ[eElv_Z::Down] + m_pEquipData->dElevPitchZ * (gData.nTNoPick[eMZ::Load] - 1);
			g_objAJinAXL.Move_Absolute(AX_MZ_ELEVATOR_Z, dPosZ);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 8:
		if(g_objAJinAXL.Is_MoveDone(AX_MZ_ELEVATOR_Z, dPosZ))
		{
			g_objCommon.Move_Position(AX_ZIG_FEEDER_X, eFeeder_X::MZLoad);
			g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::MZLoad);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;

	case 9:		
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_X, eFeeder_X::MZLoad) && g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::MZLoad))
		{			
			m_nFeederCase = 5; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;

	case 10:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::MZLoad))
		{
			g_objCommon.Set_FeederClose();
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
			g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::TrayOpen);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Feeder Y Move (PickUp)"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 12:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::TrayOpen))
		{
			gData.bFeederWorkWait = FALSE;
			//Info Processing 		
			gData.sLotIDFeeder = gData.sLotIDElevLoad[gData.nTNoPick[eMZ::Load]-1]; gData.sLotIDElevLoad[gData.nTNoPick[eMZ::Load]-1].Empty();
			gData.sMZIDFeeder = gData.sMZIDElevLoad[gData.nTNoPick[eMZ::Load]-1]; gData.sMZIDElevLoad[gData.nTNoPick[eMZ::Load]-1].Empty();
			gData.sZigIDFeeder = gData.sZigIDElevLoad[gData.nTNoPick[eMZ::Load] -1]; gData.sZigIDElevLoad[gData.nTNoPick[eMZ::Load] -1].Empty();
			gData.sRecipeFeeder = gData.sRecipeElevLoad[gData.nTNoPick[eMZ::Load] -1]; gData.sRecipeElevLoad[gData.nTNoPick[eMZ::Load] -1].Empty();
			
			gData.nSlotNoFeeder = gData.nTNoPick[eMZ::Load]; 
			
			gData.nMZNoFeeder = gData.nMZNoMZLoad[gData.nTNoPick[eMZ::Load] -1];
			gData.nMZNoMZLoad[gData.nTNoPick[eMZ::Load] -1] = 0;
			
			memcpy(gData.InfoFeeder, gData.InfoMZLoad[gData.nTNoPick[eMZ::Load] -1], sizeof(int)*ZIG_X*ZIG_Y );
			memset(gData.InfoMZLoad[gData.nTNoPick[eMZ::Load] -1], 0x00, sizeof(int)*ZIG_X*ZIG_Y );
			
			g_dlgWork.PostMessage(UM_UPDATE_MZ_INFO,eMZ::Load, NULL);

			//g_objCommon.Move_Position(AX_ZIG_FEEDER_X, eFeeder_X::TrayGrip);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Feeder X Move (PickUp)"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 13:
		//if(g_objCommon.Check_Position(AX_ZIG_FEEDER_X, eFeeder_X::TrayGrip))
		{
			g_objCommon.Set_FeederOpen();

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
		if(gData.bAgingMode || gData.bSimulMode) m_pDX01->iRailZigExist  = TRUE;

		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready) && m_pDX01->iRailZigExist)
		{
			g_objCommon.Set_RailAlignIn();

			if(m_pEquipData->bUseMES || m_pEquipData->bUseBarcodeCtZig)
			{
				m_nFeederCase = 71; m_nFeederLoop.Set_LoopTime(5000);
			}
			else
			{				
				m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			}			
			m_strLog.Format("Zig Picker load Start "); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 71:
		if(g_objCommon.Get_RailAlignIn() && g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready))
		{
			g_objCommon.Move_Position(AX_ZIG_FEEDER_X, eFeeder_X::Barcode);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 72:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_X, eFeeder_X::Barcode))
		{
			if(!m_nFeederLoop.Waiting_Time(300)) break;
			dwTick = GetTickCount();
			g_objBarcodeLot_Cognex.Set_Trigger(eBarcode::CtZig, TRUE);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 73:
		if(GetTickCount() - dwTick < 5000)
		{			
			m_strBarcode.Empty(); m_strBarcode = g_objBarcodeLot_Cognex.Get_BarcodeLot(eBarcode::CtZig);
			if(m_strBarcode != "")
			{
				gData.sZigIDFeeder = m_strBarcode;
				m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			}
		}
		break;
	case 74:
		if(m_pEquipData->bUseMES)
		{
			gMes.bTrayIDConfirm = FALSE; //Load : 1
			if(m_pEquipData->bUseMES) g_objMesAgent.Set_TrayIDReport(1, m_strBarcode); 
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		else m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		break;
	case 75:
		if(m_pEquipData->bUseMES && gMes.bTrayIDConfirm)
		{
			gMes.bTrayIDConfirm = FALSE; //Load : 1
			g_dlgWork.init_LensMap();
			gData.sZigIDFeeder = m_strBarcode;
			g_objCommon.Move_Position(AX_ZIG_FEEDER_X, eFeeder_X::TrayGrip);
			m_nFeederCase = 16; m_nFeederLoop.Set_LoopTime(5000);
		}
		else if(m_pEquipData->bUseBarcodeCtZig)
		{
			gMes.bTrayIDConfirm = FALSE; //Load : 1
			g_objCommon.Move_Position(AX_ZIG_FEEDER_X, eFeeder_X::TrayGrip);
			m_nFeederCase = 16; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 16:
		if(g_objAJinAXL.Is_Done(AX_ZIG_FEEDER_X) && g_objCommon.Get_RailAlignIn() )
		{
			g_objCommon.Move_Position(AX_ZIG_FEEDER_X, eFeeder_X::TrayGrip);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}		
		break;
	case 17:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_X, eFeeder_X::TrayGrip) )
		{
			if(!m_nFeederLoop.Waiting_Time(300)) break;
			g_objCommon.Set_RailAlignOut();
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 18:
		if(g_objCommon.Get_RailAlignOut())
		{	
			//Info Processing 
			gData.sLotIDRail = gData.sLotIDFeeder; gData.sLotIDFeeder.Empty();
			gData.sMZIDRail = gData.sMZIDFeeder; gData.sMZIDFeeder.Empty();
			gData.sZigIDRail = gData.sZigIDFeeder; gData.sZigIDFeeder.Empty();
			gData.sRecipeRail = gData.sRecipeFeeder; gData.sRecipeFeeder.Empty();
			gData.nSlotNoRail = gData.nSlotNoFeeder; gData.nSlotNoFeeder = 0;

			gData.nMZNoRail = gData.nMZNoFeeder; gData.nMZNoFeeder = 0;

			memcpy( gData.InfoRail, gData.InfoFeeder,  sizeof(int)*ZIG_X*ZIG_Y);
			memset( gData.InfoFeeder, 0x00, sizeof(int)*ZIG_X*ZIG_Y);	
			
			if(m_pEquipData->bUseMES) g_objMesAgent.Set_TrayStartedReport(gMes.sHostLotID[eMZ::Load], gMes.sHostTrayID, gMes.sHostRecipe[eMZ::Load]);

			gData.nTNoPick[eMZ::Load]++;
			if(gData.nTNoPick[eMZ::Load] > 10) gData.nTNoPick[eMZ::Load] = 1;
			m_nZigPickerCase = eTrayPickerBr::Load; // Tray Picker load Start 			
			m_nFeederCase = 0; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Zig Picker load Start "); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 20: // Tray Pick working 
		return TRUE;

	case eFeederBr::Unload:
		if(gData.bElvLoadWait || gData.bElvSlideOverWait || gData.bElvUnloadWait ) return TRUE;
		m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		return TRUE;
	case 31:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready) 
			&& g_objCommon.Check_Position(AX_ZIG_FEEDER_X, eFeeder_X::TrayGrip)
			&& g_objCommon.Get_FeederOpen())
		{
			g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::TrayOpen);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Feeder Y Move (To Pick) "); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 32:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::TrayOpen) && g_objCommon.Get_FeederOpen())
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
		if(g_objCommon.Get_FeederClose())
		{
			if(!m_nFeederLoop.Waiting_Time(m_pEquipData->nDelayAdd[eDelay::FeederGrip])) break;
				
			//Info Processing
			gData.sLotIDFeeder = gData.sLotIDRail; gData.sLotIDRail.Empty();
			gData.sMZIDFeeder = gData.sMZIDRail; gData.sMZIDRail.Empty();
			gData.sZigIDFeeder = gData.sZigIDRail; gData.sZigIDRail.Empty();
			gData.sRecipeFeeder = gData.sRecipeRail; gData.sRecipeRail.Empty();
			gData.nSlotNoFeeder = gData.nSlotNoRail; gData.nSlotNoRail = 0;

			gData.nMZNoFeeder = gData.nMZNoRail; gData.nMZNoRail = 0;

			memcpy( gData.InfoFeeder, gData.InfoRail,  sizeof(int)*ZIG_X*ZIG_Y);
			memset( gData.InfoRail, 0x00, sizeof(int)*ZIG_X*ZIG_Y);	
			
			gData.bFeederWorkWait = TRUE; // unload Start 
			
			g_objCommon.Move_Position(AX_ZIG_FEEDER_X, eFeeder_X::MZLoad);

			dPosZ = m_pMoveData->dMZElevZ[eElv_Z::Down] + m_pEquipData->dElevPitchZ * (gData.nSlotNoFeeder - 1);
			
			g_objAJinAXL.Move_Absolute(AX_MZ_ELEVATOR_Z, dPosZ);

			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Rail X Move (Unload)"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 35:
		m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);		
		return TRUE;

	case 36:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_X, eFeeder_X::MZLoad))
		{							
			g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::MZLoad);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Feeder Y Move (Unload)"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);			
		}
		break;
	case 37:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::MZLoad) )
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
			gData.sLotIDElevUnload = gData.sLotIDFeeder; gData.sLotIDFeeder.Empty();
			gData.sMZIDElevUnload = gData.sMZIDFeeder; gData.sMZIDFeeder.Empty();
			gData.sZigIDElevUnload[gData.nSlotNoFeeder - 1] = gData.sZigIDFeeder; gData.sZigIDFeeder.Empty();
			gData.sRecipeElevUnload[gData.nSlotNoFeeder - 1] = gData.sRecipeFeeder; gData.sRecipeFeeder.Empty();
						
			gData.nMZNoMZUnload[gData.nSlotNoFeeder-1] = gData.nMZNoFeeder; gData.nMZNoFeeder = 0;

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
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready))
		{
			gData.bFeederWorkWait = FALSE;

			if(Check_TrayAllReturn())
			{
				m_nMZElevCase = ElvBranch::Unload;
			}
			m_strLog.Format("Back to Branch"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
			m_nFeederCase = 0; m_nFeederLoop.Set_LoopTime(5000);			
		}		
		break;


	case (int) eFeederBr::RdySearch:	
		if(gData.bElvLoadWait || gData.bElvSlideOverWait || gData.bElvUnloadWait) return TRUE;
		m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		return TRUE;
	case 52:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready) || g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::MZReady) )
		{
			dPosZ = m_pMoveData->dMZElevZ[eElv_Z::Down] + m_pEquipData->dElevPitchZ * (gData.nTNoPick[eMZ::Ready] - 1) ;
						
			gData.bFeederWorkWait = TRUE; // load Start
			g_objAJinAXL.Move_Absolute(AX_MZ_ELEVATOR_Z, dPosZ);
			g_objCommon.Move_Position(AX_ZIG_FEEDER_X, eFeeder_X::MZReady);

			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Elev Z pitch Move, SlotNo : %d", gData.nTNoPick); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}		
		break;
	case 53:
		if(g_objAJinAXL.Is_MoveDone(AX_MZ_ELEVATOR_Z, dPosZ) && g_objCommon.Check_Position(AX_ZIG_FEEDER_X, eFeeder_X::MZReady))
		{
			g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::MZReady);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("FeederUnit X Move (MZ2), %d"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 54:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::MZReady))
		{
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Feeder Y Move (Zig Exist) "); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}		
		break;
	case 55:
		//if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::CheckExist))
		{
			int nExist = -1;
			nExist = g_dlgWork.CheckZigExistInMZ(eMZ::Ready, gData.nTNoPick[eMZ::Ready]);

			if( nExist == gData.nTNoPick[eMZ::Ready])
			{				
				g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::MZReady);
				m_nFeederCase = 60; m_nFeederLoop.Set_LoopTime(5000);
				m_strLog.Format("Feeder Y Move (Grip Zig)"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
			}
			else
			{
				//Z Pitch Move 
				//g_objAJinAXL.Move_Relative(AX_MZ_ELEVATOR_Z, -m_pEquipData->dMZPitchRightZ*(1.0)); 

				if(gData.nTNoPick[eMZ::Ready] > 10) 
				{	
					gData.nTNoPick[eMZ::Ready] = 1;
					m_nFeederCase = 0; m_nFeederLoop.Set_LoopTime(5000);
					m_strLog.Format("Elev Z Move to search Finish"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
				}
				else
				{
					//gData.nTNoPick[eMZ::Ready]++;
					m_nFeederCase = eFeederBr::RdySearch; m_nFeederLoop.Set_LoopTime(5000);
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
			g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::TrayOpen);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Feeder Y Move (PickUp)"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 62:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::TrayOpen))
		{
			gData.bFeederWorkWait = FALSE;	
		
			//Info Processing
			gData.sLotIDFeeder = gData.sLotIDElevRdy[gData.nTNoPick[eMZ::Ready]-1]; gData.sLotIDElevRdy[gData.nTNoPick[eMZ::Ready]-1].Empty();
			gData.sMZIDFeeder = gData.sMZIDElevReady[gData.nTNoPick[eMZ::Ready]-1]; gData.sMZIDElevReady[gData.nTNoPick[eMZ::Ready]-1].Empty();
			gData.sZigIDFeeder = gData.sZigIDElevReady[gData.nTNoPick[eMZ::Ready] -1]; gData.sZigIDElevReady[gData.nTNoPick[eMZ::Ready] -1].Empty();
			gData.sRecipeFeeder = gData.sRecipeElevReady[gData.nTNoPick[eMZ::Ready] -1]; gData.sRecipeElevReady[gData.nTNoPick[eMZ::Ready] -1].Empty();
			gData.nSlotNoFeeder = gData.nTNoPick[eMZ::Ready]; 
			
			gData.nMZNoFeeder = gData.nMZNoMZRdy[gData.nTNoPick[eMZ::Ready] -1]; gData.nMZNoMZRdy[gData.nTNoPick[eMZ::Ready] -1] = 0; 
			
			memcpy(gData.InfoFeeder, gData.InfoMZReady[gData.nTNoPick[eMZ::Ready] -1], sizeof(int)*ZIG_X*ZIG_Y );
			memset(gData.InfoMZReady[gData.nTNoPick[eMZ::Ready] -1], 0x00, sizeof(int)*ZIG_X*ZIG_Y );

			g_dlgWork.PostMessage(UM_UPDATE_MZ_INFO,eMZ::Ready, NULL);
						
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			m_strLog.Format("Feeder X Move (PickUp)"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 63:
		//if(g_objCommon.Check_Position(AX_ZIG_FEEDER_X, eFeeder_X::TrayGrip))
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
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(35000);
			m_strLog.Format("Feeder Y Move (Ready)"); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;
	case 65:
		if(gData.bAgingMode || gData.bSimulMode) m_pDX01->iRailZigExist  = TRUE;

		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready) && m_pDX01->iRailZigExist)
		{
			g_objCommon.Set_RailAlignIn();
			if(m_pEquipData->bUseMES || m_pEquipData->bUseBarcodeCtZig)
			{
				m_nFeederCase = 81; m_nFeederLoop.Set_LoopTime(35000);
			}
			else
			{
				m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			}		
			m_strLog.Format("Zig Picker load Start "); m_nFeederLoop.Takt_Save(3, m_nFeederCase, m_strLog);
		}
		break;

	case 81:
		if(g_objCommon.Get_RailAlignIn() && g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready))
		{
			g_objCommon.Move_Position(AX_ZIG_FEEDER_X, eFeeder_X::Barcode);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 82:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_X, eFeeder_X::Barcode))
		{
			if(!m_nFeederLoop.Waiting_Time(300)) break;
			dwTick = GetTickCount();
			g_objBarcodeLot_Cognex.Set_Trigger(eBarcode::CtZig, TRUE);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 83:
		if(GetTickCount() - dwTick < 5000)
		{			
			m_strBarcode.Empty(); m_strBarcode = g_objBarcodeLot_Cognex.Get_BarcodeLot(eBarcode::CtZig);
			if(m_strBarcode != "")
			{
				gData.sZigIDFeeder = m_strBarcode;
				m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			}
		}
		break;
	case 84:
		if(m_pEquipData->bUseMES)
		{			
			gMes.bTrayIDConfirm = FALSE; //Load : 1
			g_objMesAgent.Set_TrayIDReport(1, m_strBarcode); 
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		else m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		break;
	case 85:
		if(m_pEquipData->bUseMES && gMes.bTrayIDConfirm)
		{
			gMes.bTrayIDConfirm = FALSE; //Load : 1
			g_dlgWork.init_LensMap();
			g_objCommon.Move_Position(AX_ZIG_FEEDER_X, eFeeder_X::TrayGrip);
			m_nFeederCase = 66; m_nFeederLoop.Set_LoopTime(5000);
		}
		else if(m_pEquipData->bUseBarcodeCtZig)
		{
			g_objCommon.Move_Position(AX_ZIG_FEEDER_X, eFeeder_X::TrayGrip);
			m_nFeederCase = 66; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 66:
		if(g_objCommon.Get_RailAlignIn())
		{
			g_objCommon.Move_Position(AX_ZIG_FEEDER_X, eFeeder_X::TrayGrip);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 67:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_X, eFeeder_X::TrayGrip) && g_objCommon.Get_RailAlignIn())
		{
			if(!m_nFeederLoop.Waiting_Time(300)) break;
			g_objCommon.Set_RailAlignOut();
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 68:
		if(g_objCommon.Get_RailAlignOut())
		{	
			//Info Processing 
			gData.sLotIDRail = gData.sLotIDFeeder; gData.sLotIDFeeder.Empty();
			gData.sMZIDRail = gData.sMZIDFeeder; gData.sMZIDFeeder.Empty();
			gData.sZigIDRail = gData.sZigIDFeeder; gData.sZigIDFeeder.Empty();
			gData.sRecipeRail = gData.sRecipeFeeder; gData.sRecipeFeeder.Empty();
			gData.nSlotNoRail = gData.nSlotNoFeeder; gData.nSlotNoFeeder = 0;

			gData.nMZNoRail = gData.nMZNoFeeder; gData.nMZNoFeeder = 0;

			if(m_pEquipData->bUseMES) g_objMesAgent.Set_TrayStartedReport(gMes.sHostLotID[eMZ::Ready], gMes.sHostTrayID, gMes.sHostRecipe[eMZ::Ready]);

			memcpy( gData.InfoRail, gData.InfoFeeder,  sizeof(int)*ZIG_X*ZIG_Y);
			memset( gData.InfoFeeder, 0x00, sizeof(int)*ZIG_X*ZIG_Y);	

			gData.nTNoPick[eMZ::Ready]++;
			if(gData.nTNoPick[eMZ::Ready] > 10) gData.nTNoPick[eMZ::Ready] = 1;
			m_nZigPickerCase = eTrayPickerBr::Load; // Tray Picker load Start 			
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
		m_nZigPickerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
		return TRUE;
	case (int) eTrayPickerBr::Load:
			if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready) 
				&& (!m_pDX01->iZigPickerExist || gData.bAgingMode || gData.bSimulMode))
			{
				g_objCommon.Move_Position(AX_ZIG_PICKER_Y, eZigPicker_Y::Load);
				m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
				m_strLog.Format("Zig Picker Y Move (Rail)"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
			}
		
		break;
	case 2:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Y, eZigPicker_Y::Load))
		{
			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::LoadDown);
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("ZigPicker Z Move (Pickup)"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 3:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::LoadDown))
		{
			g_objCommon.Set_TrayPickMasterIn();
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Picker Master In"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 4:
		if(g_objCommon.Get_TrayPickMasterIn())
		{
			if(!m_nFeederLoop.Waiting_Time(m_pEquipData->nDelayAdd[eDelay::TrayPickGrip])) break;
			g_objCommon.Set_TrayPickSlaveIn();
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Picker Slave In"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;	
	case 5:
#ifndef AJINB_BOARD_USE
	m_pDX01->iZigPickerExist = TRUE;
#endif
		if(g_objCommon.Get_TrayPickMasterSlaveIn() && m_pDX01->iZigPickerExist)
		{
			if(!m_nFeederLoop.Waiting_Time(m_pEquipData->nDelayAdd[eDelay::TrayPickGrip])) break;
			//Info Processing
			gData.sLotIDTrayPick = gData.sLotIDRail; gData.sLotIDRail.Empty();
			gData.sMZIDTrayPick = gData.sMZIDRail; gData.sMZIDRail = "";
			gData.sZigIDTrayPick =  gData.sZigIDRail; gData.sZigIDRail = "";
			gData.sRecipeTrayPick =  gData.sRecipeRail; gData.sRecipeRail = "";
			gData.nSlotNoTrayPick = gData.nSlotNoRail; gData.nSlotNoRail = 0;

			gData.nMZNoTrayPicker = gData.nMZNoRail; gData.nMZNoRail = 0;

			memcpy(gData.InfoZigPick, gData.InfoRail, sizeof(int)*ZIG_X*ZIG_Y);
			memset( gData.InfoRail, 0, sizeof(int)*ZIG_X*ZIG_Y);
			
			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready);
			m_nZigPickerCase = 10; m_nZigPickerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Picker Z Move (Ready)"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 10:
		if( m_nFeederCase == 0 ) 
		{
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Feeder Search restart"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}		
		return TRUE;
	case 11:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready) 
			&& (!m_pDX01->iRailZigExist || gData.bAgingMode || gData.bSimulMode))
		{				
			g_objCommon.Move_Position(AX_ZIG_PICKER_Y, eZigPicker_Y::Index);
			g_objCommon.Set_IndexLoadAlignOut();
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Picker Y Move (Index)"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 12:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Y, eZigPicker_Y::Index)
			&& g_objCommon.Get_IndexLoadAlignOut())
		{
			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::IndexLoad);
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Picker Z Move Down"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 13:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::IndexLoad))
		{
			g_objCommon.Set_TrayPickSlaveOut();
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Picker Slave Out"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 14:
		if(g_objCommon.Get_TrayPickSlaveOut())
		{
			if(!m_nFeederLoop.Waiting_Time(m_pEquipData->nDelayAdd[eDelay::TrayPickUnGrip])) break;
			g_objCommon.Set_TrayPickMasterOut();
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Picker Master Out"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 15:
#ifndef AJINB_BOARD_USE
		m_pDX02->iIndexTZigExist = TRUE;
#endif
		if(g_objCommon.Get_TrayPickMasterSlaveOut() && m_pDX02->iIndexTZigExist)
		{
			if(!m_nFeederLoop.Waiting_Time(m_pEquipData->nDelayAdd[eDelay::TrayPickUnGrip])) break;
			//Info Processing 
			gData.sLotIDMainIndex[eMainIndex::Load] = gData.sLotIDTrayPick; gData.sLotIDTrayPick.Empty();
			gData.sMZIDMainIdex[eMainIndex::Load] = gData.sMZIDTrayPick; gData.sMZIDTrayPick = "";
			gData.sZigIDMainIndex[eMainIndex::Load] =  gData.sZigIDTrayPick; gData.sZigIDTrayPick = "";
			gData.sRecipeMainIndex[eMainIndex::Load] =  gData.sRecipeTrayPick; gData.sRecipeTrayPick = "";
			gData.nSlotNoMainIndex[eMainIndex::Load] = gData.nSlotNoTrayPick; gData.nSlotNoTrayPick = 0;

			gData.nMZNoMainIndex[eMainIndex::Load] = gData.nMZNoTrayPicker; gData.nMZNoTrayPicker = 0;

			memcpy(gData.InfoMainIndex[eMainIndex::Load], gData.InfoZigPick, sizeof(int)*ZIG_X*ZIG_Y);
			memset(gData.InfoZigPick, 0x00, sizeof(int)*ZIG_X*ZIG_Y);
			

			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready);
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Picker Z Move (Ready Up)"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 16:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready) && (!m_pDX01->iZigPickerExist || gData.bAgingMode || gData.bSimulMode))
		{
			//Load Done		
			gData.bIndexDone[eMainIndex::Load] = TRUE;
			m_nZigPickerCase = 0; m_nZigPickerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Picker Load Done"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
		//Unload 
	case (int) eTrayPickerBr::Unload:
		m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
		return TRUE;
	case 21:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready) && (!m_pDX01->iZigPickerExist || gData.bAgingMode || gData.bSimulMode))
		{
			g_objCommon.Move_Position(AX_ZIG_PICKER_Y, eZigPicker_Y::Index);
			g_objCommon.Set_IndexLoadAlignOut();
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Picker Y Move (Index)"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 22:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Y, eZigPicker_Y::Index) && g_objCommon.Get_IndexLoadAlignOut())
		{
			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::IndexUnload);
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Picker Z Move (Pick Up)"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 23:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::IndexUnload))
		{
			g_objCommon.Set_TrayPickMasterIn();
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Picker Master In"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 24:
		if(g_objCommon.Get_TrayPickMasterIn())
		{
			if(!m_nFeederLoop.Waiting_Time(m_pEquipData->nDelayAdd[eDelay::TrayPickGrip])) break;
			g_objCommon.Set_TrayPickSlaveIn();
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Picker Slave In"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 25:
		if(g_objCommon.Get_TrayPickMasterSlaveIn())
		{
			if(!m_nFeederLoop.Waiting_Time(m_pEquipData->nDelayAdd[eDelay::TrayPickGrip])) break;
			//Info Processing
			gData.sLotIDTrayPick = gData.sLotIDMainIndex[eMainIndex::Unload]; gData.sLotIDMainIndex[eMainIndex::Unload].Empty();
			gData.sMZIDTrayPick = gData.sMZIDMainIdex[eMainIndex::Unload]; gData.sMZIDMainIdex[eMainIndex::Unload] = "";
			gData.sZigIDTrayPick = gData.sZigIDMainIndex[eMainIndex::Unload]; gData.sZigIDMainIndex[eMainIndex::Unload] = "";
			gData.sRecipeTrayPick = gData.sRecipeMainIndex[eMainIndex::Unload]; gData.sRecipeMainIndex[eMainIndex::Unload] = "";
			gData.nSlotNoTrayPick = gData.nSlotNoMainIndex[eMainIndex::Unload]; gData.nSlotNoMainIndex[eMainIndex::Unload] = 0;

			gData.nMZNoTrayPicker = gData.nMZNoMainIndex[eMainIndex::Unload]; gData.nMZNoMainIndex[eMainIndex::Unload] = 0;

			memcpy(gData.InfoZigPick, gData.InfoMainIndex[eMainIndex::Unload], sizeof(int)*ZIG_X*ZIG_Y);
			memset( gData.InfoMainIndex[eMainIndex::Unload], 0x00, sizeof(int)*ZIG_X*ZIG_Y);

			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready);
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Picker Z Move (Ready)"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 26:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready) && (m_pDX01->iZigPickerExist || gData.bAgingMode || gData.bSimulMode))
		{
			gData.bIndexDone[eMainIndex::Unload] = TRUE; // Index Unload Done 	

			g_objCommon.Move_Position(AX_ZIG_PICKER_Y, eZigPicker_Y::Load);
			g_objCommon.Move_Position(AX_ZIG_FEEDER_X, eFeeder_X::TrayGrip);
			g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready);

			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Picker Y Move (Rail)"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 27:		
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Y, eZigPicker_Y::Load)
			&& g_objCommon.Check_Position(AX_ZIG_FEEDER_X, eFeeder_X::TrayGrip)
			&& g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready))
		{
			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::LoadDown);
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Picker Z Move Pick Down"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 28:		
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::LoadDown))
		{
			g_objCommon.Set_TrayPickSlaveOut(); 
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Picker Slave Out"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 29:
		if(g_objCommon.Get_TrayPickSlaveOut())
		{
			if(!m_nFeederLoop.Waiting_Time(m_pEquipData->nDelayAdd[eDelay::TrayPickUnGrip])) break;
			g_objCommon.Set_TrayPickMasterOut();
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Picker Master Out"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 30:
		if(g_objCommon.Get_TrayPickMasterSlaveOut() )
		{
			if(!m_nFeederLoop.Waiting_Time(m_pEquipData->nDelayAdd[eDelay::TrayPickUnGrip])) break;
			//Info Processing 
			gData.sLotIDRail = gData.sLotIDTrayPick; gData.sLotIDTrayPick.Empty();
			gData.sMZIDRail = gData.sMZIDTrayPick; gData.sMZIDTrayPick.Empty();
			gData.sZigIDRail = gData.sZigIDTrayPick; gData.sZigIDTrayPick.Empty();
			gData.sRecipeRail = gData.sRecipeTrayPick; gData.sRecipeTrayPick.Empty();
			gData.nSlotNoRail = gData.nSlotNoTrayPick; gData.nSlotNoTrayPick = 0;

			gData.nMZNoRail = gData.nMZNoTrayPicker; gData.nMZNoTrayPicker = 0;

			memcpy( gData.InfoRail, gData.InfoZigPick,  sizeof(int)*ZIG_X*ZIG_Y);
			memset( gData.InfoZigPick, 0x00, sizeof(int)*ZIG_X*ZIG_Y);			

			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready);
			m_nZigPickerCase++; m_nZigPickerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Picker Z Move (Ready)"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	case 31:		
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready) && (!m_pDX01->iZigPickerExist || gData.bAgingMode || gData.bSimulMode))
		{			
			m_nFeederCase = (int) eFeederBr::Unload;
					
			m_nZigPickerCase = 0; m_nZigPickerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Feeder and Rail Start (Unload)"); m_nZigPickerLoop.Takt_Save(4, m_nZigPickerCase, m_strLog);
		}
		break;
	

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
	static int nRepeat = 0;

	if(gData.bCycleStop)
	{
		gData.bIndexDone[eMainIndex::Clean] = TRUE;
		return TRUE;
	}
	
	switch(m_nLensCleanerCase)
	{
	case 0:
		nRepeat = 0;
		m_nLensCleanerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
		return TRUE;
	case 1:
		if(!gData.bIndexDone[eMainIndex::Clean] && !Check_IndexEmpty(eMainIndex::Clean))
		{
			m_nLensCleanerCase++;  m_nLensCleanerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Lens Cleanner Start"); m_nLensCleanerLoop.Takt_Save(5, m_nLensCleanerCase, m_strLog);
		}
		else if(!gData.bIndexDone[eMainIndex::Clean] && Check_IndexEmpty(eMainIndex::Clean) )
		{
			gData.bIndexDone[eMainIndex::Clean] = TRUE;
			m_nLensCleanerCase = 0; m_nLensCleanerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);	
			m_strLog.Format("Lens Cleanner Done"); m_nLensCleanerLoop.Takt_Save(5, m_nLensCleanerCase, m_strLog);
		}
		return TRUE;
	case 2:
		g_objCommon.Set_CleanerClose();
		m_nLensCleanerCase++; m_nLensCleanerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
		m_strLog.Format("Lens Cleanner Close"); m_nLensCleanerLoop.Takt_Save(5, m_nLensCleanerCase, m_strLog);
		break;
	case 3:
		if(g_objCommon.Get_CleanerClose())
		{
			g_objCommon.Set_CleanerForward();
			m_nLensCleanerCase++; m_nLensCleanerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Lens Cleanner Forward"); m_nLensCleanerLoop.Takt_Save(5, m_nLensCleanerCase, m_strLog);
		}		
		break;
	case 4:
		if(g_objCommon.Get_CleanerForwardDone())
		{
			g_objCommon.Set_CleanerOpen();
			m_nLensCleanerCase++; m_nLensCleanerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Lens Cleanner Open"); m_nLensCleanerLoop.Takt_Save(5, m_nLensCleanerCase, m_strLog);
		}
		break;
	case 5:
		if(g_objCommon.Get_CleanerOpen())
		{
			g_objCommon.Set_CleanerBackward();
			m_nLensCleanerCase++; m_nLensCleanerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Lens Cleanner Backward"); m_nLensCleanerLoop.Takt_Save(5, m_nLensCleanerCase, m_strLog);
		}
	case 6:
		if(g_objCommon.Get_CleanerBackwardDone())
		{			
			m_nLensCleanerCase++; m_nLensCleanerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);	
			m_strLog.Format("Lens Cleanner Done"); m_nLensCleanerLoop.Takt_Save(5, m_nLensCleanerCase, m_strLog);
		}
		break;
	case 7:
		if(nRepeat >= m_pEquipData->nCleanRepeat)
		{
			nRepeat = 0;
			gData.bIndexDone[eMainIndex::Clean] = TRUE;
			m_nLensCleanerCase = 0; m_nLensCleanerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);	
		}
		else
		{
			nRepeat++;
			m_nLensCleanerCase = 2; m_nLensCleanerLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
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

	static double dTopZ = 0.0;
	static int nLensNo = 0;

	if(gData.bCycleStop)
	{
		gData.bIndexDone[eMainIndex::Top] = TRUE;
		return TRUE;
	}
	
	switch(m_nTopInspectCase)
	{
	case 0:
		m_nTopInspectLoop.Set_LoopTime(5000);
		return TRUE;
	case 1:
		if(!gData.bIndexDone[eMainIndex::Top] && !Check_IndexEmpty(eMainIndex::Top)  )
		{
			m_nTopInspectCase++;
			m_nTopInspectLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Top Vision Start"); m_nTopInspectLoop.Takt_Save(6, m_nTopInspectCase, m_strLog);
		}
		else if(!gData.bIndexDone[eMainIndex::Top] && Check_IndexEmpty(eMainIndex::Top)  )
		{
			gData.bIndexDone[eMainIndex::Top] = TRUE;
			m_nTopInspectCase = 0; m_nTopInspectLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);	
			m_strLog.Format("Top Vision Done"); m_nTopInspectLoop.Takt_Save(5, m_nTopInspectCase, m_strLog);
		}		
		return TRUE;
	case 2:
		if(g_objAJinAXL.Is_Done(AX_TOP_INSPECTOR_Z))
		{
			Init_TopZig();
			nTopXPos = 1; nTopYPos = 1;
			m_nTopInspectCase++; m_nTopInspectLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Top Vision Use"); m_nTopInspectLoop.Takt_Save(6, m_nTopInspectCase, m_strLog);
						
		}
		break;
	case 3:
		if(Select_TopScanPos(nTopXPos, nTopYPos, m_pEquipData->nVisionDir))
		{
			if(m_pEquipData->nVisionDir == eVDir::fixY)
			{
				nLensNo = (gData.nLensCntX * (nTopYPos-1)) + nTopXPos;	
			}
			else if(m_pEquipData->nVisionDir == eVDir::fixX)
			{
				nLensNo = (gData.nLensCntY * (nTopXPos-1)) + nTopYPos;
			}
			//Init at First Vision  
			Init_InspectInfo(gData.nMZNoMainIndex[eMainIndex::Top], gData.nSlotNoMainIndex[eMainIndex::Top], nLensNo);
			
			int nIdx = (nTopYPos - 1) * gData.nLensCntX + nTopXPos;
			dTopUnitY = m_pEquipData->dTopStartY - (m_pEquipData->dZigPitchY * (nTopYPos - 1));
			dTopUnitX = m_pEquipData->dTopStartX + (m_pEquipData->dZigPitchX * (nTopXPos - 1));
			dTopUnitZ = m_pEquipData->dTopStartZ - (m_pEquipData->dTopPeriod/10);//m_pMoveData->dTopInspectorZ[eTopInspect_Z::ScanStart];
			
			g_objAJinAXL.Move_Absolute(AX_TOP_INSPECTOR_Y, dTopUnitY);
			g_objAJinAXL.Move_Absolute(AX_TOP_INSPECTOR_X, dTopUnitX);
			g_objAJinAXL.Move_Absolute(AX_TOP_INSPECTOR_Z, dTopUnitZ);

			m_nTopInspectCase++; m_nTopInspectLoop.Set_LoopTime(gData.nLTime[eLT::Motion]); 
		}
		else
		{
			//Done
			m_nTopInspectCase = 15; m_nTopInspectLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
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
			
				m_nTopInspectCase = 10; m_nTopInspectLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
			} 
			else 
			{
							
				m_nTopInspectCase = (int)eTopBr::VisionWait;
				g_objInspector.Set_LoadComplete("TC", gData.sMZIDMainIdex[eMainIndex::Top], gData.nMZNoMainIndex[eMainIndex::Top]
				, gData.sZigIDMainIndex[eMainIndex::Top], gData.nSlotNoMainIndex[eMainIndex::Top], nLensNo);				
				m_nTopInspectLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);			
			}
		}
		break;
	case (int)eTopBr::VisionWait:
		if (!m_pEquipData->bUseTopVision)
		{
			m_nTopInspectCase = 10; m_nTopInspectLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		}
		/*else
		{
			m_nTopInspectCase = 10; m_nTopInspectLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		}*/
		break;
	case eTopBr::Trigger:		// Move Frist
		if (g_objAJinAXL.Is_Done(AX_TOP_INSPECTOR_Z)) 
		{			
			if(gData.bReload[eVision::TC]) gData.bReload[eVision::TC] = FALSE;
			m_nTopInspectCase++;m_nTopInspectLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
		}
		break;
	case 7:		// Scan Move
		if (g_objAJinAXL.Is_Done(AX_TOP_INSPECTOR_Z)) 
		{
			double dPeriod = m_pEquipData->dTopPeriod;	
			double dTrigS = m_pEquipData->dTopStartZ;				
			double dTrigE = dTrigS + (dPeriod) * (m_pEquipData->nTopCount-1);	// Trigger End
			dTopZ = dTrigE + (dPeriod/10);								// Motion End (가감속)
			double dVelocity = m_pEquipData->dTopVelocity;
			g_objAJinAXL.Start_Scan(eVision::TC, AX_TOP_INSPECTOR_Z, dTopZ, dTrigS, dTrigE, dPeriod, dPeriod/2, dVelocity);
			m_nTopInspectCase++; m_nTopInspectLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
		}
		break;
	case 8:		// Scan End
		if (g_objAJinAXL.Is_MoveDone(AX_TOP_INSPECTOR_Z, dTopZ) && gData.bScanDone[eVision::TC]) 
		{
			g_objLogFile.Save_HandlerLog("Stop Scan");
			g_objAJinAXL.Stop_Scan(AX_TOP_INSPECTOR_Z);
			//gData.InfoMainIndex[eMainIndex::Top][nTopXPos-1][nTopYPos-1] = eLensState::TopDone;	//Scan Done
			//m_nTopInspectCase = eTopBr::VisionWait;//
			m_nTopInspectCase = 10;
			m_nTopInspectLoop.Set_LoopTime(30000);		
			
		}
		break;


	case 21:	// Top1 Z Focus Move
		if (g_objAJinAXL.Is_Done(AX_TOP_INSPECTOR_Z)) 
		{
			g_objAJinAXL.Move_Absolute(AX_TOP_INSPECTOR_Z, m_dTop1Z);
					
			m_nTopInspectCase++; m_nTopInspectLoop.Set_LoopTime(5000);
		}
		break;
	case 22:	// Send Move Complete
		if (g_objAJinAXL.Is_Done(AX_TOP_INSPECTOR_Z)) 
		{			
			CString strLog;
			//g_objInspector.Set_ZMoveComplete(VISION_PC1, "T1");
			m_nTopInspectCase = 5; m_nTopInspectLoop.Set_LoopTime(30000);	// 90AE		
		}
		break;
	

	case 10:
		if(m_pEquipData->nVisionDir == eVDir::fixY)
		{
			nTopXPos++;
			if(nTopXPos > gData.nLensCntX) 
			{
				nTopYPos++; nTopXPos = 1;
			}
		}
		else if(m_pEquipData->nVisionDir == eVDir::fixX)
		{
			nTopYPos++;
			if(nTopYPos > gData.nLensCntY) 
			{
				nTopXPos++; nTopYPos = 1;
			}
		}
		g_dlgWork.PostMessage(UM_UPDATE_VISION_INFO, (int)eVision::TC, NULL);
		m_nTopInspectCase = 3; m_nTopInspectLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		break;	
	case 15:
		g_objCommon.Move_Position(AX_TOP_INSPECTOR_Z, eTopInspect_Z::Ready);
		gData.bIndexDone[eMainIndex::Top] = TRUE;
		m_nTopInspectCase = 0; m_nTopInspectLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
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
	static double dBtmZ;
	if(gData.bCycleStop)
	{
		gData.bIndexDone[eMainIndex::None] = TRUE;
		gData.bIndexDone[eMainIndex::Btm] = TRUE;
		return TRUE;
	}
	
	switch(m_nBtmInspectCase)
	{

	case 0:
		m_nBtmInspectLoop.Set_LoopTime(5000);
		return TRUE;
	case 1:
		if(!gData.bIndexDone[eMainIndex::Btm] && !Check_IndexEmpty(eMainIndex::Btm) )
		{
			m_nBtmInspectCase++;
			m_nBtmInspectLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Btm Vision Start"); m_nBtmInspectLoop.Takt_Save(7, m_nBtmInspectCase, m_strLog);
		}
		else if(!gData.bIndexDone[eMainIndex::Btm] && Check_IndexEmpty(eMainIndex::Btm) )
		{
			gData.bIndexDone[eMainIndex::Btm] = TRUE;
			m_nBtmInspectCase = 0; m_nBtmInspectLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);	
			m_strLog.Format("Btm Vision Done"); m_nBtmInspectLoop.Takt_Save(5, m_nBtmInspectCase, m_strLog);
		}		
		return TRUE;
	case 2:
		if(g_objCommon.Check_Position(AX_BTM_INSPECTOR_Z, eBtmInspect_Z::Ready))
		{
			Init_BtmZig();
			nBtmXPos = 1; nBtmYPos = 1;
			m_nBtmInspectCase++; m_nBtmInspectLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Btm Vision Use"); m_nBtmInspectLoop.Takt_Save(7, m_nBtmInspectCase, m_strLog);

		
		}
		break;
	case 3:
		if(Select_BtmScanPos(nBtmXPos, nBtmYPos, m_pEquipData->nVisionDir))
		{
			int nIdx = (nBtmYPos - 1) * gData.nLensCntX + nBtmXPos;
			dBtmUnitY = m_pEquipData->dBtmStartY - (m_pEquipData->dZigPitchY * (nBtmYPos - 1));
			dBtmUnitX = m_pEquipData->dBtmStartX + (m_pEquipData->dZigPitchX * (nBtmXPos - 1));
			dBtmUnitZ = m_pEquipData->dBtmStartZ- (m_pEquipData->dBtmPeriod/10);//m_pMoveData->dBtmInspectorZ[eTopInspect_Z::ScanStart];

			g_objAJinAXL.Move_Absolute(AX_BTM_INSPECTOR_Y, dBtmUnitY);
			g_objAJinAXL.Move_Absolute(AX_BTM_INSPECTOR_X, dBtmUnitX);
			g_objAJinAXL.Move_Absolute(AX_BTM_INSPECTOR_Z, dBtmUnitZ);

			m_nBtmInspectCase++; m_nBtmInspectLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
		}
		else
		{
			//Done
			m_nBtmInspectCase = 15; m_nBtmInspectLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
		}
		break;
	case 4:
		if (g_objAJinAXL.Is_MoveDone(AX_BTM_INSPECTOR_Y, dBtmUnitY) &&
			g_objAJinAXL.Is_MoveDone(AX_BTM_INSPECTOR_X, dBtmUnitX) &&
			g_objAJinAXL.Is_MoveDone(AX_BTM_INSPECTOR_Z, dBtmUnitZ))
		{

			if (!m_pEquipData->bUseBtmVision)
			{
				if (gData.InfoMainIndex[eMainIndex::Btm][nBtmXPos-1][nBtmYPos-1] == eLensState::BtmReady
					||gData.InfoMainIndex[eMainIndex::Btm][nBtmXPos-1][nBtmYPos-1] == eLensState::TopDone
					||gData.InfoMainIndex[eMainIndex::Btm][nBtmXPos-1][nBtmYPos-1] == eLensState::Init)
					gData.InfoMainIndex[eMainIndex::Btm][nBtmXPos-1][nBtmYPos-1] = eLensState::BtmDone;	//Scan Done
				
				m_nBtmInspectCase = 10; m_nBtmInspectLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
			} 
			else 
			{
				int nLensNo = 0;
				if(m_pEquipData->nVisionDir == eVDir::fixY)
				{
					nLensNo = (gData.nLensCntX * (nBtmYPos-1)) + nBtmXPos;	
				}
				else if(m_pEquipData->nVisionDir == eVDir::fixX)
				{
					nLensNo = (gData.nLensCntY * (nBtmXPos-1)) + nBtmYPos;
				}				
				m_nBtmInspectCase = (int)eBtmBr::VisionWait;
				g_objInspector.Set_LoadComplete("BC", gData.sMZIDMainIdex[eMainIndex::Btm],gData.nMZNoMainIndex[eMainIndex::Btm],
					gData.sZigIDMainIndex[eMainIndex::Btm], gData.nSlotNoMainIndex[eMainIndex::Btm], nLensNo);				
				 m_nBtmInspectLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);			
			}
		}
		break;
	case (int)eBtmBr::VisionWait:
		if (!m_pEquipData->bUseBtmVision)
		{
			m_nBtmInspectCase = 10; m_nBtmInspectLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		}
		break;
	case eBtmBr::Trigger:		// Move Frist
		if (g_objAJinAXL.Is_Done(AX_BTM_INSPECTOR_Z)) 
		{			
			if(gData.bReload[eVision::BC]) gData.bReload[eVision::BC] = FALSE;
			m_nBtmInspectCase++;m_nBtmInspectLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		}
		break;
	case 7:		// Scan Move
		if (g_objAJinAXL.Is_Done(AX_BTM_INSPECTOR_Z)) 
		{
			double dPeriod = m_pEquipData->dBtmPeriod;	// 33mm
			double dTrigS = m_pEquipData->dBtmStartZ;				// Trigger Start
			double dTrigE = dTrigS + dPeriod * (m_pEquipData->nBtmCount - 1) ;	// Trigger End
			dBtmZ = dTrigE + (dPeriod/10);								// Motion End (가감속)
			double dVelocity = m_pEquipData->dBtmVelocity;
			g_objAJinAXL.Start_Scan(eVision::BC, AX_BTM_INSPECTOR_Z, dBtmZ, dTrigS, dTrigE, dPeriod, dPeriod/2, dVelocity);
			m_nBtmInspectCase++; m_nBtmInspectLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		}
		break;
	case 8:		// Scan End
		if (g_objAJinAXL.Is_MoveDone(AX_BTM_INSPECTOR_Z,dBtmZ) && gData.bScanDone[eVision::BC]) 
		{
			g_objLogFile.Save_HandlerLog("Stop Scan");
			g_objAJinAXL.Stop_Scan(AX_BTM_INSPECTOR_Z);

			//gData.InfoMainIndex[eMainIndex::Btm][nBtmXPos-1][nBtmYPos-1] = eLensState::BtmDone;	//Scan Done
			m_nBtmInspectCase = 10;//eBtmBr::VisionWait; 
			m_nBtmInspectLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		}
		break;
	case 21:	// Top1 Z Focus Move
		if (g_objAJinAXL.Is_Done(AX_BTM_INSPECTOR_Z)) 
		{
			g_objAJinAXL.Move_Absolute(AX_BTM_INSPECTOR_Z, m_dTop1Z);
			m_nBtmInspectCase++; m_nBtmInspectLoop.Set_LoopTime(5000);
		}
		break;
	case 22:	// Send Move Complete
		if (g_objAJinAXL.Is_Done(AX_BTM_INSPECTOR_Z)) 
		{			
			CString strLog;
			//g_objInspector.Set_ZMoveComplete(VISION_PC1, "B1");
			m_nBtmInspectCase = (int)eBtmBr::VisionWait; m_nBtmInspectLoop.Set_LoopTime(30000);	// 90AE		
		}
		break;
	case 10:
		if(m_pEquipData->nVisionDir == eVDir::fixY)
		{
			nBtmXPos++;
			if(nBtmXPos > gData.nLensCntX) 
			{
				nBtmYPos++; nBtmXPos = 1;
			}
		}
		else if(m_pEquipData->nVisionDir == eVDir::fixX)
		{
			nBtmYPos++;
			if(nBtmYPos > gData.nLensCntY) 
			{
				nBtmXPos++; nBtmYPos = 1;
			}
		}
		g_dlgWork.PostMessage(UM_UPDATE_VISION_INFO, (int)eVision::BC, NULL);
		m_nBtmInspectCase = 3; m_nBtmInspectLoop.Set_LoopTime(5000);
		break;	
	case 15:
		gData.bIndexDone[eMainIndex::Btm] = TRUE;
		g_objCommon.Move_Position(AX_BTM_INSPECTOR_Z, eBtmInspect_Z::Ready);
		m_nBtmInspectCase = 0; m_nBtmInspectLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
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
	static int		nTempInfo = 0;
		
	if(gData.bCycleStop)
	{
		gData.bIndexDone[eMainIndex::Mark] = TRUE;
		return TRUE;
	}

	switch(m_nMarkUnitCase)
	{
	case 0:
		m_nMarkUnitLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);	
		return TRUE;
	case 1:
		if(!gData.bIndexDone[eMainIndex::Mark] && !Check_IndexEmpty(eMainIndex::Mark))
		{
			m_nMarkUnitCase++; m_nMarkUnitLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Marking Start"); m_nMarkUnitLoop.Takt_Save(8, m_nMarkUnitCase, m_strLog);
		}
		else if(!gData.bIndexDone[eMainIndex::Mark] && Check_IndexEmpty(eMainIndex::Mark))
		{
			gData.bIndexDone[eMainIndex::Mark] = TRUE;
			m_nMarkUnitCase = 0; m_nMarkUnitLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);	
			m_strLog.Format("Marking Done"); m_nMarkUnitLoop.Takt_Save(5, m_nMarkUnitCase, m_strLog);
		}	
		return TRUE;
	case 2:
		if(g_objCommon.Check_Position(AX_MARK_UNIT_Z, eMark_Z::Ready))
		{
			Init_MarkZig();
			m_nMarkUnitCase++; m_nMarkUnitLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Marking Use"); m_nMarkUnitLoop.Takt_Save(8, m_nMarkUnitCase, m_strLog);
		}
		break;
	case 3:
		if(Select_MarkScanPos(nMarkXPos, nMarkYPos, m_pEquipData->nVisionDir))
		{
			if(m_pEquipData->nVisionDir == eVDir::fixY)
			{
				nLensNo = (gData.nLensCntX * (nMarkYPos-1)) + nMarkXPos;	
			}
			else if(m_pEquipData->nVisionDir == eVDir::fixX)
			{
				nLensNo = (gData.nLensCntY * (nMarkXPos-1)) + nMarkYPos;

			}	
			
			int nIdx = (nMarkYPos - 1) * gData.nLensCntX + nMarkXPos;
			dMarkUnitY = m_pMoveData->dMarkUnitY[eMark_Y::MarkStart] - (m_pEquipData->dZigPitchY * (nMarkYPos - 1));
			dMarkUnitX = m_pMoveData->dMarkUnitX[eMark_X::MarkStart] + (m_pEquipData->dZigPitchX * (nMarkXPos - 1));
			dMarkUnitZ = m_pMoveData->dMarkUnitZ[eMark_Z::MarkStart];

			g_objAJinAXL.Move_Absolute(AX_MARK_UNIT_Y, dMarkUnitY);
			g_objAJinAXL.Move_Absolute(AX_MARK_UNIT_X, dMarkUnitX);
			g_objAJinAXL.Move_Absolute(AX_MARK_UNIT_Z, dMarkUnitZ);
						
			m_nMarkUnitCase++; m_nMarkUnitLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
		}
		else
		{
			g_objCommon.Move_Position(AX_MARK_UNIT_Z, eMark_Z::Ready);
			m_nMarkUnitCase = 15; m_nMarkUnitLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
		}
		break;

	case 4:
		if (g_objAJinAXL.Is_MoveDone(AX_MARK_UNIT_Y, dMarkUnitY) &&
			g_objAJinAXL.Is_MoveDone(AX_MARK_UNIT_X, dMarkUnitX) &&
			g_objAJinAXL.Is_Done(AX_MARK_UNIT_Z))
		{
			m_nMarkUnitCase++; m_nMarkUnitLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
		}		
		break;
	case 5:		
	
			/*if (!m_pEquipData->bUseMark)
			{
				g_objCommon.Move_Position(AX_MARK_UNIT_Z, eMark_Z::Ready);


				m_nMarkUnitCase = 15; m_nMarkUnitLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
			} 
			*/
			//else
			//{
				bInspectFail = FALSE;
				nTempInfo = 0;
				if(!Check_InspectDone(gData.sZigIDMainIndex[eMainIndex::Mark], gData.nMZNoMainIndex[eMainIndex::Mark], gData.nSlotNoMainIndex[eMainIndex::Mark], nLensNo, nTempInfo, dwTick)) 
				{
					bInspectFail = TRUE;
					break;
				}
				if(bInspectFail) break; //Not Complete
				if(m_pEquipData->bUseMES) g_objMesAgent.Set_ProductCompletedReport(gData.sLotIDMainIndex[eMainIndex::Mark], gData.sZigIDMainIndex[eMainIndex::Mark], gData.sRecipeMainIndex[eMainIndex::Mark], nLensNo, 
					gData.sJudgeCode[gData.nMZNoMainIndex[eMainIndex::Mark]][gData.nSlotNoMainIndex[eMainIndex::Mark]][nLensNo][eVision::MARKING], gData.sNGCode[gData.nMZNoMainIndex[eMainIndex::Mark]][gData.nSlotNoMainIndex[eMainIndex::Mark]][nLensNo][eVision::MARKING] );
				
				g_objLogFile.Save_TrackingLog(nTempInfo, gData.sZigIDMainIndex[eMainIndex::Mark], gData.nMZNoMainIndex[eMainIndex::Mark], gData.nSlotNoMainIndex[eMainIndex::Mark], nLensNo);
				Write_LotJudge(gData.nMZNoMainIndex[eMainIndex::Mark], gData.nSlotNoMainIndex[eMainIndex::Mark],nLensNo, nTempInfo);
				m_nMarkUnitCase++; m_nMarkUnitLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			//}
		
		break;
	case 6:
		if(nTempInfo == 2 && m_pEquipData->bUseMark)
		{
			gData.InfoMainIndex[eMainIndex::Mark][nMarkXPos-1][nMarkYPos-1] = eLensState::Marked;	//Scan Done
			m_nMarkUnitCase++; m_nMarkUnitLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
		}
		else
		{
			gData.InfoMainIndex[eMainIndex::Mark][nMarkXPos-1][nMarkYPos-1] = eLensState::NotMarked;	//Scan Done
			m_nMarkUnitCase = 10; m_nMarkUnitLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
		}
		break;
	case 7:
		g_objCommon.Move_Position(AX_MARK_UNIT_Z, eMark_Z::MarkDown);
		m_nMarkUnitCase++; m_nMarkUnitLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
		break;
	case 8:
		if(g_objCommon.Check_Position(AX_MARK_UNIT_Z, eMark_Z::MarkDown))
		{
			g_objCommon.Move_Position(AX_MARK_UNIT_Z, eMark_Z::Ready);
			m_nMarkUnitCase = 10; m_nMarkUnitLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
		}		
		break;	
	case 10:		
		g_dlgWork.PostMessage(UM_UPDATE_VISION_INFO, (int)eVision::MARKING, NULL);

		if(m_pEquipData->nVisionDir == eVDir::fixY)
		{
			nMarkXPos++;
			if(nMarkXPos > gData.nLensCntX) 
			{
				nMarkYPos++; nMarkXPos = 1;
			}
		}
		else if(m_pEquipData->nVisionDir == eVDir::fixX)
		{
			nMarkYPos++;
			if(nMarkYPos > gData.nLensCntY) 
			{
				nMarkXPos++; nMarkYPos = 1;
			}
		}
		m_nMarkUnitCase = 3; m_nMarkUnitLoop.Set_LoopTime(5000);
		break;	
	case 15:
		if(g_objCommon.Check_Position(AX_MARK_UNIT_Z, eMark_Z::Ready))
		{
			gData.bIndexDone[eMainIndex::Mark] = TRUE;
			m_nMarkUnitCase = 0; m_nMarkUnitLoop.Set_LoopTime(gData.nLTime[eLT::Motion]);
			m_strLog.Format("Marking Done"); m_nMarkUnitLoop.Takt_Save(8, m_nMarkUnitCase, m_strLog);
		}
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
		//g_objCommon.Set_IndexLoadAlignOut();
	 	m_nMainIndexCase++; m_nIndexTLoop.Set_LoopTime(5000);
		m_strLog.Format("Load Align Out"); m_nIndexTLoop.Takt_Save(9, m_nMainIndexCase, m_strLog);
		break;
	case 3:
		//if(g_objCommon.Get_IndexLoadAlignOut())
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
		gData.bIndexDone[eMainIndex::None] = TRUE;
		m_nMainIndexCase ++; m_nIndexTLoop.Set_LoopTime(25000);
		return TRUE;
	case (int) MainIndexBranch::CheckInOut:	

		if( m_nMZElevCase == 20 && m_nFeederCase == 0 && m_nZigPickerCase == 0 && !Check_IndexEmpty(eMainIndex::Unload) && !gData.bIndexDone[eMainIndex::Unload]) 
		{ 
			m_nZigPickerCase = eTrayPickerBr::Unload; // ZigPicker ºIAI 			
			m_strLog.Format("Zig Picker Unload"); m_nIndexTLoop.Takt_Save(9, m_nMainIndexCase, m_strLog);
		}
		else if(Check_IndexEmpty(eMainIndex::Load) 
			&& m_nMZElevCase == 20 && m_nFeederCase == 0 && m_nZigPickerCase == 0
			&& !gData.bIndexDone[eMainIndex::Load] && Check_CtZigInMZ(eMZ::Load)) // Unload °¡ ºn¿oAo¸e ´U½A Load 
		{			
			m_nFeederCase = eFeederBr::LoadSearch; // Feeder  ºIAI			
			m_strLog.Format("Feeder LoadSearch"); m_nIndexTLoop.Takt_Save(9, m_nMainIndexCase, m_strLog);
		}
		else if(Check_IndexEmpty(eMainIndex::Load) 
			&& m_nMZElevCase == 20 && m_nFeederCase == 0 && m_nZigPickerCase == 0
			&& !gData.bIndexDone[eMainIndex::Load] && Check_CtZigInMZ(eMZ::Ready)) // Unload °¡ ºn¿oAo¸e ´U½A Load 
		{				
			m_nFeederCase = eFeederBr::RdySearch; // Feeder  ºIAI			
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

		//if(Check_IndexEmpty(-1) && !Check_CtZigInMZ(eMZ::Load) && Check_CVMZSensors() <= 0 )
		//{
		//	Job_LotEnd(0);
		//	//Lot End;
		//}
		return TRUE;
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
				g_objCommon.Set_IndexLoadAlignIn();
				m_nMainIndexCase++; m_nIndexTLoop.Set_LoopTime(10000);
			}
			else if(gData.bCycleStop)
			{
				g_objCommon.Set_IndexLoadAlignIn();
				m_nMainIndexCase++; m_nIndexTLoop.Set_LoopTime(10000);
			}
		}
		return TRUE;
	case 11:
		if(g_objCommon.Get_IndexLoadAlignIn())
		{
			g_objAJinAXL.Move_Relative(AX_MAIN_INDEX_R, m_pMoveData->dMainIndexR[eIndex_R::MoveP]);
			m_nMainIndexCase++; m_nIndexTLoop.Set_LoopTime(10000);
		}
		break;
	case 12:
		if (g_objAJinAXL.Is_MoveDone(AX_MAIN_INDEX_R, m_pMoveData->dMainIndexR[eIndex_R::MoveP])) 
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
	static int nMZCntPre = 0, nMZCntPost = 0;
	static int nDetectCnt[6] = {0,0,0,0,0,0};

	static DWORD dwTick;

	if(gData.bUldMZWait || gData.bElvUnloadWait) return TRUE;
	
	switch(m_nUnloadConveyorCase)
	{
	case 0:
		m_nUnloadConveyorLoop.Set_LoopTime(gData.nLTime[eLT::CV]);
		return TRUE;
	case eUnloadCVBr::start:
		if(gData.bAgingMode || gData.bSimulMode) m_pDX01->iUldCvMZExist4 = FALSE;
		
		if(m_pDX01->iUldCvMZExist1L)
		{
			nDetectCnt[0]++;
			if(nDetectCnt[0] > 5){ nMZCntPre++; nDetectCnt[0] = 0; }
		}
		if(m_pDX01->iUldCvMZExist2)
		{
			nDetectCnt[1]++;
			if(nDetectCnt[1] > 5){ nMZCntPre++; nDetectCnt[1] = 0; }
		}
		if(m_pDX01->iUldCvMZExist3)
		{
			nDetectCnt[2]++;
			if(nDetectCnt[2] > 5){ nMZCntPre++; nDetectCnt[2] = 0; }
		}
		if(m_pDX01->iUldCvMZExist4)
		{
			nDetectCnt[3]++;
			if(nDetectCnt[3] > 5){ nMZCntPre++; nDetectCnt[3] = 0; }
		}
		nDetectCnt[5]++;
		if(nDetectCnt[5] > 8)
		{
			for(int i = 0; i < 6; i++) nDetectCnt[i] = 0;
			m_nUnloadConveyorCase++;m_nUnloadConveyorLoop.Set_LoopTime(gData.nLTime[eLT::CV]);
		}		
		return TRUE;
	case 2:
		if(nMZCntPre < 4)
		{
			dwTick = GetTickCount();
			g_objCommon.Set_UnloadCVRunCW();
			m_nUnloadConveyorCase++; m_nUnloadConveyorLoop.Set_LoopTime(gData.nLTime[eLT::CV]);
		}	
		else
		{
			nMZCntPre = 0;
			m_nUnloadConveyorCase = 1; m_nUnloadConveyorLoop.Set_LoopTime(gData.nLTime[eLT::CV]);
		}
		break;
	case 3:
		if(m_pDX01->iUldCvMZExist1L)
		{
			nDetectCnt[0]++;
			if(nDetectCnt[0] > 5){ nMZCntPost++; nDetectCnt[0] = 0; }
		}
		if(m_pDX01->iUldCvMZExist2)
		{
			nDetectCnt[1]++;
			if(nDetectCnt[1] > 5){ nMZCntPost++; nDetectCnt[1] = 0; }
		}
		if(m_pDX01->iUldCvMZExist3)
		{
			nDetectCnt[2]++;
			if(nDetectCnt[2] > 5){ nMZCntPost++; nDetectCnt[2] = 0; }
		}
		if(m_pDX01->iUldCvMZExist4)
		{
			nDetectCnt[3]++;
			if(nDetectCnt[3] > 5){ nMZCntPost++; nDetectCnt[3] = 0; }
		}
		nDetectCnt[5]++;
		if(nDetectCnt[5] > 8)
		{
			for(int i = 0; i < 6; i++) nDetectCnt[i] = 0;
			m_nUnloadConveyorCase++;m_nUnloadConveyorLoop.Set_LoopTime(gData.nLTime[eLT::CV]);
		}				
		break;
	case 4:
		if(gData.bAgingMode || gData.bSimulMode)
		{
			if(m_pDX01->iUldCvMZExist1L)
			{
				m_pDX01->iUldCvMZExist4 = TRUE; m_pDX01->iUldCvMZExist1L = FALSE;
			}
		}

		if(nMZCntPost == nMZCntPre + 1)
		{
			g_objCommon.Set_UnloadCVStop();
			m_nUnloadConveyorCase++; m_nUnloadConveyorLoop.Set_LoopTime(gData.nLTime[eLT::CV]);			
		}
		else if(GetTickCount() - dwTick > 15000 )
		{
		
			nMZCntPost = 0;		
			g_objCommon.Set_UnloadCVStop();
			m_nUnloadConveyorCase = 0; m_nUnloadConveyorLoop.Set_LoopTime(gData.nLTime[eLT::CV]);					
		
		}
		break;
	case 5:
		g_objCommon.Set_LdStopper1Down();
		g_objCommon.Move_Position(AX_MZ_ELEVATOR_Z, eElv_Z::FromLdCV);
		m_nMZElevCase = ElvBranch::Start; // Slide over Check 
		m_nUnloadConveyorCase++; m_nUnloadConveyorLoop.Set_LoopTime(gData.nLTime[eLT::CV]);	
	case 6:
		if(gData.bAgingMode || gData.bSimulMode)
		{
			if(m_pDX01->iUldCvMZExist4)
			{
				m_pDX01->iUldCvMZExist4 = FALSE; 
			}	
		}
		nMZCntPre = 0; nMZCntPost = 0;
		dwTick = GetTickCount();
		m_nUnloadConveyorCase = 0; m_nUnloadConveyorLoop.Set_LoopTime(gData.nLTime[eLT::CV]);
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
	//if (m_nUnloadConveyorCase == 0) m_nUnloadConveyorCase = 1;

	m_nLoadConveyorLoop.Set_LoopTime(5000);
	m_nMZElevLoop.Set_LoopTime(5000);
	m_nFeederLoop.Set_LoopTime(5000);
	m_nZigPickerLoop.Set_LoopTime(5000);
	m_nLensCleanerLoop.Set_LoopTime(5000);
	m_nTopInspectLoop.Set_LoopTime(5000);
	m_nBtmInspectLoop.Set_LoopTime(5000);
	m_nMarkUnitLoop.Set_LoopTime(5000);
	m_nIndexTLoop.Set_LoopTime(5000);
	m_nMarkUnitLoop.Set_LoopTime(5000);



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
	for(int i = 0 ; i < 6; i++)
	{
		//if(!gData.bIndexDone[i] && !Check_IndexEmpty(i))
		if(!gData.bIndexDone[i])
		{
			return FALSE;
		}
	}

	if(!gData.bIndexDone[6] && !Check_IndexEmpty(eMainIndex::Unload)) return FALSE;

	return TRUE;	
}


BOOL CSequenceMain::Check_IndexEmpty(int nPos)
{
	// nPos (0:Load, 1:clean, 2:top, 3:empty, 4:btm, 5:Mark, 6:Unload  -1:All)
	int nS = (nPos == -1 ? 0 : nPos);
	int nE = (nPos == -1 ? 6 : nPos);

	for (int i = nS; i < nE + 1; i++) 
	{
		for (int j = 0; j < gData.nLensCntX; j++) 
		{
			for (int k = 0; k < gData.nLensCntY; k++) 
			{
				if (gData.InfoMainIndex[i][j][k] > 0) return FALSE;
			}			
		}
	}
	return TRUE;
}

BOOL CSequenceMain::Check_ZigPickerEmpty()
{
	for (int i = 0; i < gData.nLensCntX; i++) 
	{
		for(int j = 0; j < gData.nLensCntY; j++)
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
	for (int i = 0; i < gData.nLensCntX; i++) 
	{
		for(int j = 0; j < gData.nLensCntY; j++)
		{
			if (gData.InfoFeeder[i][j] > 0) return FALSE; 
		}		
	}

	for (int i = 0; i < gData.nLensCntX; i++) 
	{
		for(int j = 0; j < gData.nLensCntY; j++)
		{
			if (gData.InfoRail[i][j] > 0) return FALSE; 
		}		
	}
	return TRUE;
}




void CSequenceMain::Set_IndexEnd()
{
	
	gData.sLotIDMainIndex[eMainIndex::Unload] = gData.sLotIDMainIndex[eMainIndex::Mark];
	gData.sLotIDMainIndex[eMainIndex::Mark] = gData.sLotIDMainIndex[eMainIndex::Btm];
	gData.sLotIDMainIndex[eMainIndex::Btm] = gData.sLotIDMainIndex[eMainIndex::None];
	gData.sLotIDMainIndex[eMainIndex::None] = gData.sLotIDMainIndex[eMainIndex::Top];
	gData.sLotIDMainIndex[eMainIndex::Top] = gData.sLotIDMainIndex[eMainIndex::Clean];
	gData.sLotIDMainIndex[eMainIndex::Clean] = gData.sLotIDMainIndex[eMainIndex::Load];
	gData.sLotIDMainIndex[eMainIndex::Load] = "";

	gData.sMZIDMainIdex[eMainIndex::Unload] = gData.sMZIDMainIdex[eMainIndex::Mark];
	gData.sMZIDMainIdex[eMainIndex::Mark] = gData.sMZIDMainIdex[eMainIndex::Btm];
	gData.sMZIDMainIdex[eMainIndex::Btm] = gData.sMZIDMainIdex[eMainIndex::None];
	gData.sMZIDMainIdex[eMainIndex::None] = gData.sMZIDMainIdex[eMainIndex::Top];
	gData.sMZIDMainIdex[eMainIndex::Top] = gData.sMZIDMainIdex[eMainIndex::Clean];
	gData.sMZIDMainIdex[eMainIndex::Clean] = gData.sMZIDMainIdex[eMainIndex::Load];
	gData.sMZIDMainIdex[eMainIndex::Load] = "";

	gData.nMZNoMainIndex[eMainIndex::Unload] = gData.nMZNoMainIndex[eMainIndex::Mark]; 
	gData.nMZNoMainIndex[eMainIndex::Mark] = gData.nMZNoMainIndex[eMainIndex::Btm]; 
	gData.nMZNoMainIndex[eMainIndex::Btm] = gData.nMZNoMainIndex[eMainIndex::None]; 
	gData.nMZNoMainIndex[eMainIndex::None] = gData.nMZNoMainIndex[eMainIndex::Top]; 
	gData.nMZNoMainIndex[eMainIndex::Top] = gData.nMZNoMainIndex[eMainIndex::Clean]; 
	gData.nMZNoMainIndex[eMainIndex::Clean] = gData.nMZNoMainIndex[eMainIndex::Load];
	gData.nMZNoMainIndex[eMainIndex::Load] = 0;

	gData.sZigIDMainIndex[eMainIndex::Unload] = gData.sZigIDMainIndex[eMainIndex::Mark];
	gData.sZigIDMainIndex[eMainIndex::Mark] = gData.sZigIDMainIndex[eMainIndex::Btm];
	gData.sZigIDMainIndex[eMainIndex::Btm] = gData.sZigIDMainIndex[eMainIndex::None];
	gData.sZigIDMainIndex[eMainIndex::None] = gData.sZigIDMainIndex[eMainIndex::Top];
	gData.sZigIDMainIndex[eMainIndex::Top] = gData.sZigIDMainIndex[eMainIndex::Clean];
	gData.sZigIDMainIndex[eMainIndex::Clean] = gData.sZigIDMainIndex[eMainIndex::Load];
	gData.sZigIDMainIndex[eMainIndex::Load] = "";

	gData.sRecipeMainIndex[eMainIndex::Unload] = gData.sRecipeMainIndex[eMainIndex::Mark];
	gData.sRecipeMainIndex[eMainIndex::Mark] = gData.sRecipeMainIndex[eMainIndex::Btm];
	gData.sRecipeMainIndex[eMainIndex::Btm] = gData.sRecipeMainIndex[eMainIndex::None];
	gData.sRecipeMainIndex[eMainIndex::None] = gData.sRecipeMainIndex[eMainIndex::Top];
	gData.sRecipeMainIndex[eMainIndex::Top] = gData.sRecipeMainIndex[eMainIndex::Clean];
	gData.sRecipeMainIndex[eMainIndex::Clean] = gData.sRecipeMainIndex[eMainIndex::Load];
	gData.sRecipeMainIndex[eMainIndex::Load] = "";
	
	gData.nSlotNoMainIndex[eMainIndex::Unload] = gData.nSlotNoMainIndex[eMainIndex::Mark];
	gData.nSlotNoMainIndex[eMainIndex::Mark] = gData.nSlotNoMainIndex[eMainIndex::Btm];
	gData.nSlotNoMainIndex[eMainIndex::Btm] = gData.nSlotNoMainIndex[eMainIndex::None];
	gData.nSlotNoMainIndex[eMainIndex::None] = gData.nSlotNoMainIndex[eMainIndex::Top];
	gData.nSlotNoMainIndex[eMainIndex::Top] = gData.nSlotNoMainIndex[eMainIndex::Clean];
	gData.nSlotNoMainIndex[eMainIndex::Clean] = gData.nSlotNoMainIndex[eMainIndex::Load];
	gData.nSlotNoMainIndex[eMainIndex::Load] = 0;
		
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
	for(int i = 0; i < gData.nLensCntX; i++)
	{
		for(int j = 0; j < gData.nLensCntY; j++)
		{
			if(gData.InfoMainIndex[eMainIndex::Top][i][j] > 0)
			{
				gData.InfoMainIndex[eMainIndex::Top][i][j] = eLensState::TopReady;
			}
		}
	}	
}



BOOL CSequenceMain::Select_TopScanPos(int &nTopPosX, int &nTopPosY, int nDir)
{
	// Module¸¸ Scan

	nTopPosX = nTopPosY = 0;


	if(nDir == eVDir::fixX)
	{
		for(int i= 0; i < gData.nLensCntX; i++) 
		{
			if (i==1 || i==3 || i==5 || i==7 || i==9 || i==11 || i==13 || i==15 || i==17)
			{
				for(int j = gData.nLensCntY - 1; j >= 0; j--) 
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
				for(int j = 0 ; j < gData.nLensCntY ; j++)
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

		if (nTopPosX > gData.nLensCntX) return FALSE;
		if (nTopPosY == 0 || nTopPosX == 0) return FALSE;
	}
	else if(nDir == eVDir::fixY)
	{
		for(int i= 0; i < gData.nLensCntY; i++) 
		{
			if (i==1 || i==3 || i==5 || i==7 || i==9 || i==11 || i==13 || i==15 || i==17)
			{
				for(int j = gData.nLensCntX - 1; j >= 0; j--) 
				{
					if (gData.InfoMainIndex[eMainIndex::Top][j][i] == eLensState::TopReady)  
					{					
						nTopPosY = i + 1;
						nTopPosX = j + 1;					
						break;
					}
				}
			}
			else
			{
				for(int j = 0 ; j < gData.nLensCntX ; j++)
				{
					if (gData.InfoMainIndex[eMainIndex::Top][j][i] == eLensState::TopReady) 
					{					
						nTopPosY = i + 1;
						nTopPosX = j + 1;					
						break;
					}
				}
			}		
			if (nTopPosX > 0) break;
		}

		if (nTopPosY > gData.nLensCntY) return FALSE;
		if (nTopPosY == 0 || nTopPosX == 0) return FALSE;
	}	
	return TRUE;
}


void CSequenceMain::Init_BtmZig()
{	
	for(int i = 0; i < gData.nLensCntX; i++)
	{
		for(int j = 0; j < gData.nLensCntY; j++)
		{
			if(gData.InfoMainIndex[eMainIndex::Btm][i][j] > 0)
			{
				gData.InfoMainIndex[eMainIndex::Btm][i][j] = eLensState::BtmReady;
			}
		}
	}		
}




BOOL CSequenceMain::Select_BtmScanPos(int &nBtmPosX, int &nBtmPosY, int nDir)
{
	// Module¸Scan

	nBtmPosX = nBtmPosY = 0;

	if(nDir == eVDir::fixX)
	{
		for(int i= 0; i < gData.nLensCntX; i++) 
		{
			if (i==1 || i==3 || i==5 || i==7 || i==9 || i==11 || i==13 || i==15 || i==17)
			{
				for(int j = gData.nLensCntY - 1; j >= 0; j--) 
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
				for(int j = 0 ; j < gData.nLensCntY ; j++)
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

		if (nBtmPosX > gData.nLensCntX) return FALSE;
		
	}
	else if(nDir == eVDir::fixY)
	{
		for(int i= 0; i < gData.nLensCntY; i++) 
		{
			if (i==1 || i==3 || i==5 || i==7 || i==9 || i==11 || i==13 || i==15 || i==17)
			{
				for(int j = gData.nLensCntX - 1; j >= 0; j--) 
				{
					if (gData.InfoMainIndex[eMainIndex::Btm][j][i] == eLensState::BtmReady)  
					{
						nBtmPosY = i + 1;
						nBtmPosX = j + 1;
						break;
					}
				}
			}
			else
			{
				for(int j = 0 ; j < gData.nLensCntX ; j++)
				{
					if (gData.InfoMainIndex[eMainIndex::Btm][j][i] == eLensState::BtmReady) 
					{
						nBtmPosY = i + 1;
						nBtmPosX = j + 1;
						break;
					}
				}
			}

			if (nBtmPosX > 0) break;
		}

		if (nBtmPosY > gData.nLensCntY) return FALSE;
	}

	if (nBtmPosY == 0 || nBtmPosX == 0) return FALSE;
	
	return TRUE;
}

void CSequenceMain::Init_MarkZig()
{
	for(int i = 0; i < gData.nLensCntX; i++)
	{
		for(int j = 0; j < gData.nLensCntY; j++)
		{
			if(gData.InfoMainIndex[eMainIndex::Mark][i][j] > 0)
			{
				gData.InfoMainIndex[eMainIndex::Mark][i][j] = eLensState::MarkReady;
			}
		}
	}	
}


BOOL CSequenceMain::Select_MarkScanPos(int &nMarkPosX, int &nMarkPosY, int nDir)
{
	nMarkPosX = nMarkPosY = 0;


	if(nDir == eVDir::fixX)
	{
		for(int i= 0; i < gData.nLensCntX; i++) 
		{
			if (i==1 || i==3 || i==5 || i==7 || i==9 || i==11)
			{
				for(int j = gData.nLensCntY - 1; j >= 0; j--) 
				{
					if (gData.InfoMainIndex[eMainIndex::Mark][i][j] == eLensState::MarkReady)  
					{					
						nMarkPosY = j + 1;
						nMarkPosX = i + 1;					
						break;
					}
				}
			}
			else
			{
				for(int j = 0 ; j < gData.nLensCntY ; j++)
				{
					if (gData.InfoMainIndex[eMainIndex::Mark][i][j] == eLensState::MarkReady) 
					{					
						nMarkPosY = j + 1;
						nMarkPosX = i + 1;					
						break;
					}
				}
			}		
			if (nMarkPosY > 0) break;
		}

		if (nMarkPosX > gData.nLensCntX) return FALSE;
		if (nMarkPosY == 0 || nMarkPosX == 0) return FALSE;
	}
	else if(nDir == eVDir::fixY)
	{
		for(int i= 0; i < gData.nLensCntY; i++) 
		{
			if (i==1 || i==3 || i==5 || i==7 || i==9 || i==11)
			{
				for(int j = gData.nLensCntX - 1; j >= 0; j--) 
				{
					if (gData.InfoMainIndex[eMainIndex::Mark][j][i] == eLensState::MarkReady)  
					{					
						nMarkPosY = i + 1;
						nMarkPosX = j + 1;					
						break;
					}
				}
			}
			else
			{
				for(int j = 0 ; j < gData.nLensCntX ; j++)
				{
					if (gData.InfoMainIndex[eMainIndex::Mark][j][i] == eLensState::MarkReady) 
					{					
						nMarkPosY = i + 1;
						nMarkPosX = j + 1;					
						break;
					}
				}
			}		
			if (nMarkPosX > 0) break;
		}

		if (nMarkPosY > gData.nLensCntY) return FALSE;
		if (nMarkPosY == 0 || nMarkPosX == 0) return FALSE;
	}	
	return TRUE;

}


BOOL CSequenceMain::Check_InspectDone(const CString& sZigID, int nMZNo, int nTNo, int nLNo, int& nInfo, DWORD dwStart)
{
	int nMNo = nMZNo - 1;
	int nSlot = nTNo - 1;
	int nLens = nLNo - 1;

	CString strLog;

	if (((gData.byInspectDone[nMNo][nSlot][nLens] >> 7) & 1) == 1) return TRUE;	
	
	
	BOOL bDone = TRUE;
	nInfo = gData.nInspectInfo[nMNo][nSlot][nLens];
	if(nInfo == eLensInfo::Init) nInfo = eLensInfo::Good;
	if (m_pEquipData->bUseTopVision && ((gData.byInspectDone[nMNo][nSlot][nLens] >> 0) & 1) == 0) bDone = FALSE;	
	if (m_pEquipData->bUseBtmVision  && ((gData.byInspectDone[nMNo][nSlot][nLens] >> 1) & 1) == 0) bDone = FALSE;

	if (m_pEquipData->bResultTestUse) 
	{
		int nRand = g_objCommon.Get_Random(0, 99);
		int nNg = m_pEquipData->nResultTestNg;

		int nJudge = nRand < nNg ? 2 : 1;
		nInfo = gData.nInspectInfo[nMNo][nSlot][nLens] = nJudge;
		if (nInfo == 9) { nInfo = gData.nInspectInfo[nMNo][nSlot][nLens] = 1; }
		strLog.Format("ResultTest_Use : %d,%d,%d",nInfo, nSlot+1, nLens+1);
		g_objLogFile.Save_TestLog(strLog);
	} 
	
	DWORD dwTick = GetTickCount();
	if (!bDone) 
	{
		if (m_pEquipData->bUseInspectSkip || ((dwTick - dwStart)  > m_pEquipData->nDelayAdd[delay::InspectionWait]))
		{
			gData.nInspectInfo[nMNo][nSlot][nLens] = eLensInfo::NG;
			nInfo = gData.nInspectInfo[nMNo][nSlot][nLens];
			m_strLog.Format("Judge Time Over, SlotNo(%d), LensNo(%d)", nSlot+1, nLens+1);
			g_objLogFile.Save_HandlerLog(m_strLog);
		}
		else
		{
			return FALSE;
		}
	}		
	gData.byInspectDone[nMZNo-1][nSlot][nLens] |= (1 << 7);
	return TRUE;	// All Inspect Done
}



void CSequenceMain::Init_MZSlot(int nSlotNo, int nX, int nY)
{

}

BOOL CSequenceMain::Check_CtZigInMZ(int nPos)
{
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0;  j < gData.nLensCntX; j++)
		{
			for(int k = 0; k < gData.nLensCntY; k++)
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

BOOL CSequenceMain::Check_TrayAllReturn()
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


int CSequenceMain::Find_UnloadMZNo()
{
	int nMZNo = 0;
	for(int i = 0; i < 10; i++)
	{
		if(gData.nMZNoMZUnload[i] > 0)
		{
			nMZNo = gData.nMZNoMZUnload[i];
			return nMZNo;
		}
	}
	return nMZNo;
}

void CSequenceMain::Init_InspectInfo(int nMZNo, int nTNo, int nLensNo)
{
	gData.nInspectInfo[nMZNo-1][nTNo-1][nLensNo-1] = eLensInfo::Init;
}



void CSequenceMain::Write_LotJudge(int nMZNo, int nTrayNo, int nLensNo, int nInfo)
{
	CString strTemp;
	int nMx = nMZNo - 1;
	int nTx = nTrayNo - 1;
	int nLx = nLensNo - 1;
	if (nMx < 0 || nMx > 10 || nTx < 0 || nTx > 10 || nLx < 0 || nLx > ZIG_X*ZIG_Y || nInfo == 0) {
		strTemp.Format("Exception Write Judge(1) : %d,%d,%d,%d", nMx+1, nTx+1, nLx+1, nInfo);
		g_objLogFile.Save_TestLog(strTemp);
		return;
	}

	char chCode[2];	// 판정코드 (0:AG, 1:B1SP, 2:T1, 3:T2, 4:B2 5:B1AG 6:B13D)
	memcpy(chCode, gData.cJudgeCode[nMx][nTx][nLx], sizeof(char) *2);
	
	for (int i = 0; i < 2; i++) 
	{
		if(i == 0 && m_pEquipData->bUseTopVision && chCode[i] == 0)
		{
			chCode[i] = 0x6E; //  비전 결과가 안오면 공란으로 두지말고 E으로 기록해 달라. (From kjw request)
			strTemp.Format("Exception Write Judge(2) : %d,%d,%d,%d,%d", nMx+1, nTx+1, nLx+1, nInfo, i);
			g_objLogFile.Save_TestLog(strTemp);
		}
		else if(i == 1 && m_pEquipData->bUseBtmVision && chCode[i] == 0)
		{
			chCode[i] = 0x6E; //  비전 결과가 안오면 공란으로 두지말고 E으로 기록해 달라. (From kjw request)
			strTemp.Format("Exception Write Judge(2) : %d,%d,%d,%d,%d", nMx+1, nTx+1, nLx+1, nInfo, i);
			g_objLogFile.Save_TestLog(strTemp);
		}		
		else if (chCode[i] == 0) {
			chCode[i] = 0x45; //  비전 결과가 안오면 공란으로 두지말고 E으로 기록해 달라. (From kjw request)
			strTemp.Format("Exception Write Judge(2) : %d,%d,%d,%d,%d", nMx+1, nTx+1, nLx+1, nInfo, i);
			g_objLogFile.Save_TestLog(strTemp);
		}
	}

	CString strCode;	// Log 순서 : AG, B1_SP, T1, T2, B2, B1_AG, B1_3D, CODE
	strCode.Format("%c,%c,%d", chCode[0], chCode[1], nInfo);	// 마지막 CODE열 추가, 불량 종류 숫자 표시
	CString strResult = (nInfo == 1 ? "Pass" : "Fail");
	for (int i = 0; i < 2; i++)
	{
		if(chCode[i] == 0x6E) strResult = "Fail";
	}

	m_strLog.Format("%s,%s,%s,%d,%d,"",%s,%s", m_pEquipData->sEquipName, MAIN_VERSION, gData.sMZID[nMx], nTrayNo, nLensNo, strCode, strResult);
	g_objLogFile.Save_LotTime(nMZNo, m_strLog);
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


