/*
	파일명:	CBlurFilterData.hpp
	이름:	블러필터데이터 클래스
	기능:	블러필터클래스에서 블러필터데이터 클래스를 불러들여서 작동을 함.
			카메라별로 필터를 먹일수 있게끔 함.
*/
#pragma once
#include "CFilterData.hpp"
#include "define.hpp"
//	정의:
//		클래스:
class CBlurFilterData : public CFilterData
{
//	멤버함수:
public:
	//	생성자:
	CBlurFilterData();
	//	소멸자:
	~CBlurFilterData();
	//	접근자:
	//		흐림정도:
	float	getBlurLevelHeight();
	void	setBlurLevelHeight(float blur_level_height);



//	개인변수:
private:
	//	일반변수:
	float	_blur_level_height;
};