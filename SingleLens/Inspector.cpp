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
		if (strOp == "REQUEST") Get_AMoveRequest(nVPc, strA[0], strA[1]);

	} else if (strCmd == "POSITION") {
		if (strOp == "REQUEST") Get_PositionRequest(nVPc, strA[0]);
	
	} else if (strCmd == "RELOAD") {
		if (strOp == "REQUEST") Get_ReloadRequest(nVPc, strA[0]);

	} 
	else if (strCmd == "ERROR")
	{
		if (strOp == "REQUEST") Get_ErrorRequest(nVPc, strA[0], strA[1]);
	}
	else if (strCmd == "TRIGGER")
	{
		if (strOp == "REQUEST") Get_TriggerRequest(nVPc, strA[0], strA[1], strA[2], strA[3], strA[4]);
	}
	else if (strCmd == "FOB")
	{
		if (strOp == "UPDATE") Get_FOBUpdate(nVPc, strA[0]);
		if (strOp == "REPLY") Get_FOBReply(nVPc, strA[0]);
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
	Set_StatusReply(nStatus);
}

void CInspector::Get_StatusReply(int nVPc, CString sStatus)
{
	if (nVPc == VISION_PC1) m_nStatusPC1 = atoi(sStatus);
	
}

void CInspector::Get_StatusUpdate(int nVPc, CString sStatus)
{
	if (nVPc == VISION_PC1) m_nStatusPC1 = atoi(sStatus);

}

void CInspector::Get_LotReady(int nVPc, CString sMZID, CString sMZNo)
{
	int nMNo = atoi(sMZNo) - 1;
	if (nMNo < 0 || nMNo > 7) return;

	if (sMZID != gData.sMZID[eMZ::Load]) return;
	if (nVPc == VISION_PC1) m_bLotReady1 = TRUE;
	Set_LotReadyDone(sMZID, nMNo);

}

void CInspector::Get_ScanComplete(int nVPc, CString sGbn, CString sMZID, CString sMZNo, CString sTrayNo, CString sLensNo)
{
	int nMNo = atoi(sMZNo);
	int nTNo = atoi(sTrayNo);	// Tray Index
	int	nLNo = atoi(sLensNo);	// CM Index

	int nXPos = 0, nYPos = 0;

	//vision direction fixY
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if(pEquipData->nVisionDir == eVDir::fixY)
	{
		nYPos = ((nLNo-1) / gData.nLensCntX);
		nXPos = (nLNo-1) % gData.nLensCntX;
	}
	else
	{
		nXPos = ((nLNo-1) / gData.nLensCntY);
		nYPos = (nLNo-1) % gData.nLensCntY;
	}	

	if (nTNo < 0 || nTNo > 99 || nLNo < 0 || nLNo > 200) { g_objCommon.Show_Error(6101); return; }

	int nV = (sGbn == "TC" ? eVision::TC : (sGbn == "BC" ? eVision::BC : -1));
	if (nV == -1) { g_objCommon.Show_Error(6102); return; }
		
	if(nV == eVision::TC) //Tc
	{
		int nCase = g_objSequenceMain.Get_MainRunCase(AUTO_TOP_INSPECT);
		DWORD dwTick = GetTickCount();
		while (nCase != 5) 
		{ 
			if(GetTickCount() - dwTick > 0) break;
			else if(nCase == 5) break;
			//Exception_Log("Scan Complete", sGbn, nCase); 
			//return;
		}
	
		gData.bScanDone[eVision::TC] = TRUE;
		gData.InfoMainIndex[eMainIndex::Top][nXPos][nYPos] = eLensState::TopDone;
		//g_objSequenceMain.Set_MainRunCase(AUTO_TOP_INSPECT, 10);

	}
	else if(nV == eVision::BC) // Bc
	{
		int nCase = g_objSequenceMain.Get_MainRunCase(AUTO_BTM_INSPECT);
		DWORD dwTick = GetTickCount();
		while (nCase != 5) 
		{ 
			if(GetTickCount() - dwTick > 0) break;
			else if(nCase == 5) break;
			//Exception_Log("Scan Complete", sGbn, nCase); 
			//return;
		}
				
		gData.bScanDone[eVision::BC] = TRUE;
		gData.InfoMainIndex[eMainIndex::Btm][nXPos][nYPos] = eLensState::BtmDone;
		//g_objSequenceMain.Set_MainRunCase(AUTO_BTM_INSPECT, 10);
	}
}

void CInspector::Get_InspectComplete(int nVPc, CString sGbn, CString sMZID, CString sMZNo, CString sTrayNo, CString sLensNo, CString sJudge, CString sNgCode)
{
	int nMNo = atoi(sMZNo) - 1;
	int nTNo = atoi(sTrayNo) - 1;	// Tray Index
	int	nLNo = atoi(sLensNo) - 1;	// CM Index

	if (nTNo < 0 || nTNo > 10 || nLNo < 0 || nLNo > ZIG_X*ZIG_Y) { g_objCommon.Show_Error(6101); return; }

	int nV = (sGbn == "TC" ? eVision::TC : (sGbn == "BC" ? eVision::BC : -1));
	if (nV == -1) { g_objCommon.Show_Error(6102); return; }


	gData.cJudgeCode[nMNo][nTNo][nLNo][nV] = *(LPSTR)(LPCTSTR)sJudge;


	int nMode = theApp.Get_MainMode();
	int nPreInfo = gData.nInspectInfo[nMNo][nTNo][nLNo];

	if (sJudge == "N") 
	{  
		gData.nInspectInfo[nMNo][nTNo][nLNo] = 2;
	}	// NG
	else if (sJudge != "G")  // Good
	{ 
		if (nPreInfo < 2 || nPreInfo > 8) gData.nInspectInfo[nMNo][nTNo][nLNo] = 2;  
	}	

	gData.byInspectDone[nMNo][nTNo][nLNo] |= (1 << nV);
	
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	if (pEquipData->bUseTopVision && ((gData.byInspectDone[nMNo][nTNo][nLNo] >> 0) & 1) == 0) return;	// TC
	if (pEquipData->bUseBtmVision  && ((gData.byInspectDone[nMNo][nTNo][nLNo] >> 1) & 1) == 0) return;	// BC

}

void CInspector::Get_AMoveRequest(int nVPc, CString sGbn, CString sZ1)
{
	if (!g_objSequenceInit.Get_InitComplete()) { g_objCommon.Show_Error(50); return; }


	EQUIP_DATA *m_pEquipData = g_objDataManager.Get_pEquipData();


	if(sGbn == "TC") m_dTopZ = atof(sZ1);
	if(sGbn == "BC") m_dBtmZ = atof(sZ1);

	m_pEquipData->dTopStartZ = m_dTopZ;
	m_pEquipData->dBtmStartZ = m_dBtmZ;
	if(theApp.Get_MainMode() == MODE_MANUAL)
	{
		if(sGbn == "TC") g_objAJinAXL.Move_Absolute(AX_TOP_INSPECTOR_Z,m_pEquipData->dTopStartZ );
		if(sGbn == "BC") g_objAJinAXL.Move_Absolute(AX_BTM_INSPECTOR_Z,m_pEquipData->dBtmStartZ );
		while (1)
		{
			theApp.DoEvents();
			if(g_objAJinAXL.Is_MoveDone(AX_TOP_INSPECTOR_Z, m_pEquipData->dTopStartZ))
			{
				if(sGbn == "TC") g_objInspector.Set_MoveComplete(VISION_PC1, "TC");				
				break;
			}
			if(g_objAJinAXL.Is_MoveDone(AX_BTM_INSPECTOR_Z, m_pEquipData->dTopStartZ))
			{				
				if(sGbn == "BC") g_objInspector.Set_MoveComplete(VISION_PC1, "BC");
				break;
			}

		}
	}

}

void CInspector::Get_PositionRequest(int nVPc, CString sGbn)
{
	if (!g_objSequenceInit.Get_InitComplete()) { g_objCommon.Show_Error(50); return; }

	if(sGbn == "TC") Set_PositionReply(VISION_PC1, "TC", g_objAJinAXL.Get_Position(AX_TOP_INSPECTOR_Z));
	if(sGbn == "BC") Set_PositionReply(VISION_PC1, "BC", g_objAJinAXL.Get_Position(AX_BTM_INSPECTOR_Z));
		
}

void CInspector::Get_TriggerRequest(int nVPc, CString sGbn, CString sMZNo, CString sCtZigID, CString sZigNo, CString sLensNo)
{
	if(sGbn == "TC")
	{
		g_objSequenceMain.Set_MainRunCase(AUTO_TOP_INSPECT, eTopBr::Trigger);
	}

	if(sGbn == "BC")
	{
		g_objSequenceMain.Set_MainRunCase(AUTO_BTM_INSPECT, eBtmBr::Trigger);
	}
}

void CInspector::Get_ReloadRequest(int nVPc, CString sPc)
{
	// bScanDone[4][5] --> [4]=>0:B1,1:B2,2:T1,3:T2 / [5]=>0:C1,1:C2,2:C3,3:C4,4:C5
	CString strVPC;
	strVPC.Format("PC%d", nVPc);
	if (sPc != strVPC) return;
		
	Set_ReloadComplete(1, sPc);
}

void CInspector::Get_ErrorRequest(int nVPc, CString sErrNo, CString sErrMsg)
{
	int nErrNo = atoi(sErrNo);

	int nMode = theApp.Get_MainMode();
	if (nMode == MODE_WORK || nMode == MODE_OPERATOR) g_objCommon.Show_Error(nErrNo);
	
}

void CInspector::Set_StatusUpdate(int nStatus)
{
	CString	strSendCmd;
	strSendCmd.Format("FOB,UPDATE, %d", nStatus);
	Send_Command(VISION_PC1, strSendCmd);
}

void CInspector::Get_FOBUpdate(int nVPc, CString sStatus)
{
	
}


void CInspector::Get_FOBReply(int nVPc, CString sStatus)
{

}

void CInspector::Exception_Log(int nVPc, CString sFunc, CString sGbn, int nLotNo, int nTrayNo, int nCmNo, int nCase)
{
	CString strLog;
	strLog.Format("%s Exception ==> PC:%d, Vision:%s, LotNo:%d, TrayNo:%d, CmNo:%d, Case:%d", sFunc, nVPc, sGbn, nLotNo, nTrayNo, nCmNo, nCase);
	
}






/////////////////////////////////////////////////////////////////////////////
// Set Command

void CInspector::Set_StatusRequest()
{
	CString	strSendCmd;
	strSendCmd.Format("STATUS,REQUEST");
	Send_Command(VISION_PC1, strSendCmd);
}

void CInspector::Set_StatusReply(int nStatus)
{
	CString	strSendCmd;
	strSendCmd.Format("STATUS,REPLY,%d", nStatus);
	Send_Command(VISION_PC1, strSendCmd);
}



void CInspector::Set_LotStart(CString sMZID, int nMZNo, int nTrayCount, int nLensCount, CString sModel)
{
	m_bLotReady1 = FALSE;

	CString strSendCmd;
	strSendCmd.Format("LOT,START,%s,%d,%d,%d,%s", sMZID, nMZNo, nTrayCount, nLensCount, sModel);
	Send_Command(VISION_PC1, strSendCmd);
}

void CInspector::Set_LotEnd(CString sMZID, int nMZNo)
{
	CString	strSendCmd;
	strSendCmd.Format("LOT,END,%s,%d", sMZID, nMZNo);
	Send_Command(VISION_PC1, strSendCmd);
}

void CInspector::Set_LotReadyDone(CString sMZID, int nMZNo)
{
	CString	strSendCmd;
	strSendCmd.Format("LOT,RDYDONE,%s,%d", sMZID, nMZNo);
	Send_Command(VISION_PC1, strSendCmd);
}

void CInspector::Set_LoadComplete(CString sGbn, CString sMZID, int nMZNo, CString sTrayID, int nTrayNo, int nLensNo)
{
	CString	strSendCmd, strTemp;
	strSendCmd.Format("LOAD,COMPLETE,%s,%s,%d,%s,%d,%d", sGbn, sMZID, nMZNo, sTrayID, nTrayNo, nLensNo);
	if(sGbn == "TC") gData.bScanDone[eVision::TC] = FALSE;
	if(sGbn == "BC") gData.bScanDone[eVision::BC] = FALSE;
	Send_Command(VISION_PC1, strSendCmd);
}

void CInspector::Set_MoveComplete(int nVPc, CString sGbn)
{
	CString	strSendCmd;
	strSendCmd.Format("MOVE,COMPLETE,%s", sGbn);
	Send_Command(VISION_PC1, strSendCmd);
}

void CInspector::Set_PositionReply(int nVPc, CString sGbn, double dZ1)
{
	CString	strSendCmd;
	strSendCmd.Format("POSITION,REPLY,%s,%0.3lf", sGbn, dZ1);
	Send_Command(VISION_PC1, strSendCmd);
}

void CInspector::Set_ReloadComplete(int nVPc, CString sPc)
{
	CString	strSendCmd;
	strSendCmd.Format("RELOAD,COMPLETE");
	Send_Command(VISION_PC1, strSendCmd);
}

void CInspector::Set_InitialRequest(int nVPc)
{
	CString	strSendCmd;
	strSendCmd.Format("INITIAL,REQUEST");
	Send_Command(VISION_PC1, strSendCmd);
}

void CInspector::Set_TimeUpdate(int nVPc)
{
	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strTime;
	strTime.Format("%04d-%02d-%02d %02d:%02d:%02d.%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

	CString	strSendCmd;
	strSendCmd.Format("TIME,UPDATE,%s", strTime);
	Send_Command(VISION_PC1, strSendCmd);
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
	if (!pEquipData->bUseBtmVision && !pEquipData->bUseTopVision) m_bLotReady1 = TRUE;
	return (m_bLotReady1 );

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////

void CInspector::Test_Command()
{
}
