#pragma once

#ifdef DEVELOPER
#	ifdef _DEBUG
#		define	_EXECUTE_ENTRYPOINT	registerModuleDevDbg()
#	else
#		define	_EXECUTE_ENTRYPOINT	registerModuleDev()
#	endif
#else
#	define	_EXECUTE_ENTRYPOINT		registerModule()
#endif
