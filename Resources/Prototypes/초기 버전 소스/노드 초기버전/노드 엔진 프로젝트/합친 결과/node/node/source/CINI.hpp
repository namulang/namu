/*
	파일명:	CINI.hpp
	이름:	INI 로더
	기능:	시스템 설정(그래픽, 사운드, 버전) && 게임옵션 을 관리
*/

#pragma once
//	선언:
//		기본 인클루드:
#include <Windows.h>
#include <tchar.h>
#include <atlstr.h> // CString을 API에서 사용하기위해
//		커스텀 인클루드:
#include "CError.hpp"
#include "define.hpp"
//		전역변수 선언:
extern	CINI	g_ini;
//	정의:
//		클래스:
class CINI
{
//	멤버 함수:
public:
	//	생성자:
	CINI();
	//	소멸자:
	~CINI();
	//	접근자:	
	//		실좌표:
	int		getScreenWidth();
	int		getScreenHeight();
	//		셰이더:
	float	getShaderWidth();
	float	getShaderHeight();
	//	디폴트:
	//		전체:
	void	setDefaultVeryLow(); // 베리 로우 옵 (안전모드)		
	//		셰이더:
	void	setDefaultVeryLowShader();
	


//	멤버변수:
public:	
	//	그래픽:
	//		사용자 설정: (config)
	bool	_graphic_window_mode; // directx를 윈도우 모드로?	
	int		_graphic_width; // 해상도
	int		_graphic_height; // 해상도
	bool	_graphic_vertical_synchronize; // 수직동기화	
	bool	_graphic_32colorbit; // 32비트로 동작하는가
	bool	_grpahic_32bit_texture;
	bool	_graphic_isShaderOn; // 하드웨어적으로 불가능하거나 || 셰이더를 끈경우
	//		하드웨어 정보: (info)
	bool	_info_hardware_shader_support; // 하드웨어가 셰이더를 지원하는지 정보만 제공함

//	개인변수:
private:
	//	그래픽:
	//		화면 비율:
	WINDOW_RATIO	_graphic_ratio;
	//		세이더:
	SHADER_QUALITY	_graphic_shader_quality;
};