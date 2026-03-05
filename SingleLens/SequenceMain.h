#pragma once

#include "AJinAXL.h"
#include "DataManager.h"
#include "LoopTimer.h"



class CSequenceMain
{
public:
	CSequenceMain(void);
	virtual ~CSequenceMain(void);


private:
	AXIS_STATUS *m_pStatus[AXIS_COUNT];
	AXIS_PARAM	*m_pParam[AXIS_COUNT];

	DX_DATA_00	*m_pDX00;	// Input (X0000 - X0031)
	DX_DATA_01	*m_pDX01;	// Input (X0100 - X0131)
	DX_DATA_02	*m_pDX02;	// Input (X0200 - X0231)
	DX_DATA_03	*m_pDX03;	// Input (X0300 - X0331)
	DX_DATA_04	*m_pDX04;	// Input (X0400 - X0431)
	DX_DATA_05	*m_pDX05;	// Input (X0500 - X0531)
	DX_DATA_06	*m_pDX06;	// Input (X0600 - X0631)
	DX_DATA_07	*m_pDX07;	// Input (X0700 - X0731)
	DX_DATA_08	*m_pDX08;	// Input (X0800 - X0831)
	DX_DATA_09	*m_pDX09;	// Input (X0900 - X0931)
	DX_DATA_10	*m_pDX10;	// Input (X1000 - X1031)
	DX_DATA_11	*m_pDX11;	// Input (X1100 - X1131)
	DX_DATA_12	*m_pDX12;	// Input (X1200 - X1231)
	DX_DATA_13	*m_pDX13;	// Input (X1300 - X1331)

	DY_DATA_00	*m_pDY00;	// Output (Y0000 - Y0031)
	DY_DATA_01	*m_pDY01;	// Output (Y0100 - Y0131)
	DY_DATA_02	*m_pDY02;	// Output (Y0200 - Y0231)
	DY_DATA_03	*m_pDY03;	// Output (Y0300 - Y0331)
	DY_DATA_04	*m_pDY04;	// Output (Y0400 - Y0431)
	DY_DATA_05	*m_pDY05;	// Output (Y0500 - Y0531)
	DY_DATA_06	*m_pDY06;	// Output (Y0600 - Y0631)
	DY_DATA_07	*m_pDY07;	// Output (Y0700 - Y0731)
	DY_DATA_08	*m_pDY08;	// Output (Y0800 - Y0831)
	DY_DATA_09	*m_pDY09;	// Output (Y0900 - Y0931)
	DY_DATA_10	*m_pDY10;	// Output (Y1000 - Y1031)
	DY_DATA_11	*m_pDY11;	// Output (Y1100 - Y1131)
	DY_DATA_12	*m_pDY12;	// Output (Y1200 - Y1231)
	DY_DATA_13	*m_pDY13;	// Output (Y1300 - Y1331)

	EQUIP_DATA	*m_pEquipData;
	MOVE_DATA	*m_pMoveData;

	CString		m_strLog;	// Log String


protected:
	CWinThread	*m_pThreadBeep;
	static UINT	Thread_Beep(LPVOID lpVoid);

	BOOL		m_bThreadMainRun;
	CWinThread	*m_pThreadMainRun;
	static UINT	Thread_MainRun(LPVOID lpVoid);



private:
	int			m_nLoadConveyorCase;	//  1. (Error : 3100)
	int			m_nMZElevCase;			//  2. (Error : 3400)
	int			m_nTrayPickerCase;		//  3. (Error : 3700)
	int			m_nLensCleanerCase;		//  4. (Error : 4000)
	int			m_nTopInspectCase;		//  5. (Error : 4300)
	int			m_nBtmInspectCase;		//  6. (Error : 4600)
	int			m_nMarkerCase;			//  7. (Error : 4900)
	int			m_nIndexTableCase;		//  8. (Error : 5200)  

	DWORD		m_dwLoadConveyor;	//  1. (Error : 3100)
	DWORD		m_dwMZElev;			//  2. (Error : 3400)
	DWORD		m_dwTrayPicker;		//  3. (Error : 3700)
	DWORD		m_dwLensCleaner;	//  4. (Error : 4000)
	DWORD		m_dwTopInspect;		//  5. (Error : 4300)
	DWORD		m_dwBtmInspect;		//  6. (Error : 4600)
	DWORD		m_dwMarker;			//  7. (Error : 4900)
	DWORD		m_dwIndexTable;		//  8. (Error : 5200)  

	CLoopTimer	m_nLoadConveyorLoop;	//  1. (Error : 3100)
	CLoopTimer	m_nMZElevLoop;			//  2. (Error : 3400)
	CLoopTimer	m_nTrayPickerLoop;		//  3. (Error : 3700)
	CLoopTimer	m_nLensCleanerLoop;		//  4. (Error : 4000)
	CLoopTimer	m_nTopInspectLoop;		//  5. (Error : 4300)
	CLoopTimer	m_nBtmInspectLoop;		//  6. (Error : 4600)
	CLoopTimer	m_nMarkerLoop;			//  7. (Error : 4900)
	CLoopTimer	m_nIndexTableLoop;		//  8. (Error : 5200)  			

private:
	BOOL			LoadConveyorRun();		//  1. (Error : 3100)
	BOOL			MZElevCaseRun();		//  2. (Error : 3400)
	BOOL			TrayPickerRun();		//  3. (Error : 3700)
	BOOL			LensCleanerRun();		//  4. (Error : 4000)
	BOOL			TopInspectorRun();		//  5. (Error : 4300)
	BOOL			BtmInspectorRun();		//  6. (Error : 4600)
	BOOL			MarkerRun();			//  7. (Error : 4900)
	BOOL			IndexTableRun();		//  8. (Error : 5200)  

	BOOL LotEnd_Run();

	BOOL Run_Simulation();


	//void Job_LotStart(int nPort);
	//void Job_LotEnd(int nPort);
	void Beep_Post(int nState, int nTime);


};

extern CSequenceMain g_objSequenceMain;