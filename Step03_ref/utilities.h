#pragma once
#include "StdAfx.h"

class UtilityCreator {
private:
	Acad::ErrorStatus mErrStat;

public:
	void CreateLayer(const TCHAR* layerName, AcDbObjectId& layerId);
	void CreateBlockRecord(const TCHAR* blockName) const;

};



