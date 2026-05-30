#pragma once

#include "InspectV1.h"
//#include "InspectV2.h"
//#include "InspectV3.h"

const int VISION_ALL	= 0;	// PC1, PC2, PC3, PC4, PC5
const int VISION_PC1	= 1;	// T1, T2, B1, B2 (Jig 1/2)
const int VISION_PC2	= 2;	// T1, T2, B1, B2 (Jig 3/4)
const int VISION_PC3	= 3;	// T1, T2, B1, B2 (Jig 5), Tray Vision
// CInspector

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

	int		m_nStatusPC1;	// Vision PC1 ป๓ลย (0:Stop, 1:Run)

	BOOL	m_bLotReady1;


private:

	void Get_ConnectRequest(int nInspector);
	void Get_ConnectReply(int nInspector);
	void Get_ConnectEnd(int nInspector);

	void Get_StatusRequest(int nInspector);
	void Get_StatusReply(int nInspector, CString sStatus);
	void Get_StatusUpdate(int nInspector, CString sStatus);

	void Send_Command(int nInspector, CString strSend);
	void Exception_Log(CString sFunc, CString sGbn, int nCase);	// Receive Exception Log

	void Get_LoadComplete(CString sGbn, CString sMZID, CString sMZNo, CString sTrayID, CString sTNo, CString sLensNo);
	void Get_LotStart(CString sMZID, CString sMZNo);
public:

	CString m_sJudge[2][30][30];
	CString m_sCode[2][30][30];



	void Initialize();
	void Connect();
	void Terminate();

	void Receive_Command(int nVPc, CString sCommand);


	void Set_ConnectReply(int nInspector);
	void Set_StatusReply(int nInspector);

	void Set_LotReady(int nInspector, CString sMZID, int nMZNo);

	void Set_TriggerRequest(int nInspector, CString sGbn, CString sMZID, CString sMZNo, CString sTNo, CString sLensNo);
	void Set_ScanComplete(int nInspector, CString sGbn, CString sMZID, CString sMZNo, CString sTNo, CString sLensNo);
	void Set_InspectComplete(int nInspector, CString sGbn, CString sMZID, CString sMZNo, CString sTNo, CString sLNo);


	int Get_Random(int nStart, int nEnd);

};



extern CInspector g_objInspector;