//-----------------------------------------------------------------------------
//----- EmployeeDetails.h : Declaration of the EmployeeDetails
//-----------------------------------------------------------------------------
#pragma once

#ifdef EMPLOYEEDETAILSPROJ_MODULE
#define DLLIMPEXP __declspec(dllexport)
#else
//----- Note: we don't use __declspec(dllimport) here, because of the
//----- "local vtable" problem with msvc. If you use __declspec(dllimport),
//----- then, when a client dll does a new on the class, the object's
//----- vtable pointer points to a vtable allocated in that client
//----- dll. If the client dll then passes the object to another dll,
//----- and the client dll is then unloaded, the vtable becomes invalid
//----- and any virtual calls on the object will access invalid memory.
//-----
//----- By not using __declspec(dllimport), we guarantee that the
//----- vtable is allocated in the server dll during the ctor and the
//----- client dll does not overwrite the vtable pointer after calling
//----- the ctor. And, since we expect the server dll to remain in
//----- memory indefinitely, there is no problem with vtables unexpectedly
//----- going away.
#define DLLIMPEXP
#endif

//-----------------------------------------------------------------------------
#include "dbmain.h"
#define EMPLOYEEDETAILS_DBXSERVICE _T("EMPLOYEEDETAILS_DBXSERVICE")
//-----------------------------------------------------------------------------
class DLLIMPEXP EmployeeDetails : public AcDbObject {
private:
	Adesk::Int32 m_nID;
	Adesk::Int32 m_nCube;
	TCHAR* m_strFirstName;
	TCHAR* m_strLastName;

public:
	ACRX_DECLARE_MEMBERS(EmployeeDetails) ;

protected:
	static Adesk::UInt32 kCurrentVersionNumber ;

public:
	EmployeeDetails () ;
	EmployeeDetails (const Adesk::Int32 ID, const Adesk::Int32 cube,
					 const TCHAR* firstName, const TCHAR* lastName) ;
	virtual ~EmployeeDetails () ;

	//----- AcDbObject protocols
	//- Dwg Filing protocol
	virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler *pFiler) const ;
	virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler *pFiler) ;

	//- Dxf Filing protocol
	virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler *pFiler) const ;
	virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler *pFiler) ;

	// ------------------------------------------------
public:
	Acad::ErrorStatus SetID(const Adesk::Int32 ID);
	Acad::ErrorStatus GetID(Adesk::Int32& ID);
	Acad::ErrorStatus SetCube(const Adesk::Int32 cube);
	Acad::ErrorStatus GetCube(Adesk::Int32& cube);  
	Acad::ErrorStatus SetFirstName(const TCHAR* firstName);
	Acad::ErrorStatus GetFirstName(TCHAR*& firstName);
	Acad::ErrorStatus SetLastName(const TCHAR* lastName);
	Acad::ErrorStatus GetLastName(TCHAR*& lastName);

} ;

#ifdef EMPLOYEEDETAILSPROJ_MODULE
ACDB_REGISTER_OBJECT_ENTRY_AUTO(EmployeeDetails)
#endif
