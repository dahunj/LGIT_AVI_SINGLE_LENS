#pragma once


struct eLensState
{
	enum eName
	{
		// 0:Empty,1:Good, 2:NG, 3:Top Ready, 4: Top Done, 5: Btm Ready, 6 : Btm Done,  9:Init 
		None = 0,
		TopReady = 1,
		TopDone = 2,
		BtmReady = 3,
		BtmDone = 4,
		MarkReady = 5,
		Marked = 6,
		NotMarked = 7,
		Init = 9,

	};
};


struct eLensInfo
{
	enum eName
	{
		// 0:Empty,1:Good, 2:NG, 3:Top Ready, 4: Top Done, 5: Btm Ready, 6 : Btm Done,  9:Init 
		Empty = 0,
		Good = 1,
		NG = 2,
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


struct eLT
{
	enum Name
	{
		Motion = 0,
		Scan = 1,
		CV = 2,		
		Wait = 3,
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
		Start = 1,
		LoadMZ = 3, 
		RdyMZ = 11,
		Working = 20,
		Unload = 31,
		SlideOver = 51, 
	};
};

struct eFeederBr
{
	enum Name
	{
		Ready = 0,
		LoadSearch = 1,
		RdySearch = 51,
		Unload = 30,
	};
};

struct eTrayPickerBr
{
	enum Name
	{
		Load = 1,
		Unload = 20,

	};
};

struct eTopBr
{
	enum Name
	{
		VisionWait = 5,
		Trigger = 6, 
	};
};

struct eBtmBr
{
	enum Name
	{
		VisionWait = 5,
		Trigger = 6, 
	};
};


struct MarkerBranch
{
	enum Name
	{
		VisionWait = 5,
	};
};

struct eLoadCVBr
{
	enum Name
	{
		Check = 0,
		Start = 1,
		ElvWait = 10,
	};
};

struct eUnloadCVBr
{
	enum Name
	{
		start = 1, 
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


struct eDelay
{
	enum Name
	{
		FeederGrip = 0,
		FeederUnGrip = 1,
		TrayPickGrip = 2,
		TrayPickUnGrip = 0,
		IndexAlignIn = 1,
		IndexAlignOut = 2,
	};

};


struct eVision
{
	enum Name
	{
		TC = 0,
		BC = 1,
		MARKING = 2,
	};

};


struct eVDir
{
	enum Name
	{
		fixX = 0,
		fixY = 1,
	};
};


struct eEquipState
{
	enum name
	{
		RUN = 1,
		IDLE_STARVED = 2,
		IDLE_BLOCKED = 3,
		IDLE = 4,
		DOWN = 5,
	};
};

struct eMZBuffer
{
	enum name
	{
		Load = 0,
		Ready = 1,
		LoadCV1 = 2,
		LoadCV2 = 3,
		LoadCV3 = 4,
		LoadCV4 = 5, 
	};
};