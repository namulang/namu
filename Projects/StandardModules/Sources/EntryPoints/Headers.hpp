#pragma once

#include "../Commons/EntryPointName.hpp"
#include "../Modules/Ager.hpp"
#include "../Modules/ALU.hpp"
#include "../Modules/ArgumentTagger.hpp"
#include "../Modules/ArrTagger.hpp"
#include "../Modules/BinaryFiler.hpp"
#include "../Modules/BlockStatements.hpp"
#include "../Modules/Children.hpp"
#include "../Modules/For.hpp"
#include "../Modules/ForEach.hpp"
#include "../Modules/ForEachElement.hpp"
#include "../Modules/FileLister.hpp"
#include "../Modules/If.hpp"
#include "../Modules/Instancer.hpp"
#include "../Modules/KeyboardSpy.hpp"
#include "../Modules/KeySelectorTagger.hpp"
#include "../Modules/KeyTagger.hpp"
#include "../Modules/ModuleSelectorTagger.hpp"
#include "../Modules/ModuleTagger.hpp"
#include "../Modules/NodeSelectorTagger.hpp"
#include "../Modules/NodeTagger.hpp"
#include "../Modules/Random.hpp"
#include "../Modules/Timer.hpp"
#include "../Modules/SLU.hpp"

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
