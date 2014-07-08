/*
	파일명:	CBloomFilterData.hpp
	이름:	블룸필터데이터 클래스
	기능:	블룸필터클래스에서 블룸필터데이터 클래스를 불러들여서 작동을 함.
			카메라별로 필터를 먹일수 있게끔 함.
*/
#pragma once
//	선언:
//		커스텀 인클루드:
#include "CFilterData.hpp"
#include "define.hpp"
//	정의:
//		클래스:
class CBloomFilterData : public CFilterData
{
//	멤버함수:
public:
	//	생성자:
	CBloomFilterData();
	//	소멸자:
	~CBloomFilterData();
	//	접근자:
	//		노이즈 정도:
	float	getBloomLevel();
	void	setBloomLevel(float bloom_level);
	

	
//	개인변수:
private:
	//	일반변수:
	float	_bloom_level;
};