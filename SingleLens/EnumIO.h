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

struct eUldCV_IO
{
	enum dtName
	{
		CW = 0,
		CCW = 1,
		Stop = 2,
	};
};


struct eLdCVStpr
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


struct eElvStpr
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


struct eCleanerIO
{
	enum dtName
	{
		TopDn = 0,
		TopUp = 1,
		TopFwd = 2,
		TopBwd = 3,
		BtmDn = 4,
		BtmUp = 5,
		BtmFwd = 6,
		BtmBwd = 7, 
	};
};


struct eMarkUnit
{
	enum dtName
	{
		PenIn = 0,
		PenOut = 1,		
	};
};


struct eIndexIO
{
	enum dtName
	{
		AlignIn = 0,
		AlignOut = 1,		
	};
};