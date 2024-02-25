#include "StdAfx.h"
#include "utilities.h"

Acad::ErrorStatus UtilityCreator::CreateLayer(const TCHAR* layerName, AcDbObjectId& layerId)
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
			// 3 Create new Layer Table Record
			AcDbLayerTableRecord* pLTRecord = new AcDbLayerTableRecord;
			pLTRecord->setName(layerName);
			pLTRecord->setLineWeight(AcDb::LineWeight::kLnWt025);

			// 3.1 Open for write 
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

Acad::ErrorStatus UtilityCreator::CreateBlockRecord(const TCHAR* blockName)
{
	AcDbBlockTable* pBTable;
	AcDbBlockTableRecord* pBTRecord;

	// 1 Get the block table from the current working database
	if ((mErrStat =
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBTable, AcDb::kForRead)) ==
		Acad::eOk)
	{
		// 2 Check of the block table record already exists
		if (pBTable->has(blockName) == Adesk::kTrue)
		{
			return Acad::eDuplicateKey;
		}
		// 3 Create new Block Table Record
		pBTRecord = new AcDbBlockTableRecord;
		pBTRecord->setName(blockName);
		pBTRecord->setOrigin(AcGePoint3d::kOrigin);

		// 3.1 Add BlockTableRecord to BlockTable
		if ((mErrStat = pBTable->upgradeOpen()) == Acad::eOk)
		{
			mErrStat = pBTable->add(pBTRecord);
			//acutPrintf(_T("\nmErrStat (62): %d"), mErrStat);
		}
		else
		{
			delete pBTRecord;
		}
		pBTable->close();
	}

	if (mErrStat != Acad::eOk)
	{
		return mErrStat;
	}

	// 4 Create EMPLOYEE entities and append them to the Block Table Record
	/*	Note: After having been added to the database, an object or an entity
		is implicitely opened for write		*/
	Employee emp;
	mErrStat = emp.AddEmployee(pBTRecord);

	pBTRecord->close();

	return mErrStat;
}

Acad::ErrorStatus Employee::AddEmployee(AcDbBlockTableRecord* pBTRecord)
{
	AcDbCircle* pFace = new AcDbCircle(AcGePoint3d::kOrigin, AcGeVector3d::kZAxis, 1.0);
	AcDbCircle* pLeftEye = new AcDbCircle(AcGePoint3d( 0.33, 0.25, 0 ), AcGeVector3d::kZAxis, 0.1);
	AcDbCircle* pRightEye = new AcDbCircle(AcGePoint3d( -0.33, 0.25, 0 ), AcGeVector3d::kZAxis, 0.1);
	AcDbArc* pMouth = new AcDbArc({ 0.0, 0.5, 0 }, AcGeVector3d::kZAxis, 1.0,
		(pi + (pi * 0.3)), (pi + (pi * 0.7)));

	pFace->setColorIndex(2);
	pLeftEye->setColorIndex(5);
	pRightEye->setColorIndex(5);
	pMouth->setColorIndex(1);

	pBTRecord->appendAcDbEntity(pFace);
	pBTRecord->appendAcDbEntity(pLeftEye);
	pBTRecord->appendAcDbEntity(pRightEye);
	pBTRecord->appendAcDbEntity(pMouth);

	//AddEntities(pBTRecord, { pFace, pLeftEye, pRightEye, pMouth });

	return mErrStat;
}

void Employee::AddEntities(AcDbBlockTableRecord* pBTRecord,
	const std::initializer_list<AcDbEntity*>& Entities)
{
	size_t i{ 0 };

	for (const auto item : Entities)
	{
		if ((mErrStat = pBTRecord->appendAcDbEntity(item)) != Acad::eOk)
		{
			break;
		}
		++i;
	}

	if (mErrStat != Acad::eOk)
	{
		const size_t size = Entities.size();
		auto pEntity = Entities.begin();
		for (; i < size; ++i)
		{
			delete pEntity[i];
		}
		pBTRecord->erase();
	}
}





