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
	m_EquipData.sModel = "";
	m_EquipData.nLotBarcodePort = 0;
	m_EquipData.nAssyLoadCellPort = 0;
	m_EquipData.nUnloadLoadCellPort = 0;
	m_EquipData.bUseDoorLock = FALSE;
	m_EquipData.nVendorSelection = 0;


	m_EquipData.bUseMES = FALSE;
	m_EquipData.bUseInlineMode = FALSE;
	m_EquipData.bUseVisionCapDir = FALSE;
	m_EquipData.bUseVisionCmAlign = FALSE;
	m_EquipData.bUseVisionAlignAlarm = FALSE;
	m_EquipData.bUseVisionAlignOffset = FALSE;

	m_EquipData.bUseTrayPickerTurn = FALSE;
	m_EquipData.bUseCapPickerTurn = FALSE;
	m_EquipData.bChkAssyPickerTilt = FALSE;
	m_EquipData.bCapPickUpMulti = FALSE;
	m_EquipData.bUseMesCapReg = FALSE;
	m_EquipData.bUseMesShipReg = FALSE;
	m_EquipData.bUseIndexAssyVac = FALSE;

	m_EquipData.dLoadTrayPitchX = 0.0;
	m_EquipData.dLoadTrayPitchY = 0.0;
	m_EquipData.dCapTrayPitchX = 0.0;
	m_EquipData.dCapTrayPitchY = 0.0;
	m_EquipData.dShipTrayPitchX = 0.0;
	m_EquipData.dShipTrayPitchY = 0.0;
	m_EquipData.dIndexPitch = 0.0;

	for (int i = 0; i < 3; i++) m_EquipData.nVacOffDelay[i] = 0;
	for (int i = 0; i < 6; i++) m_EquipData.nDelayAdd[i] = 0;

	m_EquipData.sAviIp = "0.0.0.0";
	m_EquipData.dAlignOffset = 0.0;
	for (int i = 0; i < 2; i++) m_EquipData.dLoadCellRange[i] = 0.0;	// 0:Min, 1:Max 

	for (int i = 0; i < 6; i++) for (int j = 0; j < 4; j++) m_EquipData.bTower[i][j] = FALSE;
	for (int i = 0; i < 5; i++) for (int j = 0; j < 6; j++) m_EquipData.bBuzzer[i][j] = FALSE;

	m_EquipData.sPasswordMt = "";
	m_EquipData.sPasswordSi = "";

	m_EquipData.nCappingCnt = 0;
	m_EquipData.nLoadCellChkCnt = 0;

	m_EquipData.bResultTestUse = FALSE;
	m_EquipData.nResultTestNg = 0;


	//m_EquipData.sVendor[0] = "DH";
	//m_EquipData.sVendor[1] = "HS";
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
	m_EquipData.sModel = INI.Get_String("EQUIPMENT", "MODEL", "");
	gData.sRecipe = (m_EquipData.sModel == "" ? "R53B" : m_EquipData.sModel);	// Default(R53B)

	m_EquipData.nLotBarcodePort = INI.Get_Integer("EQUIPMENT", "LOT_BARCODE", 1);
	m_EquipData.nAssyLoadCellPort = INI.Get_Integer("EQUIPMENT", "ASSY_LOAD_CELL", 8);
	m_EquipData.nUnloadLoadCellPort = INI.Get_Integer("EQUIPMENT", "UNLOAD_LOAD_CELL", 9);
	m_EquipData.bUseDoorLock = INI.Get_Bool("EQUIPMENT", "DOOR_LOCK", FALSE);
	gData.nDoorLockTime = INI.Get_Integer("EQUIPMENT", "DOOR_LOCK_TIME", 0);
	gAlm.dMotionChkPos		= INI.Get_Double("EQUIPMENT", "MOTION_CHECK", 0.0);

	m_EquipData.bUseMES = INI.Get_Bool("OPTION", "MES_USE", FALSE);
	m_EquipData.bUseInlineMode = INI.Get_Bool("OPTION", "INLINE_MODE", FALSE);

	m_EquipData.nVendorSelection = INI.Get_Integer("EQUIPMENT", "VENDOR_SELECTION", 0);
	m_EquipData.sVendor[0]=INI.Get_String("VENDOR","0", "");
	m_EquipData.sVendor[1]=INI.Get_String("VENDOR","1", "");
	

#ifdef DRY_RUN_TEST
	m_EquipData.bUseVisionCapDir = FALSE;
	m_EquipData.bUseVisionCmAlign = FALSE;
#else
	m_EquipData.bUseVisionCapDir = INI.Get_Bool("OPTION", "VISION_CAP_DIR", FALSE);
	m_EquipData.bUseVisionCmAlign = INI.Get_Bool("OPTION", "VISION_CM_ALIGN", FALSE);
#endif
	m_EquipData.bUseVisionAlignAlarm = INI.Get_Bool("OPTION", "VISION_ALIGN_ALARM", FALSE);
	m_EquipData.bUseVisionAlignOffset = INI.Get_Bool("OPTION", "VISION_ALIGN_OFFSET", FALSE);
		
	m_EquipData.nInspectCmScanTimes = (ST_Y * ST_X) / 4;//INI.Get_Integer("OPTION", "SCAN_TIMES", 10000);	
	m_EquipData.nInspectCmLotTimes = INI.Get_Integer("OPTION", "LOT_TIMES", 10000);
	m_EquipData.nInspectCmMinutes = INI.Get_Integer("OPTION", "MINUTES", 10000);
		
	m_EquipData.bUseTrayPickerTurn = INI.Get_Bool("OPTION", "TRAY_PICKER_TURN", FALSE);
	m_EquipData.bUseCapPickerTurn = INI.Get_Bool("OPTION", "CAP_PICKER_TURN", FALSE);
	m_EquipData.bChkAssyPickerTilt = INI.Get_Bool("OPTION", "ASSY_PICKER_TILT", FALSE);
	m_EquipData.bCapPickUpMulti = INI.Get_Bool("OPTION", "CAP_PICKUP_MULTI", TRUE);

	m_EquipData.bUseMesCapReg = INI.Get_Bool("OPTION", "MES_CAP_REG", FALSE);
	m_EquipData.bUseMesShipReg = INI.Get_Bool("OPTION", "MES_SHIP_REG", FALSE);
	m_EquipData.bUseIndexAssyVac = INI.Get_Bool("OPTION", "INDEX_ASSY_VAC", FALSE);

	m_EquipData.dIndexPitch = INI.Get_Double ("INDEX", "PITCH", 0.0);
	m_EquipData.dLoadTrayPitchX = INI.Get_Double("LOAD_TRAY", "PITCH_X", 0.0);
	m_EquipData.dLoadTrayPitchY = INI.Get_Double("LOAD_TRAY", "PITCH_Y", 0.0);
	m_EquipData.dCapTrayPitchX = INI.Get_Double("CAP_TRAY", "PITCH_X", 0.0);
	m_EquipData.dCapTrayPitchY = INI.Get_Double("CAP_TRAY", "PITCH_Y", 0.0);
	

	for (int i = 0; i < 3; i++) { strKey.Format("%d", i); m_EquipData.nVacOffDelay[i] = INI.Get_Integer("VAC_OFF_DELAY", strKey, 30); }
	for (int i = 0; i < 6; i++) { strKey.Format("%d", i); m_EquipData.nDelayAdd[i] = INI.Get_Integer("DELAY_ADD", strKey, 100); }

	m_EquipData.sAviIp = INI.Get_String("AVI", "AVI_IP", "");
	m_EquipData.dAlignOffset = INI.Get_Double ("VISION_ALIGN", "OFFSET", 0.0);
	m_EquipData.dLoadCellRange[0] = INI.Get_Double ("LOAD_CELL", "MIN", 0.0);
	m_EquipData.dLoadCellRange[1] = INI.Get_Double ("LOAD_CELL", "MAX", 0.0);
	
	for (int i = 0; i < 6; i++) for (int j = 0; j < 4; j++) { strKey.Format("%d%d", i, j); m_EquipData.bTower[i][j] = INI.Get_Bool("TOWER", strKey, FALSE); }
	for (int i = 0; i < 5; i++) for (int j = 0; j < 6; j++) { strKey.Format("%d%d", i, j); m_EquipData.bBuzzer[i][j] = INI.Get_Bool("BUZZER", strKey, FALSE); }

	m_EquipData.sPasswordMt = INI.Get_String("HIDDEN", "PASSWORD_MT", "");
	m_EquipData.sPasswordSi = INI.Get_String("HIDDEN", "PASSWORD_SI", "");

	m_EquipData.nLoadCellChkCnt = INI.Get_Integer("LOAD_CELL", "CHECK_COUNT", 0);
	for (int i = 0; i < PICK; i++) { strKey.Format("%d", i); gData.dAssyLoadCell[i] = INI.Get_Double("ASSY_LOAD_CELL", strKey, 0.0); }

	// Gloval Data
		
	m_EquipData.nResultTestNg = INI.Get_Integer("RESULT_TEST", "RESULT_NG", 0);

	//doorinterlock log

	if (gDoorLock.nOpenStart == 0 && m_EquipData.bUseDoorLock == FALSE)
		g_objLogFile.Save_Interlock(2);
	if (gDoorLock.nOpenStart == 1 && m_EquipData.bUseDoorLock == TRUE) 
		g_objLogFile.Save_Interlock(3);



	CSingleLensDlg *pMainDlg = (CSingleLensDlg*)AfxGetApp()->GetMainWnd();
	pMainDlg->Display_EquipName();

	return TRUE;
}

BOOL CDataManager::Read_MoveData()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\MoveData"+".ini");
	if (!INI.Check_File()) { AfxMessageBox("MoveData.ini File Not Found!!!"); return FALSE; }

	CString strKey;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
