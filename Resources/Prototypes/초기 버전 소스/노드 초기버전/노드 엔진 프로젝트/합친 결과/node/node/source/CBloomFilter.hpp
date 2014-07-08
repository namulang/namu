/*
	파일명:	CBloomFilter.hpp
	이름:	노이즈 필터
	기능:	카메라클래스와 연동해서, 카메라가 찍은 대상에만 노이즈를 먹인다.
	메모:	셰이더 퀄리티가 올라가는 경우, 덜 흐릿하게 보인다. 
*/
#pragma once
//	선언:
//		기본 인클루드:
#include <d3d9.h>
//		커스텀 인클루드:
#include "CFilter.hpp"
#include "define.hpp"
#include "CBloomFilterData.hpp"
#include "CFilterData.hpp"
#include "CTexture.hpp"
//	정의:
//		클래스:
class CBloomFilter : public CFilter
{
//	멤버함수:
public:	
	//	생성자:
	CBloomFilter(LPDIRECT3DDEVICE9 device, UINT render_target_width, UINT render_target_height);
	//	소멸자:	
	virtual ~CBloomFilter();
	//	초기화:
	virtual void	initializeShader(LPDIRECT3DDEVICE9 device);
	virtual void	initializeHLSLValue(LPDIRECT3DDEVICE9 device);
	void	initializeResource(LPDIRECT3DDEVICE9 device);
	//	해제:
	void	releaseResource();
	//	실행: 메인 함수
	virtual void	excute(LPDIRECT3DDEVICE9 device, LPDIRECT3DTEXTURE9 texture, LPDIRECT3DVERTEXBUFFER9 vertex_buffer, CCamera* camera);
	//	캐스팅변환:
	CBloomFilterData*	casting(CFilterData* filter_data);
	//	변수 업데이트:
	void	update(CBloomFilterData* bloom_filter_data);
	void	updateBloomLevel(CBloomFilterData* bloom_filter_data);
	//	필터링:	
	void	filtering(LPDIRECT3DDEVICE9 device, LPDIRECT3DTEXTURE9 texture, LPDIRECT3DVERTEXBUFFER9 vertex_buffer, CCamera* camera);



//	개인변수:
private:
	//	핸들:	
	D3DXHANDLE	_bloom_level_handle;
	D3DXHANDLE	_dif_texture_handle;
	D3DXHANDLE	_dib_texture_handle;
	//	텍스쳐:
	LPDIRECT3DTEXTURE9	_temp_texture[2];
	LPDIRECT3DSURFACE9	_temp_surface[2];
	
};