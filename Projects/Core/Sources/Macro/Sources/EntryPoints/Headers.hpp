//	---------------------------------------------------------------------------------
//	DLL명	:	Macro.hpp
//	설명	:	노드엔진에서 가장 기본적으로 필요로하게 되는 선언을 정의한다
//	관계	:	노드엔진 전반에 사용되며, 특히 FileSystem에 직접적으로 사용된다.
//	특성	:	선언으로만 이루어져 있다.
//	외부포함:	디버그모드(_DEBUG)에서 crtdbg.h
//	클래스	:	
//	메모	:	
//	history	:	2011-05-29	이태훈	개발 완료
//				2016-06-01	kniz	added.
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../Commons/CommonTypedef.hpp"
#include "../Commons/CommonDefine.hpp" // 공통 type
#include "../Modules/MemoryLeakMacro/MemoryLeak.hpp" // 메모리누수 검출 매크로.
#include "../Modules/ArgumentCounter/ArgumentCounter.hpp"
#include "../Modules/ArgumentGetter/ArgumentGetter.hpp"
#include "../Modules/MacroOverloader/MacroOverloader.hpp"
#include "../Modules/ForEach/ForEach.hpp"
#include "../Modules/Helpers/Helpers.hpp"
#include "../Modules/Funnel/Funnel.hpp"
