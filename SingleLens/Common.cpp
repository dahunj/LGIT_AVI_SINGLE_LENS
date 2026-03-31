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

	if (g_objAJinAXL.Is_Done(nAxis)) {
		//if (nAxis == AX_TRAY_PICKER_X)		dCheckPos = pMoveData->dTrayPickerX[nMoveIdx];		// AXIS 00
		//if (nAxis == AX_TRAY_PICKER_Z)		dCheckPos = pMoveData->dTrayPickerZ[nMoveIdx];		// AXIS 01
		//if (nAxis == AX_TRAY_PICKER_R)		dCheckPos = pMoveData->dTrayPickerR[nMoveIdx];		// AXIS 02
		//if (nAxis == AX_LOAD_STAGE1_X)		dCheckPos = pMoveData->dLoadStage1X[nMoveIdx];		// AXIS 04
		//if (nAxis == AX_LOAD_STAGE1_Z)		dCheckPos = pMoveData->dLoadStage1Z[nMoveIdx];		// AXIS 05
		//if (nAxis == AX_LOAD_STAGE2_X)		dCheckPos = pMoveData->dLoadStage2X[nMoveIdx];		// AXIS 06
		//if (nAxis == AX_LOAD_STAGE2_Z)		dCheckPos = pMoveData->dLoadStage2Z[nMoveIdx];		// AXIS 07
		//if (nAxis == AX_LOAD_PICKER_Y)		dCheckPos = pMoveData->dLoadPickerY[nMoveIdx];		// AXIS 08
		//if (nAxis == AX_LOAD_PICKER_Z)		dCheckPos = pMoveData->dLoadPickerZ[nMoveIdx];		// AXIS 09
		//if (nAxis == AX_LOAD_PICKER_P)		dCheckPos = pMoveData->dLoadPickerP[nMoveIdx];		// AXIS 00
		//if (nAxis == AX_MAIN_INDEX_R)		dCheckPos = pMoveData->dMainIndexR[nMoveIdx];		// AXIS 11
		//if (nAxis == AX_VISION_CM_X)		dCheckPos = pMoveData->dVisionCmX[nMoveIdx];		// AXIS 12
		//if (nAxis == AX_CAP_STAGE1_X)		dCheckPos = pMoveData->dCapStage1X[nMoveIdx];		// AXIS 13
		//if (nAxis == AX_CAP_STAGE1_Z)		dCheckPos = pMoveData->dCapStage1Z[nMoveIdx];		// AXIS 14
		//if (nAxis == AX_CAP_STAGE2_X)		dCheckPos = pMoveData->dCapStage2X[nMoveIdx];		// AXIS 15
		//if (nAxis == AX_CAP_STAGE2_Z)		dCheckPos = pMoveData->dCapStage2Z[nMoveIdx];		// AXIS 16
		//if (nAxis == AX_CAP_PICKER_Y)		dCheckPos = pMoveData->dCapPickerY[nMoveIdx];		// AXIS 17
		//if (nAxis == AX_CAP_PICKER_Z)		dCheckPos = pMoveData->dCapPickerZ[nMoveIdx];		// AXIS 18
		//if (nAxis == AX_CAP_PICKER_P)		dCheckPos = pMoveData->dCapPickerP[nMoveIdx];		// AXIS 19
		//if (nAxis == AX_CAP_BUFFER_Y)		dCheckPos = pMoveData->dCapBufferY[nMoveIdx];		// AXIS 10
		//if (nAxis == AX_VISION_CAP_Y)		dCheckPos = pMoveData->dVisionCapY[nMoveIdx];		// AXIS 21
		//if (nAxis == AX_ASSY_PICKER_X)		dCheckPos = pMoveData->dAssyPickerX[nMoveIdx];		// AXIS 22
		//if (nAxis == AX_ASSY_PICKER_Y)		dCheckPos = pMoveData->dAssyPickerY[nMoveIdx];		// AXIS 23
		//if (nAxis == AX_ASSY_PICKER_Z)		dCheckPos = pMoveData->dAssyPickerZ[nMoveIdx];		// AXIS 24
		//if (nAxis == AX_TRANS_STAGE_X)		dCheckPos = pMoveData->dTransStageX[nMoveIdx];		// AXIS 25
		//if (nAxis == AX_TRANS_STAGE_Z)		dCheckPos = pMoveData->dTransStageZ[nMoveIdx];		// AXIS 26
		//if (nAxis == AX_TRANS_STAGE_T)		dCheckPos = pMoveData->dTransStageT[nMoveIdx];		// AXIS 27
		//if (nAxis == AX_UNLOAD_PICKER_X)	dCheckPos = pMoveData->dUnloadPickerX[nMoveIdx];	// AXIS 28
		//if (nAxis == AX_UNLOAD_PICKER_Z)	dCheckPos = pMoveData->dUnloadPickerZ[nMoveIdx];	// AXIS 29
		//if (nAxis == AX_UNLOAD_PICKER_P)	dCheckPos = pMoveData->dUnloadPickerP[nMoveIdx];	// AXIS 20
		//if (nAxis == AX_UNLOAD_STAGE1_Y)	dCheckPos = pMoveData->dUnloadStage1Y[nMoveIdx];	// AXIS 31
		//if (nAxis == AX_UNLOAD_STAGE1_Z)	dCheckPos = pMoveData->dUnloadStage1Z[nMoveIdx];	// AXIS 32
		//if (nAxis == AX_UNLOAD_STAGE2_Y)	dCheckPos = pMoveData->dUnloadStage2Y[nMoveIdx];	// AXIS 33
		//if (nAxis == AX_UNLOAD_STAGE2_Z)	dCheckPos = pMoveData->dUnloadStage2Z[nMoveIdx];	// AXIS 34

		if (fabs(dCurrentPos - dCheckPos) < dRange) return TRUE;

	} else return FALSE;

	return FALSE;
}

void CCommon::Move_Position(int nAxis, int nMoveIdx)
{
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();

	double dMovePos = -999.0;

	//if (nAxis == AX_TRAY_PICKER_X)			dMovePos = pMoveData->dTrayPickerX[nMoveIdx];		// AXIS 00
	//if (nAxis == AX_TRAY_PICKER_Z)			dMovePos = pMoveData->dTrayPickerZ[nMoveIdx];		// AXIS 01
	//if (nAxis == AX_TRAY_PICKER_R)			dMovePos = pMoveData->dTrayPickerR[nMoveIdx];		// AXIS 02
	//if (nAxis == AX_LOAD_STAGE1_X)			dMovePos = pMoveData->dLoadStage1X[nMoveIdx];		// AXIS 04
	//if (nAxis == AX_LOAD_STAGE1_Z)			dMovePos = pMoveData->dLoadStage1Z[nMoveIdx];		// AXIS 05
	//if (nAxis == AX_LOAD_STAGE2_X)			dMovePos = pMoveData->dLoadStage2X[nMoveIdx];		// AXIS 06
	//if (nAxis == AX_LOAD_STAGE2_Z)			dMovePos = pMoveData->dLoadStage2Z[nMoveIdx];		// AXIS 07
	//if (nAxis == AX_LOAD_PICKER_Y)			dMovePos = pMoveData->dLoadPickerY[nMoveIdx];		// AXIS 08
	//if (nAxis == AX_LOAD_PICKER_Z)			dMovePos = pMoveData->dLoadPickerZ[nMoveIdx];		// AXIS 09
	//if (nAxis == AX_LOAD_PICKER_P)			dMovePos = pMoveData->dLoadPickerP[nMoveIdx];		// AXIS 00
	//if (nAxis == AX_MAIN_INDEX_R)			dMovePos = pMoveData->dMainIndexR[nMoveIdx];		// AXIS 11
	//if (nAxis == AX_VISION_CM_X)			dMovePos = pMoveData->dVisionCmX[nMoveIdx];			// AXIS 12
	//if (nAxis == AX_CAP_STAGE1_X)			dMovePos = pMoveData->dCapStage1X[nMoveIdx];		// AXIS 13
	//if (nAxis == AX_CAP_STAGE1_Z)			dMovePos = pMoveData->dCapStage1Z[nMoveIdx];		// AXIS 14
	//if (nAxis == AX_CAP_STAGE2_X)			dMovePos = pMoveData->dCapStage2X[nMoveIdx];		// AXIS 15
	//if (nAxis == AX_CAP_STAGE2_Z)			dMovePos = pMoveData->dCapStage2Z[nMoveIdx];		// AXIS 16
	//if (nAxis == AX_CAP_PICKER_Y)			dMovePos = pMoveData->dCapPickerY[nMoveIdx];		// AXIS 17
	//if (nAxis == AX_CAP_PICKER_Z)			dMovePos = pMoveData->dCapPickerZ[nMoveIdx];		// AXIS 18
	//if (nAxis == AX_CAP_PICKER_P)			dMovePos = pMoveData->dCapPickerP[nMoveIdx];		// AXIS 19
	//if (nAxis == AX_CAP_BUFFER_Y)			dMovePos = pMoveData->dCapBufferY[nMoveIdx];		// AXIS 10
	//if (nAxis == AX_VISION_CAP_Y)			dMovePos = pMoveData->dVisionCapY[nMoveIdx];		// AXIS 21
	//if (nAxis == AX_ASSY_PICKER_X)			dMovePos = pMoveData->dAssyPickerX[nMoveIdx];		// AXIS 22
	//if (nAxis == AX_ASSY_PICKER_Y)			dMovePos = pMoveData->dAssyPickerY[nMoveIdx];		// AXIS 23
	//if (nAxis == AX_ASSY_PICKER_Z)			dMovePos = pMoveData->dAssyPickerZ[nMoveIdx];		// AXIS 24
	//if (nAxis == AX_TRANS_STAGE_X)			dMovePos = pMoveData->dTransStageX[nMoveIdx];		// AXIS 25
	//if (nAxis == AX_TRANS_STAGE_Z)			dMovePos = pMoveData->dTransStageZ[nMoveIdx];		// AXIS 26
	//if (nAxis == AX_TRANS_STAGE_T)			dMovePos = pMoveData->dTransStageT[nMoveIdx];		// AXIS 27
	//if (nAxis == AX_UNLOAD_PICKER_X)		dMovePos = pMoveData->dUnloadPickerX[nMoveIdx];		// AXIS 28
	//if (nAxis == AX_UNLOAD_PICKER_Z)		dMovePos = pMoveData->dUnloadPickerZ[nMoveIdx];		// AXIS 29
	//if (nAxis == AX_UNLOAD_PICKER_P)		dMovePos = pMoveData->dUnloadPickerP[nMoveIdx];		// AXIS 20
	//if (nAxis == AX_UNLOAD_STAGE1_Y)		dMovePos = pMoveData->dUnloadStage1Y[nMoveIdx];		// AXIS 31
	//if (nAxis == AX_UNLOAD_STAGE1_Z)		dMovePos = pMoveData->dUnloadStage1Z[nMoveIdx];		// AXIS 32
	//if (nAxis == AX_UNLOAD_STAGE2_Y)		dMovePos = pMoveData->dUnloadStage2Y[nMoveIdx];		// AXIS 33
	//if (nAxis == AX_UNLOAD_STAGE2_Z)		dMovePos = pMoveData->dUnloadStage2Z[nMoveIdx];		// AXIS 34

	if (dMovePos == -999) return;
	g_objAJinAXL.Move_Absolute(nAxis, dMovePos);
}

void CCommon::Show_Error(int nErrNo)
{
	g_csShowError.Lock();
	if (!g_dlgError.IsWindowVisible() && !g_dlgAlarm.IsWindowVisible()) {
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
	DX_DATA_12 *pDX12 = g_objAJinAXL.Get_pDX12();
	if (pDX12->iEmgSw1)		{ Show_Error(1); return FALSE; }
	if (pDX12->iEmgSw2)		{ Show_Error(2); return FALSE; }
	if (pDX12->iEmgSw3)		{ Show_Error(3); return FALSE; }
	if (!pDX12->iMainAir1)	{ Show_Error(7); return FALSE; }
	if (!pDX12->iMainAir2)	{ Show_Error(8); return FALSE; }
#endif
	return TRUE;
}

BOOL CCommon::Check_MainDoor(BOOL bAuto)
{
#ifdef DRY_RUN_TEST
	return TRUE;
#endif
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

#ifdef AJIN_BOARD_USE
	DX_DATA_13 *pDX13 = g_objAJinAXL.Get_pDX13();
	BOOL bLoad1 = g_objSequenceMain.Get_LotLoadEnable(0);
	BOOL bLoad2 = g_objSequenceMain.Get_LotLoadEnable(1);

// 	if ((!bAuto || !bLoad) && pDX13->iDoor04Unlock) { Show_Alarm("Main 04번 Door(X1019) Unlocked."); return FALSE; }

	if (pEquipData->bUseInlineMode && !pEquipData->bUseDoorLock) {
		// Inline 모드는 도어락 사용 안해도 무조건 Load Port쪽 확인한다.
		if (pDX13->iDoor01Open) { Show_Alarm("Main 01번 Door(X1300) Opened."); return FALSE; }
		if (pDX13->iDoor02Open) { Show_Alarm("Main 02번 Door(X1301) Opened."); return FALSE; }

	} else {
		if (!pEquipData->bUseDoorLock) return TRUE;

		// temp
		if (pDX13->iDoor01Open && !bLoad1)					{ Show_Alarm("Main 01번 Door(X1300) Opened."); return FALSE; }
		if (pDX13->iDoor02Open && !bLoad2)					{ Show_Alarm("Main 02번 Door(X1301) Opened."); return FALSE; }
		if (pDX13->iDoor03Open)								{ Show_Alarm("Main 03번 Door(X1302) Opened."); return FALSE; }
		if (pDX13->iDoor04Open && !gData.bLoadPort3Wait)	{ Show_Alarm("Main 04번 Door(X1303) Opened."); return FALSE; }
		if (pDX13->iDoor05Open && !gData.bUnloadPort2Wait)	{ Show_Alarm("Main 05번 Door(X1304) Opened."); return FALSE; }
		if (pDX13->iDoor06Open && !gData.bUnloadPort2Wait)	{ Show_Alarm("Main 06번 Door(X1305) Opened."); return FALSE; }
		if (pDX13->iDoor07Open)								{ Show_Alarm("Main 07번 Door(X1306) Opened."); return FALSE; }
		if (pDX13->iDoor08Open)								{ Show_Alarm("Main 08번 Door(X1307) Opened."); return FALSE; }
		if (pDX13->iDoor09Open)								{ Show_Alarm("Main 09번 Door(X1308) Opened."); return FALSE; }
		if (pDX13->iDoor10Open && !gData.bUnloadPort1Wait)	{ Show_Alarm("Main 10번 Door(X1309) Opened."); return FALSE; }
		if (pDX13->iDoor11Open && !gData.bCapPort1Wait)		{ Show_Alarm("Main 11번 Door(X1310) Opened."); return FALSE; }
		if (pDX13->iDoor12Open && !gData.bCapPort2Wait)		{ Show_Alarm("Main 12번 Door(X1311) Opened."); return FALSE; }
		if (pDX13->iDoor13Open)								{ Show_Alarm("Main 13번 Door(X1312) Opened."); return FALSE; }
	}
#endif
	return TRUE;
}

BOOL CCommon::Check_PortArea(BOOL bAuto)
{
	// 슬라이드를 사용하지 않고 손을 장비안으로 넣어 트레이 적재 및 배출을 하기 때문에 사용하지 않는다.
	return TRUE;
#ifdef DRY_RUN_TEST
	return TRUE;
#endif
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (!bAuto)	return TRUE;

#ifdef AJIN_BOARD_USE
	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();
	DX_DATA_03 *pDX03 = g_objAJinAXL.Get_pDX03();
	BOOL bLoad1 = g_objSequenceMain.Get_LotLoadEnable(0);
	BOOL bLoad2 = g_objSequenceMain.Get_LotLoadEnable(1);

	if (pEquipData->bUseInlineMode && !pEquipData->bUseDoorLock) {
		// Inline 모드는 도어락 사용 안해도 무조건 Load Port쪽 확인한다.
		if (!pDX01->iLoadPortAreaCheck) { Show_Alarm("Load Port Area(X0115) 감지 되었습니다."); return FALSE; }

	} else {
		if (!pEquipData->bUseDoorLock) return TRUE;

		if (!pDX01->iLoadPortAreaCheck && (pDX00->iLoadPort1SlideOpen || pDX00->iLoadPort1SlideClose)) {
			Show_Alarm("Load Port Area(X0115) 감지 되었습니다."); return FALSE;
		}

		if (!pDX01->iLoadPortAreaCheck && (pDX01->iLoadPort2SlideOpen || pDX01->iLoadPort2SlideClose)) {
			Show_Alarm("Load Port Area(X0115) 감지 되었습니다."); return FALSE;
		}

		if (!pDX01->iLoadPort3AreaCheck && !gData.bLoadPort3Wait) {
			Show_Alarm("Load Port Area(X0131) 감지 되었습니다."); return FALSE;
		}

		if (!pDX02->iCapPortAreaCheck	&& (pDX02->iCapPort1SlideOpen || pDX02->iCapPort1SlideClose)) {
			Show_Alarm("Cap Port Area(X0231) 감지 되었습니다."); return FALSE;
		}

		if (!pDX02->iCapPortAreaCheck	&& (pDX02->iCapPort2SlideOpen || pDX02->iCapPort2SlideClose)) {
			Show_Alarm("Cap Port Area(X0231) 감지 되었습니다."); return FALSE;
		}

		if (!pDX03->iUnloadPort1AreaCheck && (pDX03->iUnloadPort1SlideOpen || pDX03->iUnloadPort1SlideClose)) {
			Show_Alarm("Unload Port1 Area(X0315) 감지 되었습니다."); return FALSE;
		}

		if (!pDX03->iUnloadPort2AreaCheck && (pDX03->iUnloadPort2SlideOpen || pDX03->iUnloadPort2SlideClose)) {
			Show_Alarm("Unload Port2 Area(X0331) 감지 되었습니다."); return FALSE;
		}
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

	if (pDX01->iLoadPort3HighCheck)		
	{ 
		Show_MsgBox(1,"Load Port3 Full Sensor Checked.");
		//Show_Alarm("Load Port3 Full Sensor Checked.");
		return FALSE; 
	}
	if (pDX02->iCapPort1HighCheck)		
	{ 
		Show_MsgBox(1,"Cap Port1 Full Sensor Checked.");
		//Show_Alarm("Cap Port1 Full Sensor Checked.", STATE_CAPTRAY);
		return FALSE;
	}
	if (pDX02->iCapPort2HighCheck)		
	{ 
		Show_MsgBox(1,"Cap Port2 Full Sensor Checked.");
		//Show_Alarm("Cap Port1 Full Sensor Checked.", STATE_CAPTRAY);
		return FALSE;
	}
	if (pDX03->iUnloadPort1HighCheck)	
	{ 
		Show_MsgBox(1,"Unload Port1 Full Sensor Checked.");
		//Show_Alarm("Unload Port2 Full Sensor Checked.", STATE_SHIPTRAY); 
		return FALSE;
	}
	if (pDX03->iUnloadPort2HighCheck)	
	{ 
		Show_MsgBox(1,"Unload Port2 Full Sensor Checked.");
		//Show_Alarm("Unload Port2 Full Sensor Checked.", STATE_SHIPTRAY); 
		return FALSE;
	}
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
		if (i == AX_NO_AXIS) continue;
 		if (i == AX_MAIN_INDEX_R && g_objSequenceMain.Get_MainRunCase(AUTO_MAIN_INDEX) > 20) continue;
		if (!g_objAJinAXL.Get_HomeDone(i)) { Show_Error(i + 500); return FALSE; }
	}
#endif
	return TRUE;
}

void CCommon::Locking_MainDoor(BOOL bLock, BOOL bAuto)
{
	

}

void CCommon::Locking_PortSlide(BOOL bLock, int nPart)
{
	
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


void CCommon::Save_CapShiipData(int nType)	//1:Cap, 2:Ship
{
	CIniFileCS INI(gsCurrentDir + "\\System\\CapShipData.ini");

	if (nType == 1) {
		INI.Set_String("CAP_DATA", "LOTID", gData.sCapLotID);
		/*INI.Set_Integer("CAP_DATA", "TRAYCOUNT", gData.nCapTrayUseCount);
		INI.Set_Integer("CAP_DATA", "CMCOUNT", gData.nCapUseCount);*/
		INI.Set_Integer("CAP_DATA", "USETYCOUNT", gData.nCapTrayCount);
	}
	if (nType == 2) {
		INI.Set_String("SHIP_DATA", "LOTID", gData.sShipLotID);
		/*INI.Set_Integer("SHIP_DATA", "TRAYCOUNT", gData.nShipTrayUseCount);
		INI.Set_Integer("SHIP_DATA", "CMCOUNT", gData.nShipUseCount);
		INI.Set_Integer("SHIP_DATA", "USETYCOUNT", gData.nShipTrayCount);*/
	}
}


void CCommon::Read_CapShipPartNo()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\CapShipPartNo.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("CapShipPartNo.ini File Not Found!!!");
		gPart.nCapCount = gPart.nShipCount = 0;
		return;
	}

	CString sName;
	gPart.nCapCount = INI.Get_Integer("CAP_PARTNO", "COUNT", 0);
	for(int i=0; i<gPart.nCapCount; i++) {
		sName.Format("%02d", i+1);
		gPart.sCapPart[i] = INI.Get_String("CAP_PARTNO", sName, "");
		if (gPart.sCapPart[i].GetLength() < 1) gPart.sCapPart[i] = "????";
	}
	gPart.nShipCount = INI.Get_Integer("SHIP_PARTNO", "COUNT", 0);
	for(int i=0; i<gPart.nShipCount; i++) {
		sName.Format("%02d", i+1);
		gPart.sShipPart[i] = INI.Get_String("SHIP_PARTNO", sName, "");
		if (gPart.sShipPart[i].GetLength() < 1) gPart.sShipPart[i] = "????";
	}
}

BOOL CCommon::Check_CapShipPartNo(int nType, CString sPartNo)	//1:Cap, 2:Ship
{
	if (nType != 1 && nType != 2) return FALSE;
	if (sPartNo.GetLength() < 4) return FALSE;

	int nSize;
	if (nType == 1) {
		for(int i=0; i<gPart.nCapCount; i++) {
			nSize = gPart.sCapPart[i].GetLength();
			if (sPartNo.Left(nSize) == gPart.sCapPart[i]) return TRUE;
		}
	}

	if (nType == 2) {
		for(int i=0; i<gPart.nShipCount; i++) {
			nSize = gPart.sShipPart[i].GetLength();
			if (sPartNo.Left(nSize) == gPart.sShipPart[i]) return TRUE;
		}
	}
	return FALSE;
}


//////////////////////////////
void CCommon::Set_IndexLoadAlignIn()
{
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();

	pDY01->oIndexTInOutAlignIn = TRUE;
	pDY01->oIndexTInOutAlignOut = FALSE;
	g_objAJinAXL.Write_Output(1);

}

void CCommon::Set_IndexLoadAlignOut()
{
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();

	pDY01->oIndexTInOutAlignIn = FALSE;
	pDY01->oIndexTInOutAlignOut = TRUE;
	g_objAJinAXL.Write_Output(1);

}

void CCommon::Set_IndexCleanAlignIn()
{
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();

	pDY01->oIndexTCleanerAlignIn = TRUE;
	pDY01->oIndexTCleanerAlignOut = FALSE;
	g_objAJinAXL.Write_Output(1);

}

void CCommon::Set_IndexCleanAlignOut()
{
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();

	pDY01->oIndexTCleanerAlignIn = FALSE;
	pDY01->oIndexTCleanerAlignOut = TRUE;
	g_objAJinAXL.Write_Output(1);

}

void CCommon::Set_IndexTopAlignIn()
{
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();

	pDY01->oIndexTInOutAlignIn = TRUE;
	pDY01->oIndexTInOutAlignOut = FALSE;
	g_objAJinAXL.Write_Output(1);

}

void CCommon::Set_IndexTopAlignOut()
{
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();

	pDY01->oIndexTInOutAlignIn = FALSE;
	pDY01->oIndexTInOutAlignOut = TRUE;
	g_objAJinAXL.Write_Output(1);

}

void CCommon::Set_IndexBtmAlignIn()
{
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();

	pDY01->oIndexTInOutAlignIn = TRUE;
	pDY01->oIndexTInOutAlignOut = FALSE;
	g_objAJinAXL.Write_Output(1);

}

void CCommon::Set_IndexBtmAlignOut()
{
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();

	pDY01->oIndexTInOutAlignIn = FALSE;
	pDY01->oIndexTInOutAlignOut = TRUE;
	g_objAJinAXL.Write_Output(1);

}

void CCommon::Set_IndexMarkAlignIn()
{
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();

	pDY01->oIndexTInOutAlignIn = TRUE;
	pDY01->oIndexTInOutAlignOut = FALSE;
	g_objAJinAXL.Write_Output(1);

}

void CCommon::Set_IndexMarkAlignOut()
{
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();

	pDY01->oIndexTInOutAlignIn = FALSE;
	pDY01->oIndexTInOutAlignOut = TRUE;
	g_objAJinAXL.Write_Output(1);

}


//---------------Get--------------

BOOL CCommon::Get_IndexLoadAlignIn()
{
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
		
	if(pDX01->iIndexTInOutAlignIn && !pDX01->iIndexTInOutAlignOut)
	{
		return TRUE;
	}
	return FALSE;	
}

BOOL CCommon::Get_IndexLoadAlignOut()
{
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if(!pDX01->iIndexTInOutAlignIn && pDX01->iIndexTInOutAlignOut)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CCommon::Get_IndexCleanAlignIn()
{
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if(pDX01->iIndexTCleanerAlignIn && !pDX01->iIndexTCleanerAlignOut)
	{
		return TRUE;
	}
	return FALSE;

}

BOOL CCommon::Get_IndexCleanAlignOut()
{
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if(!pDX01->iIndexTCleanerAlignIn && pDX01->iIndexTCleanerAlignOut)
	{
		return TRUE;
	}
	return FALSE;

}

BOOL CCommon::Get_IndexTopAlignIn()
{
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if(pDX01->iIndexTTopAlignIn && !pDX01->iIndexTTopAlignOut)
	{
		return TRUE;
	}
	return FALSE;

}

BOOL CCommon::Get_IndexTopAlignOut()
{
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if(pDX01->iIndexTTopAlignIn && !pDX01->iIndexTTopAlignOut)
	{
		return TRUE;
	}
	return FALSE;

}

BOOL CCommon::Get_IndexBtmAlignIn()
{
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if(pDX01->iIndexTBtmAlignIn && !pDX01->iIndexTBtmAlignOut)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CCommon::Get_IndexBtmAlignOut()
{
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if(pDX01->iIndexTBtmAlignIn && !pDX01->iIndexTBtmAlignOut)
	{
		return TRUE;
	}
	return FALSE;

}

BOOL CCommon::Get_IndexMarkAlignIn()
{
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if(pDX01->iIndexTMarkAlignIn && !pDX01->iIndexTMarkAlignOut)
	{
		return TRUE;
	}
	return FALSE;

}

BOOL CCommon::Get_IndexMarkAlignOut()
{
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if(pDX01->iIndexTMarkAlignIn && !pDX01->iIndexTMarkAlignOut)
	{
		return TRUE;
	}
	return FALSE;

}

void CCommon::Set_CleanerClose()
{
	DY_DATA_02 *pDY02 = g_objAJinAXL.Get_pDY02();
	pDY02->oLensCleannerTopDown = TRUE; pDY02->oLensCleannerTopUp = FALSE;
	pDY02->oLensCleannerBtmUp = TRUE; pDY02->oLensCleannerBtmDown = FALSE;
	g_objAJinAXL.Write_Output(2);
}

void CCommon::Set_CleanerOpen()
{
	DY_DATA_02 *pDY02 = g_objAJinAXL.Get_pDY02();
	pDY02->oLensCleannerTopDown = FALSE; pDY02->oLensCleannerTopUp = TRUE;
	pDY02->oLensCleannerBtmUp = FALSE; pDY02->oLensCleannerBtmDown = TRUE;
	g_objAJinAXL.Write_Output(2);
}

BOOL CCommon::Get_CleanerClose()
{
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();

	if(pDX02->iLensCleanerDown && !pDX02->iLensCleanerUp)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CCommon::Get_CleanerOpen()
{
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();
	if(!pDX02->iLensCleanerDown && pDX02->iLensCleanerUp)
	{
		return TRUE;
	}
	return FALSE;
}




//////////////////////////////////////////////////////////////////////////
void CCommon::Set_CleanerForward()
{
	DY_DATA_02 *pDY02 = g_objAJinAXL.Get_pDY02();
	pDY02->oLensCleannerTopForward = TRUE; pDY02->oLensCleannerTopBackward = FALSE;
	pDY02->oLensCleannerBtmForward = TRUE; pDY02->oLensCleannerBtmBackward = FALSE;
	g_objAJinAXL.Write_Output(2);
}

void CCommon::Set_CleanerBackward()
{
	DY_DATA_02 *pDY02 = g_objAJinAXL.Get_pDY02();
	pDY02->oLensCleannerTopForward = FALSE; pDY02->oLensCleannerTopBackward = TRUE;
	pDY02->oLensCleannerBtmForward = FALSE; pDY02->oLensCleannerBtmBackward = TRUE;
	g_objAJinAXL.Write_Output(2);
}

BOOL CCommon::Get_CleanerForwardDone()
{
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();

	if(pDX02->iLensCleanerForward && !pDX02->iLensCleanerBackward)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CCommon::Get_CleanerBackwardDone()
{
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();
	if(!pDX02->iLensCleanerForward && pDX02->iLensCleanerBackward)
	{
		return TRUE;
	}
	return FALSE;
}



void CCommon::Set_LoadCVRunCCW()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();
	pDY00->oLoadCVCCW = TRUE;
	pDY00->oLoadCVCW = FALSE;

	g_objAJinAXL.Write_Output(0);
}

void CCommon::Set_LoadCVRunCW()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();
	pDY00->oLoadCVCCW = TRUE;
	pDY00->oLoadCVCW = TRUE;

	g_objAJinAXL.Write_Output(0);
}

void CCommon::Set_LoadCVStop()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();
	pDY00->oLoadCVCCW = FALSE;
	pDY00->oLoadCVCW = FALSE;

	g_objAJinAXL.Write_Output(0);
}



void CCommon::Set_UnloadCVRunCCW()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();
	pDY00->oUnloadCVCCW = TRUE;
	pDY00->oUnloadCVCW = FALSE;

	g_objAJinAXL.Write_Output(0);
}

void CCommon::Set_UnloadCVRunCW()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();
	pDY00->oUnloadCVCCW = TRUE;
	pDY00->oUnloadCVCW = TRUE;

	g_objAJinAXL.Write_Output(0);
}

void CCommon::Set_UnloadCVStop()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();
	pDY00->oUnloadCVCCW = FALSE;
	pDY00->oUnloadCVCW = FALSE;

	g_objAJinAXL.Write_Output(0);
}

void CCommon::Set_ElevCVRunCCW()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();
	pDY00->oMZElevCVCCW = TRUE;
	pDY00->oMZElevCVCW = FALSE;
	g_objAJinAXL.Write_Output(0);
}


void CCommon::Set_ElevCVRunCW()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();
	pDY00->oMZElevCVCCW = TRUE;
	pDY00->oMZElevCVCW = TRUE;
	g_objAJinAXL.Write_Output(0);
}
	


void CCommon::Set_ElevCVStop()
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();
	pDY00->oMZElevCVCCW = FALSE;
	pDY00->oMZElevCVCW = FALSE;
	g_objAJinAXL.Write_Output(0);
}




void CCommon::Set_TrayPickMasterIn()
{
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();
	pDY01->oTrayPickerMasterIn = TRUE; pDY01->oTrayPickerMasterOut = FALSE;
	g_objAJinAXL.Write_Output(1);
}

void CCommon::Set_TrayPickSlaveIn()
{
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();
	pDY01->oTrayPickerSlaveIn = TRUE; pDY01->oTrayPickerSlaveOut = FALSE;
	g_objAJinAXL.Write_Output(1);
}

BOOL CCommon::Get_TrayPickMasterIn()
{
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if(pDX01->iTrayPickerMasterIn && !pDX01->iTrayPickerMasterOut)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CCommon::Get_TrayPickSlaveIn()
{
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if(pDX01->iTrayPickerSlaveIn && !pDX01->iTrayPickerSlaveOut)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CCommon::Get_TrayPickMasterSlaveIn()
{
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if(pDX01->iTrayPickerMasterIn && !pDX01->iTrayPickerMasterOut
		&& pDX01->iTrayPickerSlaveIn && !pDX01->iTrayPickerSlaveOut)
	{
		return TRUE;
	}
	return FALSE;
}

void CCommon::Set_TrayPickMasterOut()
{
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();
	pDY01->oTrayPickerMasterIn = FALSE; pDY01->oTrayPickerMasterOut = TRUE;
	g_objAJinAXL.Write_Output(1);
}
void CCommon::Set_TrayPickSlaveOut()
{
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();
	pDY01->oTrayPickerSlaveIn = FALSE; pDY01->oTrayPickerSlaveOut = TRUE;
	g_objAJinAXL.Write_Output(1);
}

BOOL CCommon::Get_TrayPickMasterOut()
{
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if(!pDX01->iTrayPickerMasterIn && pDX01->iTrayPickerMasterOut)
	{
		return TRUE;
	}
	return FALSE;
}
BOOL CCommon::Get_TrayPickSlaveOut()
{
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if(!pDX01->iTrayPickerSlaveIn && pDX01->iTrayPickerSlaveOut)
	{
		return TRUE;
	}
	return FALSE;
}
BOOL CCommon::Get_TrayPickMasterSlaveOut()
{
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if(!pDX01->iTrayPickerMasterIn && pDX01->iTrayPickerMasterOut
		&& !pDX01->iTrayPickerSlaveIn && pDX01->iTrayPickerSlaveOut)
	{
		return TRUE;
	}
	return FALSE;
}