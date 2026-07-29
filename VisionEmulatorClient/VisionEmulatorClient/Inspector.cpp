// Inspector.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisionEmulatorClient.h"
#include "Inspector.h"
#include "LogFile.h"

// CInspector
IMPLEMENT_DYNAMIC(CInspector, CWnd)

CInspector g_objInspector;

CCriticalSection g_csInspectSend;	// Send_Command 문제 해결하기 위함
CCriticalSection g_csInspectRecv;	// Receive_Command 문제 해결하기 위함


CInspector::CInspector()
{
	
	//m_nStatusPC1 = 0;		// Vision PC1 상태 (0:Stop, 1:Run)
	//m_nStatusPC2 = 0;		// Vision PC2 상태 (0:Stop, 1:Run)
	//m_nStatusPC3 = 0;		// Vision PC3 상태 (0:Stop, 1:Run)

	//m_bLotReady1 = FALSE;
	//m_bLotReady2 = FALSE;
	//m_bLotReady3 = FALSE;
}


CInspector::~CInspector()
{
}


BEGIN_MESSAGE_MAP(CInspector, CWnd)
END_MESSAGE_MAP()



// CInspector 메시지 처리기입니다.


void CInspector::Receive_Command(int nVPc, CString sCommand)
{
	/*EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (!pEquipData->bUseInspectTray && !pEquipData->bUseInspectBtm && !pEquipData->bUseInspectTop) return;
*/
	g_csInspectRecv.Lock();

	char chSep = ',';
	CString strCmd, strOp, strLog;

	AfxExtractSubString(strCmd, sCommand, 0, chSep);
	AfxExtractSubString(strOp, sCommand, 1, chSep);

	// Inspector Log ////////////////////////////////////////
	strLog.Format("[H<-V%d] : %s", nVPc, sCommand);
	g_objLogFile.Save_VisionLog(strLog);
	/////////////////////////////////////////////////////////

	CString strA[8];
	for (int i = 0; i < 8; i++) AfxExtractSubString(strA[i], sCommand, i + 2, chSep);

	if (strCmd == "CONNECT") {
		if (strOp == "REQUEST") Get_ConnectRequest(nVPc);
		if (strOp == "REPLY")	Get_ConnectReply(nVPc);

	} else if (strCmd == "STATUS") {
		if (strOp == "REQUEST") Get_StatusRequest(nVPc);
		if (strOp == "REPLY")	Get_StatusReply(nVPc, strA[0]);
		if (strOp == "UPDATE")	Get_StatusUpdate(nVPc, strA[0]);

	}
	else if (strCmd == "LOAD")
	{
		//						Get_LoadComplete    			sGBn,  MZID,   MZNo,     TrayNo1, TNo,     LensNo,  
		if (strOp == "COMPLETE") Get_LoadComplete(strA[0], strA[1], strA[2], strA[3], strA[4], strA[5]);
	}
	else if (strCmd == "LOT")
	{
		if (strOp == "START") Get_LotStart(strA[0], strA[1]);
	}
	else if (strCmd == "RECIPE")
	{
		if(strOp == "LOAD") Get_RecipeLoad(strA[0], strA[1], strA[2], strA[3]);
	}

	
	
	

	g_csInspectRecv.Unlock();
}


void CInspector::Get_ConnectRequest(int nInspector)
{
	//if (nInspector == VISION_PC1) m_bConnectPC1 = TRUE;
	
	Set_ConnectReply(nInspector);
}

void CInspector::Get_ConnectReply(int nInspector)
{
	//if (nInspector == VISION_PC1) m_bConnectPC1 = TRUE;
	
}

void CInspector::Get_ConnectEnd(int nInspector)
{
	//if (nInspector == VISION_PC1) m_bConnectPC1 = FALSE;
	
}


void CInspector::Get_StatusRequest(int nInspector)
{
	//BOOL bStatus = g_objSequenceMain.Is_MainThreadRun();
	//if (bStatus) Set_StatusReply(nInspector, 1);
	//else Set_StatusReply(nInspector, 0);
}

void CInspector::Get_StatusReply(int nInspector, CString sStatus)
{
	if (nInspector == VISION_PC1) m_nStatusPC1 = atoi(sStatus);
	/*if (nInspector == INSPECTOR_PC2) m_nStatusPC2 = atoi(sStatus);
	if (nInspector == INSPECTOR_PC3) m_nStatusPC3 = atoi(sStatus);
	if (nInspector == INSPECTOR_PC4) m_nStatusPC4 = atoi(sStatus);*/
}

void CInspector::Get_StatusUpdate(int nInspector, CString sStatus)
{
	Set_StatusReply(nInspector);
}

void CInspector::Get_LotStart(CString sMZID, CString sMZNo)
{
	 int nMNo = atoi(sMZNo);

	Set_LotReady(1, sMZID, nMNo);
	/*Set_LotReady(2, gData.sLotID[0]);
	Set_LotReady(3, gData.sLotID[0]);
	Set_LotReady(4, gData.sLotID[0]);*/
}

void CInspector::Get_RecipeLoad(CString sGbn, CString sMZID, CString sTrayID, CString sRecipe)
{
	if(sGbn == "TC") Set_RecipeComplete(1, sGbn);
	if(sGbn == "BC") Set_RecipeComplete(1, sGbn);
}


void CInspector::Send_Command(int nVPc, CString sCommand)
{
	// 	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	// 	if (!pEquipData->bUseInspectBtm && !pEquipData->bUseInspectTop) return;

	g_csInspectSend.Lock();		// Critical Section

	if (nVPc == VISION_ALL || nVPc == VISION_PC1) m_Vision1.Send_Message(sCommand);
	/*if (nVPc == VISION_ALL || nVPc == VISION_PC2) m_Vision2.Send_Message(sCommand);
	if (nVPc == VISION_ALL || nVPc == VISION_PC3) m_Vision3.Send_Message(sCommand);*/

	// Inspector Log //////////////////////////////////////
	CString strLog;
	strLog.Format("[H->V%d] : %s", nVPc, sCommand);
	g_objLogFile.Save_VisionLog(strLog);
	///////////////////////////////////////////////////////

	g_csInspectSend.Unlock();	// Critical Section
}


void CInspector::Initialize()
{
	m_Vision1.Create(NULL, NULL, WS_CHILD, CRect(0,0,0,0), this, 0);

	
	/*m_Vision2.Create(NULL, NULL, WS_CHILD, CRect(0,0,0,0), this, 0);
	m_Vision3.Create(NULL, NULL, WS_CHILD, CRect(0,0,0,0), this, 0);*/
		

	/*m_Vision2.Init_Socket();
	m_Vision3.Init_Socket();*/

}



void CInspector::Connect()
{
	m_Vision1.Initialize();
}

void CInspector::Terminate()
{
	m_Vision1.Terminate();
	//m_Vision1.Exit_Socket();
	/*m_Vision2.Exit_Socket();
	m_Vision3.Exit_Socket();*/
}



void CInspector::Get_LoadComplete(CString sGbn, CString sMZID, CString sMZNo, CString sTrayID, CString sTNo, CString sLensNo)
{
	int nTNo1 = 0;
	int nCNo1 = 0;

	nTNo1 = atoi(sTNo);
	nCNo1 = atoi(sLensNo);
	
	if (nTNo1 != -1 && nCNo1 != -1) Set_TriggerRequest(VISION_PC1, sGbn, sMZID, sMZNo, sTNo, sLensNo);
	Sleep(10);

	if (nTNo1 != -1 && nCNo1 != -1) Set_ScanComplete(VISION_PC1, sGbn, sMZID, sMZNo, sTNo, sLensNo);
	Sleep(10);
		
	if (nTNo1 != -1 && nCNo1 != -1) Set_InspectComplete(VISION_PC1, sGbn, sMZID, sMZNo, sTNo, sLensNo);
	Sleep(10);
	
}

void CInspector::Set_RecipeComplete(int nInspector, CString sGbn)
{
	CString	strSendCmd;
	strSendCmd.Format("RECIPE,COMPLETE,%s,%s,%s", sGbn,"TrayID","Recipe");
	Send_Command(nInspector, strSendCmd);
}



void CInspector::Set_TriggerRequest(int nInspector, CString sGbn, CString sMZID, CString sMZNo, CString sTNo, CString sLensNo)
{
	CString	strSendCmd;
	strSendCmd.Format("TRIGGER,REQUEST,%s,%s,%s,%s,%s", sGbn, sMZID, sMZNo, sTNo, sLensNo);
	Send_Command(nInspector, strSendCmd);
}

void CInspector::Set_ScanComplete(int nInspector, CString sGbn, CString sMZID, CString sMZNo, CString sTNo, CString sLensNo)
{
	CString	strSendCmd;
	strSendCmd.Format("SCAN,COMPLETE,%s,%s,%s,%s,%s", sGbn, sMZID, sMZNo, sTNo, sLensNo);
	Send_Command(nInspector, strSendCmd);
}

void CInspector::Set_InspectComplete(int nInspector, CString sGbn, CString sMZID, CString sMZNo, CString sTNo, CString sLNo)
{
	CString	strSendCmd;

	int nPortNo, nTNo, nCNo;
	nPortNo = atoi(sMZNo);
	nTNo = atoi(sTNo);
	nCNo = atoi(sLNo);

	if(nPortNo <= 0 || nTNo <=0 || nCNo <= 0)
	{
		g_objLogFile.Save_VisionLog("Check Index Numbers");
		return;
	}


	int nRand = Get_Random(0, 99);
	int nNg = 100;

	int nJudge = nRand < nNg ? 2 : 1;


	if(nJudge == 2 && nRand < 50)
	{

		m_sJudge[nPortNo - 1][nTNo - 1][nCNo - 1] = "N";
		m_sCode[nPortNo - 1][nTNo - 1][nCNo - 1] = "EM";
	}
	else if (nJudge == 2  && nRand < 99)
	{
		m_sJudge[nPortNo - 1][nTNo - 1][nCNo - 1] = "N";
		m_sCode[nPortNo - 1][nTNo - 1][nCNo - 1] = "NG - 2";
	}
	/*else if (nJudge == 2  && nRand < 30)
	{
		m_sJudge[nPortNo - 1][nTNo - 1][nCNo - 1] = "N";
		m_sCode[nPortNo - 1][nTNo - 1][nCNo - 1] = "NG - 3";
	}
	else if (nJudge == 2 )
	{
		m_sJudge[nPortNo - 1][nTNo - 1][nCNo - 1] = "N";
		m_sCode[nPortNo - 1][nTNo - 1][nCNo - 1] = "NG - 4";
	}*/
	else 
	{

		m_sJudge[nPortNo - 1][nTNo - 1][nCNo - 1] = "G";
		m_sCode[nPortNo - 1][nTNo - 1][nCNo - 1] = "G";
	}
	
	
	strSendCmd.Format("INSPECT,COMPLETE,%s,%s,%s,%s,%s,%s,%s", sGbn, sMZID, sMZNo, sTNo, sLNo, m_sJudge[nPortNo - 1][nTNo - 1][nCNo - 1], m_sCode[nPortNo - 1][nTNo - 1][nCNo - 1]);
	Send_Command(nInspector, strSendCmd);
}


int CInspector::Get_Random(int nStart, int nEnd)
{
	static BOOL bSeed = FALSE;
	if (nStart >= nEnd) return 0;
	if (!bSeed) { srand((unsigned)time(NULL)); bSeed = TRUE; }
	return (rand() % (nEnd - nStart + 1) + nStart);
}



void CInspector::Set_ConnectReply(int nInspector)
{
	CString	strSendCmd;
	strSendCmd.Format("CONNECT,REQUEST");
	Send_Command(nInspector, strSendCmd);
}

void CInspector::Set_StatusReply(int nInspector)
{
	CString	strSendCmd;
	strSendCmd.Format("STATUS,REPLY,1");
	Send_Command(nInspector, strSendCmd);
}

void CInspector::Set_LotReady(int nInspector, CString sMZID, int nMZNo)
{
	CString	strSendCmd;
	strSendCmd.Format("LOT,READY,%s,%d,1928,2059,MEM", sMZID, nMZNo);
	Send_Command(nInspector, strSendCmd);
}

