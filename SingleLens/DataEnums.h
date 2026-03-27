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
		MZRight = 1,
		MZLeft = 2,
		Rail = 3,
	};
};


struct Feeder_Y
{
	enum dtName
	{
		Ready = 0,
		Sensing = 1,
		JigRight = 2,
		JigLeft = 3,
		Rail = 4,
	};
};



struct Tray_Picker_Y
{
	enum dtName
	{
		Ready = 0,
		Load = 1,
		MaxCnt,
	};
};



struct Tray_Picker_Z
{
	enum dtName
	{
		Ready = 0,
		Load = 1, 
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
	};
};



struct Marker_Y
{
	enum dtName
	{
		Ready = 0,
	};
};



struct Marker_Z
{
	enum dtName
	{
		Ready = 0,
	};
};



struct Btm_Index_Table_R
{
	enum dtName
	{
		Ready = 0,
	};
};


struct IndexT
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


struct LT
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