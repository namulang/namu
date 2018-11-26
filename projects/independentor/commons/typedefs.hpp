//	---------------------------------------------------------------------------------
//	파일명	:	commonTypedef.hpp
//	설명	:	노드엔진에서 사용하는 타입 정의
//	메모	:	widx를 short int로 정의하면, 엔진 전체의 부하가 줄어드는 방식으
//				로 개발되는 것을 목표로 한다.
//	히스토리:	2011-05-29	이태훈	개발 완료
//	---------------------------------------------------------------------------------
#pragma once

namespace WRD
{
	typedef int 				wint;
	typedef unsigned int		wuint;
	typedef bool 				wbool;
	typedef char				wchar;
	typedef unsigned char		wuchar;
	typedef wchar_t				wwchar;
	typedef tchar				wtchar;
	typedef short int			wshort;
	typedef unsigned short int	wushort;
	typedef float				wfloat;
	typedef double				wdbl;
	typedef long				wlong;
	typedef unsigned long		wulong;

	typedef wint				widx;
	typedef wchar				wbyte;
	typedef wuchar				wubyte;
	typedef wulong				wid;
	typedef wint				wcnt;
}
