#include "CBlurFilter.hpp"
//	생성자
CBlurFilter::CBlurFilter(LPDIRECT3DDEVICE9 device, UINT render_target_width, UINT render_target_height)
: CFilter(device, render_target_width, render_target_height),
_xblured_texture(NULL), _xblured_surface(NULL)
{
	initializeShader(device);
	initializeHLSLValue(device);
	initializeResource(device);
}
//	셰이더를 초기화한다.
void	CBlurFilter::initializeShader(LPDIRECT3DDEVICE9 device)
{
	loadShaderFile(DEFAULT_CBLURFILTER_HLSL_PATH, device);
}	
//	셰이더와 관련된 변수를 바인딩한다.
void	CBlurFilter::initializeHLSLValue(LPDIRECT3DDEVICE9 device)
{
	//	예외상황 처리:
	if (!_enable)
		return ;

	//	메인 코드:
	//		바인딩:
	_technique = _effect->GetTechniqueByName("Tech");
	_blur_level_width_handle = _effect->GetParameterByName(NULL, "m_TexW");
	_blur_level_height_handle = _effect->GetParameterByName(NULL, "m_TexH");
}
//	리소스를 초기화한다.
void	CBlurFilter::initializeResource(LPDIRECT3DDEVICE9 device)
{
	device->CreateTexture( _render_target_width, _render_target_height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &_xblured_texture, NULL);
	_xblured_texture->GetSurfaceLevel(0, &_xblured_surface);
}
//	소멸자
CBlurFilter::~CBlurFilter()
{ 
	releaseResource();

	CFilter::release(); // 베이스클래스 호출
}
//	리소스를 해제한다.
void	CBlurFilter::releaseResource()
{
	if (_xblured_texture)
	{
		_xblured_texture->Release();
		_xblured_texture = NULL;
	}
	if (_xblured_surface)
	{
		_xblured_surface->Release();
		_xblured_surface = NULL;
	}

}
//	실행: 메인 함수
void	CBlurFilter::excute(LPDIRECT3DDEVICE9 device, LPDIRECT3DTEXTURE9 texture, LPDIRECT3DVERTEXBUFFER9 vertex_buffer, CCamera* camera)
{
	CBlurFilterData* blur_filter = casting(camera->_filter_data[DEFAULT_CSHADER_BLURFILTER]);
	if (!blur_filter)
		return ;

	update(blur_filter);
	filtering(device, texture, vertex_buffer, camera);
}
//	캐스팅 변환
CBlurFilterData*	CBlurFilter::casting(CFilterData* filter_data)
{
	return ( static_cast<CBlurFilterData*>(filter_data) );
}
//	필터와 관련된 변수들을 업데이트 한다.
void	CBlurFilter::update(CBlurFilterData* blur_filter_data)
{
	updateBlurLevel(blur_filter_data);
}
//	흐림 정도를 데이터에서 추출, 셰이더에 업데이트한다.
void	CBlurFilter::updateBlurLevel(CBlurFilterData* blur_filter_data)
{
	float height_squared = blur_filter_data->getBlurLevelHeight() * blur_filter_data->getBlurLevelHeight();
	
	_effect->SetFloat(_blur_level_height_handle, height_squared);
	_effect->SetFloat(_blur_level_width_handle, height_squared * _ratio);
}
//	실제로 필터링을 실시한다.
//	texture를 Xblur_texture에 찍고  ->  oldBUffer에 찍음
void	CBlurFilter::filtering(LPDIRECT3DDEVICE9 device, LPDIRECT3DTEXTURE9 texture, LPDIRECT3DVERTEXBUFFER9 vertex_buffer, CCamera* camera)
{
	//	예외상황 처리:
	if (!_enable)
		return ;

	//	메인 코드:
	//		준비:
	//			oldBuffer: 이전 타겟을 저장함
	LPDIRECT3DSURFACE9	old_surface;
	device->GetRenderTarget(0, &old_surface); // main프레임 또는 최신텍스쳐가 들어가있음
	//			새로운 타겟:
	device->SetRenderTarget(0, _xblured_surface);
	device->Clear(0, NULL, D3DCLEAR_TARGET, DEFAULT_CENGINE_RENDERTARGET_BACKGROUND, 1.0f, 0 );
	setVertex(vertex_buffer, CArea(-1,-1,1,1) );
	//			셰이더 준비:
	_effect->SetTechnique(_technique);
	_effect->Begin(NULL, 0);
	//		2패스: X방향 블러		
	_effect->BeginPass(0);		
	device->SetTexture(0, texture);	
	drawVertex(device); // vertex = -1, -1, 1, 1
	_effect->EndPass();		
	//		3패스: Y방향 블러
	device->SetRenderTarget(0, old_surface); // 최종타겟은 버퍼클리어 필요없음
	_effect->BeginPass(1);		
	device->SetTexture(0, _xblured_texture);	
	//			카메라세팅: 최종결과물을 찍을때는, 카메라의 렌더스테이트와 argb를 적용한다.		
	//setVertex(vertex_buffer, CArea(-1, -1, 1, 1), camera->_argb.toD3DCOLOR()); // 카메라의 rgba를 적용
	setRenderState(device, camera->getRenderState()); // 카메라의 렌더스테이트를 적용
	//			출력:
	drawVertex(device); // vertex = -1, -1, 1, 1
	_effect->EndPass();		
	//		복구:		
	_effect->End();		
	old_surface->Release();
	old_surface = NULL;

}

