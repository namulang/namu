#include "CNoiseFilter.hpp"
//	생성자
CNoiseFilter::CNoiseFilter(LPDIRECT3DDEVICE9 device, int render_target_width, int render_target_height)
: CFilter(device, render_target_width, render_target_height),
_noisemap_texture(), _xrepeat_handle(NULL), _yrepeat_handle(NULL), _source_texture_handle(NULL), _noise_texture_handle(NULL)
{
	initializeShader(device);
	initializeHLSLValue(device);
	initializeResource(device);
}
//	셰이더 초기화
void	CNoiseFilter::initializeShader(LPDIRECT3DDEVICE9 device)
{
	loadShaderFile(DEFAULT_CNOISEFILTER_HLSL_PATH, device);
}	
//	HLSL에 변수 바인딩
void	CNoiseFilter::initializeHLSLValue(LPDIRECT3DDEVICE9 device)
{
	//	예외상황 처리:
	if (!_enable)
		return ;

	//	메인 코드:
	//		바인딩:
	_technique = _effect->GetTechniqueByName("Tech");
	_xrepeat_handle = _effect->GetParameterByName(NULL, "m_fRepeatX");
	_yrepeat_handle = _effect->GetParameterByName(NULL, "m_fRepeatY");
	_source_texture_handle = _effect->GetParameterByName(NULL, "source_texture");
	_noise_texture_handle = _effect->GetParameterByName(NULL, "noise_texture");
}
void	CNoiseFilter::initializeResource(LPDIRECT3DDEVICE9 device)
{
	_noisemap_texture.setFileName(DEFAULT_CNOISEFILTER_NOISEMAP_PATH);
	_noisemap_texture.loadTexture(device, true);
}
//	소멸자
CNoiseFilter::~CNoiseFilter()
{ 
	releaseResource();

	CFilter::release(); // 베이스클래스 호출
}
//	리소스 해제
void	CNoiseFilter::releaseResource()
{
	_noisemap_texture.UnloadTexture();
}
//	실행: 메인 함수
void	CNoiseFilter::excute(LPDIRECT3DDEVICE9 device, LPDIRECT3DTEXTURE9 texture, LPDIRECT3DVERTEXBUFFER9 vertex_buffer, CCamera* camera)
{
	CNoiseFilterData* noise_filter = casting(camera->_filter_data[DEFAULT_CSHADER_NOISEFILTER]);
	if (!noise_filter)
		return ;

	update(noise_filter);
	filtering(device, texture, vertex_buffer, camera);
}
//	캐스팅변환 - 필터데이터를 노이즈필터데이터로
CNoiseFilterData*	CNoiseFilter::casting(CFilterData* filter_data)
{
	return ( static_cast<CNoiseFilterData*>(filter_data) );
}
//	변수 업데이트
void	CNoiseFilter::update(CNoiseFilterData* noise_filter_data)
{
	updateNoiseLevel(noise_filter_data);
}
//	노이즈의 값정도를 업데이트 한다
void	CNoiseFilter::updateNoiseLevel(CNoiseFilterData* noise_filter_data)
{
	//	예외상황처리: 딜레이가 아직 안된경우.
	if (noise_filter_data->isTimeElapsed())
	{
		//	메인코드:
		//		데이타 계산: 셰이더에 바인딩할때, 작은값이 더 변화가 크므로, max와 min이 바뀌어야 한다.		
		int		max_level = DEFAULT_CNOISEFILTER_MAX_NOISE_LEVEL - noise_filter_data->getNoiseMinLevel(); 
		int		min_level = DEFAULT_CNOISEFILTER_MAX_NOISE_LEVEL - noise_filter_data->getNoiseMaxLevel();
		noise_filter_data->_before_xrepeat = (min_level + rand()%(max_level-min_level)) / 20.0f;
		noise_filter_data->_before_yrepeat = (min_level + rand()%(max_level-min_level)) / 20.0f;
	}
	//		바인딩:
	_effect->SetFloat(_xrepeat_handle, noise_filter_data->_before_xrepeat);
	_effect->SetFloat(_yrepeat_handle, noise_filter_data->_before_yrepeat);
}
//	필터링
void	CNoiseFilter::filtering(LPDIRECT3DDEVICE9 device, LPDIRECT3DTEXTURE9 texture, LPDIRECT3DVERTEXBUFFER9 vertex_buffer, CCamera* camera)
{		
	//	예외상황 처리:
	if (!_enable)
		return ;

	//	메인 코드:
	//		셰이더 준비:
	_effect->SetTechnique(_technique);
	_effect->Begin(NULL, 0);
	//			샘플러스테이트: 이 필터에서만 사용하는 것
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//		2패스: 노이즈
	_effect->BeginPass(0);		
	device->SetTexture(0, texture);
	device->SetTexture(1, _noisemap_texture._texture);
			
	//			카메라세팅: 최종결과물을 찍을때는, 카메라의 렌더스테이트와 argb를 적용한다.		
	setVertex(vertex_buffer, CArea(-1, -1, 1, 1)); // 카메라의 rgba를 적용
	setRenderState(device, camera->getRenderState()); // 카메라의 렌더스테이트를 적용
	//			출력:
	drawVertex(device); // vertex = -1, -1, 1, 1 
	_effect->EndPass();	
	//		복구:		
	_effect->End();		
	device->SetTexture(1, NULL);
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_NONE);	
	device->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_NONE);
	device->SetTexture(1, NULL);
}

