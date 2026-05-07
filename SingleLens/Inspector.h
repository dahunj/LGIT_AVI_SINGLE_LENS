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

	int		m_nStatusPC1;	// Vision PC1 상태 (0:Not Ready, 1:Ready, 2:Run)
	
	BOOL	m_bLotReady1;


	void Get_StatusRequest(int nVPc);
	void Get_StatusReply(int nVPc, CString sStatus);
	void Get_StatusUpdate(int nVPc, CString sStatus);

	void Get_LotReady(int nVPc, CString sLotId, CString sLotNo);
	void Get_ScanComplete(int nVPc, CString sGbn, CString sLotId, CString sLotNo, CString sTrayNo, CString sCmNo);
	void Get_InspectComplete(int nVPc, CString sGbn, CString sLotId, CString sLotNo, CString sTrayNo, CString sCmNo, CString sJudge, CString sCode);
	void Get_AMoveRequest(int nVPc, CString sGbn, CString sZ1, CString sZ2, CString sX, CString sY, CString sT, CString sR);
	void Get_PositionRequest(int nVPc, CString sGbn);
	void Get_ReloadRequest(int nVPc, CString sPc);


	void Get_ErrorRequest(int nVPc, CString sGbn, CString sLotId, CString sLotNo, CString sTrayNo, CString sCmNo, CString sErrNo, CString sErrMsg);

	void Send_Command(int nVPc, CString sCommand);
	void Exception_Log(int nVPc, CString sFunc, CString sGbn, int nLotNo, int nTrayNo, int nCmNo, int nCase);	// Recevie Exception Log



	
public:
	void Initialize();
	void Terminate();

	void Receive_Command(int nVPc, CString sCommand);

	void Set_StatusRequest(int nVPc);
	void Set_StatusReply(int nVPc, int nStatus);
	void Set_StatusUpdate(int nVPc, int nStatus);


	void Set_LotStart(int nVPc, CString sLotId, int nLotNo, int nTrayCount, int nCmCount, CString sModel);
	void Set_LotEnd(int nVPc, CString sLotId, int nLotNo);
	void Set_LoadComplete(int nVPc, CString sGbn, CString sLotId, int nLotNo, int nTrayNo, int nCmNo, double dHeight);
	void Set_MoveComplete(int nVPc, CString sGbn);

	void Set_PositionReply(int nVPc, CString sGbn, double dZ1, double dZ2, double dX, double dY, double dT, double dR);
	void Set_ReloadComplete(int nVPc, CString sPc);
	
	void Set_InitialRequest(int nVPc);
	void Set_TimeUpdate(int nVPc);

	BOOL Check_Connect(int nVPc);
	BOOL Check_LotReady();

	void Test_Command();
};

extern CInspector g_objInspector;

///////////////////////////////////////////////////////////////////////////////
