// AJinAXL.h : 헤더 파일
//
#pragma once

// *** AJin Configuration ***************************
// Motion Board    : RTEX
// In / Out Board  : RTEX
// Library Version : EzSoftwareUC V4.2.0.4042, 32Bit Version
// ********************************************************

#include "AJinDefine.h"

#include <afxwin.h>
#include <afxmt.h>
#include <set>
#include <vector>
#include <algorithm>

// 공유 예시 카운터(테스트용)
static CCriticalSection s_csCounter;


// =======================
// ThreadIdManager (선언)
// =======================
class ThreadIdManager
{
public:
	ThreadIdManager();

	int  AllocateId();
	void ReleaseId(int id);

private:
	CCriticalSection m_cs;
	std::set<int>    m_freeIds;  // 재사용 가능한 ID
	int              m_nextId;   // 아직 한 번도 안 쓴 ID 시작값
};

class CAJinAXL
{
public:
	CAJinAXL();
	virtual ~CAJinAXL();

private:
	DX_DATA_00	m_DX00;					// Input (X0000 - X0031)
	DX_DATA_01	m_DX01;					// Input (X0100 - X0131)
	DX_DATA_02	m_DX02;					// Input (X0200 - X0231)
	DX_DATA_03	m_DX03;					// Input (X0300 - X0331)
	

	DY_DATA_00	m_DY00;					// Output (Y0000 - Y0031)
	DY_DATA_01	m_DY01;					// Output (Y0100 - Y0131)
	DY_DATA_02	m_DY02;					// Output (Y0200 - Y0231)
	DY_DATA_03	m_DY03;					// Output (Y0300 - Y0331)


	AXIS_STATUS	m_Status[AXIS_COUNT];		// Axis Status Data
	AXIS_PARAM	m_Param[AXIS_COUNT];		// Axis Parameter Data
	CString		m_strAxisName[AXIS_COUNT];	// Axis Name

	BOOL		m_bReadVelocity;		// Setup Mode 에서만 읽기

protected:
	BOOL		m_bThreadAJin;
	CWinThread *m_pThreadAJin;
	static UINT	Thread_AJin(LPVOID lpVoid);

	void Sim_SetMotion(int nNo, int nAxis, double dPos);
	void Sim_SetOutToIn(int nNo);

public:
	BOOL Initialize();
	void Terminate();

	void Read_Input();					// DI Read
	void Read_Output();					// DO Read
	void Write_Output(int nModule);		// DO Write

	void Read_MotionStatus();			// Motion Status
	void Set_ReadVelocity(BOOL bRead) { m_bReadVelocity = bRead; }

	void Set_ServoOn(int nAxis);
	void Set_ServoOff(int nAxis);
	void Set_EncoderType(int nAxis, int nType);
	void Home_Search(int nAxis);
	void Set_Home(int nAxis);
	void Move_Absolute(int nAxis, double dPos);
	void Move_AbsSlow(int nAxis, double dPos, double dRatio);	// 2023.07.25
	void Move_Relative(int nAxis, double dPos);
	void Jog_Positive(int nAxis);
	void Jog_Negative(int nAxis);
	void Stop_Motion(int nAxis);
	void EStop_Motion(int nAxis);
	void Alarm_Reset(int nAxis);

	void Move_Abs_Override(int nAxis, double dPos, double dAt);
	void Move_Rel_Override(int nAxis, double dPos, double dAt);

	BOOL Is_Done(int nAxis);
	BOOL Is_Home(int nAxis);
	BOOL Is_MoveDone(int nAxis, double dPos, double dRange = 0.1);

	void Start_Trigger(int nAxis, double dStartPos, double dEndPos, double dPeriod, double dWidth);
	void Stop_Trigger(int nAxis);

	void Start_Scan(int nAxis, double dPos, double dTrigS, double dTrigE, double dTrigP, double dTrigW, double dVel);
	void Stop_Scan(int nAxis);

	void Read_AxisList();	// Axis Name & Param
	void Read_MotionParam(int nAxis);
	void Save_MotionParam(int nAxis, double dSpeedM, double dSpeedJ, double dAccel);
	void Save_RmsMotionSpeed(int nAxis, double dSpeedM, double dAccel);

	BOOL Is_AbsoluteType(int nAxis);
	BOOL Use_OrgAxis(int nAxis);
	BOOL Use_ElpAxis(int nAxis);
	BOOL Use_ElnAxis(int nAxis);

	DXY_DATA *Get_pDX(int nIndex);
	DXY_DATA *Get_pDY(int nIndex);

	DX_DATA_00 *Get_pDX00() { return &m_DX00; }
	DX_DATA_01 *Get_pDX01() { return &m_DX01; }
	DX_DATA_02 *Get_pDX02() { return &m_DX02; }
	DX_DATA_03 *Get_pDX03() { return &m_DX03; }


	DY_DATA_00 *Get_pDY00() { return &m_DY00; }
	DY_DATA_01 *Get_pDY01() { return &m_DY01; }
	DY_DATA_02 *Get_pDY02() { return &m_DY02; }
	DY_DATA_03 *Get_pDY03() { return &m_DY03; }


	AXIS_STATUS *Get_pStatus(int nAxis) { return &m_Status[nAxis]; }
	AXIS_PARAM *Get_pParam(int nAxis) { return &m_Param[nAxis]; }

	CString Get_AxisName(int nAxis) { return m_strAxisName[nAxis]; }
	double Get_Position(int nAxis) { return m_Status[nAxis].dPos; }
	BOOL   Get_ServoOn(int nAxis) { return m_Status[nAxis].bSOn; }
	BOOL   Get_AmpAlarm(int nAxis) { return m_Status[nAxis].bALM; }
	BOOL   Get_EndLimitPos(int nAxis) { return m_Status[nAxis].bELP; }
	BOOL   Get_EndLimitNeg(int nAxis) { return m_Status[nAxis].bELN; }
	BOOL   Get_HomeDone(int nAxis) { return m_Status[nAxis].bHom; }
	BOOL   Get_MotorRun(int nAxis) { return m_Status[nAxis].bRun; }

	void Save_AxisList();	// 값 입력하기 위한 테스트 프로그램


public:
	int		StartThread(int nType, int nAxis, double dPos);					// 새 워커 시작. 성공 시 쓰레드 ID(>0) 반환, 실패 시 0 반환
	void	GetCompletedIds(std::vector<int>& outCompleted);	// 완료된 쓰레드 ID들을 out에 채우고 내부 큐는 비움
	int		RunningCount() const;								// (옵션) 현재 실행 중으로 추정되는 개수

private:

	struct ThreadArgs   // 워커 스레드에서 사용할 인자
	{
		CAJinAXL*		pRunner;
		int				id;
		int				type;
		int				nAxisNo;
		double			dPosTarget;		
	};

	static UINT __cdecl WorkerProc(LPVOID pParam);		// 워커 스레드 함수 (정적)
	void NotifyDone(int id);						// 워커 종료 시 내부에서 호출 (ID 반납 + 완료 큐 적재)

	bool TryDequeue(int nAxis, int& out);

private:

	// 완료 ID 큐
	CCriticalSection	m_csCompleted;
	std::vector<int>	m_completedIds;

	// 실행 중 개수 추정치
	mutable CCriticalSection m_csRunning;
	int m_runningCount;

	// ID 매니저
	ThreadIdManager m_idMgr;




};

extern CAJinAXL g_objAJinAXL;

///////////////////////////////////////////////////////////////////////////////


