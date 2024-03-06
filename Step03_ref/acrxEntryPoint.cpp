#include "StdAfx.h"
#include "resource.h"
#include "utilities.h"
#include "EmployeeDetails.h"

#pragma comment (lib ,"EmployeeDetailsProj.lib")

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

		// TODO: Add your initialization code here

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

	static void Step05_adddetail() {
		
		AcDbObject* pObject;
		if (GetRefObject(pObject, AcDb::kForRead)) {
			pObject->close();
		}


	}


};

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CStep03_refApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CStep03_refApp, Step03, _createLayer, createLayer, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CStep03_refApp, Step03, _createBlock, createBlock, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CStep03_refApp, Step03, _setLayer, setLayer, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CStep03_refApp, Step05, _adddetail, adddetail, ACRX_CMD_TRANSPARENT, NULL)




