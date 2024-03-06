#pragma once
#include "StdAfx.h"
#include <initializer_list>

class Employee
{
private:
	Acad::ErrorStatus mErrStat;
	const double pi{ 3.141592654 };

private:
	void AddEntities(AcDbBlockTableRecord* pBTRecord,
		const std::initializer_list<AcDbEntity*>& vEntity);



public:
	Acad::ErrorStatus
		AddEmployee(AcDbBlockTableRecord* pBTRecord);

};

class UtilityCreator
{
private:
	Acad::ErrorStatus mErrStat;

public:

	Acad::ErrorStatus
		CreateLayer(const TCHAR* layerName, AcDbObjectId& layerId);

	Acad::ErrorStatus
		CreateBlockRecord(const TCHAR* blockName);

	Acad::ErrorStatus
		SetLayer(const TCHAR* blockName, const TCHAR* layerName);
};

inline bool GetRefObject(AcDbObject*& pObject, AcDb::OpenMode mode) {
	ads_name entytiName;
	ads_point entityPoint;

	if (acedEntSel(L"Select employee", entytiName, entityPoint) != RTNORM) {
		return false;
	}

	AcDbObjectId objectID;
	if (acdbGetObjectId(objectID, entytiName) != Acad::eOk) {
		return false;
	}

	if (acdbOpenAcDbObject(pObject, objectID, mode) != Acad::eOk) {
		return false;
	}

	if (!pObject->isKindOf(AcDbBlockReference::desc())) {
		pObject->close();
		return false;
	}

	return true;
}


