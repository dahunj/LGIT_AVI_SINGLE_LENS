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

	void Get_LotStart(CString sLotId, CString sRecipe, CString sCmCount, CString sVendor, CString sConfig);
	void Get_LotCancel(CString sLotId, CString sCode, CString sText);

	void Get_PPSelect(CString sLotId, CString sRecipe);
	void Get_PPSelectFail(CString sLotId, CString sRecipe, CString sCode, CString sText);


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
	void Set_ErrorUpdate(int nFlag, CString sErrNo);	// 0:해제, 1:발생
		
	void Set_IdleReport(CString sOperId, CString sSTime, CString sETime, CString sCode, CString sType);	//1:Start, 2:End

	void Set_MGZIDReport(CString sMGZID);	
	void Set_PPSelectedReport(CString sLotId, CString sVersion);

	void Set_LotStart(CString sLotId, CString sMGZId, int nSlot, CString sTrayID, CString sRecipe);
};


extern CMesAgent g_objMesAgent;

