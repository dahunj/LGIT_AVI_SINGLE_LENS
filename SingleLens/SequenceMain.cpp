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
	m_nIndexTableCase	= 0;			
	
}

int *CSequenceMain::Get_pMainRunCase()
{
	static int nMainCase[25] = { 0 };

	nMainCase[ 0] = m_nLoadConveyorCase;	
	nMainCase[ 1] = m_nMZElevCase;			
	nMainCase[ 2] = m_nFeederCase;
	nMainCase[ 3] = m_nTrayPickerCase;		
	nMainCase[ 4] = m_nLensCleanerCase;		
	nMainCase[ 5] = m_nTopInspectCase;	
	nMainCase[ 6] = m_nBtmInspectCase;	
	nMainCase[ 7] = m_nMarkerCase;		
	nMainCase[ 7] = m_nIndexTableCase;		
	return nMainCase;
}

int CSequenceMain::Get_MainRunCase(int nRun)
{
	if		(nRun == AUTO_CONVEYOR)			return m_nLoadConveyorCase;	
	else if (nRun == AUTO_MZ_ElEVATOR)		return m_nMZElevCase;	
	else if (nRun == AUTO_FEEDER)			return m_nFeederCase;		
	else if (nRun == AUTO_TRAY_PICKER)		return m_nTrayPickerCase;		
	else if (nRun == AUTO_LENS_CLEANER)		return m_nLensCleanerCase;	
	else if (nRun == AUTO_TOP_INSPECT)		return m_nTopInspectCase;	
	else if (nRun == AUTO_BTM_INSPECT)		return m_nBtmInspectCase;		
	else if (nRun == AUTO_MARKER)			return m_nMarkerCase;		
	else if (nRun == AUTO_INDEX_TABLE)		return m_nIndexTableCase;	
	

	return 0;
}

void CSequenceMain::Set_MainRunCase(int nRun, int nCase)
{
	if		(nRun == AUTO_CONVEYOR)		m_nLoadConveyorCase	= nCase;	
	else if (nRun == AUTO_MZ_ElEVATOR)		m_nMZElevCase	= nCase;	
	else if (nRun == AUTO_FEEDER)			m_nFeederCase		= nCase;	
	else if (nRun == AUTO_TRAY_PICKER)		m_nTrayPickerCase		= nCase;	
	else if (nRun == AUTO_LENS_CLEANER)		m_nLensCleanerCase	= nCase;	
	else if (nRun == AUTO_TOP_INSPECT)		m_nTopInspectCase	= nCase;	
	else if (nRun == AUTO_BTM_INSPECT)		m_nBtmInspectCase		= nCase;	
	else if (nRun == AUTO_MARKER)			m_nMarkerCase		= nCase;	
	else if (nRun == AUTO_INDEX_TABLE)		m_nIndexTableCase	= nCase;	
}

void CSequenceMain::Set_MainRunLoop(int nRun, int nLoop)
{
	if		(nRun == AUTO_CONVEYOR)			m_nLoadConveyorLoop.Set_LoopTime(nLoop);	
	else if (nRun == AUTO_MZ_ElEVATOR)		m_nMZElevLoop.Set_LoopTime(nLoop);	
	else if (nRun == AUTO_FEEDER)			m_nFeederLoop.Set_LoopTime(nLoop);		
	else if (nRun == AUTO_TRAY_PICKER)		m_nTrayPickerLoop.Set_LoopTime(nLoop);		
	else if (nRun == AUTO_LENS_CLEANER)		m_nLensCleanerLoop.Set_LoopTime(nLoop);	
	else if (nRun == AUTO_TOP_INSPECT)		m_nTopInspectLoop.Set_LoopTime(nLoop);	
	else if (nRun == AUTO_BTM_INSPECT)		m_nBtmInspectLoop.Set_LoopTime(nLoop);		
	else if (nRun == AUTO_MARKER)			m_nMarkerLoop.Set_LoopTime(nLoop);		
	else if (nRun == AUTO_INDEX_TABLE)		m_nIndexTableLoop.Set_LoopTime(nLoop);
	
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


BOOL CSequenceMain::LoadConveyorRun()
{
	return TRUE;
}

BOOL CSequenceMain::MZElevCaseRun()
{
	return TRUE;
}

BOOL CSequenceMain::TrayPickerRun()
{
	return TRUE;
}

BOOL CSequenceMain::LensCleanerRun()
{
	return TRUE;
}

BOOL CSequenceMain::TopInspectorRun()
{
	return TRUE;
}

BOOL CSequenceMain::BtmInspectorRun()
{
	return TRUE;
}

BOOL CSequenceMain::MarkerRun()
{
	return TRUE;
}

BOOL CSequenceMain::IndexTableRun()
{
	return TRUE;
}