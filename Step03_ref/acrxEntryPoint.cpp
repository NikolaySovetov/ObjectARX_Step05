#include "StdAfx.h"
#include "resource.h"
#include "utilities.h"

//-----------------------------------------------------------------------------
#define szRDS _RXST("")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CStep03_refApp : public AcRxArxApp {

public:
	CStep03_refApp() : AcRxArxApp() {}

	virtual AcRx::AppRetCode On_kInitAppMsg(void* pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode = AcRxArxApp::On_kInitAppMsg(pkt);

		// TODO: Add your initialization code here

		return (retCode);
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg(void* pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode = AcRxArxApp::On_kUnloadAppMsg(pkt);

		// TODO: Unload dependencies here

		return (retCode);
	}

	virtual void RegisterServerComponents() {
	}

	static void Step03_createLayer() {
		AcDbObjectId layerId = AcDbObjectId::kNull;
		const TCHAR* layerName{ L"USER" };
		
		UtilityCreator uc;
		uc.CreateLayer(layerName, layerId);
		if (layerId != AcDbObjectId::kNull) {
			acutPrintf(_T("\nlayer \"%s\" with ID \"%d\" created"), layerName, layerId);
		}
	}
};

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CStep03_refApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CStep03_refApp, Step03, _createLayer, createLayer, ACRX_CMD_TRANSPARENT, NULL)




