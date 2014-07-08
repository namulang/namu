#include "CBloomFilter.hpp"
//	생성자:
CBloomFilter::CBloomFilter(LPDIRECT3DDEVICE9 device, UINT render_target_width, UINT render_target_height)
: CFilter(device, render_target_width, render_target_height),
_dif_texture_handle(NULL), _dib_texture_handle(NULL)
{
	initializeShader(device);
	initializeHLSLValue(device);
	initializeResource(device);
}
//	셰이더를 초기화한다
void	CBloomFilter::initializeShader(LPDIRECT3DDEVICE9 device)
{
	loadShaderFile(DEFAULT_CBLOOMFILTER_HLSL_PATH, device);
}	
//	HLSL에 변수를 바인딩
void	CBloomFilter::initializeHLSLValue(LPDIRECT3DDEVICE9 device)
{
	//	예외상황 처리:
	if (!_enable)
		return ;

	//	메인 코드:
	//		바인딩:
	_technique = _effect->GetTechniqueByName("Tech");
	_bloom_level_handle = _effect->GetParameterByName(NULL, "_bloom");
	_dif_texture_handle = _effect->GetParameterByName(NULL, "m_TxDif");
	_dib_texture_handle = _effect->GetParameterByName(NULL, "m_TxDiB");
}
void	CBloomFilter::initializeResource(LPDIRECT3DDEVICE9 device)
{		
	device->CreateTexture( _render_target_width, _render_target_height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &_temp_texture[0], NULL);
	_temp_texture[0]->GetSurfaceLevel(0, &_temp_surface[0]);		
	device->CreateTexture( _render_target_width, _render_target_height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &_temp_texture[1], NULL);
	_temp_texture[1]->GetSurfaceLevel(0, &_temp_surface[1]);
}
//	소멸자
CBloomFilter::~CBloomFilter()
{ 
	releaseResource();

	CFilter::release(); // 베이스클래스 호출
}
//	리소스를 해제한다
void	CBloomFilter::releaseResource()
{
	if (_temp_texture[0])
	{
		_temp_texture[0]->Release();
		_temp_texture[0] = NULL;
	}
	if (_temp_surface[0])
	{
		_temp_surface[0]->Release();
		_temp_surface[0] = NULL;
	}
	if (_temp_texture[1])
	{
		_temp_texture[1]->Release();
		_temp_texture[1] = NULL;
	}
	if (_temp_surface[1])
	{
		_temp_surface[1]->Release();
		_temp_surface[1] = NULL;
	}
}
//	실행: 메인 함수
void	CBloomFilter::excute(LPDIRECT3DDEVICE9 device, LPDIRECT3DTEXTURE9 texture, LPDIRECT3DVERTEXBUFFER9 vertex_buffer, CCamera* camera)
{
	CBloomFilterData* bloom_filter = casting(camera->_filter_data[DEFAULT_CSHADER_BLOOMFILTER]);
	if (!bloom_filter)
		return ;

	update(bloom_filter);
	filtering(device, texture, vertex_buffer, camera);
}
//	캐스팅변환:
CBloomFilterData*	CBloomFilter::casting(CFilterData* filter_data)
{
	return ( static_cast<CBloomFilterData*>(filter_data) );
}
//	변수 업데이트:
void	CBloomFilter::update(CBloomFilterData* bloom_filter_data)
{
	updateBloomLevel(bloom_filter_data);
}
//	블룸 정도를 업데이트한다
void	CBloomFilter::updateBloomLevel(CBloomFilterData* bloom_filter_data)
{
	//	메인코드:
	//		바인딩:
	_effect->SetFloat(_bloom_level_handle, bloom_filter_data->getBloomLevel());		
}
//	필터링:	
void	CBloomFilter::filtering(LPDIRECT3DDEVICE9 device, LPDIRECT3DTEXTURE9 texture, LPDIRECT3DVERTEXBUFFER9 vertex_buffer, CCamera* camera)
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
	device->SetRenderTarget(0, _temp_surface[0]);
	device->Clear(0, NULL, D3DCLEAR_TARGET, DEFAULT_CENGINE_RENDERTARGET_BACKGROUND, 1.0f, 0 );
	setVertex(vertex_buffer, CArea(-1,-1,1,1) );
	//			셰이더 준비:
	_effect->SetTechnique(_technique);
	_effect->Begin(NULL, 0);
	//		2패스: 감마 먹이기
	_effect->BeginPass(0);		
	device->SetTexture(0, texture); // 원본
	drawVertex(device); // vertex = -1, -1, 1, 1
	_effect->EndPass();	
	//		3패스: X방향 블러
	device->SetRenderTarget(0, _temp_surface[1]);
	device->Clear(0, NULL, D3DCLEAR_TARGET, DEFAULT_CENGINE_RENDERTARGET_BACKGROUND, 1.0f, 0 );
	_effect->BeginPass(1);		
	device->SetTexture(0, _temp_texture[0]);
	drawVertex(device);
	_effect->EndPass();
	//		4패스: Y방향 블러
	device->SetRenderTarget(0, _temp_surface[0]);		
	device->Clear(0, NULL, D3DCLEAR_TARGET, DEFAULT_CENGINE_RENDERTARGET_BACKGROUND, 1.0f, 0 );
	_effect->BeginPass(2);		
	device->SetTexture(0, _temp_texture[1]);
	drawVertex(device);
	_effect->EndPass();		
	//		5패스: 합쳐서 최종 찍기
	device->SetRenderTarget(0, old_surface);
	_effect->BeginPass(3);
	device->SetTexture(0, texture); // 원본
	device->SetTexture(1, _temp_texture[0]); // 가공
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
	device->SetTexture(1, NULL);
}
