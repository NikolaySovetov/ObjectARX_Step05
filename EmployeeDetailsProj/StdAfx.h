//-----------------------------------------------------------------------------
//- StdAfx.h : include file for standard system include files,
//-      or project specific include files that are used frequently,
//-      but are changed infrequently
//-----------------------------------------------------------------------------
#pragma once
#define EMPLOYEEDETAILSPROJ_MODULE

/*#ifndef
#define _ALLOW_RTCc_IN_STL
#endif*/

#pragma pack(push, 8)
#pragma warning(disable : 4786 4996)
    //#pragma warning(disable: 4098)

    //-----------------------------------------------------------------------------
#include <windows.h>

    //- ObjectARX and OMF headers needs this
#include <map>
#include <tchar.h>

                //-----------------------------------------------------------------------------
    //- Include ObjectDBX/ObjectARX headers
    //- Uncomment one of the following lines to bring a given library in your project.
    //#define _BREP_SUPPORT_					//- Support for the BRep API
    //#define _HLR_SUPPORT_						//- Support for the Hidden Line Removal API
    //#define _AMODELER_SUPPORT_				//- Support for the AModeler API
    #include "dbxHeaders.h"
    
                        #pragma pack(pop)

    