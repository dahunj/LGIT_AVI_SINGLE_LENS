#pragma once


struct LensState
{
	enum eName
	{
		// 0:Empty,1:Good, 2:NG, 3:Top Ready, 4: Top Done, 5: Btm Ready, 6 : Btm Done,  9:Init 
		nothing = 0,
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

struct Conveyor_X
{
	enum dtName
	{
		Ready = 0,
	};
};



struct MZ_Elev_Z
{
	enum dtName
	{
		Ready = 0,
		Bottom = 1,
		Top = 2,
		JigPitch = 3, 
	};
};


struct Feeder_X
{
	enum dtName
	{
		Ready = 0,
		MZ1 = 1,
		MZ2 = 2,
		PickUp = 3,
	};
};


struct Feeder_Y
{
	enum dtName
	{
		Ready = 0,
		CheckExist = 1,
		Grip1 = 2,
		Grip2 = 3,
		PickUp = 4,
	};
};



struct Tray_Picker_Y
{
	enum dtName
	{
		Ready = 0,
		Rail = 1,
		Index = 2,
		MaxCnt,
	};
};



struct Tray_Picker_Z
{
	enum dtName
	{
		Ready = 0,
		
		Rail = 1, 
		Index = 2,
	};
};



struct Top_Inspector_X
{
	enum dtName
	{
		Ready = 0,
		ScanStart = 1,
	};
};



struct Top_Inspector_Y
{
	enum dtName
	{
		Ready = 0,
		ScanStart = 1,
	};
};



struct Top_Inspector_Z
{
	enum dtName
	{
		Ready = 0,
		ScanStart = 1,
	};
};



struct Btm_Inspector_X
{
	enum dtName
	{
		Ready = 0,
	};
};



struct Btm_Inspector_Y
{
	enum dtName
	{
		Ready = 0,
	};
};



struct Btm_Inspector_Z
{
	enum dtName
	{
		Ready = 0,
		
	};
};




struct Marker_X
{
	enum dtName
	{
		Ready = 0,
		LeftTop = 1,
	};
};



struct Marker_Y
{
	enum dtName
	{
		Ready = 0,
		LeftTop = 1,
	};
};



struct Marker_Z
{
	enum dtName
	{
		Ready = 0,
		LeftTop = 1,
		Mark = 2,
	};
};



struct Btm_Index_Table_R
{
	enum dtName
	{
		Ready = 0,
	};
};


struct MainIndex
{
	enum JobName
	{
		Load = 0,
		Clean = 1,
		Top = 2,
		None= 3,
		Btm = 4,
		Mark = 5,
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

struct ElevBranch
{
	enum Name
	{
		name = 0, 
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



struct eMZIdx
{
	enum Name
	{
		Load = 0,
		Ready = 1,
		CV1 = 2,
		CV2 = 3,
		CV3 = 4,
		CV4 = 5, 
	};
};