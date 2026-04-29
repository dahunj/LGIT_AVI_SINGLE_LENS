// Common.h : 헤더 파일
//
#pragma once

#define AUTO_COUNT			10

#define AUTO_LD_CONVEYOR		0
#define AUTO_MZ_ELEVATOR		1
#define AUTO_FEEDER				2
#define AUTO_TRAY_PICKER		3
#define AUTO_LENS_CLEANER		4
#define AUTO_TOP_INSPECT		5
#define AUTO_BTM_INSPECT		6
#define AUTO_MARKER				7
#define AUTO_INDEX_TABLE		8
#define AUTO_UL_CONVEYOR		9

// Module Tracking
#define LOAD_STAGE        0   
#define LOAD_PICK        1    
#define INDEX_LOAD_NO    2    
#define INDEX_LOAD_JIG    3   
#define UNLOAD_PICK        4  

// CCommon

class CCommon : public CWnd
{
	DECLARE_DYNAMIC(CCommon)

public:
	CCommon();
	virtual ~CCommon();

protected:
	DECLARE_MESSAGE_MAP()

private:
	LONGLONG	m_nFreq;		// Frequence

public:
	void Save_MotionPos();
	int	 Check_MotionPos();

	BOOL Check_Position(int nAxis, int nMoveIdx, double dRange = 0.1);
	void Move_Position(int nAxis, int nMoveIdx);

	void Show_Error(int nErrNo);
	void Set_ErrorSubMessage(CString sErrSubMsg);
	void Show_Alarm(CString sMsg, int nState=4, BOOL bOn=TRUE);
	int Show_MsgBox(int nBtnCnt, CString sMsg);
	int Show_NumPad(CString sOld, CString &sNew, int nAxis = -1);
	int Show_KeyPad(CString &sKey);
	int Show_Password(int &nUser);

	BOOL Check_MainEmgAir();
	BOOL Check_MainDoor(BOOL bAuto=FALSE);

	BOOL Check_TrayFull();

	

	BOOL Check_ServoOn();
	BOOL Check_DirveAlarm();
	BOOL Check_EndLimit();
	BOOL Check_HomeDone();

 	void Locking_MainDoor(BOOL bLock, BOOL bAuto=FALSE);
 	void Locking_PortSlide(BOOL bLock, int nPart=0);

	///////////////////////////////////////////////////////////////////////////
	void Get_RAMSize(CString &strRAM);
	void Get_CPUInfo(CString &strCPU);
	void Get_HardInfo(CString &strHardDisk);


	///////////////////////////////////////////////////////////////////////////
	
	int Get_Random(int nStart, int nEnd);
	void Backup_File(CString strPath, CString strName);	// System Folder


	void  Get_MainIndexPos(int nPos);

	///////////////////////////////////////////////////////////////////////////
	void Set_ElevStopper1In();
	void Set_ElevStopper1Out();
	void Set_ElevStopper1Up();
	void Set_ElevStopper1Down();
	BOOL Get_ElevStopper1In();
	BOOL Get_ElevStopper1Out();
	BOOL Get_ElevStopper1Up();
	BOOL Get_ElevStopper1Down();

	void Set_ElevStopper2In();
	void Set_ElevStopper2Out();
	void Set_ElevStopper2Up();
	void Set_ElevStopper2Down();
	BOOL Get_ElevStopper2In();
	BOOL Get_ElevStopper2Out();
	BOOL Get_ElevStopper2Up();
	BOOL Get_ElevStopper2Down();
	
	void Set_IndexLoadAlignIn();
	void Set_IndexLoadAlignOut();

	BOOL Get_IndexLoadAlignIn();
	BOOL Get_IndexLoadAlignOut();


	void Set_CleanerClose();
	void Set_CleanerOpen();

	BOOL Get_CleanerClose();
	BOOL Get_CleanerOpen();

	void Set_TrayPickMasterIn();
	void Set_TrayPickSlaveIn();

	BOOL Get_TrayPickMasterIn();
	BOOL Get_TrayPickSlaveIn();
	BOOL Get_TrayPickMasterSlaveIn();

	void Set_TrayPickMasterOut();
	void Set_TrayPickSlaveOut();

	BOOL Get_TrayPickMasterOut();
	BOOL Get_TrayPickSlaveOut();
	BOOL Get_TrayPickMasterSlaveOut();

	void Set_FeederClose();
	void Set_FeederOpen();
	BOOL Get_FeederClose();
	BOOL Get_FeederOpen();


	void Set_CleanerForward();
	void Set_CleanerBackward();

	BOOL Get_CleanerForwardDone();
	BOOL Get_CleanerBackwardDone();

	void Set_LoadCVRunCCW();
	void Set_LoadCVRunCW();
	void Set_LoadCVStop();

	void Set_UnloadCVRunCCW();
	void Set_UnloadCVRunCW();
	void Set_UnloadCVStop();

	void Set_ElevCVRunCCW();
	void Set_ElevCVRunCW();
	void Set_ElevCVStop();

};

extern CCommon g_objCommon;

///////////////////////////////////////////////////////////////////////////////
