// LogFile.cpp: implementation of the CLogFile class.
//
#include "stdafx.h"
#include "LogFile.h"
#include "DataManager.h"
#include "Common.h"
#include "AJinAXL.h"
#include "AJinDefine.h"
#include "DataManager.h"

// CLogFile
CLogFile g_objLogFile;

CCriticalSection g_csAlarmLog;
CCriticalSection g_csAlarmResetLog;
CCriticalSection g_csHandlerLog;
CCriticalSection g_csRunTimeLog;
CCriticalSection g_csInspectorLog;
CCriticalSection g_csJobListLog;
CCriticalSection g_csZigListLog;
CCriticalSection g_csAviHandlerLog;
CCriticalSection g_csECMLog;
CCriticalSection g_csLoadCellLog;
CCriticalSection g_csMachineStopLog;
CCriticalSection g_csMesAgentLog;
CCriticalSection g_csTrackingLog;
CCriticalSection g_csBarcodeLog;
CCriticalSection g_csMCCLog;
CCriticalSection g_csStdMotionLog;
CCriticalSection g_csEfficiencyLog;
CCriticalSection g_csLotTimeLog;
CCriticalSection g_csTerminalLog;

CLogFile::CLogFile()
{
}

CLogFile::~CLogFile()
{
}

///////////////////////////////////////////////////////////////////////////////

void CLogFile::Create_Folder(CString sPath)
{
	if (sPath == _T("")) return;
	if (sPath.Right(1) == _T("\\")) sPath = sPath.Left(sPath.GetLength() - 1);
	if (GetFileAttributes(sPath) != -1) return;	// Directory Exist!!!

	int nFound = sPath.ReverseFind('\\');
	Create_Folder(sPath.Left(nFound));

	CreateDirectory(sPath, NULL);
}

void CLogFile::MakeFolder(CString sPath)	//"D:\\Run\\Log\\LotData\\YYYY\\MM\\DD\\";
{
	CString sTemp;
	int nIdx = 0;

	while(true) {
		nIdx = sPath.Find("\\");
		sTemp += sPath.Mid(0, nIdx) + "\\";
		CreateDirectory(sTemp,FALSE);
		sPath = sPath.Mid(nIdx+1, sPath.GetLength());
		if (nIdx<0) break;
	}
}

///////////////////////////////////////////////////////////////////////////////

void CLogFile::Save_AlarmLog(CString sLog)
{
	g_csAlarmLog.Lock();

	CString strPath = gsCurrentDir + "\\LOG\\Alarm";

	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile, strSave;
	strFile.Format("%s\\%04d%02d%02d_Alarm.txt", strPath, time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			strSave.Format("%02d:%02d:%02d %03d,%s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);	// , Aß°¡

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csAlarmLog.Unlock();
}

void CLogFile::Save_AlarmResetLog(CString sLog)
{
	g_csAlarmResetLog.Lock();

	CString strPath = gsCurrentDir + "\\LOG\\AlarmReset";

	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile, strSave;
	strFile.Format("%s\\%04d%02d%02d_AlarmReset.txt", strPath, time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			strSave.Format("%02d:%02d:%02d %03d,%s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);	// , Aß°¡

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csAlarmResetLog.Unlock();
}

void CLogFile::Save_HandlerLog(CString sLog)
{
	g_csHandlerLog.Lock();

	CString strPath = gsCurrentDir + "\\LOG\\Handler";

	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile, strSave;
	strFile.Format("%s\\%04d%02d%02d_Handler.txt", strPath, time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			strSave.Format("[%02d:%02d:%02d.%03d], %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csHandlerLog.Unlock();

	Save_ECMLog(4, sLog);
}


void CLogFile::Save_TerminalLog(const CString& sLog)
{
	

	CString strPath = gsCurrentDir + "\\LOG\\Terminal";

	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile, strSave;
	strFile.Format("%s\\%04d%02d%02d_Terminal.txt", strPath, time.wYear, time.wMonth, time.wDay);

	g_csTerminalLog.Lock();
	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			strSave.Format("[%02d:%02d:%02d.%03d], %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csTerminalLog.Unlock();
	
}

void CLogFile::Save_SaveRunTimeLog(CString sLog)
{
	g_csRunTimeLog.Lock();

	CString strPath = gsCurrentDir + "\\LOG\\RunTime";

	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile, strSave;
	strFile.Format("%s\\%04d%02d%02d.txt", strPath, time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			strSave.Format("[%02d:%02d:%02d.%03d], %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csRunTimeLog.Unlock();
}

void CLogFile::Save_InspectorLog(CString sLog)
{
	g_csInspectorLog.Lock();

	CString strPath = gsCurrentDir + "\\LOG\\Inspector";

	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile, strSave;
	strFile.Format("%s\\%04d%02d%02d_Inspector.txt", strPath, time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			strSave.Format("[%02d:%02d:%02d.%03d],%s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csInspectorLog.Unlock();
}

void CLogFile::Save_JobListLog(CString sLog, int nMZNo)
{
	g_csJobListLog.Lock();

	CString strPath = gsCurrentDir + "\\LOG\\JobList";

	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString sTitle, strFile, strSave;
	sTitle.Format("Time,LotID,MGZ_ID,Start_Time,End_Time,Run_Time,Unload_Time,Tact(S-E),Tact(RunTime),Tact(Unload_Time),UPH(S-E),UPH(RunTime),UPH(Unload_Time),Alarm_Count,Stop_Time,Zig_Count,Lens_Count,Good_Count,NG_Count\r\n");
	strFile.Format("%s\\%04d%02d%02d_JobList.csv", strPath, time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();
			if (file.GetLength() < 1) file.Write(sTitle, sTitle.GetLength());

			strSave.Format("[%02d:%02d:%02d.%03d], %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csJobListLog.Unlock();

	Save_ECMLog(2, sLog, nMZNo);
}



void CLogFile::Save_CtZigResult(CString sLog, int nMZNo, int nPos)
{


	SYSTEMTIME time;
	GetLocalTime(&time);

	CString sVisionPos;

	if(nPos == eVision::TC)
	{
		sVisionPos = "Top";
	}
	else
	{
		sVisionPos = "Btm";
	}	

	CString strPath1 = "D:\\EVMS\\TP\\Log";
	CString strPath2 = "D:\\EVMS\\TP\\Backup";
	CString strPath3;

	Create_Folder(strPath1);
	Create_Folder(strPath2);


	strPath3 = gsCurrentDir + "\\LOG\\ZIgList";
	Create_Folder(strPath3);

	CString strFile1, strFile2, strFile3, strTitle, strTime, strPcName, strSave;
	
	strFile1.Format("%s\\%s_%04d%02d%02d%02d_ZigList.csv", strPath1, gData.sMZIDMainIdex[eMainIndex::Mark], time.wYear, time.wMonth, time.wDay, time.wHour);
	strFile2.Format("%s\\%s_%04d%02d%02d%02d_ZigList.csv", strPath2, gData.sMZIDMainIdex[eMainIndex::Mark], time.wYear, time.wMonth, time.wDay, time.wHour);
	strFile3.Format("%s\\%s_%s_ZigList.csv", strPath3, gLot.sStartTime[nMZNo-1], gData.sMZIDMainIdex[eMainIndex::Mark]);
	
	g_csZigListLog.Lock();
	
	CFile file;
	if (!file.Open(strFile1, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) 
	{
		g_objLogFile.Save_HandlerLog("LotTime Open Fail");
		return;
	}
	strTitle.Format("Time,LotID,MGZ_ID,Start_Time,End_Time,Run_Time,Tact,UPH,UPH_Compare,Inspection_Count\r\n");
	
	try {
		file.SeekToEnd();

		if (file.GetLength() < 1) file.Write(strTitle, strTitle.GetLength());

		strTime.Format("'%04d-%02d-%02d %02d:%02d:%02d.%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
		
		strSave.Format("%s,%s\r\n", strTime, sLog);

		file.Write(strSave, strSave.GetLength());
		file.Close();


	} catch (CFileException *pEx) {
		pEx->Delete();
	}



	CFile file2;
	if (!file2.Open(strFile2, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) 
	{
		g_objLogFile.Save_HandlerLog("LotTime Open Fail");
		return;
	}
	strTitle.Format("Time,LotID,MGZ_ID,Start_Time,End_Time,Run_Time,Tact,UPH,UPH_Compare,Inspection_Count\r\n");

	try {
		file2.SeekToEnd();

		if (file2.GetLength() < 1) file2.Write(strTitle, strTitle.GetLength());

		strTime.Format("'%04d-%02d-%02d %02d:%02d:%02d.%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
		
		strSave.Format("%s,%s\r\n", strTime, sLog);

		file2.Write(strSave, strSave.GetLength());
		file2.Close();


	} catch (CFileException *pEx) {
		pEx->Delete();
	}
	

	CFile file3;
	if (!file3.Open(strFile3, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) 
	{
		g_objLogFile.Save_HandlerLog("LotTime Open Fail");
		return;
	}
	strTitle.Format("Time,LotID,MGZ_ID,Start_Time,End_Time,Run_Time,Tact,UPH,UPH_Compare,Inspection_Count\r\n");

	try {
		file3.SeekToEnd();

		if (file3.GetLength() < 1) file3.Write(strTitle, strTitle.GetLength());

		strTime.Format("'%04d-%02d-%02d %02d:%02d:%02d.%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
		
		strSave.Format("%s,%s\r\n", strTime, sLog);

		file3.Write(strSave, strSave.GetLength());
		file3.Close();	

	} catch (CFileException *pEx) {
		pEx->Delete();
	}


	g_csZigListLog.Unlock();

}

void CLogFile::Save_LotResult(int nPNo, CString sLog)
{
	CString strPath1 = "D:\\EVMS\\TP\\Log";
	CString strPath2 = "D:\\EVMS\\TP\\Backup";
	CString strPath3;

	Create_Folder(strPath1);
	Create_Folder(strPath2);

	CTime tNow = CTime::GetCurrentTime();
	CTime tLog = tNow - CTimeSpan(7 * 60 * 60);

	strPath3.Format("%s\\LOG\\SPC\\%04d\\%02d\\%02d\\", gsCurrentDir, tLog.GetYear(), tLog.GetMonth(), tLog.GetDay());
	MakeFolder(strPath3);

	CString strFile1, strFile2, strFile3, strTitle, strDate, strSave;
	strFile1.Format("%s\\%s_%04d%02d%02d07_CapLot_Result.csv", strPath1, gData.sZigID[nPNo], tLog.GetYear(), tLog.GetMonth(), tLog.GetDay());
	strFile2.Format("%s\\%s_%04d%02d%02d07_CapLot_Result.csv", strPath2, gData.sZigID[nPNo], tLog.GetYear(), tLog.GetMonth(), tLog.GetDay());
	strFile3.Format("%s%s_CapLot_Result.csv", strPath3, gData.sZigID[nPNo]);

	CFile file;
	if (!file.Open(strFile1, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) return;

	strTitle.Format("날짜,Lot Start,Lot End,Term,호기,Lot ID,투입수\r\n");

	try {
		file.SeekToEnd();

		if (file.GetLength() < 1) file.Write(strTitle, strTitle.GetLength());

		strDate.Format("%02d/%02d", tNow.GetMonth(), tNow.GetDay());

		strSave.Format("%s,%s\r\n", strDate, sLog);

		file.Write(strSave, strSave.GetLength());
		file.Close();

		CopyFile(strFile1, strFile2, FALSE);	// Backup
		CopyFile(strFile1, strFile3, FALSE);	// SPC

	} catch (CFileException *pEx) {
		pEx->Delete();
	}
}

void CLogFile::Save_AviHandlerLog(CString sLog)
{
	g_csAviHandlerLog.Lock();

	CString strPath = gsCurrentDir + "\\LOG\\AviHandler";

	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile, strSave;
	strFile.Format("%s\\%04d%02d%02d.txt", strPath, time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			strSave.Format("[%02d:%02d:%02d %03d] %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csAviHandlerLog.Unlock();
}

void CLogFile::Save_LotError(CString sLog, int nPNo)
{
	CString strPath1 = "D:\\EVMS\\TP\\Log";
	CString strPath2 = "D:\\EVMS\\TP\\Backup";
	CString strPath3;

	Create_Folder(strPath1);
	Create_Folder(strPath2);

	SYSTEMTIME time;
	GetLocalTime(&time);

	strPath3.Format("%s\\LOG\\SPC\\%04d\\%02d\\%02d\\", gsCurrentDir, time.wYear, time.wMonth, time.wDay);
	MakeFolder(strPath3);

	
}


void CLogFile::Save_ECMLog(int nType, CString strLog, int nMGZNo)	//nType:1[Alarm], 2[Joblist] 3[Inspect]
{
	int nMNo = nMGZNo - 1;

	if(nMNo < 0 ) nMNo = 0;

	CString strFile, strFile2, sTitle, strTime, strSave;

	CString strPath = "D:\\EVMS\\TP\\Log\\";
	CString strPath2 = "D:\\EVMS\\TP\\Backup\\";

	Create_Folder(strPath);
	Create_Folder(strPath2);

	SYSTEMTIME time;
	GetLocalTime(&time);
	strTime.Format("%04d-%02d-%02d %02d:%02d:%02d:%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

	if (nType == 1) sTitle.Format("Time,Station,Type,LotNum,Error Code,Error,Start_Time,End_Time,Lead_Time,Barcode\r\n");
	if (nType == 2) sTitle.Format("Time,Station,Type,LotNum,Start_Time,End_Time,Run_Time,Unload_Time,Tact(S-E),Tact(RunTime),Tact(Unload_Time),UPH(S-E),UPH(RunTime),UPH(Unload_Time),Alarm_Count,Stop_Time,Efficiency(RunTime), Efficiency(Unload),Tray_Count,CM_Count,Good_Count,NG_Count,N1_Count,N2_Count,N3_Count,N4_Count,MESNG_Count\r\n");
	if (nType == 3) sTitle.Format("Time,Station,Type,LotNum,Load_Pick,Inspect,Barcode,NG_Pick,Good_Pick,Trans_Pick\r\n");
	if (nType == 4) sTitle.Format("Time,Station,Type\r\n");

	if (nType == 1) strFile.Format("%s%s_%04d%02d%02d%02d_Alarm.csv", strPath, "SingleLens", time.wYear, time.wMonth, time.wDay, time.wHour);
	if (nType == 2) strFile.Format("%s%s_%04d%02d%02d%02d_JobList.csv", strPath, gData.sMZID[eMZBuffer::Load] , time.wYear, time.wMonth, time.wDay, time.wHour);
	if (nType == 3) strFile.Format("%s%s_%04d%02d%02d%02d_Inspector.csv", strPath, "SingleLens", time.wYear, time.wMonth, time.wDay, time.wHour);
	if (nType == 4) strFile.Format("%s%s_%04d%02d%02d%02d_Handler.csv", strPath, "SingleLens", time.wYear, time.wMonth, time.wDay, time.wHour);

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	g_csECMLog.Lock();

	CFile file;
	if (!file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) return;

	try 
	{
		file.SeekToEnd();

		if (file.GetLength() < 1) file.Write(sTitle, sTitle.GetLength());

		if(nType == 4) strSave.Format("%s,%s,%s,%s\r\n", strTime, gData.sComName, pEquipData->sModelName, strLog);
		else if(nType == 2) strSave.Format("%s,%s,%s,%s\r\n", strTime, gData.sComName, pEquipData->sModelName, strLog);
		else
		{
			strSave.Format("%s,%s,%s,%s,%s\r\n", strTime, gData.sComName, pEquipData->sModelName, strLog, "");
		}
		file.Write(strSave, strSave.GetLength());
		file.Close();

	}
	catch (CFileException *pEx)
	{
		pEx->Delete();
	}


	g_csECMLog.Unlock();
}


///////////////////////////////////////////////////////////////////////////////

void CLogFile::Save_TestLog(CString sLog)
{
	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strPath = gsCurrentDir + "\\LOG\\TEST";

	Create_Folder(strPath);

	CString strFile, strSave;
	strFile.Format("%s\\%04d%02d%02d.txt", strPath, time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			strSave.Format("[%02d:%02d:%02d %03d] %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
}

void CLogFile::Save_LotLog(int nPNo)
{
	
}

void CLogFile::Save_OperatingRatio(CString sLog)	// °¡μ¿·u AU¾÷ Aß
{
	CString strPath = gsCurrentDir + "\\LOG\\OperatingRatio";

	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile, strSave, strTitle;
	strFile.Format("%s\\%04d%02d%02d.csv", strPath, time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			if (file.GetLength() < 1) {
				strTitle.Format("Time,호기,Lot ID,Lot Start,Lot End,Cycle Time,CM(EA),Run Time,Stop Time,Error Time,Error Count,수율,UPH,MTB\r\n");
				file.Write(strTitle, strTitle.GetLength());
			}

			char szPcName[MAX_COMPUTERNAME_LENGTH + 1];
			DWORD dwNameSize = MAX_COMPUTERNAME_LENGTH + 1;
			GetComputerName(szPcName, &dwNameSize);

			strSave.Format("[%02d:%02d:%02d %03d],%s,%s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, szPcName, sLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
}

void CLogFile::Save_MachineStopLog(CString sLog)
{
	g_csMachineStopLog.Lock();

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strPath, strFile, strTitle, strSave;
	strPath.Format("%s\\LOG\\MachineStop", gsCurrentDir);
	Create_Folder(strPath);

	strFile.Format("%s\\%04d%02d%02d_MachineStop.csv", strPath, time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			if (file.GetLength() < 1) {
				strTitle.Format("Time,Comment,Lead_Time\r\n");
				file.Write(strTitle, strTitle.GetLength());
			}

			strSave.Format("%02d:%02d:%02d %03d,%s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csMachineStopLog.Unlock();
}

void CLogFile::Save_MesAgentLog(CString sLog)
{
	g_csMesAgentLog.Lock();

	CString strPath = gsCurrentDir + "\\LOG\\MESAgent";

	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile, strSave;
	strFile.Format("%s\\%04d%02d%02d_MesAgent.txt", strPath, time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			strSave.Format("[%02d:%02d:%02d %03d], %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csMesAgentLog.Unlock();
}

void CLogFile::Save_TrackingLog(int nInfo, CString sBarcode, int nMZNo, int nZigNo, int nLensNo)
{
	g_csTrackingLog.Lock();

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strPath, strPath2, strFile, strFile2, strTitle, strSave, strSave2;
	strPath.Format("%s\\LOG\\Tracking\\%04d-%02d-%02d", gsCurrentDir, time.wYear, time.wMonth, time.wDay);
	Create_Folder(strPath);

	strFile.Format("%s\\%s_Tracking.csv", strPath, sBarcode);

	strPath2 = "D:\\EVMS\\TP\\Log";
	Create_Folder(strPath2);

	strFile2.Format("%s\\%s_%04d%02d%02d%02d_Tracking.csv", strPath2, sBarcode, time.wYear, time.wMonth, time.wDay, time.wHour);
	
	
	CString sMarkUse;
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if(pEquipData->bUseMark) sMarkUse = "Use";
	else					 sMarkUse = "Skip";

	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	double dMarkZ = pMoveData->dMarkUnitZ[eMark_Z::MarkDown];
	
	
	CFile file;
	if (!file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) return;

	strTitle.Format("Time,Tray Barcode,Judge,MZG No,Tray No,Lens No,Index Pocket No, Mark Use, Mark Pos\r\n");

	try {
		file.SeekToEnd();

		if (file.GetLength() < 1) file.Write(strTitle, strTitle.GetLength());

		if (nInfo == 1 || nInfo == 9) 
		{
			strSave.Format("%04d-%02d-%02d %02d:%02d:%02d.%03d,%s,G,%d,%d,%d,%d,%s,%0.3lf\r\n",
				time.wYear, time.wMonth, time.wDay,time.wHour, time.wMinute, time.wSecond, time.wMilliseconds,
				sBarcode, nMZNo, nZigNo, nLensNo, gData.nTablePocketMainIndex[eMainIndex::Mark], sMarkUse, dMarkZ); 
		}
		else
		{
			strSave.Format("%04d-%02d-%02d %02d:%02d:%02d.%03d,%s,N,%d,%d,%d,%d,%s,%0.3lf\r\n",
				time.wYear, time.wMonth, time.wDay,time.wHour, time.wMinute, time.wSecond, time.wMilliseconds,
				sBarcode, nMZNo, nZigNo, nLensNo, gData.nTablePocketMainIndex[eMainIndex::Mark], sMarkUse, dMarkZ); 
		}
		file.Write(strSave, strSave.GetLength());
		file.Close();

	} catch (CFileException *pEx) {
		pEx->Delete();
	}


	CFile file2;
	if (!file2.Open(strFile2, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) return;

	strTitle.Format("Time,Tray Barcode,Judge,MZG No,Tray No,Lens No,Index Pocket No\r\n");

	try {
		file2.SeekToEnd();

		if (file2.GetLength() < 1) file2.Write(strTitle, strTitle.GetLength());

		if (nInfo == 1 || nInfo == 9) 
		{
			strSave2.Format("%04d-%02d-%02d %02d:%02d:%02d.%03d,%s,G,%d,%d,%d,%d\r\n",
				time.wYear, time.wMonth, time.wDay,time.wHour, time.wMinute, time.wSecond, time.wMilliseconds,
				sBarcode, nMZNo, nZigNo, nLensNo, gData.nIndexPos); 
		}
		else
		{
			strSave2.Format("%04d-%02d-%02d %02d:%02d:%02d.%03d,%s,N,%d,%d,%d,%d\r\n",
				time.wYear, time.wMonth, time.wDay,time.wHour, time.wMinute, time.wSecond, time.wMilliseconds,
				sBarcode, nMZNo, nZigNo, nLensNo, gData.nIndexPos); 
		}
		file2.Write(strSave2, strSave2.GetLength());
		file2.Close();

	} catch (CFileException *pEx) {
		pEx->Delete();
	}

	//Save_ECMTracking(strSave, nTrayCount, nPosX, nPosY, nTrayNo, nCmNo);


	g_csTrackingLog.Unlock();
}



void CLogFile::Save_Interlock(int nType)
{
	CString strFile, sTitle, sTitle1, strTime, strSave, strSave1, strSave2, strSave3, strSave4, strSave5, strSave6, strLotID, strDoor[23], sInterUse;

	CString sECMPath = "D:\\EVMS\\TP\\LOG\\";
	Create_Folder(sECMPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	if (nType == 0) {
		gIt.nOpenTime = 0;
		gIt.nOpenStart = 0;
		gIt.nLogYY = time.wYear;	//등록년
		gIt.nLogMM = time.wMonth;	//등록월
		gIt.nLogDD = time.wDay;		//등록날
		gIt.nLogHH = time.wHour;	//등록시간
	}
	if (gIt.nLogMM < 1 || gIt.nLogMM > 12) return;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (nType == 1)	strTime.Format("%04d-%02d-%02d %02d:00:00.000",		 time.wYear, time.wMonth, time.wDay, time.wHour);
	else			strTime.Format("%04d-%02d-%02d %02d:%02d:%02d.%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

	strLotID = gData.sLotIDElevLoad[eMZ::Load];
	if(strLotID == "") strLotID = gData.sMZIDElevLoad[eMZ::Load]; 


	if(strLotID != "") strFile.Format("%s%s_%04d%02d%02d%02d_InterlockResult.csv", sECMPath, strLotID, gIt.nLogYY, gIt.nLogMM, gIt.nLogDD, gIt.nLogHH);
	else strFile.Format("%sSingleLensDOOR1_%04d%02d%02d%02d_InterlockResult.csv", sECMPath, gIt.nLogYY, gIt.nLogMM, gIt.nLogDD, gIt.nLogHH);
	
	sTitle.Format("time,station,lotNum,barcode,SWversion,State,site,Line,Machine,operator,result,Interlock,Interlock off Time,Interlock Coverage,Door I/L 1,Door I/L 2,Door I/L 3,Door I/L 4,Door I/L 5,Door I/L 6,Door I/L 7,Door I/L 8\r\n");
	
	if (nType == 0) { DeleteFile(strFile); return; }
	
	

	int		nSite;
	CString sSite, sLine, sModel;
	nSite = 5;  //C5
	sModel = gData.sRecipeElevLoad[eMZ::Load];
	sSite.Format("Gumi Campus %d Area", nSite);
	sLine.Format("Campus %d %s", nSite, sModel);

	int	   nNGTime;
	double dTime, dPer;
	if (nType == 1) 
	{
		if (gIt.nOpenStart == 1) {
			nNGTime = (GetTickCount() - gIt.dwOpenStartTime) / 1000;	//초단위
			gIt.nOpenTime = gIt.nOpenTime + nNGTime;
		}
		if (gIt.nOpenTime > 0) {
			if (gIt.nOpenTime > 3600) gIt.nOpenTime = 3600;
			dTime = gIt.nOpenTime / 60.0;	//분단위
			dPer = ((3600.0 - gIt.nOpenTime) / 3600.0) * 100.0;
			if (dPer > 100.0) dPer = 100.0;
		} else {
			dTime = 0.0; dPer = 100.0;
		}
		gIt.dwOpenStartTime = GetTickCount();
		gIt.nOpenTime = 0;
		gIt.nLogYY = time.wYear;
		gIt.nLogMM = time.wMonth;
		gIt.nLogDD = time.wDay;
		gIt.nLogHH = time.wHour;

		if (pEquipData->bUseDoorLock) sInterUse = "OK";
		else						  sInterUse = "NG";
	}
	if (nType == 2) {
		sInterUse = "NG";
		gIt.nOpenStart = 1;
		gIt.dwOpenStartTime = GetTickCount();
	}
	if (nType == 3) {
		sInterUse = "OK";
		gIt.nOpenStart = 0;
		nNGTime = (GetTickCount() - gIt.dwOpenStartTime) / 1000;
		gIt.nOpenTime = gIt.nOpenTime + nNGTime;
	}

	CFile file;
	if (!file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) return;

	try {
		file.SeekToEnd();

		if (file.GetLength() < 1) file.Write(sTitle, sTitle.GetLength());

		strSave1.Format("%s,%s,%s,,%s,MP,%s,%s,%s,%s", strTime, gData.sComName, strLotID, MAIN_VERSION, sSite, sLine, "SingleLens", gData.sOperID);
		if (nType == 1) strSave2.Format("A1,%s,%0.2lf,%d%%", sInterUse, dTime, int(dPer+0.5));
		if (nType == 2) strSave2.Format("F,NG,,");
		if (nType >= 3) strSave2.Format("A2,OK,,");

		DX_DATA_03 *pDX03 = g_objAJinAXL.Get_pDX03();
		
		if (pDX03->iDoor01Unlock) strDoor[0] = "Open"; else strDoor[0] = "Close";
		if (pDX03->iDoor02Unlock) strDoor[1] = "Open"; else strDoor[1] = "Close";
		if (pDX03->iDoor03Unlock) strDoor[2] = "Open"; else strDoor[2] = "Close";
		if (pDX03->iDoor04Unlock) strDoor[3] = "Open"; else strDoor[3] = "Close";
		if (pDX03->iDoor05Unlock) strDoor[4] = "Open"; else strDoor[4] = "Close";
		if (pDX03->iDoor06Unlock) strDoor[5] = "Open"; else strDoor[5] = "Close";
		if (pDX03->iDoor07Unlock) strDoor[6] = "Open"; else strDoor[6] = "Close";
		if (pDX03->iDoor08Unlock) strDoor[7] = "Open"; else strDoor[7] = "Close";
		

		strSave3.Format("%s,%s,%s,%s,%s,%s,%s,%s",    strDoor[0],  strDoor[1],  strDoor[2],  strDoor[3],  strDoor[4],  strDoor[5],  strDoor[6],  strDoor[7]);
		

		strSave.Format("%s,%s,%s\r\n", strSave1, strSave2, strSave3);
		file.Write(strSave, strSave.GetLength());
		file.Close();

	} catch (CFileException *pEx) {
		pEx->Delete();
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// v1.0.1.1 Test
void CLogFile::Save_JobListExcel(CString sLog)
{
	SYSTEMTIME time;
	GetLocalTime(&time);	
}



void CLogFile::Save_PCLog(int nPNo, CString sLog)
{
	CString strPath1 = "D:\\EVMS\\TP\\Log";
	CString strPath2 = "D:\\EVMS\\TP\\Backup";

	Create_Folder(strPath1);
	Create_Folder(strPath2);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile1, strFile2, strTitle, strTime, strPcName, strSave;
	strFile1.Format("%s\\%s_%04d%02d%02d%02d_PC.csv", strPath1, gData.sZigID[nPNo-1], time.wYear, time.wMonth, time.wDay, time.wHour);
	strFile2.Format("%s\\%s_%04d%02d%02d%02d_PC.csv", strPath2, gData.sZigID[nPNo-1], time.wYear, time.wMonth, time.wDay, time.wHour);

	CFile file;
	if (!file.Open(strFile1, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) return;

	strTitle.Format("Time,Station,LotID,ModuleConfig,CPU,RAM,HardDisk\r\n");

	try {
		file.SeekToEnd();

		if (file.GetLength() < 1) file.Write(strTitle, strTitle.GetLength());

		strTime.Format("%04d-%02d-%02d %02d:%02d:%02d:%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

		char szPcName[MAX_COMPUTERNAME_LENGTH + 1];
		DWORD dwNameSize = MAX_COMPUTERNAME_LENGTH + 1;
		GetComputerName(szPcName, &dwNameSize);

		strSave.Format("%s,%s,%s\r\n", strTime, szPcName, sLog);

		file.Write(strSave, strSave.GetLength());
		file.Close();

		CopyFile(strFile1, strFile2, FALSE);	// Backup

	} catch (CFileException *pEx) {
		pEx->Delete();
	}


}


void CLogFile::Save_BarcodeLog(const CString& sLog)
{
	CString strPath = gsCurrentDir + "\\LOG\\Barcode";
	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile, strSave;
	strFile.Format("%s\\%04d%02d%02d_Barcode.txt", strPath, time.wYear, time.wMonth, time.wDay);

	g_csBarcodeLog.Lock();
	
	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) {
		try {
			file.SeekToEnd();

			strSave.Format("%02d:%02d:%02d %03d,%s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}

	g_csBarcodeLog.Unlock();
}



void CLogFile::Save_MCCLog(const CString& sLog)
{
	g_csMCCLog.Lock();
	
	CString strPath = gsCurrentDir + "\\LOG\\MCC";
	CString strPath2 = "D:\\Dump\\MCC";

	Create_Folder(strPath);
	Create_Folder(strPath2);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile,strFile2, strSave;
	strFile.Format("%s\\%04d%02d%02d_MCC.txt", strPath, time.wYear, time.wMonth, time.wDay);
	strFile2.Format("%s\\%04d%02d%02d_MCC.txt", strPath2, time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			strSave.Format("[%02d:%02d:%02d.%03d], %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}

	CFile file2;
	if (file2.Open(strFile2, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file2.SeekToEnd();

			strSave.Format("[%02d:%02d:%02d.%03d],%s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

			file2.Write(strSave, strSave.GetLength());
			file2.Close();

		}
		catch (CFileException *pEx)
		{
			pEx->Delete();
		}
	}

	g_csMCCLog.Unlock();
}


void CLogFile::Save_LotTime(int nMZNo,const CString& sLog)
{
	CString strPath1 = "D:\\EVMS\\TP\\Log";
	CString strPath2 = "D:\\EVMS\\TP\\Backup";
	CString strPath3;

	Create_Folder(strPath1);
	Create_Folder(strPath2);

	SYSTEMTIME time;
	GetLocalTime(&time);

	strPath3 = gsCurrentDir + "\\LOG\\LotTime";
	Create_Folder(strPath3);

	CString strFile1, strFile2, strFile3, strTitle, strTime, strPcName, strSave;
	strFile1.Format("%s\\%s_%04d%02d%02d%02d_LOT_TIME.csv", strPath1, gData.sMZIDMainIdex[eMainIndex::Mark], time.wYear, time.wMonth, time.wDay, time.wHour);
	strFile2.Format("%s\\%s_%04d%02d%02d%02d_LOT_TIME.csv", strPath2, gData.sMZIDMainIdex[eMainIndex::Mark], time.wYear, time.wMonth, time.wDay, time.wHour);
	strFile3.Format("%s\\%s_%s_LOT_TIME.csv", strPath3, gLot.sStartTime[nMZNo-1], gData.sMZIDMainIdex[eMainIndex::Mark]);


	g_csLotTimeLog.Lock();

	CFile file;
	if (!file.Open(strFile1, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) 
	{
		g_objLogFile.Save_HandlerLog("LotTime Open Fail");
		return;
	}
	strTitle.Format("Time,Station,Machine,Version,LotID,MZID,Recipe,ZigID,TrayNo,LensNo,LensNo(AVI),Barcode,TC,BC,CODE,Result\r\n");

	try {
		file.SeekToEnd();

		if (file.GetLength() < 1) file.Write(strTitle, strTitle.GetLength());

		strTime.Format("'%04d-%02d-%02d %02d:%02d:%02d.%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

		char szPcName[MAX_COMPUTERNAME_LENGTH + 1];
		DWORD dwNameSize = MAX_COMPUTERNAME_LENGTH + 1;
		GetComputerName(szPcName, &dwNameSize);

		strSave.Format("%s,%s,%s\r\n", strTime, szPcName, sLog);

		file.Write(strSave, strSave.GetLength());
		file.Close();


	} catch (CFileException *pEx) {
		pEx->Delete();
	}



	CFile file2;
	if (!file2.Open(strFile2, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) 
	{
		g_objLogFile.Save_HandlerLog("LotTime Open Fail");
		return;
	}
	strTitle.Format("Time,Station,Machine,Version,LotID,MZID,Recipe,ZigID,TrayNo,LensNo,LensNo(AVI),Barcode,TC,BC,CODE,Result\r\n");

	try {
		file2.SeekToEnd();

		if (file2.GetLength() < 1) file2.Write(strTitle, strTitle.GetLength());

		strTime.Format("'%04d-%02d-%02d %02d:%02d:%02d.%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

		char szPcName[MAX_COMPUTERNAME_LENGTH + 1];
		DWORD dwNameSize = MAX_COMPUTERNAME_LENGTH + 1;
		GetComputerName(szPcName, &dwNameSize);

		strSave.Format("%s,%s,%s\r\n", strTime, szPcName, sLog);

		file2.Write(strSave, strSave.GetLength());
		file2.Close();
			

	} catch (CFileException *pEx) {
		pEx->Delete();
	}



	CFile file3;
	if (!file3.Open(strFile3, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) 
	{
		g_objLogFile.Save_HandlerLog("LotTime Open Fail");
		return;
	}
	strTitle.Format("Time,Station,Machine,Version,LotID,MZID,Recipe,ZigID,TrayNo,LensNo,LensNo(AVI),Barcode,TC,BC,CODE,Result\r\n");

	try {
		file3.SeekToEnd();

		if (file3.GetLength() < 1) file3.Write(strTitle, strTitle.GetLength());

		strTime.Format("'%04d-%02d-%02d %02d:%02d:%02d.%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

		char szPcName[MAX_COMPUTERNAME_LENGTH + 1];
		DWORD dwNameSize = MAX_COMPUTERNAME_LENGTH + 1;
		GetComputerName(szPcName, &dwNameSize);

		strSave.Format("%s,%s,%s\r\n", strTime, szPcName, sLog);

		file3.Write(strSave, strSave.GetLength());
		file3.Close();	

	} catch (CFileException *pEx) {
		pEx->Delete();
	}

	g_csLotTimeLog.Unlock();

}





void CLogFile::Save_StdMotionLog(CString sType, int nZone, int nCase, int nValue, CString sZone, CString sMsg)
{
	if (gData.sStdMotionFile.GetLength() < 10) return;

	g_csStdMotionLog.Lock();

	CString strPath = "D:\\EVMS\\TP\\LOGL";
	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile, strKey, strCycle, strTitle, strLog, strSave;

	// 파일명 : LotID_생성년월일시_공정명_Normal_#호기번호_PC이름_모델명_순번.csv => Lot Start시 생성
	strFile.Format("%s\\%s", strPath, gData.sStdMotionFile);

	strKey.Format("[CH_DV]%s%03d%03d[1]", sType, nZone, nCase);

	if (sType == "Y" && nValue == 1) strCycle = "";	// 선행동작 (시작시 공란)
	else strCycle.Format("%s%03d", sType, nCase-1);	// 선행동작 표시

	strLog.Format("%s,%d,%s,%s,%s", strKey, nValue, sZone, strCycle, sMsg);

	strTitle = "Time,Key,Value,Index,CycleIndex,Note\r\n";

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();
			if (file.GetLength() < 1) file.Write(strTitle, strTitle.GetLength());
			strSave.Format("%04d%02d%02d%02d%02d%02d.%03d,%s\r\n",
				time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, strLog);
			file.Write(strSave, strSave.GetLength());
			file.Close();
		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csStdMotionLog.Unlock();
}

void CLogFile::Save_EfficiencyLog(int nZone, CString sStatus, int nCode, CString sNote)
{
	if (gData.sEfficiencyFile.GetLength() < 10) return;

	g_csEfficiencyLog.Lock();

	CString strPath, strFile, strZone, strMsg, strTitle, strLog, strSave;

	strPath.Format("D:\\EVMS\\TP\\LOGL");
	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	//파일명 : LotID_생성년월일시_공정명_Efficiency_#호기번호_PC이름_모델명_순번.csv
	strFile.Format("%s\\%s", strPath, gData.sEfficiencyFile);

	if (nZone < 0) strZone = "None";
	else Get_ZoneMsg(nZone, 0, strZone, strMsg);

	strLog.Format("%s-%s-%04d,%s", sStatus, strZone, nCode, sNote);

	strTitle = "Time,Code,Comment\r\n";

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();
			if (file.GetLength() < 1) file.Write(strTitle, strTitle.GetLength());
			strSave.Format("%04d-%02d-%02d-%02d-%02d-%02d.%03d,%s\r\n",
				time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, strLog);
			file.Write(strSave, strSave.GetLength());
			file.Close();
		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csEfficiencyLog.Unlock();
}


void CLogFile::Get_ZoneMsg(int nZone, int nCase, CString &sZone, CString &sMsg)
{
	switch (nZone) {
	case 1:		
		sZone = "Load C/V";
		switch (nCase) 
		{
		case 1: sMsg = "Load Tray, Port check"; break;
		case 2: sMsg = "Tray X Move to Load Position"; break;
		}
		break;
	case 2:		
		sZone = "MZ Elevator";
		switch (nCase) {
		case 1: sMsg = "Z Cylinder Down"; break;
		case 2: sMsg = "Load Tray Slave Out"; break;		
		}
		break;
	case 3:		 
		sZone = "Zig Feeder";
		switch (nCase) {
		case 0: sMsg = "check angle port and angle inspection option"; break;
		case 1: sMsg = "Master out"; break;
		case 2: sMsg  ="Slave out"; break;	
		}
		break;
	case 4:		 
		sZone = "Zig Picker";
		switch (nCase) {
		case  1: sMsg = "Z Axis Move to Support Up Position or Wait Pos[S]"; break;
		case  2: sMsg = "Z Axis Move to Support Up Pos from Wait pos[S]";break;	
		}
		break;
	case 5:		 
		sZone = "LensCleaner";
		switch (nCase) {
		case  1: sMsg = "Z Axis Move to Support Up Position or Wait Pos[S]"; break;
		case  2: sMsg = "Z Axis Move to Support Up Pos from Wait pos[S]";break;		
		}
		break;
	case 6:		 
		sZone = "TopInspector";
		switch (nCase) 
		{
			case  1: sMsg = "Angle Tray Empty Checked"; break;
			case  2: sMsg = "Angle Tray Y & Btm1 Picker X Move to Pick Position"; break;		
		}
		break;
	case 7:		 
		sZone = "BtmInspector";
		switch (nCase) 
		{
			case  1: sMsg = "X Move to Module Align or Wait(Align) Position[S]"; break;
			case  2: sMsg = "Align Z Axis Down"; break;
		}
		break;
	case 8:		 
		sZone = "MarkUnit";
		switch (nCase) 
		{
			case  1: sMsg = "X Move to Module Align or Wait(Align) Position[S]"; break;		
		}
		break;
	case 9:		 
		sZone = "MainIndex";
		switch (nCase) 
		{
			case  1: sMsg = "X Move to Module Align or Wait(Align) Position[S]"; break;	
		}
		break;
	case 10:	 
		sZone = "Unload C/V";
		switch (nCase) 
		{
			case  1: sMsg = "Working Stage Number checked"; break;
		}
		break;

	}
}

