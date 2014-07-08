#pragma once

#include "../Commons/EntryPoint.hpp"

#include "../Modules/Assigner/Assigner.hpp"
#include "../Modules/BinaryLoader/BinaryLoader.hpp"
#include "../Modules/BinarySaver/BinarySaver.hpp"
#include "../Modules/ElementExtractor/ElementExtractor.hpp"
#include "../Modules/ElementInserter/ElementInserter.hpp"
#include "../Modules/ElementRemover/ElementRemover.hpp"
#include "../Modules/Enabler/Enabler.hpp"
#include "../Modules/ErrorSpy/ErrorSpy.hpp"
#include "../Modules/Exactor/Exactor.hpp"
#include "../Modules/Extender/Extender.hpp"
#include "../Modules/FileLister/FileLister.hpp"
#include "../Modules/ScriptFileLister/ScriptFileLister.hpp"
#include "../Modules/NodeFileLister/NodeFileLister.hpp"
#include "../Modules/FrameCounter/FrameCounter.hpp"
#include "../Modules/GroupChanger/GroupChanger.hpp"
#include "../Modules/If/If.hpp"
#include "../Modules/IfElse/IfElse.hpp"
#include "../Modules/Logic/Logic.hpp"
#include "../Modules/Looper/Looper.hpp"
#include "../Modules/NameChanger/NameChanger.hpp"
#include "../Modules/NodeCreator/NodeCreator.hpp"
#include "../Modules/NodeRemover/NodeRemover.hpp"
#include "../Modules/PriorityChanger/PriorityChanger.hpp"
#include "../Modules/Timer/Timer.hpp"
#include "../Modules/StorerTemplate/Templates/Templates.hpp"

#ifndef StandardModule_EXPORTS
#	ifdef DEVELOPER
#		ifdef _DEBUG
#			ifdef _UNICODE
#				pragma comment(lib, "../../../binary/Developer.Debug/module.dev.dbg/StandardModule.dev.dbg.lib")
#			else
#				pragma comment(lib, "../../../binary/Developer.Debug.Mbcs/module.dev.dbg.mbcs/StandardModule.dev.dbg.mbcs.lib")
#			endif
#		else
#			ifdef _UNICODE
#				pragma comment(lib, "../../../binary/Developer.Release/module.dev/StandardModule.dev.lib")
#			else
#				pragma comment(lib, "../../../binary/Developer.Release.Mbcs/module.dev.mbcs/StandardModule.dev.mbcs.lib")
#			endif
#		endif
#	else
#		ifdef _UNICODE
#			pragma comment(lib, "../../../binary/Release/Modules/StandardModule.lib")
#		else
#			pragma comment(lib, "../../../binary/Release.Mbcs/module.mbcs/StandardModule.mbcs.lib")
#		endif
#	endif
#endif
