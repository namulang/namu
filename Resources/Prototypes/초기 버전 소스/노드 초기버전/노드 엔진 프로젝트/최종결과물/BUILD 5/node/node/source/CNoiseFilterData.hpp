/*
	파일명:	CNoiseFilterData.hpp
	이름:	노이즈필터데이터 클래스
	기능:	노이즈필터클래스에서 노이즈필터데이터 클래스를 불러들여서 작동을 함.
			카메라별로 필터를 먹일수 있게끔 함.
*/
#pragma once
//	선언:
//		기본 인클루드:
#include <Windows.h>
//		커스텀 인클루드:
#include "CFilterData.hpp"
#include "define.hpp"
//	정의:
//		클래스:
class CNoiseFilterData : public CFilterData
{
//	멤버함수:
public:
	//	생성자:
	CNoiseFilterData();
	//	소멸자:
	~CNoiseFilterData();
	//	접근자:
	//		노이즈 정도:
	int		getNoiseMaxLevel();
	void	setNoiseMaxLevel(int noise_max);
	int		getNoiseMinLevel();
	void	setNoiseMinLevel(int noise_min);
	//		딜레이:
	void	setDelay(int delay);
	int		getDelay();
	bool	isTimeElapsed();


//	멤버변수:
public:
	float	_before_yrepeat;
	float	_before_xrepeat;

//	개인변수:
private:
	//	일반변수:
	int		_min;
	int		_max;
	int		_delay; // milisecond
	DWORD	_before_worked_milisecond; // 이전번에 작동했던 타임.

};