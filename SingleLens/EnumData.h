#pragma once


struct eLensState
{
	enum eName
	{
		// 0:Empty,1:Good, 2:NG, 3:Top Ready, 4: Top Done, 5: Btm Ready, 6 : Btm Done,  9:Init 
		None = 0,
		Good = 1,
		NG = 2,
		TopReady = 3,
		TopDone = 4,
		BtmReady = 5,
		BtmDone = 6,
		Marked = 7, 
		Init = 9,

	};
};


struct eMainIndex
{
	enum JobName
	{
		Load = 0,
		Clean = 1,
		Top = 2,
		None= 3,
		Btm = 4,
		Mark = 5,
		Unload = 6,
	};

};


struct LoopTime
{
	enum Name
	{
		Motion = 0,
		Scan = 1,
		Wait = 2,
	};
};


struct SpeedMode
{
	enum Name
	{
		Fast = 0,
		Normal = 1,
		Slow = 2,
	};
};


//seq branch 

struct MainIndexBranch
{
	enum Name
	{
		name = 0,
		CheckInOut = 5,
		
	};
};

struct ElvBranch
{
	enum Name
	{
		Load = 0,
		Work = 1,
		LoadMZ = 3, 
		RdyMZ = 11,
		Unload = 31,
		SlideOver = 51, 
	};
};

struct FeederBranch
{
	enum Name
	{
		Ready = 0,
		LoadSearch = 1,
		Unload = 30,
	};
};

struct ZigPickBranch
{
	enum Name
	{
		Load = 1,
		Unload = 20,

	};
};

struct TopBranch
{
	enum Name
	{
		VisionWait = 5,
	};
};

struct BtmBranch
{
	enum Name
	{
		VisionWait = 5,
	};
};


struct MarkerBranch
{
	enum Name
	{
		VisionWait = 5,
	};
};

struct delay
{
	enum Name
	{
		InspectionWait = 5,

	};

};



struct eMZ
{
	enum Name
	{
		Load = 0,
		Ready = 1,
		Unload = 2,
	};
};