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

void CLogFile::Save_JobListLog(CString sLog, BOOL bMode)
{
	g_csJobListLog.Lock();

	CString strPath = gsCurrentDir + "\\LOG\\JobList";

	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString sTitle, strFile, strSave;
	sTitle.Format("Time,lotNum,Start_Time,End_Time,Run_Time,Tray_Count,CM_Count,Tack,Good_Count,NG_Count,NG1_Count,NG2_Count,MESNG_Count\r\n");
	strFile.Format("%s\\%04d%02d%02d_JobList.txt", strPath, time.wYear, time.wMonth, time.wDay);

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

	if (bMode == TRUE) Save_ECMLog(2, sLog);
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


void CLogFile::Save_ECMLog(int nType, CString strLog)	//nType:1[Alarm], 2[Joblist] 3[Inspect]
{
	g_csECMLog.Lock();

	CString strFile, strFile2, sTitle, strTime, strSave;

	CString strPath = "D:\\EVMS\\TP\\Log\\";
	CString strPath2 = "D:\\EVMS\\TP\\Backup\\";

	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);
	strTime.Format("%04d-%02d-%02d %02d:%02d:%02d:%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

	

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


	/*if (gLot.sLotID == "") gLot.sLotID = "LOT_ID";
	strFile.Format("%s\\%s_AVITracking.csv", strPath, gLot.sLotID);*/

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
	CString strPath, strFile, sTitle, sTitle1, strTime, strSave, strSave1, strSave2, strSave3, strSave4, strLotID, strDoor[13];
		
	strPath = "D:\\EVMS\\TP\\Log\\";
	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);
	
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
	strFile1.Format("%s\\%s_%04d%02d%02d%02d_LOT_TIME.csv", strPath1, gData.sMZID[nMZNo-1], time.wYear, time.wMonth, time.wDay, time.wHour);
	strFile2.Format("%s\\%s_%04d%02d%02d%02d_LOT_TIME.csv", strPath2, gData.sMZID[nMZNo-1], time.wYear, time.wMonth, time.wDay, time.wHour);
	strFile3.Format("%s\\%s_LOT_TIME.csv", strPath3, gData.sMZID[nMZNo-1]);

	CFile file;
	if (!file.Open(strFile1, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) return;

	strTitle.Format("Time,Station,Machine,Version,ZigID,TrayNo,LensNo,Barcode,TC,BC,CODE,Result\r\n");

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

		CopyFile(strFile1, strFile2, FALSE);	// Backup
		CopyFile(strFile1, strFile3, FALSE);	// SPC

	} catch (CFileException *pEx) {
		pEx->Delete();
	}
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
