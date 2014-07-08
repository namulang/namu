/*
	파일명:	CFilterData.hpp
	이름:	필터데이터 베이스 클래스
	기능:	필터 데이터에서 기본적으로 갖게되는 부분
*/
#pragma once
//	정의:
//		클래스:
class CFilterData
{
//	멤버함수:
public:
	//	생성자:
	CFilterData() : _enable(false)
	{}
	//	소멸자:
	~CFilterData()
	{}


//	멤버변수:
public:
	//	상태변수:
	bool	_enable;
};