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

Acad::ErrorStatus UtilityCreator::SetLayer(const TCHAR* blockName, const TCHAR* layerName)
{
	AcDbBlockTable* pBTable;

	// 1 Open the block table of the current working database
	if ((mErrStat =
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBTable, AcDb::kForRead)) !=
		Acad::eOk)
	{
		acedAlert(L"\nCan't open Block Table.");
		return mErrStat;
	}

	// 2 Get the MODEL_SPACE block table record
	AcDbBlockTableRecord* pBTRecord;
	mErrStat = pBTable->getAt(ACDB_MODEL_SPACE, pBTRecord, AcDb::kForRead);
	pBTable->close();

	if (mErrStat != Acad::eOk)
	{
		acedAlert(L"\nCan't get Block Table Record.");
		return mErrStat;
	}

	// 3 Obtain a block table record iterator
	AcDbBlockTableRecordIterator* pBTRIterator;
	mErrStat = pBTRecord->newIterator(pBTRIterator, Adesk::kTrue, Adesk::kTrue);
	pBTRecord->close();

	if (mErrStat != Acad::eOk)
	{
		acedAlert(L"\nCan't obtain Block Table Record Iterator.");
		return mErrStat;
	}

	// 4 Itrerate through the MODEL_SPACE
	TCHAR* currentBlockName;
	AcDbEntity* pEntity;
	AcDbObjectId blockId;

	for (pBTRIterator->start(); !pBTRIterator->done(); pBTRIterator->step())
	{
		// 5 Open object for read
		if (pBTRIterator->getEntity(pEntity, AcDb::kForRead, Adesk::kFalse) != Acad::eOk)
		{
			acedAlert(L"\nCan't open object.");
			continue;
		}

		// 6 Check if the entity is a block reference
		if (pEntity->isA() != AcDbBlockReference::desc())
		{
			pEntity->close();
			continue;
		}

		// 7 Obtain the block table record of the reference and check it name
		blockId = (AcDbBlockReference::cast(pEntity))->blockTableRecord();

		if (acdbOpenObject(/*(AcDbObject*&)*/pBTRecord, blockId, AcDb::kForRead) == Acad::eOk) 
		{
			pBTRecord->getName(currentBlockName);
			if (_tcscmp(currentBlockName, blockName) == 0) 
			{
				if (pEntity->upgradeOpen() == Acad::eOk)
					pEntity->setLayer(layerName);
			}
			pBTRecord->close();
			acdbFree(currentBlockName);
		}
		pEntity->close();
	}
	
	return mErrStat;
}

//------------------------------------------------------------------------------
Acad::ErrorStatus Employee::AddEmployee(AcDbBlockTableRecord* pBTRecord)
{
	AcDbCircle* pFace = new AcDbCircle(AcGePoint3d::kOrigin, AcGeVector3d::kZAxis, 1.0);
	AcDbCircle* pLeftEye = new AcDbCircle(AcGePoint3d(0.33, 0.25, 0), AcGeVector3d::kZAxis, 0.1);
	AcDbCircle* pRightEye = new AcDbCircle(AcGePoint3d(-0.33, 0.25, 0), AcGeVector3d::kZAxis, 0.1);
	AcDbArc* pMouth = new AcDbArc({ 0.0, 0.5, 0 }, AcGeVector3d::kZAxis, 1.0,
		(pi + (pi * 0.3)), (pi + (pi * 0.7)));

	pFace->setColorIndex(2);
	pLeftEye->setColorIndex(5);
	pRightEye->setColorIndex(5);
	pMouth->setColorIndex(1);

	AddEntities(pBTRecord, { pFace, pLeftEye, pRightEye, pMouth });

	return mErrStat;
}

void Employee::AddEntities(AcDbBlockTableRecord* pBTRecord,
	const std::initializer_list<AcDbEntity*>& Entities)
{
	size_t i{ 0 };

	for (const auto ent : Entities)
	{
		if ((mErrStat = pBTRecord->appendAcDbEntity(ent)) != Acad::eOk)
		{
			break;
		}
		ent->close();
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





