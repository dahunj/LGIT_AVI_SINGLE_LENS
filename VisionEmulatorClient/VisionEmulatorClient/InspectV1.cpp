// InspectV1.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisionEmulatorClient.h"
#include "InspectV1.h"
#include "LogFile.h"
#include "Inspector.h"

#define	VISION1_IP	"127.0.0.1"
#define VISION1_PORT	12001		// Equip Handler Port

const char STX = 0x02;
const char ETX = 0x03;
const CString CRLF = "\r\n";

// CInspectV1

//CInspectV1 g_objVision1;

IMPLEMENT_DYNAMIC(CInspectV1, CWnd)

CInspectV1::CInspectV1()
{
	m_bConnected = FALSE;
	m_bEquipmentOnline = FALSE;
	m_strRecvCmd = "";
}

CInspectV1::~CInspectV1()
{
}


BEGIN_MESSAGE_MAP(CInspectV1, CWnd)
	ON_MESSAGE(UM_CLIENT_CONNECT, OnClientConnect)
	ON_MESSAGE(UM_CLIENT_RECEIVE, OnClientReceive)
	ON_MESSAGE(UM_CLIENT_CLOSE, OnClientClose)
END_MESSAGE_MAP()



// CInspectV1 메시지 처리기입니다.



void CInspectV1::Initialize()
{
	if (m_bConnected) return;

	m_bConnected = m_Client.Open_Socket(VISION1_IP, VISION1_PORT, this);	
	Sleep(1000);

}

void CInspectV1::Terminate()
{
	m_bConnected = FALSE;
	m_bEquipmentOnline = FALSE;
	m_Client.Close_Socket();

	//g_objLogFile.Save_MesAgentLog("MesAgent Terminate.");	Sleep(500);
}


LRESULT CInspectV1::OnClientConnect(WPARAM wConnect, LPARAM lParam)
{
	m_bConnected = (BOOL)wConnect;
	if (!m_bConnected) return 0;

	//
	g_objLogFile.Save_VisionLog("Equip Connected");
	return 0;
}

LRESULT CInspectV1::OnClientClose(WPARAM wParam, LPARAM lParam)
{
	m_bConnected = FALSE;
	m_bEquipmentOnline = FALSE;
	m_Client.Close_Socket();
	g_objLogFile.Save_VisionLog("Equip Disconnected");
	return 0;
}

LRESULT CInspectV1::OnClientReceive(WPARAM wParam, LPARAM lParam)
{
	BYTE byRecv[1025] = { 0 };	// Buffer 1024, Last 0x00
	int nLen = m_Client.Read_Socket(byRecv);

	CString strRecvSocket, strLog;
	strRecvSocket.Format("%s", byRecv);
	m_strRecvCmd += strRecvSocket;

	while (!m_strRecvCmd.IsEmpty()) 
	{
		int nStart = m_strRecvCmd.Find("@");
		int nEnd = m_strRecvCmd.Find("\n");

		if (nEnd < 0) break;	// 버퍼에 들어오는 중...

		if (nStart < 0 || nStart > nEnd) 
		{
			strLog.Format("[OnClientReceive] <<Error>> - Start(%d), End(%d).\n%s", nStart, nEnd, m_strRecvCmd);
			g_objLogFile.Save_VisionLog(strLog);
			m_strRecvCmd.Delete(0, nEnd + 1);	// 쓰레기값이 채워져 있어서...
			continue;
		}

		CString strRecv = m_strRecvCmd.Mid(nStart + 1, nEnd - nStart - 1);
		m_strRecvCmd.Delete(0, nEnd + 1);

		// Inspector Log ////////////////////////////////////////////////////////////
		strLog.Format("[<-] : %s", strRecv);
		g_objLogFile.Save_VisionLog(strLog);
		/////////////////////////////////////////////////////////////////////////////
		
		g_objInspector.Receive_Command(VISION_PC1, strRecv);
	/*	CString strXml = strRecv.Right(strRecv.GetLength() - 13);
		if (!Extract_Xml(strXml)) return 0;*/
		if (!m_strRecvCmd.IsEmpty()) Sleep(1);

	}

	return 0;
}



void CInspectV1::Send_Message(CString sMessage)
{
	CString strSendSocket;
	strSendSocket.Format("@%s\n", sMessage);

	char chSend[4096] = { 0 };
	int nLength = strSendSocket.GetLength();
	memcpy(chSend, (LPSTR)(LPCSTR)strSendSocket, nLength);

	m_Client.Write_Socket((BYTE*)chSend, nLength);
}

///////////////////////////////////////
