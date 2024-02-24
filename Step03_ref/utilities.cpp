#include "StdAfx.h"
#include "utilities.h"

Acad::ErrorStatus UtilityCreator::CreateLayer(const ACHAR* layerName, AcDbObjectId& layerId)
{
	// 1 Get the layer table from the current working database
	AcDbLayerTable* pLTable;

	if ((mErrStat = 
		acdbHostApplicationServices()->workingDatabase()->getLayerTable(pLTable, AcDb::kForRead)) == 
		Acad::eOk)
	{
		// 2 Check to see if a layer of the same name already exists
		if ((mErrStat = pLTable->getAt(layerName, layerId, Adesk::kFalse)) != Acad::eOk)
		{
			// 3 Create Layer Table Record
			AcDbLayerTableRecord* pLTRecord = new AcDbLayerTableRecord;
			pLTRecord->setName(layerName);
			pLTRecord->setLineWeight(AcDb::LineWeight::kLnWt025);

			if ((mErrStat = pLTable->upgradeOpen()) == Acad::eOk)
			{
				pLTable->add(layerId, pLTRecord);
				pLTRecord->close();
			}
			else 
			{
				delete pLTRecord;
			}
		}
		pLTable->close();
	}

	return mErrStat;
}

Acad::ErrorStatus UtilityCreator::CreateBlockRecord(const ACHAR* blockName) const
{
	return Acad::eOk;
}



