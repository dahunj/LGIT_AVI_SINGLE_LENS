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
		if (!m_pDX00->iMZElevMZExist1Left && !m_pDX00->iMZElevMZExist2) 
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
		if (m_niBtmInspectorCase == 0) m_niBtmInspectorCase = 1;		//  6. (Error : 1600)
		if (m_niMarkerCase == 0)	 m_niMarkerCase = 1;				//  7. (Error : 1700)
		if (m_niIndexTableCase == 0)	 m_niIndexTableCase = 1;		//  8. (Error : 1800)
		
		m_niMainInitCase++;m_tiMainInitLoop.Set_LoopTime(5000);
		break;

	case 51:	// Wait 
		if (m_niMainInitCase == 90 && m_niConveyorCase == 90 && m_niMZElevCase == 90 && m_niFeederCase == 90 &&
			m_niTrayPickerCase == 90 && m_niLensCleanCase == 90 && m_niTopInspectorCase == 90 && m_niBtmInspectorCase == 90 &&
			m_niMarkerCase == 90 && m_niIndexTableCase == 90 )
		{
			m_niMainInitCase = 52;m_tiMainInitLoop.Set_LoopTime(5000);
		}
		return TRUE;
	case 52:
		m_pDY01->oIndexTInOutAlignIn = FALSE;
		m_pDY01->oIndexTInOutAlignOut = TRUE;
		m_pDY01->oIndexTCleanerAlignIn = FALSE;
		m_pDY01->oIndexTCleanerAlignOut = TRUE;
		m_pDY01->oIndexTTopAlignIn = FALSE;
		m_pDY01->oIndexTTopAlignOut = TRUE;
		m_pDY01->oIndexTEmptyAlignIn = FALSE;
		m_pDY01->oIndexTEmptyAlignOut = TRUE;
		m_pDY01->oIndexTBtmAlignIn = FALSE;
		m_pDY01->oIndexTBtmAlignOut = TRUE;
		m_pDY01->oIndexTMarkerAlignIn = FALSE;
		m_pDY01->oIndexTMarkerAlignOut = TRUE;
		g_objAJinAXL.Write_Output(1);
		m_niMainInitCase = 90;m_tiMainInitLoop.Set_LoopTime(5000);
		break;
	case 53:
		if(!m_pDX01->iIndexTInOutAlignIn && m_pDX01->iIndexTInOutAlignOut
			&& !m_pDX01->iIndexTCleanerAlignIn && m_pDX01->iIndexTCleanerAlignOut
			&& !m_pDX01->iIndexTTopAlignIn && m_pDX01->iIndexTTopAlignOut
			&& !m_pDX01->iIndexTEmptyAlignIn && m_pDX01->iIndexTEmptyAlignOut
			&& !m_pDX01->iIndexTBtmAlignIn && m_pDX01->iIndexTBtmAlignOut
			&& !m_pDX01->iIndexTMarkAlignIn && m_pDX01->iIndexTMarkAlignOut		
		)
		{
			m_niMainInitCase = 90;m_tiMainInitLoop.Set_LoopTime(5000);
		}
		break;

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
	switch (m_niMZElevCase)
	{
	case 0:
		return TRUE;
	case 1:
		g_objLogFile.Save_HandlerLog("[Initial Sequence] - MZ Elevator Complete");
		m_niConveyorCase = 90; m_tiConveyorLoop.Set_LoopTime(5000);
		break;
	case 90:
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
		if (!m_pDX00->iMZElevMZExist1Left && !m_pDX00->iMZElevMZExist2) 
		{			
			g_objAJinAXL.Set_EncoderType(AX_MZ_ELEV_Z, 0);	// Inc
			g_objAJinAXL.Set_EncoderType(AX_MZ_ELEV_Z, 1);	// Abs
			
			m_niMZElevCase++; m_tiMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 2:		
		if (g_objCommon.Check_Position(AX_FEEDER_Y,0) && m_niFeederCase > 7) 
		{
			if (!m_tiMZElevLoop.Waiting_Time(100)) break;
			g_objAJinAXL.Home_Search(AX_MZ_ELEV_Z);
			m_niMZElevCase++; m_tiMZElevLoop.Set_LoopTime(5000);
		}
		break;
	case 3:		
		if (g_objAJinAXL.Is_Home(AX_MZ_ELEV_Z)) 
		{			
			if (!m_tiMZElevLoop.Waiting_Time(100)) break;
			g_objAJinAXL.Set_EncoderType(AX_MZ_ELEV_Z, 0);	// Inc
			g_objAJinAXL.Set_EncoderType(AX_MZ_ELEV_Z, 1);	// Abs
			m_niMZElevCase++; m_tiMZElevLoop.Set_LoopTime(5000);
			
		}
		break;
	case 4:
		if (!m_tiMZElevLoop.Waiting_Time(100)) break;
		g_objCommon.Move_Position(AX_MZ_ELEV_Z, MZ_Elev_Z::Ready);
		m_niMZElevCase++; m_tiMZElevLoop.Set_LoopTime(5000);
		break;
	case 5:
		if(g_objCommon.Check_Position(AX_MZ_ELEV_Z, MZ_Elev_Z::Ready))
		{
			g_objLogFile.Save_HandlerLog("[Initial Sequence] - MZ Elevator Complete");
			m_niMZElevCase = 90; m_tiMZElevLoop.Set_LoopTime(5000);
		}
		break;

	case 90:	// Initial Complete
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
		if (!m_pDX01->iMZCoatJigExist && m_niTrayPickerCase > 5)  
		{				
			m_niFeederCase++; m_tiFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 4:
		m_niFeederCase++; m_tiFeederLoop.Set_LoopTime(5000);
		break;
	case 5:
		if(m_niTrayPickerCase > 5) // Tray Picker Z Ready Up Complete 
		{
			g_objAJinAXL.Home_Search(AX_FEEDER_Y);
			m_niFeederCase++; m_tiFeederLoop.Set_LoopTime(5000);
		}
		return TRUE;

	case 6:
		if(g_objAJinAXL.Is_Home(AX_FEEDER_Y))
		{
			g_objCommon.Move_Position(AX_FEEDER_Y, Feeder_Y::Ready);
			g_objAJinAXL.Home_Search(AX_FEEDER_X);
			m_niFeederCase++; m_tiFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 7:
		if(g_objAJinAXL.Is_Home(AX_FEEDER_X) && g_objCommon.Check_Position(AX_FEEDER_Y, Feeder_Y::Ready))
		{			
			g_objLogFile.Save_HandlerLog("[Initial Sequence] - Feeder Complete");
			m_niFeederCase = 90; m_tiFeederLoop.Set_LoopTime(5000);
		}
		break;
	case 90:	// Initial Complete
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
		if (!m_pDX01->iTrayPickerExist) 
		{
			g_objAJinAXL.Set_EncoderType(AX_TRAY_PICKER_Z, 0);	// Inc
			g_objAJinAXL.Set_EncoderType(AX_TRAY_PICKER_Z, 1);	// Abs
			m_niTrayPickerCase++; m_tiTrayPickerLoop.Set_LoopTime(5000);
		}
		break;
	case 2:
		g_objAJinAXL.Home_Search(AX_TRAY_PICKER_Z);
		m_niTrayPickerCase++; m_tiTrayPickerLoop.Set_LoopTime(15000);
		break;
	case 3:
		if(g_objAJinAXL.Is_Home(AX_TRAY_PICKER_Z))
		{			
			g_objAJinAXL.Set_EncoderType(AX_TRAY_PICKER_Z, 0);	// Inc
			g_objAJinAXL.Set_EncoderType(AX_TRAY_PICKER_Z, 1);	// Abs
			m_niTrayPickerCase++; m_tiTrayPickerLoop.Set_LoopTime(5000);
		}
		break;
	case 4:
		if(!m_tiTrayPickerLoop.Waiting_Time(100)) break;
		g_objCommon.Move_Position(AX_TRAY_PICKER_Z, Tray_Picker_Z::Ready);
		m_niTrayPickerCase++; m_tiTrayPickerLoop.Set_LoopTime(5000);
		break;
	case 5:
		if(g_objCommon.Check_Position(AX_TRAY_PICKER_Z, Tray_Picker_Z::Ready))
		{
			g_objAJinAXL.Set_EncoderType(AX_TRAY_PICKER_Y, 0);	// Inc
			g_objAJinAXL.Set_EncoderType(AX_TRAY_PICKER_Y, 1);	// Abs
			m_niTrayPickerCase++; m_tiTrayPickerLoop.Set_LoopTime(5000);
		}
		break;
	case 6:
		g_objAJinAXL.Home_Search(AX_TRAY_PICKER_Y);
		m_niTrayPickerCase++; m_tiTrayPickerLoop.Set_LoopTime(5000);
		break;
	case 7:
		if(g_objAJinAXL.Is_Home(AX_TRAY_PICKER_Y))
		{
			g_objAJinAXL.Set_EncoderType(AX_TRAY_PICKER_Y, 0);	// Inc
			g_objAJinAXL.Set_EncoderType(AX_TRAY_PICKER_Y, 1);	// Abs
					
			m_niTrayPickerCase++; m_tiTrayPickerLoop.Set_LoopTime(5000);
		}
		break;
	case 8:
		if(!m_tiTrayPickerLoop.Waiting_Time(100)) break;
		g_objCommon.Move_Position(AX_TRAY_PICKER_Y, Tray_Picker_Y::Ready);
		m_niTrayPickerCase++; m_tiTrayPickerLoop.Set_LoopTime(5000);
	case 9:
		if(g_objCommon.Check_Position(AX_TRAY_PICKER_Y, Tray_Picker_Y::Ready))
		{
			m_niTrayPickerCase++; m_tiTrayPickerLoop.Set_LoopTime(5000);
		}
		break;
	case 10:
		{
			m_pDY01->oTrayPickerSlaveIn = FALSE;
			m_pDY01->oTrayPickerSlaveOut = TRUE;
			m_pDY01->oTrayPickerMasterIn = FALSE;
			m_pDY01->oTrayPickerMasterOut = TRUE;
			g_objAJinAXL.Write_Output(1);
			m_niTrayPickerCase++; m_tiTrayPickerLoop.Set_LoopTime(5000);
		}
		break;
	case 13:		// Tray Picker Slave Out 
		if (!m_pDX01->iTrayPickerSlaveIn && m_pDX01->iTrayPickerSlaveOut) 
		{
			m_niTrayPickerCase++; m_tiTrayPickerLoop.Set_LoopTime(5000);
		}
		break;
	case 14:		// Tray Picker Master Out 
		if (!m_pDX01->iTrayPickerMasterIn && m_pDX01->iTrayPickerMasterOut) 
		{
			g_objLogFile.Save_HandlerLog("[Initial Sequence] - Feeder Complete");
			m_niTrayPickerCase = 90; m_tiTrayPickerLoop.Set_LoopTime(5000);
			
		}
		break;
	case 90:	// Initial Complete
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
			m_niTopInspectorCase++; m_tiTopInspectorLoop.Set_LoopTime(5000);
		}
		break;
	case 2:
		g_objAJinAXL.Home_Search(AX_TOP_INSPECTOR_Z);
		m_niTopInspectorCase++; m_tiTopInspectorLoop.Set_LoopTime(15000);
		break;
	case 3:
		if(g_objAJinAXL.Is_Home(AX_TOP_INSPECTOR_Z))
		{			
			g_objAJinAXL.Set_EncoderType(AX_TOP_INSPECTOR_Z, 0);	// Inc
			g_objAJinAXL.Set_EncoderType(AX_TOP_INSPECTOR_Z, 1);	// Abs
			m_niTopInspectorCase++; m_tiTopInspectorLoop.Set_LoopTime(5000);
		}
		break;
	case 4:
		if(!m_tiTopInspectorLoop.Waiting_Time(100)) break;
		g_objCommon.Move_Position(AX_TOP_INSPECTOR_Z, Top_Inspector_Z::Ready);
		m_niTopInspectorCase++; m_tiTopInspectorLoop.Set_LoopTime(5000);
		break;
	case 5:
		if(g_objCommon.Check_Position(AX_TOP_INSPECTOR_Z, Top_Inspector_Z::Ready))
		{
			m_niTopInspectorCase++; m_tiTopInspectorLoop.Set_LoopTime(5000);
		}
		break;
	case 6:
		g_objAJinAXL.Home_Search(AX_TOP_INSPECTOR_Y);
		m_niTopInspectorCase++; m_tiTopInspectorLoop.Set_LoopTime(5000);
		break;
	case 7:
		if(g_objAJinAXL.Is_Home(AX_TOP_INSPECTOR_Y))
		{			
			m_niTopInspectorCase++; m_tiTopInspectorLoop.Set_LoopTime(5000);
		}
		break;
	case 8:
		g_objCommon.Move_Position(AX_TOP_INSPECTOR_Y, Top_Inspector_Y::Ready);
		m_niTopInspectorCase++; m_tiTopInspectorLoop.Set_LoopTime(5000);
	case 9:
		if(g_objCommon.Check_Position(AX_TOP_INSPECTOR_Y, Top_Inspector_Y::Ready))
		{
			m_niTopInspectorCase++; m_tiTopInspectorLoop.Set_LoopTime(5000);
		}
		break;
	case 10:
		g_objAJinAXL.Home_Search(AX_TOP_INSPECTOR_X);
		m_niTopInspectorCase++; m_tiTopInspectorLoop.Set_LoopTime(15000);
		break;
	case 11:		// Tray Picker Slave Out 
		if(g_objAJinAXL.Is_Home(AX_TOP_INSPECTOR_X))
		{			
			g_objCommon.Move_Position(AX_TOP_INSPECTOR_X, Top_Inspector_X::Ready);
			m_niTopInspectorCase++; m_tiTopInspectorLoop.Set_LoopTime(5000);
		}
		break;
	case 12:
		if(g_objCommon.Check_Position(AX_TOP_INSPECTOR_X, Top_Inspector_X::Ready))
		{
			g_objLogFile.Save_HandlerLog("[Initial Sequence] - Top Inspector Complete");
			m_niTopInspectorCase = 90; m_tiTopInspectorLoop.Set_LoopTime(5000);
		}		

	case 90:	// Initial Complete
		return TRUE;
	}

	// 1. (Error : 1500)
	if (m_tiTopInspectorLoop.Over_LoopTime()) {
		g_objCommon.Show_Error(1500 + m_niTopInspectorCase);
		return FALSE;
	}



	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// 6. (Error : 1600)
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
			m_niBtmInspectorCase++; m_tiBtmInspectorLoop.Set_LoopTime(5000);
		}
		break;
	case 2:
		g_objAJinAXL.Home_Search(AX_BTM_INSPECTOR_Z);
		m_niBtmInspectorCase++; m_tiBtmInspectorLoop.Set_LoopTime(15000);
		break;
	case 3:
		if(g_objAJinAXL.Is_Home(AX_BTM_INSPECTOR_Z))
		{			
			g_objAJinAXL.Set_EncoderType(AX_BTM_INSPECTOR_Z, 0);	// Inc
			g_objAJinAXL.Set_EncoderType(AX_BTM_INSPECTOR_Z, 1);	// Abs
			m_niBtmInspectorCase++; m_tiBtmInspectorLoop.Set_LoopTime(5000);
		}
		break;
	case 4:
		if(!m_tiBtmInspectorLoop.Waiting_Time(100)) break;
		g_objCommon.Move_Position(AX_BTM_INSPECTOR_Z, Btm_Inspector_Z::Ready);
		m_niBtmInspectorCase++; m_tiBtmInspectorLoop.Set_LoopTime(5000);
		break;
	case 5:
		if(g_objCommon.Check_Position(AX_BTM_INSPECTOR_Z, Btm_Inspector_Z::Ready))
		{
			m_niBtmInspectorCase++; m_tiBtmInspectorLoop.Set_LoopTime(5000);
		}
		break;
	case 6:
		g_objAJinAXL.Home_Search(AX_BTM_INSPECTOR_Y);
		m_niBtmInspectorCase++; m_tiBtmInspectorLoop.Set_LoopTime(5000);
		break;
	case 7:
		if(g_objAJinAXL.Is_Home(AX_BTM_INSPECTOR_Y))
		{			
			m_niBtmInspectorCase++; m_tiBtmInspectorLoop.Set_LoopTime(5000);
		}
		break;
	case 8:
		g_objCommon.Move_Position(AX_BTM_INSPECTOR_Y, Btm_Inspector_Y::Ready);
		m_niBtmInspectorCase++; m_tiBtmInspectorLoop.Set_LoopTime(5000);
	case 9:
		if(g_objCommon.Check_Position(AX_BTM_INSPECTOR_Y, Btm_Inspector_Y::Ready))
		{
			m_niBtmInspectorCase++; m_tiBtmInspectorLoop.Set_LoopTime(5000);
		}
		break;
	case 10:
		g_objAJinAXL.Home_Search(AX_BTM_INSPECTOR_X);
		m_niBtmInspectorCase++; m_tiBtmInspectorLoop.Set_LoopTime(15000);
		break;
	case 11:		// Tray Picker Slave Out 
		if(g_objAJinAXL.Is_Home(AX_BTM_INSPECTOR_X))
		{			
			g_objCommon.Move_Position(AX_BTM_INSPECTOR_X, Btm_Inspector_X::Ready);
			m_niBtmInspectorCase++; m_tiBtmInspectorLoop.Set_LoopTime(5000);
		}
		break;
	case 12:
		if(g_objCommon.Check_Position(AX_BTM_INSPECTOR_X, Btm_Inspector_X::Ready))
		{
			g_objLogFile.Save_HandlerLog("[Initial Sequence] - Btm Inspector Complete");
			m_niBtmInspectorCase = 90; m_tiBtmInspectorLoop.Set_LoopTime(5000);
		}		

	case 90:	// Initial Complete
		return TRUE;
	}

	// 1. (Error : 1600)
	if (m_tiBtmInspectorLoop.Over_LoopTime()) {
		g_objCommon.Show_Error(1600 + m_niBtmInspectorCase);
		return FALSE;
	}

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// 7. (Error : 1700)
BOOL CSequenceInit::Initial_Marker()
{
	switch (m_niMarkerCase)
	{
	case 0:
		return TRUE;
	case 1:
		if (1) 
		{
			g_objAJinAXL.Set_EncoderType(AX_MARK_UNIT_Z, 0);	// Inc
			g_objAJinAXL.Set_EncoderType(AX_MARK_UNIT_Z, 1);	// Abs
			m_niMarkerCase++; m_tiMarkerLoop.Set_LoopTime(5000);
		}
		break;
	case 2:
		g_objAJinAXL.Home_Search(AX_MARK_UNIT_Z);
		m_niMarkerCase++; m_tiMarkerLoop.Set_LoopTime(15000);
		break;
	case 3:
		if(g_objAJinAXL.Is_Home(AX_MARK_UNIT_Z))
		{			
			g_objAJinAXL.Set_EncoderType(AX_MARK_UNIT_Z, 0);	// Inc
			g_objAJinAXL.Set_EncoderType(AX_MARK_UNIT_Z, 1);	// Abs
			m_niMarkerCase++; m_tiMarkerLoop.Set_LoopTime(5000);
		}
		break;
	case 4:
		if(!m_tiMarkerLoop.Waiting_Time(100)) break;
		g_objCommon.Move_Position(AX_MARK_UNIT_Z, Marker_Z::Ready);
		m_niMarkerCase++; m_tiMarkerLoop.Set_LoopTime(5000);
		break;
	case 5:
		if(g_objCommon.Check_Position(AX_MARK_UNIT_Z, Marker_Z::Ready))
		{
			m_niMarkerCase++; m_tiMarkerLoop.Set_LoopTime(5000);
		}
		break;
	case 6:
		g_objAJinAXL.Home_Search(AX_MARK_UNIT_Y);
		m_niMarkerCase++; m_tiMarkerLoop.Set_LoopTime(5000);
		break;
	case 7:
		if(g_objAJinAXL.Is_Home(AX_MARK_UNIT_Y))
		{			
			m_niMarkerCase++; m_tiMarkerLoop.Set_LoopTime(5000);
		}
		break;
	case 8:
		g_objCommon.Move_Position(AX_MARK_UNIT_Y, Marker_Y::Ready);
		m_niMarkerCase++; m_tiMarkerLoop.Set_LoopTime(5000);
	case 9:
		if(g_objCommon.Check_Position(AX_MARK_UNIT_Y, Marker_Y::Ready))
		{
			m_niMarkerCase++; m_tiMarkerLoop.Set_LoopTime(5000);
		}
		break;
	case 10:
		g_objAJinAXL.Home_Search(AX_MARK_UNIT_X);
		m_niMarkerCase++; m_tiMarkerLoop.Set_LoopTime(15000);
		break;
	case 11:		// Tray Picker Slave Out 
		if(g_objAJinAXL.Is_Home(AX_MARK_UNIT_X))
		{			
			g_objCommon.Move_Position(AX_MARK_UNIT_X, Marker_X::Ready);
			m_niMarkerCase++; m_tiMarkerLoop.Set_LoopTime(5000);
		}
		break;
	case 12:
		if(g_objCommon.Check_Position(AX_MARK_UNIT_X, Marker_X::Ready))
		{
			g_objLogFile.Save_HandlerLog("[Initial Sequence] - Marker Complete");
			m_niMarkerCase = 90; m_tiMarkerLoop.Set_LoopTime(5000);
		}		

	case 90:	// Initial Complete
		return TRUE;
	}

	// 1. (Error : 1600)
	if (m_tiBtmInspectorLoop.Over_LoopTime()) {
		g_objCommon.Show_Error(1600 + m_niBtmInspectorCase);
		return FALSE;
	}


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

