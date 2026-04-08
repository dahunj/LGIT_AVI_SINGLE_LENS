// Inspector.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "SingleLens.h"
#include "Inspector.h"

#include "LogFile.h"
#include "Common.h"
#include "DataManager.h"

#include "SequenceMain.h"
#include "MESInterface.h"
#include "AviHandler.h"

#define UDP_VPC_HOST_IP	"192.168.25.23"

#define UDP_VPC_LPORT	21000
#define UDP_VPC_HPORT	21001

IMPLEMENT_DYNAMIC(CInspector, CWnd)

CInspector g_objInspector;

CCriticalSection g_csInspector;	// Send_Command 문제 해결하기 위함

// CInspector

CInspector::CInspector()
{
	m_strRecvCmd = "";
	m_nStatusVPC = 0;		// Vision 상태 (0:Not Ready, 1:Ready)
	m_bLotReady = FALSE;
}

CInspector::~CInspector()
{
}

BEGIN_MESSAGE_MAP(CInspector, CWnd)
	ON_WM_TIMER()
	ON_MESSAGE(UM_UDP_RECEIVE, OnUdpReceive)
END_MESSAGE_MAP()

// CInspector 메시지 처리기입니다.

void CInspector::Initialize()
{
	BOOL bOpened;
#ifndef AJIN_BOARD_USE
	bOpened = m_UdpVisionPC.Open_Socket(7000, 7001, "127.0.0.1", this);
#else
	bOpened = m_UdpVisionPC.Open_Socket(UDP_VPC_LPORT, UDP_VPC_HPORT, UDP_VPC_HOST_IP, this);
#endif
	if (bOpened) Set_ConnectRequest();
}

void CInspector::Terminate()
{
	Set_ConnectEnd();
	m_UdpVisionPC.Close_Socket();
}

///////////////////////////////////////////////////////////////////////////////
// UDP Socket Message

void CInspector::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(nIDEvent);
	m_nStatusVPC = 0;

	CWnd::OnTimer(nIDEvent);
}

LRESULT CInspector::OnUdpReceive(WPARAM wLocalPort, LPARAM lParam)
{
	UINT nPort = (UINT)wLocalPort;
	BYTE byRecv[1024] = { 0 };
	CString strLog;

	int nLen = m_UdpVisionPC.Read_Socket(byRecv);

	if (nLen < 1) {
		strLog.Format("[H<-V] : Local Port (%d) Mismatch or Receive Data Zero (%d)", nPort, nLen);
		g_objLogFile.Save_InspectorLog(strLog);
		return 0;
	}

	CString strRecvSocket;
	strRecvSocket.Format("%s", byRecv);
	m_strRecvCmd += strRecvSocket;

	while (!m_strRecvCmd.IsEmpty()) {
		int nStart = m_strRecvCmd.Find("@");
		int nEnd = m_strRecvCmd.Find("\n");

		if (nEnd < 0) break;	// 버퍼에 들어오는 중...

		if (nStart < 0 || nStart > nEnd) {
			strLog.Format("[H<-V] : <<Error>> %s : Start(%d), End(%d)", m_strRecvCmd, nStart, nEnd);
			g_objLogFile.Save_InspectorLog(strLog);
			m_strRecvCmd.Delete(0, nEnd + 1);	// 쓰레기값이 채워져 있어서...
			continue;
		}

		CString strRecv = m_strRecvCmd.Mid(nStart + 1, nEnd - nStart - 1);
		m_strRecvCmd.Delete(0, nEnd + 1);

		char chSep = ',';
		CString strCmd, strOp;

		AfxExtractSubString(strCmd, strRecv, 0, chSep);
		AfxExtractSubString(strOp, strRecv, 1, chSep);

		// Inspector Log ////////////////////////////////////////
		if (strCmd != "HEART" && strOp != "BEAT") {
			strLog.Format("[H<-V] : %s", strRecv);
			g_objLogFile.Save_InspectorLog(strLog);
		}
		/////////////////////////////////////////////////////////

		EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
 		if (!pEquipData->bUseVisionCapDir && !pEquipData->bUseVisionCmAlign) return 0;

		CString strArg[11];
		for (int i = 0; i < 11; i++) AfxExtractSubString(strArg[i], strRecv, i + 2, chSep);

		if (strCmd == "CONNECT") {
			if (strOp == "REQUEST")	Get_ConnectRequest();
			else if (strOp == "REPLY") Get_ConnectReply();
			else if (strOp == "END") Get_ConnectEnd();

		} else if (strCmd == "STATUS") {
			if (strOp == "REQUEST")	Get_StatusRequest();
			else if (strOp == "REPLY") Get_StatusReply(strArg[0]);
			else if (strOp == "UPDATE") Get_StatusUpdate(strArg[0]);

		} else if (strCmd == "LOT") {
			if (strOp == "READY") Get_LotReady(strArg[0], strArg[1]);

		} else if (strCmd == "INSPECT") {
			if (strOp == "COMPLETE") Get_InspectComplete(strArg[0], strArg[1], strArg[2], strArg[3], strArg[4], strArg[5], strArg[6]);

		} else if (strCmd == "SCAN") {
			if (strOp == "COMPLETE") Get_ScanComplete(strArg[0], strArg[1], strArg[2], strArg[3], strArg[4]);

		}else if (strCmd == "ERROR") {
			if (strOp == "REQUEST") Get_ErrorRequest(strArg[0], strArg[1], strArg[2], strArg[3], strArg[4], strArg[5]);

		} else if (strCmd == "HEART") {
			if (strOp == "BEAT") Get_HeartBeat();
		}
		else if (strCmd == "RELOAD")
		{
			if(strOp == "REQUEST") Get_ReloadRequest();
		}
	}

	return 1;
}

///////////////////////////////////////////////////////////////////////////////
// Get Command

void CInspector::Get_ConnectRequest()
{
	Set_ConnectReply();
}

void CInspector::Get_ConnectReply()
{
}

void CInspector::Get_ConnectEnd()
{
}

void CInspector::Get_StatusRequest()
{
}

void CInspector::Get_StatusReply(CString sStatus)
{
	m_nStatusVPC = atoi(sStatus);
}

void CInspector::Get_StatusUpdate(CString sStatus)
{
	KillTimer(0);
	m_nStatusVPC = atoi(sStatus);
	SetTimer(0, 15000, NULL);
}

void CInspector::Get_LotReady(CString sLotId, CString sPortNo)
{
	int nPortNo = atoi(sPortNo);
	if (sLotId != gData.sLotID[nPortNo-1]) return;
	m_bLotReady = TRUE;
}

void CInspector::Get_InspectComplete(CString sGbn, CString sMZID, CString sZigID, CString sSlotNo, CString sLensNo, CString sJudge, CString sNgCode)
{
	int	nSlot = atoi(sSlotNo) - 1;
	int	nLens = atoi(sLensNo) - 1;
	if ( nSlot < 0 || nSlot > 29 || nLens < 0 || nLens > 39) { g_objCommon.Show_Error(6101); return; }


	int nV = (sGbn == "T1" ? 0 : 1);
	if (nV == -1) { g_objCommon.Show_Error(6102); return; }


	gData.cJudgeCode[nSlot][nLens][nV] = *(LPSTR)(LPCTSTR)sJudge;


	if (sJudge != "G" && sNgCode.GetLength() < 2) sNgCode = "NON";	// Good 일때 NG Code는 Space(" ")


	if (sJudge == "N1" || sJudge == "N2" || sJudge == "N3" || sJudge == "N4")
	{
		
	}

	int nMode = theApp.Get_MainMode();
	int nPreInfo = gData.nInspectInfo[nSlot][nLens];

	if		(sJudge == "N") { if (nPreInfo < 8 || nPreInfo > 8) gData.nInspectInfo[nSlot][nLens] = LensState::NG; }	// N4
	else if	(sJudge == "B")  { if (nPreInfo < 7 || nPreInfo > 8) gData.nInspectInfo[nSlot][nLens] = LensState::NG; }	// BS
	else if (sJudge == "G")
	{
		gData.nInspectInfo[nSlot][nLens] = LensState::Good;
	}

	gData.byInspectDone[nSlot][nLens] |= (1 << nV);

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	if (pEquipData->bUseTopVision && ((gData.byInspectDone[nSlot][nLens] >> 0) & 1) == 0) return;	// T1
	if (pEquipData->bUseBtmVision  && ((gData.byInspectDone[nSlot][nLens] >> 1) & 1) == 0) return;	// B1
	
}

void CInspector::Get_ScanComplete(CString sGbn, CString sMZId, CString sLotId, CString sSlotNo, CString sLensNo)
{
	if (sGbn == "T1")
	{
		int nCase = g_objSequenceMain.Get_MainRunCase(AUTO_TOP_INSPECT);
		if (nCase != 10) { Exception_Log("Scan Complete", sGbn, nCase); return; }
		m_nT1ScanCnt++;
		if (m_nT1ScanCnt < m_nT1ScanReq) return;
		gData.bScanDone[0] = TRUE; 
		g_objSequenceMain.Set_MainRunCase(AUTO_TOP_INSPECT, 10);

	}
	else if(sGbn == "B1")
	{
		int nCase = g_objSequenceMain.Get_MainRunCase(AUTO_BTM_INSPECT);
		if (nCase != 10) { Exception_Log("Scan Complete", sGbn, nCase); return; }
		m_nB1ScanCnt++;
		if (m_nB1ScanCnt < m_nB1ScanReq) return;
		gData.bScanDone[1] = TRUE; 
		g_objSequenceMain.Set_MainRunCase(AUTO_BTM_INSPECT, 10);
	}
}

void CInspector::Get_ErrorRequest(CString sGbn, CString sLotId, CString sPortNo, CString sTrayNo, CString sCmNo, CString sErrNo)
{
	int	nTNo = atoi(sTrayNo) - 1;
	int	nCNo = atoi(sCmNo) - 1;
	int nPNo = atoi(sPortNo) - 1;
	if (nTNo < 0 || nTNo > 99 || nCNo < 0 || nCNo > 200 || nPNo < 0 || nPNo > 2) { g_objCommon.Show_Error(6101); return; }

	int nErrNo = atoi(sErrNo);	// 6120 : Mirror Z Axis Error, 6130: Btm2 Picker Module Error

	CString strErrMsg;
	strErrMsg.Format(" ==> Vision:%s. LotID:%s. PortNo:%d. Tray:%d. CM:%d", sGbn, sLotId, nPNo+1, nTNo+1, nCNo+1);

	g_objCommon.Set_ErrorSubMessage(strErrMsg);

	int nMode = theApp.Get_MainMode();
	if (nErrNo != 6120 && (nMode == MODE_WORK || nMode == MODE_OPERATOR)) g_objCommon.Show_Error(nErrNo);
}

void CInspector::Get_HeartBeat()
{
	KillTimer(0);
	m_nStatusVPC = 1;
	SetTimer(0, 15000, NULL);
}

void CInspector::Get_ReloadRequest( )
{
	


}

void CInspector::Get_ZMoveRequest(int nInspector, CString sGbn, CString sZ)
{
	double dZ = atof(sZ);
	CString strLog = "";

	int nMode = theApp.Get_MainMode();

	if (sGbn == "T1") 
	{
		if (nMode == MODE_WORK || nMode == MODE_OPERATOR) 
		{	
			// AutoRun
			int nCase1 = g_objSequenceMain.Get_MainRunCase(AUTO_TOP_INSPECT);
			
			if (nCase1 != TopBranch::VisionWait ) { Exception_Log("ZMove Request", sGbn, nCase1); return; }
			g_objSequenceMain.m_dTop1Z = dZ;
			g_objSequenceMain.Set_MainRunCase(AUTO_TOP_INSPECT, 6);

		} 
		/*else if (nMode == MODE_MANUAL)
		{
			if (!g_objAJinAXL.Is_Home(AX_TOP_INSPECTOR_Z) || dZ < 0.0) return;
			g_objAJinAXL.Move_Absolute(AX_TOP_INSPECTOR_Z, dZ);
			DWORD dwStart = GetTickCount();
			while (!g_objAJinAXL.Is_MoveDone(AX_TOP_INSPECTOR_Z, dZ)) {
				if (GetTickCount() - dwStart > 10000) return;
				DoEvents();
			}
			Set_MoveComplete(nInspector, sGbn);
		}*/
	}

}

void CInspector::Exception_Log(CString sFunc, CString sGbn, int nCase)
{
	CString strLog;
	strLog.Format("%s Exception ==> Vision:%s, Case:%d", sFunc, sGbn, nCase);
	g_objLogFile.Save_InspectorLog(strLog);
}

/////////////////////////////////////////////////////////////////////////////
// Set Command

void CInspector::Set_ConnectRequest()
{
	CString	strSendCmd;
	strSendCmd.Format("CONNECT,REQUEST");
	Send_Command(strSendCmd);
}

void CInspector::Set_ConnectReply()
{
	CString	strSendCmd;
	strSendCmd.Format("CONNECT,REPLY");
	Send_Command(strSendCmd);
}

void CInspector::Set_ConnectEnd()
{
	CString	strSendCmd;
	strSendCmd.Format("CONNECT,END");
	Send_Command(strSendCmd);
}

void CInspector::Set_StatusRequest()
{
	CString	strSendCmd;
	strSendCmd.Format("STATUS,REQUEST");
	Send_Command(strSendCmd);
}

void CInspector::Set_StatusReply(int nStatus)
{
	CString	strSendCmd;
	strSendCmd.Format("STATUS,REPLY,%d", nStatus);
	Send_Command(strSendCmd);
}

void CInspector::Set_StatusUpdate(int nStatus)
{
	CString	strSendCmd;
	strSendCmd.Format("STATUS,UPDATE,%d", nStatus);
	Send_Command(strSendCmd);
}

void CInspector::Set_LotStart(CString sLotId, int nPortNo)
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	m_bLotReady = FALSE;
	CString	strSendCmd;
	//strSendCmd.Format("LOT,START,%s,%d,%d,%d,%s", sLotId, nPortNo, gData.nTrayUseCount[nPortNo-1], gData.nCmUseCount[nPortNo-1], gData.sRecipe);
	Send_Command(strSendCmd);
}

void CInspector::Set_LotEnd(CString sLotId, int nPortNo)
{
	CString	strSendCmd;
	strSendCmd.Format("LOT,END,%s,%d", sLotId, nPortNo);
	Send_Command(strSendCmd);
}

void CInspector::Set_LoadComplete(int nInspector, CString sGbn, CString sZigID, CString sMZID, int nSlotNo, int nLensNo)
{
	CString	strSendCmd, strTemp;

	if (sGbn == "T1" || sGbn == "B1" ) {
		int nScanReq = 0;
		
		if (sGbn == "T1") { m_nT1ScanReq = gData.nScanReqTop; m_nT1ScanCnt = 0; gData.bScanDone[0] = FALSE; }
		if (sGbn == "B1") { m_nB1ScanReq = gData.nScanReqBtm; m_nB1ScanCnt = 0; gData.bScanDone[1] = FALSE; }
	}
	strSendCmd.Format("LOAD,COMPLETE,%s,%s,%s,%d,%d", sGbn, sZigID, sMZID, nSlotNo, nLensNo);
	Send_Command(strSendCmd);
}

void CInspector::Set_InitialRequest()
{
	CString	strSendCmd;
	strSendCmd.Format("INITIAL,REQUEST");
	Send_Command(strSendCmd);
}

void CInspector::Set_LightOff()
{
	CString strSendCmd;
	strSendCmd.Format("LIGHT,OFF");
	Send_Command(strSendCmd);
}
void CInspector::Set_ReloadComplete()
{
	CString	strSendCmd;
	strSendCmd.Format("RELOAD,COMPLETE");
	Send_Command(strSendCmd);
}


void CInspector::Set_ZMoveComplete(int nInspector, CString sGbn)
{
	CString	strSendCmd;
	strSendCmd.Format("ZMOVE,COMPLETE,%s", sGbn);
	Send_Command(strSendCmd);
}

///////////////////////////////////////////////////////////////////////////////

int CInspector::Get_VisionStatus()
{
	return m_nStatusVPC;
}

BOOL CInspector::Check_LotReady()
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
#ifdef DRY_RUN_TEST
	m_bLotReady = TRUE;
#else
	if (!pEquipData->bUseVisionCapDir && !pEquipData->bUseVisionCmAlign) m_bLotReady = TRUE;
#endif
	return m_bLotReady;
}

/////////////////////////////////////////////////////////////////////////////
// UDP Socket Send Message

void CInspector::Send_Command(CString strSend)
{
	// Inspector Log //////////////////////////////////////
	CString strLog;
	strLog.Format("[H->V] : %s", strSend);
	g_objLogFile.Save_InspectorLog(strLog);
	///////////////////////////////////////////////////////

	g_csInspector.Lock();	// Critical Section

	CString strSendSocket;
	strSendSocket.Format("@%s\n", strSend);

	char chSend[1024] = { 0 };
	int nLength = strSendSocket.GetLength();
	memcpy(chSend, (LPSTR)(LPCSTR)strSendSocket, nLength);

	m_UdpVisionPC.Write_Socket((BYTE*)chSend, nLength);

	g_csInspector.Unlock();	// Critical Section
}

/////////////////////////////////////////////////////////////////////////////

void CInspector::Test_Command()
{
}
