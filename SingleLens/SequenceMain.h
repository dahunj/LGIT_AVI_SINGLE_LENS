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


	DY_DATA_00	*m_pDY00;	// Output (Y0000 - Y0031)
	DY_DATA_01	*m_pDY01;	// Output (Y0100 - Y0131)
	DY_DATA_02	*m_pDY02;	// Output (Y0200 - Y0231)
	DY_DATA_03	*m_pDY03;	// Output (Y0300 - Y0331)


	EQUIP_DATA	*m_pEquipData;
	MOVE_DATA	*m_pMoveData;

	CString		m_strLog;	// Log String


protected:
	CWinThread	*m_pThreadBeep;
	static UINT	Thread_Beep(LPVOID lpVoid);

	BOOL		m_bThreadMainRun;
	CWinThread	*m_pThreadMainRun;
	static UINT	Thread_MainRun(LPVOID lpVoid);


public:
	void Begin_MainRunThread();
	void End_MainRunThread();

	BOOL Is_MainThreadRun() { return m_bThreadMainRun; }

	void Reset_MainRunCase();
	int *Get_pMainRunCase();
	int  Get_MainRunCase(int nRun);
	void Set_MainRunCase(int nRun, int nCase);
	void Set_MainRunLoop(int nRun, int nLoop);


private:
	int			m_nLoadConveyorCase;	//  1. (Error : 3100)
	int			m_nMZElevCase;			//  2. (Error : 3400)
	int			m_nFeederCase;			//  3. (Error : 3700)
	int			m_nZigPickerCase;		//  4. (Error : 4000)
	int			m_nLensCleanerCase;		//  5. (Error : 4300)
	int			m_nTopInspectCase;		//  6. (Error : 4600)
	int			m_nBtmInspectCase;		//  7. (Error : 4900)
	int			m_nMarkUnitCase;			//  8. (Error : 5200)
	int			m_nMainIndexCase;			//  9. (Error : 5500)  
	int			m_nUnloadConveyorCase;	//  10. (Error : 5800)

	DWORD		m_dwLoadConveyor;		//  1. (Error : 3100)
	DWORD		m_dwMZElev;				//  2. (Error : 3400)
	DWORD		m_nFeeder;				//  3. (Error : 3700)
	DWORD		m_dwZigPicker;			//  4. (Error : 4000)
	DWORD		m_dwLensCleaner;		//  5. (Error : 4300)
	DWORD		m_dwTopInspect;			//  6. (Error : 4600)
	DWORD		m_dwBtmInspect;			//  7. (Error : 4900)
	DWORD		m_dwMarkUnit;				//  8. (Error : 5200)
	DWORD		m_dwIndexT;				//  9. (Error : 5500)
	DWORD		m_dwUnloadConveyor;			//  10. (Error : 5800)

	CLoopTimer	m_nLoadConveyorLoop;	//  1. (Error : 3100)
	CLoopTimer	m_nMZElevLoop;			//  2. (Error : 3400)
	CLoopTimer	m_nFeederLoop;			//  3. (Error : 3700)
	CLoopTimer	m_nZigPickerLoop;		//  4. (Error : 4000)
	CLoopTimer	m_nLensCleanerLoop;		//  5. (Error : 4300)
	CLoopTimer	m_nTopInspectLoop;		//  6. (Error : 4600)
	CLoopTimer	m_nBtmInspectLoop;		//  7. (Error : 4900)
	CLoopTimer	m_nMarkUnitLoop;			//  8. (Error : 5200) 
	CLoopTimer	m_nIndexTLoop;			//  9. (Error : 5500) 
	CLoopTimer	m_nUnloadConveyorLoop;	//  10. (Error : 5800)

	BOOL		m_bLotEnd;

private:
	BOOL			LoadConveyorRun();		//  1. (Error : 3100)
	BOOL			MZElevRun();			//  2. (Error : 3400)
	BOOL			FeederRun();			//  3. (Error : 3700)
	BOOL			ZigPickerRun();			//  4. (Error : 4000)
	BOOL			LensCleanerRun();		//  5. (Error : 4300)
	BOOL			TopInspectorRun();		//  6. (Error : 4600)
	BOOL			BtmInspectorRun();		//  7. (Error : 4900)
	BOOL			MarkUnitRun();			//  8. (Error : 5200)
	BOOL			MainIndexRun();			//  9. (Error : 5500)  
	BOOL			UnloadConveyorRun();	//  10. (Error : 5800)

	BOOL LotEnd_Run();

	BOOL Run_Simulation();


	void Job_LotStart();
	void Job_LotEnd();

	void Beep_Post(int nState, int nTime);


public:
	double m_dTop1Z;
	
	BOOL Get_IsAutoRun();

	BOOL Check_ElevEmpty(int nPos);
	BOOL Check_ModuleLotEnd(int nLotNo);

	void Set_ClearRunData(BOOL bInit);
	void Set_ClearLotData(BOOL bInit, int nLotNo);
	
	//Conveyor 
	int Check_CVMZSensors();
	BOOL Check_IndexDone();

	BOOL Check_ZigPickerEmpty();
	BOOL Check_FeederEmpty();
	BOOL Check_IndexEmpty(int nPos);
	BOOL Check_CtZigInMZ(int nPos);

	int Search_ZigSlotNo(int nPos, int nSlot);
	
	void Set_IndexEnd();

	BOOL CheckCtZigAllReturn();	
	//////////////////////////////////////////////////////////////////////////
	void Init_TopZig();
	BOOL Select_TopScanPos(int &nTopPosX, int &nTopPosY);
		
	void Init_BtmZig();
	BOOL Select_BtmScanPos(int &nBtmPosX, int &nBtmPosY);

	void Init_MarkZig();
	BOOL Select_MarkScanPos(int &nMarkPosX, int &nMarkPosY);

	BOOL Check_InspectDone(const CString& sZigID, int sSlotNo, int sLensNo, DWORD dwStart);
	
	void Init_MZSlot(int nSlotNo, int nX, int nY);
};

extern CSequenceMain g_objSequenceMain;