// Inspector.h : 헤더 파일
//
#pragma once

#include "InspectV1.h"



const int VISION_ALL	= 0;	// PC1, PC2, PC3, PC4, PC5
const int VISION_PC1	= 1;	// Top Camera1, Btm Camera1
const int VISION_PC2	= 2;	// Top Camera2, Btm Camera2


class CInspector : public CWnd
{
	DECLARE_DYNAMIC(CInspector)

public:
	CInspector();
	virtual ~CInspector();

protected:
	DECLARE_MESSAGE_MAP()
	

private:
	CInspectV1	m_Vision1;

	CString		m_sMZID;

	int		m_nStatusPC1;	// Vision PC1 상태 (0:Not Ready, 1:Ready, 2:Run)
	int		m_nFOBStatus;
	
	BOOL	m_bLotReady1;

	int		m_nBCScanReq, m_nTCScanReq;
	int		m_nBCScanCnt, m_nTCScanCnt;

	void Get_StatusRequest(int nVPc);
	void Get_StatusReply(int nVPc, CString sStatus);
	void Get_StatusUpdate(int nVPc, CString sStatus);

	void Get_FOBUpdate(int nVPc, CString sStatus);
	void Get_FOBReply(int nVPc, CString sStatus);

	void Get_LotReady(int nVPc, CString sMZID, CString sMZNo);
	void Get_ScanComplete(int nVPc, CString sGbn, CString sMZID, CString sMZNo, CString sTrayNo, CString sLensNo);
	void Get_InspectComplete(int nVPc, CString sGbn, CString sMZID, CString sMZNo, CString sTrayNo, CString sLensNo, CString sJudge, CString sNgCode);
	
	void Get_AMoveRequest(int nVPc, CString sGbn, CString sZ1);
	void Get_PositionRequest(int nVPc, CString sGbn);
	void Get_ReloadRequest(int nVPc, CString sMZID, CString sGbn);
	void Get_TriggerRequest(int nVPc, CString sGbn, CString sMZNo, CString sCtZigID, CString sZigNo, CString sLensNo);
	void Get_AlignRequest(int nVPc, CString sMZID, CString sGbn, CString sMGZNo, CString sZigNo, CString sDeltaX, CString sDeltaY);
	
	void Get_ErrorRequest(int nVPc, CString sErrNo, CString sErrMsg);

	void Send_Command(int nVPc, CString sCommand);
	void Exception_Log(int nVPc, CString sFunc, CString sGbn, int nLotNo, int nTrayNo, int nCmNo, int nCase);	// Recevie Exception Log
	
	
public:
	double m_dTopZ;
	double Get_TopZ() { return m_dTopZ; }

	double m_dBtmZ;
	double Get_BtmZ() { return m_dBtmZ; }
	
	CString m_strLog;

	void Initialize();
	void Terminate();

	void Receive_Command(int nVPc, CString sCommand);

	void Set_StatusRequest();
	void Set_StatusReply(int nStatus);
	void Set_StatusUpdate(int nStatus);
	
	void Set_LotStart(CString sMZID, int nMZNo, int nTrayCount, int nLensCount, CString sModel);
	void Set_LotEnd(CString sMZID, int nMZNo);
	void Set_LotReadyDone(CString sMZID, int nMZNo);

	void Set_LoadComplete(CString sGbn, CString sMZID, int nMZNo, CString sTrayID, int nTrayNo, int nLensNo);
	void Set_MoveComplete(int nVPc, CString sGbn);

	void Set_PositionReply(int nVPc, CString sGbn, double dZ1);
	void Set_ReloadComplete(int nVPc, CString sGbn);
	
	void Set_InitialRequest(int nVPc);
	void Set_TimeUpdate(int nVPc);

	void Set_FOBRequest();

	BOOL Check_Connect(int nVPc);
	BOOL Check_LotReady();

	void Test_Command();
};

extern CInspector g_objInspector;

///////////////////////////////////////////////////////////////////////////////
