/*
	파일명:	CEngine.hpp
	이름:	엔진 클래스
	기능:	다이렉트X와 관련된 모든 기능을 다 다룬다
*/
#pragma once
//	선언:
//		라이브러리:
#pragma comment (lib, "d3dxof.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "d3d9.lib")
//			디버그 및 릴리즈 구분:
#ifdef	_DEBUG
#pragma comment (lib, "d3dx9d.lib")
#else
#pragma comment (lib, "d3dx9.lib")
#endif
//		기본 인클루드:
#include <windows.h>
#include <d3dx9.h>
//		커스텀 인클루드:
#include "CINI.hpp"
#include "CWindow.hpp"
#include "CError.hpp"
#include "CArea.hpp"
#include "CRgb.hpp"
#include "CCamera.hpp"
#include "CTexture.hpp"
#include "define.hpp"
#include "CShader.hpp"
//	정의:
//		클래스:
class CEngine
{
//	멤버함수:
public:	
	//		생성자:
	CEngine(CINI* ini);
	//		소멸자:
	~CEngine();
	//		복구:
	void	restore();
	//		렌더링:
	//			통합:
	void	rendering(CCamera* camera, int index);
	void	render(CCamera* camera, int index);
	//			최종 출력:
	HRESULT	present();
	//			화면 비우기:
	void	clearBuffer(D3DCOLOR color);

//	개인함수:
private:	
	//	초기화:
	void	initializeDirectx();
	void	initializeDevice();
	void	initializeVertexBuffer();
	void	initializeRenderState();
	void	initializeMatrix();
	void	initializeDisplayMode();
	void	initializeCapabilities();	
	void	initializeTextureCapacity(int texture_capacity);
	void	initializeShader();
	void	initializeFilter();
	//	소멸자:
	void	releaseResource();
	HRESULT	releaseDevice();
	void	releaseShader();
	void	releaseFilter();
	//	복구:
	void	restoreDevice();
	void	restoreResource();	
	//	디스플레이모드:
	void	getCurrentDisplayMode(D3DDISPLAYMODE* display);
	void	getEnumerateDisplayMode(bool is32bitcolor);
	void	enumerateOneDisplayMode(D3DFORMAT format, int start_index, int count);
	int		getEnumerateDisplayModeCount(bool is32bitcolor);
	void	selectModeInEnumeratedMode();
	//	필터링:
	void	filtering(CCamera* camera);	
	//	버텍스:
	void	setVertex(	CArea vertex, 
						DWORD color = D3DCOLOR_ARGB(255,255,255,255), 
						CArea texture = CArea(0.0f, 0.0f, 1.0f, 1.0f));
	void	drawVertex();
	//	카메라:	
	void	getWorldMatrix(CCamera* camera);
	void	setRenderState(char mode);
	//	렌더링타겟:
	void	swapRenderTargetToTexture();
	void	swapRenderTargetToFrameBuffer();
	//	텍스쳐:	
	void	loadTexture(CString filename); 


	
//	멤버변수:
public:
	CShader	_shader;

//	개인변수:
private:
	//	다이렉트:
	LPDIRECT3D9			_direct;
	LPDIRECT3DDEVICE9	_device;		
	D3DCAPS9			_caps;
	//	디스플레이 모드:
	D3DDISPLAYMODE*	_playable_display_modes;
	int				_playable_display_mode_number;
	D3DDISPLAYMODE	_selected_display_mode;
	int				_isHardwareVertexProcessingEnable;	
	//	데이터:
	D3DPRESENT_PARAMETERS	_present_parameter; 
	LPDIRECT3DVERTEXBUFFER9	_vertex_buffer; 
	//	리소스:	
	CTexture*	_texture; // 중요! 텍스쳐 자체는 CEngine에 있고, CNode의 텍스쳐 노드는, CScripter->_engine을 통해서 텍스쳐에 접근한다
	int			_texture_capacity; // 실제로 저장되는 건 [0 ~ capacity-1] 까지다
	int			_texture_size;
	//	접근자포인터:
	CINI*	_ini;
};