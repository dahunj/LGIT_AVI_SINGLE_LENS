// AJinAXL.cpp : 구현 파일
//
#include "stdafx.h"
#include "AJinAXL.h"
#include "SingleLens.h"
#include <math.h>
#include "Common.h"
#include "DataManager.h"
#include "FifoTaskProcessor.h"

// AJin Board Library
#include "AXL.h"
#include "AXM.h"
#include "AXD.h"
#include "AXC.h"
#include "AXDev.h"
#pragma comment (lib, "AXL.lib")

CAJinAXL g_objAJinAXL;

CAJinAXL::CAJinAXL(void)
{
	for (int i = 0; i < DIO_MODULE_COUNT; i++) { DXY_DATA *pDX = Get_pDX(i); pDX->nValue = 0; }
	for (int i = 0; i < DIO_MODULE_COUNT; i++) { DXY_DATA *pDY = Get_pDY(i); pDY->nValue = 0; }

	for (int i = 0; i < AXIS_COUNT; i++) m_strAxisName[i] = _T("");

	m_pThreadAJin = NULL;
	m_bThreadAJin = FALSE;

	m_bReadVelocity = FALSE;
	m_runningCount = 0;
}

CAJinAXL::~CAJinAXL(void)
{
}

BOOL CAJinAXL::Initialize()
{
#ifdef AJIN_BOARD_USE
	DWORD dwReturn;

	dwReturn = AxlOpenNoReset(7);
	if (dwReturn != AXT_RT_SUCCESS) return FALSE;

	// DIO
	long lDIOCount;
	dwReturn = AxdInfoGetModuleCount(&lDIOCount);
	if (dwReturn != AXT_RT_SUCCESS) return FALSE;
	if (lDIOCount < DIO_MODULE_COUNT) return FALSE;

	if(gData.bAgingMode)
	{

	}
	else
	{
		Read_Input();
	}	
	Read_Output();

	// Door Interlock
	m_DY03.oModeSelect = TRUE;   Write_Output(3); theApp.uSleep(500);
	m_DY03.oSafetyReset = TRUE;  Write_Output(3); theApp.uSleep(500);
	m_DY03.oSafetyReset = FALSE; Write_Output(3); theApp.uSleep(500);
	m_DY03.oSafetyReset = TRUE;  Write_Output(3); theApp.uSleep(500);
	m_DY03.oSafetyReset = FALSE; Write_Output(3); theApp.uSleep(500);

	Alarm_Reset(-1);	// All Reset

	// Motion
	long lAxisCount;
	dwReturn = AxmInfoGetAxisCount(&lAxisCount);
	if (dwReturn != AXT_RT_SUCCESS) return FALSE;
	if (lAxisCount < AXIS_COUNT) return FALSE;

	CString strMotFile = gsCurrentDir + "\\System\\AJinSetting.mot";
	dwReturn = AxmMotLoadParaAll((LPSTR)(LPCSTR)strMotFile);
	if (dwReturn != AXT_RT_SUCCESS) return FALSE;
#endif

	Read_AxisList();	// Axis Name & Param

	for (long i = 0; i < AXIS_COUNT; i++) Set_ServoOn(i);

#ifdef AJIN_BOARD_USE
	// Trigger 초기화
	long lChCount, lPulse;
	double dUnits;

	if (AxcInfoGetTotalChannelCount(&lChCount)!= AXT_RT_SUCCESS) return FALSE;
	if (lChCount < 2) return FALSE;	// 2채널

	if (AxcTriggerSetEnable(0, DISABLE) != AXT_RT_SUCCESS) return FALSE;

	if (AxmMotGetMoveUnitPerPulse(AX_TOP_INSPECTOR_Z, &dUnits, &lPulse) != AXT_RT_SUCCESS) return FALSE;
	if (AxcMotSetMoveUnitPerPulse(0, dUnits / lPulse) != AXT_RT_SUCCESS) return FALSE;

	if (AxcSignalSetEncInputMethod(0, ObverseSqr4Mode) != AXT_RT_SUCCESS) return FALSE;
	if (AxcSignalSetEncReverse(0, 0) != AXT_RT_SUCCESS) return FALSE;	// 엔코더 입력 카운터 (0:반전없음, 1:반전)
	if (AxcTriggerSetLevel(0, HIGH) != AXT_RT_SUCCESS) return FALSE;	// 트리거 펄스 출력 레벨 (0:Low, 1:High)
	if (AxcTriggerSetFunction(0, 1) != AXT_RT_SUCCESS) return FALSE;	// 0:절대위치 트리거, 1:주기위치 트리거

	if (AxcTriggerSetBlockLowerPos(0, 0.0) != AXT_RT_SUCCESS) return FALSE;
	if (AxcTriggerSetBlockUpperPos(0, 1000.0) != AXT_RT_SUCCESS) return FALSE;



	if (AxcTriggerSetEnable(1, DISABLE) != AXT_RT_SUCCESS) return FALSE;

	if (AxmMotGetMoveUnitPerPulse(AX_BTM_INSPECTOR_Z, &dUnits, &lPulse) != AXT_RT_SUCCESS) return FALSE;
	if (AxcMotSetMoveUnitPerPulse(1, dUnits / lPulse) != AXT_RT_SUCCESS) return FALSE;

	if (AxcSignalSetEncInputMethod(1, ObverseSqr4Mode) != AXT_RT_SUCCESS) return FALSE;
	if (AxcSignalSetEncReverse(1, 0) != AXT_RT_SUCCESS) return FALSE;	// 엔코더 입력 카운터 (0:반전없음, 1:반전)
	if (AxcTriggerSetLevel(1, HIGH) != AXT_RT_SUCCESS) return FALSE;	// 트리거 펄스 출력 레벨 (0:Low, 1:High)
	if (AxcTriggerSetFunction(1, 1) != AXT_RT_SUCCESS) return FALSE;	// 0:절대위치 트리거, 1:주기위치 트리거

	if (AxcTriggerSetBlockLowerPos(1, 0.0) != AXT_RT_SUCCESS) return FALSE;
	if (AxcTriggerSetBlockUpperPos(1, 1000.0) != AXT_RT_SUCCESS) return FALSE;
#endif
	
	//Init Trigger 
	Start_Scan(eVision::TC, AX_TOP_INSPECTOR_Z, 0, 0, 500, 10, 10, 1);
	Start_Scan(eVision::BC, AX_BTM_INSPECTOR_Z, 0, 0, 500, 10, 10, 1);

	m_DY02.oMainIndexZigAlignIn = TRUE;
	m_DY02.oMainIndexZigAlignOut = FALSE;
	Write_Output(2);

	m_bThreadAJin = TRUE;
	m_pThreadAJin = AfxBeginThread(Thread_AJin, NULL);

#ifndef AJIN_BOARD_USE
	if (!proc.Start())
	{		
		return FALSE;
	}
#endif


	return TRUE;
}


void CAJinAXL::Terminate()
{
	if (m_pThreadAJin) {
		m_bThreadAJin = FALSE;
		WaitForSingleObject(m_pThreadAJin->m_hThread, INFINITE);
	}

	for (long i = 0; i < AXIS_COUNT; i++) Set_ServoOff(i);

#ifdef AJIN_BOARD_USE
	if (AxlIsOpened()) AxlClose();
#endif
}

void CAJinAXL::Read_Input()
{
#ifdef AJIN_BOARD_USE	

	BOOL nTemp[64];
	if(gData.bAgingMode)
	{
		 nTemp[0] = m_DX00.iLdCVMZExist1R;
		 nTemp[1] = m_DX00.iLdCVMZExist2;
		 nTemp[2] = m_DX00.iLdCVMZExist3;
		 nTemp[3] = m_DX00.iLdCVMZExist4;
		 nTemp[4] = m_DX00.iLdCVMZExist5;

		 nTemp[5] = m_DX00.iElvMZExist1;
		 nTemp[6] = m_DX00.iElvMZExist2;

		 nTemp[7] =  m_DX01.iUldCvMZExist1L;
		 nTemp[8] =  m_DX01.iUldCvMZExist2;
		 nTemp[9] =  m_DX01.iUldCvMZExist3;
		 nTemp[10] = m_DX01.iUldCvMZExist4;
	}
	
	AxdiReadInportDword( 0, 0, &m_DX00.nValue);
	AxdiReadInportDword( 1, 0, &m_DX01.nValue);
	AxdiReadInportDword( 2, 0, &m_DX02.nValue);
	AxdiReadInportDword( 3, 0, &m_DX03.nValue);


	if(gData.bAgingMode)
	{
		m_DX00.iLdCVMZExist1R = nTemp[0];
		m_DX00.iLdCVMZExist2 = nTemp[1]; 
		m_DX00.iLdCVMZExist3 = nTemp[2]; 
		m_DX00.iLdCVMZExist4 = nTemp[3]; 
		m_DX00.iLdCVMZExist5 = nTemp[4]; 

		m_DX00.iElvMZExist1	= nTemp[5]; 
		m_DX00.iElvMZExist2 = nTemp[6]; 

		m_DX01.iUldCvMZExist1L = nTemp[7];
		m_DX01.iUldCvMZExist2 = nTemp[8]; 
		m_DX01.iUldCvMZExist3 = nTemp[9]; 
		m_DX01.iUldCvMZExist4 =	nTemp[10];
	}

	
#endif
}

void CAJinAXL::Read_Output()
{
#ifdef AJIN_BOARD_USE
	AxdoReadOutportDword(4, 0, &m_DY00.nValue);
	AxdoReadOutportDword(5, 0, &m_DY01.nValue);
	AxdoReadOutportDword(6, 0, &m_DY02.nValue);
	AxdoReadOutportDword(7, 0, &m_DY03.nValue);

#endif
}

void CAJinAXL::Write_Output(int nModule)
{
#ifdef AJIN_BOARD_USE
	if (nModule ==  0) AxdoWriteOutportDword(4, 0, m_DY00.nValue);
	if (nModule ==  1) AxdoWriteOutportDword(5, 0, m_DY01.nValue);
	if (nModule ==  2) AxdoWriteOutportDword(6, 0, m_DY02.nValue);
	if (nModule ==  3) AxdoWriteOutportDword(7, 0, m_DY03.nValue);

#else
	Sim_SetOutToIn(nModule);
#endif
}

void CAJinAXL::Read_MotionStatus()
{
#ifdef AJIN_BOARD_USE
	DWORD dwStatus;
	for (int i = 0; i < AXIS_COUNT; i++) {
		//AxmStatusGetCmdPos(i, &m_Status[i].dPos);		// Position Reading
		AxmStatusGetActPos(i, &m_Status[i].dPos);		// Position Reading

		if (m_bReadVelocity) AxmStatusReadVel(i, &m_Status[i].dVel);	// Velocity Reading

		AxmSignalIsServoOn(i, &dwStatus);								// Servo-On Reading
		m_Status[i].bSOn = (BOOL)dwStatus;

		AxmSignalReadInputBit(i, UIO_INP0, &dwStatus);	// Origin Limit (In0 : Home)
		m_Status[i].bOrg = (BOOL)dwStatus;

		AxmStatusReadMechanical(i, &dwStatus);	// Mechanical Input
		m_Status[i].bELP = (BOOL)((dwStatus >> 0) & 1);	// Positive Limit (bit0)
		m_Status[i].bELN = (BOOL)((dwStatus >> 1) & 1);	// Negative Limit (bit1)
		m_Status[i].bALM = (BOOL)((dwStatus >> 4) & 1);	// Alarm (bit4)
		m_Status[i].bInP = (BOOL)((dwStatus >> 5) & 1);	// In-Position (bit5)

		AxmStatusReadInMotion(i, &dwStatus);			// Motion Running
		m_Status[i].bRun = (BOOL)dwStatus;

		AxmHomeGetResult(i, &dwStatus);					// Home Done
		m_Status[i].bHom = (dwStatus == HOME_SUCCESS ? TRUE : FALSE);
	}

	int	nIndexPos = 0;
	if      (!m_pDX02->iIndexPosBit0 &&  !m_pDX02->iIndexPosBit1 && !m_pDX02->iIndexPosBit2) nIndexPos = 1;
	else if ( m_pDX02->iIndexPosBit0 &&  !m_pDX02->iIndexPosBit1 && !m_pDX02->iIndexPosBit2) nIndexPos = 2;
	else if (!m_pDX02->iIndexPosBit0 &&   m_pDX02->iIndexPosBit1 && !m_pDX02->iIndexPosBit2) nIndexPos = 3;
	else if ( m_pDX02->iIndexPosBit0 &&   m_pDX02->iIndexPosBit1 && !m_pDX02->iIndexPosBit2) nIndexPos = 4;
	else if (!m_pDX02->iIndexPosBit0 &&  !m_pDX02->iIndexPosBit1 &&  m_pDX02->iIndexPosBit2) nIndexPos = 5;
	else if ( m_pDX02->iIndexPosBit0 &&  !m_pDX02->iIndexPosBit1 &&  m_pDX02->iIndexPosBit2) nIndexPos = 6;
	else if (!m_pDX02->iIndexPosBit0 &&   m_pDX02->iIndexPosBit1 &&  m_pDX02->iIndexPosBit2) nIndexPos = 7;
	else if ( m_pDX02->iIndexPosBit0 &&   m_pDX02->iIndexPosBit1 &&  m_pDX02->iIndexPosBit2) nIndexPos = 8;

	gData.nIndexPos = nIndexPos;

	gData.nIndexPos = gData.nIndexPos - 1;
	if(gData.nIndexPos == 0) gData.nIndexPos= 8;
#endif
}

void CAJinAXL::Set_ServoOn(int nAxis)
{
#ifdef AJIN_BOARD_USE
	AxmMoveEStop(nAxis);
	AxmSignalServoOn(nAxis, TRUE);
#endif
}

void CAJinAXL::Set_ServoOff(int nAxis)
{
#ifdef AJIN_BOARD_USE
	AxmMoveEStop(nAxis);
	AxmSignalServoOn(nAxis, FALSE);
#endif
}

void CAJinAXL::Set_EncoderType(int nAxis, int nType)
{
#ifdef AJIN_BOARD_USE
	if (!Is_AbsoluteType(nAxis)) return;
	if (nType == 0) return;		// RTEX일 경우 Incremental 모드 설정을 하지 않음
	AxmSignalSetEncoderType(nAxis, nType);	// ENCODER_TYPE_INCREMENTAL(0), ENCODER_TYPE_ABSOLUTE(1)
	Sleep(10);		// 추가 2017.07.28
#endif
}

void CAJinAXL::Home_Search(int nAxis)
{
#ifdef AJIN_BOARD_USE
	AxmHomeSetStart(nAxis);
	m_Status[nAxis].bHom = FALSE; m_Status[nAxis].bRun = TRUE;
#endif
}

void CAJinAXL::Set_Home(int nAxis)
{
#ifdef AJIN_BOARD_USE
	AxmStatusSetActPos(nAxis, 0.0);
	AxmStatusSetCmdPos(nAxis, 0.0);
	AxmHomeSetResult(nAxis, HOME_SUCCESS);
#endif
}

void CAJinAXL::Move_Absolute(int nAxis, double dPos)
{
#ifdef AJIN_BOARD_USE
	AxmMotSetAbsRelMode(nAxis, POS_ABS_MODE);
	double	dVel = m_Param[nAxis].dSpeedM;
	double	dAcc = m_Param[nAxis].dAccel;
	AxmMoveStartPos(nAxis, dPos, dVel, dAcc, dAcc);
	m_Status[nAxis].bInP = FALSE; m_Status[nAxis].bRun = TRUE;
#else
	Sim_SetMotion(1, nAxis, dPos);
#endif
}

void CAJinAXL::Move_AbsVel(int nAxis, double dPos, double dVel ,double dAcc)
{
#ifdef AJIN_BOARD_USE
	AxmMotSetAbsRelMode(nAxis, POS_ABS_MODE);
	AxmMoveStartPos(nAxis, dPos, dVel, dAcc, dAcc);
	m_Status[nAxis].bInP = FALSE; m_Status[nAxis].bRun = TRUE;
#else
	Sim_SetMotion(1,nAxis, dPos);
#endif
}

void CAJinAXL::Move_Relative(int nAxis, double dPos)
{
#ifdef AJIN_BOARD_USE
	if (nAxis == AX_MAIN_INDEX_R) {
		AxmStatusSetActPos(nAxis, 0.0);
		AxmStatusSetCmdPos(nAxis, 0.0);
	}
	AxmMotSetAbsRelMode(nAxis, POS_REL_MODE);
	double	dVel = m_Param[nAxis].dSpeedM;
	double	dAcc = m_Param[nAxis].dAccel;
	AxmMoveStartPos(nAxis, dPos, dVel, dAcc, dAcc);
	m_Status[nAxis].bInP = FALSE; m_Status[nAxis].bRun = TRUE;
#else
	Sim_SetMotion(2,nAxis, dPos);
#endif
}

void CAJinAXL::Jog_Positive(int nAxis)
{	
#ifdef AJIN_BOARD_USE
	double	dVel = m_Param[nAxis].dSpeedJ; 
	double	dAcc = m_Param[nAxis].dSpeedJ * 4.0;
	AxmMoveVel(nAxis, dVel, dAcc, dAcc);
#endif
}

void CAJinAXL::Jog_Negative(int nAxis)
{
#ifdef AJIN_BOARD_USE
	double	dVel = m_Param[nAxis].dSpeedJ * -1.0;
	double	dAcc = m_Param[nAxis].dSpeedJ * 4.0;
	AxmMoveVel(nAxis, dVel, dAcc, dAcc);
#endif
}

void CAJinAXL::Stop_Motion(int nAxis)
{
#ifdef AJIN_BOARD_USE
	AxmMoveSStop(nAxis);
#endif
}

void CAJinAXL::EStop_Motion(int nAxis)
{
#ifdef AJIN_BOARD_USE
	AxmMoveEStop(nAxis);
#endif
}

void CAJinAXL::Alarm_Reset(int nAxis)
{
#ifdef AJIN_BOARD_USE
	int nAxStart = (nAxis == -1 ? 0 : nAxis);
	int nAxEnd = (nAxis == -1 ? AXIS_COUNT : nAxis + 1);
	for (int i = nAxStart; i < nAxEnd; i++) AxmMoveEStop(i);
	Sleep(200);
	for (int i = nAxStart; i < nAxEnd; i++) AxmSignalServoAlarmReset(i, TRUE);
	Sleep(200);
	for (int i = nAxStart; i < nAxEnd; i++) AxmSignalServoAlarmReset(i, FALSE);
#endif
}

void CAJinAXL::Move_Abs_Override(int nAxis, double dPos, double dAt)
{
#ifdef AJIN_BOARD_USE
	AxmMotSetAbsRelMode(nAxis, POS_ABS_MODE);
	double	dVel = m_Param[nAxis].dSpeedM;
	double	dAcc = m_Param[nAxis].dSpeedM * 4.0;
	double dMaxVel;
	AxmMotGetMaxVel(nAxis, &dMaxVel);

	AxmOverrideSetMaxVel(nAxis, dMaxVel);	// 오버라이드 최대값 설정
	AxmOverrideVelAtPos (nAxis, dPos, dVel, dAcc, dAcc, dAt, dVel/4.0, COMMAND);
	m_Status[nAxis].bInP = FALSE; m_Status[nAxis].bRun = TRUE;
#else
	Sim_SetMotion(3, nAxis, dPos);
#endif
}

void CAJinAXL::Move_Rel_Override(int nAxis, double dPos, double dAt)
{
#ifdef AJIN_BOARD_USE
	AxmMotSetAbsRelMode(nAxis, POS_REL_MODE);
	double	dVel = m_Param[nAxis].dSpeedM;
	double	dAcc = m_Param[nAxis].dSpeedM * 4.0;
	double dMaxVel;
	AxmMotGetMaxVel(nAxis, &dMaxVel);
	
	AxmOverrideSetMaxVel(nAxis, dMaxVel);	// 오버라이드 최대값 설정
	AxmOverrideVelAtPos (nAxis, dPos, dVel, dAcc, dAcc, dAt, dVel/4.0, COMMAND);
	m_Status[nAxis].bInP = FALSE; m_Status[nAxis].bRun = TRUE;
#endif
}

BOOL CAJinAXL::Is_Done(int nAxis)
{
#ifdef AJIN_BOARD_USE
	if (m_Status[nAxis].bRun) return FALSE;
	if (!m_Status[nAxis].bInP) return FALSE;
#endif
	return TRUE;
}

BOOL CAJinAXL::Is_Home(int nAxis)
{
#ifdef AJIN_BOARD_USE
	if (!m_Status[nAxis].bHom) return FALSE;
	if (m_Status[nAxis].bRun) return FALSE;
#endif
	return TRUE;
}

BOOL CAJinAXL::Is_MoveDone(int nAxis, double dPos, double dRange)
{
#ifdef AJIN_BOARD_USE
	if (!Is_Done(nAxis)) return FALSE;
	if (fabs(m_Status[nAxis].dPos - dPos) > dRange) return FALSE;
#endif
	return TRUE;
}

void CAJinAXL::Start_Trigger(int nAxis, double dStartPos, double dEndPos, double dPeriod, double dWidth)
{
#ifdef AJIN_BOARD_USE
	AxmTriggerSetReset(nAxis);

	double dTrigTime = dWidth / m_Param[nAxis].dSpeedM * 1000000.0;	// mm->usec

	// 1. Command Position ****************************************************
// 	AxmTriggerSetTimeLevel(nAxis, dTrigTime, HIGH, COMMAND, DISABLE);
	// 2. Actual Position *****************************************************
	AxmTriggerSetTimeLevel(nAxis, dTrigTime, HIGH, ACTUAL, DISABLE);
	//*************************************************************************
	
	DWORD dwCode = AxmTriggerSetBlock(nAxis, dStartPos, dEndPos, dPeriod);
	if (dwCode != AXT_RT_SUCCESS) AfxMessageBox("Trigger Setting Error");
#endif
}

void CAJinAXL::Stop_Trigger(int nAxis)
{
#ifdef AJIN_BOARD_USE
	AxmTriggerSetReset(nAxis);
#endif
}

void CAJinAXL::Start_Scan(int nCh, int nAxis, double dPos, double dTrigS, double dTrigE, double dTrigP, double dTrigW, double dVel)
{
#if defined(AJIN_BOARD_USE)
	double dSpeed = dVel;//m_Param[nAxis].dSpeedM;
	double dWidth = (dTrigP/2) / dSpeed*1000000;
		//dTrigW / dSpeed * 1000000;	// mm => usec

	AxcTriggerSetEnable(nCh, DISABLE);
	AxcTriggerSetBlock(nCh, dTrigS, dTrigE, dTrigP);
	AxcTriggerSetTime(nCh, dWidth);
	AxcTriggerSetEnable(nCh, ENABLE);

	Move_AbsVel(nAxis, dPos, dVel, 500);
#endif
}

void CAJinAXL::Stop_Scan(int nAxis)
{
#if defined(AJIN_BOARD_USE)
	AxcTriggerSetEnable(0, DISABLE);
	Sleep(5);
	AxcTriggerSetEnable(1, DISABLE);
#endif
}

void CAJinAXL::Clear_Scan(int nCh)
{
#if defined(AJIN_BOARD_USE)
	if(nCh == 0) AxcStatusSetActPos(0,0.0);
	Sleep(5);
	if(nCh == 1 ) AxcStatusSetActPos(1,0.0);
#endif
}


/////////////////////////////////////////////////////////////////////////////
// Motion Param Read / Write Function

void CAJinAXL::Read_AxisList()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\AxisList.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("AxisList.ini File Not Found!!!");
		return;
	}

	CString strSection, strName;
	for (int i = 0; i < AXIS_COUNT; i++) {
		strSection.Format("AXIS_%02d", i);

		strName = INI.Get_String(strSection, "NAME", "");
		m_strAxisName[i].Format("[%02d] %s", i, strName);
		m_Param[i].dSpeedM = INI.Get_Double(strSection, "MOVE", 0.0);
		m_Param[i].dSpeedJ = INI.Get_Double(strSection, "JOG", 0.0);
		m_Param[i].dAccel = INI.Get_Double(strSection, "ACC", 0.0);
	}
}

void CAJinAXL::Read_MotionParam(int nAxis)
{
	CIniFileCS INI(gsCurrentDir + "\\System\\AxisList.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("AxisList.ini File Not Found!!!");
		return;
	}
	
	CString strSection;
	strSection.Format("AXIS_%02d", nAxis);
	m_Param[nAxis].dSpeedM = INI.Get_Double(strSection, "MOVE", 0.0);
	m_Param[nAxis].dSpeedJ = INI.Get_Double(strSection, "JOG", 0.0);
	m_Param[nAxis].dAccel = INI.Get_Double(strSection, "ACC", 0.0);
}

void CAJinAXL::Save_MotionParam(int nAxis, double dSpeedM, double dSpeedJ, double dAccel)
{
	CIniFileCS INI(gsCurrentDir + "\\System\\AxisList.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("AxisList.ini File Not Found!!!");
		return;
	}
	
	CString strSection;
	strSection.Format("AXIS_%02d", nAxis);
	INI.Set_Double(strSection, "MOVE", dSpeedM, "%0.3lf");
	INI.Set_Double(strSection, "JOG", dSpeedJ, "%0.3lf");
	INI.Set_Double(strSection, "ACC", dAccel, "%0.3lf");

	// RMS 항목
	Save_RmsMotionSpeed(nAxis, dSpeedM, dAccel);
}

void CAJinAXL::Save_RmsMotionSpeed(int nAxis, double dSpeedM, double dAccel)
{	
	CString strAxis, strSpeed, strAccel;
	strSpeed.Format("%0.3lf", dSpeedM);
	strAccel.Format("%0.3lf", dAccel);
	

}

/////////////////////////////////////////////////////////////////////////////
// Thread Function 
UINT CAJinAXL::Thread_AJin(LPVOID lpVoid)
{
	while (g_objAJinAXL.m_bThreadAJin) {
		g_objAJinAXL.Read_Input();
		g_objAJinAXL.Read_MotionStatus();
		Sleep(5);
	}
	g_objAJinAXL.m_bThreadAJin = FALSE;
	g_objAJinAXL.m_pThreadAJin = NULL;
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
BOOL CAJinAXL::Is_AbsoluteType(int nAxis)
{
	return FALSE;
}

BOOL CAJinAXL::Use_OrgAxis(int nAxis)
{
	return FALSE;
}

BOOL CAJinAXL::Use_ElpAxis(int nAxis)
{
	if (Use_OrgAxis(nAxis)) return FALSE;
	else return TRUE;
}

BOOL CAJinAXL::Use_ElnAxis(int nAxis)
{
	if (Use_OrgAxis(nAxis)) return FALSE;
	else return TRUE;
}

///////////////////////////////////////////////////////////////////////////////

DXY_DATA *CAJinAXL::Get_pDX(int nIndex)
{
	if (nIndex ==  0) return (DXY_DATA*)&m_DX00;
	if (nIndex ==  1) return (DXY_DATA*)&m_DX01;
	if (nIndex ==  2) return (DXY_DATA*)&m_DX02;
	if (nIndex ==  3) return (DXY_DATA*)&m_DX03;
	
	return NULL;
}

DXY_DATA *CAJinAXL::Get_pDY(int nIndex)
{
	if (nIndex ==  0) return (DXY_DATA*)&m_DY00;
	if (nIndex ==  1) return (DXY_DATA*)&m_DY01;
	if (nIndex ==  2) return (DXY_DATA*)&m_DY02;
	if (nIndex ==  3) return (DXY_DATA*)&m_DY03;
	
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////

void CAJinAXL::Save_AxisList()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\AxisList.ini");
	if (!INI.Check_File()) { AfxMessageBox("AxisList.ini File Not Found!!!"); return; }

	CString strAxis[AXIS_COUNT];

	strAxis[0 ] = "TRAY PICKER X";
	strAxis[1 ] = "TRAY PICKER Z";
	strAxis[2 ] = "TRAY PICKER R";
	strAxis[3 ] = "NO AXIS";
	strAxis[4 ] = "LOAD STAGE1 X";
	strAxis[5 ] = "LOAD STAGE1 Z";
	strAxis[6 ] = "LOAD STAGE2 X";
	strAxis[7 ] = "LOAD STAGE2 Z";
	strAxis[8 ] = "LOAD PICKER Y";
	strAxis[9 ] = "LOAD PICKER Z";
	strAxis[10] = "LOAD PICKER P";
	strAxis[11] = "MAIN INDEX R";
	strAxis[12] = "VISION CM X";
	strAxis[13] = "CAP STAGE1 X";
	strAxis[14] = "CAP STAGE1 Z";
	strAxis[15] = "CAP STAGE2 X";
	strAxis[16] = "CAP STAGE2 Z";
	strAxis[17] = "CAP PICKER Y";
	strAxis[18] = "CAP PICKER Z";
	strAxis[19] = "CAP PICKER P";
	strAxis[20] = "CAP BUFFER Y";
	strAxis[21] = "VISION CAP Y";
	strAxis[22] = "ASSY PICKER X";
	strAxis[23] = "ASSY PICKER Y";
	strAxis[24] = "ASSY PICKER Z";
	strAxis[25] = "TRANS STAGE X";
	strAxis[26] = "TRANS STAGE Z";
	strAxis[27] = "TRANS STAGE T";
	strAxis[28] = "UNLOAD PICKER X";
	strAxis[29] = "UNLOAD PICKER Z";
	strAxis[30] = "UNLOAD PICKER P";
	strAxis[31] = "UNLOAD STAGE1 Y";
	strAxis[32] = "UNLOAD STAGE1 Z";
	strAxis[33] = "UNLOAD STAGE2 Y";
	strAxis[34] = "UNLOAD STAGE2 Z";

	CString strSection, strName;
	for (int i = 0; i < AXIS_COUNT; i++) {
		strSection.Format("AXIS_%02d", i);
		INI.Set_String(strSection, "NAME", strAxis[i]);
	}

	Read_AxisList();
}

///////////////////////////////////////////////////////////////////////////////



void CAJinAXL::Sim_SetMotion(int nNo, int nAxis, double dPos)
{	
	Task t;
	t.nType = nNo;
	t.nAxis = nAxis;
	t.dPos = dPos;
	t.id = 0;

	proc.Enqueue(t);
	::Sleep(SIM_WAITTIMEM);		
}





ThreadIdManager::ThreadIdManager()
	: m_nextId(1)
{
}

int ThreadIdManager::AllocateId()
{
	CSingleLock lock(&m_cs, TRUE);
	if (!m_freeIds.empty())
	{
		std::set<int>::iterator it = m_freeIds.begin();
		int id = *it;
		m_freeIds.erase(it);
		return id;
	}
	return m_nextId++;
}

void ThreadIdManager::ReleaseId(int id)
{
	CSingleLock lock(&m_cs, TRUE);
	m_freeIds.insert(id);
}


int CAJinAXL::StartThread(int nType, int nAxis, double dPos)
{
	// 1) ID 배정
	int id = m_idMgr.AllocateId();
	if (id <= 0) return 0;

	// 2) 인자 준비
	ThreadArgs* pArgs	= new ThreadArgs;
	pArgs->pRunner		= this;
	pArgs->id			= id;
	pArgs->nAxisNo		= nAxis;
	pArgs->type			= nType;
	pArgs->dPosTarget	= dPos;

	// 3) 스레드 시작
	CWinThread* pThread = AfxBeginThread(&CAJinAXL::WorkerProc, pArgs);
	if (!pThread)
	{
		m_idMgr.ReleaseId(id);
		delete pArgs;
		return 0;
	}

	// 실행 중 개수 증가
	{
		CSingleLock lock(&m_csRunning, TRUE);
		++m_runningCount;
	}

	return id;
}


// 정적 워커 스레드 함수
UINT __cdecl CAJinAXL::WorkerProc(LPVOID pParam)
{
	ThreadArgs* pArgs = reinterpret_cast<ThreadArgs*>(pParam);
	if (!pArgs) return 0;

	CAJinAXL* pRunner = pArgs->pRunner;
	const int id = pArgs->id;

	const int nType = pArgs->type;
	const int nAxis = pArgs->nAxisNo;
	double dSpeed = g_objAJinAXL.Get_pParam(nAxis)->dSpeedM;

	double dPos = pArgs->dPosTarget;
	double dPosCur = g_objAJinAXL.m_Status[nAxis].dPos;


	g_objAJinAXL.Get_pStatus(nAxis)->bRun = TRUE;

	if(nType == 1 || nType == 3)
	{	
		while(TRUE)
		{	
			::Sleep(SIM_WAITTIMEM);

			if(nAxis == AX_MAIN_INDEX_R)
			{
				if(dPos >= dPosCur)
				{
					g_objAJinAXL.m_Status[nAxis].dPos += (dSpeed/1000)*VELOCITY_WEIGHT*7200;
					if(g_objAJinAXL.m_Status[nAxis].dPos > dPos) break;
				}
				else if(dPos < dPosCur)
				{
					g_objAJinAXL.m_Status[nAxis].dPos -= (dSpeed/1000)*VELOCITY_WEIGHT*7200;
					if(g_objAJinAXL.m_Status[nAxis].dPos < dPos) break;
				}
			}
			else
			{
				if(dPos >= dPosCur)
				{
					g_objAJinAXL.m_Status[nAxis].dPos += (dSpeed/1000)*VELOCITY_WEIGHT;
					if(g_objAJinAXL.m_Status[nAxis].dPos > dPos) break;
				}
				else if(dPos < dPosCur)
				{
					g_objAJinAXL.m_Status[nAxis].dPos -= (dSpeed/1000)*VELOCITY_WEIGHT;
					if(g_objAJinAXL.m_Status[nAxis].dPos < dPos) break;
				}
			}

			

		}

		g_objAJinAXL.Get_pStatus(nAxis)->bRun = FALSE;
		g_objAJinAXL.m_Status[nAxis].dPos = dPos;				
	}
	else if(nType == 2)
	{
		double target = g_objAJinAXL.m_Status[nAxis].dPos + dPos;

		while(TRUE)
		{
			::Sleep(SIM_WAITTIMEM);


			if(nAxis == AX_MAIN_INDEX_R)
			{
				if(dPos >= dPosCur)
				{
					g_objAJinAXL.m_Status[nAxis].dPos += (dSpeed/1000)*VELOCITY_WEIGHT*7200;
					if(g_objAJinAXL.m_Status[nAxis].dPos > target) break;
				}
				else if(dPos < dPosCur)
				{
					g_objAJinAXL.m_Status[nAxis].dPos -= (dSpeed/1000)*VELOCITY_WEIGHT*7200;
					if(g_objAJinAXL.m_Status[nAxis].dPos < target) break;
				}		
			}
			else
			{
				if(dPos >= dPosCur)
				{
					g_objAJinAXL.m_Status[nAxis].dPos += (dSpeed/1000)*VELOCITY_WEIGHT;
					if(g_objAJinAXL.m_Status[nAxis].dPos > target) break;
				}
				else if(dPos < dPosCur)
				{
					g_objAJinAXL.m_Status[nAxis].dPos -= (dSpeed/1000)*VELOCITY_WEIGHT;
					if(g_objAJinAXL.m_Status[nAxis].dPos < target) break;
				}			
			}
		}

		g_objAJinAXL.Get_pStatus(nAxis)->bRun = FALSE;
		g_objAJinAXL.m_Status[nAxis].dPos = target;	

	}


	// 종료 통지
	if (pRunner)
		pRunner->NotifyDone(id);

	// 인자 해제
	delete pArgs;
	return 0;
}




void CAJinAXL::GetCompletedIds(std::vector<int>& outCompleted)
{
	outCompleted.clear();
	CSingleLock lock(&m_csCompleted, TRUE);
	if (!m_completedIds.empty())
	{
		outCompleted.swap(m_completedIds); // 한번에 비우기
	}
}

int CAJinAXL::RunningCount() const
{
	CSingleLock lock(const_cast<CCriticalSection*>(&m_csRunning), TRUE);
	return m_runningCount;
}


void CAJinAXL::NotifyDone(int id)
{
	// 1) ID 반납
	m_idMgr.ReleaseId(id);

	// 2) 완료 큐 적재
	{
		CSingleLock lock(&m_csCompleted, TRUE);
		m_completedIds.push_back(id);
	}

	// 3) 실행 중 개수 감소
	{
		CSingleLock lock(&m_csRunning, TRUE);
		if (m_runningCount > 0) --m_runningCount;
	}
}

void CAJinAXL::Sim_SetOutToIn(int nNo)
{
	Sleep(SIM_WAITTIMES);
	
	if(nNo == 0)
	{
		m_DX00.iLdCVStpr1UpR = m_DY00.oLdCVStpr1UpR;
		m_DX00.iLdCVStpr1Dn = m_DY00.oLdCVStpr1Dn;
		m_DX00.iLdCVLift2Up = m_DY00.oLdCVStpr2Up;
		m_DX00.iLdCVLift2Dn = m_DY00.oLdCVStpr2Dn;

		m_DX00.iElvLift1UpL = m_DY00.oElvStpr1UpL;
		m_DX00.iElvLift1Dn = m_DY00.oElvStpr1Dn;
		m_DX00.iElvLift1In = m_DY00.oElvStpr1In;
		m_DX00.iElvLift1Out = m_DY00.oElvStpr1Out;

		m_DX00.iElvLift2UpR =		m_DY00.oElvStpr2UpR;
		m_DX00.iElvLift2Dn =		m_DY00.oElvStpr2Dn;
		m_DX00.iElvLift2In =			m_DY00.oElvStpr2In;
		m_DX00.iElvLift2Out =			m_DY00.oElvStpr2Out;
	}

	if(nNo == 1)
	{
		m_DX01.iUldCvStprUp =			m_DY01.oUldCvStprUp;
		m_DX01.iUldCvStprDn =			m_DY01.oUldCvStprDn;
		
		m_DX01.iFeederGripOpen =		m_DY01.oFeederGripOpen;
		m_DX01.iFeederGripClose =		m_DY01.oFeederGripClose;

		m_DX01.iRailZigAlignIn =		m_DY01.oRailZigAlignIn;
		m_DX01.iRailZigAlignOut =		m_DY01.oRailZigAlignOut;
		m_DX01.iZigPickerMasterIn =		m_DY01.oZigPickerMasterIn;
		m_DX01.iZigPickerMasterOut =	m_DY01.oZigPickerMasterOut;
		m_DX01.iZigPickerSlaveIn =		m_DY01.oZigPickerSlaveIn;
		m_DX01.iZigPickerSlaveOut =		m_DY01.oZigPickerSlaveOut;
	}

	if(nNo == 2)
	{
		m_DX02.iMainIndexZigAlignOut =		m_DY02.oMainIndexZigAlignOut;
		m_DX02.iMainIndexZigAlignIn =		m_DY02.oMainIndexZigAlignIn;
		m_DX02.iCleanerTopDn =				m_DY02.oCleanerTopDn;
		m_DX02.iCleanerTopUp =				m_DY02.oCleanerTopUp;
		m_DX02.iCleanerTopFwd =				m_DY02.oCleanerTopFwd;
		m_DX02.iCleanerTopBwd =				m_DY02.oCleanerTopBwd;
		m_DX02.iCleanerBtmDn =				m_DY02.oCleanerBtmDn;
		m_DX02.iCleanerBtmUp =				m_DY02.oCleanerBtmUp;
		m_DX02.iCleanerBtmFwd =				m_DY02.oCleanerBtmFwd;
		m_DX02.iCleanerBtmBwd =				m_DY02.oCleanerBtmBwd;
		m_DX02.IMarkPenDown =					m_DY02.oMarkPenDown;
		m_DX02.IMarkPenUp =				m_DY02.oMarkPenUp;
	}

	if(nNo == 3)
	{
		m_DX03.iDoor01Unlock =			m_DY03.oDoor01Unlock; 	
		m_DX03.iDoor02Unlock =			m_DY03.oDoor02Unlock; 	
		m_DX03.iDoor03Unlock =			m_DY03.oDoor03Unlock; 	
		m_DX03.iDoor04Unlock =			m_DY03.oDoor04Unlock; 	
		m_DX03.iDoor05Unlock =			m_DY03.oDoor05Unlock; 	
		m_DX03.iDoor06Unlock =			m_DY03.oDoor06Unlock; 	
		m_DX03.iDoor07Unlock =			m_DY03.oDoor07Unlock;	
		m_DX03.iDoor08Unlock =			m_DY03.oDoor08Unlock;	
	}	
}
