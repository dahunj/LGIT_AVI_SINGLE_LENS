// LogFile.h : 헤더 파일
//
#pragma once

class CLogFile  
{
public:
	CLogFile();
	virtual ~CLogFile();

public:
	void Create_Folder(CString sPath);
	void MakeFolder(CString sPath);

	void Save_AlarmLog(CString sLog);
	void Save_AlarmResetLog(CString sLog);
	void Save_HandlerLog(CString sLog);
	void Save_SaveRunTimeLog(CString sLog);
	void Save_InspectorLog(CString sLog);
	void Save_JobListLog(CString sLog, BOOL bMode=FALSE);
	void Save_LotResult(int nPNo, CString sLog);
	void Save_LotLog(int nPNo);
	void Save_AviHandlerLog(CString sLog);
	void Save_LotError(CString sLog, int nPNo=0);
	void Save_ECMLog(int nType, CString strLog);	//nType:1[Alarm], 2[Joblist] 3[Inspect]
	void Save_TestLog(CString sLog);
	void Save_OperatingRatio(CString sLog);
	
	void Save_MachineStopLog(CString sLog);
	void Save_MesAgentLog(CString sLog);
	void Save_CmTrackingLog(CString strOut, int nTrayCount, int nPosX, int nPosY, int nPortNo, int nTrayNo, int nCmNo);
	void Save_ECMTracking(CString sLog, int nTrayCount, int nPosX, int nPosY, int nPortNo, int nTrayNo, int nCmNo);
	void Save_Interlock(int nType);	
	void Save_PCLog(int nPNo, CString sLog);
	
	void Save_MCCLog(const CString& sLog);

	
	
	void Save_JobListExcel(CString sLog);	

	// Log 표준화
	void Save_StdMotionLog(CString sType, int nZone, int nCase, int nValue, CString sZone, CString sMsg);
	void Save_EfficiencyLog(int nZone, CString sStatus, int nCode, CString sNote);
	void Get_ZoneMsg(int nZone, int nCase, CString &sZone, CString &sMsg);

};

extern CLogFile g_objLogFile;

///////////////////////////////////////////////////////////////////////////////
