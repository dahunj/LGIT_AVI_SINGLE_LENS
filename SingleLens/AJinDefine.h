///////////////////////////////////////////////////////////////////////////////
// AJinDefine.h : AJin Structure
#pragma once

///////////////////////////////////////////////////////////////////////////////
// Motion Axis
const int AXIS_COUNT = 15;		// Motion Module


const int AX_MZ_ELEVATOR_Z			= 0;
const int AX_ZIG_FEEDER_X			= 1;
const int AX_ZIG_FEEDER_Y			= 2;
const int AX_ZIG_PICKER_Y		= 3;
const int AX_ZIG_PICKER_Z		= 4;
const int AX_TOP_INSPECTOR_X	= 5;
const int AX_TOP_INSPECTOR_Y	= 6;
const int AX_TOP_INSPECTOR_Z	= 7;
const int AX_BTM_INSPECTOR_X	= 8;
const int AX_BTM_INSPECTOR_Y	= 9;
const int AX_BTM_INSPECTOR_Z	= 10;
const int AX_MARK_UNIT_X			= 11;
const int AX_MARK_UNIT_Y			= 12;
const int AX_MARK_UNIT_Z			= 13;	
const int AX_MAIN_INDEX_R		= 14;





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

		DWORD iLdCVMZExist1R: 1;				// X0000
		DWORD iLdCVMZExist2: 1;				// X0001
		DWORD iLdCVMZExist3 : 1;				// X0002
		DWORD iLdCVMZExist4 : 1;				// X0003
		DWORD iLdCVMZExist5 : 1;				// X0004
		DWORD i0005 : 1;						// X0005
		DWORD i0006 : 1;				// X0006
		DWORD i0007 : 1;			// X0007
		DWORD iLdCVStpr1UpR : 1;				// X0008
		DWORD iLdCVStpr1Dn : 1;				// X0009
		DWORD iLdCVLift2Up : 1;			// X0010
		DWORD iLdCVLift2Dn : 1;		// X0011
		DWORD i0012 : 1;			// X0012
		DWORD i0013 : 1;		// X0013
		DWORD i0014 : 1;		// X0014
		DWORD i0015 : 1;		// X0015
		DWORD iElvMZExist1 : 1;			// X0016
		DWORD i0017 : 1;			// X0017
		DWORD iElvLift1UpL : 1;			// X0018
		DWORD iElvLift1Dn : 1;			// X0019
		DWORD iElvLift1In : 1;			// X0020
		DWORD iElvLift1Out : 1;						// X0021
		DWORD i0022	: 1;		// X0022
		DWORD i0023	: 1;		// X0023
		DWORD iElvMZExist2		: 1;						// X0024
		DWORD i0025					: 1;			// X0025 - 임시 부여 
		DWORD iElvLift2UpR		: 1;				// X0026 - 임시 부여 
		DWORD iElvLift2Dn	: 1;				// X0027
		DWORD iElvLift2In		: 1;				// X0028
		DWORD iElvLift2Out	: 1;				// X0029
		DWORD i0030 : 1;					// X0030
		DWORD i0031 : 1;					// X0031
	};
} DX_DATA_00;	// Digital Input 00

typedef union tag_DX_DATA_01 {
	DWORD nValue;
	struct {
		DWORD iUldCvMZExist1L :1;			// X0100
		DWORD iUldCvMZExist2 :1;			// X0101
		DWORD iUldCvMZExist3 : 1;		// X0102
		DWORD iUldCvMZExist4 : 1;		// X0103
		DWORD i0104 : 1;					// X0104
		DWORD i0105 : 1;					// X0105
		DWORD iUldCvStprUp : 1;		// X0106
		DWORD iUldCvStprDn : 1;		// X0107
		DWORD iFeederGripOpen : 1;			// X0108
		DWORD iFeederGripClose : 1;			// X0109
		DWORD iFeederZigExist : 1;			// X0110
		DWORD iFeederZigExistEmit : 1;					// X0111
		DWORD iMagazineZigExist : 1;		// X0112
		DWORD iRailZigExist : 1;			// X0113
		DWORD iRailZigAlignIn : 1;		// X0114
		DWORD iRailZigAlignOut : 1;		// X0115
		DWORD iZigPickerMasterIn : 1;		// X0116
		DWORD iZigPickerMasterOut : 1;		// X0117
		DWORD iZigPickerSlaveIn : 1;		// X0118
		DWORD iZigPickerSlaveOut : 1;		// X0119
		DWORD iZigPickerExist : 1;			// X0120
		DWORD i0121 : 1;					// X0121
		DWORD i0122 : 1;					// X0122
		DWORD i0123 : 1;					// X0123
		DWORD i0124 : 1;					// X0124
		DWORD i0125 : 1;					// X0125
		DWORD i0126 : 1;					// X0126
		DWORD i0127 : 1;					// X0127
		DWORD i0128 : 1;					// X0128
		DWORD i0129 : 1;					// X0129
		DWORD i0130 : 1;					// X0130
		DWORD i0131 : 1;					// X0131
	};
} DX_DATA_01;	// Digital Input 01

typedef union tag_DX_DATA_02 {
	DWORD nValue;
	struct {
		DWORD iIndexPosBit0			: 1;		// X0200
		DWORD iIndexPosBit1 			: 1;		// X0201
		DWORD iIndexPosBit2		: 1;		// X0202
		DWORD i0203		: 1;		// X0203
		DWORD iMainIndexZigAlignOut		: 1;		// X0204
		DWORD iMainIndexZigAlignIn		: 1;	    // X0205
		DWORD iIndexTZigExist : 1;		// X0206
		DWORD i0207 : 1;					// X0207
		DWORD iCleanerTopDn : 1;			// X0208
		DWORD iCleanerTopUp : 1;			// X0209
		DWORD iCleanerTopFwd : 1;		// X0210
		DWORD iCleanerTopBwd : 1;		// X0211
		DWORD i0212 : 1;		// X0212
		DWORD i0213 : 1;					// X0213
		DWORD i0214 : 1;					// X0214
		DWORD i0215 : 1;					// X0215
		DWORD iCleanerBtmUp : 1;			// X0216
		DWORD iCleanerBtmDn : 1;			// X0217
		DWORD iCleanerBtmFwd : 1;		// X0218
		DWORD iCleanerBtmBwd : 1;		// X0219
		DWORD i0220 : 1;		// X0220
		DWORD i0221 : 1;					// X0221
		DWORD i0222 : 1;					// X0222
		DWORD i0223 : 1;					// X0223
		DWORD IMarkPenDown : 1;		// X0224
		DWORD IMarkPenUp : 1;		// X0225
		DWORD IMarkPenExist : 1;		// X0226
		DWORD i0227 : 1;		// X0227
		DWORD i0228 : 1;					// X0228
		DWORD i0229 : 1;					// X0229
		DWORD i0230 : 1;					// X0230
		DWORD i0231 : 1;		// X0231
	};
} DX_DATA_02;	// Digital Input 02

typedef union tag_DX_DATA_03 {
	DWORD nValue;
	struct {
		DWORD iEmgSw1 : 1;			// X0300
		DWORD iEmgSw2 : 1;			// X0301
		DWORD iEmgSw3 : 1;			// X0302
		DWORD iEmgSw4 : 1;			// X0303
		DWORD iMainAir1 : 1;		// X0304
		DWORD i0305 : 1;			// X0305
		DWORD i0306 : 1;			// X0306
		DWORD i0307 : 1;			// X0307
		DWORD i0308 : 1;			// X0308
		DWORD i0309 : 1;			// X0309
		DWORD i0310 : 1;			// X0310
		DWORD i0311 : 1;			// X0311
		DWORD iStartSw : 1;			// X0312
		DWORD i0313 : 1;			// X0313
		DWORD iStopSw : 1;			// X0314
		DWORD i0315 : 1;			// X0315
		DWORD iResetSw : 1;			// X0316
		DWORD i0317 : 1;			// X0317
		DWORD iLoadOpenSw : 1;	// X0318				//배선 이슈로 자리 바꿈 
		DWORD iLoadRunSw : 1;		// X0319
		DWORD iUnloadOpenSw : 1;		// X0320 iUnloadOpenSw
		DWORD iUnloadRunSw : 1;		// X0321 iUnloadRunSw
		DWORD iDoor01Unlock : 1;	// X0322
		DWORD iDoor02Unlock : 1;	// X0323
		DWORD iDoor03Unlock : 1;		// X0324
		DWORD iDoor04Unlock : 1;		// X0325
		DWORD iDoor05Unlock : 1;		// X0326
		DWORD iDoor06Unlock : 1;		// X0327
		DWORD iDoor07Unlock : 1;				// X0328
		DWORD iDoor08Unlock : 1;				// X0329
		DWORD i0330 : 1;				// X0330
		DWORD i0331 : 1;				// X0331
	};
} DX_DATA_03;	// Digital Input 03


///////////////////////////////////////////////////////////////////////////////
// Output (Y0000 - Y1331)
typedef union tag_DY_DATA_00 {
	DWORD nValue;
	struct {
		DWORD oLoadCVRun : 1;				// Y0000
		DWORD oLoadCVDirCCW : 1;			// Y0001
		DWORD o0002 : 1;					// Y0002
		DWORD o0003 : 1;					// Y0003
		DWORD o0004 : 1;					// Y0004
		DWORD o0005 : 1;					// Y0005
		DWORD o0006 : 1;			// Y0006
		DWORD o0007 : 1;		// Y0007
		DWORD oLdCVStpr1UpR : 1;				// Y0008
		DWORD oLdCVStpr1Dn : 1;				// Y0009
		DWORD oLdCVStpr2Up : 1;		// Y0010
		DWORD oLdCVStpr2Dn : 1;	// Y0011
		DWORD o0012 : 1;		// Y0012
		DWORD o0013 : 1;	// Y0013
		DWORD o0014 : 1;		// Y0014
		DWORD o0015 : 1;	// Y0015
		DWORD oElvCvRun : 1;				// Y0016
		DWORD oElvCvDirCCW : 1;				// Y0017
		DWORD oElvStpr1UpL : 1;					// Y0018
		DWORD oElvStpr1Dn : 1;					// Y0019
		DWORD oElvStpr1In : 1;					// Y0020
		DWORD oElvStpr1Out : 1;					// Y0021
		DWORD o0022 : 1;					// Y0022
		DWORD o0023 : 1;					// Y0023
		DWORD o0024 : 1;		// Y0024
		DWORD o0025 : 1;		// Y0025
		DWORD oElvStpr2UpR : 1;				// Y0026
		DWORD oElvStpr2Dn : 1;				// Y0027
		DWORD oElvStpr2In : 1;					// Y0028
		DWORD oElvStpr2Out : 1;					// Y0029
		DWORD o0030 : 1;					// Y0030
		DWORD o0031 : 1;					// Y0031
	};
} DY_DATA_00;		// Digital Output 00

typedef union tag_DY_DATA_01 {
	DWORD nValue;
	struct {
		DWORD oUldCvRun : 1;							// Y0100
		DWORD oUldCvDirCCW : 1;						// Y0101
		DWORD o0102 : 1;								// Y0102
		DWORD o0103 : 1;								// Y0103
		DWORD o0104 : 1;								// Y0104
		DWORD o0105 : 1;								// Y0105
		DWORD oUldCvStprUp : 1;					// Y0106
		DWORD oUldCvStprDn : 1;					// Y0107
		DWORD oFeederGripOpen : 1;						// Y0108
		DWORD oFeederGripClose : 1;						// Y0109
		DWORD o0110	: 1;								// Y0110
		DWORD o0111	: 1;								// Y0111
		DWORD o0112 : 1;								// Y0112
		DWORD o0113 : 1;								// Y0113
		DWORD oRailZigAlignIn : 1;					// Y0114
		DWORD oRailZigAlignOut : 1;					// Y0115
		DWORD oZigPickerMasterIn : 1;					// Y0116
		DWORD oZigPickerMasterOut : 1;					// Y0117
		DWORD oZigPickerSlaveIn : 1;					// Y0118
		DWORD oZigPickerSlaveOut : 1;					// Y0119
		DWORD o0120 : 1;								// Y0120
		DWORD o0121 : 1;								// Y0121
		DWORD o0122 : 1;								// Y0122
		DWORD o0123 : 1;								// Y0123
		DWORD o0124 : 1;								// Y0124
		DWORD o0125 : 1;								// Y0125
		DWORD o0126 : 1;								// Y0126
		DWORD o0127 : 1;								// Y0127
		DWORD o0128 : 1;								// Y0128
		DWORD o0129 : 1;								// Y0129
		DWORD o0130 : 1;								// Y0130
		DWORD o0131 : 1;								// Y0131
	};
} DY_DATA_01;		// Digital Output 01

typedef union tag_DY_DATA_02 {
	DWORD nValue;
	struct {
		DWORD o0200 : 1;							// Y0200
		DWORD o0201: 1;					// Y0201
		DWORD o0202: 1;									// Y0202
		DWORD o0203: 1;									// Y0203
		DWORD oMainIndexZigAlignOut: 1;								// Y0204
		DWORD oMainIndexZigAlignIn : 1;									// Y0205
		DWORD o0206 : 1;											// Y0206
		DWORD o0207 : 1;											// Y0207
		DWORD oCleanerTopDn : 1;								// Y0208
		DWORD oCleanerTopUp : 1;								// Y0209
		DWORD oCleanerTopFwd : 1;											// Y0210
		DWORD oCleanerTopBwd : 1;											// Y0211
		DWORD oCleanerTopBlow : 1;											// Y0212
		DWORD oCleanerTopBlowOff : 1;											// Y0213
		DWORD o0214 : 1;					// Y0214
		DWORD o0215 : 1;					// Y0215
		DWORD oCleanerBtmUp :1;						// Y0216
		DWORD oCleanerBtmDn :1;						// Y0217
		DWORD oCleanerBtmFwd :1;					// Y0218
		DWORD oCleanerBtmBwd :1;					// Y0219
		DWORD oCleanerBtmBlowOn :1;						// Y0220
		DWORD oCleanerBtmBlowOff :	1;					// Y0221
		DWORD o0222 : 1;					// Y0222
		DWORD o0223 : 1;					// Y0223
		DWORD oMarkPenDown : 1;					// Y0224
		DWORD oMarkPenUp : 1;					// Y0225
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
		DWORD oDustPowerOn : 1;					// Y0311
		DWORD oStartLamp1: 1;					// Y0312
		DWORD oStartLamp2 : 1;					// Y0313
		DWORD oStopLamp1: 1;					// Y0314
		DWORD oStopLamp2 : 1;					// Y0315
		DWORD oResetLamp1 : 1;	// Y0316
		DWORD oResetLamp2 : 1;	// Y0317
		DWORD oLdOpenLamp   : 1;					// Y0318
		DWORD oLdRunLamp    : 1;					// Y0319
		DWORD oUldOpenLamp  : 1;								// Y0320
		DWORD oUldRunLamp    : 1;								// Y0321
		DWORD oDoor01Unlock : 1;						// Y0322
		DWORD oDoor02Unlock : 1;						// Y0323
		DWORD oDoor03Unlock : 1;						// Y0324
		DWORD oDoor04Unlock : 1;						// Y0325
		DWORD oDoor05Unlock : 1;						// Y0326
		DWORD oDoor06Unlock : 1;						// Y0327
		DWORD oDoor07Unlock : 1;						// Y0328
		DWORD oDoor08Unlock : 1;						// Y0329
		DWORD o0330 : 1;					// Y0330
		DWORD o0331 : 1;					// Y0331
	};
} DY_DATA_03;		// Digital Output 03

///////////////////////////////////////////////////////////////////////////////
