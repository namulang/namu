/*
	파일명:	CRgb.hpp
	이름:	RGB 클래스
	기능:	RGB값을 int로 갖고 있음
	메모:	테스트X
*/
#pragma once
//	선언:
//		기본 인클루드:
#include <d3dx9.h>
//	정의:
//		클래스:
class CRgb
{
//	멤버 함수:
public:
	//	생성자:
	//		기본생성자:
	CRgb();
	//		float 4개:
	CRgb(char red, char green, char blue);
	//		복사생성자:
	CRgb(CRgb& rgb);
	//	소멸자:
	~CRgb();
	//	초기화:
	void	initialize();
	//	연산자 오버로딩:
	DWORD	toD3DCOLOR();
	CRgb&	operator = (CRgb& rgb);
	//	변경자:
	//		빨강:
	void	setRed(int red);
	int		getRed();
	//		초록:
	void	setGreen(int green);
	int		getGreen();
	//		파랑:
	void	setBlue(int blue);
	int		getBlue();
	//		RGB:
	void	setRGB(int red, int green, int blue);
	//		세팅이 된 적 있는가: RGB값이 유효한가
	bool	isSetted();
	


//	멤버변수:
protected:
	//	RGB:
	int		_red, _green, _blue;
	bool	_setted; // 외부에서 따로 세팅을 했나
};
