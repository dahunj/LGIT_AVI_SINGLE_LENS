// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.
#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.

#include <afxdisp.h>        // MFC 자동화 클래스입니다.

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

///////////////////////////////////////////////////////////////////////////////

// Library Add
#include "CSControls.h"
#include "CSIniFile.h" 
#include "CSComPort.h"
#include "CSUdpSocket.h"
#include "CSClientSocket.h"
#include "CSGrid.h"

#include "DataEnums.h"

#include <math.h>
#include <iostream>
#include <vector>

#include <dbghelp.h>
#include <stdio.h>
#include <time.h>
#pragma comment(lib, "Dbghelp.lib")

#ifdef _DEBUG
	#pragma comment(lib, "CSControlsD.lib")
	#pragma comment(lib, "CSIniFileD.lib")
	#pragma comment(lib, "CSComPortD.lib")
	#pragma comment(lib, "CSUdpSocketD.lib")
	#pragma comment(lib, "CSClientSocketD.lib")
	#pragma comment(lib, "CSGridD.lib")
#else
	#pragma comment(lib, "CSControlsR.lib")
	#pragma comment(lib, "CSIniFileR.lib")
	#pragma comment(lib, "CSComPortR.lib")
	#pragma comment(lib, "CSUdpSocketR.lib")
	#pragma comment(lib, "CSClientSocketR.lib")
	#pragma comment(lib, "CSGridR.lib")
#endif

#define MAIN_VERSION	_T("V 0.0.0.1b")
//
//#define AJIN_BOARD_USE
//#define LOT_BARCODE_USE
//#define LOAD_CELL_USE

// 테스트 런 옵션
//#define DRY_RUN_TEST		// Dry Run Test 시 사용

// #define BARCODE_CHECK   	// Cap/Ship Barcode Check

#define SIM_WAITTIMES	 1		//
#define SIM_WAITTIMEM	 1		//
#define	VELOCITY_WEIGHT	 8

//Magazine Slot MAX Number 
const int SLOT_NO_MAX = 10;

const int ZIG_MAX = 500;

//Zig X-Y
const int ZIG_X = 4, ZIG_Y = 8;

///////////////////////////////////////////////////////////////////////////////

extern CString gsCurrentDir;	// 현재 프로젝트 폴더

typedef struct
{
	//new 
	int		nTime[10]; //LoopTime Set Value 

	int     nStatus;
	int		nLanguage;

	int		nMZCnt;
	int		nLensUseCnt[60];
	int		nLensMaxCnt;
	
	BOOL	bIndexDone[6]; //0: Load , 1: Clean, 2: Top, 3:empty, 4:btm, 5: Mark
	
	int		nZigX;
	int		nZigY;

	// Infomation 
	int InfoMagazine[10][ZIG_X][ZIG_Y];
	int InfoFeeder[ZIG_X][ZIG_Y];
	int	InfoZigPick[ZIG_X][ZIG_Y];
	int InfoMainIndex[6][ZIG_X][ZIG_Y]; // 0:Empty,1:Good, 2:NG, 3:Top Ready, 4: Top Done, 5: Btm Ready, 6 : Btm Done,  9:Init 
	
	std::vector<int> nInfoMark[ZIG_X][ZIG_Y];

	int nInfoMZLoad[10];
	int nInfoMZUnload[10];

	BOOL	bDryRunMode;
	int		nSpeedOption; // 여러개의 속도 옵션 가지게 바꾸고 싶다. 
	
	CString	sOperID;		// Operator
	CString	sRecipe;		// Recipe Item
	CString	sZigID[60];


	CString	sMZIDElev;
	CString	sZigIDElev;
	int		nSlotNoElev;
	
		
	CString	sMZIDTrayPick;
	CString	sZigIDTrayPick;
	int		nSlotNoTrayPick;
	
	CString	sMZIDLoad;
	CString	sZigIDLoad;
	int		nSlotNoLoad;

	CString	sMZIDCleaner;
	CString	sZigIDCleaner;
	int		nSlotNoCleaner;

	CString	sMZIDTop;
	CString	sZigIDTop;
	int		nSlotNoTop;

	CString	sMZIDBtm;
	CString	sZigIDBtm;
	int		nSlotNoBtm;

	CString	sMZIDMark;
	CString	sZigIDMark;
	int		nSlotNoMark;


	int		nScanReqTop;
	int		nScanReqBtm;
	
	BOOL    bScanDone[2];            // 0:Top 1: Btm


	char	cJudgeCode[10][ZIG_X*ZIG_Y][2];	
	int     nInspectInfo[10][ZIG_X*ZIG_Y];    // ????? (0:Empty, 1:Good, 2:NG, 3:NoResult, 7:Request, 8:NG, 9:Init)
	BYTE	byInspectDone[10][ZIG_X*ZIG_Y];	// 검사완료 (2bit 사용 ==> 0:T1, 1:Btm1)

	//0: Rignt, 1 : Left,  판정코드 (0:Top, 1:Btm)
	
	BOOL    bCycleStop;                // Run 
	BOOL    bFirstLotStart;
	BOOL    bLotEndBeep;     

	
	DWORD    dwMStopStartTime;        // ????? ???? ???, Stop ???or????? ?????? ??? ???????? 
	DWORD    dwMStopEndTime;
	DWORD    dwMStopProcTime;

	CString sAlarmTime[3];
	CString sAlarmList[3];

	CString    sComName;
	int        nDoorLockTime;
	DWORD    dwDoorStartTime;

	BOOL	bLoadOpenSW;	// LED Switch below doors of machine  
	BOOL	bUnloadOpenSW;
	
} GLOVAL_DATA;


typedef struct 
{
	CString sLotID[60];

	int nMZRunningCnt;

	int nLensCnt[60];
	int	nLotStatus[60];	//0:Wait, 1, 2:Run, 3:Lot_End

	BOOL bEmptyLot[60];




	///////////old 

	
	CString sStartTime[2];
	CString sEndTime[2];
	DWORD	dwLotStart[2];
	DWORD	dwLotEnd[2];
	int		nTrayCount[2];
	int		nCmCount[2];
	double  dTackTime;
	int		nGoodCount[2];
	int		nNgCount[2];
	int		nCapFailCount[2];			// Cap Tilt Error Count

	int		nCapCount[2];

	int		nErrorCount;
	DWORD	dwRunTime;
	DWORD	dwStopTime;
	DWORD	dwErrorTime;

	BOOL	bLotEndComplete[2];

	double	dAverageCycle[15][2][20];

	DWORD	dwTaktData[4];	// 0:Load, 1:Assembly, 2:Unload, 3:Index
	BOOL	bTaktDone[3];	// 0:Load, 1:Assembly, 2:Unload

} GLOVAL_LOT;

typedef struct {
	BOOL	bBegin;
	CString	sLotID;
	int		nAlmNo;
	CString sAlmMsg;
	CString sStartTime;
	CString sEndTime;
	DWORD	dwStartTime;
	DWORD	dwEndTime;
	DWORD	dwProcTime;

	double  dMotionChkPos;
	double  dMotionPos[35];


} GLOVAL_ALM;

typedef struct {
	double  dTaktTime;
	double	dTakt[24][50];	// 시간당 각 Lot의 Takt (시간당 최대 50개)
	int		nLotCount[24];	// 시간당 Lot 수량 (0~23)
	int		nCmCount[2];	// 주간(0:7~19h), 야간(1:19~7h)
} GLOVAL_UPH;

typedef struct {
	int		nLotStatus;				// 0:Stop, 1:Start Send, 2:Start Receive
	DWORD	dwLotStartTime;			// Lot Start time

	// Host 전공정 Data
	CString		sHostLotID;			//Host 수신 Lot ID
	CString		sHostRecipe;		//Host 수신 Recipe ID
	CString		sHostModel;			//Host 수신 Recipe ID
	int			nHostCount;			//Host 수신 CM 총갯수
	CString		sHostCancelCode;	//Host Cancel 수신 code
	CString		sHostCancelText;	//Host Cancel 수신 내용

	// 장비 실적 Data	// LJH Port별로 관리해야할지 정해야한다.
	CString		sBarID[2][50][12];		//Barcode ID(장비) [50]:Tray, [12]:Pocket
	CString		sJudge[2][50][12];		//N:NG, H:Special NG, M:성능불량(MES NG)
	CString		sNGCode[2][50][12];		//대표NG Code
} GLOVAL_MES;

typedef struct{
	int		nType;			//nType:1[정시], 2[해제] 3[설정]
	int		nWriteHH;		//등록시간
	int		nOpenStart;		//1:Start, Open Start 했는지 안했는지 
	DWORD	dwOpenStartTime;
	int		nOpenTime;
	BOOL	bFirst; // 처음 프로그램 켜질때 

	CString sCurrTime;
	int		nTimeYYYY;
	int		nTimeMM;
	int		nTimeDD;
	int		nTimeHH;
	double	dTime;
	double	dPer;
}GLOBAL_DOORLOCK;



typedef struct {
	int			nCapCount;
	CString		sCapPart[20];
	int			nShipCount;
	CString		sShipPart[20];
} GLOVAL_PART;


extern GLOVAL_DATA	gData;
extern GLOVAL_LOT	gLot;
extern GLOVAL_ALM	gAlm;
extern GLOVAL_UPH	gUph;
extern GLOVAL_MES	gMes;
extern GLOBAL_DOORLOCK gDoorLock;
extern GLOVAL_PART		gPart;




