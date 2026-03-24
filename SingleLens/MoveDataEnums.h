#pragma once


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
	};
};



struct Top_Inspector_Y
{
	enum dtName
	{
		Ready = 0,
	};
};



struct Top_Inspector_Z
{
	enum dtName
	{
		Ready = 0,
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
