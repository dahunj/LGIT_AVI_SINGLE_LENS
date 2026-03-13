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
	nCase[2]  = m_niMZElevCase;		//  2. (Error : 1200)
	nCase[3]  = m_niFeederCase;		//  3. (Error : 1300)
	nCase[4]  = m_niTrayPickerCase;		//  4. (Error : 1400)
	nCase[5]  = m_niTopInspectorCase;		//  5. (Error : 1500)
	nCase[6]  = m_niBtmInspectorCase; 		//  6. (Error : 1600)
	nCase[7]  = m_niMarkerCase;		//  7. (Error : 1700)
	nCase[8]  = m_niIndexTableCase;		//  8. (Error : 1800)
	

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
	m_tiMarkerLoop.Set_LoopTime(20000); 		//  7. (Error : 1700)
	m_tiIndexTableLoop.Set_LoopTime(20000);		//  8. (Error : 1800)

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
	m_niMarkerCase	= 0;	//  7. (Error : 1700)
	m_niIndexTableCase	= 0;	//  8. (Error : 1800)
	
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

		if (!g_objSequenceInit.Initial_MainInit()) break;		//  0. (Error : 1000)
		if (!g_objSequenceInit.Initial_Conveyor()) break;		//  1. (Error : 1100)
		if (!g_objSequenceInit.Initial_MZ_Elevator()) break;		//  2. (Error : 1200)
		if (!g_objSequenceInit.Initial_Feeder()) break;		//  3. (Error : 1300)
		if (!g_objSequenceInit.Initial_TrayPicker()) break;		//  4. (Error : 1400)
		if (!g_objSequenceInit.Initial_TopInspector()) break;		//  5. (Error : 1500)
		if (!g_objSequenceInit.Initial_BtmInspector()) break;		//  6. (Error : 1600)
		if (!g_objSequenceInit.Initial_Marker()) break;		//  7. (Error : 1700)
		if (!g_objSequenceInit.Initial_IndexTable()) break;		//  8. (Error : 1800)
		

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
		if (!m_pDX00->iMZElevMZExist1 && !m_pDX00->iMZElevMZExist2) 
		{
			m_niMainInitCase++; m_tiMainInitLoop.Set_LoopTime(5000);
		}
		break;
	case 3:		
		if (!m_pDX01->iTrayPickerExist) 
		{
			m_niMainInitCase++; m_tiMainInitLoop.Set_LoopTime(5000);
		}
		break;

	case 4:		
		if (!m_pDX01->iFeederCoatJigCheck)
		{
			m_niMainInitCase++; m_tiMainInitLoop.Set_LoopTime(5000);
		}
		break;
	case 5:		
		if (!m_pDX01->iRailCheckFront && !m_pDX01->iRailCheckRear ) 
		{
			m_niMainInitCase++; m_tiMainInitLoop.Set_LoopTime(5000);
		}
		break;
	case 6:		
		if (!m_pDX01->iMZCoatJigExist) 
		{
			m_niMainInitCase = 50; m_tiMainInitLoop.Set_LoopTime(5000);
		}
		break;
	case 50:	// 각 파트 초기화 진행
		if (m_niConveyorCase == 0)	 m_niConveyorCase = 1;				//  1. (Error : 1100)
		if (m_niMZElevCase == 0) m_niMZElevCase = 1;					//  2. (Error : 1200)
		if (m_niFeederCase == 0) m_niFeederCase = 1;					//  3. (Error : 1300)
		if (m_niTrayPickerCase == 0)	 m_niTrayPickerCase = 1;		//  4. (Error : 1400)
		if (m_niTopInspectorCase == 0)	 m_niTopInspectorCase = 1;		//  5. (Error : 1500)
		if (m_niBtmInspectorCase == 0) m_niBtmInspectorCase = 1;					//  3. (Error : 1300)
		if (m_niMarkerCase == 0)	 m_niMarkerCase = 1;		//  4. (Error : 1400)
		if (m_niIndexTableCase == 0)	 m_niIndexTableCase = 1;		//  5. (Error : 1500)


		m_niMainInitCase++;
		break;

	case 51:	// Wait 
		if (m_niMainInitCase == 90 && m_niMZElevCase == 90 && m_niFeederCase == 90 &&
			m_niTrayPickerCase == 90 && m_niLensCleanCase == 90 && m_niTopInspectorCase == 90 && m_niBtmInspectorCase == 90 &&
			m_niMarkerCase == 90 && m_niIndexTableCase == 90 ) {
				m_niMainInitCase = 90;
		}
		return TRUE;

	case 90:	// Initial Complete
		m_bInitComplete = TRUE;

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
		if (!m_pDX00->iMZElevMZExist1 && !m_pDX00->iMZElevMZExist2) 
		{			
			g_objAJinAXL.Set_EncoderType(AX_MZ_ELEV_Z, 0);	// Inc
			g_objAJinAXL.Set_EncoderType(AX_MZ_ELEV_Z, 1);	// Abs
			
			m_niMZElevCase++; m_tiMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 2:		
		if (g_objCommon.Check_Position(AX_FEEDER_Y,0) && m_niFeederCase > 5) 
		{
			if (!m_tiMZElevLoop.Waiting_Time(500)) break;
			g_objAJinAXL.Home_Search(AX_MZ_ELEV_Z);
			m_niMZElevCase++; m_tiMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 3:		
		if (g_objAJinAXL.Is_Home(AX_MZ_ELEV_Z)) 
		{			
			if (!m_tiMZElevLoop.Waiting_Time(500)) break;
			g_objAJinAXL.Set_EncoderType(AX_MZ_ELEV_Z, 0);	// Inc
			g_objAJinAXL.Set_EncoderType(AX_MZ_ELEV_Z, 1);	// Abs
			m_niMZElevCase = 90; m_tiMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 90:	// Initial Complete
		return TRUE;
	}

	//g_objAJinAXL.Set_EncoderType(AX_NG_STAGE1_Z, 0);	// Inc
	//g_objAJinAXL.Set_EncoderType(AX_NG_STAGE2_Z, 0);	// Inc
	//g_objAJinAXL.Set_EncoderType(AX_NG_STAGE1_Z, 1);	// Abs
	//g_objAJinAXL.Set_EncoderType(AX_NG_STAGE2_Z, 1);	// Abs



	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// 3. (Error : 1300)
BOOL CSequenceInit::Initial_Feeder()
{
	switch (m_niMZElevCase)
	{
	case 0:
		return TRUE;
	case 1:
		if (!m_pDX01->iFeederCoatJigCheck) 
		{
			m_niFeederCase++; m_tiFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 2:	
		if (!m_pDX01->iRailCheckFront && !m_pDX01->iRailCheckRear) 
		{
			m_niFeederCase++; m_tiFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 3:	
		if (!m_pDX01->iMZCoatJigExist) 
		{
			g_objAJinAXL.Home_Search(AX_FEEDER_Y);			
			m_niFeederCase++; m_tiFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 4:
		if(g_objAJinAXL.Is_Home(AX_FEEDER_Y))
		{
			g_objCommon.Move_Position(AX_FEEDER_Y, Feeder_Y::Ready);
			g_objAJinAXL.Home_Search(AX_FEEDER_X);
			m_niFeederCase++; m_tiFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 5:
		if(g_objAJinAXL.Is_Home(AX_FEEDER_X) && g_objCommon.Check_Position(AX_FEEDER_Y, Feeder_Y::Ready))
		{			
			g_objLogFile.Save_HandlerLog("[Initial Sequence] - Front Picker Complete");
			m_niFeederCase = 90; m_tiFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 90:	// Initial Complete
		return TRUE;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// 4. (Error : 1400)
BOOL CSequenceInit::Initial_TrayPicker()
{
	switch (m_niMainInitCase)
	{
	case 3:		// Tray Picker Slave Out 
		if (!m_pDX01->iTrayPickerSlaveIn && m_pDX01->iTrayPickerSlaveOut) 
		{
			m_niMainInitCase++; m_tiMainInitLoop.Set_LoopTime(5000);
		}
		break;
	case 4:		// Tray Picker Master Out 
		if (!m_pDX01->iTrayPickerMasterIn && m_pDX01->iTrayPickerMasterOut) 
		{
			m_niMainInitCase++; m_tiMainInitLoop.Set_LoopTime(5000);
		}
		break;
	}

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// 5. (Error : 1500)
BOOL CSequenceInit::Initial_TopInspector()
{
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// 6. (Error : 1600)
BOOL CSequenceInit::Initial_BtmInspector()
{
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// 7. (Error : 1700)
BOOL CSequenceInit::Initial_Marker()
{
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// 8. (Error : 1800)
BOOL CSequenceInit::Initial_IndexTable()
{
	return TRUE;
}




///////////////////////////////////////////////////////////////////////////////

BOOL CSequenceInit::Initial_Simulation()
{
#ifdef AJIN_BOARD_USE
	return TRUE;
#endif

	Sleep(SIM_WAITTIMES);

	
	

	return TRUE;
}

