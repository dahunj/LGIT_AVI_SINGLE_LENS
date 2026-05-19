#pragma once


// CInspectV1

class CInspectV1 : public CWnd
{
	DECLARE_DYNAMIC(CInspectV1)

public:
	CInspectV1();
	virtual ~CInspectV1();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnClientConnect(WPARAM wConnect, LPARAM lParam);
	afx_msg LRESULT OnClientReceive(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClientClose(WPARAM wParam, LPARAM lParam);

private:
	CClientSocketCS m_Client;

	BOOL	m_bConnected;
	BOOL	m_bEquipmentOnline;

	CString m_strRecvCmd;

	int		m_nRecvCmdCount;	// 4Byte
	int		m_nSendCmdCount;


public:
	void Initialize();
	void Terminate();

	BOOL Is_Connected() { return m_bConnected; }
	BOOL Is_HostOnline() { return m_bEquipmentOnline; }



public:
	void Send_Message(CString sMessage);

	/*void Get_S6F11_CarrierIDReport();
	void Get_S6F11_CarrierOutReport();

	void Get_S7F26();
	void Get_S6F11_LotIDReport();*/

public:
	/*void Set_S6F12_LotIDReport();
	void Set_S2F49_LotStart(int nLotNo);*/


};

/*extern CInspectV1 g_objVision1;*/

