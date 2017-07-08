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
#include "BuildInformation.hpp"
#include "CommonTypedef.hpp"
#include "CommonDefine.hpp" // 공통 type
#include "MemoryLeak.hpp" // 메모리누수 검출 매크로.
#include "ArgumentCounter.hpp"
#include "ArgumentGetter.hpp"
#include "Overloader.hpp"
#include "ForEach.hpp"
#include "Helpers.hpp"
#include "Funnel.hpp"
