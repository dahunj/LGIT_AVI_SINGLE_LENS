// GridWindow.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SingleLens.h"
#include "GridWindow.h"


IMPLEMENT_DYNAMIC(CGridWindow, CWnd)

	CGridWindow::CGridWindow()
{
	m_nRows = 12;
	m_nColumns = 12;
	m_nCellGap = 1;
	m_nSelectedCell = -1;

	m_clrGridLine = RGB(100, 100, 100);
	m_clrWindowBackground = RGB(220, 220, 220);
	m_clrSelectedBorder = RGB(255, 0, 0);
}

CGridWindow::~CGridWindow()
{
	if (m_font.GetSafeHandle() != NULL)
	{
		m_font.DeleteObject();
	}
}

BEGIN_MESSAGE_MAP(CGridWindow, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
END_MESSAGE_MAP()

BOOL CGridWindow::Create(
	CWnd* pParent,
	const CRect& rect,
	UINT nID,
	int nRows,
	int nColumns)
{
	if (pParent == NULL || nRows <= 0 || nColumns <= 0)
		return FALSE;

	m_nRows = nRows;
	m_nColumns = nColumns;

	m_cells.clear();
	m_cells.resize(m_nRows * m_nColumns);

	CString strClassName = AfxRegisterWndClass(
		CS_HREDRAW | CS_VREDRAW,
		::LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)::GetStockObject(NULL_BRUSH),
		NULL);

	BOOL bResult = CWnd::CreateEx(
		WS_EX_CLIENTEDGE,
		strClassName,
		_T("GridWindow"),
		WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		rect,
		pParent,
		nID);

	if (!bResult)
		return FALSE;

	LOGFONT logFont;
	ZeroMemory(&logFont, sizeof(LOGFONT));

	logFont.lfHeight = 10;
	logFont.lfWeight = FW_NORMAL;
	logFont.lfCharSet = DEFAULT_CHARSET;

	_tcscpy_s(
		logFont.lfFaceName,
		LF_FACESIZE,
		_T("Arial"));

	m_font.CreateFontIndirect(&logFont);

	return TRUE;
}

void CGridWindow::SetGridSize(int nRows, int nColumns)
{
	if (nRows <= 0 || nColumns <= 0)
		return;

	m_nRows = nRows;
	m_nColumns = nColumns;
	m_nSelectedCell = -1;

	m_cells.clear();
	m_cells.resize(m_nRows * m_nColumns);

	Invalidate(FALSE);
}

int CGridWindow::GetCellCount() const
{
	return m_nRows * m_nColumns;
}

int CGridWindow::GetCellIndex(int nRow, int nColumn) const
{
	if (nRow < 0 || nRow >= m_nRows)
		return -1;

	if (nColumn < 0 || nColumn >= m_nColumns)
		return -1;

	return (nRow * m_nColumns) + nColumn;
}

BOOL CGridWindow::IsValidIndex(int nIndex) const
{
	return nIndex >= 0 &&
		nIndex < static_cast<int>(m_cells.size());
}

BOOL CGridWindow::SetCellText(
	int nIndex,
	const CString& strText)
{
	if (!IsValidIndex(nIndex))
		return FALSE;

	m_cells[nIndex].strText = strText;

	if (GetSafeHwnd() != NULL)
		InvalidateRect(GetCellRect(nIndex), FALSE);

	return TRUE;
}

BOOL CGridWindow::SetCellText(
	int nRow,
	int nColumn,
	const CString& strText)
{
	int nIndex = GetCellIndex(nRow, nColumn);
	return SetCellText(nIndex, strText);
}

BOOL CGridWindow::SetCellNumber(
	int nIndex,
	int nNumber)
{
	CString strNumber;
	strNumber.Format(_T("%d"), nNumber);

	return SetCellText(nIndex, strNumber);
}

BOOL CGridWindow::SetCellNumber(
	int nRow,
	int nColumn,
	int nNumber)
{
	int nIndex = GetCellIndex(nRow, nColumn);
	return SetCellNumber(nIndex, nNumber);
}

BOOL CGridWindow::SetCellBackgroundColor(
	int nIndex,
	COLORREF clrBackground)
{
	if (!IsValidIndex(nIndex))
		return FALSE;

	m_cells[nIndex].clrBackground = clrBackground;

	if (GetSafeHwnd() != NULL)
		InvalidateRect(GetCellRect(nIndex), FALSE);

	return TRUE;
}

BOOL CGridWindow::SetCellBackgroundColor(
	int nRow,
	int nColumn,
	COLORREF clrBackground)
{
	int nIndex = GetCellIndex(nRow, nColumn);

	return SetCellBackgroundColor(
		nIndex,
		clrBackground);
}

BOOL CGridWindow::SetCellTextColor(
	int nIndex,
	COLORREF clrText)
{
	if (!IsValidIndex(nIndex))
		return FALSE;

	m_cells[nIndex].clrText = clrText;

	if (GetSafeHwnd() != NULL)
		InvalidateRect(GetCellRect(nIndex), FALSE);

	return TRUE;
}

BOOL CGridWindow::SetCellTextColor(
	int nRow,
	int nColumn,
	COLORREF clrText)
{
	int nIndex = GetCellIndex(nRow, nColumn);

	return SetCellTextColor(
		nIndex,
		clrText);
}

void CGridWindow::ClearAll()
{
	int nCount = static_cast<int>(m_cells.size());

	for (int i = 0; i < nCount; ++i)
	{
		m_cells[i].strText = _T("");
		m_cells[i].clrBackground = RGB(255, 255, 255);
		m_cells[i].clrText = RGB(0, 0, 0);
	}

	m_nSelectedCell = -1;
	Invalidate(FALSE);
}

void CGridWindow::SetAllBackgroundColor(
	COLORREF clrBackground)
{
	int nCount = static_cast<int>(m_cells.size());

	for (int i = 0; i < nCount; ++i)
	{
		m_cells[i].clrBackground = clrBackground;
	}

	Invalidate(FALSE);
}

void CGridWindow::SetCellGap(int nGap)
{
	if (nGap < 0)
		nGap = 0;

	m_nCellGap = nGap;
	Invalidate(FALSE);
}

void CGridWindow::SetGridLineColor(COLORREF clrColor)
{
	m_clrGridLine = clrColor;
	Invalidate(FALSE);
}

CRect CGridWindow::GetCellRect(int nIndex) const
{
	CRect rectEmpty(0, 0, 0, 0);

	if (!IsValidIndex(nIndex))
		return rectEmpty;

	CRect rectClient;
	GetClientRect(&rectClient);

	int nRow = nIndex / m_nColumns;
	int nColumn = nIndex % m_nColumns;

	// 나눗셈 오차를 줄이기 위해 좌표를 비율로 계산
	int nLeft =
		rectClient.left +
		(rectClient.Width() * nColumn / m_nColumns);

	int nRight =
		rectClient.left +
		(rectClient.Width() * (nColumn + 1) / m_nColumns);

	int nTop =
		rectClient.top +
		(rectClient.Height() * nRow / m_nRows);

	int nBottom =
		rectClient.top +
		(rectClient.Height() * (nRow + 1) / m_nRows);

	return CRect(nLeft, nTop, nRight, nBottom);
}

void CGridWindow::OnPaint()
{
	CPaintDC paintDC(this);

	CRect rectClient;
	GetClientRect(&rectClient);

	// 더블 버퍼링
	CDC memoryDC;
	memoryDC.CreateCompatibleDC(&paintDC);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(
		&paintDC,
		rectClient.Width(),
		rectClient.Height());

	CBitmap* pOldBitmap = memoryDC.SelectObject(&bitmap);

	memoryDC.FillSolidRect(
		rectClient,
		m_clrWindowBackground);

	CFont* pOldFont = NULL;

	if (m_font.GetSafeHandle() != NULL)
		pOldFont = memoryDC.SelectObject(&m_font);

	memoryDC.SetBkMode(TRANSPARENT);

	CPen gridPen(
		PS_SOLID,
		1,
		m_clrGridLine);

	CPen selectedPen(
		PS_SOLID,
		2,
		m_clrSelectedBorder);

	int nCellCount = GetCellCount();

	for (int i = 0; i < nCellCount; ++i)
	{
		CRect rectCell = GetCellRect(i);

		// 셀 사이 간격
		CRect rectFill = rectCell;

		if (m_nCellGap > 0)
		{
			rectFill.DeflateRect(
				m_nCellGap,
				m_nCellGap);
		}

		memoryDC.FillSolidRect(
			rectFill,
			m_cells[i].clrBackground);

		CPen* pOldPen = NULL;

		if (i == m_nSelectedCell)
			pOldPen = memoryDC.SelectObject(&selectedPen);
		else
			pOldPen = memoryDC.SelectObject(&gridPen);

		CBrush* pOldBrush =
			(CBrush*)memoryDC.SelectStockObject(NULL_BRUSH);

		memoryDC.Rectangle(rectCell);

		memoryDC.SelectObject(pOldBrush);
		memoryDC.SelectObject(pOldPen);

		memoryDC.SetTextColor(m_cells[i].clrText);

		memoryDC.DrawText(
			m_cells[i].strText,
			rectFill,
			DT_CENTER |
			DT_VCENTER |
			DT_SINGLELINE |
			DT_NOPREFIX);
	}

	if (pOldFont != NULL)
		memoryDC.SelectObject(pOldFont);

	paintDC.BitBlt(
		0,
		0,
		rectClient.Width(),
		rectClient.Height(),
		&memoryDC,
		0,
		0,
		SRCCOPY);

	memoryDC.SelectObject(pOldBitmap);
}

BOOL CGridWindow::OnEraseBkgnd(CDC* pDC)
{
	// OnPaint에서 전체 배경을 그리므로 깜빡임 방지
	return TRUE;
}

int CGridWindow::HitTestCell(CPoint point) const
{
	CRect rectClient;
	GetClientRect(&rectClient);

	if (!rectClient.PtInRect(point))
		return -1;

	if (rectClient.Width() <= 0 ||
		rectClient.Height() <= 0)
	{
		return -1;
	}

	int nColumn =
		point.x * m_nColumns /
		rectClient.Width();

	int nRow =
		point.y * m_nRows /
		rectClient.Height();

	return GetCellIndex(nRow, nColumn);
}

void CGridWindow::OnLButtonDown(
	UINT nFlags,
	CPoint point)
{
	int nCell = HitTestCell(point);

	if (nCell >= 0)
	{
		int nOldCell = m_nSelectedCell;
		m_nSelectedCell = nCell;

		if (IsValidIndex(nOldCell))
			InvalidateRect(GetCellRect(nOldCell), FALSE);

		InvalidateRect(GetCellRect(m_nSelectedCell), FALSE);
	}

	CWnd::OnLButtonDown(nFlags, point);
}

int CGridWindow::GetSelectedCell() const
{
	return m_nSelectedCell;
}

void CGridWindow::OnSize(
	UINT nType,
	int cx,
	int cy)
{
	CWnd::OnSize(nType, cx, cy);
	Invalidate(FALSE);
}