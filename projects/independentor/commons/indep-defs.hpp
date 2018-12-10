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
#define WRD_FUNCTION_CALL	__stdcall
#define WRD_ENTRYPOINT_CALL	__stdcall

//		dll:
#ifdef _USRDLL
#	define WRD_DLL __declspec(dllexport)
#else
#	define WRD_DLL __declspec(dllimport)
#endif

//		custom type:
//			function part:
//				parameter part:
#define WRD_IN	// 파라메터로 넘기는 값이다. WRD_OUT과 차별을 두기 위해 만들었으나 실제로는 많이 사용되지 않는다
#define WRD_OUT	// 보통 인자와 다르게 값이 변경되어서 나오는 변수다.

//			general:
#define WRD_DEFAULT_FALSE		false
#define WRD_DEFAULT_TRUE			true
#define WRD_DEFAULT				0
#define WRD_ERROR_0				0
#define WRD_ERROR_MINUS1			-1
#define WRD_ERROR_1				1
#define WRD_DUMMY				0
#define WRD_SUCCESS				0
#define WRD_NULL					0x00
#define WRD_NO_NAME				0
#define WRD_LOCALE				"korean"
#define WRD_FALSE				0
#define WRD_TRUE					1
#define WRD_INDEX_ERROR			-1
#define WRD_HAS_NO_SCRIPTCODE	-1
#define WRD_HAS_NO_ID			0
#define WRD_MAX_ARGCNT			32
#define WRD_VOID

#ifdef UNICODE
    #define tchar wchar_t
    #define tmain wmain
    #define tcslen wcslen
    #define tcscat wcscat
    #define tcscpy wcscpy
    #define tcsncpy wcsncpy
    #define tcscmp wcscmp
    #define tcsncmp wcsncmp
    #define tprintf wprintf
    #define tscanf wscanf
    #define fgetts fgetws
    #define fputts fputws
#else
    #define tchar char
    #define tcslen strlen
    #define tcscat strcat
    #define tcscpy strcpy
    #define tcsncpy strncpy
    #define tcscmp strcmp
    #define tcsncmp strncmp
    #define tprintf printf
    #define tscanf scanf
    #define fgetts fgets
    #define fputts fputs
#endif

//	macros:
#define WRD_UNCONST_THIS()			This* unconst = const_cast<This*>(this);

#define WRD_INHERIT_2(THIS, SUPER)	\
		WRD_INHERIT_1(THIS)	\
	public:	\
		typedef SUPER Super;	\
	private:
#define WRD_INHERIT_1(THIS)	\
	public:	\
		typedef THIS This;	\
	private:
#define WRD_INHERIT(...)	WRD_OVERLOAD(WRD_INHERIT, __VA_ARGS__)

///	the macro for definining lazymethod which will be initialized when it's called.
//	this's uses static variable inside of method.
#define WRD_LAZY_METHOD_4(ReturnType, Name, isConst, initValue)	\
	isConst ReturnType& Name() isConst {	\
		static ReturnType inner(initValue);	\
		return inner;	\
	}
#define WRD_LAZY_METHOD_3(ReturnType, Name, initValue)	\
	WRD_LAZY_METHOD_4(ReturnType, Name, const, initValue)
#define WRD_LAZY_METHOD(...)	WRD_OVERLOAD(WRD_LAZY_METHOD, __VA_ARGS__)
