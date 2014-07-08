#include "CNoiseFilterData.hpp"
//	생성자
CNoiseFilterData::CNoiseFilterData() : _max(DEFAULT_CNOISEFILTER_MAX_NOISE_LEVEL), _min(DEFAULT_CNOISEFILTER_MIN_NOISE_LEVEL), 
_delay(DEFAULT_CNOISEFILTER_DELAY), _before_xrepeat(1.0f), _before_yrepeat(1.0f)
{}
//	소멸자
CNoiseFilterData::~CNoiseFilterData()
{}
//	발생할 수 있는 최대 노이즈 값을 가져온다
int		CNoiseFilterData::getNoiseMaxLevel()
{
	return _max;
}
//	발생할 수 있는 최대 노이즈 값을 정한다
void	CNoiseFilterData::setNoiseMaxLevel(int noise_max)
{
	if (noise_max <= _min)
		noise_max = _min + 1;
	if (noise_max > DEFAULT_CNOISEFILTER_MAX_NOISE_LEVEL)
		noise_max = DEFAULT_CNOISEFILTER_MAX_NOISE_LEVEL;

	_max = noise_max;
}
//	발생할 수 있는 최소 노이즈 값을 가져온다
int		CNoiseFilterData::getNoiseMinLevel()
{
	return _min;
}
//	발생할 수 있는 최소 노이즈 값을 정한다
void	CNoiseFilterData::setNoiseMinLevel(int noise_min)
{
	if (noise_min < DEFAULT_CNOISEFILTER_MIN_NOISE_LEVEL)
		noise_min = DEFAULT_CNOISEFILTER_MAX_NOISE_LEVEL;
	if (noise_min >= _max)
		noise_min = _max - 1;

	_max = noise_min;
}
//	노이즈가 변하게되는 시간간격을 정한다
void	CNoiseFilterData::setDelay(int delay)
{
	//	예외상황처리:
	if (delay < 0)
		delay = 1;

	_delay = delay;
}
//	노이즈가 변하게되는 시간간격을 가져온다
int		CNoiseFilterData::getDelay()
{
	return _delay;
}
//	새로운 노이즈를 그릴 시간이 되었는지 확인한다
bool	CNoiseFilterData::isTimeElapsed()
{
	DWORD	now = timeGetTime();
	if ( (static_cast<int>(now-_before_worked_milisecond)) >= _delay )
	{
		_before_worked_milisecond = now;
		return true;
	}

	return false;
}
