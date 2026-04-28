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

struct eElevIO
{
	enum dtName
	{
		CW = 0,
		CCW = 1,
		Stop = 2, 
	};
};

struct eElevStopper 
{
	enum dtName
	{
		Up1 = 0,
		Down1 = 1,
		In1 = 2,
		Out1 = 3,
		Up2 = 4,
		Down2 = 5,
		In2 = 6,
		Out2 = 7, 
	};
};


struct eElev_Z
{
	enum dtName
	{
		Ready = 0,
		Down = 1,
		Up = 2,		
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
		PickerUp= 3,
	};
};

struct eFeeder_Y
{
	enum dtName
	{
		Ready = 0,		
		MZReady = 1,
		MZLoad = 2,
		PickerUp = 3,
	};
};

struct eFeeder_IO
{
	enum dtName
	{
		GripOpen = 0,
		GripClose = 1,
		RailAlignIn = 2,
		RailAlignOut = 3,
		ExistInFeeder = 4,
		ExistOnRail = 5,
		ExistInMZ = 6,
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
		Index = 2,
	};
};


struct ePicker_IO
{
	enum dtName
	{
		MasterIn = 0,
		MasterOut = 1,
		SlaveIn = 2,
		SlaveOut = 3,	
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
