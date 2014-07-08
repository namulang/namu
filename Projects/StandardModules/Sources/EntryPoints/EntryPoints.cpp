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

		modulelist.push( NEBlockedModuleSet() );
		modulelist.push( NEBlockedNodeSet() );
		modulelist.push( Assign() );
		modulelist.push( AssignWith() );
		modulelist.push( BinaryLoader() );
		modulelist.push( BinarySaver() );
		modulelist.push( ElementExtractor() );
		modulelist.push( ElementInserter() );
		modulelist.push( ElementRemover() );
		modulelist.push( Enabler() );
		modulelist.push( ErrorSpy() );
		modulelist.push( Exactor() );
		modulelist.push( Extender() );
		modulelist.push( FileLister() );
		modulelist.push( ScriptFileLister() );
		modulelist.push( NodeFileLister() );
		modulelist.push( FrameCounter() );
		modulelist.push( GroupChanger() );
		modulelist.push( If() );
		modulelist.push( IfElse() );
		modulelist.push( Logic() );
		modulelist.push( LogicWith() );
		modulelist.push( For() );
		modulelist.push( NameChanger() );
		modulelist.push( NodeCreator() );
		modulelist.push( NodeRemover() );
		modulelist.push( PriorityChanger() );
		modulelist.push( Timer() );

		modulelist.push( BooleanStorer() );
		modulelist.push( CharStorer() );
		modulelist.push( WCharStorer() );
		modulelist.push( ByteStorer() );
		modulelist.push( ShortStorer() );
		modulelist.push( UShortStorer() );
		modulelist.push( IntStorer() );
		modulelist.push( UIntStorer() );
		modulelist.push( UByteStorer() );
		modulelist.push( FloatStorer() );
		modulelist.push( DoubleStorer() );
		modulelist.push( StringStorer() );
		modulelist.push( WStringStorer() );
		modulelist.push( Int64Storer() );
		modulelist.push( NodeSetStorer() );
		modulelist.push( ModuleSetStorer() );
		modulelist.push( BooleanSetStorer() );
		modulelist.push( ByteSetStorer() );
		modulelist.push( UByteSetStorer() );
		modulelist.push( ShortSetStorer() );
		modulelist.push( UShortSetStorer() );
		modulelist.push( IntSetStorer() );
		modulelist.push( UIntSetStorer() );
		modulelist.push( FloatSetStorer() );
		modulelist.push( DoubleSetStorer() );
		modulelist.push( StringSetStorer() );
		modulelist.push( WStringSetStorer() );
		modulelist.push( Int64SetStorer() );

		modulelist.push( FloatAging() );
		modulelist.push(MessageSender());
		modulelist.push(MessageReceiver());
		modulelist.push(KeyboardSpy());
		modulelist.push(ForEach());
		modulelist.push(ForNodeEach());
		modulelist.push(ForSystemModule());
		modulelist.push(ModuleInfoExtractor());
		modulelist.push(NodeCopier());
		modulelist.push(YourProject());
		modulelist.push(ManagedFloatAging());
		modulelist.push( Random() );
		modulelist.push( StateModule() );

		return modulelist;
	}
}
