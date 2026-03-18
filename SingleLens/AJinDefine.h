///////////////////////////////////////////////////////////////////////////////
// AJinDefine.h : AJin Structure
#pragma once

///////////////////////////////////////////////////////////////////////////////
// Motion Axis
const int AXIS_COUNT = 16;		// Motion Module


const int AX_MZ_ELEV_Z			= 0;
const int AX_FEEDER_X			= 1;
const int AX_FEEDER_Y			= 2;
const int AX_TRAY_PICKER_Y		= 3;
const int AX_TRAY_PICKER_Z		= 4;
const int AX_INDEX_TABLE_R		= 5;
const int AX_TOP_INSPECTOR_X	= 6;
const int AX_TOP_INSPECTOR_Y	= 7;
const int AX_TOP_INSPECTOR_Z	= 8;
const int AX_BTM_INSPECTOR_X	= 9;
const int AX_BTM_INSPECTOR_Y	= 10;
const int AX_BTM_INSPECTOR_Z	= 11;
const int AX_MARKER_X			= 12;
const int AX_MARKER_Y			= 13;
const int AX_MARKER_Z			= 14;	




///////////////////////////////////////////////////////////////////////////////
// Motion Status
typedef struct tag_AXIS_STATUS {
	double dPos;		// Motor Current Position
	double dVel;		// Motor Current Velocity
	BOOL bSOn;			// Servo On Status
	BOOL bOrg;			// Origin Sensor
	BOOL bELP;			// End Limit Positive
	BOOL bELN;			// End Limit Negative
	BOOL bALM;			// Driver Alarm
	BOOL bInP;			// In Position
	BOOL bRun;			// Running
	BOOL bHom;			// Home Complete
} AXIS_STATUS;

///////////////////////////////////////////////////////////////////////////////
// Motion Parameter
typedef struct tag_AXIS_PARAM {
	double dSpeedM;	// Move Speed
	double dSpeedJ;	// Jog Speed
	double dAccel;	// Move Accel
} AXIS_PARAM;

///////////////////////////////////////////////////////////////////////////////
// DIO Count
const long DIO_MODULE_COUNT = 4;		// IO Module (PCI-DI64R 2EA, PCI-DO64R 2EA)

///////////////////////////////////////////////////////////////////////////////
// 변환 타입
typedef union tag_DXY_DATA {
	DWORD nValue;
	struct {
		DWORD b0000 : 1;	// 0000
		DWORD b0001 : 1;	// 0001
		DWORD b0002 : 1;	// 0002
		DWORD b0003 : 1;	// 0003
		DWORD b0004 : 1;	// 0004
		DWORD b0005 : 1;	// 0005
		DWORD b0006 : 1;	// 0006
		DWORD b0007 : 1;	// 0007
		DWORD b0008 : 1;	// 0008
		DWORD b0009 : 1;	// 0009
		DWORD b0010 : 1;	// 0010
		DWORD b0011 : 1;	// 0011
		DWORD b0012 : 1;	// 0012
		DWORD b0013 : 1;	// 0013
		DWORD b0014 : 1;	// 0014
		DWORD b0015 : 1;	// 0015
		DWORD b0016 : 1;	// 0016
		DWORD b0017 : 1;	// 0017
		DWORD b0018 : 1;	// 0018
		DWORD b0019 : 1;	// 0019
		DWORD b0020 : 1;	// 0020
		DWORD b0021 : 1;	// 0021
		DWORD b0022 : 1;	// 0022
		DWORD b0023 : 1;	// 0023
		DWORD b0024 : 1;	// 0024
		DWORD b0025 : 1;	// 0025
		DWORD b0026 : 1;	// 0026
		DWORD b0027 : 1;	// 0027
		DWORD b0028 : 1;	// 0028
		DWORD b0029 : 1;	// 0029
		DWORD b0030 : 1;	// 0030
		DWORD b0031 : 1;	// 0031
	};
} DXY_DATA;	// Digital Input Output

///////////////////////////////////////////////////////////////////////////////
// Input (X0000 - X1031)
typedef union tag_DX_DATA_00 {
	DWORD nValue;
	struct {

		DWORD iLoadCVMZExist1: 1;				// X0000
		DWORD iLoadCVMZExist2: 1;				// X0001
		DWORD iLoadCVMZExist3 : 1;				// X0002
		DWORD iLoadCVMZExist4 : 1;				// X0003
		DWORD iLoadCVMZExist5 : 1;				// X0004
		DWORD i0009 : 1;						// X0005
		DWORD iLoadCVStopperUp : 1;				// X0006
		DWORD iLoadCVStopperDown : 1;			// X0007
		DWORD iMZElevMZExist1 : 1;				// X0008
		DWORD iMZElevMZExist2 : 1;				// X0009
		DWORD iMZElevLoadStopperIn : 1;			// X0010
		DWORD iMZElevLoadStopperOut : 1;		// X0011
		DWORD iMZElevLoadStopperUp : 1;			// X0012
		DWORD iMZElevLoadStopperDown : 1;		// X0013
		DWORD iMZElevUnloadStopperUp : 1;		// X0014
		DWORD iMZElevUnloadStopperDown : 1;		// X0015
		DWORD iUnloadCVMZExist1 : 1;			// X0016
		DWORD iUnloadCVMZExist2 : 1;			// X0017
		DWORD iUnloadCVMZExist3 : 1;			// X0018
		DWORD iUnloadCVMZExist4 : 1;			// X0019
		DWORD iUnloadCVMZExist5 : 1;			// X0020
		DWORD i0021 : 1;						// X0021
		DWORD iUnloadCVStopperUp	: 1;		// X0022
		DWORD iUnloadCVStopperDown	: 1;		// X0023
		DWORD i0024 : 1;						// X0024
		DWORD iMZElevExistLeft : 1;			// X0025 - 임시 부여 
		DWORD iMZElevExistRight : 1;			// X0026 - 임시 부여 
		DWORD i0027 : 1;						// X0027
		DWORD iMZLoadSW1 : 1;					// X0028
		DWORD iMZLoadSW2 : 1;					// X0029
		DWORD iMZUnloadSW1 : 1;					// X0030
		DWORD iMZUnloadSW2 : 1;					// X0031
	};
} DX_DATA_00;	// Digital Input 00

typedef union tag_DX_DATA_01 {
	DWORD nValue;
	struct {
		DWORD iFeederGripOpen :1;			// X0100
		DWORD iFeederGripClose :1;			// X0101
		DWORD iFeederCoatJigCheck : 1;	// X0102
		DWORD i0103 : 1;					// X0103
		DWORD iRailCheckFront : 1;	// X0104
		DWORD iRailCheckRear : 1;		// X0105
		DWORD iMZCoatJigExist : 1;	// X0106
		DWORD i0107 : 1;					// X0107
		DWORD iTrayPickerMasterIn : 1;		// X0108
		DWORD iTrayPickerMasterOut : 1;		// X0109
		DWORD iTrayPickerSlaveIn : 1;		// X0110
		DWORD iTrayPickerSlaveOut : 1;		// X0111
		DWORD iTrayPickerExist : 1;			// X0112
		DWORD iTrayPickerExistEmitter : 1;					// X0113
		DWORD i0114 : 1;					// X0114
		DWORD i0115 : 1;					// X0115
		DWORD iIndexTPosBit0 : 1;		// X0116
		DWORD iIndexTPosBit1 : 1;		// X0117
		DWORD iIndexTPosBit2 : 1;		// X0118
		DWORD i0119 : 1;					// X0119
		DWORD iIndexTInOutAlignIn : 1;					// X0120
		DWORD iIndexTInOutAlignOut : 1;					// X0121
		DWORD iIndexTCleanerAlignIn : 1;		// X0122
		DWORD iIndexTCleanerAlignOut : 1;					// X0123
		DWORD iIndexTTopAlignIn : 1;					// X0124
		DWORD iIndexTTopAlignOut : 1;					// X0125
		DWORD iIndexTEmptyAlignIn : 1;					// X0126
		DWORD iIndexTEmptyAlignOut : 1;					// X0127
		DWORD iIndexTBtmAlignIn : 1;					// X0128
		DWORD iIndexTBtmAlignOut : 1;					// X0129
		DWORD iIndexTMarkAlignIn : 1;					// X0130
		DWORD iIndexTMarkAlignOut : 1;		// X0131
	};
} DX_DATA_01;	// Digital Input 01

typedef union tag_DX_DATA_02 {
	DWORD nValue;
	struct {
		DWORD iLensCleanerDown			: 1;		// X0200
		DWORD iLensCleanerUp			: 1;		// X0201
		DWORD iLensCleanerForward		: 1;		// X0202
		DWORD iLensCleanerBackward		: 1;		// X0203
		DWORD iLensCleanerAirBlow		: 1;		// X0204
		DWORD iLensCleanerSuctionOn		: 1;	    // X0205
		DWORD i0206 : 1;		// X0206
		DWORD i0207 : 1;					// X0207
		DWORD iCapPort1Support1In : 1;		// X0208
		DWORD iCapPort1Support1Out : 1;		// X0209
		DWORD iCapPort1Support2In : 1;		// X0210
		DWORD iCapPort1Support2Out : 1;		// X0211
		DWORD iCapPort1HighCheck : 1;		// X0212
		DWORD i0213 : 1;					// X0213
		DWORD i0214 : 1;					// X0214
		DWORD i0215 : 1;					// X0215
		DWORD iCapPort2SlideLock : 1;		// X0216
		DWORD iCapPort2SlideUnlock : 1;		// X0217
		DWORD iCapPort2SlideClose : 1;		// X0218
		DWORD iCapPort2SlideOpen : 1;		// X0219
		DWORD iCapPort2LowCheck : 1;		// X0220
		DWORD i0221 : 1;					// X0221
		DWORD i0222 : 1;					// X0222
		DWORD i0223 : 1;					// X0223
		DWORD iCapPort2Support1In : 1;		// X0224
		DWORD iCapPort2Support1Out : 1;		// X0225
		DWORD iCapPort2Support2In : 1;		// X0226
		DWORD iCapPort2Support2Out : 1;		// X0227
		DWORD iCapPort2HighCheck : 1;					// X0228
		DWORD i0229 : 1;					// X0229
		DWORD i0230 : 1;					// X0230
		DWORD iCapPortAreaCheck : 1;		// X0231
	};
} DX_DATA_02;	// Digital Input 02

typedef union tag_DX_DATA_03 {
	DWORD nValue;
	struct {
		DWORD iEMGSW1 : 1;			// X0300
		DWORD iEMGSW2 : 1;			// X0301
		DWORD iEMGSW3 : 1;			// X0302
		DWORD iEMGSW4 : 1;			// X0303
		DWORD iMainAir1 : 1;		// X0304
		DWORD i0305 : 1;		// X0305
		DWORD i0306 : 1;		// X0306
		DWORD i0307 : 1;		// X0307
		DWORD i0308 : 1;		// X0308
		DWORD i0309 : 1;		// X0309
		DWORD i0310 : 1;		// X0310
		DWORD i0311 : 1;		// X0311
		DWORD iStartSW : 1;		// X0312
		DWORD i0313 : 1;		// X0313
		DWORD iStopSW : 1;		// X0314
		DWORD i0315 : 1;		// X0315
		DWORD iResetSW : 1;		// X0316
		DWORD i0317 : 1;		// X0317
		DWORD i0318 : 1;		// X0318
		DWORD i0319 : 1;		// X0319
		DWORD iDoorUnlockFront1 : 1;		// X0320
		DWORD iDoorUnlockFront2 : 1;		// X0321
		DWORD iDoorUnlockRight1 : 1;		// X0322
		DWORD iDoorUnlockRight2 : 1;		// X0323
		DWORD iDoorUnlockRear1 : 1;		// X0324
		DWORD iDoorUnlockRear2 : 1;		// X0325
		DWORD iDoorUnlockLeft1 : 1;		// X0326
		DWORD iDoorUnlockLeft2 : 1;		// X0327
		DWORD i0328 : 1;		// X0328
		DWORD i0329 : 1;		// X0329
		DWORD i0330 : 1;		// X0330
		DWORD i0331 : 1;		// X0331
	};
} DX_DATA_03;	// Digital Input 03


///////////////////////////////////////////////////////////////////////////////
// Output (Y0000 - Y1331)
typedef union tag_DY_DATA_00 {
	DWORD nValue;
	struct {
		DWORD oLoadCVCW : 1;				// Y0000
		DWORD oLoadCVCCW : 1;				// Y0001
		DWORD o0002 : 1;					// Y0002
		DWORD o0003 : 1;					// Y0003
		DWORD o0004 : 1;					// Y0004
		DWORD o0005 : 1;					// Y0005
		DWORD oLoadCVStopperUp : 1;			// Y0006
		DWORD oLoadCVStopperDown : 1;		// Y0007
		DWORD oMZElevCVCW : 1;				// Y0008
		DWORD oMZElevCVCCW : 1;				// Y0009
		DWORD oMZElevLoadStopperIn : 1;		// Y0010
		DWORD oMZElevLoadStopperOut : 1;	// Y0011
		DWORD oMZElevLoadStopperUp : 1;		// Y0012
		DWORD oMZElevLoadStopperDown : 1;	// Y0013
		DWORD oMZElevUnloadStopperUp : 1;		// Y0014
		DWORD oMZElevUnloadStopperDown : 1;	// Y0015
		DWORD oUnloadCVCW : 1;				// Y0016
		DWORD oUnloadCVCCW : 1;				// Y0017
		DWORD o0018 : 1;					// Y0018
		DWORD o0019 : 1;					// Y0019
		DWORD o0020 : 1;					// Y0020
		DWORD o0021 : 1;					// Y0021
		DWORD oUnloadCVStopperUp : 1;					// Y0022
		DWORD oUnloadCVStopperDown : 1;					// Y0023
		DWORD o0024 : 1;		// Y0024
		DWORD o0025 : 1;		// Y0025
		DWORD o0026 : 1;					// Y0026
		DWORD o0027 : 1;					// Y0027
		DWORD oMZLoadSW1 : 1;					// Y0028
		DWORD oMZLoadSW2 : 1;					// Y0029
		DWORD oMZUnloadSW1 : 1;					// Y0030
		DWORD oMZUnloadSW2 : 1;					// Y0031
	};
} DY_DATA_00;		// Digital Output 00

typedef union tag_DY_DATA_01 {
	DWORD nValue;
	struct {
		DWORD oFeederGripOpen : 1;		// Y0100
		DWORD oFeederGripClose : 1;	// Y0101
		DWORD o0102 : 1;					// Y0102
		DWORD o0103 : 1;					// Y0103
		DWORD o0104 : 1;					// Y0104
		DWORD o0105 : 1;					// Y0105
		DWORD o0106 : 1;					// Y0106
		DWORD o0107 : 1;					// Y0107
		DWORD oTrayPickerMasterIn : 1;		// Y0108
		DWORD oTrayPickerMasterOut : 1;		// Y0109
		DWORD oTrayPickerSlaveIn : 1;		// Y0110
		DWORD oTrayPickerSlaveOut : 1;		// Y0111
		DWORD o0112 : 1;					// Y0112
		DWORD o0113 : 1;					// Y0113
		DWORD o0114 : 1;					// Y0114
		DWORD o0115 : 1;					// Y0115
		DWORD o0116 : 1;					// Y0116
		DWORD o0117 : 1;					// Y0117
		DWORD o0118 : 1;					// Y0118
		DWORD o0119 : 1;					// Y0119
		DWORD oIndexTInOutAlignIn : 1;		// Y0120
		DWORD oIndexTInOutAlignOut : 1;		// Y0121
		DWORD oIndexTCleanerAlignIn : 1;		// Y0122
		DWORD oIndexTCleanerAlignOut : 1;	// Y0123
		DWORD oIndexTTopAlignIn : 1;			// Y0124
		DWORD oIndexTTopAlignOut : 1;		// Y0125
		DWORD oIndexTEmptyAlignIn : 1;		// Y0126
		DWORD oIndexTEmptyAlignOut : 1;		// Y0127
		DWORD oIndexTBtmAlignIn : 1;			// Y0128
		DWORD oIndexTBtmAlignOut : 1;		// Y0129
		DWORD oIndexTMarkerAlignIn : 1;		// Y0130
		DWORD oIndexTMarkerAlignOut : 1;		// Y0131
	};
} DY_DATA_01;		// Digital Output 01

typedef union tag_DY_DATA_02 {
	DWORD nValue;
	struct {
		DWORD oLensCleannerTopDown :1;		// Y0200
		DWORD oLensCleannerTopUp :1;		// Y0201
		DWORD oLensCleannerTopForward :1;					// Y0202
		DWORD oLensCleannerTopBackward :1;					// Y0203
		DWORD oLensCleannerTopBlow :1;					// Y0204
		DWORD oLensCleannerTopSuction :		1;					// Y0205
		DWORD o0206 : 1;					// Y0206
		DWORD o0207 : 1;					// Y0207
		DWORD oLensCleannerBtmDown : 1;		// Y0208
		DWORD oLensCleannerBtmUp : 1;		// Y0209
		DWORD oLensCleannerBtmForward : 1;					// Y0210
		DWORD oLensCleannerBtmBackward : 1;					// Y0211
		DWORD oLensCleannerBtmBlow : 1;					// Y0212
		DWORD oLensCleannerBtmSuction : 1;					// Y0213
		DWORD o0214 : 1;					// Y0214
		DWORD o0215 : 1;					// Y0215
		DWORD o0216 : 1;					// Y0216
		DWORD o0217 : 1;					// Y0217
		DWORD o0218 : 1;					// Y0218
		DWORD o0219 : 1;					// Y0219
		DWORD o0220 : 1;					// Y0220
		DWORD o0221 : 1;					// Y0221
		DWORD o0222 : 1;					// Y0222
		DWORD o0223 : 1;					// Y0223
		DWORD o0224 : 1;					// Y0224
		DWORD o0225 : 1;					// Y0225
		DWORD o0226 : 1;					// Y0226
		DWORD o0227 : 1;					// Y0227
		DWORD o0228 : 1;					// Y0228
		DWORD o0229 : 1;					// Y0229
		DWORD o0230 : 1;					// Y0230
		DWORD o0231 : 1;					// Y0231
	};
} DY_DATA_02;		// Digital Output 02

typedef union tag_DY_DATA_03 {
	DWORD nValue;
	struct {
		DWORD oTowerGreen : 1;	// Y0300
		DWORD oTowerYellow : 1;	// Y0301
		DWORD oTowerRed : 1;					// Y0302
		DWORD oBuzzerBit0 : 1;					// Y0303
		DWORD oBuzzerBit1 : 1;					// Y0304
		DWORD oBuzzerBit2 : 1;					// Y0305
		DWORD oBuzzerBit3 : 1;					// Y0306
		DWORD oBuzzerBit4 : 1;					// Y0307
		DWORD oInsideLight : 1;				// Y0308
		DWORD oSafetyReset : 1;				// Y0309
		DWORD oModeSelect : 1;					// Y0310
		DWORD o0311 : 1;					// Y0311
		DWORD oStartLampGreenFront : 1;					// Y0312
		DWORD oStartLampGreenRear : 1;					// Y0313
		DWORD oStopLampRedFront : 1;					// Y0314
		DWORD oStopLampRedRear : 1;					// Y0315
		DWORD oResetLampYellowFront : 1;	// Y0316
		DWORD oResetLampYellowRear : 1;	// Y0317
		DWORD o0318 : 1;					// Y0318
		DWORD o0319 : 1;					// Y0319
		DWORD oDoor01UnlockFront1 : 1;					// Y0320
		DWORD oDoor01UnlockFront2 : 1;					// Y0321
		DWORD oDoor01UnlockRight1 : 1;					// Y0322
		DWORD oDoor01UnlockRight2 : 1;					// Y0323
		DWORD oDoor01UnlockRear1 : 1;	// Y0324
		DWORD oDoor01UnlockRear2 : 1;	// Y0325
		DWORD oDoor01UnlockLeft1 : 1;					// Y0326
		DWORD oDoor01UnlockLeft2 : 1;					// Y0327
		DWORD o0328 : 1;					// Y0328
		DWORD o0329 : 1;					// Y0329
		DWORD o0330 : 1;					// Y0330
		DWORD o0331 : 1;					// Y0331
	};
} DY_DATA_03;		// Digital Output 03

///////////////////////////////////////////////////////////////////////////////
