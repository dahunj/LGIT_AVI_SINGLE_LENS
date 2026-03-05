#include "StdAfx.h"
#include "SingleLens.h"
#include "SingleLensDlg.h"
#include "SequenceMain.h"


CSequenceMain g_objSequenceMain;


CSequenceMain::CSequenceMain(void)
{
}


CSequenceMain::~CSequenceMain(void)
{
}


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