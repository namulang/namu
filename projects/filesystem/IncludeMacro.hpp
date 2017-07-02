//	---------------------------------------------------------------------------------
//	파일명	:	IncludeMacro.hpp
//	설명	:	Macro 패키지를 import 한다.
//	메모	:	Macro는 dll의 형태가 아니므로 헤더파일만 import 한다.
//	히스토리:	2011-05-29	이태훈	개발 완료
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#ifndef BUILD_TARGET_FILESYSTEM
#   include "../macro/SetDLLIMPORT.hpp"
#endif
#include "../macro/Headers.hpp" // 내부에서 NE_DLL_PREV_STATUS 정의
#include "../macro/SetDLLEXPORT.hpp"