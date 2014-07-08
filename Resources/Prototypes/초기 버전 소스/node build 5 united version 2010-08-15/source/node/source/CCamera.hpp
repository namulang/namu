/*
	파일명:	CCamera.hpp
	이름:	카메라 클래스
	기능:	개체들을 지정한 영역에, 축소/확대하여 렌더링함			
*/
#pragma once
//	선언:
//		커스텀 인클루드:
#include "define.hpp"
#include "CArgb.hpp"
#include "CFilterData.hpp"
#include "CBlurFilterData.hpp" // #필터#추가#
#include "CNoiseFilterData.hpp"
#include "CBloomFilterData.hpp"
//	정의:
//		클래스:
class CCamera
{
//	멤버함수:
public:	
	//	생성자:
	CCamera();
	CCamera(float x, float y, float z, float angle, float scale_x, float scale_y, CArgb argb, bool preserve, char render_state);
	//	소멸자:
	~CCamera();
	//	필터검색:
	bool	isThereEnabledFilter();
	void	setRenderState(char render_state);
	char	getRenderState();
	void	initializeRenderState();
	bool	isPreserved();



//	개인함수:
private:
	//	초기화:
	void	initializeFilterData();



//	멤버변수:
public:	
	//	카메라 속성:		
	float	_angle,
			_x, _y, _z,
			_scale_x, _scale_y;	
	bool	_render_state_setted;
	CArgb	_argb;
	bool	_preserve;
	bool	_enable;
	//	필터:
	CFilterData*	_filter_data[DEFAULT_CSHADER_FILTER_NUMBER];	

private:
	char	_render_state;	
};