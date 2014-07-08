#pragma once

#include "../Commons/EntryPointName.hpp"

#include "../Modules/NEBlockedModuleSet/NEBlockedModuleSet.hpp"
#include "../Modules/NEBlockedNodeSet/NEBlockedNodeSet.hpp"
#include "../Modules/Assign/Assign.hpp"
#include "../Modules/AssignWith/AssignWith.hpp"
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
#include "../Modules/LogicWith/LogicWith.hpp"
#include "../Modules/For/For.hpp"
#include "../Modules/NameChanger/NameChanger.hpp"
#include "../Modules/NodeCreator/NodeCreator.hpp"
#include "../Modules/NodeRemover/NodeRemover.hpp"
#include "../Modules/PriorityChanger/PriorityChanger.hpp"
#include "../Modules/Timer/Timer.hpp"
#include "../Modules/StorerTemplate/Templates/Templates.hpp"
#include "../Modules/AgingTemplate/Templates.hpp"
#include "../Modules/MessageSender/MessageSender.hpp"
#include "../Modules/MessageReceiver/MessageReceiver.hpp"
#include "../Modules/KeyboardSpy/KeyboardSpy.hpp"
#include "../Modules/ForEach/ForEach.hpp"
#include "../Modules/ForNodeEach/ForNodeEach.hpp"
#include "../Modules/ForSystemModule/ForSystemModule.hpp"
#include "../Modules/ModuleInfoExtractor/ModuleInfoExtractor.hpp"
#include "../Modules/NodeCopier/NodeCopier.hpp"
#include "../Modules/YourProject/YourProject.hpp"
#include "../Modules/ManagedAgingTemplate/Templates.hpp"
#include "../Modules/Random/Random.hpp"
#include "../Modules/StateModule/StateModule.hpp"

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
