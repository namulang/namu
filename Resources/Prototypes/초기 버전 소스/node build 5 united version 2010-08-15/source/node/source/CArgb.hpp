/*
	파일명:	CARgb.hpp
	이름:	ARGB 클래스 (CRgb의 파생클래스)
	기능:	ARGB값을 저장함. 
			같은 CArgb끼리 대입이 가능.
			DWORD에 CArgb를 놓으면 자동으로 D3DCOLOR_ARGB로 연산을 처리한다
	메모:	테스트X
			
*/
#pragma once
//	선언:
//		기본 인클루드:
#include <d3dx9.h>
//		커스텀 인클루드:
#include "CRgb.hpp"
//	정의:
//		클래스:
class CArgb : public CRgb
{
//	멤버함수:
public:
	//	생성자:
	CArgb();
	CArgb(char alpha, char red, char green, char blue);
	CArgb(CArgb& argb);
	//	소멸자:
	~CArgb();
	//	초기화:
	void	initialize();
	//	변경자:
	//		알파:
	void	setAlpha(int alpha);
	int		getAlpha();
	//		ARGB:	
	void	setARGB(int alpha, int red, int green, int blue);
	//		세팅이 된적이 있는가: ARGB값이 유효한가
	bool	isSetted();
	//	연산자 오버로딩:
	DWORD	toD3DCOLOR();
	CArgb&	operator = (CArgb& argb);



//	멤버변수:
private:
	//	일반변수:
	int		_alpha;
	bool	_alpha_setted;
};