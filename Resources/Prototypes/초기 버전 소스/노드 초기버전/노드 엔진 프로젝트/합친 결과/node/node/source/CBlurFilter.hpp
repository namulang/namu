/*
	파일명:	CBlurFilter.hpp
	이름:	블러 필터
	기능:	카메라클래스와 연동해서, 카메라가 찍은 대상에만 블러를 먹인다.
	메모:	셰이더 퀄리티가 올라가는 경우, 덜 흐릿하게 보인다. 
*/
#pragma once
//	선언:
//		기본 인클루드:
#include <d3d9.h>
//		커스텀 인클루드:
#include "CFilter.hpp"
#include "define.hpp"
#include "CBlurFilterData.hpp"
#include "CFilterData.hpp"
//	정의:
//		클래스:
class CBlurFilter : public CFilter
{
//	멤버함수:
public:	
	//	생성자:
	CBlurFilter(LPDIRECT3DDEVICE9 device, UINT render_target_width, UINT render_target_height);	
	//	소멸자:	
	virtual ~CBlurFilter();
	//	초기화:
	virtual void	initializeShader(LPDIRECT3DDEVICE9 device);
	virtual void	initializeHLSLValue(LPDIRECT3DDEVICE9 device);
	void	initializeResource(LPDIRECT3DDEVICE9 device);
	//	해제:
	void	releaseResource();
	//	실행: 메인 함수
	virtual void	excute(LPDIRECT3DDEVICE9 device, LPDIRECT3DTEXTURE9 texture, LPDIRECT3DVERTEXBUFFER9 vertex_buffer, CCamera* camera);
	//	캐스팅변환:
	CBlurFilterData*	casting(CFilterData* filter_data);
	//	변수 업데이트:
	void	update(CBlurFilterData* blur_filter_data);
	void	updateBlurLevel(CBlurFilterData* blur_filter_data);
	//	필터링:	
	void	filtering(LPDIRECT3DDEVICE9 device, LPDIRECT3DTEXTURE9 texture, LPDIRECT3DVERTEXBUFFER9 vertex_buffer, CCamera* camera);



//	개인변수:
private:
	//	핸들:
	D3DXHANDLE	_blur_level_width_handle;
	D3DXHANDLE	_blur_level_height_handle;
	//	리소스:
	LPDIRECT3DTEXTURE9	_xblured_texture;
	LPDIRECT3DSURFACE9	_xblured_surface;
};