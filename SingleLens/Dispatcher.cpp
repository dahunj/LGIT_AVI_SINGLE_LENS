// Dispatcher.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SingleLens.h"
#include "Dispatcher.h"

#include "LogFile.h"
#include "Common.h"
#include "SequenceMain.h"

#define UDP_DISPATCHER_LPORT	8020
#define UDP_DISPATCHER_HPORT	8020

IMPLEMENT_DYNAMIC(CDispatcher, CWnd)

CDispatcher g_objDispatcher;

CCriticalSection g_csDispatcher;	// Send_Command 문제 해결하기 위함

// CDispatcher


CDispatcher::CDispatcher()
{
	gData.nROSReqCount = 0;

	m_strRecvCmd = "";
	m_bConnected = FALSE;
	m_nMdjIndex = 0;
	m_nPortNo = 0;
	Reset(0);
}

CDispatcher::~CDispatcher()
{
}


BEGIN_MESSAGE_MAP(CDispatcher, CWnd)
		ON_MESSAGE(UM_UDP_CLIENT_RECEIVE, OnUdpClientReceive)
END_MESSAGE_MAP()



// CDispatcher 메시지 처리기입니다.


// CDispatcherer 메시지 처리기입니다.

BOOL CDispatcher::Initialize()
{
	BOOL bOpenRecv = m_UdpRecv.Open_Socket(UDP_DISPATCHER_LPORT, this);
	BOOL bOpenSend = m_UdpSend.Open_Socket(this);
	if (!bOpenRecv || !bOpenSend) return FALSE;

	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	CString strLog;
	strLog.Format("Initialize : Handler IP(%s), TimeOver(%d msec)", pRosData->sHandlerIp, pRosData->nJudgeTimeOver);
	g_objLogFile.Save_DispatcherLog(strLog);

	Set_ConnectRequest();

	return TRUE;
}

void CDispatcher::Terminate()
{

	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	POSITION pos = pRosData->lstMdjIp.GetHeadPosition();
	while (pos) {
		CString strIp = pRosData->lstMdjIp.GetNext(pos);
		Set_ConnectEnd(strIp);
	}

	m_UdpRecv.Close_Socket();
	m_UdpSend.Close_Socket();

	g_objDataManager.Save_RosData();

	g_objLogFile.Save_DispatcherLog("Terminate");
}

void CDispatcher::Reset(int nMzNo)
{
	if (nMzNo == 0) {
		memset(m_bJudgeReq, 0x00, sizeof(BOOL) * 3 * 10 * 200);
		memset(m_dwReqStart, 0x00, sizeof(DWORD) * 3 * 10 * 200);
		memset(m_bJudgeDone, 0x00, sizeof(BOOL) * 3 * 10 * 200);
		memset(m_dwTimeStart, 0x00, sizeof(DWORD) * 3 * 10 * 200);

		memset(gData.nROSInfo, 0x00, sizeof(int)*7*10*800); 
	} 
	else
	{
		memset(m_bJudgeReq[nMzNo-1], 0x00, sizeof(BOOL) * 10 * 200);
		memset(m_dwReqStart[nMzNo-1], 0x00, sizeof(DWORD) * 10 * 200);
		memset(m_bJudgeDone[nMzNo-1], 0x00, sizeof(BOOL) * 10 * 200);
		memset(m_dwTimeStart[nMzNo-1], 0x00, sizeof(DWORD) * 10 * 200);

		memset(gData.nROSInfo[nMzNo-1], 0x00, sizeof(int)*10*800); 
	}
}

///////////////////////////////////////////////////////////////////////////////
// UDP Socket Message

LRESULT CDispatcher::OnUdpClientReceive(WPARAM wLocalPort, LPARAM lParam)
{
	UINT nPort = (UINT)wLocalPort;
	BYTE byRecv[1025] = { 0 };
	CString strLog;

	int nLen = m_UdpRecv.Read_Socket(byRecv);

	if (nLen < 1) {
		strLog.Format("[H<-J] : Local Port (%d) Mismatch or Receive Data Zero (%d)", nPort, nLen);
		g_objLogFile.Save_DispatcherLog(strLog);
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
			strLog.Format("[H<-J] : <<Error>> %s : Start(%d), End(%d)", m_strRecvCmd, nStart, nEnd);
			g_objLogFile.Save_DispatcherLog(strLog);
			m_strRecvCmd.Delete(0, nEnd + 1);	// 쓰레기값이 채워져 있어서...
			continue;
		}

		CString strRecv = m_strRecvCmd.Mid(nStart + 1, nEnd - nStart - 1);
		m_strRecvCmd.Delete(0, nEnd + 1);

		EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
		if (!pEquipData->bUseROS) return 0;

		char chSep = ',';
		CString strCmd, strOp, strIp;

		AfxExtractSubString(strCmd, strRecv, 0, chSep);
		AfxExtractSubString(strOp, strRecv, 1, chSep);
		AfxExtractSubString(strIp, strRecv, 2, chSep);	// Recieve MDJ IP

		// Dispatcher Log /////////////////////////////////////////////////////
		strLog.Format("[H<-J] : %s", strRecv);
		g_objLogFile.Save_DispatcherLog(strLog);
		///////////////////////////////////////////////////////////////////////

		CString strArg[8];
		for (int i = 0; i < 8; i++) AfxExtractSubString(strArg[i], strRecv, i + 3, chSep);

		if (strCmd == "CONNECT") {
			if (strOp == "REQUEST")	Get_ConnectRequest(strIp);
			else if (strOp == "REPLY") Get_ConnectReply(strIp);
			else if (strOp == "END") Get_ConnectEnd(strIp);

		} else if (strCmd == "STATUS") {
			if (strOp == "REQUEST")	Get_StatusRequest(strIp);
			else if (strOp == "REPLY") Get_StatusReply(strArg[0]);
			else if (strOp == "UPDATE") Get_StatusUpdate(strArg[0]);

		} else if (strCmd == "JUDGE") {
			if (strOp == "REPLY") Get_JudgeReply(strArg[0], strArg[1], strArg[2], strArg[3], strArg[4], strArg[5], strArg[6], strArg[7]);

		} else if (strCmd == "INFO") {
			if (strOp == "REQUEST")	Get_InfoRequest(strIp);
		}
	}

	return 1;
}

///////////////////////////////////////////////////////////////////////////////
// Get Command

void CDispatcher::Get_ConnectRequest(CString sIp)
{
	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	POSITION pos = pRosData->lstMdjIp.Find(sIp);
	if (!pos) pRosData->lstMdjIp.AddTail(sIp);

	Set_ConnectReply(sIp);
}

void CDispatcher::Get_ConnectReply(CString sIp)
{
	m_bConnected = TRUE;
}

void CDispatcher::Get_ConnectEnd(CString sIp)
{
	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	POSITION pos = pRosData->lstMdjIp.Find(sIp);
	if (pos) pRosData->lstMdjIp.RemoveAt(pos);
	Set_ConnectEnd(sIp);

	if (pRosData->lstMdjIp.GetCount() < 1) m_bConnected = FALSE;
}

void CDispatcher::Get_StatusRequest(CString sIp)
{
	int nEqStatus = (int)g_objSequenceMain.Is_MainThreadRun();
	Set_StatusReply(sIp, nEqStatus);
}

void CDispatcher::Get_StatusReply(CString sStatus)
{
	int nRosStatus = atoi(sStatus);
}

void CDispatcher::Get_StatusUpdate(CString sStatus)
{
	int nRosStatus = atoi(sStatus);
}

void CDispatcher::Get_InfoRequest(CString sIp)
{
	Set_InfoReply(sIp);
}

void CDispatcher::Get_JudgeReply(CString sModel, CString sLotId, CString sMzNo, CString sTrayNo, CString sLensNo, CString sBarcode, CString sCode, CString sJudge)
{
	CString strLog;
	int	nMx = atoi(sMzNo) - 1;	// Port Number Index (1 ~ 50)
	int	nTx = atoi(sTrayNo) - 1;					// Tray Number Index (0)
	int	nMESNo = atoi(sLensNo);		// Module Number Index (1 ~ 40)
	
	int nLx = g_objCommon.ConvertToAVINo(nMESNo) - 1;
	
	if (nMx < 0 || nMx >= 3 || nTx < 0 || nTx >= 10 || nLx < 0 || nLx >= 200) {
		strLog.Format("[Get_JudgeReply] Receive Data Error1 ==> LotId(%s),JudgeReq(%d),TrayNo(%d),LensNo(%d),Judge(%s)", sLotId, (int)m_bJudgeReq, nTx+1, nLx+1, sJudge);
		g_objLogFile.Save_DispatcherLog(strLog);
		return;
	}

	if (sJudge != "G" && sJudge != "N" && sJudge != "R") {
		strLog.Format("[Get_JudgeReply] Receive Data Error2 ==> LotId(%s),JudgeReq(%d),TrayNo(%d),LensNo(%d),Judge(%s)", sLotId, (int)m_bJudgeReq, nTx+1, nLx+1, sJudge);
		g_objLogFile.Save_DispatcherLog(strLog);
		return;
	}

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (!m_bJudgeReq[nMx][nTx][nLx]) {
		strLog.Format("[Get_JudgeReply] Receive Data Error3 ==> LotId(%s),JudgeReq(%d),TrayNo(%d),LensNo(%d),Judge(%s)", sLotId, (int)m_bJudgeReq, nTx+1, nLx+1, sJudge);
		g_objLogFile.Save_DispatcherLog(strLog);
		return;
	}

	if (m_bJudgeDone[nMx][nTx][nLx] || (gData.nROSInfo[nMx][nTx][nLx] > 0 && gData.nROSInfo[nMx][nTx][nLx] != eROSInfo::Requested))
	{
		strLog.Format("[Get_JudgeReply] Already been judged,LotId(%s),TrayNo(%d),LensNo(%d),Judge(%s),PreJudge(%d)", sLotId, nTx+1, nLx+1, sJudge, gData.nROSInfo[nMx][nTx][nLx]);
		g_objLogFile.Save_DispatcherLog(strLog);
		return;
	}

	if (gData.nROSReqCount > 0) gData.nROSReqCount--;

	if (sJudge == "G") // Good
	{		
		gData.nROSInfo[nMx][nTx][nLx] = eROSInfo::Good;
		gLot.nRosJugCnt_Good[nMx]++;
	}	
	if (sJudge == "N") // ROS NG
	{ 
		gData.nROSInfo[nMx][nTx][nLx] = eROSInfo::NG;
		gLot.nRosJugCnt_NG[nMx]++;
	}	
	if (sJudge == "R") // ROS Repair 
	{ 
		gData.nROSInfo[nMx][nTx][nLx] = eROSInfo::Repair;
		gLot.nRosJugCnt_Repair[nMx]++;
	}	
	if (sJudge == "E") // ROS Repair 
	{ 
		gData.nROSInfo[nMx][nTx][nLx] = eROSInfo::Empty;
		gLot.nRosJugCnt_Repair[nMx]++;
	}	

	m_bJudgeDone[nMx][nTx][nLx] = TRUE;

	DWORD dwTerm = GetTickCount() - m_dwReqStart[nMx][nTx][nLx];
	strLog.Format("[Get_JudgeReply] Judge Result MzNo(%s) TrayNo(%s) LensNo(%s) Time,%d", sMzNo, sTrayNo, sLensNo, dwTerm);
	g_objLogFile.Save_DispatcherLog(strLog);
}

/////////////////////////////////////////////////////////////////////////////
// Set Command

void CDispatcher::Set_ConnectRequest()
{
	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	if (pRosData->lstMdjIp.GetCount() < 1) return;

	CString	strSendCmd, strIp;
	strSendCmd.Format("CONNECT,REQUEST,%s", pRosData->sHandlerIp);

	POSITION pos = pRosData->lstMdjIp.GetHeadPosition();
	while (pos) {
		strIp = pRosData->lstMdjIp.GetNext(pos);
		Send_Command(strIp, strSendCmd);
	}
}

void CDispatcher::Set_ConnectReply(CString sIp)
{
	m_bConnected = TRUE;

	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	CString	strSendCmd;
	strSendCmd.Format("CONNECT,REPLY,%s", pRosData->sHandlerIp);
	Send_Command(sIp, strSendCmd);
}

void CDispatcher::Set_ConnectEnd(CString sIp)
{
	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	CString	strSendCmd;
	strSendCmd.Format("CONNECT,END,%s", pRosData->sHandlerIp);
	Send_Command(sIp, strSendCmd);
}

void CDispatcher::Set_StatusRequest()
{
	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	if (pRosData->lstMdjIp.GetCount() < 1) return;

	CString	strSendCmd, strIp;
	strSendCmd.Format("STATUS,REQUEST,%s", pRosData->sHandlerIp);
	POSITION pos = pRosData->lstMdjIp.GetHeadPosition();
	while (pos) {
		strIp = pRosData->lstMdjIp.GetNext(pos);
		Send_Command(strIp, strSendCmd);
	}
}

void CDispatcher::Set_StatusReply(CString sIp, int nStatus)
{
	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	CString	strSendCmd;
	strSendCmd.Format("STATUS,REPLY,%s,%d", pRosData->sHandlerIp, nStatus);
	Send_Command(sIp, strSendCmd);
}

void CDispatcher::Set_StatusUpdate(int nStatus)
{
	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	if (pRosData->lstMdjIp.GetCount() < 1) return;

	CString	strSendCmd, strIp;
	strSendCmd.Format("STATUS,UPDATE,%s,%d", pRosData->sHandlerIp, nStatus);
	POSITION pos = pRosData->lstMdjIp.GetHeadPosition();
	while (pos) {
		strIp = pRosData->lstMdjIp.GetNext(pos);
		Send_Command(strIp, strSendCmd);
	}
}

void CDispatcher::Set_LotStart(int nMZNo, int nTotalTrayCnt, int nTotalLensCnt)
{
	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	if (pRosData->lstMdjIp.GetCount() < 1) return;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	CString strLotId = gLot.sLotID[nMZNo-1];
	m_nPortNo = nMZNo;

	CString	strSendCmd, strIp;
	strSendCmd.Format("LOT,START,%s,%s,%s,%d,%d,%d", pRosData->sHandlerIp, pEquipData->sModelName, strLotId, nMZNo, nTotalTrayCnt, nTotalLensCnt);
	POSITION pos = pRosData->lstMdjIp.GetHeadPosition();
	while (pos) {
		strIp = pRosData->lstMdjIp.GetNext(pos);
		Send_Command(strIp, strSendCmd);
	}
}

void CDispatcher::Set_LotEnd(int nPortNo)
{
	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	if (pRosData->lstMdjIp.GetCount() < 1) return;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	CString strLotId = gLot.sLotID[nPortNo-1];

	CString	strSendCmd, strIp;
	strSendCmd.Format("LOT,END,%s,%s,%s,%d", pRosData->sHandlerIp, pEquipData->sModelName, strLotId, nPortNo);
	POSITION pos = pRosData->lstMdjIp.GetHeadPosition();
	while (pos) {
		strIp = pRosData->lstMdjIp.GetNext(pos);
		Send_Command(strIp, strSendCmd);
	}
}

void CDispatcher::Set_InfoReply(CString sIp)
{
	if (m_nPortNo < 1) return;

	CString strLotId = gLot.sLotID[m_nPortNo-1];
	

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();

	CString	strSendCmd;
	strSendCmd.Format("INFO,REPLY,%s,%s,%s,%d,%d,%d", pRosData->sHandlerIp, pEquipData->sModelName, strLotId, m_nPortNo, gLot.nTrayCount[m_nPortNo-1], gLot.nLensCount[m_nPortNo-1]);
	//strSendCmd.Format("INFO,REPLY,%s,%s,%s,%d,%d,%d", pRosData->sHandlerIp, pEquipData->sModelName, strLotId, m_nPortNo, nTrayUseCnt, nCmUseCnt);
	Send_Command(sIp, strSendCmd);
}

void CDispatcher::Set_JudgeRequest(int nMZNo, int nTrayNo, int nLensNo)
{

	if (nMZNo < 1 || nMZNo > 3 || nTrayNo < 1 || nTrayNo > 10 || nLensNo < 1 || nLensNo > 200) return;
	// Do not overwrite an outstanding request for the same position.
	if (m_bJudgeReq[nMZNo-1][nTrayNo-1][nLensNo-1] && !m_bJudgeDone[nMZNo-1][nTrayNo-1][nLensNo-1]) return;


	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	if (pRosData->lstMdjIp.GetCount() < 1) { g_objCommon.Show_Error(9310); return; }

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	CString strLotId   = gLot.sLotID[nMZNo-1];
	//CString strBarcode = gLot.sBarCode[nMZNo-1][nTrayNo-1][nCmNo-1];
	CString strNgCode  = gData.sNGCode[nMZNo-1][nTrayNo-1][nLensNo-1][eVision::MARKING];
	gLot.nRosJugCnt_Req[nMZNo-1]++;


	gData.nROSInfo[nMZNo-1][nTrayNo-1][nLensNo-1] = eROSInfo::Requested;

	m_bJudgeDone[nMZNo-1][nTrayNo-1][nLensNo-1] = FALSE;
	m_bJudgeReq[nMZNo-1][nTrayNo-1][nLensNo-1] = TRUE;
	m_dwReqStart[nMZNo-1][nTrayNo-1][nLensNo-1] = GetTickCount();
	m_dwTimeStart[nMZNo-1][nTrayNo-1][nLensNo-1] = m_dwReqStart[nMZNo-1][nTrayNo-1][nLensNo-1];
	gData.nROSReqCount++;	

	CString	strSendCmd, strIp;
	strSendCmd.Format("JUDGE,REQUEST,%s,%s,%s,%d,%d,%d,%s,%s",
		pRosData->sHandlerIp, pEquipData->sModelName, strLotId, nMZNo, nTrayNo, nLensNo, "", strNgCode);
		//pRosData->sHandlerIp, pEquipData->sModelName, strLotId, nMZNo, nTrayNo, nCmNo, "", strNgCode, gLot.nImageCnt[nPortNo-1][nTrayNo-1][nCmNo-1][0]);

	if (m_nMdjIndex >= pRosData->lstMdjIp.GetCount()) m_nMdjIndex = 0;	// 다시 첫번째 부터...

	POSITION pos = pRosData->lstMdjIp.FindIndex(m_nMdjIndex++);
	strIp = pRosData->lstMdjIp.GetAt(pos); 
	Send_Command(strIp, strSendCmd);
}

void CDispatcher::Set_TimeUpdate()
{
	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	if (pRosData->lstMdjIp.GetCount() < 1) return;

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strTime;
	strTime.Format("%04d,%02d,%02d,%02d,%02d,%02d,%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

	CString	strSendCmd, strIp;
	strSendCmd.Format("TIME,UPDATE,%s,%s", pRosData->sHandlerIp, strTime);
	POSITION pos = pRosData->lstMdjIp.GetHeadPosition();
	while (pos) {
		strIp = pRosData->lstMdjIp.GetNext(pos);
		Send_Command(strIp, strSendCmd);
	}
}

/////////////////////////////////////////////////////////////////////////////
// UDP Socket Send Message

void CDispatcher::Send_Command(CString sIp, CString sSend)
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (!pEquipData->bUseROS) return;

	CString strLog;
	strLog.Format("[H->J] : %s", sSend);
	g_objLogFile.Save_DispatcherLog(strLog);

	CString strSendSocket;
	strSendSocket.Format("@%s\n", sSend);

	char chSend[1025] = { 0 };
	int nLength = strSendSocket.GetLength();
	memcpy(chSend, (LPSTR)(LPCSTR)strSendSocket, nLength);

	g_csDispatcher.Lock();		// Critical Section

#ifndef AJIN_BOARD_USE
	m_UdpSend.Write_Socket(sIp, 8021, (BYTE*)chSend, nLength);
#else 
	m_UdpSend.Write_Socket(sIp, UDP_DISPATCHER_HPORT, (BYTE*)chSend, nLength);
#endif
		
	g_csDispatcher.Unlock();	// Critical Section
}

///////////////////////////////////////////////////////////////////////////////

BOOL CDispatcher::Is_JudgeDone(int nMNo, int nTrayNo, int nLensNo, int &nInfo)
{
	if (nMNo < 1 || nMNo > 3 || nTrayNo < 1 || nTrayNo > 10 || nLensNo < 1 || nLensNo > 200 || gData.bCycleStop) return TRUE;

	if (!m_bJudgeReq[nMNo-1][nTrayNo-1][nLensNo-1]) return TRUE;
	if (m_bJudgeDone[nMNo-1][nTrayNo-1][nLensNo-1])
	{
		//Final ROS Result OverWrite 
		nInfo = gData.nROSInfo[nMNo-1][nTrayNo-1][nLensNo-1];
		gData.nInfoMainIndex[nMNo-1][nTrayNo-1][nLensNo-1] = nInfo;
		return TRUE;
	}

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	int nTerm = (int)(GetTickCount() - m_dwTimeStart[nMNo-1][nTrayNo-1][nLensNo-1]);

	if (nTerm > pEquipData->nROSTimeOut) {		// Time Over
		CString strLog;
		strLog.Format("Judge Time Over (%d msec),Bar(None),PortNo(%d),TrayNo(%d),CmNo(%d)", pEquipData->nROSTimeOut, nMNo, nTrayNo, nLensNo);
		g_objLogFile.Save_DispatcherLog(strLog);
		m_bJudgeDone[nMNo-1][nTrayNo-1][nLensNo-1] = TRUE;
		
		if (gData.nROSReqCount > 0) gData.nROSReqCount--;
		nInfo = eROSInfo::Repair;
		gData.nROSInfo[nMNo-1][nTrayNo-1][nLensNo-1] = nInfo;
		gData.nInfoMainIndex[nMNo-1][nTrayNo-1][nLensNo-1] = nInfo;

		gLot.nRosJugCnt_Repair[nMNo-1]++;	//ROS TimeOver -> ROS-Repair
		return TRUE;
	}
	return FALSE;
}

void CDispatcher::Set_TimeOver(int nPortNo, int nTrayNo, int nCmNo)
{
	m_dwTimeStart[nPortNo-1][nTrayNo-1][nCmNo-1] = GetTickCount();
}

/////////////////////////////////////////////////////////////////////////////

void CDispatcher::Test_Command(int nNo)
{
}

