//	---------------------------------------------------------------------------------
//	파일명	:	DebugMacro.hpp
//	설명	:	NEDebugManger를 이용해서 디버그 메세지를 출력한다.
//	관계	:	선언되야 하는 헤더.	#include "Kernal.hpp"
//	사용방법:	모든 메세지는 printf 타입의 문자열을 사용할 수 있다. 
//				또한 디버그모드에서만 컴파일되는 매크로도 있는 반면, 항상 출력되는
//				매크로 또한 존재한다.
//	메모	:	
//	히스토리:	2011-05-29	이태훈	개발 완료
//	---------------------------------------------------------------------------------
#pragma once

#ifdef DEVELOPER
#	define	KERNAL_ERROR(printf_string, ...)	\
	Kernal::getInstance().getDebugManager().alert(Kernal::getInstance().getHeader(), NEResult::LEVEL_ERROR, \
	_T("\n-----------------------------------------------------------")## \
	_T("\n")##_T(printf_string)## \
	_T("\n-----------------------------------------------------------")## \
	_T("\ndomain :\tKernal")## \
	_T("\ntype :\t\tError")## \
	_T("\nfunction :\t")##_T(__FUNCSIG__)## \
	_T("\nline :\t\t%d ")## \
	_T("\n")##_T(__FILE__)##_T("(%d)")## \
	_T("\n-----------------------------------------------------------\n"), \
	__VA_ARGS__, __LINE__, __LINE__);

#	define	KERNAL_WARNING(printf_string, ...)	\
	Kernal::getInstance().getDebugManager().alert(Kernal::getInstance().getHeader(), NEResult::LEVEL_WARNING, \
	_T("\n-----------------------------------------------------------")## \
	_T("\n")##_T(printf_string)## \
	_T("\n-----------------------------------------------------------")## \
	_T("\ndomain :\tKernal")## \
	_T("\ntype :\t\tWarning")## \
	_T("\nfunction :\t")##_T(__FUNCSIG__)## \
	_T("\nline :\t\t%d ")## \
	_T("\n")##_T(__FILE__)##_T("(%d)")## \
	_T("\n-----------------------------------------------------------\n"), \
	__VA_ARGS__, __LINE__, __LINE__);
	
#	define	KERNAL_INFORMATION(printf_string, ...)	\
	Kernal::getInstance().getDebugManager().alert(Kernal::getInstance().getHeader(), NEResult::LEVEL_INFORMATION, \
	_T("\n-----------------------------------------------------------")## \
	_T("\n")##_T(printf_string)## \
	_T("\n-----------------------------------------------------------")## \
	_T("\ndomain :\tKernal")## \
	_T("\ntype :\t\tInformation")## \
	_T("\nfunction :\t")##_T(__FUNCSIG__)## \
	_T("\nline :\t\t%d ")## \
	_T("\n")##_T(__FILE__)##_T("(%d)")## \
	_T("\n-----------------------------------------------------------\n"), \
	__VA_ARGS__, __LINE__, __LINE__);
	
#	define	ALERT_ERROR(printf_string, ...)	\
	Kernal::getInstance().getDebugManager().alert(getHeader(), NEResult::LEVEL_ERROR, \
	_T("\n-----------------------------------------------------------")## \
	_T("\n")##_T(printf_string)## \
	_T("\n-----------------------------------------------------------")## \
	_T("\ndomain :\tKernal")## \
	_T("\ntype :\t\tError")## \
	_T("\nfunction :\t")##_T(__FUNCSIG__)## \
	_T("\nline :\t\t%d ")## \
	_T("\n")##_T(__FILE__)##_T("(%d)")## \
	_T("\n-----------------------------------------------------------\n"), \
	__VA_ARGS__, __LINE__, __LINE__);
	
#	define	ALERT_WARNING(printf_string, ...)	\
	Kernal::getInstance().getDebugManager().alert(getHeader(), NEResult::LEVEL_WARNING, \
	_T("\n-----------------------------------------------------------")## \
	_T("\n")##_T(printf_string)## \
	_T("\n-----------------------------------------------------------")## \
	_T("\ndomain :\tKernal")## \
	_T("\ntype :\t\tWarning")## \
	_T("\nfunction :\t")##_T(__FUNCSIG__)## \
	_T("\nline :\t\t%d ")## \
	_T("\n")##_T(__FILE__)##_T("(%d)")## \
	_T("\n-----------------------------------------------------------\n"), \
	__VA_ARGS__, __LINE__, __LINE__);
	
#	define	ALERT_INFORMATION(printf_string, ...) \
	Kernal::getInstance().getDebugManager().alert(getHeader(), NEResult::LEVEL_INFORMATION, \
	_T("\n-----------------------------------------------------------")## \
	_T("\n")##_T(printf_string)## \
	_T("\n-----------------------------------------------------------")## \
	_T("\ndomain :\tKernal")## \
	_T("\ntype :\t\tInformation")## \
	_T("\nfunction :\t")##_T(__FUNCSIG__)## \
	_T("\nline :\t\t%d ")## \
	_T("\n")##_T(__FILE__)##_T("(%d)")## \
	_T("\n-----------------------------------------------------------\n"), \
	__VA_ARGS__, __LINE__, __LINE__);
	
#	define	ALERT_ERROR_IN_SPECIFIED_MODULE(identifier, printf_string, ...)	\
	Kernal::getInstance().getDebugManager().alert((identifier), NEResult::LEVEL_ERROR, \
	_T("\n-----------------------------------------------------------")## \
	_T("\n")##_T(printf_string)## \
	_T("\n-----------------------------------------------------------")## \
	_T("\ndomain :\tKernal")## \
	_T("\ntype :\t\tError")## \
	_T("\nfunction :\t")##_T(__FUNCSIG__)## \
	_T("\nline :\t\t%d ")## \
	_T("\n")##_T(__FILE__)##_T("(%d)")## \
	_T("\n-----------------------------------------------------------\n"), \
	__VA_ARGS__, __LINE__, __LINE__);
	
#	define	ALERT_WARNING_IN_SPECIFIED_MODULE(identifier, printf_string, ...)	\
	Kernal::getInstance().getDebugManager().alert((identifier), NEResult::LEVEL_WARNING, \
	_T("\n-----------------------------------------------------------")## \
	_T("\n")##_T(printf_string)## \
	_T("\n-----------------------------------------------------------")## \
	_T("\ndomain :\tKernal")## \
	_T("\ntype :\t\tWarning")## \
	_T("\nfunction :\t")##_T(__FUNCSIG__)## \
	_T("\nline :\t\t%d ")## \
	_T("\n")##_T(__FILE__)##_T("(%d)")## \
	_T("\n-----------------------------------------------------------\n"), \
	__VA_ARGS__, __LINE__, __LINE__);
	
#	define	ALERT_INFORMATION_IN_SPECIFIED_MODULE(identifier, printf_string, ...)	\
	Kernal::getInstance().getDebugManager().alert((identifier), NEResult::LEVEL_INFORMATION, \
	_T("\n-----------------------------------------------------------")## \
	_T("\n")##_T(printf_string)## \
	_T("\n-----------------------------------------------------------")## \
	_T("\ndomain :\tKernal")## \
	_T("\ntype :\t\tInformation")## \
	_T("\nfunction :\t")##_T(__FUNCSIG__)## \
	_T("\nline :\t\t%d ")## \
	_T("\n")##_T(__FILE__)##_T("(%d)")## \
	_T("\n-----------------------------------------------------------\n"), \
	__VA_ARGS__, __LINE__, __LINE__);
	
#	define ASSERT(expression)							\
	if(expression)										\
	{													\
		KERNAL_ERROR(#expression ## _T("is asserted!"))	\
		__asm int 3;									\
	}

#	define IS_NULL(ref, return_type)					\
	if( ! &ref)											\
	{													\
		KERNAL_WARNING(#expression ## _T(" is null!"))	\
		return return_type								\
	}
#	define IS_NULL(ref)									\
	if( ! &ref)											\
		return KERNAL_WARNING(#ref ## _T(" is null!"))

#else
#	define	ALERT_ERROR(printf_string, ...)				;
#	define	ALERT_WARNING(printf_string, ...)			;
#	define	ALERT_INFORMATION(printf_string, ...)		;
#	define	KERNAL_ERROR(printf_string, ...)			;
#	define	KERNAL_WARNING(printf_string, ...)			;
#	define	KERNAL_INFORMATION(printf_string, ...)		;
#	define	ASSERT(expression)							;
#endif
