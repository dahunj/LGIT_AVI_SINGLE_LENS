// SequenceInit.h : 헤더 파일
//
#pragma once

#include "AJinAXL.h"
#include "DataManager.h"
#include "LoopTimer.h"

class CSequenceInit
{
public:
	CSequenceInit();
	virtual ~CSequenceInit();
	
private:
	AXIS_STATUS *m_pStatus[AXIS_COUNT];
	AXIS_PARAM	*m_pParam[AXIS_COUNT];
	
	DX_DATA_00	*m_pDX00;	// Input (X0000 - X0031)
	DX_DATA_01	*m_pDX01;	// Input (X0100 - X0131)
	DX_DATA_02	*m_pDX02;	// Input (X0200 - X0231)
	DX_DATA_03	*m_pDX03;	// Input (X0300 - X0331)


	DY_DATA_00	*m_pDY00;	// Output (Y0000 - Y0031)
	DY_DATA_01	*m_pDY01;	// Output (Y0100 - Y0131)
	DY_DATA_02	*m_pDY02;	// Output (Y0200 - Y0231)
	DY_DATA_03	*m_pDY03;	// Output (Y0300 - Y0331)


	EQUIP_DATA	*m_pEquipData;
	MOVE_DATA	*m_pMoveData;

	int			m_niMainInitCase;			//  0. (Error : 1000)
	int			m_niConveyorCase;			//  1. (Error : 1100)
	int			m_niMZElevCase;				//  2. (Error : 1200)
	int			m_niFeederCase;				//  3. (Error : 1300)
	int			m_niTrayPickerCase;			//  4. (Error : 1400)
	int			m_niLensCleanCase;			//  5. (Error : 1500)
	int			m_niTopInspectorCase;		//  6. (Error : 1600)
	int			m_niBtmInspectorCase; 		//  7. (Error : 1700)
	int			m_niMarkUnitCase;				//  8. (Error : 1800)
	int			m_niMainIndexCase;			
	
	CLoopTimer	m_tiMainInitLoop;		//  0. (Error : 1000)
	CLoopTimer	m_tiConveyorLoop;		//  1. (Error : 1100)
	CLoopTimer	m_tiMZElevLoop;			//  2. (Error : 1200)
	CLoopTimer	m_tiFeederLoop;			//  3. (Error : 1300)
	CLoopTimer	m_tiTrayPickerLoop;		//  4. (Error : 1400)
	CLoopTimer	m_tiLensCleanLoop;		//  5. (Error : 1500)
	CLoopTimer	m_tiTopInspectorLoop;	//  6. (Error : 1600)
	CLoopTimer	m_tiBtmInspectorLoop;	//  7. (Error : 1700)
	CLoopTimer	m_tiMarkUnitLoop;			//  8. (Error : 1800)
	CLoopTimer	m_tiMainIndexLoop;		
	
	BOOL		m_bInitComplete;
	
protected:
	BOOL		m_bThreadInitial;
	CWinThread	*m_pThreadInitial;
	static UINT	Thread_Initial(LPVOID lpVoid);

private:
	BOOL Initial_MainInit();			//  0. (Error : 1000)
	BOOL Initial_Conveyor();			//  1. (Error : 1100)
	BOOL Initial_MZ_Elevator();			//  2. (Error : 1200)	
	BOOL Initial_Feeder();				//  3. (Error : 1300)
	BOOL Initial_TrayPicker();			//  5. (Error : 1400)
	BOOL Initial_LensCleaner();			//  4. (Error : 1500)
	BOOL Initial_TopInspector();		//  6. (Error : 1600)
	BOOL Initial_BtmInspector();		//  7. (Error : 1700)
	BOOL Initial_MarkUnit();			//  8. (Error : 1800)
	BOOL Initial_MainIndex();			//  9. (Error : 1900)

	BOOL Initial_Simulation();

public:
	BOOL Get_ThreadInitial() { return m_bThreadInitial; }
	BOOL Get_InitComplete() { return m_bInitComplete; }
	void Set_InitComplete(BOOL bInitComp) { m_bInitComplete = bInitComp; }	
	
	int *Get_InitialCase();

	void Begin_InitialThread();
	void End_InitialThread();
	void Init_Replay();
	void Reset_InitialCase();

	BOOL Is_InitThreadRun() { return m_bThreadInitial; }
	BOOL Check_Mode();
};

extern CSequenceInit g_objSequenceInit;

///////////////////////////////////////////////////////////////////////////////
