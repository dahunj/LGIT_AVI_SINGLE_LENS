#pragma once

struct eLdCV_IO
{
	enum dtName
	{
		CW = 0,
		CCW = 1,
		Stop = 2,
	};
};

struct eLdCV_Stopper
{
	enum dtName
	{
		Up1 = 0,
		Down1 = 1,
		Up2 = 2,
		Down2 = 3,
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
		MZReady = 1,
		MZLoad = 2,
		LoadUp= 3,
	};
};


struct Feeder_Y
{
	enum dtName
	{
		Ready = 0,
		CheckExist = 1,
		Grip1 = 2,
		MZLoad = 3,
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
