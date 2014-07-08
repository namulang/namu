/*
	파일명:	CArea.hpp
	이름:	영역 클래스
	기능:	CRect의 float 판.
			x1, x2, y1, y2를 float형태로 저장한다
			CArea간의 operator 연산 지원
	메모:	테스트X
*/
#pragma once
//	정의:
//		클래스:
class CArea
{
//	멤버 함수:
public:	
	//	생성자:
	//		기본생성자:
	CArea();
	//		float 4개:
	CArea(float x1, float y1, float x2, float y2);
	//		복사생성자:
	CArea(CArea& area);
	//	소멸자:
	~CArea();
	//	연산자 중첩:
	//		사칙연산:
	//			덧셈:
	CArea	operator + (CArea& area);
	CArea&	operator += (CArea& area);
	//			뺄셈:
	CArea	operator - (CArea& area);
	CArea&	operator -= (CArea& area);
	//			곱셈:
	CArea	operator * (CArea& area);
	CArea&	operator *= (CArea& area);
	//			나눗셈:
	CArea	operator / (CArea& area);
	CArea&	operator /= (CArea& area);
	//			등호:
	CArea&	operator = (CArea& area);
	//		논리연산:
	//			같은가:
	bool	operator == (CArea& area);



//	멤버변수:
public:	
	//	영역:
	float	_x1, _y1, _x2,	_y2;
};
