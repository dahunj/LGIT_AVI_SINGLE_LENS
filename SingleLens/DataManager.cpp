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

	m_EquipData.nNoWorkTime = 0;

	m_EquipData.bUseMES = FALSE;
	m_EquipData.bUseBarcodeMGZ = FALSE;
	m_EquipData.bUseBarcodeCtZig = FALSE;
	
	m_EquipData.dIndexPitch = 0.0;

	for (int i = 0; i < 3; i++) m_EquipData.nVacOffDelay[i] = 0;
	for (int i = 0; i < 6; i++) m_EquipData.nDelayAdd[i] = 0;

	m_EquipData.sAviIp = "0.0.0.0";
	

	for (int i = 0; i < 6; i++) for (int j = 0; j < 4; j++) m_EquipData.bTower[i][j] = FALSE;
	for (int i = 0; i < 5; i++) for (int j = 0; j < 6; j++) m_EquipData.bBuzzer[i][j] = FALSE;
	
	m_EquipData.bResultTestUse = FALSE;
	m_EquipData.nResultTestNg = 0;

	m_EquipData.nVisionDir = eVDir::fixY;
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

	if(!m_EquipData.sModelName.IsEmpty())
	{
		CString sPathSource;
		sPathSource = gsCurrentDir + "\\System\\Model";
		sPathSource += _T("\\");
		sPathSource += m_EquipData.sModelName;
		sPathSource += _T("\\");

		g_objDataManager.Read_ModelEquipData(sPathSource);		
	}
	
	return TRUE;
}



BOOL CDataManager::Read_ModelEquipData(CString strPath)
{
	CIniFileCS INI(strPath + "EquipData.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("EquipData.ini File Not Found!!!!");
		return FALSE;
	}

	CString strKey;
	m_EquipData.sEquipName = INI.Get_String("EQUIPMENT", "NAME", "");
	m_EquipData.sModelName = INI.Get_String("EQUIPMENT", "MODEL", "");


	CSingleLensDlg *pMainDlg = (CSingleLensDlg*)AfxGetApp()->GetMainWnd();
	pMainDlg->Display_EquipName();


	m_EquipData.nLotBarcodePort = INI.Get_Integer("EQUIPMENT", "LOT_BARCODE", 1);

	m_EquipData.bUseDoorLock = FALSE; //INI.Get_Bool("EQUIPMENT", "DOOR_LOCK", FALSE);
	gData.nDoorLockTime = INI.Get_Integer("EQUIPMENT","DOOR_LOCK_TIME", 0);
	gAlm.dMotionChkPos		= INI.Get_Double("EQUIPMENT","MOTION_CHECK", 0.0);
	m_EquipData.nNoWorkTime = INI.Get_Integer("EQUIPMENT", "NO_WORK_TIME", 0);

	m_EquipData.bUseMES = INI.Get_Bool("OPTION", "MES_USE", FALSE);
	m_EquipData.bUseBarcodeMGZ = INI.Get_Bool("OPTION", "BARCODE_MGZ_USE", FALSE);
	m_EquipData.bUseBarcodeCtZig = INI.Get_Bool("OPTION", "BARCODE_ZIG_USE", FALSE);


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
	m_EquipData.nCleanRepeat = INI.Get_Integer("CLEAN", "REPEAT", 0);
	
	m_EquipData.dTopStartZ	 = INI.Get_Double("TRIGGER",  "TOP_START_Z", 0.00);
	m_EquipData.nTopCount    = INI.Get_Integer("TRIGGER", "TOP_COUNT",	 0);
	m_EquipData.dTopPeriod   = INI.Get_Double("TRIGGER",  "TOP_PERIOD",  0.00);
	m_EquipData.dTopVelocity = INI.Get_Double("TRIGGER",  "TOP_VEL",	 0.00);
	m_EquipData.dTopStartX	 = INI.Get_Double("TRIGGER",  "TOP_START_X", 0.00);
	m_EquipData.dTopStartY   = INI.Get_Double("TRIGGER",  "TOP_START_Y", 0.00);
	m_EquipData.dTopPitchX   = INI.Get_Double("TRIGGER",  "TOP_PITCH_X", 0.00);
	m_EquipData.dTopPitchY	 = INI.Get_Double("TRIGGER",  "TOP_PITCH_Y", 0.00);
	
	m_EquipData.dBtmStartZ	 = INI.Get_Double("TRIGGER",  "BTM_START_Z", 0.00);
	m_EquipData.nBtmCount    = INI.Get_Integer("TRIGGER", "BTM_COUNT",	 0);
	m_EquipData.dBtmPeriod   = INI.Get_Double("TRIGGER",  "BTM_PERIOD",  0.00);
	m_EquipData.dBtmVelocity = INI.Get_Double("TRIGGER",  "BTM_VEL",	 0.00);
	m_EquipData.dBtmStartX	 = INI.Get_Double("TRIGGER",  "BTM_START_X", 0.00);
	m_EquipData.dBtmStartY   = INI.Get_Double("TRIGGER",  "BTM_START_Y", 0.00);
	m_EquipData.dBtmPitchX   = INI.Get_Double("TRIGGER",  "BTM_PITCH_X", 0.00);
	m_EquipData.dBtmPitchY	 = INI.Get_Double("TRIGGER",  "BTM_PITCH_Y", 0.00);

	m_EquipData.bUseTopVision = INI.Get_Bool("OPTION", "TOP_VISION", FALSE);	
	m_EquipData.bUseBtmVision = INI.Get_Bool("OPTION", "BTM_VISION", FALSE);
	m_EquipData.bUseMark = INI.Get_Bool("OPTION", "MARK_USE", FALSE);

	for (int i = 0; i < 6; i++) for (int j = 0; j < 4; j++) { strKey.Format("%d%d", i, j); m_EquipData.bTower[i][j] = INI.Get_Bool("TOWER", strKey, FALSE); }
	for (int i = 0; i < 5; i++) for (int j = 0; j < 6; j++) { strKey.Format("%d%d", i, j); m_EquipData.bBuzzer[i][j] = INI.Get_Bool("BUZZER", strKey, FALSE); }


	m_EquipData.nDelayAdd[0] = INI.Get_Integer("DELAY_ADD", "FEEDER_CLOSE", 100);
	m_EquipData.nDelayAdd[1] = INI.Get_Integer("DELAY_ADD", "FEEDER_OPEN", 100);
	m_EquipData.nDelayAdd[2] = INI.Get_Integer("DELAY_ADD", "TRAY_PICKER_CLOSE", 100);
	m_EquipData.nDelayAdd[3] = INI.Get_Integer("DELAY_ADD", "TRAY_PICKER_OPEN", 100);
	m_EquipData.nDelayAdd[4] = INI.Get_Integer("DELAY_ADD", "INDEX_ALIGN_IN", 100);
	m_EquipData.nDelayAdd[5] = INI.Get_Integer("DELAY_ADD", "INDEX_ALIGN_OUT", 100);
	

	m_EquipData.sPasswordOp = INI.Get_String("HIDDEN", "PASSWORD_OP", "");
	m_EquipData.sPasswordEngr = INI.Get_String("HIDDEN", "PASSWORD_ENGR", "");

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
