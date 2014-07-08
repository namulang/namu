/*
	파일명:	CScripter.hpp
	이름:	스크립터 클래스
	기능:	스크립트 파일(맵)로부터 스크립트 데이터를 읽는다. 그에 따라, 객체들을 생성한다
			스크립트 클래스의 제어아래, 모든 객체들이 움직이고, 렌더링이 된다

	메모:	군데군데 테스트용으로 채워넣은 코드가 많음 (2010-07-08)
*/
#pragma once
//	선언:
//		커스텀 인클루드:
#include "CEngine.hpp"
#include "CCamera.hpp"
#include "CError.hpp"
#include "define.hpp"
//임시임시임시임시임시임시임시임시임시임시임시임시임시
#define	TEMP_CAMERA_NUMBER	5 //  임시임시임시임시임시
//임시임시임시임시임시임시임시임시임시임시임시임시임시

//	정의:
//		클래스:
class CScripter
{
//	멤버함수:
public:	
	//	생성자:
	CScripter(CEngine* engine);
	//	소멸자:
	~CScripter();
	//	익스큐트함수:	한 프레임 계산 및 출력하기	
	void	excute(); //	익스큐트 함수란? ... 이 클래스가 메인으로 담당하는 가장 핵심적인 기능
	
//	개인함수:
private:
	//	렌더링:
	void	rendering();
	//	렌더링 사전 작업:	
	void	preRender();
	void	searchLastPreserveCamera();
	//	렌더링 사후 작업:	
	HRESULT	postRender();



//	멤버변수:
private:
	//	카메라: ( #작업# 임시)
	CCamera		_camera[TEMP_CAMERA_NUMBER]; //	#작업#	테스트用. 실제로는, 씬영역에 위치해있다. 	
	//	접근자변수:
	CEngine*	_engine;
};