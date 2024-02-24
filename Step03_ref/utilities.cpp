#include "StdAfx.h"
#include "utilities.h"

void UtilityCreator::CreateLayer(const ACHAR* layerName, AcDbObjectId& layerId) {

	// 1 Get the layer table from the current working database
	AcDbLayerTable* pLTable;

	mErrStat = acdbHostApplicationServices()->workingDatabase()->getLayerTable(pLTable, AcDb::kForRead);
	
	if (mErrStat != Acad::ErrorStatus::eOk) {
		acedAlert(L"\nError: Can't get the current layer table");
	}

	// 2 Check to see if a layer of the same name already exists
	if (pLTable->getAt(layerName, layerId, Adesk::kFalse) != Acad::ErrorStatus::eKeyNotFound) {
		acedAlert(L"\nWarning: The layer is exists");
		return;
	}

	// 3 Create new layer
	AcDbLayerTableRecord* pLayer = new AcDbLayerTableRecord;
	pLayer->setName(layerName);

	// 3.1 Add and close
	if (pLTable->upgradeOpen() != Acad::ErrorStatus::eOk) {
		acedAlert(L"\nError: Can't open layer table.");
		delete pLayer;
		return;
	}
	pLTable->add(pLayer);
	pLayer->close();
	pLTable->close();
}

void UtilityCreator::CreateBlockRecord(const ACHAR* blockName) const {
	
}



