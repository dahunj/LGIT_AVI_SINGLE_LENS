#include "StdAfx.h"
#include "SingleLens.h"
#include "SingleLensDlg.h"
#include "SequenceMain.h"
#include "Common.h"
#include "Inspector.h"
#include "LogFile.h"


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
	m_nZigPickerCase	= 0;			
	m_nLensCleanerCase	= 0;			
	m_nTopInspectCase	= 0;			
	m_nBtmInspectCase	= 0;			
	m_nMarkUnitCase		= 0;			
	m_nIndexTCase	= 0;	
	m_nUnloadConveyorCase = 0;
	
}

int *CSequenceMain::Get_pMainRunCase()
{
	static int nMainCase[25] = { 0 };

	nMainCase[0] = m_nLoadConveyorCase;	
	nMainCase[1] = m_nMZElevCase;			
	nMainCase[2] = m_nFeederCase;
	nMainCase[3] = m_nZigPickerCase;		
	nMainCase[4] = m_nLensCleanerCase;		
	nMainCase[5] = m_nTopInspectCase;	
	nMainCase[6] = m_nBtmInspectCase;	
	nMainCase[7] = m_nMarkUnitCase;		
	nMainCase[8] = m_nIndexTCase;	
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
	else if (nRun == AUTO_INDEX_TABLE)		return m_nIndexTCase;	
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
	else if (nRun == AUTO_MARKER)			m_nMarkUnitLoop.Set_LoopTime(nLoop);		
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
		
		return TRUE;
	

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
	static int  nMZCnt = 0;
	static int	nSlotNo = 0;
	DWORD dwTick1 = 0, dwTick2 = 0;
	
	//Suppose MZ on Right of Elev
	switch(m_nMZElevCase)
	{
	case 0:
		nMZCnt = Check_MZSensors();
		if(nMZCnt > 0 && !gData.bCycleStop)
		{
			if (!m_nMZElevLoop.Waiting_Time(500)) break;			
			m_nMZElevCase = 1; m_nMZElevLoop.Set_LoopTime(5000);
		}	
		return TRUE;
	case 1:
		if(!m_pDX00->iMZElevMZExist1 && !m_pDX00->iMZElevMZExist2)
		{
			//CW 회전하려면 CCW도 True 로 해야함 
			g_objCommon.Set_LoadCVRunCW();
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		}		
		break;
	case 2:
		if(m_pDX00->iMZElevMZExist1)
		{
			g_objCommon.Set_LoadCVStop();
			Sleep(5);
			g_objCommon.Set_ElevCVRunCW();
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 3:
		if(m_pDX00->iMZElevMZExist2)
		{
			g_objCommon.Set_ElevCVStop();
			Sleep(5);

			//out 
			//Stopper Up 
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 10:
		//if(m_pDX00->iMZElevUnloadStopperUp)
		{
			//m_pDY00->oMZElevAlignRightIn = TRUE; m_pDY00->oMZElevAlignRightOut = FALSE;
			g_objAJinAXL.Write_Output(0);
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 11:
		//if(m_pDX00->iMZElevUnloadStopperIn)
		{
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 12:
		//if(!m_pDX00->iMZElevExistLeft)
		{
			g_objCommon.Set_LoadCVRunCW();
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 13:
		//if(m_pDX00->iMZElevExistLeft)
		{
			g_objCommon.Set_LoadCVStop();
			Sleep(10);
			//Stopper Up 
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 14:
		//if(m_pDX00->iMZElevLoadStopperUp)
		{
			//m_pDY00->oMZElevAlignRightIn = TRUE; m_pDY00->oMZElevAlignRightOut = FALSE;
			g_objAJinAXL.Write_Output(0);
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 15:
		//if(m_pDX00->iMZElevLoadStopperIn)
		{
			m_nMZElevCase++; m_nMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 16:
		nSlotNo = 1;
		m_nMZElevCase = (int) FeederBranch::LoadSearch; m_nMZElevLoop.Set_LoopTime(5000);
		return TRUE;	
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
	static int nSlotNo = 0;
	static double dPosZ = 0.0;

	switch(m_nFeederCase)
	{
	case 0:
		return TRUE;

	case (int) FeederBranch::LoadSearch:		
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, Feeder_Y::Ready))
		{
			//아래 부터 검사 
			dPosZ = m_pMoveData->dMZElevZ[MZ_Elev_Z::Bottom] + m_pEquipData->dMZPitchRightZ * (nSlotNo - 1) ;
			g_objAJinAXL.Move_Absolute(AX_MZ_ELEVATOR_Z, dPosZ);

			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}		
		break;
	case 2:
		if(g_objAJinAXL.Is_MoveDone(AX_MZ_ELEVATOR_Z, dPosZ))
		{
			g_objCommon.Move_Position(AX_ZIG_FEEDER_X, Feeder_X::MZ2);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 3:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_X, Feeder_X::MZ2))
		{
			g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, Feeder_Y::CheckExist);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 4:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, Feeder_Y::CheckExist))
		{
			if(m_pDX01->iMagazineZigExist)
			{				
				g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, Feeder_Y::MZ2);
				m_nFeederCase = 10; m_nFeederLoop.Set_LoopTime(5000);
			}
			else
			{
				//Z Pitch Move 
				g_objAJinAXL.Move_Relative(AX_MZ_ELEVATOR_Z,  m_pEquipData->dMZPitchRightZ*(1.0)); 
				m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
			}
		}
		break;

	case 10:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, Feeder_Y::MZ2))
		{
			m_pDY01->oFeederGripClose = TRUE; m_pDY01->oFeederGripOpen = FALSE;
			g_objAJinAXL.Write_Output(1);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 11:
		if(m_pDX01->iFeederGripClose && !m_pDX01->iFeederGripOpen)
		{
			//Info
			gData.nSlotNoElev = nSlotNo;
#ifndef AJIN_BOARD_USE
			m_strLog.Format("%d", gData.nSlotNoElev++);
			gData.sZigIDElev = m_strLog;
#endif
			//gData.sZigIDElev = Get barcode 
			g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, Feeder_Y::ZigPicker);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 12:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, Feeder_Y::ZigPicker))
		{
			g_objCommon.Move_Position(AX_ZIG_FEEDER_X, Feeder_X::ZigPicker);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 13:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_X, Feeder_X::ZigPicker))
		{
			m_pDY01->oFeederGripClose = FALSE; m_pDY01->oFeederGripOpen = TRUE;
			g_objAJinAXL.Write_Output(1);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 14:
		if(m_pDX01->iFeederGripOpen && !m_pDX01->iFeederGripClose)
		{
			g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, Feeder_Y::Ready);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 15:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, Feeder_Y::Ready))
		{
			nSlotNo++;
			if(nSlotNo > 10) nSlotNo = 1;
			m_nZigPickerCase = ZigPickBranch::Load; // Tray Picker load Start 			
			m_nFeederCase = 0; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 20: // Tray Pick working 
		return TRUE;

	case (int) FeederBranch::Unload:
		return TRUE;
	case 31:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, Feeder_Y::Ready) && g_objCommon.Get_FeederOpen())
		{
			g_objCommon.Move_Position(AX_ZIG_FEEDER_X, Feeder_X::ZigPicker);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 32:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_X, Feeder_X::ZigPicker) && g_objCommon.Get_FeederOpen())
		{
			g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, Feeder_Y::ZigPicker);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 33:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, Feeder_Y::ZigPicker))
		{
			g_objCommon.Set_FeederClose();
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 34:
		if(g_objCommon.Get_FeederClose() && m_pDX01->iFeederZigExist)
		{
			g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, Feeder_Y::MZ2);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 35:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, Feeder_Y::MZ2))
		{
			g_objCommon.Set_FeederOpen();
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 36:
		if(g_objCommon.Get_FeederOpen())
		{
			g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, Feeder_Y::Ready);
			m_nFeederCase++; m_nFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 37:
		if(g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, Feeder_Y::Ready))
		{
			m_nIndexTCase = (int) IndexTBranch::CheckInOut;
			m_nFeederCase = 0; m_nFeederLoop.Set_LoopTime(5000);
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
	switch(m_nMZElevCase)
	{
	case 0:
		return TRUE;
	case (int) ZigPickBranch::Load:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Ready))
		{
			g_objCommon.Move_Position(AX_ZIG_PICKER_Y, Tray_Picker_Y::Rail);
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 2:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Y, Tray_Picker_Y::Rail))
		{
			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Rail);
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 3:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Rail))
		{
			g_objCommon.Set_TrayPickMasterIn();
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 5:
		if(g_objCommon.Get_TrayPickMasterIn())
		{
			g_objCommon.Set_TrayPickSlaveIn();
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	
	case 6:
		if(g_objCommon.Get_TrayPickMasterSlaveIn())
		{
			//Info 
			gData.nSlotNoTrayPick = gData.nSlotNoElev; gData.nSlotNoElev = 0;
			gData.sZigIDTrayPick =  gData.sZigIDElev; gData.sZigIDElev = "";
			
			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Ready);
			m_nZigPickerCase = 10; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 10:
		if( m_nFeederCase == 0 ) 
		{
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}		
		return TRUE;
	case 11:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Ready))
		{			
			m_nFeederCase = (int)FeederBranch::LoadSearch;
			g_objCommon.Move_Position(AX_ZIG_PICKER_Y, Tray_Picker_Y::Index);
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 12:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Y, Tray_Picker_Y::Index))
		{
			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Index);
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 13:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Index))
		{
			g_objCommon.Set_TrayPickSlaveOut();
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 14:
		if(g_objCommon.Get_TrayPickSlaveOut())
		{
			g_objCommon.Set_TrayPickMasterOut();
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 15:
		if(g_objCommon.Get_TrayPickMasterSlaveOut())
		{
			//Info
			gData.nSlotNoLoad = gData.nSlotNoTrayPick; gData.nSlotNoTrayPick = 0;
			gData.sZigIDLoad =  gData.sZigIDTrayPick; gData.sZigIDTrayPick = "";

			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Ready);
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 16:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Ready))
		{
			//Load Done 
			m_nIndexTCase = (int) IndexTBranch::ZoneStart; 
			m_nZigPickerCase = 0; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
		//Unload 
	case (int) ZigPickBranch::Unload:
		return TRUE;
	case 21:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Ready))
		{
			g_objCommon.Move_Position(AX_ZIG_PICKER_Y, Tray_Picker_Y::Index);
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 22:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Y, Tray_Picker_Y::Index))
		{
			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Index);
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 23:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Index))
		{
			g_objCommon.Set_TrayPickMasterIn();
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 24:
		if(g_objCommon.Get_TrayPickMasterIn())
		{
			g_objCommon.Set_TrayPickSlaveIn();
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 25:
		if(g_objCommon.Get_TrayPickMasterSlaveIn())
		{
			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Ready);
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 26:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Ready))
		{
			g_objCommon.Move_Position(AX_ZIG_PICKER_Y, Tray_Picker_Y::Rail);
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 27:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Y, Tray_Picker_Y::Rail))
		{
			g_objCommon.Check_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Rail);
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 28:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Rail))
		{
			g_objCommon.Set_TrayPickSlaveOut();
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 29:
		if(g_objCommon.Get_TrayPickSlaveOut())
		{
			g_objCommon.Set_TrayPickMasterOut();
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 30:
		if(g_objCommon.Get_TrayPickMasterSlaveOut())
		{
			g_objCommon.Check_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Ready);
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 31:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Ready))
		{			
			m_nFeederCase = (int) FeederBranch::Unload;
			m_nZigPickerCase = 0; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;




	/*	if(g_objCommon.Check_Position(AX_ZIG_PICKER_Y, Tray_Picker_Y::Index))
		{
			

			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Index);
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}*/
		break;
	case 32:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Index))
		{
			g_objCommon.Set_TrayPickMasterIn();
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 33:
		if(g_objCommon.Get_TrayPickMasterIn())
		{
			g_objCommon.Set_TrayPickSlaveIn();
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 34:
		if(g_objCommon.Get_TrayPickMasterSlaveIn())
		{
			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Ready);
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 35:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Ready))
		{
			g_objCommon.Move_Position(AX_ZIG_PICKER_Y, Tray_Picker_Y::Rail);
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 36:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Y, Tray_Picker_Y::Rail))
		{
			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Rail);
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 37:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Rail))
		{
			g_objCommon.Set_TrayPickSlaveOut();
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 38:
		if(g_objCommon.Get_TrayPickSlaveOut())
		{
			g_objCommon.Set_TrayPickMasterOut();
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 39:
		if(g_objCommon.Get_TrayPickMasterSlaveOut())
		{
			g_objCommon.Move_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Ready);
			m_nZigPickerCase++; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 40:
		m_nIndexTCase = (int)IndexTBranch::CheckInOut;
		m_nZigPickerCase = 0; m_nTrayPickerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		break;

	}

	// 4. (Error : 4000)
	if (m_nTrayPickerLoop.Over_LoopTime()) 
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
		if(!gData.bIndexDone[IndexT::Clean] && !Check_IndexEmpty(IndexT::Top))
		{
			m_nLensCleanerCase = 1;  m_nLensCleanerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		return TRUE;
	case 1:
		g_objCommon.Set_CleanerClose();
		m_nLensCleanerCase++; m_nLensCleanerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		break;
	case 2:
		if(g_objCommon.Get_CleanerClose())
		{
			g_objCommon.Set_CleanerForward();
			m_nLensCleanerCase++; m_nLensCleanerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}		
		break;
	case 3:
		if(g_objCommon.Get_CleanerForwardDone())
		{

			g_objCommon.Set_CleanerOpen();
			m_nLensCleanerCase++; m_nLensCleanerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;
	case 4:
		if(g_objCommon.Get_CleanerOpen())
		{
			g_objCommon.Set_CleanerBackward();
			m_nLensCleanerCase++; m_nLensCleanerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
	case 5:
		if(g_objCommon.Get_CleanerBackwardDone())
		{
			gData.bIndexDone[IndexT::Clean] = TRUE;
			m_nLensCleanerCase = 0; m_nLensCleanerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);			
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
		if(!gData.bIndexDone[IndexT::Top] && !Check_IndexEmpty(IndexT::Top))
		{
			m_nTopInspectCase++;
			m_nTopInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		return TRUE;
	case 1:
		if(g_objCommon.Check_Position(AX_TOP_INSPECTOR_Z, Top_Inspector_Z::Ready))
		{
			if(m_pEquipData->bUseTopVision)
			{
				Init_TopZig();
				nTopXPos = 1; nTopYPos = 1;
				m_nTopInspectCase++; m_nTopInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			}
		}
		break;
	case 2:
		if(Select_TopScanPos(nTopXPos, nTopYPos))
		{
			int nIdx = (nTopYPos - 1) * gData.nZigX + nTopXPos;
			dTopUnitY = m_pMoveData->dTopInspectorY[Top_Inspector_Y::ScanStart] + (m_pEquipData->dZigPitchY * (nTopYPos - 1));
			dTopUnitX = m_pMoveData->dTopInspectorX[Top_Inspector_X::ScanStart] + (m_pEquipData->dZigPitchX * (nTopXPos - 1));
			dTopUnitZ = m_pMoveData->dTopInspectorZ[Top_Inspector_Z::ScanStart];
			
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
	case 3:
		if (g_objAJinAXL.Is_MoveDone(AX_TOP_INSPECTOR_Y, dTopUnitY) &&
			g_objAJinAXL.Is_MoveDone(AX_TOP_INSPECTOR_X, dTopUnitX) &&
			g_objAJinAXL.Is_MoveDone(AX_TOP_INSPECTOR_Z, dTopUnitZ))
		{

			if (!m_pEquipData->bUseTopVision)
			{
				if (gData.nInfoIndexT[IndexT::Top][nTopYPos-1][nTopXPos-1] == 9)
					gData.nInfoIndexT[IndexT::Top][nTopYPos-1][nTopXPos-1] = LensState::TopDone;	//Scan Done
			
				m_nTopInspectCase = 10; m_nTopInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Scan]);
			} 
			else 
			{
				int nLensNo = (gData.nZigY - nTopYPos) * gData.nZigX + nTopXPos;	// Tray 하단부터 모듈 적재한다.
				g_objInspector.Set_LoadComplete(VISION_PC1, "T1", gData.sZigIDTop , gData.sMZIDTop, gData.nSlotNoTop, nLensNo);
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
			g_objInspector.Set_ZMoveComplete(VISION_PC1, "T1");
			m_nTopInspectCase = 5; m_nTopInspectLoop.Set_LoopTime(30000);	// 90초		
		}
		break;
	case 10:
		nTopXPos++;
		if(nTopXPos > gData.nZigX) 
		{
			nTopXPos = 1; nTopYPos++;
		}
		m_nTopInspectCase = 2; m_nTopInspectLoop.Set_LoopTime(5000);
		break;	
	case 15:
		gData.bIndexDone[IndexT::Top] = TRUE;
		m_nLensCleanerCase = 0; m_nLensCleanerLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
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
		if(!gData.bIndexDone[IndexT::Btm] && !Check_IndexEmpty(IndexT::Btm))
		{
			m_nBtmInspectCase++;
			m_nBtmInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		return TRUE;
	case 1:
		if(g_objCommon.Check_Position(AX_BTM_INSPECTOR_Z, Btm_Inspector_Z::Ready))
		{
			if(m_pEquipData->bUseBtmVision)
			{
				Init_TopZig();
				nBtmXPos = 1; nBtmYPos = 1;
				m_nBtmInspectCase++; m_nBtmInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			}
		}
		break;
	case 2:
		if(Select_TopScanPos(nBtmXPos, nBtmYPos))
		{
			int nIdx = (nBtmYPos - 1) * gData.nZigX + nBtmXPos;
			dBtmUnitY = m_pMoveData->dTopInspectorY[Top_Inspector_Y::ScanStart] + (m_pEquipData->dZigPitchY * (nBtmYPos - 1));
			dBtmUnitX = m_pMoveData->dTopInspectorX[Top_Inspector_X::ScanStart] + (m_pEquipData->dZigPitchX * (nBtmXPos - 1));
			dBtmUnitZ = m_pMoveData->dTopInspectorZ[Top_Inspector_Z::ScanStart];

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
	case 3:
		if (g_objAJinAXL.Is_MoveDone(AX_BTM_INSPECTOR_Y, dBtmUnitY) &&
			g_objAJinAXL.Is_MoveDone(AX_BTM_INSPECTOR_X, dBtmUnitX) &&
			g_objAJinAXL.Is_MoveDone(AX_BTM_INSPECTOR_Z, dBtmUnitZ))
		{

			if (!m_pEquipData->bUseTopVision)
			{
				if (gData.nInfoIndexT[IndexT::Btm][nBtmYPos-1][nBtmXPos-1] == 9)
					gData.nInfoIndexT[IndexT::Btm][nBtmYPos-1][nBtmXPos-1] = LensState::BtmDone;	//Scan Done
				
				m_nBtmInspectCase = 10; m_nBtmInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Scan]);
			} 
			else 
			{
				int nLensNo = (gData.nZigY - nBtmYPos) * gData.nZigX + nBtmXPos;	// Tray 하단부터 모듈 적재한다.
				g_objInspector.Set_LoadComplete(VISION_PC1, "B1", gData.sZigIDBtm , gData.sMZIDBtm, gData.nSlotNoBtm, nLensNo);
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
			g_objInspector.Set_ZMoveComplete(VISION_PC1, "B1");
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
		gData.bIndexDone[IndexT::Btm] = TRUE;
		m_nBtmInspectCase = 0; m_nBtmInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
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
		if(!gData.bIndexDone[IndexT::Mark] && !Check_IndexEmpty(IndexT::Mark))
		{
			m_nMarkUnitCase++; m_nMarkUnitLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		return TRUE;
	case 1:
		if(g_objCommon.Check_Position(AX_MARK_UNIT_Z, Marker_Z::Ready))
		{
			if(m_pEquipData->bUseMark)
			{
				//Init_TopZig();
				dwTick = GetTickCount();
				nMarkXPos = 1; nMarkYPos = 1;
				nLensNo = 1;
				m_nMarkUnitCase = 2; m_nMarkUnitLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
			}
		}
		break;
	case 2:
		if(Select_MarkScanPos(nMarkXPos, nMarkYPos))
		{
			int nIdx = (nMarkYPos - 1) * gData.nZigX + nMarkXPos;
			dMarkUnitY = m_pMoveData->dMarkUnitY[Marker_Y::LeftTop] + (m_pEquipData->dZigPitchY * (nMarkYPos - 1));
			dMarkUnitX = m_pMoveData->dMarkUnitX[Marker_X::LeftTop] + (m_pEquipData->dZigPitchX * (nMarkXPos - 1));
			dMarkUnitZ = m_pMoveData->dMarkUnitZ[Marker_Z::LeftTop];

			g_objAJinAXL.Move_Absolute(AX_MARK_UNIT_Y, dMarkUnitY);
			g_objAJinAXL.Move_Absolute(AX_MARK_UNIT_X, dMarkUnitX);
			g_objAJinAXL.Move_Absolute(AX_MARK_UNIT_Z, dMarkUnitZ);

			nLensNo = (gData.nZigY - nMarkYPos) * gData.nZigX + nMarkXPos;	// Tray 하단부터 모듈 적재한다.
			m_nMarkUnitCase = 5; m_nMarkUnitLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		else
		{
			m_nMarkUnitCase = 15; m_nMarkUnitLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}
		break;

	case 5:
		if (g_objAJinAXL.Is_MoveDone(AX_MARK_UNIT_Y, dMarkUnitY) &&
			g_objAJinAXL.Is_MoveDone(AX_MARK_UNIT_X, dMarkUnitX) &&
			g_objAJinAXL.Is_MoveDone(AX_MARK_UNIT_Z, dMarkUnitZ))
		
		break;
	case 6:
		if (!m_pEquipData->bUseMark)
		{
			g_objCommon.Move_Position(AX_MARK_UNIT_Z, Marker_Z::Ready);
			if (gData.nInfoIndexT[IndexT::Mark][nMarkYPos-1][nMarkXPos-1] == 9)
				gData.nInfoIndexT[IndexT::Mark][nMarkYPos-1][nMarkXPos-1] = LensState::Marked;	//Scan Done

			m_nBtmInspectCase = 15; m_nBtmInspectLoop.Set_LoopTime(gData.nTime[LoopTime::Scan]);
		} 
		else
		{
			bInspectFail = FALSE;
			if(!Check_InspectDone(gData.sZigIDMark, gData.nSlotNoMark, nLensNo, dwTick)) 
			{
				bInspectFail = TRUE;
				break;
			}
			if(bInspectFail) break; //Not Complete

			g_objCommon.Move_Position(AX_MARK_UNIT_Z, Marker_Z::Mark);
			m_nMarkUnitCase++; m_nMarkUnitLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}		
	case 7:
		if(g_objCommon.Check_Position(AX_MARK_UNIT_Z, Marker_Z::Mark))
		{
			g_objCommon.Move_Position(AX_MARK_UNIT_Z, Marker_Z::Ready);
			m_nMarkUnitCase = 2; m_nMarkUnitLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
		}		
		break;	
case 15:
		gData.bIndexDone[IndexT::Mark] = TRUE;
		m_nMarkUnitCase = 0; m_nMarkUnitLoop.Set_LoopTime(gData.nTime[LoopTime::Motion]);
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
BOOL CSequenceMain::IndexTRun()
{
	switch(m_nIndexTCase)
	{
	case 0:
		if (Check_IndexEmpty(-1) && Check_ZigPickerEmpty()) return TRUE;

		if(m_nZigPickerCase > 4 && m_nZigPickerCase <= 14)
		{
			m_nIndexTCase++; m_nIndexTLoop.Set_LoopTime(5000);
		}

		/*if(gData.bIndexDone[IndexT::Load] && g_objCommon.Get_IndexLoadAlignOut())
		{
			g_objCommon.Set_IndexLoadAlignIn();
		}*/		
		return TRUE;
	case 1:
		g_objCommon.Set_IndexLoadAlignOut();
	 	m_nIndexTCase++; m_nIndexTLoop.Set_LoopTime(5000);
		break;
	case 2:
		if(g_objCommon.Get_IndexLoadAlignOut())
		{
			m_nIndexTCase = 5; m_nIndexTLoop.Set_LoopTime(5000);
		}
		break;
	case (int)IndexTBranch::CheckInOut:
		if(Check_IndexEmpty(IndexT::Load))
		{			
			m_nFeederCase = FeederBranch::LoadSearch; // Feeder  부터
			m_nIndexTCase = 10; m_nIndexTLoop.Set_LoopTime(5000);
		}
		else 
		{ 
			m_nZigPickerCase = ZigPickBranch::Unload; // ZigPicker 부터 
			m_nIndexTCase = 10; m_nIndexTLoop.Set_LoopTime(5000);
		}
		break;
	case 10:
		// Wait Done 
		return TRUE;

	case IndexTBranch::ZoneStart:
		if(g_objCommon.Get_IndexLoadAlignIn()) //Set at ZigPicker Run 
		{
			m_nIndexTCase++; m_nIndexTLoop.Set_LoopTime(5000);
		}
	case 12:
		if(Check_IndexDone() && g_objCommon.Get_IndexLoadAlignIn())
		{
			if (Check_IndexEmpty(-1)) 
			{ 
				m_nIndexTCase = 0;
				return TRUE;
			}

			if ((g_objAJinAXL.Get_Position(AX_ZIG_PICKER_Y) <= 200.0 && g_objCommon.Check_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Ready)) 
				&& g_objCommon.Get_CleanerOpen()
				&& g_objCommon.Check_Position(AX_TOP_INSPECTOR_Z, Top_Inspector_Z::Ready)
				&& g_objCommon.Check_Position(AX_BTM_INSPECTOR_Z, Btm_Inspector_Z::Ready)
				&& g_objCommon.Check_Position(AX_MARK_UNIT_Z, Marker_Z::Ready))				 
			{
				g_objAJinAXL.Move_Relative(AX_MAIN_INDEX_R, m_pMoveData->dMainIndexR[0]);
				m_nIndexTCase++; m_nIndexTLoop.Set_LoopTime(10000);
			}

		}
		return TRUE;
	case 13:
		if (g_objAJinAXL.Is_MoveDone(AX_MAIN_INDEX_R, m_pMoveData->dMainIndexR[0])) {
			
			Set_IndexEnd();
			m_nIndexTCase = 0; m_nIndexTLoop.Set_LoopTime(5000);
		}
		break;

		// Lot End Home
	case 50:		// Index R Home

		if ((g_objAJinAXL.Get_Position(AX_ZIG_PICKER_Y) <= 200.0 && g_objCommon.Check_Position(AX_ZIG_PICKER_Z, Tray_Picker_Z::Ready)) 
			&& g_objCommon.Get_CleanerOpen()
			&& g_objCommon.Check_Position(AX_TOP_INSPECTOR_Z, Top_Inspector_Z::Ready)
			&& g_objCommon.Check_Position(AX_BTM_INSPECTOR_Z, Btm_Inspector_Z::Ready)
			&& g_objCommon.Check_Position(AX_MARK_UNIT_Z, Marker_Z::Ready))				 
		{
			g_objAJinAXL.Home_Search(AX_MAIN_INDEX_R);
			m_nIndexTCase++; m_nIndexTLoop.Set_LoopTime(10000);
		}
		break;
	case 51:		// Check R Home Done
		if (g_objAJinAXL.Is_Home(AX_MAIN_INDEX_R)) 
		{
			m_nIndexTCase = 0;
		}
		break;
	}
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
	switch(m_nUnloadConveyorCase)
	{
	case 0:
		return TRUE;
	

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
	if (m_nLoadConveyorCase == 0)	m_nLoadConveyorCase = 1;
	if (m_nMZElevCase == 0)			m_nMZElevCase = 1;
	if (m_nFeederCase == 0)			m_nFeederCase = 1;
	if (m_nZigPickerCase == 0)		m_nZigPickerCase = 1;
	if (m_nLensCleanerCase == 0)	m_nLensCleanerCase = 1;
	if (m_nTopInspectCase == 0)		m_nTopInspectCase = 1;
	if (m_nBtmInspectCase == 0 )	m_nBtmInspectCase = 1;
	if (m_nMarkUnitCase == 0)			m_nMarkUnitCase = 1;
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
	if (m_pDX00->iLoadCVMZExist1Left) nMZCnt++;
	
	return nMZCnt;	
}

BOOL CSequenceMain::Check_IndexDone()
{
	for(int i = 0 ; i < 6; i++)
	{
		if(!gData.bIndexDone[i] && !Check_IndexEmpty(i))
		{
			return FALSE;
		}
	}
	return TRUE;	
}


BOOL CSequenceMain::Check_IndexEmpty(int nPos)
{
	// nPos (0:Load, 1:clean, 2:top, 3:empty, 4:btm, 5:Mark  -1:All)
	int nS = (nPos == -1 ? 0 : nPos);
	int nE = (nPos == -1 ? 5 : nPos);

	for (int i = nS; i < nE + 1; i++) 
	{
		for (int j = 0; j < ZIG_X; j++) 
		{
			for (int k = 0; k < ZIG_Y; k++) 
			{
				if (gData.nInfoIndexT[i][j][k] > 0) return FALSE;
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
			if (gData.nInfoZigPick[i] > 0) return FALSE; 
		}		
	}
	return TRUE;
}



void CSequenceMain::Set_IndexEnd()
{
	memmove(gData.nInfoIndexT[IndexT::Clean], gData.nInfoIndexT[IndexT::Load], sizeof(int)*6*ZIG_X*ZIG_Y);
	memmove(gData.nInfoIndexT[IndexT::Top], gData.nInfoIndexT[IndexT::Clean], sizeof(int)*6*ZIG_X*ZIG_Y);
	memmove(gData.nInfoIndexT[IndexT::None], gData.nInfoIndexT[IndexT::Top], sizeof(int)*6*ZIG_X*ZIG_Y);
	memmove(gData.nInfoIndexT[IndexT::Btm], gData.nInfoIndexT[IndexT::None], sizeof(int)*6*ZIG_X*ZIG_Y);
	memmove(gData.nInfoIndexT[IndexT::Mark], gData.nInfoIndexT[IndexT::Btm], sizeof(int)*6*ZIG_X*ZIG_Y);

	memset(gData.nInfoIndexT[IndexT::Load], 0x00, sizeof(int)*6*ZIG_X*ZIG_Y);

	memset(gData.bIndexDone, 0x00, sizeof(BOOL) * 6);

}

void CSequenceMain::Init_TopZig()
{
	for(int i = 0; i < ZIG_X; i++)
	{
		for(int j = 0; j < ZIG_Y; j++)
		{
			if(gData.nInfoIndexT[IndexT::Top][ZIG_X][ZIG_Y] == LensState::Init)
			{
				gData.nInfoIndexT[IndexT::Top][ZIG_X][ZIG_Y] = LensState::TopReady;
			}
		}
	}
}



BOOL CSequenceMain::Select_TopScanPos(int &nTopPosX, int &nTopPosY)
{
	// Module만 Scan

	nTopPosX = nTopPosY = 0;

	//Y 기준 X 증가하면서 찍는 방법 
	for(int j=(gData.nZigY - 1); j>=0; j--) 
	{
		if (j==1 || j==3 || j==5 || j==7 || j==9 || j==11)
		{
			for(int i = (gData.nZigX-1); i >=0; i--) 
			{
				if (gData.nInfoIndexT[IndexT::Top][j][i] == LensState::TopReady)  
				{
					nTopPosY = j + 1;
					nTopPosX = i + 1;
					break;
				}
			}
		}
		else
		{
			for(int i = 0; i < gData.nZigX; i++)
			{
				if (gData.nInfoIndexT[IndexT::Top][j][i] == LensState::TopReady) 
				{
					nTopPosY = j + 1;
					nTopPosX = i + 1;
					break;
				}
			}
		}
		
		if (nTopPosY > 0) break;
	}

	if (nTopPosY > gData.nZigY) return FALSE;
	if (nTopPosY == 0 || nTopPosX ==0) return FALSE;
	return TRUE;
}


void CSequenceMain::Init_BtmZig()
{
	for(int i = 0; i < ZIG_X; i++)
	{
		for(int j = 0; j < ZIG_Y; j++)
		{
			if(gData.nInfoIndexT[IndexT::Btm][ZIG_X][ZIG_Y] == LensState::Init
				|| gData.nInfoIndexT[IndexT::Btm][ZIG_X][ZIG_Y] == LensState::TopDone)
			{
				gData.nInfoIndexT[IndexT::Btm][ZIG_X][ZIG_Y] = LensState::BtmReady;
			}
		}
	}
}




BOOL CSequenceMain::Select_BtmScanPos(int &nBtmPosX, int &nBtmPosY)
{
	// Module만 Scan

	nBtmPosX = nBtmPosY = 0;

	//Y 기준 X 증가하면서 찍는 방법 
	for(int j=(gData.nZigY - 1); j>=0; j--) 
	{
		if (j==1 || j==3 || j==5 || j==7 || j==9 || j==11)
		{
			for(int i = (gData.nZigX-1); i >=0; i--) 
			{
				if (gData.nInfoIndexT[IndexT::Btm][j][i] == LensState::BtmReady)  
				{
					nBtmPosY = j + 1;
					nBtmPosX = i + 1;
					break;
				}
			}
		}
		else
		{
			for(int i = 0; i < gData.nZigX; i++)
			{
				if (gData.nInfoIndexT[IndexT::Btm][j][i] == LensState::BtmReady) 
				{
					nBtmPosY = j + 1;
					nBtmPosX = i + 1;
					break;
				}
			}
		}

		if (nBtmPosY > 0) break;
	}

	if (nBtmPosY > gData.nZigY) return FALSE;
	if (nBtmPosY == 0 || nBtmPosX ==0) return FALSE;
	return TRUE;
}



BOOL CSequenceMain::Select_MarkScanPos(int &nMarkPosX, int &nMarkPosY)
{
	// Module만 Scan
	return TRUE;
}


BOOL CSequenceMain::Check_InspectDone(const CString& sZigID, int sSlotNo, int sLensNo, DWORD dwStart)
{
	int nSlot = sSlotNo - 1;
	int nLens = sLensNo - 1;

	if (((gData.byInspectDone[nSlot][nLens] >> 7) & 1) == 1) return TRUE;	// 판정 완료 (2번 판정하지 않기 위해)

	
	BOOL bDone = TRUE;
	if (m_pEquipData->bUseTopVision && ((gData.byInspectDone[nSlot][nLens] >> 0) & 1) == 0)
		bDone = FALSE;	// return FALSE;	// Angle
	if (m_pEquipData->bUseBtmVision  && ((gData.byInspectDone[nSlot][nLens] >> 1) & 1) == 0) 
		bDone = FALSE;


	DWORD dwTick = GetTickCount();
	if (!bDone) 
	{
		if (m_pEquipData->bUseInspectSkip || ((dwTick - dwStart)  > m_pEquipData->nDelayAdd[delay::InspectionWait]))
		{
			gData.nInspectInfo[nSlot][nLens] = LensState::NG;
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



	gData.byInspectDone[nSlot][nLens] |= (1 << 7);	// 판정 완료 (2번 판정하지 않기 위해)
	return TRUE;	// All Inspect Done
}