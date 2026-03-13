// SetupEquipDlg.cpp : ±∏«ˆ ∆ƒ¿œ¿‘¥œ¥Ÿ.
//
#include "stdafx.h"
#include "SingleLens.h"
#include "SetupEquipDlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "DataManager.h"
#include "Common.h"
#include "SetupDlg.h"
#include "MESInterface.h"
#include "AviHandler.h"

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
	for (int i = 0; i < 12; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 7; i++) DDX_Control(pDX, IDC_LABEL_0 + i,  m_Label[i]);

	DDX_Control(pDX, IDC_STC_EQUIP_NAME, m_stcEquipName);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_RDO_MODEL_0 + i, m_rdoModel[i]);
	DDX_Control(pDX, IDC_CBO_LOT_BARCODE_PORT, m_cboLotBarcodePort);
	DDX_Control(pDX, IDC_CBO_LOAD_CELL_PORT_0, m_cboAssyLoadCellPort);
	DDX_Control(pDX, IDC_CBO_LOAD_CELL_PORT_1, m_cboUnloadLoadCellPort);
	DDX_Control(pDX, IDC_STC_MOTION_CHECK, m_stcMotionCheck);
	DDX_Control(pDX, IDC_LBL_DOOR_LOCK, m_lblDoorLock);	
	DDX_Control(pDX, IDC_LBL_DOOR_LOCK2, m_lblDoorLock2);
	DDX_Control(pDX, IDC_STC_DOORLOCK_TIME, m_stcDoorLockTime);

	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_RDO_DOOR_LOCK_0 + i, m_rdoDoorLock[i]);
	DDX_Control(pDX, IDC_CBO_MOVE_DATA_SEL, m_cboMoveDataSelection);

	DDX_Control(pDX, IDC_CHK_USE_INLINE_MODE, m_chkUseInlineMode);
	DDX_Control(pDX, IDC_CHK_USE_VISION_CAP_DIR, m_chkUseVisionCapDir);
	DDX_Control(pDX, IDC_CHK_USE_VISION_CM_ALIGN, m_chkUseVisionCmAlign);
	DDX_Control(pDX, IDC_CHK_USE_VISION_ALIGN_ALARM, m_chkUseVisionAlignAlarm);
	DDX_Control(pDX, IDC_CHK_USE_VISION_ALIGN_OFFSET, m_chkUseVisionAlignOffset);

	DDX_Control(pDX, IDC_CHK_USE_TRAY_PICKER_TURN, m_chkUseTrayPickerTurn);
	DDX_Control(pDX, IDC_CHK_USE_CAP_PICKER_TURN, m_chkUseCapPickerTurn);
	DDX_Control(pDX, IDC_CHK_ASSY_PICKER_TILT, m_chkAssyPickerTilt);

	DDX_Control(pDX, IDC_CHK_CAP_PICK_UP_MULTI, m_chkCapPickUpMulti);
	DDX_Control(pDX, IDC_CHK_USE_MES_CAP_REG, m_chkUseMesCapReg);
	DDX_Control(pDX, IDC_CHK_USE_MES_SHIP_REG, m_chkUseMesShipReg);
	DDX_Control(pDX, IDC_CHK_USE_INDEX_ASSY_VAC, m_chkUseIndexAssyVac);
	
	for (int i = 0; i < 13; i++) DDX_Control(pDX, IDC_LBL_MODEL_0 + i,  m_lblModel[i]);
	for (int i = 0; i < 1; i++) DDX_Control(pDX, IDC_STC_INDEX_DATA_0 + i, m_stcIndexData[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_LOAD_TRAY_DATA_0 + i, m_stcLoadTrayData[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_CAP_TRAY_DATA_0 + i, m_stcCapTrayData[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_SHIP_TRAY_DATA_0 + i, m_stcShipTrayData[i]);

	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_LBL_PICKER_VAC_OFF_0 + i,  m_lblPickerVacOff[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_VAC_OFF_DELAY_0 + i, m_stcVacOffDelay[i]);

	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_LBL_DELAY_ADD_0 + i,  m_lblDelayAdd[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_STC_DELAY_ADD_0 + i, m_stcDelayAdd[i]);

	DDX_Control(pDX, IDC_LBL_AVI_IP, m_lblAviIp);
	DDX_Control(pDX, IDC_IPA_AVI_IP, m_ipaAviIp);

	DDX_Control(pDX, IDC_LBL_ALIGN_OFFSET, m_lblAlignOffset);
	DDX_Control(pDX, IDC_STC_ALIGN_OFFSET, m_stcAlignOffset);

	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_STC_LOAD_CELL_RANGE_0 + i, m_stcLoadCellRange[i]);

	DDX_Control(pDX, IDC_GRP_TOWER, m_grpTower);
	for (int i = 0; i < 10; i++) DDX_Control(pDX, IDC_LBL_TOWER_0 + i,  m_lblTower[i]);
	for (int i = 0; i < 6; i++) for (int j = 0; j < 4; j++) DDX_Control(pDX, IDC_CHK_TOWER_0_0 + i * 4 + j,  m_chkTower[i][j]);
	DDX_Control(pDX, IDC_GRP_BUZZER, m_grpBuzzer);
	for (int i = 0; i < 11; i++) DDX_Control(pDX, IDC_LBL_BUZZER_0 + i,  m_lblBuzzer[i]);
	for (int i = 0; i < 5; i++) for (int j = 0; j < 6; j++) DDX_Control(pDX, IDC_CHK_BUZZER_0_0 + i * 6 + j,  m_chkBuzzer[i][j]);

	DDX_Control(pDX, IDC_GRP_HIDDEN, m_grpHidden);
	DDX_Control(pDX, IDC_LBL_PASSWORD_MT, m_lblPasswordMt);
	DDX_Control(pDX, IDC_STC_PASSWORD_MT, m_stcPasswordMt);
	DDX_Control(pDX, IDC_LBL_PASSWORD_SI, m_lblPasswordSi);
	DDX_Control(pDX, IDC_EDT_PASSWORD_SI, m_edtPasswordSi);

	for(int i = 0; i < 3; i++) DDX_Control(pDX, IDC_LBL_VISION_0 +i, m_lblCMVision[i] );
	for(int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_CM_VISION_0 +i, m_stcCMVision[i]);

	DDX_Control(pDX, IDC_GRP_RESULT_TEST, m_grpResultTest);
	DDX_Control(pDX, IDC_LBL_RESULT_TEST, m_lblResultTest);
	DDX_Control(pDX, IDC_CHK_RESULT_TEST_USE, m_chkResultTestUse);
	DDX_Control(pDX, IDC_EDT_RESULT_TEST, m_edtResultTest);

}

BEGIN_MESSAGE_MAP(CSetupEquipDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_STN_CLICKED(IDC_STC_EQUIP_NAME, &CSetupEquipDlg::OnStnClickedStcEquipName)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RDO_MODEL_0, IDC_RDO_MODEL_1, OnRdoModelClick)
	ON_STN_CLICKED(IDC_STC_MOTION_CHECK, &CSetupEquipDlg::OnStnClickedStcMotionCheck)

	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_INDEX_DATA_0, IDC_STC_INDEX_DATA_0, OnStcIndexDataClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_LOAD_TRAY_DATA_0, IDC_STC_LOAD_TRAY_DATA_3, OnStcLoadTrayDataClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_CAP_TRAY_DATA_0, IDC_STC_CAP_TRAY_DATA_3, OnStcCapTrayDataClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_SHIP_TRAY_DATA_0, IDC_STC_SHIP_TRAY_DATA_3, OnStcShipTrayDataClick)

	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_VAC_OFF_DELAY_0, IDC_STC_VAC_OFF_DELAY_2, OnStcVacOffDelayClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_DELAY_ADD_0, IDC_STC_DELAY_ADD_5, OnStcDelayAddClick)

	ON_STN_CLICKED(IDC_STC_ALIGN_OFFSET, &CSetupEquipDlg::OnStcAlignOffsetClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_LOAD_CELL_RANGE_0, IDC_STC_LOAD_CELL_RANGE_1, OnStcLoadCellRangeClick)

	ON_STN_CLICKED(IDC_STC_SHOW_HIDDEN, &CSetupEquipDlg::OnStnClickedStcShowHidden)
	ON_STN_CLICKED(IDC_STC_PASSWORD_MT, &CSetupEquipDlg::OnStnClickedStcPasswordMt)
	ON_BN_CLICKED(IDC_BTN_AVI_CONNECT, &CSetupEquipDlg::OnBnClickedBtnAviConnect)
	ON_BN_CLICKED(IDC_BTN_AVI_DISCONNECT, &CSetupEquipDlg::OnBnClickedBtnAviDisconnect)
	ON_STN_CLICKED(IDC_STC_CM_VISION_0, &CSetupEquipDlg::OnStnClickedStcCmVision0)
	ON_STN_CLICKED(IDC_STC_CM_VISION_1, &CSetupEquipDlg::OnStnClickedStcCmVision1)
	ON_STN_CLICKED(IDC_STC_CM_VISION_2, &CSetupEquipDlg::OnStnClickedStcCmVision2)
	ON_STN_CLICKED(IDC_STC_DOORLOCK_TIME, &CSetupEquipDlg::OnStnClickedStcDoorlockTime)
END_MESSAGE_MAP()

// CSetupEquipDlg ∏ﬁΩ√¡ˆ √≥∏Æ±‚¿‘¥œ¥Ÿ.

void CSetupEquipDlg::Initial_Controls() 
{
	CString strText;
	for (int i = 0; i < 12; i++) m_Group[i].Init_Ctrl("πŸ≈¡", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	m_Label[0].Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x10, 0xC0));	// Equip Name
	m_Label[1].Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xA0, 0x00));	// Model
	for (int i = 2; i < 5; i++) m_Label[i].Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x10, 0xC0));	// Port
	m_Label[5].Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x10, 0xC0));	// Motin Check
	m_Label[6].Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x20, 0x20)); // Vendor Selection 

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	strText.Format("%s", pEquipData->sVendor[0]); m_cboMoveDataSelection.AddString(strText); 
	strText.Format("%s", pEquipData->sVendor[1]); m_cboMoveDataSelection.AddString(strText); 

	m_cboMoveDataSelection.Init_Ctrl("πŸ≈¡", 12, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xF0, 0xE0, 0x00));



	m_stcEquipName.Init_Ctrl("πŸ≈¡", 15, TRUE, RGB(0x00, 0x00, 0x80), RGB(0xE0, 0xFF, 0xE0));
	for (int i = 0; i < 2; i++) m_rdoModel[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xF0, 0xE0, 0x00), CRadioCS::emRed, 0);
	for (int i = 0; i < 4; i++) { strText.Format("COM%d", i + 1); m_cboLotBarcodePort.AddString(strText); }
	m_cboLotBarcodePort.Init_Ctrl("πŸ≈¡", 12, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xF0, 0xE0, 0x00));
	for (int i = 7; i < 9; i++) { strText.Format("COM%d", i + 1); m_cboAssyLoadCellPort.AddString(strText); }
	m_cboAssyLoadCellPort.Init_Ctrl("πŸ≈¡", 12, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xF0, 0xE0, 0x00));
	for (int i = 7; i < 9; i++) { strText.Format("COM%d", i + 1); m_cboUnloadLoadCellPort.AddString(strText); }
	m_cboUnloadLoadCellPort.Init_Ctrl("πŸ≈¡", 12, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xF0, 0xE0, 0x00));

	m_stcMotionCheck.Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0x00, 0x00, 0x80), RGB(0xF0, 0xE0, 0x00));
	m_lblDoorLock.Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	for (int i = 0; i < 2; i++) m_rdoDoorLock[i].Init_Ctrl("πŸ≈¡", 11, FALSE, COLOR_DEFAULT, RGB(0xC0, 0xC0, 0xC0), CRadioCS::emRed, 0);
	m_lblDoorLock2.Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	m_stcDoorLockTime.Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0x00, 0x00, 0x80), RGB(0xF0, 0xE0, 0x00));

	m_chkUseInlineMode.Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xD0, 0x80, 0x20), CCheckCS::emRed, 0);

	m_chkUseVisionCapDir.Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0x00, 0xF0, 0xF0), CCheckCS::emRed, 0);

	m_chkUseVisionCmAlign.Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0x60, 0xF0, 0x80), CCheckCS::emRed, 0);
	m_chkUseVisionAlignAlarm.Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0x60, 0xF0, 0x80), CCheckCS::emRed, 0);
	m_chkUseVisionAlignOffset.Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0x60, 0xF0, 0x80), CCheckCS::emRed, 0);

	m_chkUseTrayPickerTurn.Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xD0, 0xA0, 0xF0), CCheckCS::emRed, 0);
	m_chkUseCapPickerTurn.Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xD0, 0xA0, 0xF0), CCheckCS::emRed, 0);
	m_chkAssyPickerTilt.Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xD0, 0xA0, 0xF0), CCheckCS::emRed, 0);
	m_chkCapPickUpMulti.Init_Ctrl("πŸ≈¡", 10, TRUE, COLOR_DEFAULT, RGB(0xD0, 0xA0, 0xF0), CCheckCS::emRed, 0);

	m_chkUseMesCapReg.Init_Ctrl("πŸ≈¡", 10, TRUE, COLOR_DEFAULT, RGB(0xD0, 0x80, 0x20), CCheckCS::emRed, 0);
	m_chkUseMesShipReg.Init_Ctrl("πŸ≈¡", 10, TRUE, COLOR_DEFAULT, RGB(0xD0, 0x80, 0x20), CCheckCS::emRed, 0);
	m_chkUseIndexAssyVac.Init_Ctrl("πŸ≈¡", 10, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0x00), CCheckCS::emRed, 0);

	m_lblModel[0].Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x80, 0xC0));
	for (int i = 1; i < 5; i++) m_lblModel[i].Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x20, 0x50, 0x00));
	for (int i = 5; i < 9; i++) m_lblModel[i].Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x20, 0x20));
	for (int i = 9; i < 13; i++) m_lblModel[i].Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x40, 0x80));
	for (int i = 0; i < 1; i++) m_stcIndexData[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xE0));
	for (int i = 0; i < 2; i++) m_stcLoadTrayData[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xD0, 0xD0, 0xD0));
	for (int i = 2; i < 4; i++) m_stcLoadTrayData[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xE0));
	for (int i = 0; i < 2; i++) m_stcCapTrayData[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xD0, 0xD0, 0xD0));
	for (int i = 2; i < 4; i++) m_stcCapTrayData[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xE0));
	for (int i = 0; i < 2; i++) m_stcShipTrayData[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xD0, 0xD0, 0xD0));
	for (int i = 2; i < 4; i++) m_stcShipTrayData[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xE0));

	for (int i = 0; i < 3; i++) m_lblPickerVacOff[i].Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x80, 0x00, 0x00));
	for (int i = 0; i < 3; i++) m_stcVacOffDelay[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xE0, 0xE0));

	for (int i = 0; i < 6; i++) m_lblDelayAdd[i].Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x60, 0x40));
	for (int i = 0; i < 6; i++) m_stcDelayAdd[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xE0));

	m_lblAviIp.Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));

	m_lblAlignOffset.Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x80, 0xC0));
	m_stcAlignOffset.Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xE0));

	for (int i = 0; i < 2; i++) m_stcLoadCellRange[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xE0, 0xE0));

	m_grpTower.Init_Ctrl("πŸ≈¡", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	for (int i = 0; i < 10; i++) m_lblTower[i].Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 6; i++) for (int j = 0; j < 4; j++) m_chkTower[i][j].Init_Ctrl("πŸ≈¡", 11, FALSE, COLOR_DEFAULT, RGB(0x00, 0xF0, 0x00), CCheckCS::emRed, 0);
	m_grpBuzzer.Init_Ctrl("πŸ≈¡", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	for (int i = 0; i < 11; i++) m_lblBuzzer[i].Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 5; i++) for (int j = 0; j < 6; j++) m_chkBuzzer[i][j].Init_Ctrl("πŸ≈¡", 11, FALSE, COLOR_DEFAULT, RGB(0x00, 0xE0, 0xF0), CCheckCS::emRed, 0);

	m_grpHidden.Init_Ctrl("πŸ≈¡", 10, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	m_lblPasswordMt.Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	m_stcPasswordMt.Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0xC0, 0xC0, 0xC0));
	m_lblPasswordSi.Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	m_edtPasswordSi.Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);

	for (int i = 0; i < 3; i++) m_lblCMVision[i].Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	for (int i = 0; i < 3; i++) m_stcCMVision[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xD0, 0xD0, 0xD0));

	m_grpResultTest.Init_Ctrl("πŸ≈¡", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	m_lblResultTest.Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	m_chkResultTestUse.Init_Ctrl("πŸ≈¡", 10, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60), CCheckCS::emRed, 0);
	m_edtResultTest.Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);

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
	m_lblPasswordMt.ShowWindow(SW_HIDE);
	m_stcPasswordMt.ShowWindow(SW_HIDE);
	m_lblPasswordSi.ShowWindow(SW_HIDE);
	m_edtPasswordSi.ShowWindow(SW_HIDE);

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

void CSetupEquipDlg::OnRdoModelClick(UINT nID)
{
	CIniFileCS INI(gsCurrentDir + "\\System\\EquipData.ini");
	if (!INI.Check_File()) { AfxMessageBox("EquipData.ini File Not Found!!!"); return; }

	CString strData;
	CString strModel = (m_rdoModel[1].GetCheck() ? "R54B" : "R53B");

	int nTrayY =  ST_Y;
	strData.Format("%d", nTrayY); m_stcShipTrayData[1].SetWindowText(strData);

	double dPitchX = INI.Get_Double("SHIP_TRAY", "PITCH_X_" + strModel, 0.0);
	double dPitchY = INI.Get_Double("SHIP_TRAY", "PITCH_Y_" + strModel, 0.0);
	strData.Format("%0.2lf", dPitchX); m_stcShipTrayData[2].SetWindowText(strData);
	strData.Format("%0.2lf", dPitchY); m_stcShipTrayData[3].SetWindowText(strData);
}

void CSetupEquipDlg::OnStnClickedStcMotionCheck()
{
	CString strOld, strNew;
	m_stcMotionCheck.GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcMotionCheck.SetWindowText(strNew);
}

void CSetupEquipDlg::OnStcIndexDataClick(UINT nID)
{
	int ID = nID - IDC_STC_INDEX_DATA_0;

	CString strOld, strNew;
	m_stcIndexData[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcIndexData[ID].SetWindowText(strNew);
}

void CSetupEquipDlg::OnStcLoadTrayDataClick(UINT nID)
{
	int ID = nID - IDC_STC_LOAD_TRAY_DATA_0;

	CString strOld, strNew;
	m_stcLoadTrayData[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcLoadTrayData[ID].SetWindowText(strNew);
}

void CSetupEquipDlg::OnStcCapTrayDataClick(UINT nID)
{
	int ID = nID - IDC_STC_CAP_TRAY_DATA_0;

	CString strOld, strNew;
	m_stcCapTrayData[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcCapTrayData[ID].SetWindowText(strNew);
}

void CSetupEquipDlg::OnStcShipTrayDataClick(UINT nID)
{
	int ID = nID - IDC_STC_SHIP_TRAY_DATA_0;

	CString strOld, strNew;
	m_stcShipTrayData[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcShipTrayData[ID].SetWindowText(strNew);
}

void CSetupEquipDlg::OnStcVacOffDelayClick(UINT nID)
{
	int ID = nID - IDC_STC_VAC_OFF_DELAY_0;

	CString strOld, strNew;
	m_stcVacOffDelay[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcVacOffDelay[ID].SetWindowText(strNew);
}

void CSetupEquipDlg::OnStcDelayAddClick(UINT nID)
{
	int ID = nID - IDC_STC_DELAY_ADD_0;

	CString strOld, strNew;
	m_stcDelayAdd[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcDelayAdd[ID].SetWindowText(strNew);
}

void CSetupEquipDlg::OnStcAlignOffsetClick()
{
	CString strOld, strNew;
	m_stcAlignOffset.GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcAlignOffset.SetWindowText(strNew);
}

void CSetupEquipDlg::OnStcLoadCellRangeClick(UINT nID)
{
	int ID = nID - IDC_STC_LOAD_CELL_RANGE_0;

	CString strOld, strNew;
	m_stcLoadCellRange[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcLoadCellRange[ID].SetWindowText(strNew);
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
	m_stcPasswordMt.SetWindowText(strData);
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
		m_lblPasswordMt.ShowWindow(SW_HIDE);
		m_stcPasswordMt.ShowWindow(SW_HIDE);
		if (g_dlgSetup.Get_LoginUser() != 2) return;
		m_lblPasswordSi.ShowWindow(SW_HIDE);
		m_edtPasswordSi.ShowWindow(SW_HIDE);
	} else {
		m_grpResultTest.ShowWindow(SW_SHOW);
		m_lblResultTest.ShowWindow(SW_SHOW);
		m_chkResultTestUse.ShowWindow(SW_SHOW);
		m_edtResultTest.ShowWindow(SW_SHOW);


		m_grpHidden.ShowWindow(SW_SHOW);
		m_lblPasswordMt.ShowWindow(SW_SHOW);
		m_stcPasswordMt.ShowWindow(SW_SHOW);
		if (g_dlgSetup.Get_LoginUser() != 2) return;
		m_lblPasswordSi.ShowWindow(SW_SHOW);
		m_edtPasswordSi.ShowWindow(SW_SHOW);
	}
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupEquipDlg::Display_EquipData()
{
	

}

void CSetupEquipDlg::Save_EquipData()
{
	
}

void CSetupEquipDlg::Cancel_EquipData()
{
	g_objDataManager.Read_EquipData();
	g_objDataManager.Read_MoveData();
	g_objCommon.Read_CapShipPartNo();

	Display_EquipData();

	g_objLogFile.Save_HandlerLog("[Setup Equip] Cancel Click");
}

///////////////////////////////////////////////////////////////////////////////


void CSetupEquipDlg::OnBnClickedBtnAviConnect()
{
	g_objAviHandler.Initialize();
}


void CSetupEquipDlg::OnBnClickedBtnAviDisconnect()
{
	g_objAviHandler.Set_ConnectStatus(FALSE);
	g_objAviHandler.Terminate();
}


void CSetupEquipDlg::OnStnClickedStcCmVision0()
{
	CString strOld, strNew;
	m_stcCMVision[0].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcCMVision[0].SetWindowText(strNew);
}


void CSetupEquipDlg::OnStnClickedStcCmVision1()
{
	CString strOld, strNew;
	m_stcCMVision[1].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcCMVision[1].SetWindowText(strNew);
}


void CSetupEquipDlg::OnStnClickedStcCmVision2()
{
	CString strOld, strNew;
	m_stcCMVision[2].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcCMVision[2].SetWindowText(strNew);
}


void CSetupEquipDlg::OnStnClickedStcDoorlockTime()
{
	CString strOld, strNew;

	m_stcDoorLockTime.GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcDoorLockTime.SetWindowText(strNew);
}
