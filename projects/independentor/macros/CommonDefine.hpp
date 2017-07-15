//	---------------------------------------------------------------------------------
//	파일명	:	MacroCommonDefine.hpp
//	설명	:	NE에서 사용하는 define. Macro의 속해있다.
//	메모	:
//	히스토리:	2011-01-07	이태훈	작성
//				2011-05-29	개발 완료
//	---------------------------------------------------------------------------------
#pragma once

//	define:
//		calling convention:
#define NE_FUNCTION_CALL	__stdcall
#define NE_ENTRYPOINT_CALL	__stdcall

//		dll:
#ifdef _USRDLL
#	define NE_DLL __declspec(dllexport)
#else
#	define NE_DLL __declspec(dllimport)
#endif

//		custom type:
//			function part:
//				parameter part:
#define NE_IN	// 파라메터로 넘기는 값이다. NE_OUT과 차별을 두기 위해 만들었으나 실제로는 많이 사용되지 않는다
#define NE_OUT	// 보통 인자와 다르게 값이 변경되어서 나오는 변수다.

//			general:
#define NE_DEFAULT_FALSE					false
#define NE_DEFAULT_TRUE						true
#define NE_DEFAULT							0
#define NE_ERROR_0							0
#define NE_ERROR_MINUS1						-1
#define NE_ERROR_1							1
#define NE_DUMMY							0
#define NE_SUCCESS							0
#define NE_NULL								0x00
#define NE_NO_NAME							0
#define NE_LOCALE							"korean"
#define NE_FALSE							0
#define NE_TRUE								1
#define NE_INDEX_ERROR						-1
#define NE_HAS_NO_SCRIPTCODE				-1
#define NE_HAS_NO_ID						0
#define NE_MACRO_MAXIMUM_OF_ARGUMENT_COUNT	32
#define NE_VOID