// DataManager.cpp: 구현 파일
//
#include "stdafx.h"
#include "SingleLens.h"
#include "DataManager.h"

#include "Common.h"
#include "SingleLensDlg.h"
#include "SequenceMain.h"
#include "LogFile.h"

// CDataManager
CDataManager g_objDataManager;

CDataManager::CDataManager()
{
	Reset_EquipData();
	Reset_MoveData();
}

CDataManager::~CDataManager()
{
}

void CDataManager::Reset_EquipData()
{
	m_EquipData.sEquipName = "";
	m_EquipData.sModelName = "";
	m_EquipData.nLotBarcodePort = 0;

	m_EquipData.bUseDoorLock = FALSE;



	m_EquipData.bUseMES = FALSE;
	
	m_EquipData.dIndexPitch = 0.0;

	for (int i = 0; i < 3; i++) m_EquipData.nVacOffDelay[i] = 0;
	for (int i = 0; i < 6; i++) m_EquipData.nDelayAdd[i] = 0;

	m_EquipData.sAviIp = "0.0.0.0";
	

	for (int i = 0; i < 6; i++) for (int j = 0; j < 4; j++) m_EquipData.bTower[i][j] = FALSE;
	for (int i = 0; i < 5; i++) for (int j = 0; j < 6; j++) m_EquipData.bBuzzer[i][j] = FALSE;
	
	m_EquipData.bResultTestUse = FALSE;
	m_EquipData.nResultTestNg = 0;
}

void CDataManager::Reset_MoveData()
{
	
}

BOOL CDataManager::Read_EquipData()
{
 	CIniFileCS INI(gsCurrentDir + "\\System\\EquipData.ini");
	if (!INI.Check_File()) { AfxMessageBox("EquipData.ini File Not Found!!!"); return FALSE; }

	CString strKey;
	m_EquipData.sEquipName = INI.Get_String("EQUIPMENT", "NAME", "");
	m_EquipData.sModelName = INI.Get_String("EQUIPMENT", "MODEL", "");

	CSingleLensDlg *pMainDlg = (CSingleLensDlg*)AfxGetApp()->GetMainWnd();
	pMainDlg->Display_EquipName();

	
	m_EquipData.nLotBarcodePort = INI.Get_Integer("EQUIPMENT", "LOT_BARCODE", 1);

	m_EquipData.bUseDoorLock = FALSE; //INI.Get_Bool("EQUIPMENT", "DOOR_LOCK", FALSE);
	gData.nDoorLockTime = INI.Get_Integer("EQUIPMENT","DOOR_LOCK_TIME", 0);
	gAlm.dMotionChkPos		= INI.Get_Double("EQUIPMENT","MOTION_CHECK", 0.0);

	m_EquipData.bUseMES = INI.Get_Bool("OPTION", "MES_USE", FALSE);
	

	for (int i = 0; i < 3; i++) { strKey.Format("%d", i); m_EquipData.nVacOffDelay[i] = INI.Get_Integer("VAC_OFF_DELAY", strKey, 30); }
	for (int i = 0; i < 6; i++) { strKey.Format("%d", i); m_EquipData.nDelayAdd[i] = INI.Get_Integer("DELAY_ADD", strKey, 100); }

	m_EquipData.sAviIp = INI.Get_String("AVI", "AVI_IP", "");
	
	//doorinterlock log
	if (gDoorLock.nOpenStart == 0 && m_EquipData.bUseDoorLock == FALSE)
		g_objLogFile.Save_Interlock(2);
	if (gDoorLock.nOpenStart == 1 && m_EquipData.bUseDoorLock == TRUE) 
		g_objLogFile.Save_Interlock(3);

	m_EquipData.nZigArrayX =  INI.Get_Integer("COAT_ZIG", "ARRAY_X", 0); gData.nLensCntX = m_EquipData.nZigArrayX;
	m_EquipData.nZigArrayY =  INI.Get_Integer("COAT_ZIG", "ARRAY_Y", 0); gData.nLensCntY = m_EquipData.nZigArrayY;	
	m_EquipData.dZigPitchX = INI.Get_Double("COAT_ZIG", "PITCH_X", 0.00);
	m_EquipData.dZigPitchY = INI.Get_Double("COAT_ZIG", "PITCH_Y", 0.00);

	m_EquipData.dElevPitchZ = INI.Get_Double("ELEVATOR", "PITCH_Z", 0.00);


	m_EquipData.dTopStart	 = INI.Get_Double("TRIGGER", "TOP_START",   0.00);
	m_EquipData.dTopCount    = INI.Get_Double("TRIGGER", "TOP_COUNT",	 0.00);
	m_EquipData.dTopPeriod   = INI.Get_Double("TRIGGER", "TOP_PERIOD",  0.00);
	m_EquipData.dTopVelocity = INI.Get_Double("TRIGGER", "TOP_VEL",	 0.00);
	m_EquipData.dBtmStart	 = INI.Get_Double("TRIGGER", "BTM_START",   0.00);
	m_EquipData.dBtmCount    = INI.Get_Double("TRIGGER", "BTM_COUNT",	 0.00);
	m_EquipData.dBtmPeriod   = INI.Get_Double("TRIGGER", "BTM_PERIOD",  0.00);
	m_EquipData.dBtmVelocity = INI.Get_Double("TRIGGER", "BTM_VEL",	 0.00);
	
	m_EquipData.bUseTopVision = INI.Get_Bool("OPTION", "TOP_VISION", FALSE);	
	m_EquipData.bUseBtmVision = INI.Get_Bool("OPTION", "BTM_VISION", FALSE);
	
	for (int i = 0; i < 6; i++) for (int j = 0; j < 4; j++) { strKey.Format("%d%d", i, j); m_EquipData.bTower[i][j] = INI.Get_Bool("TOWER", strKey, FALSE); }
	for (int i = 0; i < 5; i++) for (int j = 0; j < 6; j++) { strKey.Format("%d%d", i, j); m_EquipData.bBuzzer[i][j] = INI.Get_Bool("BUZZER", strKey, FALSE); }

	CString strIndex;
	for(int i = 0; i < 6; i++)
	{
		strIndex.Format("%d", i);
		m_EquipData.nDelayAdd[i] = INI.Get_Integer("DELAY_ADD", strIndex, 0);
	}

	m_EquipData.sPasswordOp = INI.Get_String("HIDDEN", "PASSWORD_ENGR", "");
	m_EquipData.sPasswordEngr = INI.Get_String("HIDDEN", "PASSWORD_OP", "");

	// Gloval Data		
	m_EquipData.nResultTestNg = INI.Get_Integer("RESULT_TEST", "RESULT_NG", 0);
	
	return TRUE;
}






BOOL CDataManager::Read_MoveData()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\MoveData"+".ini");
	if (!INI.Check_File()) { AfxMessageBox("MoveData.ini File Not Found!!!"); return FALSE; }

	CString strKey;

	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dMZElevZ[i]				= INI.Get_Double("00_MZ_ELEVATOR_Z", strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dFeederX[i]				= INI.Get_Double("01_ZIG_FEEDER_X", strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dFeederY[i]				= INI.Get_Double("02_ZIG_FEEDER_Y", strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dTrayPickerY[i]			= INI.Get_Double("03_ZIG_PICKER_Y", strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dTrayPickerZ[i]			= INI.Get_Double("04_ZIG_PICKER_Z", strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dTopInspectorX[i]		= INI.Get_Double("05_TOP_INSPECTOR_X", strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dTopInspectorY[i]		= INI.Get_Double("06_TOP_INSPECTOR_Y", strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dTopInspectorZ[i]		= INI.Get_Double("07_TOP_INSPECTOR_Z", strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dBtmInspectorX[i]		= INI.Get_Double("08_BTM_INSPECTOR_X", strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dBtmInspectorY[i]		= INI.Get_Double("09_BTM_INSPECTOR_Y", strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dBtmInspectorZ[i]		= INI.Get_Double("10_BTM_INSPECTOR_Z", strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dMarkUnitX[i]			= INI.Get_Double("11_MARK_UNIT_X", strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dMarkUnitY[i]			= INI.Get_Double("12_MARK_UNIT_Y", strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dMarkUnitZ[i]			= INI.Get_Double("13_MARK_UNIT_Z", strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dMainIndexR[i]			= INI.Get_Double("14_MAIN_INDEX_R", strKey, 0.0); }

	return TRUE;
}




///////////////////////////////////////////////////////////////////////////////
