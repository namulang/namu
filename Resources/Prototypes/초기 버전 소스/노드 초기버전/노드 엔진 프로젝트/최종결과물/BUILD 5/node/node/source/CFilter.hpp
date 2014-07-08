/*
	파일명:	CFilter.hpp
	이름:	필터 베이스 클래스
	기능:	모든 필터들의 베이스 클래스
*/
#pragma once
//	선언:
//		기본 인클루드:
#include <d3dx9.h>
//		커스텀 인클루드:
#include "CError.hpp"
#include "CCamera.hpp"
#include "CArea.hpp"
#include "CArgb.hpp"
#include "define.hpp"
//	정의:
//		클래스:
class CFilter
{
//	멤버함수:
public:
	//	생성자:
	CFilter(LPDIRECT3DDEVICE9 device, UINT render_target_width, UINT render_target_height);		
	//	소멸자:
	virtual	~CFilter();
	virtual void	release();
	//	렌더링:
	void	drawVertex(LPDIRECT3DDEVICE9 device);
	virtual	void excute(LPDIRECT3DDEVICE9 device, LPDIRECT3DTEXTURE9 texture, LPDIRECT3DVERTEXBUFFER9 vertex_buffer, CCamera* camera) = 0;
	//	셰이더 파일 로드:
	void	loadShaderFile(LPCTSTR filename, LPDIRECT3DDEVICE9 device);	
	
//	보안함수:
protected:
	//	버텍스:
	void	setVertex(LPDIRECT3DVERTEXBUFFER9 vertex_buffer, CArea vertex_area , DWORD color = D3DCOLOR_ARGB(255,255,255,255), CArea texture_area = CArea(0.0f, 0.0f, 1.0f, 1.0f));	
	//	렌더스테이트:
	void	setRenderState(LPDIRECT3DDEVICE9 device, char mode);



//	멤버변수:
public:
	//	상태변수:
	bool			_enable;

//	보안변수:
protected:
	//	바인딩:
	LPD3DXEFFECT	_effect;
	D3DXHANDLE		_technique;
	//	내부변수:
	LPD3DXBUFFER	_err;
	//	상태변수:
	UINT			_render_target_width;
	UINT			_render_target_height;
	float			_ratio;
};