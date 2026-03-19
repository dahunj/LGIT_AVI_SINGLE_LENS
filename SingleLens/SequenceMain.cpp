#include "StdAfx.h"
#include "SingleLens.h"
#include "SingleLensDlg.h"
#include "SequenceMain.h"
#include "Common.h"


CSequenceMain g_objSequenceMain;


CSequenceMain::CSequenceMain(void)
{
}


CSequenceMain::~CSequenceMain(void)
{
}


void CSequenceMain::Reset_MainRunCase()
{
	m_nLoadConveyorCase	= 0;			
	m_nMZElevCase		= 0;			
	m_nFeederCase		= 0;
	m_nTrayPickerCase	= 0;			
	m_nLensCleanerCase	= 0;			
	m_nTopInspectCase	= 0;			
	m_nBtmInspectCase	= 0;			
	m_nMarkerCase		= 0;			
	m_nIndexTCase	= 0;	
	m_nUnloadConveyorCase = 0;
	
}

int *CSequenceMain::Get_pMainRunCase()
{
	static int nMainCase[25] = { 0 };

	nMainCase[0] = m_nLoadConveyorCase;	
	nMainCase[1] = m_nMZElevCase;			
	nMainCase[2] = m_nFeederCase;
	nMainCase[3] = m_nTrayPickerCase;		
	nMainCase[4] = m_nLensCleanerCase;		
	nMainCase[5] = m_nTopInspectCase;	
	nMainCase[6] = m_nBtmInspectCase;	
	nMainCase[7] = m_nMarkerCase;		
	nMainCase[8] = m_nIndexTCase;	
	nMainCase[9] = m_nUnloadConveyorCase;
	return nMainCase;
}

int CSequenceMain::Get_MainRunCase(int nRun)
{
	if		(nRun == AUTO_LD_CONVEYOR)			return m_nLoadConveyorCase;	
	else if (nRun == AUTO_MZ_ELEVATOR)		return m_nMZElevCase;	
	else if (nRun == AUTO_FEEDER)			return m_nFeederCase;		
	else if (nRun == AUTO_TRAY_PICKER)		return m_nTrayPickerCase;		
	else if (nRun == AUTO_LENS_CLEANER)		return m_nLensCleanerCase;	
	else if (nRun == AUTO_TOP_INSPECT)		return m_nTopInspectCase;	
	else if (nRun == AUTO_BTM_INSPECT)		return m_nBtmInspectCase;		
	else if (nRun == AUTO_MARKER)			return m_nMarkerCase;		
	else if (nRun == AUTO_INDEX_TABLE)		return m_nIndexTCase;	
	else if (nRun == AUTO_UL_CONVEYOR)		return m_nUnloadConveyorCase;

	return 0;
}

void CSequenceMain::Set_MainRunCase(int nRun, int nCase)
{
	if		(nRun == AUTO_LD_CONVEYOR)		m_nLoadConveyorCase	= nCase;	
	else if (nRun == AUTO_MZ_ELEVATOR)		m_nMZElevCase	= nCase;	
	else if (nRun == AUTO_FEEDER)			m_nFeederCase		= nCase;	
	else if (nRun == AUTO_TRAY_PICKER)		m_nTrayPickerCase		= nCase;	
	else if (nRun == AUTO_LENS_CLEANER)		m_nLensCleanerCase	= nCase;	
	else if (nRun == AUTO_TOP_INSPECT)		m_nTopInspectCase	= nCase;	
	else if (nRun == AUTO_BTM_INSPECT)		m_nBtmInspectCase		= nCase;	
	else if (nRun == AUTO_MARKER)			m_nMarkerCase		= nCase;	
	else if (nRun == AUTO_INDEX_TABLE)		m_nIndexTCase	= nCase;
	else if (nRun == AUTO_UL_CONVEYOR)		m_nUnloadConveyorCase	= nCase;	
}

void CSequenceMain::Set_MainRunLoop(int nRun, int nLoop)
{
	if		(nRun == AUTO_LD_CONVEYOR)			m_nLoadConveyorLoop.Set_LoopTime(nLoop);	
	else if (nRun == AUTO_MZ_ELEVATOR)		m_nMZElevLoop.Set_LoopTime(nLoop);	
	else if (nRun == AUTO_FEEDER)			m_nFeederLoop.Set_LoopTime(nLoop);		
	else if (nRun == AUTO_TRAY_PICKER)		m_nTrayPickerLoop.Set_LoopTime(nLoop);		
	else if (nRun == AUTO_LENS_CLEANER)		m_nLensCleanerLoop.Set_LoopTime(nLoop);	
	else if (nRun == AUTO_TOP_INSPECT)		m_nTopInspectLoop.Set_LoopTime(nLoop);	
	else if (nRun == AUTO_BTM_INSPECT)		m_nBtmInspectLoop.Set_LoopTime(nLoop);		
	else if (nRun == AUTO_MARKER)			m_nMarkerLoop.Set_LoopTime(nLoop);		
	else if (nRun == AUTO_INDEX_TABLE)		m_nIndexTLoop.Set_LoopTime(nLoop);
	else if (nRun == AUTO_UL_CONVEYOR)		m_nUnloadConveyorLoop.Set_LoopTime(nLoop);
}



///////////////////////////////////////////////////////////////////////////////

BOOL CSequenceMain::Get_IsAutoRun()
{
	int *pCase = Get_pMainRunCase();
	for (int i = 0; i < AUTO_COUNT; i++) {
		/*if (i == AUTO_LOAD_BUFFER1 && m_nLoadBuff1Case == 50) continue;
		if (i == AUTO_LOAD_BUFFER2 && m_nLoadBuff2Case == 50) continue;
		if (i == AUTO_TRANS_BUFFER1 && m_nTransBuff1Case == 50) continue;
		if (i == AUTO_TRANS_BUFFER2 && m_nTransBuff2Case == 50) continue;
		if (i == AUTO_NG_STAGE1 && m_nNgStage1Case == 50) continue;
		if (i == AUTO_NG_STAGE2 && m_nNgStage2Case == 50) continue;
		if (i == AUTO_OK_STAGE1 && m_nOkStage1Case == 50) continue;
		if (i == AUTO_OK_STAGE2 && m_nOkStage2Case == 50) continue;*/

		if (*(pCase + i) > 0) return TRUE;
	}

	if (!Check_ModuleEmpty(0)) return TRUE;

	return FALSE;
}

BOOL CSequenceMain::Check_ModuleEmpty(int nPos)
{
	
	return TRUE;
}

BOOL CSequenceMain::Check_ModuleLotEnd(int nLotNo)
{


	return TRUE;
}

void CSequenceMain::Set_ClearRunData(BOOL bInit)
{
	
}

void CSequenceMain::Set_ClearLotData(BOOL bInit, int nLotNo)
{
	
}

///////////////////////////////////////////////////////////////////////////////



UINT CSequenceMain::Thread_Beep(LPVOID lpVoid)
{
	g_objSequenceMain.Beep_Post(0, (int)lpVoid);
	g_objSequenceMain.m_pThreadBeep = NULL;
	return 0;
}

UINT CSequenceMain::Thread_MainRun(LPVOID lpVoid)
{
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
	static int nMZCnt = 0; //Conveyor 위의 매거진 개수 

	switch(m_nLoadConveyorCase)
	{
	case 0:
		nMZCnt = Check_MZSensors();
		if(nMZCnt > 0 && !gData.bCycleStop)
		{
			if (!m_nLoadConveyorLoop.Waiting_Time(500)) break;			
			m_nLoadConveyorCase++; m_nLoadConveyorLoop.Set_LoopTime(5000);
		}
		return TRUE;
	case 1:
		if(m_pDX00->iMZElevExistRight)
		{
			m_nLoadConveyorCase = 10; m_nLoadConveyorLoop.Set_LoopTime(5000);			
		}
		else
		{
			m_pDY00->oLoadCVCCW = TRUE; m_pDY00->oLoadCVCW = TRUE;
			m_pDY00->oMZElevCVCCW = TRUE; m_pDY00->oMZElevCVCW = TRUE;
			g_objAJinAXL.Write_Output(0);
			m_nLoadConveyorCase++; m_nLoadConveyorLoop.Set_LoopTime(5000);		
		}
		break;
	case 2:
		if(m_pDX00->iMZElevExistRight)
		{
			m_pDY00->oLoadCVCCW = FALSE; m_pDY00->oLoadCVCW = FALSE;
			m_pDY00->oMZElevCVCCW = FALSE; m_pDY00->oMZElevCVCW = FALSE;
			g_objAJinAXL.Write_Output(0);
			m_nLoadConveyorCase = 3; m_nLoadConveyorLoop.Set_LoopTime(5000);	
		}
		break;
	case 3:
		m_pDY00->oMZElevLoadStopperUp = TRUE; m_pDY00->oMZElevUnloadStopperDown = FALSE;
		break;
	case 5:
		if(m_pDX00->iMZElevExistLeft)
		{
			nMZCnt--;			
		}
		break;

	//case 2:
	//	m_pDY00->oLoadCVStopperUp = FALSE; m_pDY00->oLoadCVStopperDown = TRUE;
	//	g_objAJinAXL.Write_Output(0);

	//	if(!m_pDX00->iLoadCVStopperUp && m_pDX00->iLoadCVStopperDown)
	//	{
	//			
	//	}
	//	break;
	//case 2:
	//	if(m_pDX00->iMZElevExistRight)
	//	{
	//		m_pDY00->oLoadCVCCW = FALSE; m_pDY00->oLoadCVCW = FALSE;
	//		g_objAJinAXL.Write_Output(0);
	//		m_nLoadConveyorCase++; m_nLoadConveyorLoop.Set_LoopTime(5000);
	//	}



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
	//Suppose MZ on Right of Elev
	switch(m_nMZElevCase)
	{
	case 0:
		return TRUE;
	case 1:
		if(m_pDX00->iMZElevExistRight && m_pDX00->iMZElevExistLeft)
		{
			m_nMZElevCase = 10; m_nMZElevLoop.Set_LoopTime(5000);	
		}
		else if(m_pDX00->iMZElevExistRight && ! m_pDX00->iMZElevExistLeft)
		{
			m_nMZElevCase = 30; m_nMZElevLoop.Set_LoopTime(5000);	
		}
		else if(!m_pDX00->iMZElevExistRight && m_pDX00->iMZElevExistLeft)
		{
			m_nMZElevCase = 50; m_nMZElevLoop.Set_LoopTime(5000);	
		}
		else  
		{
			// empty
			m_nMZElevCase = 70; m_nMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 70:
		//CW 회전하려면 CCW도 True 로 해야함 
		m_pDY00->oLoadCVCCW = TRUE; m_pDY00->oLoadCVCW = TRUE;
		m_pDY00->oMZElevCVCCW = TRUE; m_pDY00->oMZElevCVCW = TRUE;
		g_objAJinAXL.Write_Output(0);
		m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		break;
	case 71:
		if(m_pDX00->iMZElevExistRight)
		{
			m_pDY00->oLoadCVCCW = FALSE; m_pDY00->oLoadCVCW = FALSE;
			m_pDY00->oMZElevCVCCW = FALSE; m_pDY00->oMZElevCVCW = FALSE;
			g_objAJinAXL.Write_Output(0);
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 72:
		if(m_pDX00->iMZElevExistRight)
		{
			//m_pDY00->oMZElevAlignRightUp = TRUE; m_pDY00->oMZElevAlignRightDown = FALSE;
			//m_pDY00->oMZElevAlignRightIn = TRUE; m_pDY00->oMZElevAlignRightOut = FALSE;
			g_objAJinAXL.Write_Output(0);
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 73:
		//CCW는 CCW만 TRUE
		if(gLot.nMZRunningCnt > 1)
		{
			m_pDY00->oLoadCVCCW = TRUE; m_pDY00->oLoadCVCW = FALSE;
			m_pDY00->oMZElevCVCCW = TRUE; m_pDY00->oMZElevCVCW = FALSE;
			g_objAJinAXL.Write_Output(0);
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		}
		else // MZ = 1 
		{
			m_nMZElevCase = 100; m_nMZElevLoop.Set_LoopTime(5000);
		}		
		break;
	case 100:		
		if(g_objCommon.Check_Position(AX_FEEDER_Y, Feeder_Y::Ready))
		{
			//아래 부터 검사 
			g_objCommon.Move_Position(AX_MZ_ELEV_Z, MZ_Elev_Z::Bottom);
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		}		
		break;
	case 101:
		if(g_objCommon.Check_Position(AX_MZ_ELEV_Z, MZ_Elev_Z::Bottom))
		{
			g_objCommon.Move_Position(AX_FEEDER_X, Feeder_X::MZRight);
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 102:
		if(g_objCommon.Check_Position(AX_FEEDER_X, Feeder_X::MZRight))
		{
			g_objCommon.Move_Position(AX_FEEDER_Y, Feeder_Y::Sensing);
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 103:
		if(g_objCommon.Check_Position(AX_FEEDER_Y, Feeder_Y::Sensing))
		{
			if(m_pDX01->iFeederCoatJigCheck)
			{
				g_objCommon.Move_Position(AX_FEEDER_Y, Feeder_Y::JigRight);
				m_nMZElevCase = 110; m_nMZElevLoop.Set_LoopTime(5000);
			}
			else
			{
				g_objAJinAXL.Move_Relative(AX_MZ_ELEV_Z,  m_pEquipData->dMZPitchZ*(1.0)); 
				m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
			}
		}
		break;
	case 104:
		break;
	case 110:
		if(g_objCommon.Check_Position(AX_FEEDER_Y, Feeder_Y::JigRight))
		{
			m_pDY01->oFeederGripClose = TRUE; m_pDY01->oFeederGripOpen = FALSE;
			g_objAJinAXL.Write_Output(1);
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 111:
		if(m_pDX01->iFeederGripClose && !m_pDX01->iFeederGripOpen)
		{
			g_objCommon.Move_Position(AX_FEEDER_Y, Feeder_Y::Rail);
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 112:
		if(g_objCommon.Check_Position(AX_FEEDER_Y, Feeder_Y::Rail))
		{
			g_objCommon.Move_Position(AX_FEEDER_X, Feeder_X::Rail);
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 113:
		if(g_objCommon.Check_Position(AX_FEEDER_X, Feeder_X::Rail))
		{
			m_pDY01->oFeederGripClose = FALSE; m_pDY01->oFeederGripOpen = TRUE;
			g_objAJinAXL.Write_Output(1);
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 114:
		if(m_pDX01->iFeederGripOpen && !m_pDX01->iFeederGripClose)
		{
			g_objCommon.Move_Position(AX_FEEDER_Y, Feeder_Y::Ready);
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 115:
		if(g_objCommon.Check_Position(AX_FEEDER_Y, Feeder_Y::Ready))
		{
			g_objCommon.Move_Position(AX_FEEDER_X, Feeder_X::Ready);
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 116:
		if(g_objCommon.Check_Position(AX_FEEDER_X, Feeder_X::Ready))
		{
			m_nTrayPickerCase = 1; // Tray Picker load Start 
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
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

	// 3. (Error : 3700)
	if (m_nFeederLoop.Over_LoopTime()) 
	{		
		g_objCommon.Show_Error(3700 + m_nFeederCase);
		return FALSE;
	}

	return TRUE;
}
// 4. (Error : 4000)
BOOL CSequenceMain::TrayPickerRun()
{
	// 4. (Error : 4000)
	if (m_nTrayPickerLoop.Over_LoopTime()) 
	{		
		g_objCommon.Show_Error(4000 + m_nTrayPickerCase);
		return FALSE;
	}
	return TRUE;
}

// 5. (Error : 4300)
BOOL CSequenceMain::LensCleanerRun()
{


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
	// 7. (Error : 4900)
	if (m_nBtmInspectLoop.Over_LoopTime()) 
	{		
		g_objCommon.Show_Error(4900 + m_nBtmInspectCase);
		return FALSE;
	}
	return TRUE;
}

// 8. (Error : 5200)
BOOL CSequenceMain::MarkerRun()
{
	// 8. (Error : 5200)
	if (m_nMarkerLoop.Over_LoopTime()) 
	{		
		g_objCommon.Show_Error(5200 + m_nMarkerCase);
		return FALSE;
	}
	return TRUE;
}

// 9. (Error : 5500)
BOOL CSequenceMain::IndexTRun()
{
	// 9. (Error : 5500)
	if (m_nIndexTLoop.Over_LoopTime()) 
	{		
		g_objCommon.Show_Error(5500 + m_nIndexTCase);
		return FALSE;
	}
	return TRUE;
}

BOOL CSequenceMain::UnloadConveyorRun()
{
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

	if (m_nLoadConveyorCase == 0)	m_nLoadConveyorCase = 1;
	if (m_nMZElevCase == 0)			m_nMZElevCase = 1;
	if (m_nFeederCase == 0)			m_nFeederCase = 1;
	if (m_nTrayPickerCase == 0)		m_nTrayPickerCase = 1;
	if (m_nLensCleanerCase == 0)	m_nLensCleanerCase = 1;
	if (m_nTopInspectCase == 0)		m_nTopInspectCase = 1;
	if (m_nBtmInspectCase == 0 )	m_nBtmInspectCase = 1;
	if (m_nMarkerCase == 0)			m_nMarkerCase = 1;
	if (m_nIndexTCase == 0 )		m_nIndexTCase = 1;
	if (m_nUnloadConveyorCase == 0) m_nUnloadConveyorCase = 1;

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


int CSequenceMain::Check_MZSensors()
{
	int nMZCnt = 0;
	if (m_pDX00->iLoadCVMZExist5) nMZCnt++;
	if (m_pDX00->iLoadCVMZExist4) nMZCnt++;
	if (m_pDX00->iLoadCVMZExist3) nMZCnt++;
	if (m_pDX00->iLoadCVMZExist2) nMZCnt++;
	if (m_pDX00->iLoadCVMZExist1) nMZCnt++;
	if (m_pDX00->iMZElevExistLeft) nMZCnt++;
	if (m_pDX00->iMZElevExistRight) nMZCnt++;

	return nMZCnt;
	
}