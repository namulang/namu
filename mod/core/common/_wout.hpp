#pragma once

#ifdef WIN32
#	undef _wout
#	ifdef  __namu = 1 // I'm currently building module
#		define _wout __declspec(dllexport)
#	else
#		define _wout __declspec(dllimport)
#	endif
#else
#	undef _wout
#	define _wout
#endif
