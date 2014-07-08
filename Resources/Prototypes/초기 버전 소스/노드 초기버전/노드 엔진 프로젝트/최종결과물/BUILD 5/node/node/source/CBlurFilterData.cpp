#include "CBlurFilterData.hpp"
//	생성자
CBlurFilterData::CBlurFilterData() : CFilterData(), _blur_level_height(30.0f)
{
}
//	소멸자
CBlurFilterData::~CBlurFilterData()
{

}
//	얼마나 흐리게 하는지 값을 넘겨준다.
float	CBlurFilterData::getBlurLevelHeight()
{
	return _blur_level_height;
}
//	흐림정도를 넘겨온 변경한다.
void	CBlurFilterData::setBlurLevelHeight(float blur_level_height)
{
	//	예외상황처리: 경계선(min, max)을 넘으면 값을 보정
	if (blur_level_height < DEFAULT_CBLURFILTERDATA_BLUR_LEVEL_MIN)
		blur_level_height = DEFAULT_CBLURFILTERDATA_BLUR_LEVEL_MIN;
	if (blur_level_height > DEFAULT_CBLURFILTERDATA_BLUR_LEVEL_MAX)
		blur_level_height = DEFAULT_CBLURFILTERDATA_BLUR_LEVEL_MAX;
	
	//	메인코드:
	_blur_level_height = blur_level_height;
}
