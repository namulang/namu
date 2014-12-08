#pragma once

#include "../Commons/EntryPointName.hpp"
#include "../Modules/Ager.hpp"
#include "../Modules/ALU.hpp"
#include "../Modules/BinaryFiler.hpp"
#include "../Modules/ArrElement.hpp"
#include "../Modules/If.hpp"

#ifndef StandardModule_EXPORTS
#	ifdef DEVELOPER
#		ifdef _DEBUG
#			ifdef _UNICODE
#				pragma comment(lib, "StandardModule.dev.dbg.lib")
#			else
#				pragma comment(lib, "StandardModule.dev.dbg.mbcs.lib")
#			endif
#		else
#			ifdef _UNICODE
#				pragma comment(lib, "StandardModule.dev.lib")
#			else
#				pragma comment(lib, "StandardModule.dev.mbcs.lib")
#			endif
#		endif
#	else
#		ifdef _UNICODE
#			pragma comment(lib, "StandardModule.lib")
#		else
#			pragma comment(lib, "StandardModule.mbcs.lib")
#		endif
#	endif
#endif
