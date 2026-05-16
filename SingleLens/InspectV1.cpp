// InspectV1.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "SingleLens.h"
#include "InspectV1.h"

#include "LogFile.h"
#include "Inspector.h"

const int VISION_PC  = 1;
const int LOCAL_PORT = 12001;

IMPLEMENT_DYNAMIC(CInspectV1, CWnd)

// CInspectV1

CInspectV1::CInspectV1()
{
	m_strRecvCmd = "";
	m_bConnected = FALSE;
}

CInspectV1::~CInspectV1()
{
}

BEGIN_MESSAGE_MAP(CInspectV1, CWnd)
	ON_MESSAGE(UM_SERVER_ACCEPT, &CInspectV1::OnServerAccept)
	ON_MESSAGE(UM_SERVER_RECEIVE, &CInspectV1::OnServerReceive)
	ON_MESSAGE(UM_SERVER_REMOVE, &CInspectV1::OnServerRemove)
END_MESSAGE_MAP()

// CInspectV1 메시지 처리기입니다.

void CInspectV1::Init_Socket()
{
	m_Socket.Listen_Socket(LOCAL_PORT, this);
}

void CInspectV1::Exit_Socket()
{
	m_Socket.Close_Socket();
}

void CInspectV1::Send_Message(CString sMessage)
{
	CString strSendSocket;
	strSendSocket.Format("@%s\n", sMessage);

	char chSend[1025] = { 0 };
	int nLength = strSendSocket.GetLength();
	memcpy(chSend, (LPSTR)(LPCSTR)strSendSocket, nLength);

	m_Socket.Write_Socket(0, (BYTE*)chSend, nLength);
}

///////////////////////////////////////////////////////////////////////////////
// Server Socket Message

LRESULT CInspectV1::OnServerAccept(WPARAM wLocalPort, LPARAM lClientIdx)
{
	UINT nPort = (UINT)wLocalPort;
	if (nPort != LOCAL_PORT) { g_objLogFile.Save_InspectorLog( "OnServerAccept - Local Port Mismatch"); return 0; }

	if (lClientIdx > 0) { for (int i = 0; i < m_Socket.Get_ClientCount()-1; i++) m_Socket.Close_Client(i); }
	m_bConnected = TRUE;

	return 0;
}

LRESULT CInspectV1::OnServerReceive(WPARAM wLocalPort, LPARAM lClientIdx)
{
	UINT nPort = (UINT)wLocalPort;
	if (nPort != LOCAL_PORT) { g_objLogFile.Save_InspectorLog( "OnServerReceive - Local Port Mismatch"); return 0; }

	BYTE byRecv[1025] = { 0 };
	int nLen = m_Socket.Read_Socket(0, byRecv);
	if (nLen < 1) { g_objLogFile.Save_InspectorLog( "Receive Data Zero"); return 0; }

	CString strLog, strRecvSocket;
	strRecvSocket.Format("%s", byRecv);
	m_strRecvCmd += strRecvSocket;

	while (!m_strRecvCmd.IsEmpty()) {
		int nStart = m_strRecvCmd.Find("@");
		int nEnd = m_strRecvCmd.Find("\n");

		if (nEnd < 0) break;	// 버퍼에 들어오는 중...

		if (nStart < 0 || nStart > nEnd) {
			strLog.Format("[CInspectV1] <<Error>> %s : Start(%d), End(%d)", m_strRecvCmd, nStart, nEnd);
			g_objLogFile.Save_InspectorLog( strLog);
			m_strRecvCmd.Delete(0, nEnd + 1);	// 쓰레기값이 채워져 있어서...
			continue;
		}

		CString strRecv = m_strRecvCmd.Mid(nStart + 1, nEnd - nStart - 1);
		m_strRecvCmd.Delete(0, nEnd + 1);

		g_objInspector.Receive_Command(VISION_PC, strRecv);

		if (!m_strRecvCmd.IsEmpty()) theApp.uSleep(5);
	}

	return 0;
}

LRESULT CInspectV1::OnServerRemove(WPARAM wLocalPort, LPARAM lClientIdx)
{
	UINT nPort = (UINT)wLocalPort;
	if (nPort != LOCAL_PORT) { g_objLogFile.Save_InspectorLog( "OnServerRemove - Local Port Mismatch"); return 0; }

	m_bConnected = FALSE;

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
