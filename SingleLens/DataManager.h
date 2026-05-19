// DataManager.h : 헤더 파일
//
#pragma once

///////////////////////////////////////////////////////////////////////////////
// Equip Data
typedef struct tag_EQUIP_DATA {
	
	double	dElevPitchZ;
	double	dElevPitchZReady;
	
	BOOL	bUseCleaner;
	BOOL	bUseTopVision;
	BOOL	bUseBtmVision;
	BOOL	bUseMark;


	int		nZigArrayX;
	int		nZigArrayY;
	double  dZigPitchY;
	double	dZigPitchX;
	
	BOOL	bUseInspectSkip;


	CString sEquipName;
	CString sModel;
	int		nLotBarcodePort;

	BOOL	bUseDoorLock;
	
	BOOL	bUseMES;	

	double	dIndexPitch;

	int		nVacOffDelay[3];	// 0:Load,1:Assy,2:Unload
	int		nDelayAdd[6];		// 0:LoadPicker Grip, 1:CapPicker VacOn, 2:AssyPicker VacOn, 3:UnloadPicker VacOn, 4:LoadCell, 5:AssyPicker CapPress

	CString	sAviIp;

	BOOL	bTower[6][4];		// [0:None,1:Init,2:Ready,3:Run,4:Alarm,5:Error][0:Green,1:Yellow,2:Red,3:Flicker]
	BOOL	bBuzzer[5][6];		// [0::Alarm,1:Error,2:LotEnd,3:CapTray,4:ShipTray][0:Bit0,1:Bit1,2:Bit2,3:Bit3,4:Bit4,5:Flicker]
	CString	sPasswordOp;
	CString	sPasswordEngr;
		

	BOOL	bResultTestUse;		// Result Test Use
	int		nResultTestNg;		// Result Test Ng Ratio (0~100)

	//Trigger 
	double	dTopStart;
	int	dTopCount;
	double	dTopPeriod;
	double	dTopVelocity;

	double	dBtmStart;
	int	dBtmCount;
	double	dBtmPeriod;
	double	dBtmVelocity;




} EQUIP_DATA;

///////////////////////////////////////////////////////////////////////////////
// Move Data
typedef struct tag_MOVE_DATA 
{

	double  dMZElevZ[5];			// AXIS 00	[2]
	double  dFeederX[5];			// AXIS 01	[3]
	double  dFeederY[5];			// AXIS 02	[2]
	double  dTrayPickerY[5];		// AXIS 04	[4]
	double  dTrayPickerZ[5];		// AXIS 05	[5]
	double  dTopInspectorX[5];		// AXIS 06	[4]
	double  dTopInspectorY[5];		// AXIS 07	[5]
	double  dTopInspectorZ[5];		// AXIS 08	[3]
	double  dBtmInspectorX[5];		// AXIS 09	[4]
	double  dBtmInspectorY[5];		// AXIS 10	[2]
	double  dBtmInspectorZ[5];		// AXIS 11	[1]
	double  dMarkUnitX[5];			// AXIS 12	[2]
	double  dMarkUnitY[5];			// AXIS 12	[2]
	double  dMarkUnitZ[5];			// AXIS 12	[2]
	double  dMainIndexR[5];			// AXIS 12	[2]
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
