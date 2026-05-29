// SetupEquipDlg.cpp : ±∏«ˆ ∆ƒ¿œ¿‘¥œ¥Ÿ.
//
#include "stdafx.h"
#include "SingleLens.h"
#include "SingleLensDlg.h"
#include "SetupEquipDlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "DataManager.h"
#include "Common.h"
#include "SetupDlg.h"



// CSetupEquipDlg ¥Î»≠ ªÛ¿⁄¿‘¥œ¥Ÿ.

IMPLEMENT_DYNAMIC(CSetupEquipDlg, CDialogEx)

CSetupEquipDlg::CSetupEquipDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupEquipDlg::IDD, pParent)
{
}

CSetupEquipDlg::~CSetupEquipDlg()
{
}

void CSetupEquipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	/*for (int i = 0; i < 12; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 7; i++) DDX_Control(pDX, IDC_LABEL_0 + i,  m_Label[i]);
*/
	DDX_Control(pDX, IDC_STC_EQUIP_NAME, m_stcEquipName);
	DDX_Control(pDX, IDC_STC_EQUIP_MODEL, m_stcEquipModel);
	DDX_Control(pDX, IDC_CBO_MODEL_CHANGE, m_cboModelChange);

	DDX_Control(pDX, IDC_CBO_LOT_BARCODE_PORT, m_cboLotBarcodePort);
	
	DDX_Control(pDX, IDC_STC_MOTION_CHECK, m_stcMotionCheck);
	DDX_Control(pDX, IDC_LBL_DOOR_LOCK, m_lblDoorLock);	
	DDX_Control(pDX, IDC_LBL_DOOR_LOCK2, m_lblDoorLock2);
	DDX_Control(pDX, IDC_STC_DOORLOCK_TIME, m_stcDoorLockTime);

	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_RDO_DOOR_LOCK_0 + i, m_rdoDoorLock[i]);		
		
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_LBL_DELAY_ADD_0 + i,  m_lblDelayAdd[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_STC_DELAY_ADD_0 + i, m_stcDelayAdd[i]);

	DDX_Control(pDX, IDC_LBL_AVI_IP, m_lblAviIp);
	DDX_Control(pDX, IDC_IPA_AVI_IP, m_ipaAviIp);
	DDX_Control(pDX, IDC_GRP_TOWER, m_grpTower);
	for (int i = 0; i < 10; i++) DDX_Control(pDX, IDC_LBL_TOWER_0 + i,  m_lblTower[i]);
	for (int i = 0; i < 6; i++) for (int j = 0; j < 4; j++) DDX_Control(pDX, IDC_CHK_TOWER_0_0 + i * 4 + j,  m_chkTower[i][j]);
	DDX_Control(pDX, IDC_GRP_BUZZER, m_grpBuzzer);
	for (int i = 0; i < 11; i++) DDX_Control(pDX, IDC_LBL_BUZZER_0 + i,  m_lblBuzzer[i]);
	for (int i = 0; i < 5; i++) for (int j = 0; j < 6; j++) DDX_Control(pDX, IDC_CHK_BUZZER_0_0 + i * 6 + j,  m_chkBuzzer[i][j]);

	DDX_Control(pDX, IDC_GRP_HIDDEN, m_grpHidden);
	DDX_Control(pDX, IDC_LBL_PASSWORD_MT, m_lblPasswordOp);
	DDX_Control(pDX, IDC_STC_PASSWORD_MT, m_stcPasswordOp);
	DDX_Control(pDX, IDC_LBL_PASSWORD_ENGR, m_lblPasswordEngr);
	DDX_Control(pDX, IDC_EDT_PASSWORD_ENGR, m_edtPasswordEngr);
		
	DDX_Control(pDX, IDC_GRP_RESULT_TEST, m_grpResultTest);
	DDX_Control(pDX, IDC_LBL_RESULT_TEST, m_lblResultTest);
	DDX_Control(pDX, IDC_CHK_RESULT_TEST_USE, m_chkResultTestUse);
	DDX_Control(pDX, IDC_EDT_RESULT_TEST, m_edtResultTest);

	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_ZIG_DATA_0 + i, m_stcZigData[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_STC_TRIGGER_TOP_0 + i, m_stcTriggerTop[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_STC_TRIGGER_BTM_0 + i, m_stcTriggerBtm[i]);

	DDX_Control(pDX, IDC_STC_ELV_DATA_0, m_stcElvData[0]);
	
	DDX_Control(pDX, IDC_CHK_TOP_VISION, m_chkTopVision);
	DDX_Control(pDX, IDC_CHK_BTM_VISION, m_chkBtmVision);
	DDX_Control(pDX, IDC_CHK_MARK_USE, m_chkMarkUse);
}

BEGIN_MESSAGE_MAP(CSetupEquipDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_STN_CLICKED(IDC_STC_EQUIP_NAME, &CSetupEquipDlg::OnStnClickedStcEquipName)
	ON_STN_CLICKED(IDC_STC_MOTION_CHECK, &CSetupEquipDlg::OnStnClickedStcMotionCheck)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_DELAY_ADD_0, IDC_STC_DELAY_ADD_5, OnStcDelayAddClick)
	ON_STN_CLICKED(IDC_STC_SHOW_HIDDEN, &CSetupEquipDlg::OnStnClickedStcShowHidden)
	ON_STN_CLICKED(IDC_STC_PASSWORD_MT, &CSetupEquipDlg::OnStnClickedStcPasswordMt)	
	ON_STN_CLICKED(IDC_STC_DOORLOCK_TIME, &CSetupEquipDlg::OnStnClickedStcDoorlockTime)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_ZIG_DATA_0, IDC_STC_ZIG_DATA_3, OnStcZigDataClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_TRIGGER_TOP_0, IDC_STC_TRIGGER_TOP_7, OnStcTriggerTopClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_TRIGGER_BTM_0, IDC_STC_TRIGGER_BTM_7, OnStcTriggerBtmClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_ELV_DATA_0, IDC_STC_ELV_DATA_0, OnStcElvDataClick)
	ON_BN_CLICKED(IDC_BTN_MODEL_ADD, &CSetupEquipDlg::OnBnClickedBtnModelAdd)
	ON_STN_CLICKED(IDC_STC_EQUIP_MODEL, &CSetupEquipDlg::OnStnClickedStcEquipModel)
	ON_CBN_SELCHANGE(IDC_CBO_MODEL_CHANGE, &CSetupEquipDlg::OnCbnSelchangeCboModelChange)
	ON_CBN_DROPDOWN(IDC_CBO_MODEL_CHANGE, &CSetupEquipDlg::OnCbnDropdownCboModelChange)
END_MESSAGE_MAP()

// CSetupEquipDlg ∏ﬁΩ√¡ˆ √≥∏Æ±‚¿‘¥œ¥Ÿ.

void CSetupEquipDlg::Initial_Controls() 
{
	CString strText;
	//for (int i = 0; i < 12; i++) m_Group[i].Init_Ctrl("πŸ≈¡", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	//m_Label[0].Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x10, 0xC0));	// Equip Name
	//m_Label[1].Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xA0, 0x00));	// Model
	//for (int i = 2; i < 5; i++) m_Label[i].Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x10, 0xC0));	// Port
	//m_Label[5].Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x10, 0xC0));	// Motin Check
	//m_Label[6].Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x20, 0x20)); // Vendor Selection 

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	m_stcEquipName.Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0x00, 0x00, 0x80), RGB(0xE0, 0xFF, 0xE0));
	m_stcEquipModel.Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0x00, 0x00, 0x80), RGB(0xE0, 0xFF, 0xE0));
	m_cboModelChange.Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xE0, 0x00));
	
	for (int i = 0; i < 4; i++) { strText.Format("COM%d", i + 1); m_cboLotBarcodePort.AddString(strText); }
	m_cboLotBarcodePort.Init_Ctrl("πŸ≈¡", 12, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xF0, 0xE0, 0x00));
	
	m_stcMotionCheck.Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0x00, 0x00, 0x80), RGB(0xF0, 0xE0, 0x00));
	m_lblDoorLock.Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	for (int i = 0; i < 2; i++) m_rdoDoorLock[i].Init_Ctrl("πŸ≈¡", 11, FALSE, COLOR_DEFAULT, RGB(0xC0, 0xC0, 0xC0), CRadioCS::emRed, 0);
	m_lblDoorLock2.Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	m_stcDoorLockTime.Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0x00, 0x00, 0x80), RGB(0xF0, 0xE0, 0x00));
	
	for (int i = 0; i < 6; i++) m_lblDelayAdd[i].Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x60, 0x40));
	for (int i = 0; i < 6; i++) m_stcDelayAdd[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xE0));

	m_lblAviIp.Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	
	m_grpTower.Init_Ctrl("πŸ≈¡", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	for (int i = 0; i < 10; i++) m_lblTower[i].Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 6; i++) for (int j = 0; j < 4; j++) m_chkTower[i][j].Init_Ctrl("πŸ≈¡", 11, FALSE, COLOR_DEFAULT, RGB(0x00, 0xF0, 0x00), CCheckCS::emRed, 0);
	m_grpBuzzer.Init_Ctrl("πŸ≈¡", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	for (int i = 0; i < 11; i++) m_lblBuzzer[i].Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 5; i++) for (int j = 0; j < 6; j++) m_chkBuzzer[i][j].Init_Ctrl("πŸ≈¡", 11, FALSE, COLOR_DEFAULT, RGB(0x00, 0xE0, 0xF0), CCheckCS::emRed, 0);

	m_grpHidden.Init_Ctrl("πŸ≈¡", 10, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	m_lblPasswordOp.Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	m_stcPasswordOp.Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0xC0, 0xC0, 0xC0));
	m_lblPasswordEngr.Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	m_edtPasswordEngr.Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
		
	m_grpResultTest.Init_Ctrl("πŸ≈¡", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	m_lblResultTest.Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	m_chkResultTestUse.Init_Ctrl("πŸ≈¡", 10, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60), CCheckCS::emRed, 0);
	m_edtResultTest.Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);

	for (int i = 0; i < 2; i++) m_stcZigData[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xD0, 0xD0, 0xD0));
	for (int i = 2; i < 4; i++) m_stcZigData[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xE0));

	for (int i = 0; i < 8; i++) m_stcTriggerTop[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xE0));
	for (int i = 0; i < 8; i++) m_stcTriggerBtm[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xE0));


	m_chkTopVision.Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60), CCheckCS::emRed, 0);
	m_chkBtmVision.Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60), CCheckCS::emRed, 0);
	m_chkMarkUse.Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60), CCheckCS::emRed, 0);
}


void CSetupEquipDlg::InitModelComboBox()
{

	CString sPathSource;
	sPathSource = gsCurrentDir + "\\System\\Model";

	for(int i=m_cboModelChange.GetCount()-1; i>=0; i--)
	{
		m_cboModelChange.DeleteString(i);
	}

	if (GetFileAttributes(sPathSource) == -1) return;	// µ∑∫≈‰∏Æ æ¯¿Ω

	int nIndex = 0 ;

	CFileFind ff;

	BOOL bFile = ff.FindFile(sPathSource + _T("\\*.*"));

	while(bFile)
	{
		bFile = ff.FindNextFile();

		CString str;	// = ff.GetFileName();

		if(ff.IsDots()) continue;

		if(ff.IsDirectory()){
			str = ff.GetFileName();
			m_cboModelChange.AddString(str);
		}

		//str = str.Left(str.ReverseFind(_T('.')));

		//m_cboModelChange.AddString(str);

	}
	ff.Close();
}

BOOL CSetupEquipDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  ø©±‚ø° √ﬂ∞° √ ±‚»≠ ¿€æ˜¿ª √ﬂ∞°«’¥œ¥Ÿ.
	SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// øπø‹: OCX º”º∫ ∆‰¿Ã¡ˆ¥¬ FALSE∏¶ π›»Ø«ÿæﬂ «’¥œ¥Ÿ.
}

BOOL CSetupEquipDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSetupEquipDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

	Display_EquipData();

	m_grpHidden.ShowWindow(SW_HIDE);
	m_lblPasswordOp.ShowWindow(SW_HIDE);
	m_stcPasswordOp.ShowWindow(SW_HIDE);
	m_lblPasswordEngr.ShowWindow(SW_HIDE);
	m_edtPasswordEngr.ShowWindow(SW_HIDE);

	m_grpResultTest.ShowWindow(SW_HIDE);
	m_lblResultTest.ShowWindow(SW_HIDE);
	m_chkResultTestUse.ShowWindow(SW_HIDE);
	m_edtResultTest.ShowWindow(SW_HIDE);
}

void CSetupEquipDlg::OnStnClickedStcEquipName()
{
	CString strKey;
	if (g_objCommon.Show_KeyPad(strKey) != IDOK) return;

	m_stcEquipName.SetWindowText(strKey);
}

void CSetupEquipDlg::OnStnClickedStcMotionCheck()
{
	CString strOld, strNew;
	m_stcMotionCheck.GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcMotionCheck.SetWindowText(strNew);
}


void CSetupEquipDlg::OnStcDelayAddClick(UINT nID)
{
	int ID = nID - IDC_STC_DELAY_ADD_0;

	CString strOld, strNew;
	m_stcDelayAdd[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcDelayAdd[ID].SetWindowText(strNew);
}



void CSetupEquipDlg::OnStnClickedStcPasswordMt()
{
	CString strTemp, strData;

	if (g_objCommon.Show_NumPad("", strData) != IDOK) return;

	int nLen = strData.GetLength();
	if (nLen < 1) return;

	for (int i = 0; i < nLen; i++ ) {
		strTemp = strData.Mid(i, 1);
		if (strTemp < "0" || strTemp > "9") { AfxMessageBox("Password Input Error......"); return; }
	}
	m_stcPasswordOp.SetWindowText(strData);
}

void CSetupEquipDlg::OnStnClickedStcShowHidden()
{
	if (m_grpHidden.IsWindowVisible()) 
	{
		m_grpResultTest.ShowWindow(SW_HIDE);
		m_lblResultTest.ShowWindow(SW_HIDE);
		m_chkResultTestUse.ShowWindow(SW_HIDE);
		m_edtResultTest.ShowWindow(SW_HIDE);

		m_grpHidden.ShowWindow(SW_HIDE);
		m_lblPasswordOp.ShowWindow(SW_HIDE);
		m_stcPasswordOp.ShowWindow(SW_HIDE);
		if (g_dlgSetup.Get_LoginUser() != 2) return;
		m_lblPasswordEngr.ShowWindow(SW_HIDE);
		m_edtPasswordEngr.ShowWindow(SW_HIDE);
	} 
	else 
	{
		m_grpResultTest.ShowWindow(SW_SHOW);
		m_lblResultTest.ShowWindow(SW_SHOW);
		m_chkResultTestUse.ShowWindow(SW_SHOW);
		m_edtResultTest.ShowWindow(SW_SHOW);


		m_grpHidden.ShowWindow(SW_SHOW);
		m_lblPasswordOp.ShowWindow(SW_SHOW);
		m_stcPasswordOp.ShowWindow(SW_SHOW);
		if (g_dlgSetup.Get_LoginUser() != 2) return;
		m_lblPasswordEngr.ShowWindow(SW_SHOW);
		m_edtPasswordEngr.ShowWindow(SW_SHOW);
	}
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupEquipDlg::Display_EquipData()
{
	CString strData;
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	m_stcEquipName.SetWindowText(pEquipData->sEquipName);
	m_stcEquipModel.SetWindowText(pEquipData->sModelName);
	
	m_rdoDoorLock[(int)pEquipData->bUseDoorLock].SetCheck(TRUE);
	strData.Format("%d", gData.nDoorLockTime);	m_stcDoorLockTime.SetWindowText(strData);

	strData.Format("%0.3lf", gAlm.dMotionChkPos);	 m_stcMotionCheck.SetWindowText(strData);
	
	strData.Format("%d", pEquipData->nZigArrayX); m_stcZigData[0].SetWindowText(strData);
	strData.Format("%d", pEquipData->nZigArrayY); m_stcZigData[1].SetWindowText(strData);
	strData.Format("%0.2lf", pEquipData->dZigPitchX); m_stcZigData[2].SetWindowText(strData);
	strData.Format("%0.2lf", pEquipData->dZigPitchY); m_stcZigData[3].SetWindowText(strData);
	
	strData.Format("%0.2lf",	pEquipData->dTopStartZ); m_stcTriggerTop[0].SetWindowText(strData);
	strData.Format("%02d",		pEquipData->nTopCount); m_stcTriggerTop[1].SetWindowText(strData);
	strData.Format("%0.2lf",	pEquipData->dTopPeriod); m_stcTriggerTop[2].SetWindowText(strData);
	strData.Format("%0.2lf",	pEquipData->dTopVelocity); m_stcTriggerTop[3].SetWindowText(strData);
	strData.Format("%0.2lf",	pEquipData->dTopStartX); m_stcTriggerTop[4].SetWindowText(strData);
	strData.Format("%0.2lf",	pEquipData->dTopStartY); m_stcTriggerTop[5].SetWindowText(strData);
	strData.Format("%0.2lf",	pEquipData->dTopPitchX); m_stcTriggerTop[6].SetWindowText(strData);
	strData.Format("%0.2lf",	pEquipData->dTopPitchY); m_stcTriggerTop[7].SetWindowText(strData);
	
	strData.Format("%0.2lf",	pEquipData->dBtmStartZ);	m_stcTriggerBtm[0].SetWindowText(strData);
	strData.Format("%02d",		pEquipData->nBtmCount);		m_stcTriggerBtm[1].SetWindowText(strData);
	strData.Format("%0.2lf",	pEquipData->dBtmPeriod);	m_stcTriggerBtm[2].SetWindowText(strData);
	strData.Format("%0.2lf",	pEquipData->dBtmVelocity);	m_stcTriggerBtm[3].SetWindowText(strData);
	strData.Format("%0.2lf",	pEquipData->dBtmStartX);	m_stcTriggerBtm[4].SetWindowText(strData);
	strData.Format("%0.2lf",	pEquipData->dBtmStartY);	m_stcTriggerBtm[5].SetWindowText(strData);
	strData.Format("%0.2lf",	pEquipData->dBtmPitchX);	m_stcTriggerBtm[6].SetWindowText(strData);
	strData.Format("%0.2lf",	pEquipData->dBtmPitchY);	m_stcTriggerBtm[7].SetWindowText(strData);
	
	strData.Format("%0.2lf", pEquipData->dElevPitchZ); m_stcElvData[0].SetWindowText(strData);
	
	m_chkTopVision.SetCheck(pEquipData->bUseTopVision);
	m_chkBtmVision.SetCheck(pEquipData->bUseBtmVision);
	m_chkMarkUse.SetCheck(pEquipData->bUseMark);
	
	for (int i = 0; i < 6; i++) for (int j = 0; j < 4; j++) m_chkTower[i][j].SetCheck(pEquipData->bTower[i][j]);
	for (int i = 0; i < 5; i++) for (int j = 0; j < 6; j++) m_chkBuzzer[i][j].SetCheck(pEquipData->bBuzzer[i][j]);
		
	for (int i = 0; i < 6; i++) 
	{
		strData.Format("%d", pEquipData->nDelayAdd[i]);
		m_stcDelayAdd[i].SetWindowText(strData);
	}

	m_chkResultTestUse.SetCheck(pEquipData->bResultTestUse);
	strData.Format("%d", pEquipData->nResultTestNg); m_edtResultTest.SetWindowText(strData);


}

void CSetupEquipDlg::Save_EquipData()
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	CString strKey, strData, strModel;
	int nData;
	double dData;

	CIniFileCS INI(gsCurrentDir + "\\System\\EquipData.ini");
	if (!INI.Check_File()) { AfxMessageBox("EquipData.ini File Not Found!!!"); return ; }

	
	m_stcEquipName.GetWindowText(strData); INI.Set_String("EQUIPMENT", "NAME", strData);
	m_stcEquipModel.GetWindowText(strModel); INI.Set_String("EQUIPMENT", "MODEL", strModel);
	CSingleLensDlg *pMainDlg = (CSingleLensDlg*)AfxGetMainWnd();
	pMainDlg->Display_EquipName();

	nData = m_cboLotBarcodePort.GetCurSel(); INI.Set_Integer("EQUIPMENT", "LOT_BARCODE", nData + 1);
	if(m_rdoDoorLock[0].GetCheck())
	{
		pEquipData->bUseDoorLock = FALSE;
		INI.Set_Bool("EQUIPMENT", "DOOR_LOCK", m_rdoDoorLock[0].GetCheck());
	}
	else
	{
		INI.Set_Bool("EQUIPMENT", "DOOR_LOCK", m_rdoDoorLock[1].GetCheck());
		pEquipData->bUseDoorLock = TRUE;
	}
	m_stcMotionCheck.GetWindowText(strData); dData = atof(strData); INI.Set_Double("EQUIPMENT", "MOTION_CHECK", dData, "%0.3lf");
	
	m_stcDoorLockTime.GetWindowText(strData);gData.nDoorLockTime = atoi(strData);
	INI.Set_Integer("EQUIPMENT", "DOOR_LOCK_TIME", gData.nDoorLockTime);
	
	m_stcZigData[0].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer ("COAT_ZIG", "ARRAY_X", nData);pEquipData->nZigArrayX = nData; gData.nLensCntX = pEquipData->nZigArrayX;
	m_stcZigData[1].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer ("COAT_ZIG", "ARRAY_Y", nData);pEquipData->nZigArrayY = nData; gData.nLensCntY = pEquipData->nZigArrayY;
	
	m_stcZigData[2].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("COAT_ZIG", "PITCH_X", dData, "%0.2lf");pEquipData->dZigPitchX = dData;
	m_stcZigData[3].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("COAT_ZIG", "PITCH_Y", dData, "%0.2lf");pEquipData->dZigPitchY = dData;
	
	m_stcTriggerTop[0].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRIGGER", "TOP_START_Z",		dData, "%0.2lf");pEquipData->dTopStartZ = dData;
	m_stcTriggerTop[1].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("TRIGGER", "TOP_COUNT",		nData);			 pEquipData->nTopCount = nData;
	m_stcTriggerTop[2].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRIGGER", "TOP_PERIOD",		dData, "%0.2lf");pEquipData->dTopPeriod = dData;
	m_stcTriggerTop[3].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRIGGER", "TOP_VEL",			dData, "%0.2lf");pEquipData->dTopVelocity = dData;
	m_stcTriggerTop[4].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRIGGER", "TOP_START_X",		dData, "%0.2lf");pEquipData->dTopStartX = dData;
	m_stcTriggerTop[5].GetWindowText(strData); dData = atoi(strData); INI.Set_Double ("TRIGGER", "TOP_START_Y",		dData, "%0.2lf");pEquipData->dTopStartY = dData;
	m_stcTriggerTop[6].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRIGGER", "TOP_PITCH_X",		dData, "%0.2lf");pEquipData->dTopPitchX = dData;
	m_stcTriggerTop[7].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRIGGER", "TOP_PITCH_Y",		dData, "%0.2lf");pEquipData->dTopPitchY = dData;
	
	m_stcTriggerBtm[0].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRIGGER", "BTM_START_Z",  dData, "%0.2lf");pEquipData->dBtmStartZ = dData;
	m_stcTriggerBtm[1].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("TRIGGER", "BTM_COUNT",	 nData);		  pEquipData->nBtmCount = nData;
	m_stcTriggerBtm[2].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRIGGER", "BTM_PERIOD",   dData, "%0.2lf");pEquipData->dBtmPeriod = dData;
	m_stcTriggerBtm[3].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRIGGER", "BTM_VEL",		 dData, "%0.2lf");pEquipData->dBtmVelocity = dData;
	m_stcTriggerBtm[4].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRIGGER", "BTM_START_X",  dData, "%0.2lf");pEquipData->dBtmStartX = dData;
	m_stcTriggerBtm[5].GetWindowText(strData); dData = atoi(strData); INI.Set_Double ("TRIGGER", "BTM_START_Y",	 dData, "%0.2lf");pEquipData->dBtmStartY = dData;
	m_stcTriggerBtm[6].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRIGGER", "BTM_PITCH_X",  dData, "%0.2lf");pEquipData->dBtmPitchX = dData;
	m_stcTriggerBtm[7].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRIGGER", "BTM_PITCH_Y",	 dData, "%0.2lf");pEquipData->dBtmPitchY = dData;


	m_stcElvData[0].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("ELEVATOR", "PITCH_Z", dData, "%0.2lf"); pEquipData->dElevPitchZ = dData;
	
	pEquipData->bUseTopVision = m_chkTopVision.GetCheck();INI.Set_Bool("OPTION", "TOP_VISION", pEquipData->bUseTopVision);	 
	pEquipData->bUseBtmVision = m_chkBtmVision.GetCheck();INI.Set_Bool("OPTION", "BTM_VISION", pEquipData->bUseBtmVision);
	pEquipData->bUseMark = m_chkMarkUse.GetCheck(); INI.Set_Bool("OPTION", "MARK_USE", pEquipData->bUseMark);


	m_stcDelayAdd[0].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_ADD", "FEEDER_CLOSE", nData);
	m_stcDelayAdd[1].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_ADD", "FEEDER_OPEN", nData);
	m_stcDelayAdd[2].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_ADD", "TRAY_PICKER_CLOSE", nData);
	m_stcDelayAdd[3].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_ADD", "TRAY_PICKER_OPEN", nData);
	m_stcDelayAdd[4].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_ADD", "INDEX_ALIGN_IN", nData);
	m_stcDelayAdd[5].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_ADD", "INDEX_ALIGN_OUT", nData);
	
	for (int i = 0; i < 6; i++) for (int j = 0; j < 4; j++) { strKey.Format("%d%d", i, j); INI.Set_Bool("TOWER", strKey, m_chkTower[i][j].GetCheck()); }
	for (int i = 0; i < 5; i++) for (int j = 0; j < 6; j++) { strKey.Format("%d%d", i, j); INI.Set_Bool("BUZZER", strKey, m_chkBuzzer[i][j].GetCheck()); }
	
	m_stcPasswordOp.GetWindowText(strData); INI.Set_String("HIDDEN", "PASSWORD_OP", strData); pEquipData->sPasswordOp = strData;
	m_edtPasswordEngr.GetWindowText(strData); INI.Set_String("HIDDEN", "PASSWORD_ENGR", strData); pEquipData->sPasswordEngr = strData;
		
	pEquipData->bResultTestUse = m_chkResultTestUse.GetCheck();
	m_edtResultTest.GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("RESULT_TEST", "RESULT_NG", nData);


	CString sPathSource;
	sPathSource = gsCurrentDir + "\\System\\Model\\";
	sPathSource += strModel;
	sPathSource += _T("\\");
	Save_ModelEquipData(sPathSource);

	Cancel_EquipData();

	g_objCommon.Backup_File(gsCurrentDir + "\\System", "EquipData");

}



void CSetupEquipDlg::Save_ModelEquipData(CString sPath)
{
	CString strKey, strData;
	int nData;
	double dData;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	CIniFileCS INI(sPath + "EquipData.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("EquipData.ini File Not Found!!");
		return;
	}

	m_stcEquipName.GetWindowText(strData); INI.Set_String("EQUIPMENT", "NAME", strData);
	m_stcEquipModel.GetWindowText(strData); INI.Set_String("EQUIPMENT", "MODEL", strData);
	nData = m_cboLotBarcodePort.GetCurSel(); INI.Set_Integer("EQUIPMENT", "LOT_BARCODE", nData + 1);
	INI.Set_Bool("EQUIPMENT", "DOOR_LOCK", m_rdoDoorLock[1].GetCheck());
	
	m_stcZigData[0].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer ("COAT_ZIG", "ARRAY_X", nData);pEquipData->nZigArrayX = nData;
	m_stcZigData[1].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer ("COAT_ZIG", "ARRAY_Y", nData);pEquipData->nZigArrayY = nData;
	m_stcZigData[2].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("COAT_ZIG", "PITCH_X", dData, "%0.2lf");pEquipData->dZigPitchX = dData;
	m_stcZigData[3].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("COAT_ZIG", "PITCH_Y", dData, "%0.2lf");pEquipData->dZigPitchY = dData;

	m_stcTriggerTop[0].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRIGGER", "TOP_START_Z",		dData, "%0.2lf");pEquipData->dTopStartZ = dData;
	m_stcTriggerTop[1].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("TRIGGER", "TOP_COUNT",		nData);			 pEquipData->nTopCount = nData;
	m_stcTriggerTop[2].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRIGGER", "TOP_PERIOD",		dData, "%0.2lf");pEquipData->dTopPeriod = dData;
	m_stcTriggerTop[3].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRIGGER", "TOP_VEL",			dData, "%0.2lf");pEquipData->dTopVelocity = dData;
	m_stcTriggerTop[4].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRIGGER", "TOP_START_X",		dData, "%0.2lf");pEquipData->dTopStartX = dData;
	m_stcTriggerTop[5].GetWindowText(strData); dData = atoi(strData); INI.Set_Double ("TRIGGER", "TOP_START_Y",		dData, "%0.2lf");pEquipData->dTopStartY = dData;
	m_stcTriggerTop[6].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRIGGER", "TOP_PITCH_X",		dData, "%0.2lf");pEquipData->dTopPitchX = dData;
	m_stcTriggerTop[7].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRIGGER", "TOP_PITCH_Y",		dData, "%0.2lf");pEquipData->dTopPitchY = dData;

	m_stcTriggerBtm[0].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRIGGER", "BTM_START_Z",  dData, "%0.2lf");pEquipData->dBtmStartZ = dData;
	m_stcTriggerBtm[1].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("TRIGGER", "BTM_COUNT",	 nData);		  pEquipData->nBtmCount = nData;
	m_stcTriggerBtm[2].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRIGGER", "BTM_PERIOD",   dData, "%0.2lf");pEquipData->dBtmPeriod = dData;
	m_stcTriggerBtm[3].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRIGGER", "BTM_VEL",		 dData, "%0.2lf");pEquipData->dBtmVelocity = dData;
	m_stcTriggerBtm[4].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRIGGER", "BTM_START_X",  dData, "%0.2lf");pEquipData->dBtmStartX = dData;
	m_stcTriggerBtm[5].GetWindowText(strData); dData = atoi(strData); INI.Set_Double ("TRIGGER", "BTM_START_Y",	 dData, "%0.2lf");pEquipData->dBtmStartY = dData;
	m_stcTriggerBtm[6].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRIGGER", "BTM_PITCH_X",  dData, "%0.2lf");pEquipData->dBtmPitchX = dData;
	m_stcTriggerBtm[7].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRIGGER", "BTM_PITCH_Y",	 dData, "%0.2lf");pEquipData->dBtmPitchY = dData;


	m_stcElvData[0].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("ELEVATOR", "PITCH_Z", dData, "%0.2lf"); pEquipData->dElevPitchZ = dData;

	pEquipData->bUseTopVision = m_chkTopVision.GetCheck();INI.Set_Bool("OPTION", "TOP_VISION", pEquipData->bUseTopVision);	 
	pEquipData->bUseBtmVision = m_chkBtmVision.GetCheck();INI.Set_Bool("OPTION", "BTM_VISION", pEquipData->bUseBtmVision);
	pEquipData->bUseMark = m_chkMarkUse.GetCheck(); INI.Set_Bool("OPTION", "MARK_USE", pEquipData->bUseMark);
	
	m_stcDelayAdd[0].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_ADD", "FEEDER_CLOSE", nData);
	m_stcDelayAdd[1].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_ADD", "FEEDER_OPEN", nData);
	m_stcDelayAdd[2].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_ADD", "TRAY_PICKER_CLOSE", nData);
	m_stcDelayAdd[3].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_ADD", "TRAY_PICKER_OPEN", nData);
	m_stcDelayAdd[4].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_ADD", "INDEX_ALIGN_IN", nData);
	m_stcDelayAdd[5].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_ADD", "INDEX_ALIGN_OUT", nData);
		
	for (int i = 0; i < 6; i++) for (int j = 0; j < 4; j++) { strKey.Format("%d%d", i, j); INI.Set_Bool("TOWER", strKey, m_chkTower[i][j].GetCheck()); }
	for (int i = 0; i < 5; i++) for (int j = 0; j < 6; j++) { strKey.Format("%d%d", i, j); INI.Set_Bool("BUZZER", strKey, m_chkBuzzer[i][j].GetCheck()); }
	
	m_stcPasswordOp.GetWindowText(strData); INI.Set_String("HIDDEN", "PASSWORD_OP", strData); pEquipData->sPasswordOp = strData;
	m_edtPasswordEngr.GetWindowText(strData); INI.Set_String("HIDDEN", "PASSWORD_ENGR", strData); pEquipData->sPasswordEngr = strData;

	pEquipData->bResultTestUse = m_chkResultTestUse.GetCheck();
	m_edtResultTest.GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("RESULT_TEST", "RESULT_NG", nData);


	g_objLogFile.Save_HandlerLog("[Setup Equip] Model Save");
}


void CSetupEquipDlg::Cancel_EquipData()
{
	g_objDataManager.Read_EquipData();
	g_objDataManager.Read_MoveData();

	
	Display_EquipData();

	g_objLogFile.Save_HandlerLog("[Setup Equip] Cancel Click");
}

///////////////////////////////////////////////////////////////////////////////


void CSetupEquipDlg::OnStcZigDataClick(UINT nID)
{
	int ID = nID - IDC_STC_ZIG_DATA_0;

	CString strOld, strNew;
	m_stcZigData[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcZigData[ID].SetWindowText(strNew);
}



void CSetupEquipDlg::OnStcTriggerTopClick(UINT nID)
{
	int ID = nID - IDC_STC_TRIGGER_TOP_0;

	CString strOld, strNew;
	m_stcTriggerTop[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcTriggerTop[ID].SetWindowText(strNew);
}



void CSetupEquipDlg::OnStcTriggerBtmClick(UINT nID)
{
	int ID = nID - IDC_STC_TRIGGER_BTM_0;

	CString strOld, strNew;
	m_stcTriggerBtm[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcTriggerBtm[ID].SetWindowText(strNew);
}


void CSetupEquipDlg::OnStcElvDataClick(UINT nID)
{
	int ID = nID - IDC_STC_ELV_DATA_0;

	CString strOld, strNew;
	m_stcElvData[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcElvData[ID].SetWindowText(strNew);
}



void CSetupEquipDlg::OnStnClickedStcDoorlockTime()
{
	CString strOld, strNew;

	m_stcDoorLockTime.GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcDoorLockTime.SetWindowText(strNew);
}


void CSetupEquipDlg::OnBnClickedBtnModelAdd()
{
	CString strModel;
	m_stcEquipModel.GetWindowText(strModel);

	if(!strModel.IsEmpty())
	{
		CString sPathSource;
		sPathSource = gsCurrentDir + "\\System\\Model";
		sPathSource += _T("\\");
		sPathSource += strModel;

		if (GetFileAttributes(sPathSource) == -1) {	// µ∑∫≈‰∏Æ æ¯¿Ω
			g_objLogFile.Create_Folder(sPathSource);

			CString strOriginFile, strTargetFile;

			strOriginFile = gsCurrentDir + "\\System\\EquipData.ini";
			strTargetFile = sPathSource + "\\EquipData.ini";
			if (!CopyFile(strOriginFile, strTargetFile, FALSE)) {
				AfxMessageBox("EquipData.ini File Copy Fail!!!");
				return;
			}
/*
			strOriginFile = gsCurrentDir + "\\System\\MoveData.ini";
			strTargetFile = sPathSource + "\\MoveData.ini";
			if (!CopyFile(strOriginFile, strTargetFile, FALSE)) {
				AfxMessageBox("EquipData.ini File Copy Fail!!!");
				return;
			}
*/
		} else {
			if (gData.nLanguage == 0) AfxMessageBox("¿ÃπÃ ∞∞¿∫ ∏µ®¿Ã ¿÷Ω¿¥œ¥Ÿ.");
			else					  AfxMessageBox("You already have the same model.");
		}
		Save_EquipData();

		Display_EquipData();
	}
}


void CSetupEquipDlg::OnStnClickedStcEquipModel()
{
	CString strKey, strMsg;
	if (g_objCommon.Show_KeyPad(strKey) != IDOK) return;
	if (strKey.Find("-") >= 0) {
		strMsg.Format("[%s] Recipe Name ( - ) ¿‘∑¬∫“∞°...", strKey);
		g_objCommon.Show_MsgBox(1, strMsg);
		return;
	}
	if (strKey.Find(" ") >= 0) {
		strMsg.Format("[%s] Recipe Name (  ) ¿‘∑¬∫“∞°...", strKey);
		g_objCommon.Show_MsgBox(1, strMsg);
		return;
	}

	m_stcEquipModel.SetWindowText(strKey);

	m_strLog.Format("[Setup Equip] OnStnClickedStcEquipModel - Data(%s)", strKey);
	g_objLogFile.Save_HandlerLog(m_strLog);
}


void CSetupEquipDlg::OnCbnSelchangeCboModelChange()
{
	CString strModel;
	int nSel = m_cboModelChange.GetCurSel();
	m_cboModelChange.GetLBText(nSel, strModel);

	if(!strModel.IsEmpty())
	{
		CString sPathSource;
		sPathSource = gsCurrentDir + "\\System\\Model";
		sPathSource += _T("\\");
		sPathSource += strModel;
		sPathSource += _T("\\");

		g_objDataManager.Read_ModelEquipData(sPathSource);
		//		g_objDataManager.Read_ModelMoveData(sPathSource);

		Display_EquipData();
	}
}


void CSetupEquipDlg::OnCbnDropdownCboModelChange()
{
	InitModelComboBox();
}
