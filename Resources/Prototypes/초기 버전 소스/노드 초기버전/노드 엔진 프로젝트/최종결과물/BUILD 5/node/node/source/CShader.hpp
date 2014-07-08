/*
	파일명:	CShader.hpp
	이름:	셰이더 클래스
	기능:	셰이더와 관련된 모든 부분을 담당하고 있음. 주로, 필터 관리자.
*/
#pragma once
//	선언:
//		기본 인클루드:
#include <d3dx9.h>
//		커스텀 인클루드:
#include "CFilter.hpp"
#include "CINI.hpp"
#include "CBlurFilter.hpp" // #필터#추가#
#include "CNoiseFilter.hpp"
#include "CBloomFilter.hpp"
//	정의:
//		클래스:
class CShader
{
//	멤버함수:
public:
	//	생성자:
	CShader();
	//	소멸자:
	~CShader();
	//	초기화:
	void	initialize(LPDIRECT3DDEVICE9 device, CINI* ini);
	void	initializeLastPreserveCamera();
	//	해제:
	void	release();
	//	접근자:
	//		카메라:
	void	setLastPreserveCamera(CCamera* camera);
	//		렌더링타겟:
	void	swapOldToRecentIndex();
	int		getRecentIndex();
	int		getOldIndex();
	//	렌더링 타겟:
	void	swapToMainFrame();
	void	swapToRecentTarget();
	void	swapToOldTarget();
	//	필터링:
	void	preFiltering(CCamera* camera);
	//	렌더링 후, 필터링을 하기 위한 마무리작업
	void	postFiltering(CCamera* camera, LPDIRECT3DVERTEXBUFFER9 vertex_buffer);
	void	clearBuffer(D3DCOLOR color);
	void	filtering(CCamera* camera, LPDIRECT3DTEXTURE9 texture, LPDIRECT3DVERTEXBUFFER9 vertex_buffer);

//	개인함수:
private:
	//	초기화:
	void	initializeFilter(); 
	void	initializeRenderTargetTexture();
	void	initializeValue(CINI* ini, LPDIRECT3DDEVICE9 device);
	//	해제:
	void	releaseFilter();
	void	releaseRenderTargetTexture();
	//	필터링:
	//		싱글필터링: 필터가 하나만 켜있는 경우.
	void	singleFiltering(CCamera* camera, LPDIRECT3DTEXTURE9 texture, LPDIRECT3DVERTEXBUFFER9 vertex_buffer);
	//		중첩필터링: 하나의 카메라의 여러개의 필터가 동시에 켜진경우
	void	nestedFiltering(CCamera* camera, LPDIRECT3DTEXTURE9 texture, LPDIRECT3DVERTEXBUFFER9 vertex_buffer, char last_filter_index);
	


//	멤버변수:
public:
	//	상태변수:
	bool	_iniShaderOn;

//	개인변수:
private:
	//	필터:
	CFilter*			_filter[DEFAULT_CSHADER_FILTER_NUMBER];	
	//	리소스:
	LPDIRECT3DTEXTURE9	_temp_texture[2];
	LPDIRECT3DSURFACE9	_temp_surface[2];
	LPDIRECT3DSURFACE9	_mainframe_surface;
	LPDIRECT3DTEXTURE9	_nested_filter_texture[2];
	LPDIRECT3DSURFACE9	_nested_filter_surface[2];
	//	일반 변수:
	int					_recent_index;
	UINT				_rendertarget_width;
	UINT				_rendertarget_height;
	CCamera*			_last_preserve_index; // last_preserve가 있을경우, 여기에 주소값이 들어간다.
	//	접근자:
	LPDIRECT3DDEVICE9	_device;
};