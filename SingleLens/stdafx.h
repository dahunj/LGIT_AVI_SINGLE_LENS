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
#include "CSServerSocket.h"

#include "EnumData.h"
#include "EnumMoveData.h"
#include "EnumIO.h"

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
	#pragma comment(lib, "CSServerSocketD.lib")
	#pragma comment(lib, "CSGridD.lib")
#else
	#pragma comment(lib, "CSControlsR.lib")
	#pragma comment(lib, "CSIniFileR.lib")
	#pragma comment(lib, "CSComPortR.lib")
	#pragma comment(lib, "CSUdpSocketR.lib")
	#pragma comment(lib, "CSClientSocketR.lib")
	#pragma comment(lib, "CSServerSocketR.lib")
	#pragma comment(lib, "CSGridR.lib")
#endif

#define MAIN_VERSION	_T("V 0.0.1.6b")


//---------------------------------
//#define AJIN_BOARD_USE



#define SIM_WAITTIMES	 1		//
#define SIM_WAITTIMEM	 1		//
#define	VELOCITY_WEIGHT	 5

#define MES_WAITTIME	10000

//Magazine Slot MAX Number 
const int SLOT_NO_MAX = 10;

//Zig X-Y
const int ZIG_X = 40, ZIG_Y = 20; // MAX

///////////////////////////////////////////////////////////////////////////////

extern CString gsCurrentDir;	// 현재 프로젝트 폴더

typedef struct
{
	CString	sOperID;		// Operator
		
	CString	sMZID[7];
	CString	sZigID[7][10];	
	

	//비전 요청으로 1~3까지만 운용, 4~7 나머지는 버퍼로 남겨둔다
	int		nMZNo[7]; // From UI MZ Input 
	int		nMZCnt;

	int		nCtZigTotalCnt[7];
	int		nLensTotalCnt[7];
	int		nLensUseCnt[7][10];
	int		nLensMaxCnt;

	int		nLoadTrayCnt[7];
	int		nUnloadTrayCnt[7];
	
	int		nLTime[10];	 //LoopTime Set Value 

	int     nStatus;
	int		nLanguage;

	int		nTNoPick[2];	//0: Load, 1: Ready
		
	int		nLensCntX;
	int		nLensCntY;

	// Info Processing

	// Lens State 
	// 0:Empty,1:Good, 2:NG, 3:Top Ready, 4: Top Done, 5: Btm Ready, 6 : Btm Done,  9:Init
	int InfoMZLoad[10][ZIG_X][ZIG_Y];
	int InfoMZReady[10][ZIG_X][ZIG_Y];
	int InfoFeeder[ZIG_X][ZIG_Y];
	int InfoRail[ZIG_X][ZIG_Y];			//if needed 
	int	InfoZigPick[ZIG_X][ZIG_Y];
	int InfoMainIndex[7][ZIG_X][ZIG_Y]; //0: Load , 1: Clean, 2: Top, 3:empty, 4:btm, 5: Mark, 6: Unload 
	int InfoMZUnload[10][ZIG_X][ZIG_Y];

	int	InfoCtZigLoad[10];
	int	InfoCtZigRdy[10];
	int	InfoCtZigUnload[10];

	int nMZNoMZLoad[10];
	int nMZNoMZRdy[10];
	int nMZNoFeeder;
	int nMZNoRail;
	int nMZNoTrayPicker;
	int nMZNoMainIndex[7];
	int nMZNoMZUnload[10];	
	
	BOOL	ZigMap[3][10];
	int		LensMap[3][10][ZIG_X][ZIG_Y];	
		
	//Coating Zig 10장 
	CString	sLotIDElevLoad[10];
	CString	sMZIDElevLoad[10];
	CString	sZigIDElevLoad[10];
	CString	sRecipeElevLoad[10];


	CString	sLotIDElevRdy[10];
	CString	sMZIDElevReady[10];
	CString	sZigIDElevReady[10];
	CString	sRecipeElevReady[10];
	
	
	CString	sLotIDElevUnload;
	CString	sMZIDElevUnload;
	CString	sZigIDElevUnload[10];
	CString sRecipeElevUnload[10];
	int		nTablePocketElevUnload[10];
	

	CString	sLotIDFeeder;
	CString	sMZIDFeeder;
	CString	sZigIDFeeder;
	CString sRecipeFeeder;
	int		nSlotNoFeeder;	
	int		nTablePocketFeeder;

	CString sLotIDRail;
	CString	sMZIDRail;
	CString	sZigIDRail;
	CString	sRecipeRail;
	int		nSlotNoRail;
	int		nTablePocketRail;
		
	CString	sLotIDTrayPick;
	CString	sMZIDTrayPick;
	CString	sZigIDTrayPick;
	CString	sRecipeTrayPick;
	int		nSlotNoTrayPick;
	int		nTablePocketTrayPick;
	
	//Main Index Pocket 6개 + Unload 1개 
	CString	sLotIDMainIndex[7];
	CString	sMZIDMainIdex[7];
	CString	sZigIDMainIndex[7];
	CString sRecipeMainIndex[7];
	int		nSlotNoMainIndex[7];
	int		nTablePocketMainIndex[7];

	int		nScanReqTop;
	int		nScanReqBtm;
	
	BOOL    bScanDone[2];            // 0:Top 1: Btm
	BOOL	bReload[2];

	char	cJudgeCode[7][10][ZIG_X*ZIG_Y][2];
	CString	sJudgeCode[7][10][ZIG_X*ZIG_Y][3]; // 0:Top 1: Btm , 2: Top Priority  
	CString sNGCode[7][10][ZIG_X*ZIG_Y][3];
	int     nInspectInfo[7][10][ZIG_X*ZIG_Y];    // ????? (0:Empty, 1:Good, 2:NG, 3:NoResult, 7:Request, 8:NG, 9:Init)
	BYTE	byInspectDone[7][10][ZIG_X*ZIG_Y];	// 검사완료 (2bit 사용 ==> 0:T1, 1:Btm1)

	//0: Rignt, 1 : Left,  판정코드 (0:Top, 1:Btm)
	
	BOOL    bCycleStop;                // Run 
	BOOL    bFirstLotStart;
	BOOL    bLotEndBeep;     
		
	DWORD    dwMStopStartTime;        // ????? ???? ???, Stop ???or????? ?????? ??? ???????? 
	DWORD    dwMStopEndTime;
	DWORD    dwMStopProcTime;

	CString		sAlarmTime[3];
	CString		sAlarmList[3];

	CString    sComName;
	int        nDoorLockTime;
	DWORD    dwDoorStartTime;

	BOOL	bLoadOpenSW;	// LED Switch below doors of machine  
	BOOL	bUnloadOpenSW;
	
	BOOL	bIndexDone[7]; 

	int		nIndexPos;

	BOOL	bElvLoadWait;
	BOOL	bElvUnloadWait;
	BOOL	bElvSlideOverWait;
	BOOL	bFeederWorkWait;		
	
	BOOL	bLdMZWait;
	BOOL	bUldMZWait;
		
	BOOL	bAgingMode;
	BOOL	bSimulMode;
	int		nSpeedOption; // 여러개의 속도 옵션 가지게 바꾸고 싶다. 


	CString sStdMotionFile;
	CString sEfficiencyFile;
	int		nStdEqNo;	// Log 표준화 (설비번호)
	int		nStdLotNo;	// Log 표준화 (하루 기준으로 작업한 Lot 번호)
	int		nStdLogDay;	// Log 표준화 (작업일)

	int		nSelectNo;

	double  dDeltaX[7];
	double  dDeltaY[7];

	DWORD	dwInspectWait;

	int		nTowerState;

} GLOVAL_DATA;


typedef struct 
{
	CString sLotID[7];

	int nMZRunningCnt;

	int nLensCnt[60];
	int	nLotStatus[7];	//0:Wait, 1, 2:Run, 3:Lot_End
			
	///////////old 	
	CString sStartTime[7]; // 동시에 7개 매거진 돌 수 있나? 
	CString sEndTime[7];
	DWORD	dwLotStart[7];
	DWORD	dwLotEnd[7];	
	
	int		nTrayCount[7];
	int		nLensCount[7];
	DWORD	dwFirstUnloadTray[7];
	
	double  dTackTime_Unload;
	double  dTactTime_RunTime;
	double  dTactTime_StoETime; //Start to End 

	int		nGoodCount[7];
	int		nNgCount[7];

	int		nErrorCount[7];

	DWORD	dwStopTime[7];
	DWORD	dwErrorTime;

	DWORD	dwTime_StoE[7];
	DWORD	dwTime_RunTime[7];
	DWORD	dwTime_Unload[7];

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
	int		nLensCount[2];	// 주간(0:7~19h), 야간(1:19~7h)
} GLOVAL_UPH;

typedef struct {
	
	BOOL		bMGZIDReported;
	BOOL		bPPConfirm;
	BOOL		bTrayIDConfirm;
	
	CString		sLotID[2];
	CString		sMGZID[2]; // 0: Load, 1: Ready 

	DWORD	dwMesTime;
	
	DWORD	dwLotStartTime;			// Lot Start time

	// Host 전공정 Data
	int			nElevPos;			

	CString		sHostLotID[2];			//Host 수신 Lot ID
	CString		sHostRecipe[2];		//Host 수신 Recipe ID
	CString		sHostMGZID[2];			//Host 수신 Load 부 ID
	CString		sHostUldMGZID;		//Host 수신 Load 부 ID
	int			nHostCount[2];			//Host 수신 CM 총갯수
	CString		sHostTrayID;

	CString		sHostFailLotId;
	CString		sHostFailCode;
	CString		sHostFailText;

	CString		sHostCancelCode;
	CString		sHostCancelText;

	int			nPocketCnt;
	CString		sPocketNo[141];
	CString		sResult[141];
	
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


extern GLOVAL_DATA	gData;
extern GLOVAL_LOT	gLot;
extern GLOVAL_ALM	gAlm;
extern GLOVAL_UPH	gUph;
extern GLOVAL_MES	gMes;
extern GLOBAL_DOORLOCK gDoorLock;





