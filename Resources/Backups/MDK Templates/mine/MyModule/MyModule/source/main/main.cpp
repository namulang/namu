#include "header.hpp"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

namespace NE
{

#if PROPERTY_EXPORT_EXECUTE_MODULE == 1
	NEModuleList _declspec(dllexport) _stdcall _EXECUTE_ENTRYPOINT
	{		
		NEModuleList modulelist;

		modulelist.push( MyModule() );

		return modulelist;
	}
#endif

#if PROPERTY_EXPORT_PANEL == 1
	NEPanelList _declspec(dllexport) _stdcall _PANEL_ENTRYPOINT
	{
		NEPanelList panellist;

		panellist.push( MyModulePanel() );

		return panellist;
	}
#endif
}
