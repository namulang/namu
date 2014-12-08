#include "Headers.hpp"

BOOL APIENTRY DllMain( 
						HMODULE hModule,
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
	NEModuleList _declspec(dllexport) _stdcall _EXECUTE_ENTRYPOINT
	{		
		NEModuleList modulelist;

		modulelist.push( Ager() );
		modulelist.push( ALU() );
		modulelist.push( BinaryFiler() );
		modulelist.push( ArrElementer() );
		modulelist.push( If() );
		return modulelist;
	}
}
