// SetupEquipDlg.h : 헤더 파일
//
#pragma once

// CSetupEquipDlg 대화 상자입니다.

class CSetupEquipDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupEquipDlg)

public:
	CSetupEquipDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSetupEquipDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SETUP_EQUIP_DLG };
	CGroupCS	m_Group[12];

	CLabelCS	m_lblMotionCheck;
	CLabelCS	m_lblNoWorkTime;
	CLabelCS	m_lblSafetySwitch;

	CLabelCS	m_lblCtZig[4];
	CLabelCS	m_lblTriggerTop[8];
	CLabelCS	m_lblTriggerBtm[8];

	CLabelCS	m_lblPitchZ;
	CLabelCS	m_lblRepeat;
	CLabelCS	m_lblMarking[2];

	CStaticCS	m_stcEquipName;
	CStaticCS	m_stcEquipModel;
	CComboCS    m_cboModelChange;
		
	CStaticCS	m_stcNoWorkTime;
	CStaticCS	m_stcSafetySwitch;

	CStaticCS	m_stcMotionCheck;
	CLabelCS	m_lblDoorLock;
	CRadioCS	m_rdoDoorLock[2];
	CLabelCS	m_lblDoorLock2;
	CStaticCS	m_stcDoorLockTime;
	
	CLabelCS	m_lblDelayAdd[8];
	CStaticCS	m_stcDelayAdd[8];

	CLabelCS	m_lblAviIp;
	CIPAddressCtrl	m_ipaAviIp;

	CStaticCS	m_stcZigData[4];
	CStaticCS	m_stcTriggerTop[8];
	CStaticCS	m_stcTriggerBtm[8];

	CStaticCS	m_stcElvData[1];
	CStaticCS	m_stcCleanerData;

	CStaticCS	m_stcMarkCount;
	CStaticCS	m_stcMarkTimeout;

	CGroupCS	m_grpTower;
	CLabelCS	m_lblTower[10];
	CCheckCS	m_chkTower[6][4];
	CGroupCS	m_grpBuzzer;
	CLabelCS	m_lblBuzzer[11];
	CCheckCS	m_chkBuzzer[5][6];

	CGroupCS	m_grpHidden;
	CLabelCS	m_lblPasswordOp;
	CStaticCS	m_stcPasswordOp;
	CLabelCS	m_lblPasswordEngr;
	CEditCS		m_edtPasswordEngr;

	CGroupCS	m_grpResultTest;
	CLabelCS	m_lblResultTest;
	CCheckCS	m_chkResultTestUse;
	CEditCS		m_edtResultTest;

	CCheckCS	m_chkTopVision;
	CCheckCS	m_chkBtmVision;
	CCheckCS	m_chkMarkUse;

	CCheckCS	m_chkUseMES;
	CCheckCS	m_chkUseMESLotEndSelect;

	CCheckCS	m_chkUseBarcodeMGZ;
	CCheckCS	m_chkUseBarcodeCtZig;

	CCheckCS	m_chkAutoRecipeChange;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnStnClickedStcEquipName();
	afx_msg void OnStnClickedStcMotionCheck();
	afx_msg void OnStnClickedStcDoorlockTime();
	afx_msg void OnStnClickedStcNoWorkTime();
	afx_msg void OnStcZigDataClick(UINT nID);
	afx_msg void OnStcTriggerTopClick(UINT nID);
	afx_msg void OnStcTriggerBtmClick(UINT nID);
	afx_msg void OnStcElvDataClick(UINT nID);
	afx_msg void OnBnClickedBtnModelAdd();
	afx_msg void OnStnClickedStcEquipModel();
	afx_msg void OnCbnSelchangeCboModelChange();
	afx_msg void OnCbnDropdownCboModelChange();
	afx_msg void OnStnClickedStcCleanerData0(UINT nID);	
	afx_msg void OnStnClickedStcMarkTimeout(UINT nID);
	afx_msg void OnStcDelayAddClick(UINT nID);


	afx_msg void OnStnClickedStcShowHidden();
	afx_msg void OnStnClickedStcPasswordMt();

private:
	CString m_strLog;

	void Initial_Controls();
	void Display_EquipData();

public:
	void InitModelComboBox();
	void Save_EquipData();
	void Save_ModelEquipData(CString sPath);
	void Cancel_EquipData();

	
	afx_msg void OnBnClickedChkUseBarcodeMgz();
	afx_msg void OnBnClickedChkUseBarcodeCtzig();
	afx_msg void OnBnClickedChkUseMes();

	afx_msg void OnStnClickedStcSafetySwitch();
};

///////////////////////////////////////////////////////////////////////////////
