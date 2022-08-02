//  ---------------------------------------------------------------------------------
//  파일명  :   NEMaroMemoryLeak.hpp
//  설명    :   메모리리킹 현상을 감지해서 디버그창에 알려준다
//  메모    :   디버그모드에서만(_DEBUG) 사용된다.
//  히스토리:   2011-01-07  이태훈  작성
//              2011-05-29  이태훈  개발 완료
//  ---------------------------------------------------------------------------------
#pragma once

#ifdef _DEBUG

//  include:
#   include <crtdbg.h>

//  define:
#   define CRTDBG_MAP_ALLOC
#   define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

//      macro:  다음 매크로를 프로그램이 시작하는 함수 최상단에 사용한다
//              메모리누수 메세지는 디버그창에 나옴
#   define NAMU_MEMORYLEAK _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#else
#   define NAMU_MEMORYLEAK
#endif
