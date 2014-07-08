#include "CCamera.hpp"

CCamera::CCamera() 
: _x(0.0f), _y(0.0f), _z(0.0f), _angle(0.0f), _scale_x(1.0f), _scale_y(1.0f), 
_argb(), _preserve(false), _enable(true), _render_state(DEFAULT_CENGINE_RENDERSTATE_DEFAULT), _render_state_setted(false)
{
	initializeFilterData();
}
CCamera::CCamera(float x, float y, float z, float angle, float scale_x, float scale_y, CArgb argb, bool preserve, char render_state) 
: _x(x), _y(y), _z(z), _angle(angle), _scale_x(scale_x), _scale_y(scale_y), 
_render_state(render_state), _argb(argb), _render_state_setted(true),
_preserve(preserve), _enable(true)
{}
//	소멸자:
CCamera::~CCamera()
{}
//	활성화된 필터가 하나라도 있는지 검사한다
bool	CCamera::isThereEnabledFilter()
{
	for (int n=0; n < DEFAULT_CSHADER_FILTER_NUMBER ;n++)
	{
		if (_filter_data[n]->_enable)
			return true;
	}
	
	return false;
}
//	필터를 초기화한다.
void	CCamera::initializeFilterData() // #필터#추가#
{
	_filter_data[DEFAULT_CSHADER_BLURFILTER] = new CBlurFilterData();
	_filter_data[DEFAULT_CSHADER_NOISEFILTER] = new CNoiseFilterData();
	_filter_data[DEFAULT_CSHADER_BLOOMFILTER] = new CBloomFilterData();
}
//	카메라의 렌더스테이트를 세팅한다.
//	_render_state_setted가 true가 되면, 이 카메라로 렌더링하는 모든 노드개체에, 
//	카메라의 렌더스테이트를 적용한다.
void	CCamera::setRenderState(char render_state)
{
	if (render_state > DEFAULT_CENGINE_RENDERSTATE_NUMBER)
		render_state = DEFAULT_CENGINE_RENDERSTATE_NUMBER;

	_render_state = render_state;
	_render_state_setted = true;
}
//	현재 렌더스테이트를 가져온다.
char	CCamera::getRenderState()
{
	return _render_state;
}
//	렌더스테이트를 초기화한다. (강제로, 노드개체에 렌더스테이를 적용하지 않는다)
void	CCamera::initializeRenderState()
{
	_render_state = DEFAULT_CENGINE_RENDERSTATE_DEFAULT;
	_render_state_setted = false;
}
//	이 카메라가 preserve 상태인지를 반환한다.
//	단순히, _preserve 가 true이라고 해도, 필터를 켜놓지 않으면 의미가 없다.
//	그래서, 필터가 꺼져있으면 false를 반환한다.
bool	CCamera::isPreserved()
{
	if (_preserve && isThereEnabledFilter())
		return true;
	else
		return false;
}