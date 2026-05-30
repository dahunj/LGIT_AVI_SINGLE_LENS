#pragma once

struct eElv_Z
{
	enum dtName
	{
		FromLdCV = 0,
		Down = 1,
		ToUldCV = 2,		
		Pitch = 3,
		PitchMinus = 4,
			
	};
};

struct eElevReady_Z
{
	enum dtName
	{
		Ready = 0,
		Down = 5,
		Up = 6,		
		Pitch = 7,
		PitchMinus = 8,
	};
};

struct eFeeder_X
{
	enum dtName
	{
		Ready = 0,
		MZReady = 1,
		MZLoad = 2,
		TrayGrip= 3,
	};
};

struct eFeeder_Y
{
	enum dtName
	{
		Ready = 0,		
		MZReady = 1,
		MZLoad = 2,
		TrayGrip = 3,
	};
};


struct eZigPicker_Y
{
	enum dtName
	{
		Ready = 0,
		Load = 1,
		Index = 2,
		MaxCnt,
	};
};

struct eZigPicker_Z
{
	enum dtName
	{
		Ready = 0,
		LoadDown = 1, 
		IndexLoad = 2,
		IndexUnload = 3,
	};
};



struct eTopInspect_X
{
	enum dtName
	{
		Ready = 0,
		ScanStart = 1,
		PitchP = 2,
		PitchM = 3,
	};
};

struct eTopInspect_Y
{
	enum dtName
	{
		Ready = 0,
		ScanStart = 1,
		PitchP = 2,
		PitchM = 3,
	};
};

struct eTopInspect_Z
{
	enum dtName
	{
		Ready = 0,
		ScanStart = 1,
		ScanEnd = 2,
		Scan = 3,
	};
};



struct eBtmInspect_X
{
	enum dtName
	{
		Ready = 0,
		ScanStart = 1,
		PitchP = 2,
		PitchM = 3,
	};
};



struct eBtmInspect_Y
{
	enum dtName
	{
		Ready = 0,
		ScanStart = 1,
		PitchP = 2,
		PitchM = 3,
	};
};



struct eBtmInspect_Z
{
	enum dtName
	{
		Ready = 0,
		ScanStart = 1,
		ScanEnd = 2,
		Scan = 3,
	};
};




struct eMark_X
{
	enum dtName
	{
		Ready = 0,
		MarkStart = 1,
		PitchP = 2,
		PitchM = 3,
	};
};



struct eMark_Y
{
	enum dtName
	{
		Ready = 0,
		MarkStart = 1,
		PitchP = 2,
		PitchM = 3,
	};
};



struct eMark_Z
{
	enum dtName
	{
		Ready = 0,
		MarkStart = 1,
		MarkDown = 2,
		Dummy = 3,
	};
};



struct eIndex_R
{
	enum dtName
	{
		Ready = 0,
		MoveP = 1,
		MoveM = 2,
	};
};
