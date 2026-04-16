#pragma once
#include <afxwin.h>

// CBmpControl

class CBmpControl : public CStatic
{
	DECLARE_DYNAMIC(CBmpControl)

public:
	CBmpControl();
	virtual ~CBmpControl();

public:
	CBitmap m_bmp;

	BOOL  LoadBmp(UINT nID);
	void ClearBmp();

protected:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()
};


