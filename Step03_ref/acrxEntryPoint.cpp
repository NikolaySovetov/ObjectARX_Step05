#include "StdAfx.h"
#include "resource.h"
#include "utilities.h"

//-----------------------------------------------------------------------------
#define szRDS _RXST("")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CStep03_refApp : public AcRxArxApp
{
public:
	CStep03_refApp() : AcRxArxApp()
	{}

	virtual AcRx::AppRetCode On_kInitAppMsg(void* pkt)
	{
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode = AcRxArxApp::On_kInitAppMsg(pkt);

		AcRxObject* pSvc;
		if (!(pSvc = acrxServiceDictionary->at(EMPLOYEEDETAILS_DBXSERVICE)))
		{
			// Try to load the module, if it is not yet present 
			if (!acrxDynamicLinker->loadModule(_T("EmployeeDetailsProj.dbx"), 0))
			{
				acutPrintf(_T("Unable to load EmployeeDetailsProj.dbx. Unloading this application...\n"));
				return (AcRx::kRetError);
			}
		}

		return (retCode);
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg(void* pkt)
	{
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode = AcRxArxApp::On_kUnloadAppMsg(pkt);

		// TODO: Unload dependencies here

		return (retCode);
	}

	virtual void RegisterServerComponents()
	{
	}

	static void Step03_createLayer()
	{
		AcDbObjectId layerId;
		const TCHAR* layerName(L"USER");

		UtilityCreator uc;
		if (uc.CreateLayer(layerName, layerId) == Acad::eOk)
		{
			applyCurDwgLayerTableChanges();
			acutPrintf(_T("\nLayer \"%s\" created"), layerName);
		}
	}

	static void Step03_createBlock()
	{
		const TCHAR* blockName{ L"Employee" };
		UtilityCreator uc;

		if (uc.CreateBlockRecord(blockName) == Acad::eOk)
		{
			acutPrintf(_T("\nBlock Record \"%s\" created"), blockName);
		}
		else
		{
			acutPrintf(_T("\nCan't create \"%s\""), blockName);
		}
	}

	static void Step03_setLayer()
	{
		const TCHAR* blockName{ L"Employee" };
		const TCHAR* layerName{ L"USER" };
		UtilityCreator uc;

		if (uc.SetLayer(blockName, layerName) == Acad::eOk)
		{
			acutPrintf(_T("\nSet Layer \"%s\" for \"%s\"."), layerName, blockName);
		}
	}

	static void Step05_addDetail() {
		AddDetails(L"EMPLOYEE_DICTIONARY", L"DETAILS");
	}

	static void Step05_removeDetail() {
		RemoveDetails(L"EMPLOYEE_DICTIONARY", L"DETAILS");
	}

	static void Step05_listDetail() {
		ListDetails(L"EMPLOYEE_DICTIONARY", L"DETAILS");
	}
};

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CStep03_refApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CStep03_refApp, Step03, _createLayer, createLayer, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CStep03_refApp, Step03, _createBlock, createBlock, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CStep03_refApp, Step03, _setLayer, setLayer, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CStep03_refApp, Step05, _addDetail, addDetail, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CStep03_refApp, Step05, _removeDetail, removeDetail, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CStep03_refApp, Step05, _listDetail, listDetail, ACRX_CMD_TRANSPARENT, NULL)




