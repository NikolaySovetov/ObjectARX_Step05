#pragma once
#include "StdAfx.h"

class UtilityCreator 
{
private:
	Acad::ErrorStatus mErrStat;

public:
	Acad::ErrorStatus
		CreateLayer(const ACHAR* layerName, AcDbObjectId& layerId);
	Acad::ErrorStatus
		CreateBlockRecord(const ACHAR* blockName) const;

};



