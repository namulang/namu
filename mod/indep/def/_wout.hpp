#pragma once

#ifdef WIN32
#	undef _wout
#	ifdef  indep = 1 // I'm currently building indep module
#		define _wout __declspec(dllexport)
#	else
#		define _wout __declspec(dllimport)
#	endif
#else
#	undef _wout
#	define _wout
#endif