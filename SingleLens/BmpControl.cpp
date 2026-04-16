// BmpControl.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SingleLens.h"
#include "BmpControl.h"


// CBmpControl

IMPLEMENT_DYNAMIC(CBmpControl, CStatic)

CBmpControl::CBmpControl()
{

}

CBmpControl::~CBmpControl()
{
	ClearBmp();
}


BEGIN_MESSAGE_MAP(CBmpControl, CStatic)
	    ON_WM_PAINT()
		ON_WM_ERASEBKGND()
END_MESSAGE_MAP()




BOOL  CBmpControl::LoadBmp(UINT nID)
{
	 ClearBmp();

	 if (!m_bmp.LoadBitmap(nID))
		 return FALSE;

	 Invalidate();
	 UpdateWindow();
	 return TRUE;
}

void CBmpControl::ClearBmp()
{
	if (m_bmp.GetSafeHandle() != NULL)
		m_bmp.DeleteObject();
}

BOOL CBmpControl::OnEraseBkgnd(CDC* pDC)
{
	// 깜빡임 줄이려고 배경 지우기 막음
	return TRUE;
}


void CBmpControl::OnPaint()
{
	CPaintDC dc(this);

	CRect rcClient;
	GetClientRect(&rcClient);

	// 비트맵 없으면 그냥 배경색으로 채움
	if (m_bmp.GetSafeHandle() == NULL)
	{
		dc.FillSolidRect(&rcClient, RGB(255, 255, 255));
		return;
	}

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	CBitmap* pOldBmp = memDC.SelectObject(&m_bmp);

	BITMAP bm;
	::ZeroMemory(&bm, sizeof(BITMAP));
	m_bmp.GetBitmap(&bm);

	dc.SetStretchBltMode(HALFTONE);

	dc.StretchBlt(
		0, 0, rcClient.Width(), rcClient.Height(),
		&memDC,
		0, 0, bm.bmWidth, bm.bmHeight,
		SRCCOPY);

	memDC.SelectObject(pOldBmp);
}


// CBmpControl 메시지 처리기입니다.


