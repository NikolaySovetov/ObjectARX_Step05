#pragma once
#include "StdAfx.h"

class UtilityCreator {
private:
	Acad::ErrorStatus mErrStat;

public:
	void CreateLayer(const ACHAR* layerName, AcDbObjectId& layerId);
	void CreateBlockRecord(const ACHAR* blockName) const;

};



