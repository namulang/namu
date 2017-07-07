//	---------------------------------------------------------------------------------
//	파일명	:	MacroSetDLLIMPORT.hpp
//	설명	:	NE에서 사용하는 DLL을 묵시적 연결(implicit linking)에 사용할때의 defi
//				ne. DLL 프로젝트는 MSVS에서 자동으로 _USRDLL가 정의 되므로 이것을 이용
//				했다. 
//	메모	:
//	히스토리:	2011-02-08	이태훈	작성
//				2011-05-29	이태훈	개발 완료
//	---------------------------------------------------------------------------------
//	pragma once가 없어야 한다.

//	include:
#include "CommonDefine.hpp"

//	define:
#ifdef NE_DLL
#	undef NE_DLL
#endif

#define NE_DLL _declspec(dllimport)
