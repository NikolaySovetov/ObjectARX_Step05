#pragma once
#include "StdAfx.h"
#include <initializer_list>
#include <memory>


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

class UtilityCreator {
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

//class Dictionary {
//protected:
//	AcDbDictionary* m_pDictionary{};
//	bool m_initFlag{};
//
//public:
//	~Dictionary();
//	AcDbDictionary* Get(AcDb::OpenMode mode = AcDb::kForRead);
//};

class ExtensionDictionary {
private:
	AcDbDictionary* m_pDictionary{};
	bool m_initFlag{};

public:
	ExtensionDictionary();
	~ExtensionDictionary();
	AcDbDictionary* Get(AcDb::OpenMode mode = AcDb::kForRead);
};

class EmployeeDictionary {
private:
	AcDbDictionary* m_pDictionary{};
	bool m_initFlag{};

public:
	EmployeeDictionary();
	~EmployeeDictionary();
	AcDbDictionary* Get(AcDb::OpenMode mode = AcDb::kForRead);
};

bool GetRefObject(AcDbObject*& pObject, AcDb::OpenMode mode);








