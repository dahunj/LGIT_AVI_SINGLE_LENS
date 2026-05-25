// SequenceInit.cpp : 구현 파일
//
#include "stdafx.h"
#include "SingleLens.h"
#include "SequenceInit.h"
#include "math.h"

#include "LogFile.h"
#include "Common.h"
#include "SequenceMain.h"
#include "MESInterface.h"
#include "WorkDlg.h"

CSequenceInit g_objSequenceInit;

CSequenceInit::CSequenceInit()
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
	m_pMoveData = g_objDataManager.Get_pMoveData();
	
	m_bThreadInitial = FALSE;
	m_pThreadInitial = NULL;
	
	Reset_InitialCase();

	m_bInitComplete = FALSE;
}

CSequenceInit::~CSequenceInit()
{
	if (m_pThreadInitial) {
		m_bThreadInitial = FALSE;
		WaitForSingleObject(m_pThreadInitial->m_hThread, INFINITE);
	}
}

int *CSequenceInit::Get_InitialCase()
{
	static int nCase[14] = { 0 };

	nCase[0]  = m_niMainInitCase;		//  0. (Error : 1000)
	nCase[1]  = m_niConveyorCase;		//  1. (Error : 1100)
	nCase[2]  = m_niMZElevCase;			//  2. (Error : 1200)
	nCase[3]  = m_niFeederCase;			//  3. (Error : 1300)
	nCase[4]  = m_niTrayPickerCase;		//  4. (Error : 1400)
	nCase[5]  = m_niLensCleanCase;		//  4. (Error : 1500)
	nCase[6]  = m_niTopInspectorCase;	//  5. (Error : 1600)
	nCase[7]  = m_niBtmInspectorCase; 	//  6. (Error : 1700)
	nCase[8]  = m_niMarkUnitCase;			//  7. (Error : 1800)
	nCase[9]  = m_niMainIndexCase;		//  8. (Error : 1900)
	

	return nCase;
}

void CSequenceInit::Begin_InitialThread()
{
	m_bInitComplete = FALSE;

	Init_Replay();

	if (m_niMainInitCase == 0) m_niMainInitCase = 1;

	if (m_pThreadInitial) End_InitialThread();
	m_bThreadInitial = TRUE;
	m_pThreadInitial = AfxBeginThread(Thread_Initial, NULL);
}

void CSequenceInit::End_InitialThread()
{
	if (m_pThreadInitial) {
		m_bThreadInitial = FALSE;
		WaitForSingleObject(m_pThreadInitial->m_hThread, INFINITE);
	}
}

void CSequenceInit::Init_Replay()
{
	m_tiMainInitLoop.Set_LoopTime(20000);		//  0. (Error : 1000)
	m_tiConveyorLoop.Set_LoopTime(20000);		//  1. (Error : 1100)
	m_tiMZElevLoop.Set_LoopTime(20000);		//  2. (Error : 1200)
	m_tiFeederLoop.Set_LoopTime(20000);		//  3. (Error : 1300)
	m_tiTrayPickerLoop.Set_LoopTime(20000);		//  4. (Error : 1400)
	m_tiTopInspectorLoop.Set_LoopTime(20000);		//  5. (Error : 1500)
	m_tiBtmInspectorLoop.Set_LoopTime(20000);		//  6. (Error : 1600)
	m_tiMarkUnitLoop.Set_LoopTime(20000); 		//  7. (Error : 1700)
	m_tiMainIndexLoop.Set_LoopTime(20000);		//  8. (Error : 1800)

}

void CSequenceInit::Reset_InitialCase()
{
	m_niMainInitCase	= 0;	//  0. (Error : 1000)
	m_niConveyorCase	= 0;	//  1. (Error : 1100)
	m_niMZElevCase	= 0;	//  2. (Error : 1200)
	m_niFeederCase	= 0;	//  3. (Error : 1300)
	m_niTrayPickerCase	= 0;	//  4. (Error : 1400)
	m_niTopInspectorCase		= 0;	//  5. (Error : 1500)
	m_niBtmInspectorCase 	= 0;	//  6. (Error : 1600)
	m_niMarkUnitCase	= 0;	//  7. (Error : 1700)
	m_niMainIndexCase	= 0;	//  8. (Error : 1800)
	
}


BOOL CSequenceInit::Check_Mode()
{
	if(theApp.Get_MainMode() == MODE_MANUAL
		|| theApp.Get_MainMode() == MODE_SETUP
		|| theApp.Get_MainMode() == MODE_PARAM
		|| theApp.Get_MainMode() == MODE_PROHIBIT
		) return FALSE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Initial Thread Function 

UINT CSequenceInit::Thread_Initial(LPVOID lpVoid)
{
	while (g_objSequenceInit.m_bThreadInitial) {
		if (!g_objSequenceInit.Check_Mode()) break;
		if (!g_objCommon.Check_MainEmgAir()) break;
		if (!g_objCommon.Check_MainDoor()) break;
		if (!g_objCommon.Check_TrayFull()) break;
		if (!g_objCommon.Check_ServoOn()) break;
		if (!g_objCommon.Check_DirveAlarm()) break;

		if (!g_objSequenceInit.Initial_MainInit()) break;			//  0. (Error : 1000)
		if (!g_objSequenceInit.Initial_Conveyor()) break;			//  1. (Error : 1100)
		if (!g_objSequenceInit.Initial_MZ_Elevator()) break;		//  2. (Error : 1200)
		if (!g_objSequenceInit.Initial_Feeder()) break;				//  3. (Error : 1300)
		if (!g_objSequenceInit.Initial_TrayPicker()) break;			//  4. (Error : 1400)
		if (!g_objSequenceInit.Initial_LensCleaner()) break;		//  5. (Error : 1500)
		if (!g_objSequenceInit.Initial_TopInspector()) break;		//  5. (Error : 1500)
		if (!g_objSequenceInit.Initial_BtmInspector()) break;		//  6. (Error : 1600)
		if (!g_objSequenceInit.Initial_MarkUnit()) break;				//  7. (Error : 1700)
		if (!g_objSequenceInit.Initial_MainIndex()) break;			//  8. (Error : 1800)
		

		if (!g_objSequenceInit.Initial_Simulation()) break;

		Sleep(10);
	}
	g_objSequenceInit.m_bThreadInitial = FALSE;
	g_objSequenceInit.m_pThreadInitial = NULL;

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// 0. (Error : 1000)
BOOL CSequenceInit::Initial_MainInit()
{
	switch (m_niMainInitCase)
	{
	case 0:		// Wait
		return TRUE;

	case 1:		// Initial Start
		g_objLogFile.Save_HandlerLog("[Initial Sequence] MainInit Start");
		gLot.sLotID[0] = gLot.sLotID[1] = "";
		m_niMainInitCase++; m_tiMainInitLoop.Set_LoopTime(5000);
		break;	

	// Load
	case 2:		
		if (!m_pDX00->iElvMZExist1 && !m_pDX00->iElvMZExist2) 
		{
			m_niMainInitCase++; m_tiMainInitLoop.Set_LoopTime(5000);
		}
		break;
	case 3:		
		if (!m_pDX01->iZigPickerExist) 
		{
			m_niMainInitCase++; m_tiMainInitLoop.Set_LoopTime(5000);
		}
		break;

	case 4:		
		if (!m_pDX01->iFeederZigExist)
		{
			m_niMainInitCase++; m_tiMainInitLoop.Set_LoopTime(5000);
		}
		break;
	case 5:		
		if (!m_pDX01->iRailZigExist) //&& !m_pDX02->iIndexTZigExist) 
		{
			m_niMainInitCase++; m_tiMainInitLoop.Set_LoopTime(5000);
		}
		break;
	case 6:		
		if (!m_pDX01->iMagazineZigExist) 
		{
			m_niMainInitCase = 50; m_tiMainInitLoop.Set_LoopTime(5000);
		}
		break;
	case 50:	// 각 파트 초기화 진행
		if(m_niConveyorCase == 0)			m_niConveyorCase = 1;
		if(m_niMZElevCase == 0)				m_niMZElevCase = 1;
		if(m_niMainIndexCase == 0)			m_niMainIndexCase = 1;
		if(m_niFeederCase == 0)				m_niFeederCase = 1; 

		if (m_niTrayPickerCase == 0)		m_niTrayPickerCase = 1;		
		if (m_niLensCleanCase == 0)			m_niLensCleanCase = 1;		
		if (m_niTopInspectorCase == 0)		m_niTopInspectorCase = 1;		
		if (m_niBtmInspectorCase == 0)		m_niBtmInspectorCase = 1;		
		if (m_niMarkUnitCase == 0)			m_niMarkUnitCase = 1;				
		
		
		m_niMainInitCase++;m_tiMainInitLoop.Set_LoopTime(5000);
		break;

	case 51:	// Wait 
		if (m_niConveyorCase == 90 && m_niMZElevCase == 90 && m_niFeederCase == 90 &&
			m_niTrayPickerCase == 90 && m_niLensCleanCase == 90 && m_niTopInspectorCase == 90 
			&& m_niBtmInspectorCase == 90 && m_niMarkUnitCase == 90 && m_niMainIndexCase == 90 )
		{
			
			m_niMainInitCase = 90;m_tiMainInitLoop.Set_LoopTime(5000);
		}
		return TRUE;
	
	case 90:	// Initial Complete
		if(m_niMainIndexCase != 90) return TRUE;
		m_bInitComplete = TRUE;
		m_niMainInitCase = 0;

		Reset_InitialCase();

		// 변수 초기화
		g_objSequenceMain.Reset_MainRunCase();
		g_objSequenceMain.Set_ClearRunData(TRUE);
		if (gData.bCycleStop) g_dlgWork.PostMessage(UM_RESET_CYCLE_STOP, NULL, NULL);

		
		g_objLogFile.Save_HandlerLog("[Initial Sequence] MainInit Complete");
		return FALSE;	// Thread_Initial 종료
	}

	// 0. (Error : 1000)
	if (m_tiMainInitLoop.Over_LoopTime()) {
		g_objCommon.Show_Error(1000 + m_niMainInitCase);
		return FALSE;
	}
	return TRUE;
	
}

/////////////////////////////////////////////////////////////////////////////
// 1. (Error : 1100)
BOOL CSequenceInit::Initial_Conveyor()
{
	switch (m_niMZElevCase)
	{
	case 0:
		return TRUE;
	case 1:
		g_objCommon.Set_LoadCVStop();
		g_objCommon.Set_UnloadCVStop();
		g_objLogFile.Save_HandlerLog("[Initial Sequence] - MZ Elevator Complete");
		m_niConveyorCase = 90; m_tiConveyorLoop.Set_LoopTime(65000);
		break;
	case 90:
		m_tiConveyorLoop.Set_LoopTime(5000);
		return TRUE;
	}

	// 1. (Error : 1100)
	if (m_tiConveyorLoop.Over_LoopTime()) {
		g_objCommon.Show_Error(1100 + m_niConveyorCase);
		return FALSE;
	}

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// 2. (Error : 1200)
BOOL CSequenceInit::Initial_MZ_Elevator()
{
	switch (m_niMZElevCase)
	{
	case 0:
		return TRUE;
	case 1:
		if (!m_pDX00->iElvMZExist1 && !m_pDX00->iElvMZExist2) 
		{			
			g_objCommon.Set_ElevCVStop();
			Sleep(10);
			g_objCommon.Set_ElevLift1Out();
			Sleep(10);
			g_objCommon.Set_ElevLift1Down();
			Sleep(10);
			g_objCommon.Set_ElevStopper2Out();
			Sleep(10);
			g_objCommon.Set_ElevStopper2Down();
			Sleep(10);
			
			g_objAJinAXL.Set_EncoderType(AX_MZ_ELEVATOR_Z, 0);	// Inc
			g_objAJinAXL.Set_EncoderType(AX_MZ_ELEVATOR_Z, 1);	// Abs
			
			m_niMZElevCase++; m_tiMZElevLoop.Set_LoopTime(25000);
		}
		break;
	case 2:		
		if (g_objCommon.Check_Position(AX_ZIG_FEEDER_Y,0) && m_niFeederCase > 7) 
		{
			if (!m_tiMZElevLoop.Waiting_Time(100)) break;
			g_objAJinAXL.Home_Search(AX_MZ_ELEVATOR_Z);
			m_niMZElevCase++; m_tiMZElevLoop.Set_LoopTime(30000);
		}
		break;
	case 3:		
		if (g_objAJinAXL.Is_Home(AX_MZ_ELEVATOR_Z)) 
		{			
			if (!m_tiMZElevLoop.Waiting_Time(100)) break;
			g_objAJinAXL.Set_EncoderType(AX_MZ_ELEVATOR_Z, 0);	// Inc
			g_objAJinAXL.Set_EncoderType(AX_MZ_ELEVATOR_Z, 1);	// Abs
			m_niMZElevCase++; m_tiMZElevLoop.Set_LoopTime(30000);
			
		}
		break;
	case 4:
		if (!m_tiMZElevLoop.Waiting_Time(100)) break;
		g_objCommon.Move_Position(AX_MZ_ELEVATOR_Z, eElv_Z::Ready);
		m_niMZElevCase++; m_tiMZElevLoop.Set_LoopTime(5000);
		break;
	case 5:
		if(g_objCommon.Check_Position(AX_MZ_ELEVATOR_Z, eElv_Z::Ready))
		{
			g_objLogFile.Save_HandlerLog("[Initial Sequence] - MZ Elevator Complete");
			m_niMZElevCase = 90; m_tiMZElevLoop.Set_LoopTime(5000);
		}
		break;

	case 90:	// Initial Complete
		m_tiMZElevLoop.Set_LoopTime(5000);
		return TRUE;
	}

	// 1. (Error : 1200)
	if (m_tiMZElevLoop.Over_LoopTime()) {
		g_objCommon.Show_Error(1200 + m_niMZElevCase);
		return FALSE;
	}

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// 3. (Error : 1300)
BOOL CSequenceInit::Initial_Feeder()
{
	switch (m_niFeederCase)
	{
	case 0:
		return TRUE;
	case 1:
		if (!m_pDX01->iFeederZigExist) 
		{
			m_niFeederCase++; m_tiFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 2:	
		if (!m_pDX01->iMagazineZigExist) 
		{
			m_niFeederCase++; m_tiFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 3:	
		if (!m_pDX01->iRailZigExist && m_niTrayPickerCase > 10)  
		{				
			m_niFeederCase++; m_tiFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 4:
		m_niFeederCase++; m_tiFeederLoop.Set_LoopTime(30000);
		break;
	case 5:
		if(m_niTrayPickerCase > 10) // Tray Picker Z Ready Up Complete 
		{
			g_objAJinAXL.Home_Search(AX_ZIG_FEEDER_Y);
			m_niFeederCase++; m_tiFeederLoop.Set_LoopTime(15000);
		}
		return TRUE;

	case 6:
		if(g_objAJinAXL.Is_Home(AX_ZIG_FEEDER_Y))
		{
			g_objCommon.Move_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready);
			g_objAJinAXL.Home_Search(AX_ZIG_FEEDER_X);
			m_niFeederCase++; m_tiFeederLoop.Set_LoopTime(15000);
		}
		break;
	case 7:
		if(g_objAJinAXL.Is_Home(AX_ZIG_FEEDER_X) && g_objCommon.Check_Position(AX_ZIG_FEEDER_Y, eFeeder_Y::Ready))
		{			
			g_objLogFile.Save_HandlerLog("[Initial Sequence] - Feeder Complete");
			m_niFeederCase = 90; m_tiFeederLoop.Set_LoopTime(15000);
		}
		break;
	case 90:	// Initial Complete
		m_tiFeederLoop.Set_LoopTime(5000);
		return TRUE;
	}

	// 1. (Error : 1300)
	if (m_tiFeederLoop.Over_LoopTime()) {
		g_objCommon.Show_Error(1300 + m_niFeederCase);
		return FALSE;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// 4. (Error : 1400)
BOOL CSequenceInit::Initial_TrayPicker()
{
	
	switch (m_niTrayPickerCase)
	{
	case 0:
		return TRUE;
	case 1:
		if (!m_pDX01->iZigPickerExist) 
		{
			g_objAJinAXL.Set_EncoderType(AX_ZIG_PICKER_Z, 0);	// Inc
			g_objAJinAXL.Set_EncoderType(AX_ZIG_PICKER_Z, 1);	// Abs
			m_niTrayPickerCase++; m_tiTrayPickerLoop.Set_LoopTime(5000);
		}
		break;
	case 2:
		g_objAJinAXL.Home_Search(AX_ZIG_PICKER_Z);
		m_niTrayPickerCase++; m_tiTrayPickerLoop.Set_LoopTime(15000);
		break;
	case 3:
		if(g_objAJinAXL.Is_Home(AX_ZIG_PICKER_Z))
		{			
			g_objAJinAXL.Set_EncoderType(AX_ZIG_PICKER_Z, 0);	// Inc
			g_objAJinAXL.Set_EncoderType(AX_ZIG_PICKER_Z, 1);	// Abs
			m_niTrayPickerCase++; m_tiTrayPickerLoop.Set_LoopTime(15000);
		}
		break;
	case 4:
		if(!m_tiTrayPickerLoop.Waiting_Time(100)) break;
		g_objCommon.Move_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready);
		m_niTrayPickerCase = 10; m_tiTrayPickerLoop.Set_LoopTime(25000);
		break;
	case 10:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready))
		{
			g_objAJinAXL.Set_EncoderType(AX_ZIG_PICKER_Y, 0);	// Inc
			g_objAJinAXL.Set_EncoderType(AX_ZIG_PICKER_Y, 1);	// Abs
			m_niTrayPickerCase++; m_tiTrayPickerLoop.Set_LoopTime(25000);
		}
		break;
	case 11:
		g_objAJinAXL.Home_Search(AX_ZIG_PICKER_Y);
		m_niTrayPickerCase++; m_tiTrayPickerLoop.Set_LoopTime(25000);
		break;
	case 12:
		if(g_objAJinAXL.Is_Home(AX_ZIG_PICKER_Y))
		{
			g_objAJinAXL.Set_EncoderType(AX_ZIG_PICKER_Y, 0);	// Inc
			g_objAJinAXL.Set_EncoderType(AX_ZIG_PICKER_Y, 1);	// Abs
					
			m_niTrayPickerCase++; m_tiTrayPickerLoop.Set_LoopTime(25000);
		}
		break;
	case 13:
		if(!m_tiTrayPickerLoop.Waiting_Time(100)) break;
		g_objCommon.Move_Position(AX_ZIG_PICKER_Y, eZigPicker_Y::Ready);
		m_niTrayPickerCase++; m_tiTrayPickerLoop.Set_LoopTime(25000);
	case 14:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Y, eZigPicker_Y::Ready))
		{
			m_niTrayPickerCase++; m_tiTrayPickerLoop.Set_LoopTime(25000);
		}
		break;
	case 15:
		{
			g_objCommon.Set_TrayPickMasterOut();
			Sleep(5);
			g_objCommon.Set_TrayPickSlaveOut();			
			m_niTrayPickerCase++; m_tiTrayPickerLoop.Set_LoopTime(25000);
		}
		break;
	case 16:		// Tray Picker Slave Out 
		if (g_objCommon.Get_TrayPickMasterSlaveOut()) 
		{
			g_objLogFile.Save_HandlerLog("[Initial Sequence] - Feeder Complete");
			m_niTrayPickerCase = 90; m_tiTrayPickerLoop.Set_LoopTime(5000);

		}
		break;
		
	case 90:	// Initial Complete
		m_tiTrayPickerLoop.Set_LoopTime(5000);
		return TRUE;
	}

	// 1. (Error : 1400)
	if (m_tiTrayPickerLoop.Over_LoopTime()) {
		g_objCommon.Show_Error(1400 + m_niTrayPickerCase);
		return FALSE;
	}

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// 5. (Error : 1500)
BOOL CSequenceInit::Initial_LensCleaner()
{
	switch (m_niLensCleanCase)
	{
	case 0:
		return TRUE;
	case 1:
		g_objCommon.Set_CleanerOpen();
		m_niLensCleanCase++; m_tiLensCleanLoop.Set_LoopTime(5000);
		break;
	case 2:
		if(g_objCommon.Get_CleanerOpen())
		{
			g_objCommon.Set_CleanerBackward();
			m_niLensCleanCase = 10; m_tiLensCleanLoop.Set_LoopTime(5000);
		}		
		break;
	case 10:
		if(g_objCommon.Get_CleanerBackwardDone())
		{
			g_objLogFile.Save_HandlerLog("[Initial Sequence] - Lens Clean Complete");
			m_niLensCleanCase = 90; m_tiLensCleanLoop.Set_LoopTime(5000);
		}		
		break;	

	case 90:	// Initial Complete
		m_tiLensCleanLoop.Set_LoopTime(5000);
		return TRUE;
	}

	// 1. (Error : 1500)
	if (m_tiLensCleanLoop.Over_LoopTime()) {
		g_objCommon.Show_Error(1500 + m_niLensCleanCase);
		return FALSE;
	}



	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// 5. (Error : 1600)
BOOL CSequenceInit::Initial_TopInspector()
{
	switch (m_niTopInspectorCase)
	{
	case 0:
		return TRUE;
	case 1:
		if (1) 
		{
			g_objAJinAXL.Set_EncoderType(AX_TOP_INSPECTOR_Z, 0);	// Inc
			g_objAJinAXL.Set_EncoderType(AX_TOP_INSPECTOR_Z, 1);	// Abs
			m_niTopInspectorCase++; m_tiTopInspectorLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		}
		break;
	case 2:
		g_objAJinAXL.Home_Search(AX_TOP_INSPECTOR_Z);
		m_niTopInspectorCase++; m_tiTopInspectorLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		break;
	case 3:
		if(g_objAJinAXL.Is_Home(AX_TOP_INSPECTOR_Z))
		{			
			g_objAJinAXL.Set_EncoderType(AX_TOP_INSPECTOR_Z, 0);	// Inc
			g_objAJinAXL.Set_EncoderType(AX_TOP_INSPECTOR_Z, 1);	// Abs
			g_objAJinAXL.Clear_Scan(eVision::TC);
			m_niTopInspectorCase++; m_tiTopInspectorLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		}
		break;
	case 4:
		if(!m_tiTopInspectorLoop.Waiting_Time(100)) break;
		g_objCommon.Move_Position(AX_TOP_INSPECTOR_Z, eTopInspect_Z::Ready);
		m_niTopInspectorCase = 10; m_tiTopInspectorLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		break;
	case 10:
		if(g_objCommon.Check_Position(AX_TOP_INSPECTOR_Z, eTopInspect_Z::Ready))
		{
			m_niTopInspectorCase++; m_tiTopInspectorLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		}
		break;
	case 11:
		g_objAJinAXL.Home_Search(AX_TOP_INSPECTOR_Y);
		m_niTopInspectorCase++; m_tiTopInspectorLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		break;
	case 12:
		if(g_objAJinAXL.Is_Home(AX_TOP_INSPECTOR_Y))
		{			
			m_niTopInspectorCase++; m_tiTopInspectorLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		}
		break;
	case 13:
		g_objCommon.Move_Position(AX_TOP_INSPECTOR_Y, eTopInspect_Y::Ready);
		m_niTopInspectorCase++; m_tiTopInspectorLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
	case 14:
		if(g_objCommon.Check_Position(AX_TOP_INSPECTOR_Y, eTopInspect_Y::Ready))
		{
			m_niTopInspectorCase++; m_tiTopInspectorLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		}
		break;
	case 15:
		g_objAJinAXL.Home_Search(AX_TOP_INSPECTOR_X);
		m_niTopInspectorCase++; m_tiTopInspectorLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		break;
	case 16:		
		if(g_objAJinAXL.Is_Home(AX_TOP_INSPECTOR_X))
		{			
			g_objCommon.Move_Position(AX_TOP_INSPECTOR_X, eTopInspect_X::Ready);
			m_niTopInspectorCase++; m_tiTopInspectorLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		}
		break;
	case 17:
		if(g_objCommon.Check_Position(AX_TOP_INSPECTOR_X, eTopInspect_X::Ready))
		{
			g_objLogFile.Save_HandlerLog("[Initial Sequence] - Top Inspector Complete");
			m_niTopInspectorCase = 90; m_tiTopInspectorLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		}		

	case 90:	// Initial Complete
		m_tiTopInspectorLoop.Set_LoopTime(5000);
		return TRUE;
	}

	// 1. (Error : 1600)
	if (m_tiTopInspectorLoop.Over_LoopTime()) {
		g_objCommon.Show_Error(1600 + m_niTopInspectorCase);
		return FALSE;
	}



	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// 6. (Error : 1700)
BOOL CSequenceInit::Initial_BtmInspector()
{
	switch (m_niBtmInspectorCase)
	{
	case 0:
		return TRUE;
	case 1:
		if (1) 
		{
			g_objAJinAXL.Set_EncoderType(AX_BTM_INSPECTOR_Z, 0);	// Inc
			g_objAJinAXL.Set_EncoderType(AX_BTM_INSPECTOR_Z, 1);	// Abs
			m_niBtmInspectorCase++; m_tiBtmInspectorLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		}
		break;
	case 2:
		g_objAJinAXL.Home_Search(AX_BTM_INSPECTOR_Z);
		m_niBtmInspectorCase++; m_tiBtmInspectorLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		break;
	case 3:
		if(g_objAJinAXL.Is_Home(AX_BTM_INSPECTOR_Z))
		{			
			g_objAJinAXL.Set_EncoderType(AX_BTM_INSPECTOR_Z, 0);	// Inc
			g_objAJinAXL.Set_EncoderType(AX_BTM_INSPECTOR_Z, 1);	// Abs
			g_objAJinAXL.Clear_Scan(eVision::BC);
			m_niBtmInspectorCase++; m_tiBtmInspectorLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		}
		break;
	case 4:
		if(!m_tiBtmInspectorLoop.Waiting_Time(100)) break;
		g_objCommon.Move_Position(AX_BTM_INSPECTOR_Z, eBtmInspect_Z::Ready);
		m_niBtmInspectorCase = 10; m_tiBtmInspectorLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		break;
	case 10:
		if(g_objCommon.Check_Position(AX_BTM_INSPECTOR_Z, eBtmInspect_Z::Ready))
		{
			m_niBtmInspectorCase++; m_tiBtmInspectorLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		}
		break;
	case 11:
		g_objAJinAXL.Home_Search(AX_BTM_INSPECTOR_Y);
		m_niBtmInspectorCase++; m_tiBtmInspectorLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		break;
	case 12:
		if(g_objAJinAXL.Is_Home(AX_BTM_INSPECTOR_Y))
		{			
			m_niBtmInspectorCase++; m_tiBtmInspectorLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		}
		break;
	case 13:
		g_objCommon.Move_Position(AX_BTM_INSPECTOR_Y, eBtmInspect_Y::Ready);
		m_niBtmInspectorCase++; m_tiBtmInspectorLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
	case 14:
		if(g_objCommon.Check_Position(AX_BTM_INSPECTOR_Y, eBtmInspect_Y::Ready))
		{
			m_niBtmInspectorCase++; m_tiBtmInspectorLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		}
		break;
	case 15:
		g_objAJinAXL.Home_Search(AX_BTM_INSPECTOR_X);
		m_niBtmInspectorCase++; m_tiBtmInspectorLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		break;
	case 16:		// Tray Picker Slave Out 
		if(g_objAJinAXL.Is_Home(AX_BTM_INSPECTOR_X))
		{			
			g_objCommon.Move_Position(AX_BTM_INSPECTOR_X, eBtmInspect_X::Ready);
			m_niBtmInspectorCase++; m_tiBtmInspectorLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		}
		break;
	case 17:
		if(g_objCommon.Check_Position(AX_BTM_INSPECTOR_X, eBtmInspect_X::Ready))
		{
			g_objLogFile.Save_HandlerLog("[Initial Sequence] - Btm Inspector Complete");
			m_niBtmInspectorCase = 90; m_tiBtmInspectorLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		}		

	case 90:	// Initial Complete
		m_tiBtmInspectorLoop.Set_LoopTime(gData.nLTime[eLT::Scan]);
		return TRUE;
	}

	// 1. (Error : 1600)
	if (m_tiBtmInspectorLoop.Over_LoopTime()) {
		g_objCommon.Show_Error(1700 + m_niBtmInspectorCase);
		return FALSE;
	}

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// 7. (Error : 1800)
BOOL CSequenceInit::Initial_MarkUnit()
{
	switch (m_niMarkUnitCase)
	{
	case 0:
		return TRUE;
	case 1:
		if (1) 
		{
			g_objAJinAXL.Set_EncoderType(AX_MARK_UNIT_Z, 0);	// Inc
			g_objAJinAXL.Set_EncoderType(AX_MARK_UNIT_Z, 1);	// Abs
			m_niMarkUnitCase++; m_tiMarkUnitLoop.Set_LoopTime(5000);
		}
		break;
	case 2:
		g_objAJinAXL.Home_Search(AX_MARK_UNIT_Z);
		m_niMarkUnitCase++; m_tiMarkUnitLoop.Set_LoopTime(15000);
		break;
	case 3:
		if(g_objAJinAXL.Is_Home(AX_MARK_UNIT_Z))
		{			
			g_objAJinAXL.Set_EncoderType(AX_MARK_UNIT_Z, 0);	// Inc
			g_objAJinAXL.Set_EncoderType(AX_MARK_UNIT_Z, 1);	// Abs
			m_niMarkUnitCase++; m_tiMarkUnitLoop.Set_LoopTime(5000);
		}
		break;
	case 4:
		if(!m_tiMarkUnitLoop.Waiting_Time(100)) break;
		g_objCommon.Move_Position(AX_MARK_UNIT_Z, eMark_Z::Ready);
		m_niMarkUnitCase++; m_tiMarkUnitLoop.Set_LoopTime(5000);
		break;
	case 5:
		if(g_objCommon.Check_Position(AX_MARK_UNIT_Z, eMark_Z::Ready))
		{
			m_niMarkUnitCase++; m_tiMarkUnitLoop.Set_LoopTime(5000);
		}
		break;
	case 6:
		g_objAJinAXL.Home_Search(AX_MARK_UNIT_Y);
		m_niMarkUnitCase++; m_tiMarkUnitLoop.Set_LoopTime(5000);
		break;
	case 7:
		if(g_objAJinAXL.Is_Home(AX_MARK_UNIT_Y))
		{			
			m_niMarkUnitCase++; m_tiMarkUnitLoop.Set_LoopTime(5000);
		}
		break;
	case 8:
		g_objCommon.Move_Position(AX_MARK_UNIT_Y, eMark_Y::Ready);
		m_niMarkUnitCase++; m_tiMarkUnitLoop.Set_LoopTime(5000);
	case 9:
		if(g_objCommon.Check_Position(AX_MARK_UNIT_Y, eMark_Y::Ready))
		{
			m_niMarkUnitCase++; m_tiMarkUnitLoop.Set_LoopTime(5000);
		}
		break;
	case 10:
		g_objAJinAXL.Home_Search(AX_MARK_UNIT_X);
		m_niMarkUnitCase++; m_tiMarkUnitLoop.Set_LoopTime(15000);
		break;
	case 11:		// Tray Picker Slave Out 
		if(g_objAJinAXL.Is_Home(AX_MARK_UNIT_X))
		{			
			g_objCommon.Move_Position(AX_MARK_UNIT_X, eMark_X::Ready);
			m_niMarkUnitCase++; m_tiMarkUnitLoop.Set_LoopTime(5000);
		}
		break;
	case 12:
		if(g_objCommon.Check_Position(AX_MARK_UNIT_X, eMark_X::Ready))
		{
			g_objLogFile.Save_HandlerLog("[Initial Sequence] - Marker Complete");
			m_niMarkUnitCase = 90; m_tiMarkUnitLoop.Set_LoopTime(5000);
		}		

	case 90:	// Initial Complete
		m_tiMarkUnitLoop.Set_LoopTime(5000);
		return TRUE;
	}

	// 1. (Error : 1800)
	if (m_tiBtmInspectorLoop.Over_LoopTime()) {
		g_objCommon.Show_Error(1800 + m_niBtmInspectorCase);
		return FALSE;
	}


	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// 8. (Error : 1900)
BOOL CSequenceInit::Initial_MainIndex()
{

	switch (m_niMainIndexCase)
	{
	case 0:
		return TRUE;
	case 1:
		if(m_niTrayPickerCase > 10
			&& m_niLensCleanCase > 10
			&& m_niTopInspectorCase > 10
			&& m_niBtmInspectorCase > 10
			&& m_niMarkUnitCase > 10)
		{
			g_objLogFile.Save_HandlerLog("[Initial Sequence] - Main Index Start");
			m_niMainIndexCase++; m_tiMainIndexLoop.Set_LoopTime(5000);
		}
		return TRUE;
	case 2:
		g_objCommon.Set_IndexLoadAlignIn();
		m_niMainIndexCase++; m_tiMainIndexLoop.Set_LoopTime(5000);
		break;
	case 3:
		if(g_objCommon.Get_IndexLoadAlignIn())
		{					
			m_niMainIndexCase++; m_tiMainIndexLoop.Set_LoopTime(25000);
		}
		break;
	case 4:
		if(g_objCommon.Check_Position(AX_ZIG_PICKER_Z, eZigPicker_Z::Ready)
			&& g_objCommon.Check_Position(AX_TOP_INSPECTOR_Z, eTopInspect_Z::Ready)
			&& g_objCommon.Check_Position(AX_BTM_INSPECTOR_Z, eBtmInspect_Z::Ready)
			&& g_objCommon.Get_CleanerOpen() && g_objCommon.Get_CleanerBackwardDone()) //Interlock 
		{			
			g_objAJinAXL.Home_Search(AX_MAIN_INDEX_R);					
			m_niMainIndexCase++; m_tiMainIndexLoop.Set_LoopTime(30000);
		}		
		break;
	case 5:
	    if(g_objAJinAXL.Is_Home(AX_MAIN_INDEX_R))
		{
			g_objCommon.Move_Position(AX_MAIN_INDEX_R, eIndex_R::Ready);
			m_niMainIndexCase = 6; m_tiMainIndexLoop.Set_LoopTime(30000);
		}
		break;
	case 6:
		if(g_objCommon.Check_Position(AX_MAIN_INDEX_R, eIndex_R::Ready))
		{
			m_niMainIndexCase = 90; m_tiMainIndexLoop.Set_LoopTime(65000);
		}
		break;

	case 90:	// Initial Complete		
		m_tiMainIndexLoop.Set_LoopTime(5000);
		return TRUE;
	}

	// 1. (Error : 1900)
	if (m_tiMainIndexLoop.Over_LoopTime())
	{
		g_objCommon.Show_Error(1900 + m_niMainIndexCase);
		return FALSE;
	}
	
	return TRUE;
}




///////////////////////////////////////////////////////////////////////////////

BOOL CSequenceInit::Initial_Simulation()
{
#ifdef AJIN_BOARD_USE
	return TRUE;
#endif

	Sleep(SIM_WAITTIMES);

	if(m_niMZElevCase == 2)
	{

	}
	

	if(m_niFeederCase == 1)
	{
		m_pDX01->iFeederZigExist = FALSE;
	}
	if(m_niFeederCase == 2)
	{
		m_pDX01->iMagazineZigExist = FALSE;
	}
	if(m_niFeederCase == 3)
	{
		m_pDX01->iRailZigExist = FALSE;
	}

	return TRUE;
}

