// Inspector.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "SingleLens.h"
#include "Inspector.h"

#include "LogFile.h"
#include "Common.h"
#include "DataManager.h"

#include "SequenceInit.h"
#include "SequenceMain.h"




IMPLEMENT_DYNAMIC(CInspector, CWnd)

CInspector g_objInspector;

CCriticalSection g_csInspectSend;	// Send_Command 문제 해결하기 위함
CCriticalSection g_csInspectRecv;	// Receive_Command 문제 해결하기 위함
// CInspector

CInspector::CInspector()
{
	m_nStatusPC1 = 0;		// Vision PC1 상태 (0:Not Ready, 1:Ready, 2:Run)
	

	m_bLotReady1 = FALSE;	
}

CInspector::~CInspector()
{
}

BEGIN_MESSAGE_MAP(CInspector, CWnd)

	
END_MESSAGE_MAP()

// CInspector 메시지 처리기입니다.

void CInspector::Initialize()
{
	m_Vision1.Create(NULL, NULL, WS_CHILD, CRect(0,0,0,0), this, 0);

	m_Vision1.Init_Socket();
}

void CInspector::Terminate()
{
	m_Vision1.Exit_Socket();
}

///////////////////////////////////////////////////////////////////////////////
// UDP Socket Message


void CInspector::Receive_Command(int nVPc, CString sCommand)
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	
	g_csInspectRecv.Lock();

	char chSep = ',';
	CString strCmd, strOp, strLog;

	AfxExtractSubString(strCmd, sCommand, 0, chSep);
	AfxExtractSubString(strOp, sCommand, 1, chSep);

	// Inspector Log ////////////////////////////////////////
	strLog.Format("[H<-V%d] : %s", nVPc, sCommand);
	g_objLogFile.Save_InspectorLog(strLog);
	/////////////////////////////////////////////////////////
	CString strA[7];
	for (int i = 0; i < 7; i++) AfxExtractSubString(strA[i], sCommand, i + 2, chSep);

	if (strCmd == "STATUS") {
		if (strOp == "REQUEST") Get_StatusRequest(nVPc);
		if (strOp == "REPLY")	Get_StatusReply(nVPc, strA[0]);
		if (strOp == "UPDATE")	Get_StatusUpdate(nVPc, strA[0]);

	} else if (strCmd == "LOT") {
		if (strOp == "READY") Get_LotReady(nVPc, strA[0], strA[1]);

	} else if (strCmd == "SCAN") {
		if (strOp == "COMPLETE") Get_ScanComplete(nVPc, strA[0], strA[1], strA[2], strA[3], strA[4]);

	} else if (strCmd == "INSPECT") {
		if (strOp == "COMPLETE") Get_InspectComplete(nVPc, strA[0], strA[1], strA[2], strA[3], strA[4], strA[5], strA[6]);

	} else if (strCmd == "AMOVE") {
		if (strOp == "REQUEST") Get_AMoveRequest(nVPc, strA[0], strA[1], strA[2], strA[3], strA[4], strA[5], strA[6]);

	} else if (strCmd == "POSITION") {
		if (strOp == "REQUEST") Get_PositionRequest(nVPc, strA[0]);
	
	} else if (strCmd == "RELOAD") {
		if (strOp == "REQUEST") Get_ReloadRequest(nVPc, strA[0]);

	} else if (strCmd == "ERROR") {
		if (strOp == "REQUEST") Get_ErrorRequest(nVPc, strA[0], strA[1], strA[2], strA[3], strA[4], strA[5], strA[6]);
	}

	g_csInspectRecv.Unlock();
}

///////////////////////////////////////////////////////////////////////////////
// Get Command

void CInspector::Get_StatusRequest(int nVPc)
{
	BOOL bInit = g_objSequenceInit.Get_InitComplete();
	BOOL bRun = g_objSequenceMain.Is_MainThreadRun();
	int nStatus = bRun ? 2 : bInit ? 1 : 0;
	Set_StatusReply(nVPc, nStatus);
}

void CInspector::Get_StatusReply(int nVPc, CString sStatus)
{
	if (nVPc == VISION_PC1) m_nStatusPC1 = atoi(sStatus);
	
}

void CInspector::Get_StatusUpdate(int nVPc, CString sStatus)
{
	if (nVPc == VISION_PC1) m_nStatusPC1 = atoi(sStatus);

}

void CInspector::Get_LotReady(int nVPc, CString sLotId, CString sLotNo)
{
	int nLx = atoi(sLotNo) - 1;
	if (nLx < 0 || nLx > 4) return;

	/*if (sLotId != gData.sLotID[nLx]) return;
	if (nVPc == VISION_PC1) m_bLotReady1 = TRUE;*/

}

void CInspector::Get_ScanComplete(int nVPc, CString sGbn, CString sLotId, CString sLotNo, CString sTrayNo, CString sCmNo)
{
	int nLx = atoi(sLotNo) - 1;		// Lot Index
	int nTx = atoi(sTrayNo) - 1;	// Tray Index
	int	nCx = atoi(sCmNo) - 1;		// CM Index
	
}

void CInspector::Get_InspectComplete(int nVPc, CString sGbn, CString sLotId, CString sLotNo, CString sTrayNo, CString sCmNo, CString sJudge, CString sCode)
{
	int nLx = atoi(sLotNo) - 1;		// Lot Index
	int nTx = atoi(sTrayNo) - 1;	// Tray Index
	int	nCx = atoi(sCmNo) - 1;		// CM Index
	
}

void CInspector::Get_AMoveRequest(int nVPc, CString sGbn, CString sZ1, CString sZ2, CString sX, CString sY, CString sT, CString sR)
{
	if (!g_objSequenceInit.Get_InitComplete()) { g_objCommon.Show_Error(50); return; }

	double dZ1 = atof(sZ1);
	double dZ2 = atof(sZ2);
	double dX  = atof(sX);
	double dY  = atof(sY);
	double dT  = atof(sT);
	double dR  = atof(sR);

	int nMode = theApp.Get_MainMode();
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	
}

void CInspector::Get_PositionRequest(int nVPc, CString sGbn)
{
	if (!g_objSequenceInit.Get_InitComplete()) { g_objCommon.Show_Error(50); return; }
		
}


void CInspector::Get_ReloadRequest(int nVPc, CString sPc)
{
	// bScanDone[4][5] --> [4]=>0:B1,1:B2,2:T1,3:T2 / [5]=>0:C1,1:C2,2:C3,3:C4,4:C5
	CString strVPC;
	strVPC.Format("PC%d", nVPc);
	if (sPc != strVPC) return;
		
	Set_ReloadComplete(1, sPc);
}

void CInspector::Get_ErrorRequest(int nVPc, CString sGbn, CString sLotId, CString sLotNo, CString sTrayNo, CString sCmNo, CString sErrNo, CString sErrMsg)
{
	int nLx = atoi(sLotNo) - 1;		// Lot Index
	int nTx = atoi(sTrayNo) - 1;	// Tray Index
	int	nCx = atoi(sCmNo) - 1;		// CM Index
	
	int nMode = theApp.Get_MainMode();
	
}

void CInspector::Exception_Log(int nVPc, CString sFunc, CString sGbn, int nLotNo, int nTrayNo, int nCmNo, int nCase)
{
	CString strLog;
	strLog.Format("%s Exception ==> PC:%d, Vision:%s, LotNo:%d, TrayNo:%d, CmNo:%d, Case:%d", sFunc, nVPc, sGbn, nLotNo, nTrayNo, nCmNo, nCase);
	
}






/////////////////////////////////////////////////////////////////////////////
// Set Command

void CInspector::Set_StatusRequest(int nVPc)
{
	CString	strSendCmd;
	strSendCmd.Format("STATUS,REQUEST");
	Send_Command(nVPc, strSendCmd);
}

void CInspector::Set_StatusReply(int nVPc, int nStatus)
{
	CString	strSendCmd;
	strSendCmd.Format("STATUS,REPLY,%d", nStatus);
	Send_Command(nVPc, strSendCmd);
}

void CInspector::Set_StatusUpdate(int nVPc, int nStatus)
{
	CString	strSendCmd;
	strSendCmd.Format("STATUS,UPDATE,%d", nStatus);
	Send_Command(nVPc, strSendCmd);
}

void CInspector::Set_LotStart(int nVPc, CString sLotId, int nLotNo, int nTrayCount, int nCmCount, CString sModel)
{
	m_bLotReady1 = FALSE;

	CString strSendCmd;
	strSendCmd.Format("LOT,START,%s,%d,%d,%d,%s", sLotId, nLotNo, nTrayCount, nCmCount, sModel);
	Send_Command(nVPc, strSendCmd);
}

void CInspector::Set_LotEnd(int nVPc, CString sLotId, int nLotNo)
{
	CString	strSendCmd;
	strSendCmd.Format("LOT,END,%s,%d", sLotId, nLotNo);
	Send_Command(nVPc, strSendCmd);
}

void CInspector::Set_LoadComplete(int nVPc, CString sGbn, CString sLotId, int nLotNo, int nTrayNo, int nCmNo, double dHeight)
{
	CString	strSendCmd, strTemp;
	strSendCmd.Format("LOAD,COMPLETE,%s,%s,%d,%d,%d,%0.3lf", sGbn, sLotId, nLotNo, nTrayNo, nCmNo, dHeight);
	Send_Command(nVPc, strSendCmd);
}

void CInspector::Set_MoveComplete(int nVPc, CString sGbn)
{
	CString	strSendCmd;
	strSendCmd.Format("MOVE,COMPLETE,%s", sGbn);
	Send_Command(nVPc, strSendCmd);
}

void CInspector::Set_PositionReply(int nVPc, CString sGbn, double dZ1, double dZ2, double dX, double dY, double dT, double dR)
{
	CString	strSendCmd;
	strSendCmd.Format("POSITION,REPLY,%s,%0.3lf,%0.3lf,%0.3lf,%0.3lf,%0.3lf,%0.3lf", sGbn, dZ1, dZ2, dX, dY, dT, dR);
	Send_Command(nVPc, strSendCmd);
}



void CInspector::Set_ReloadComplete(int nVPc, CString sPc)
{
	CString	strSendCmd;
	strSendCmd.Format("RELOAD,COMPLETE,%s", sPc);
	Send_Command(nVPc, strSendCmd);
}

void CInspector::Set_InitialRequest(int nVPc)
{
	CString	strSendCmd;
	strSendCmd.Format("INITIAL,REQUEST");
	Send_Command(nVPc, strSendCmd);
}

void CInspector::Set_TimeUpdate(int nVPc)
{
	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strTime;
	strTime.Format("%04d-%02d-%02d %02d:%02d:%02d.%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

	CString	strSendCmd;
	strSendCmd.Format("TIME,UPDATE,%s", strTime);
	Send_Command(nVPc, strSendCmd);
}

/////////////////////////////////////////////////////////////////////////////
// UDP Socket Send Message

void CInspector::Send_Command(int nVPc, CString sCommand)
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	// 	if (!pEquipData->bUseInspectBtm && !pEquipData->bUseInspectTop) return;

	g_csInspectSend.Lock();	// Critical Section

	// Inspector Log //////////////////////////////////////
	CString strLog;
	strLog.Format("[H->V%d] : %s", nVPc, sCommand);
	if (nVPc == VISION_ALL || nVPc == VISION_PC1) g_objLogFile.Save_InspectorLog(strLog);


	if (nVPc == VISION_ALL || nVPc == VISION_PC1) m_Vision1.Send_Message(sCommand);
	

	g_csInspectSend.Unlock();	// Critical Section
}

///////////////////////////////////////////////////////////////////////////////

BOOL CInspector::Check_Connect(int nVPc)
{
	if (nVPc == VISION_PC1) return m_Vision1.Is_Connected();

	
	return FALSE;
}

BOOL CInspector::Check_LotReady()
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	/*if (!pEquipData->bUseInspectBtm && !pEquipData->bUseInspectTop) m_bLotReady1 = m_bLotReady2 = m_bLotReady3 = m_bLotReady4 = m_bLotReady5 = TRUE;
	return (m_bLotReady1 && m_bLotReady2 && m_bLotReady3 && m_bLotReady4 && m_bLotReady5);*/

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////

void CInspector::Test_Command()
{
}
