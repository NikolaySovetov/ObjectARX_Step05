//-----------------------------------------------------------------------------
//----- EmployeeDetails.cpp : Implementation of EmployeeDetails
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "EmployeeDetails.h"

//-----------------------------------------------------------------------------
Adesk::UInt32 EmployeeDetails::kCurrentVersionNumber = 1;

//-----------------------------------------------------------------------------
ACRX_DXF_DEFINE_MEMBERS(
	EmployeeDetails, AcDbObject,
	AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent,
	AcDbProxyEntity::kNoOperation, EMPLOYEEDETAILS,
	EMPLOYEEDETAILSPROJAPP
	| Product Desc : A description for your object
	| Company : Your company name
	| WEB Address : Your company WEB site address
)

//-----------------------------------------------------------------------------
EmployeeDetails::EmployeeDetails() : AcDbObject() {
	m_nID = 0;
	m_nCube = 0;
	m_strFirstName = NULL; 
	m_strLastName = NULL;
}

EmployeeDetails::EmployeeDetails(const Adesk::Int32 ID, const Adesk::Int32 cube,
								 const TCHAR* firstName, const TCHAR* lastName) {
	this->SetID(ID);
	this->SetCube(cube);
	this->SetFirstName(firstName);
	this->SetLastName(lastName);
}

EmployeeDetails::~EmployeeDetails() {
}

//-----------------------------------------------------------------------------
//----- AcDbObject protocols
//- Dwg Filing protocol
Acad::ErrorStatus EmployeeDetails::dwgOutFields(AcDbDwgFiler * pFiler) const {
	assertReadEnabled();
	//----- Save parent class information first.
	Acad::ErrorStatus es = AcDbObject::dwgOutFields(pFiler);
	if (es != Acad::eOk)
		return (es);
	//----- Object version number needs to be saved first
	if ((es = pFiler->writeUInt32(EmployeeDetails::kCurrentVersionNumber)) != Acad::eOk)
		return (es);
	//----- Output params
	//.....

	// Write the data members
	pFiler->writeItem(m_nID);
	pFiler->writeItem(m_nCube);
	pFiler->writeItem(m_strFirstName);
	pFiler->writeItem(m_strLastName);

	return (pFiler->filerStatus());
}

Acad::ErrorStatus EmployeeDetails::dwgInFields(AcDbDwgFiler * pFiler) {
	assertWriteEnabled();
	//----- Read parent class information first.
	Acad::ErrorStatus es = AcDbObject::dwgInFields(pFiler);
	if (es != Acad::eOk)
		return (es);
	//----- Object version number needs to be read first
	Adesk::UInt32 version = 0;
	if ((es = pFiler->readUInt32(&version)) != Acad::eOk)
		return (es);
	if (version > EmployeeDetails::kCurrentVersionNumber)
		return (Acad::eMakeMeProxy);
	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//if ( version < EmployeeDetails::kCurrentVersionNumber )
	//	return (Acad::eMakeMeProxy) ;
	//----- Read params
	//.....

	// Read the data member
	switch (version) {
	case 1:
		pFiler->readItem(&m_nID);
		pFiler->readItem(&m_nCube);
		pFiler->readItem(&m_strFirstName);
		pFiler->readItem(&m_strLastName);
		break;
	}

	return (pFiler->filerStatus());
}

//- Dxf Filing protocol
Acad::ErrorStatus EmployeeDetails::dxfOutFields(AcDbDxfFiler * pFiler) const {
	assertReadEnabled();
	//----- Save parent class information first.
	Acad::ErrorStatus es = AcDbObject::dxfOutFields(pFiler);
	if (es != Acad::eOk)
		return (es);
	es = pFiler->writeItem(AcDb::kDxfSubclass, _RXST("EmployeeDetails"));
	if (es != Acad::eOk)
		return (es);
	//----- Object version number needs to be saved first
	if ((es = pFiler->writeUInt32(kDxfInt32, EmployeeDetails::kCurrentVersionNumber)) != Acad::eOk)
		return (es);
	//----- Output params
	//.....

	// Write out the data members
	pFiler->writeItem(AcDb::kDxfInt32, m_nID);
	pFiler->writeItem(AcDb::kDxfInt32 + 1, m_nCube);
	pFiler->writeItem(AcDb::kDxfXTextString, m_strFirstName);
	pFiler->writeItem(AcDb::kDxfXTextString + 1, m_strLastName);

	return (pFiler->filerStatus());
}

Acad::ErrorStatus EmployeeDetails::dxfInFields(AcDbDxfFiler * pFiler) {
	assertWriteEnabled();
	//----- Read parent class information first.
	Acad::ErrorStatus es = AcDbObject::dxfInFields(pFiler);
	if (es != Acad::eOk || !pFiler->atSubclassData(_RXST("EmployeeDetails")))
		return (pFiler->filerStatus());
	//----- Object version number needs to be read first
	struct resbuf rb;
	pFiler->readItem(&rb);
	if (rb.restype != AcDb::kDxfInt32) {
		pFiler->pushBackItem();
		pFiler->setError(Acad::eInvalidDxfCode, _RXST("\nError: expected group code %d (version #)"), AcDb::kDxfInt32);
		return (pFiler->filerStatus());
	}
	Adesk::UInt32 version = (Adesk::UInt32)rb.resval.rlong;
	if (version > EmployeeDetails::kCurrentVersionNumber)
		return (Acad::eMakeMeProxy);
	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//if ( version < EmployeeDetails::kCurrentVersionNumber )
	//	return (Acad::eMakeMeProxy) ;
	// 
	//----- Read params in non order dependant manner
	while (es == Acad::eOk && (es = pFiler->readResBuf(&rb)) == Acad::eOk) {
		switch (rb.restype) {
		case AcDb::kDxfInt32:
			m_nID = rb.resval.rlong;
			break;
		case AcDb::kDxfInt32 + 1:
			m_nCube = rb.resval.rlong;
			break;
		case AcDb::kDxfXTextString:
			if (m_strFirstName != NULL)
				free(m_strFirstName);
			m_strFirstName = _tcsdup(rb.resval.rstring);
			break;
		case AcDb::kDxfXTextString + 1:
			if (m_strLastName != NULL)
				free(m_strLastName);
			m_strLastName = _tcsdup(rb.resval.rstring);
			break;
		default:
			//----- An unrecognized group. Push it back so that the subclass can read it again.
			pFiler->pushBackItem();
			es = Acad::eEndOfFile;
			break;
		}
	}
	//----- At this point the es variable must contain eEndOfFile
	//----- - either from readResBuf() or from pushback. If not,
	//----- it indicates that an error happened and we should
	//----- return immediately.
	if (es != Acad::eEndOfFile)
		return (Acad::eInvalidResBuf);

	return (pFiler->filerStatus());
}

// ------------------------------------------------
Acad::ErrorStatus EmployeeDetails::SetID(const Adesk::Int32 cnID) {
	assertWriteEnabled();
	m_nID = cnID;

	return Acad::eOk;
}

Acad::ErrorStatus EmployeeDetails::GetID(Adesk::Int32 & nID) {
	assertReadEnabled();
	nID = m_nID;

	return Acad::eOk;
}

Acad::ErrorStatus EmployeeDetails::SetCube(const Adesk::Int32 cnCube) {
	assertWriteEnabled();
	m_nCube = cnCube;

	return Acad::eOk;
}

Acad::ErrorStatus EmployeeDetails::GetCube(Adesk::Int32 & nCube) {
	assertReadEnabled();
	nCube = m_nCube;

	return Acad::eOk;
}

Acad::ErrorStatus EmployeeDetails::SetFirstName(const TCHAR * pcstrFirstName) {
	assertWriteEnabled();
	if (m_strFirstName)
		free(m_strFirstName);
	m_strFirstName = _tcsdup(pcstrFirstName);

	return Acad::eOk;
}

Acad::ErrorStatus EmployeeDetails::GetFirstName(TCHAR * &pstrFirstName) {
	assertReadEnabled();
	pstrFirstName = m_strFirstName;

	return Acad::eOk;
}

Acad::ErrorStatus EmployeeDetails::SetLastName(const TCHAR * pcstrLastName) {
	assertWriteEnabled();
	if (m_strLastName)
		free(m_strLastName);
	m_strLastName = _tcsdup(pcstrLastName);

	return Acad::eOk;
}

Acad::ErrorStatus EmployeeDetails::GetLastName(TCHAR * &pstrLastName) {
	assertReadEnabled();
	pstrLastName = m_strLastName;

	return Acad::eOk;
}





