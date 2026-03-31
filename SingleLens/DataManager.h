// DataManager.h : 헤더 파일
//
#pragma once

///////////////////////////////////////////////////////////////////////////////
// Equip Data
typedef struct tag_EQUIP_DATA {
	
	double	dMZPitchLeftZ;
	double	dMZPitchRightZ;
	BOOL	bUseCleaner;
	BOOL	bUseTopVision;
	BOOL	bUseBtmVision;
	BOOL	bUseMark;

	double  dZigPitchY;
	double	dZigPitchX;
	
	BOOL	bUseInspectSkip;
	
	
/////////////////////	
	CString sEquipName;
	CString sModel;
	int		nLotBarcodePort;
	int		nAssyLoadCellPort;
	int		nUnloadLoadCellPort;
	BOOL	bUseDoorLock;

	int		nVendorSelection;
	CString sVendor[2];

	BOOL	bUseMES;
	BOOL	bUseInlineMode;
	BOOL	bUseVisionCapDir;
	
	BOOL	bUseTrayPickerTurn;
	BOOL	bUseCapPickerTurn;
	BOOL	bChkAssyPickerTilt;
	BOOL	bCapPickUpMulti;	// Cap Pick Up Type 설정 : TRUE = 멀티 픽업, FALSE = 개별 픽업
	BOOL	bUseMesCapReg;
	BOOL	bUseMesShipReg;
	BOOL	bUseIndexAssyVac;

	double	dIndexPitch;
	double	dLoadTrayPitchX;
	double	dLoadTrayPitchY;
	double	dCapTrayPitchX;
	double	dCapTrayPitchY;
	double	dShipTrayPitchX;
	double	dShipTrayPitchY;

	int		nVacOffDelay[3];	// 0:Load,1:Assy,2:Unload
	int		nDelayAdd[6];		// 0:LoadPicker Grip, 1:CapPicker VacOn, 2:AssyPicker VacOn, 3:UnloadPicker VacOn, 4:LoadCell, 5:AssyPicker CapPress

	CString	sAviIp;

	double	dAlignOffset;

	double	dLoadCellRange[2];	// 0: Min, 1: Max 

	BOOL	bTower[6][4];		// [0:None,1:Init,2:Ready,3:Run,4:Alarm,5:Error][0:Green,1:Yellow,2:Red,3:Flicker]
	BOOL	bBuzzer[5][6];		// [0::Alarm,1:Error,2:LotEnd,3:CapTray,4:ShipTray][0:Bit0,1:Bit1,2:Bit2,3:Bit3,4:Bit4,5:Flicker]
	CString	sPasswordMt;
	CString	sPasswordSi;

	int		nCappingCnt;		// Load Cell 측정을 위해 Capping한 Cap 수량 저장
	int		nLoadCellChkCnt;	// Assy Picker Load Cell 측정 주기


	BOOL	bUseVisionCmAlign;
	BOOL	bUseVisionAlignAlarm;
	BOOL	bUseVisionAlignOffset;

	int		nInspectCmScanTimes;	// 랏 당 CM 검사 최대 횟수
	int		nInspectCmLotTimes; 	// 시간당 랏 개수 
	int		nInspectCmMinutes;		// 몇분 간격으로 설정 할지 	

	BOOL	bResultTestUse;		// Result Test Use
	int		nResultTestNg;		// Result Test Ng Ratio (0~100)

} EQUIP_DATA;

///////////////////////////////////////////////////////////////////////////////
// Move Data
typedef struct tag_MOVE_DATA 
{

	double  dMzElevZ[10];			// AXIS 00	[2]
	double  dFeederX[10];			// AXIS 01	[3]
	double  dFeederY[10];			// AXIS 02	[2]
	double  dTrayPickerY[10];		// AXIS 04	[4]
	double  dTrayPickerZ[10];		// AXIS 05	[5]
	double  dTopInspectorX[10];		// AXIS 06	[4]
	double  dTopInspectorY[10];		// AXIS 07	[5]
	double  dTopInspectorZ[10];		// AXIS 08	[3]
	double  dBtmInspectorX[10];		// AXIS 09	[4]
	double  dBtmInspectorY[10];		// AXIS 10	[2]
	double  dBtmInspectorZ[10];		// AXIS 11	[1]
	double  dMarkUnitX[10];			// AXIS 12	[2]
	double  dMarkUnitY[10];			// AXIS 12	[2]
	double  dMarkUnitZ[10];			// AXIS 12	[2]
	double  dIndexTR[10];			// AXIS 12	[2]
} MOVE_DATA;

///////////////////////////////////////////////////////////////////////////////

class CDataManager
{
public:
	CDataManager();
	virtual ~CDataManager();

private:
	EQUIP_DATA	m_EquipData;
	MOVE_DATA	m_MoveData;

public:	
	void Reset_EquipData();
	void Reset_MoveData();

	BOOL Read_EquipData();
	BOOL Read_MoveData();

	EQUIP_DATA *Get_pEquipData() { return &m_EquipData; }
	MOVE_DATA *Get_pMoveData() { return &m_MoveData; }
};

extern CDataManager g_objDataManager;

///////////////////////////////////////////////////////////////////////////////
