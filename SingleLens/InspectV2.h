// InspectV2.h : 헤더 파일
//
#pragma once

// CInspectV2

class CInspectV2 : public CWnd
{
	DECLARE_DYNAMIC(CInspectV2)

public:
	CInspectV2();
	virtual ~CInspectV2();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnServerAccept(WPARAM wLocalPort, LPARAM lClientIdx);
	afx_msg LRESULT OnServerReceive(WPARAM wLocalPort, LPARAM lClientIdx);
	afx_msg LRESULT OnServerRemove(WPARAM wLocalPort, LPARAM lClientIdx);

private:
	CServerSocketCS	m_Socket;

	CString	m_strRecvCmd;
	BOOL	m_bConnected;

public:
	void Init_Socket();
	void Exit_Socket();

	void Send_Message(CString sMessage);
	BOOL Is_Connected() { return m_bConnected; }
};

///////////////////////////////////////////////////////////////////////////////
