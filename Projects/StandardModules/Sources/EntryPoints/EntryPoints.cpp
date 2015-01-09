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
		modulelist.push( ArgumentTagger() );
		modulelist.push( ArrTagger() );
		modulelist.push( BinaryFiler() );
		modulelist.push( BlockStatements() );
		modulelist.push( Children() );
		modulelist.push( For() );
		modulelist.push( ForEach() );
		modulelist.push( ForEachElement() );
		modulelist.push( If() );
		modulelist.push( Instancer() );
		modulelist.push( KeyboardSpy() );
		modulelist.push( KeySelectorTagger() );
		modulelist.push( KeyTagger() );
		modulelist.push( ModuleSelectorTagger() );
		modulelist.push( ModuleTagger() );
		modulelist.push( NodeSelectorTagger() );
		modulelist.push( NodeTagger() );
		modulelist.push( Random() );
		modulelist.push( Timer() );

		return modulelist;
	}
}
