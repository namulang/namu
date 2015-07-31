#pragma once

#include "../Commons/EntryPointName.hpp"
#include "../Modules/Console.hpp"
#include "../Modules/ConsoleCommand.hpp"

#ifndef CONSOLE_EXPORTS
#	ifdef DEVELOPER
#		ifdef _DEBUG
#			ifdef _UNICODE
#				pragma comment(lib, "Console.dev.dbg.lib")
#			else
#				pragma comment(lib, "Console.dev.dbg.mbcs.lib")
#			endif
#		else
#			ifdef _UNICODE
#				pragma comment(lib, "Console.dev.lib")
#			else
#				pragma comment(lib, "Console.dev.mbcs.lib")
#			endif
#		endif
#	else
#		ifdef _UNICODE
#			pragma comment(lib, "Console.lib")
#		else
#			pragma comment(lib, "Console.mbcs.lib")
#		endif
#	endif
#endif
