#pragma once


// CMesAgent

class CMesAgent : public CWnd
{
	DECLARE_DYNAMIC(CMesAgent)

public:
	CMesAgent();
	virtual ~CMesAgent();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnClientConnect(WPARAM wConnect, LPARAM lParam);
	afx_msg LRESULT OnClientReceive(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClientClose(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

private:
	CClientSocketCS m_Client;

	BOOL	m_bConnected;
	BOOL	m_bHostOnline;
	CString m_strRecvCmd;


private:
	void Get_ReciveData();
	void Get_ControlState(CString sFlag);	// 1:Online, 2:Offline
	void Get_TimeSync();

	void Get_LotStart(CString sLotId, CString sMGZId);
	void Get_LotIDFail(CString sLotId, CString sCode, CString sText);
	
	void Get_PPSelect(CString sLotId, CString sMGZID, CString sRecipe, CString sLensCount);
	void Get_MGZCancel(CString sMGZId, CString sCode, CString sText);

	void Get_MGZ_Confirm(CString sMGZId);
	void Get_PPUpload_Confirm(CString sRecipeID);
	void Get_PPUpload_Fail(CString sRecipeID, CString sFailCode, CString sFailText);

	void Get_TrayID_Confirm(CString sStrings);
	void Get_Tray_Cancel(CString sTrayID, CString sCode, CString sText);

	void Get_Terminal(CString sMsg);

	void Send_Command(CString sSend);

public:
	void Initialize();
	void Terminate();

	BOOL Is_Connected() { return m_bConnected; }
	BOOL Is_HostOnline() { return m_bHostOnline; }
	BOOL Exist_Recipe(CString sRecipe);

	void Set_OperUpdate(CString sOperId);				// Operator ID 변경시 보고
	void Set_ControlState(int nFlag, CString sOperId);	// 1:Onine, 2:Offline
	void Set_EquipState(int nFlag);						// 
	void Set_ErrorUpdate(int nFlag, int nErrNo, int nCategory);	// nFlag(0:해제, 1:발생)
		
	void Set_LotAbort(CString sLotId, CString sRecipe);
	void Set_IdleSet(CString sOperId, CString sCode);	// 비가동 집계 Set
	void Set_IdleReset(CString sOperId, CString sCode);	// 비가동 집계 Reset
	void Set_IdleReport(CString sOperId, CString sCode, CString sText, CString sSTime, CString sETime);

	void Set_MGZIDReport(int nType, CString sMGZID);	//1: Load, 2:Unload 
	void Set_PPSelectedReport(CString sLotId, CString sMGZId, CString sRecipeId);
	void Set_PPUploadCompletedReport(CString sLotId, CString sMGZId, CString sRecipeId);

	void Set_LotStartedReport(CString sLotId, CString sMGZId, CString sRecipe);
	
	void Set_TrayIDReport(int nType, CString sTrayID); //1: Load, 2:Unload 
	void Set_TrayStartedReport(CString sLotID, CString sTrayID, CString sRecipeID);

	void Set_ProductCompletedReport(CString sLotID, CString sTrayID, CString sRecipeID, int nPocketNo, CString sResult, CString sReasonCode);

	void Set_TrayCompleted(CString sLotID, CString sMGZID, CString sRecipe, CString sTrayID);
	void Set_LotCompleted(CString sLotID, CString sMZID, CString sRecipe);

	void Set_AlarmLog(int nErrNo, CString sErrMsg, int nCategory);
	void Reset_AlarmLog();

};


extern CMesAgent g_objMesAgent;

