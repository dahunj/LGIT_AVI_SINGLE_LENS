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

#include <math.h>

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

//Tray Slot No
const int TRAY_X = 4, TRAY_Y = 8;


// R53B (VR-L) : LoadTray(3x4), CapTray(4x7),  ShipTray(3x7),  Picker(4) => AllPicker(1,2,3,4)
// R54B (VR-R) : LoadTray(3x4), CapTray(4x7),  ShipTray(3x6),  Picker(4) => AllPicker(1,2,3,4)
const int LT_X = 4, LT_Y = 3, CT_X = 4, CT_Y = 7,  ST_X = 4, ST_Y = 5, PICK = 4;

///////////////////////////////////////////////////////////////////////////////

extern CString gsCurrentDir;	// 현재 프로젝트 폴더

typedef struct
{
	CString	sLotID[2];
	CString	sOperID;		// Operator
	CString	sRecipe;		// Recipe Item
	CString sVendor;		// Cap Vendor 
		
	

} GLOVAL_DATA;

typedef struct {
	CString	sLotID[2];
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


const int UNLOADSTAGE1_Z_MOVEDOWN				= 0;
const int UNLOADSTAGE1_Z_MOVEUP					= 1;
const int UNLOADSTAGE1_Z_LOADSUPPORTUP			= 2;
const int UNLOADSTAGE1_Z_LOADSUPPORTDOWN		= 3;
const int UNLOADSTAGE1_Z_UNLOADSUPPORTUP		= 4;
const int UNLOADSTAGE1_Z_UNLOADSUPPORTDOWN		= 5;

const int UNLOADSTAGE2_Z_MOVEDOWN				= 0;
const int UNLOADSTAGE2_Z_MOVEUP					= 1;
const int UNLOADSTAGE2_Z_LOADSUPPORTUP			= 2;
const int UNLOADSTAGE2_Z_LOADSUPPORTDOWN		= 3;
const int UNLOADSTAGE2_Z_UNLOADSUPPORTUP		= 4;
const int UNLOADSTAGE2_Z_UNLOADSUPPORTDOWN		= 5;



const int UNLOADSTAGE1_Y_WORKPOS = 1;

#define UL_STG1_Z_MOVE_DOWN 0
#define UL_STG1_Z_MOVE_UP 1

#define UL_STG1_Y_WORK_POS 1