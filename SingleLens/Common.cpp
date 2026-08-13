// Common.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "SingleLens.h"
#include "Common.h"

#include "LogFile.h"
#include "AJinAXL.h"
#include "DataManager.h"

#include "ErrorDlg.h"
#include "AlarmDlg.h"
#include "MsgBoxDlg.h"
#include "NumPadDlg.h"
#include "KeyPadDlg.h"
#include "PasswordDlg.h"
#include "WorkDlg.h"

#include "SequenceMain.h"

#include <iostream>
#include <string>
#include <fstream>
#include "Wininet.h"

#include <wbemidl.h>
#include <comdef.h>

#pragma comment(lib, "wbemuuid.lib")

// CCommon
CCommon g_objCommon;

IMPLEMENT_DYNAMIC(CCommon, CWnd)

CCriticalSection g_csShowError;
CCriticalSection g_csShowAlarm;
CCriticalSection g_csIndexVacuum;

CCommon::CCommon()
{
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	m_nFreq = freq.QuadPart;
}

CCommon::~CCommon()
{
}

BEGIN_MESSAGE_MAP(CCommon, CWnd)
END_MESSAGE_MAP()

// CCommon 메시지 처리기입니다.

void CCommon::Save_MotionPos()
{
	int nCount = 0;
	for(int i=0; i<AXIS_COUNT; i++) {
		if (i == 3 || i == 11) continue;	// No Axis, Index R Axis
		if(g_objAJinAXL.Is_Done(i)) { gAlm.dMotionPos[i] = g_objAJinAXL.Get_Position(i); }
		else						{ gAlm.dMotionPos[i] = -100.0; nCount++; }
	}
	if (nCount == 0) return;

	theApp.uSleep(1000);
	nCount = 0;
	for(int i=0; i<AXIS_COUNT; i++) {
		if (i == 3 || i == 11) continue;	// No Axis, Index R Axis
		if (gAlm.dMotionPos[i] < -10.0) {
			if(g_objAJinAXL.Is_Done(i)) gAlm.dMotionPos[i] = g_objAJinAXL.Get_Position(i);
			else nCount++;
		}
	}
	if (nCount == 0) return;

	theApp.uSleep(3000);
	for(int i=0; i<AXIS_COUNT; i++) {
		if (i == 3 || i == 11) continue;	// No Axis, Index R Axis
		if (gAlm.dMotionPos[i] < -10.0) {
			if(g_objAJinAXL.Is_Done(i)) gAlm.dMotionPos[i] = g_objAJinAXL.Get_Position(i);
		}
	}
}

int CCommon::Check_MotionPos()
{
	int		nMotionNo = 99;
	double	dCurrentPos, dCheckPos;

	if (gAlm.dMotionChkPos < 0.05) return nMotionNo;

	for(int i=0; i<AXIS_COUNT; i++) {
		if (i == 3 || i == 11) continue;	// No Axis, Index R Axis
		if (gAlm.dMotionPos[i] < -10.0) continue;
		if (!g_objAJinAXL.Is_Done(i)) continue;

		dCheckPos   = gAlm.dMotionPos[i];
		dCurrentPos = g_objAJinAXL.Get_Position(i);
		if (fabs(dCurrentPos - dCheckPos) > gAlm.dMotionChkPos) return i;
	}
	return nMotionNo;
}

BOOL CCommon::Check_Position(int nAxis, int nMoveIdx, double dRange)
{
	double dCurrentPos = g_objAJinAXL.Get_Position(nAxis);
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();

	double dCheckPos = -1.0;

	if (g_objAJinAXL.Is_Done(nAxis))
	{
		if (nAxis == AX_MZ_ELEVATOR_Z)			dCheckPos = pMoveData->dMZElevZ[nMoveIdx];		// AXIS 00
		if (nAxis == AX_ZIG_FEEDER_X)			dCheckPos = pMoveData->dFeederX[nMoveIdx];		// AXIS 01
		if (nAxis == AX_ZIG_FEEDER_Y)			dCheckPos = pMoveData->dFeederY[nMoveIdx];		// AXIS 02
		if (nAxis == AX_ZIG_PICKER_Y)			dCheckPos = pMoveData->dTrayPickerY[nMoveIdx];		// AXIS 04
		if (nAxis == AX_ZIG_PICKER_Z)			dCheckPos = pMoveData->dTrayPickerZ[nMoveIdx];		// AXIS 05
		if (nAxis == AX_TOP_INSPECTOR_X)		dCheckPos = pMoveData->dTopInspectorX[nMoveIdx];		// AXIS 06
		if (nAxis == AX_TOP_INSPECTOR_Y)		dCheckPos = pMoveData->dTopInspectorY[nMoveIdx];		// AXIS 07
		if (nAxis == AX_TOP_INSPECTOR_Z)		dCheckPos = pMoveData->dTopInspectorZ[nMoveIdx];		// AXIS 08
		if (nAxis == AX_BTM_INSPECTOR_X)		dCheckPos = pMoveData->dBtmInspectorX[nMoveIdx];		// AXIS 09
		if (nAxis == AX_BTM_INSPECTOR_Y)		dCheckPos = pMoveData->dBtmInspectorY[nMoveIdx];		// AXIS 00
		if (nAxis == AX_BTM_INSPECTOR_Z)		dCheckPos = pMoveData->dBtmInspectorZ[nMoveIdx];		// AXIS 11
		if (nAxis == AX_MARK_UNIT_X)			dCheckPos = pMoveData->dMarkUnitX[nMoveIdx];		// AXIS 12
		if (nAxis == AX_MARK_UNIT_Y)			dCheckPos = pMoveData->dMarkUnitY[nMoveIdx];		// AXIS 13
		if (nAxis == AX_MARK_UNIT_Z)			dCheckPos = pMoveData->dMarkUnitZ[nMoveIdx];		// AXIS 14
		if (nAxis == AX_MAIN_INDEX_R)			dCheckPos = pMoveData->dMainIndexR[nMoveIdx];		// AXIS 15
		

		if (fabs(dCurrentPos - dCheckPos) < dRange) return TRUE;

	} else return FALSE;

	return FALSE;
}

void CCommon::Move_Position(int nAxis, int nMoveIdx)
{
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();

	double dMovePos = -999.0;

	if (nAxis == AX_MZ_ELEVATOR_Z)			dMovePos = pMoveData->dMZElevZ[nMoveIdx];		// AXIS 00
	if (nAxis == AX_ZIG_FEEDER_X)			dMovePos = pMoveData->dFeederX[nMoveIdx];		// AXIS 01
	if (nAxis == AX_ZIG_FEEDER_Y)			dMovePos = pMoveData->dFeederY[nMoveIdx];		// AXIS 02
	if (nAxis == AX_ZIG_PICKER_Y)			dMovePos = pMoveData->dTrayPickerY[nMoveIdx];		// AXIS 04
	if (nAxis == AX_ZIG_PICKER_Z)			dMovePos = pMoveData->dTrayPickerZ[nMoveIdx];		// AXIS 05
	if (nAxis == AX_TOP_INSPECTOR_X)		dMovePos = pMoveData->dTopInspectorX[nMoveIdx];		// AXIS 06
	if (nAxis == AX_TOP_INSPECTOR_Y)		dMovePos = pMoveData->dTopInspectorY[nMoveIdx];		// AXIS 07
	if (nAxis == AX_TOP_INSPECTOR_Z)		dMovePos = pMoveData->dTopInspectorZ[nMoveIdx];		// AXIS 08
	if (nAxis == AX_BTM_INSPECTOR_X)		dMovePos = pMoveData->dBtmInspectorX[nMoveIdx];		// AXIS 09
	if (nAxis == AX_BTM_INSPECTOR_Y)		dMovePos = pMoveData->dBtmInspectorY[nMoveIdx];		// AXIS 00
	if (nAxis == AX_BTM_INSPECTOR_Z)		dMovePos = pMoveData->dBtmInspectorZ[nMoveIdx];		// AXIS 11
	if (nAxis == AX_MARK_UNIT_X)			dMovePos = pMoveData->dMarkUnitX[nMoveIdx];		// AXIS 12
	if (nAxis == AX_MARK_UNIT_Y)			dMovePos = pMoveData->dMarkUnitY[nMoveIdx];		// AXIS 13
	if (nAxis == AX_MARK_UNIT_Z)			dMovePos = pMoveData->dMarkUnitZ[nMoveIdx];		// AXIS 14
	if (nAxis == AX_MAIN_INDEX_R)			dMovePos = pMoveData->dMainIndexR[nMoveIdx];		// AXIS 15

	if (dMovePos == -999) return;
	g_objAJinAXL.Move_Absolute(nAxis, dMovePos);
}

void CCommon::Show_Error(int nErrNo)
{
	g_csShowError.Lock();
	if (!g_dlgError.IsWindowVisible() && !g_dlgAlarm.IsWindowVisible()) 
	{
		for(int i = 0; i < 7; i++)
		{
			gLot.nErrorCount[i]++;
		}

		g_dlgError.Set_ErrorNumber(nErrNo);
		g_dlgError.ShowWindow(SW_SHOW);
	}
	g_csShowError.Unlock();
}

void CCommon::Set_ErrorSubMessage(CString sErrSubMsg)
{
	g_dlgError.Set_ErrorSubMessage(sErrSubMsg);
}

void CCommon::Show_Alarm(CString sMsg, int nState, BOOL bOn)
{
	g_csShowAlarm.Lock();
	if (bOn) {
		if (!g_dlgError.IsWindowVisible() && !g_dlgAlarm.IsWindowVisible()) {
			g_dlgWork.MachineStopLog("ALARM", sMsg);
			g_dlgAlarm.Set_AlarmMessage(sMsg);
			g_dlgAlarm.Set_AlarmState(nState);
			g_dlgAlarm.ShowWindow(SW_SHOW);
		}
	} else {
		if (!g_dlgError.IsWindowVisible() && g_dlgAlarm.IsWindowVisible()) {
			g_dlgAlarm.ShowWindow(SW_HIDE);
		}
	}
	g_csShowAlarm.Unlock();
}

int CCommon::Show_MsgBox(int nBtnCnt, CString sMsg)
{
	CMsgBoxDlg dlgMsgBox;
	dlgMsgBox.Set_Message(nBtnCnt, sMsg);
	return dlgMsgBox.DoModal();
}

int CCommon::Show_NumPad(CString sOld, CString &sNew, int nAxis)
{
	CNumPadDlg dlgNumPad;
	dlgNumPad.Set_OldValue(sOld, nAxis);
	if (dlgNumPad.DoModal() != IDOK) return IDCANCEL;

	sNew = g_strReturnNumPad;
	return IDOK;
}

int CCommon::Show_KeyPad(CString &sKey)
{
	CKeyPadDlg dlgKeyPad;
	if (dlgKeyPad.DoModal() != IDOK) return IDCANCEL;

	sKey = g_strReturnKeyPad;
	return IDOK;
}

int CCommon::Show_Password(int &nUser)
{
	CPasswordDlg dlgPassword;
	if (dlgPassword.DoModal() != IDOK) return IDCANCEL;

	nUser = g_nLoginUser;
	return IDOK;
}

BOOL CCommon::Check_MainEmgAir()
{
#ifdef AJIN_BOARD_USE
	DX_DATA_03 *pDX03 = g_objAJinAXL.Get_pDX03();
	if (pDX03->iEmgSw1)		{ Show_Error(1); return FALSE; }
	if (pDX03->iEmgSw2)		{ Show_Error(2); return FALSE; }
	if (pDX03->iEmgSw3)		{ Show_Error(3); return FALSE; }
	if (pDX03->iEmgSw4)		{ Show_Error(4); return FALSE; }
	if (!pDX03->iMainAir1)	{ Show_Error(7); return FALSE; }
	
#endif
	return TRUE;
}

BOOL CCommon::Check_MainDoor(BOOL bAuto)
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

#ifdef AJIN_BOARD_USE
	DX_DATA_03 *pDX03 = g_objAJinAXL.Get_pDX03();

	if (!pEquipData->bUseDoorLock) 
	{		
		//Don't Check Door when Unlocked 
		//if (pDX03->iDoor01UnlockFront1) { Show_Alarm("Main 01번 Door(X0322) Opened."); return FALSE; }
		//if (pDX03->iDoor02UnlockFront2) { Show_Alarm("Main 02번 Door(X0323) Opened."); return FALSE; }
	} 
	else
	{
		if (!pEquipData->bUseDoorLock) return TRUE;

		// temp
		if (pDX03->iDoor01Unlock )						{ Show_Alarm("Main 01번 Door(X0322) Opened."); return FALSE; }
		if (pDX03->iDoor02Unlock)							{ Show_Alarm("Main 02번 Door(X0323) Opened."); return FALSE; }
		if (pDX03->iDoor03Unlock && !gData.bUnloadOpenSW)	{ Show_Alarm("Main 03번 Door(X0324) Opened."); return FALSE; }
		if (pDX03->iDoor04Unlock)							{ Show_Alarm("Main 04번 Door(X0325) Opened."); return FALSE; }
		if (pDX03->iDoor05Unlock)							{ Show_Alarm("Main 05번 Door(X0326) Opened."); return FALSE; }
		if (pDX03->iDoor06Unlock)							{ Show_Alarm("Main 06번 Door(X0327) Opened."); return FALSE; }
		if (pDX03->iDoor07Unlock && !gData.bLoadOpenSW)	{ Show_Alarm("Main 07번 Door(X0328) Opened."); return FALSE; }
		if (pDX03->iDoor08Unlock)							{ Show_Alarm("Main 08번 Door(X0329) Opened."); return FALSE; }		
	}
#endif
	return TRUE;
}


BOOL CCommon::Check_TrayFull()
{
#ifdef AJIN_BOARD_USE
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();
	DX_DATA_03 *pDX03 = g_objAJinAXL.Get_pDX03();

	
#endif
	return TRUE;
}



// Servo On Error : Error (100 - 145)
BOOL CCommon::Check_ServoOn()
{
#ifdef AJIN_BOARD_USE
	for (int i = 0; i < AXIS_COUNT; i++) {
		if (i == 3) continue;
		if (!g_objAJinAXL.Get_ServoOn(i)) { Show_Error(i + 100); return FALSE; }
	}
#endif
	return TRUE;
}

// Drive Alarm : Error(200 - 245)
BOOL CCommon::Check_DirveAlarm()
{
#ifdef AJIN_BOARD_USE
	for (int i = 0; i < AXIS_COUNT; i++) {
		if (i == 3) continue;
		if (g_objAJinAXL.Get_AmpAlarm(i)) { Show_Error(i + 200); return FALSE; }
	}
#endif
	return TRUE;
}

// Limit Check : Error ELN(300 - 345), ELP(400 - 445)
BOOL CCommon::Check_EndLimit()
{
#ifdef AJIN_BOARD_USE
	for (int i = 0; i < AXIS_COUNT; i++) {
		if (g_objAJinAXL.Use_OrgAxis(i)) continue;
		if (g_objAJinAXL.Get_EndLimitPos(i)) { Show_Error(i + 300); return FALSE; }
		if (g_objAJinAXL.Get_EndLimitNeg(i)) { Show_Error(i + 400); return FALSE; }
	}
#endif
	return TRUE;
}

// Home Check : Error (500 - 545)
BOOL CCommon::Check_HomeDone()
{
#ifdef AJIN_BOARD_USE
	for (int i = 0; i < AXIS_COUNT; i++) {
		
 		//if (i == AX_MAIN_INDEX_R && g_objSequenceMain.Get_MainRunCase(AUTO_MAIN_INDEX) > 20) continue;
		if (!g_objAJinAXL.Get_HomeDone(i)) { Show_Error(i + 500); return FALSE; }
	}
#endif
	return TRUE;
}

void CCommon::Locking_MainDoor(BOOL bLock, BOOL bAuto)
{
	DY_DATA_03 *pDY03 = g_objAJinAXL.Get_pDY03();

	// 0000 0000 0000 1111 1111 1111 1111 1111
	// 0    0    0    F    F    F    F    F
	if (bLock) 
	{
		pDY03->oDoor01Unlock = FALSE;
		pDY03->oDoor02Unlock = FALSE;
		pDY03->oDoor03Unlock = FALSE;
		pDY03->oDoor04Unlock = FALSE;
		pDY03->oDoor05Unlock = FALSE;
		pDY03->oDoor06Unlock = FALSE;
		pDY03->oDoor07Unlock = FALSE;
		pDY03->oDoor08Unlock = FALSE;
		
		if(bAuto && gData.bLoadOpenSW) pDY03->oDoor08Unlock = TRUE;
		if(bAuto && gData.bUnloadOpenSW) pDY03->oDoor03Unlock = TRUE;
	} 
	else
	{
		DWORD dwStart = GetTickCount();
		while (TRUE) {
			BOOL bMove = FALSE;
			for (int i = 0; i < AXIS_COUNT; i++) {
				if (!g_objAJinAXL.Is_Done(i)) { bMove = TRUE; break; }
			}
			if (!bMove) break;
			if (GetTickCount() - dwStart > 5000) break;	// 5초
			theApp.DoEvents();
		}
		pDY03->oDoor01Unlock = TRUE;
		pDY03->oDoor02Unlock = TRUE;
		pDY03->oDoor03Unlock = TRUE;
		pDY03->oDoor04Unlock = TRUE;
		pDY03->oDoor05Unlock = TRUE;
		pDY03->oDoor06Unlock = TRUE;
		pDY03->oDoor07Unlock = TRUE;
		pDY03->oDoor08Unlock = TRUE;
		
	}
	g_objAJinAXL.Write_Output(3);

}


/////////////////////////////////////////////////////////////////////////////

int CCommon::Get_Random(int nStart, int nEnd)
{
	static BOOL bSeed = FALSE;
	if (nStart >= nEnd) return 0;
	if (!bSeed) { srand((unsigned)time(NULL)); bSeed = TRUE; }
	return (rand() % (nEnd - nStart + 1) + nStart);
}

void CCommon::Backup_File(CString strPath, CString strName)
{
	g_objLogFile.Create_Folder(strPath + "\\Backup");

	CString strOriginFile, strTargetFile, strDateTime;

	SYSTEMTIME time;
	GetLocalTime(&time);
	strDateTime.Format("%04d%02d%02d_%02d%02d%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);

	strOriginFile.Format("%s\\%s.ini", strPath, strName);
	strTargetFile.Format("%s\\Backup\\%s_%s.ini", strPath, strName, strDateTime);

	if (!CopyFile(strOriginFile, strTargetFile, FALSE)) return;
}
///////////////////////////////////////////////////////////////



void CCommon::Get_HardInfo(CString &strHardDisk)
{
	ULARGE_INTEGER freeBytesAvailable, totalBytes, totalFreeBytes;

	// GetDiskFreeSpaceEx 호출
	if (GetDiskFreeSpaceEx("C:\\", &freeBytesAvailable, &totalBytes, &totalFreeBytes)) {
		// GB로 변환하여 출력
		double totalGB = static_cast<double>(totalBytes.QuadPart) / (1024 * 1024 * 1024);
		double freeGB = static_cast<double>(totalFreeBytes.QuadPart) / (1024 * 1024 * 1024);
		double usedGB = totalGB - freeGB;

		strHardDisk.Format("%lf", freeGB);
	}
}

void CCommon::Get_RAMSize(CString &strRAM)
{
	ULONGLONG Size;
	GetPhysicallyInstalledSystemMemory(&Size);
	strRAM.Format(_T("%llu"), ((Size/1024)/1024));
}

void CCommon::Get_CPUInfo(CString& strCPU)
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	HKEY hKey;	
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"), 0, KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		char buffer[256];
		DWORD bufferSize = sizeof(buffer);
		if (RegQueryValueEx(hKey, _T("ProcessorNameString"), NULL, NULL, (LPBYTE)buffer, &bufferSize) == ERROR_SUCCESS)
		{
			strCPU = (CString)buffer;
		}
		RegCloseKey(hKey);
	}

	switch (sysInfo.wProcessorArchitecture) {
	case PROCESSOR_ARCHITECTURE_AMD64: strCPU += " x64";  break;
	case PROCESSOR_ARCHITECTURE_INTEL: strCPU += " x86"; break;
	default:  strCPU += " Unknown"; break;
	}   
}


////////////////////////////////////////////////


void CCommon::Set_LdStopper1Up()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();

	pDY00->oLdCVStpr1UpR = TRUE;
	pDY00->oLdCVStpr1Dn = FALSE;
	g_objAJinAXL.Write_Output(0);

}

void CCommon::Set_LdStopper1Down()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();

	pDY00->oLdCVStpr1UpR = FALSE;
	pDY00->oLdCVStpr1Dn = TRUE;
	g_objAJinAXL.Write_Output(0);

}

BOOL CCommon::Get_LdStopper1Up()
{
	
	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();

	if(pDX00->iLdCVStpr1UpR && !pDX00->iLdCVStpr1Dn)
	{
		return TRUE;
	}
	return FALSE;	
}

BOOL CCommon::Get_LdStopper1Down()
{
	

	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();

	if(!pDX00->iLdCVStpr1UpR && pDX00->iLdCVStpr1Dn)
	{
		return TRUE;
	}
	return FALSE;	
}

void CCommon::Set_LdStopper2Up()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();

	pDY00->oLdCVStpr2Up = TRUE;
	pDY00->oLdCVStpr2Dn = FALSE;
	g_objAJinAXL.Write_Output(0);

}

void CCommon::Set_LdStopper2Down()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();

	pDY00->oLdCVStpr2Up = FALSE;
	pDY00->oLdCVStpr2Dn = TRUE;
	g_objAJinAXL.Write_Output(0);

}



BOOL CCommon::Get_LdStopper2Up()
{
	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();


	if(pDX00->iLdCVLift2Up && !pDX00->iLdCVLift2Dn)
	{
		return TRUE;
	}
	return FALSE;	
}


BOOL CCommon::Get_LdStopper2Down()
{
	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();

	

	if(!pDX00->iLdCVLift2Up && pDX00->iLdCVLift2Dn)
	{
		return TRUE;
	}
	return FALSE;	
}




/////////////
void CCommon::Set_ElevLift1In()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();

	pDY00->oElvStpr1In = TRUE;
	pDY00->oElvStpr1Out = FALSE;
	g_objAJinAXL.Write_Output(0);

}

void CCommon::Set_ElevLift1Out()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();

	pDY00->oElvStpr1In = FALSE;
	pDY00->oElvStpr1Out = TRUE;
	g_objAJinAXL.Write_Output(0);
}

void CCommon::Set_ElevLift1Up()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();

	pDY00->oElvStpr1UpL = TRUE;
	pDY00->oElvStpr1Dn = FALSE;
	g_objAJinAXL.Write_Output(0);

}

void CCommon::Set_ElevLift1Down()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();

	pDY00->oElvStpr1UpL = FALSE;
	pDY00->oElvStpr1Dn = TRUE;
	g_objAJinAXL.Write_Output(0);

}

BOOL CCommon::Get_ElevLift1In()
{
	if(gData.bAgingMode) return TRUE;

	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();

	if(pDX00->iElvLift1In && !pDX00->iElvLift1Out)
	{
		return TRUE;
	}
	return FALSE;	
}

BOOL CCommon::Get_ElevLift1Out()
{
	if(gData.bAgingMode) return TRUE;

	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();

	if(!pDX00->iElvLift1In && pDX00->iElvLift1Out)
	{
		return TRUE;
	}
	return FALSE;	
}


BOOL CCommon::Get_ElevLift1Up()
{
	if(gData.bAgingMode) return TRUE;

	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();

	if(pDX00->iElvLift1UpL && !pDX00->iElvLift1Dn)
	{
		return TRUE;
	}
	return FALSE;	
}


BOOL CCommon::Get_ElevLift1Down()
{
	if(gData.bAgingMode) return TRUE;

	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();

	if(!pDX00->iElvLift1UpL && pDX00->iElvLift1Dn)
	{
		return TRUE;
	}
	return FALSE;	

}
//////////////////////////////


//////////////////////
void CCommon::Set_ElevLift2In()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();

	pDY00->oElvStpr2In = TRUE;
	pDY00->oElvStpr2Out = FALSE;
	g_objAJinAXL.Write_Output(0);

}

void CCommon::Set_ElevLift2Out()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();

	pDY00->oElvStpr2In = FALSE;
	pDY00->oElvStpr2Out = TRUE;
	g_objAJinAXL.Write_Output(0);
}

void CCommon::Set_ElevLift2Up()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();

	pDY00->oElvStpr2UpR = TRUE;
	pDY00->oElvStpr2Dn = FALSE;
	g_objAJinAXL.Write_Output(0);

}

void CCommon::Set_ElevLift2Down()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();

	pDY00->oElvStpr2UpR = FALSE;
	pDY00->oElvStpr2Dn = TRUE;
	g_objAJinAXL.Write_Output(0);

}

BOOL CCommon::Get_ElevLift2In()
{
	if(gData.bAgingMode || gData.bSimulMode) return TRUE;

	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();

	if(pDX00->iElvLift2In && !pDX00->iElvLift2Out)
	{
		return TRUE;
	}
	return FALSE;	
}

BOOL CCommon::Get_ElevLift2Out()
{
	if(gData.bAgingMode) return TRUE;

	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();

	if(!pDX00->iElvLift2In && pDX00->iElvLift2Out)
	{
		return TRUE;
	}
	return FALSE;	
}


BOOL CCommon::Get_ElevLift2Up()
{
	if(gData.bAgingMode|| gData.bSimulMode) return TRUE;

	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();

	if(pDX00->iElvLift2UpR && !pDX00->iElvLift2Dn)
	{
		return TRUE;
	}
	return FALSE;	
}


BOOL CCommon::Get_ElevLift2Down()
{
	if(gData.bAgingMode) return TRUE;

	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();

	if(!pDX00->iElvLift2UpR && pDX00->iElvLift2Dn)
	{
		return TRUE;
	}
	return FALSE;	

}

//////////////////////////////


void CCommon::Set_IndexLoadAlignIn()
{
	DY_DATA_02 *pDY02 = g_objAJinAXL.Get_pDY02();

	pDY02->oMainIndexZigAlignIn = TRUE;
	pDY02->oMainIndexZigAlignOut = FALSE;
	g_objAJinAXL.Write_Output(2);

}

void CCommon::Set_IndexLoadAlignOut()
{
	DY_DATA_02 *pDY02 = g_objAJinAXL.Get_pDY02();

	pDY02->oMainIndexZigAlignIn = FALSE;
	pDY02->oMainIndexZigAlignOut = TRUE;
	g_objAJinAXL.Write_Output(2);

}



//---------------Get--------------

BOOL CCommon::Get_IndexLoadAlignIn()
{
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();
		
	if(pDX02->iMainIndexZigAlignIn && !pDX02->iMainIndexZigAlignOut)
	{
		return TRUE;
	}
	return FALSE;	
}

BOOL CCommon::Get_IndexLoadAlignOut()
{
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();

	if(!pDX02->iMainIndexZigAlignIn && pDX02->iMainIndexZigAlignOut)
	{
		return TRUE;
	}
	return FALSE;	
}

void CCommon::Set_CleanerClose()
{
	DY_DATA_02 *pDY02 = g_objAJinAXL.Get_pDY02();
	pDY02->oCleanerTopDn = TRUE; pDY02->oCleanerTopUp = FALSE;
	pDY02->oCleanerBtmUp = TRUE; pDY02->oCleanerBtmDn = FALSE;
	g_objAJinAXL.Write_Output(2);
}

void CCommon::Set_CleanerOpen()
{
	DY_DATA_02 *pDY02 = g_objAJinAXL.Get_pDY02();
	pDY02->oCleanerTopDn = FALSE; pDY02->oCleanerTopUp = TRUE;
	pDY02->oCleanerBtmUp = FALSE; pDY02->oCleanerBtmDn = TRUE;
	g_objAJinAXL.Write_Output(2);
}

BOOL CCommon::Get_CleanerClose()
{
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();

	if(pDX02->iCleanerTopDn && !pDX02->iCleanerTopUp
		&& !pDX02->iCleanerBtmDn && pDX02->iCleanerBtmUp)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CCommon::Get_CleanerOpen()
{
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();

	if(!pDX02->iCleanerTopDn && pDX02->iCleanerTopUp
		&& pDX02->iCleanerBtmDn && !pDX02->iCleanerBtmUp)
	{
		return TRUE;
	}
	return FALSE;
}




//////////////////////////////////////////////////////////////////////////
void CCommon::Set_CleanerForward()
{
	DY_DATA_02 *pDY02 = g_objAJinAXL.Get_pDY02();
	pDY02->oCleanerTopFwd = TRUE; pDY02->oCleanerTopBwd = FALSE;
	pDY02->oCleanerBtmFwd = TRUE; pDY02->oCleanerBtmBwd = FALSE;
	g_objAJinAXL.Write_Output(2);
}

void CCommon::Set_CleanerBackward()
{
	DY_DATA_02 *pDY02 = g_objAJinAXL.Get_pDY02();
	pDY02->oCleanerTopFwd = FALSE; pDY02->oCleanerTopBwd = TRUE;
	pDY02->oCleanerBtmFwd = FALSE; pDY02->oCleanerBtmBwd = TRUE;
	g_objAJinAXL.Write_Output(2);
}

BOOL CCommon::Get_CleanerForwardDone()
{
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();
	if(pDX02->iCleanerBtmFwd && !pDX02->iCleanerBtmBwd
		&& pDX02->iCleanerTopFwd && !pDX02->iCleanerTopBwd)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CCommon::Get_CleanerBackwardDone()
{
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();
	if(!pDX02->iCleanerBtmFwd && pDX02->iCleanerBtmBwd
		&& !pDX02->iCleanerTopFwd && pDX02->iCleanerTopBwd)
	{
		return TRUE;
	}
	return FALSE;
}



void CCommon::Set_LoadCVRunCCW()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();
	pDY00->oLoadCVRun = TRUE;
	pDY00->oLoadCVDirCCW = FALSE;

	g_objAJinAXL.Write_Output(0);
}

void CCommon::Set_LoadCVRunCW()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();
	pDY00->oLoadCVRun = TRUE;
	pDY00->oLoadCVDirCCW = TRUE;

	g_objAJinAXL.Write_Output(0);
}

void CCommon::Set_LoadCVStop()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();
	pDY00->oLoadCVRun = FALSE;
	pDY00->oLoadCVDirCCW = FALSE;

	g_objAJinAXL.Write_Output(0);
}



void CCommon::Set_UnloadCVRunCCW()
{
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();
	pDY01->oUldCvRun = TRUE;
	pDY01->oUldCvDirCCW = FALSE;

	g_objAJinAXL.Write_Output(1);
}

void CCommon::Set_UnloadCVRunCW()
{
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();
	pDY01->oUldCvRun = TRUE;
	pDY01->oUldCvDirCCW = TRUE;

	g_objAJinAXL.Write_Output(1);
}

void CCommon::Set_UnloadCVStop()
{
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();
	pDY01->oUldCvRun = FALSE;
	pDY01->oUldCvDirCCW = FALSE;

	g_objAJinAXL.Write_Output(1);
}

void CCommon::Set_ElevCVRunCCW()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();
	pDY00->oElvCvRun = TRUE;
	pDY00->oElvCvDirCCW = FALSE;
	g_objAJinAXL.Write_Output(0);
}

void CCommon::Set_ElevCVRunCW()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();
	pDY00->oElvCvRun = TRUE;
	pDY00->oElvCvDirCCW = TRUE;
	g_objAJinAXL.Write_Output(0);
}

void CCommon::Set_ElevCVStop()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();
	pDY00->oElvCvRun = FALSE;
	pDY00->oElvCvDirCCW = FALSE;
	g_objAJinAXL.Write_Output(0);
}

void CCommon::Set_TrayPickMasterIn()
{
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();
	pDY01->oZigPickerMasterIn = TRUE; pDY01->oZigPickerMasterOut = FALSE;
	g_objAJinAXL.Write_Output(1);
}

void CCommon::Set_TrayPickSlaveIn()
{
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();
	pDY01->oZigPickerSlaveIn = TRUE; pDY01->oZigPickerSlaveOut = FALSE;
	g_objAJinAXL.Write_Output(1);
}

BOOL CCommon::Get_TrayPickMasterIn()
{
	if(gData.bAgingMode || gData.bSimulMode) return TRUE;
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if(pDX01->iZigPickerMasterIn && !pDX01->iZigPickerMasterOut)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CCommon::Get_TrayPickSlaveIn()
{
	if(gData.bAgingMode || gData.bSimulMode) return TRUE;
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if(pDX01->iZigPickerSlaveIn && !pDX01->iZigPickerSlaveOut)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CCommon::Get_TrayPickMasterSlaveIn()
{
	if(gData.bAgingMode || gData.bSimulMode) return TRUE;
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if(pDX01->iZigPickerMasterIn && !pDX01->iZigPickerMasterOut
		&& pDX01->iZigPickerSlaveIn && !pDX01->iZigPickerSlaveOut)
	{
		return TRUE;
	}
	return FALSE;
}

void CCommon::Set_TrayPickMasterOut()
{
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();
	pDY01->oZigPickerMasterIn = FALSE; pDY01->oZigPickerMasterOut = TRUE;
	g_objAJinAXL.Write_Output(1);
}
void CCommon::Set_TrayPickSlaveOut()
{
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();
	pDY01->oZigPickerSlaveIn = FALSE; pDY01->oZigPickerSlaveOut = TRUE;
	g_objAJinAXL.Write_Output(1);
}

BOOL CCommon::Get_TrayPickMasterOut()
{
	if(gData.bAgingMode || gData.bSimulMode) return TRUE;
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if(!pDX01->iZigPickerMasterIn && pDX01->iZigPickerMasterOut)
	{
		return TRUE;
	}
	return FALSE;
}
BOOL CCommon::Get_TrayPickSlaveOut()
{
	if(gData.bAgingMode || gData.bSimulMode) return TRUE;
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if(!pDX01->iZigPickerSlaveIn && pDX01->iZigPickerSlaveOut)
	{
		return TRUE;
	}
	return FALSE;
}
BOOL CCommon::Get_TrayPickMasterSlaveOut()
{
	if(gData.bAgingMode || gData.bSimulMode) return TRUE;
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if(!pDX01->iZigPickerMasterIn && pDX01->iZigPickerMasterOut
		&& !pDX01->iZigPickerSlaveIn && pDX01->iZigPickerSlaveOut)
	{
		return TRUE;
	}
	return FALSE;
}

void CCommon::Set_FeederClose()
{
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();
	pDY01->oFeederGripOpen = FALSE; pDY01->oFeederGripClose = TRUE;
	g_objAJinAXL.Write_Output(1);
}

void CCommon::Set_FeederOpen()
{	
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();
	pDY01->oFeederGripOpen = TRUE; pDY01->oFeederGripClose = FALSE;
	g_objAJinAXL.Write_Output(1);
}

BOOL CCommon::Get_FeederClose()
{
	if(gData.bAgingMode || gData.bSimulMode) return TRUE;

	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if(!pDX01->iFeederGripOpen && pDX01->iFeederGripClose)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CCommon::Get_FeederOpen()
{
	if(gData.bAgingMode || gData.bSimulMode) return TRUE;

	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if(pDX01->iFeederGripOpen && !pDX01->iFeederGripClose)
	{
		return TRUE;
	}
	return FALSE;
}





void CCommon::Set_RailAlignIn()
{
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();
	pDY01->oRailZigAlignIn = TRUE; pDY01->oRailZigAlignOut = FALSE;
	g_objAJinAXL.Write_Output(1);
}

void CCommon::Set_RailAlignOut()
{
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();
	pDY01->oRailZigAlignIn = FALSE; pDY01->oRailZigAlignOut = TRUE;
	g_objAJinAXL.Write_Output(1);
}

BOOL CCommon::Get_RailAlignIn()
{
	if(gData.bAgingMode || gData.bSimulMode) return TRUE;
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if(pDX01->iRailZigAlignIn && !pDX01->iRailZigAlignOut)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CCommon::Get_RailAlignOut()
{
	if(gData.bAgingMode || gData.bSimulMode) return TRUE;
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if(!pDX01->iRailZigAlignIn && pDX01->iRailZigAlignOut)
	{
		return TRUE;
	}
	return FALSE;
}



bool CCommon::IsEmptyPocket(int oldNo)
{
	return oldNo == 32 || oldNo == 68 || oldNo == 113;
}


int CCommon::ConvertToMESNo(int nAVINo)
{
	const int ROWS = 16;
	const int COLS = 9;

	if (nAVINo < 1 || nAVINo > 144)
		return -1;

	if (IsEmptyPocket(nAVINo))
		return 0;

	int colBase[COLS] =
	{
		1, 17, 33, 49, 65, 78, 94, 110, 126
	};

	int row = (nAVINo - 1) / COLS;   // 0~15, 위에서 아래
	int col = (nAVINo - 1) % COLS;   // 0~8

	int offset = 0;

	// 아래쪽부터 위로 올라가면서 빈 포켓은 건너뜀
	for (int r = ROWS - 1; r >= 0; r--)
	{
		int checkOldNo = r * COLS + col + 1;

		if (IsEmptyPocket(checkOldNo))
			continue;

		if (r == row)
			return colBase[col] + offset;

		offset++;
	}

	return -1;
}


int CCommon::ConvertToAVINo(int nMESNo)
{
	const int ROWS = 16;
	const int COLS = 9;

	int colBase[COLS] =
	{
		1, 17, 33, 49, 65, 78, 94, 110, 126
	};

	if (nMESNo < 1 || nMESNo > 141)
		return -1;

	for (int col = 0; col < COLS; col++)
	{
		int offset = 0;

		for (int row = ROWS - 1; row >= 0; row--)
		{
			int oldNo = row * COLS + col + 1;

			if (IsEmptyPocket(oldNo))
				continue;

			int checkNewNo = colBase[col] + offset;

			if (checkNewNo == nMESNo)
				return oldNo;

			offset++;
		}
	}

	return -1;
}

int CCommon::Get_TablePocketNo()
{
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();

	int	nIndexPos = 0;
	if      (!pDX02->iIndexPosBit0 &&  !pDX02->iIndexPosBit1 && !pDX02->iIndexPosBit2) nIndexPos = 1;
	else if ( pDX02->iIndexPosBit0 &&  !pDX02->iIndexPosBit1 && !pDX02->iIndexPosBit2) nIndexPos = 2;
	else if (!pDX02->iIndexPosBit0 &&   pDX02->iIndexPosBit1 && !pDX02->iIndexPosBit2) nIndexPos = 3;
	else if ( pDX02->iIndexPosBit0 &&   pDX02->iIndexPosBit1 && !pDX02->iIndexPosBit2) nIndexPos = 4;
	else if (!pDX02->iIndexPosBit0 &&  !pDX02->iIndexPosBit1 &&  pDX02->iIndexPosBit2) nIndexPos = 5;
	else if ( pDX02->iIndexPosBit0 &&  !pDX02->iIndexPosBit1 &&  pDX02->iIndexPosBit2) nIndexPos = 6;
	else if (!pDX02->iIndexPosBit0 &&   pDX02->iIndexPosBit1 &&  pDX02->iIndexPosBit2) nIndexPos = 7;
	else if ( pDX02->iIndexPosBit0 &&   pDX02->iIndexPosBit1 &&  pDX02->iIndexPosBit2) nIndexPos = 8;

	gData.nIndexPos = nIndexPos;

	gData.nIndexPos = gData.nIndexPos - 1;
	if(gData.nIndexPos == 0) gData.nIndexPos= 8;

	return gData.nIndexPos;
}