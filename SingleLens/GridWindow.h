#pragma once

#include <vector>

class CGridWindow : public CWnd
{
	DECLARE_DYNAMIC(CGridWindow)

public:
	struct GRID_CELL
	{
		CString strText;
		COLORREF clrBackground;
		COLORREF clrText;

		GRID_CELL()
		{
			strText = _T("");
			clrBackground = RGB(255, 255, 255);
			clrText = RGB(0, 0, 0);
		}
	};

public:
	CGridWindow();
	virtual ~CGridWindow();

	// 윈도우 생성
	BOOL Create(
		CWnd* pParent,
		const CRect& rect,
		UINT nID,
		int nRows = 12,
		int nColumns = 12);

	// 행과 열 개수 변경
	void SetGridSize(int nRows, int nColumns);

	// 전체 셀 개수
	int GetCellCount() const;

	// 셀 텍스트 설정
	BOOL SetCellText(int nIndex, const CString& strText);
	BOOL SetCellText(int nRow, int nColumn, const CString& strText);

	// 셀에 숫자 설정
	BOOL SetCellNumber(int nIndex, int nNumber);
	BOOL SetCellNumber(int nRow, int nColumn, int nNumber);

	// 셀 배경색 설정
	BOOL SetCellBackgroundColor(int nIndex, COLORREF clrBackground);
	BOOL SetCellBackgroundColor(
		int nRow,
		int nColumn,
		COLORREF clrBackground);

	// 셀 글자색 설정
	BOOL SetCellTextColor(int nIndex, COLORREF clrText);
	BOOL SetCellTextColor(
		int nRow,
		int nColumn,
		COLORREF clrText);

	// 전체 셀 초기화
	void ClearAll();

	// 전체 배경색 설정
	void SetAllBackgroundColor(COLORREF clrBackground);

	// 셀 간격 및 테두리 설정
	void SetCellGap(int nGap);
	void SetGridLineColor(COLORREF clrColor);

	// 마우스 좌표로 셀 번호 얻기
	int HitTestCell(CPoint point) const;

	int GetSelectedCell() const;

protected:
	int GetCellIndex(int nRow, int nColumn) const;
	BOOL IsValidIndex(int nIndex) const;
	CRect GetCellRect(int nIndex) const;

protected:
	int m_nRows;
	int m_nColumns;
	int m_nCellGap;

	int m_nSelectedCell;

	COLORREF m_clrGridLine;
	COLORREF m_clrWindowBackground;
	COLORREF m_clrSelectedBorder;

	CFont m_font;

	std::vector<GRID_CELL> m_cells;

protected:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};