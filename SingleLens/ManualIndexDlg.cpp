// ManualIndexDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SingleLens.h"
#include "ManualIndexDlg.h"
#include "afxdialogex.h"

#include "Common.h"
#include "AJinDefine.h"
#include "AJinAXL.h"
#include "LogFile.h"

#include "SingleLensDlg.h"
#include "ManualDlg.h"


// CManualIndexDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualIndexDlg, CDialogEx)

CManualIndexDlg::CManualIndexDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualIndexDlg::IDD, pParent)
{

}

CManualIndexDlg::~CManualIndexDlg()
{
}

void CManualIndexDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUP_0, m_Group[0]);	
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_STC_AXIS_POS_0 + i, m_stcAxisPos[i]);

	for (int i = 0; i <  4; i++) DDX_Control(pDX, IDC_BTN_INDEX_R_0 + i, m_BtnIndexR[i]);
	for (int i = 0; i <  3; i++) DDX_Control(pDX, IDC_LED_INDEX_POS_0 + i, m_LedIndexPos[i]);

	for (int i = 0; i <  2; i++) DDX_Control(pDX, IDC_BTN_INDEX_IO_0 + i, m_BtnIndexIO[i]);
	for (int i = 0; i <  2; i++) DDX_Control(pDX, IDC_LED_INDEX_IO_0 + i, m_LedIndexIO[i]);
}


BEGIN_MESSAGE_MAP(CManualIndexDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()	
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_INDEX_R_0, IDC_BTN_INDEX_R_3, OnBtnIndexRClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_INDEX_IO_0, IDC_BTN_INDEX_IO_1, OnBtmIndexIOClick)	

END_MESSAGE_MAP()


// CManualIndexDlg 메시지 처리기입니다.


BOOL CManualIndexDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();
		
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CManualIndexDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualIndexDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;
		
	//Display_Status();

	m_strLog.Format("[Manual Repeat] Show Window");
	g_objLogFile.Save_HandlerLog(m_strLog);
}


void CManualIndexDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CManualIndexDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnTimer(nIDEvent);
}


void CManualIndexDlg::Initial_Controls()
{
	m_Group[0].Init_Ctrl("Arial", 11, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);	
}


void CManualIndexDlg::Display_Status()
{
	CString strPos;

	double dAngle = 0.0;
	double dPos = g_objAJinAXL.Get_Position(AX_MAIN_INDEX_R);
	
	dAngle = (dPos/7200.0);
	if(dAngle > 360) dAngle = fmod(dAngle, 360.0);
	strPos.Format("%0.3lf", dAngle);
	m_stcAxisPos[0].SetWindowText(strPos);
	
	//int nPos = g_objCommon.Get_MainIndexPos(0);
	strPos.Format("%d", gData.nIndexPos);
	m_stcAxisPos[1].SetWindowText(strPos);
	
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();
	for (int i = 0; i < 3; i++) m_LedIndexPos[i].Set_On((pDX02->nValue >> i) & 1);					// Index Position
}



void CManualIndexDlg::OnBtnIndexRClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_INDEX_R_0;

	if(nIndex == eIndex_R::Ready)
	{
		g_objCommon.Move_Position(AX_MAIN_INDEX_R, eIndex_R::Ready);
	}
	if(nIndex == eIndex_R::MoveP)
	{
		g_objAJinAXL.Move_Relative(AX_MAIN_INDEX_R, 60 ); //60 degree 
	}
	if(nIndex == eIndex_R::MoveM)
	{		
		g_objAJinAXL.Move_Relative(AX_MAIN_INDEX_R, -60 ); //60 degree 
	}	
	m_strLog.Format("[Manual Index R X] R (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtmIndexIOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
		
	int nIndex = nID - IDC_BTN_INDEX_IO_0;

	DY_DATA_02 *pDY02 = g_objAJinAXL.Get_pDY02();

	if(nIndex == eIndexIO::AlignIn)
	{
		pDY02->oMainIndexZigAlignIn = TRUE; pDY02->oMainIndexZigAlignOut = FALSE;
	}
	if(nIndex == eIndexIO::AlignOut)
	{
		pDY02->oMainIndexZigAlignIn = FALSE; pDY02->oMainIndexZigAlignOut = TRUE;
	}
	
	m_strLog.Format("[Manual Index IO ] I/O (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}