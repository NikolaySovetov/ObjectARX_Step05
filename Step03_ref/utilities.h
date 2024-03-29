#pragma once
#include "StdAfx.h"
#include "EmployeeDetails.h"
#include <initializer_list>

#pragma comment (lib ,"EmployeeDetailsProj.lib")

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

class Dictionary {
protected:
	AcDbDictionary* m_pDictionary{};

public:
	~Dictionary();
	AcDbDictionary* Get(AcDb::OpenMode mode = AcDb::kForRead);
};

class ExtensionDict : public Dictionary {
public:
	ExtensionDict();
	ExtensionDict(AcDbObject*& pObject);
};

class EmployeeDict : public Dictionary {
public:
	EmployeeDict(const TCHAR* strDictName);
	EmployeeDict(AcDbDictionary* pExtDict, const TCHAR* strDictName);
};

void AddDetails(const TCHAR* strDictName, const TCHAR* strRecordName);
void RemoveDetails(const TCHAR* strDictName, const TCHAR* strRecordName);
void ListDetails(const TCHAR* strDictName, const TCHAR* strRecordName);






