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
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// 3. (Error : 1300)
BOOL CSequenceInit::Initial_Feeder()
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// 4. (Error : 1400)
BOOL CSequenceInit::Initial_TrayPicker()
{
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

