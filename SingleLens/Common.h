// Common.h : 헤더 파일
//
#pragma once

#define AUTO_COUNT			16

#define AUTO_TRAY_PICKER	0
#define AUTO_LOAD_STAGE1	1
#define AUTO_LOAD_STAGE2	2
#define AUTO_LOAD_PICKER	3
#define AUTO_MAIN_INDEX		4
#define AUTO_VISION_CM		5
#define AUTO_VISION_CAP		6
#define AUTO_CAP_STAGE1		7
#define AUTO_CAP_STAGE2		8
#define AUTO_CAP_PICKER		9
#define AUTO_CAP_BUFFER		10
#define AUTO_ASSY_PICKER	11
#define AUTO_TRANS_STAGE	12
#define AUTO_UNLOAD_PICKER	13
#define AUTO_UNLOAD_STAGE1	14
#define AUTO_UNLOAD_STAGE2	15

#define ASSY_LOAD_CELL		1
#define UNLOAD_LOAD_CELL	2

// Module Tracking
#define LOAD_STAGE		0	// Stage No 저장. 1 or 2
#define LOAD_PICK		1	// Picker Jig 번호 저장. 1~6
#define INDEX_LOAD_NO	2	// Index Loading 할때 번호 저장. 1~8
#define INDEX_LOAD_JIG	3	// Index Load Jig 번호 저장. 1~5
#define UNLOAD_PICK		4	// Picker Jig 번호 저장. 1~6

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
	BOOL Check_PortArea(BOOL bAuto=FALSE);
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

	void Save_CapShiipData(int nType);	//1:Cap, 2:Ship
	///////////////////////////////////////////////////////////////////////////
	void Read_CapShipPartNo();
	BOOL Check_CapShipPartNo(int nType, CString sPartNo);	//1:Cap, 2:Ship


	int Get_Random(int nStart, int nEnd);
	void Backup_File(CString strPath, CString strName);	// System Folder

	///////////////////////////////////////////////////////////////////////////
	

};

extern CCommon g_objCommon;

///////////////////////////////////////////////////////////////////////////////
