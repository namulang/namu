#include "CRgb.hpp"
//	기본생성자
CRgb::CRgb() : _red(255), _green(255), _blue(255), _setted(false)
{

}
//	생성자:
CRgb::CRgb(char red, char green, char blue)
: _red(red), _green(green), _blue(blue), _setted(true)
{
}
//	복사생성자
CRgb::CRgb(CRgb& rgb)
: _red(rgb._red), _green(rgb._green), _blue(rgb._blue), _setted(rgb._setted) 
{

}
//	소멸자
CRgb::~CRgb() 
{

}
//	RGB값을 D3DCOLOR 값(DWORD)로 변경한다
DWORD	CRgb::toD3DCOLOR()
{
	return D3DCOLOR_XRGB(_red, _green, _blue);
}
//	RGB값이 세팅이 되었는지를 반환한다.
//	초기화 후, 한번이라도 RGB값을 변경한경우, 이 카메라로 렌더링하는
//	모든 노드 개체에 RGB값을 강제 적용한다.
bool	CRgb::isSetted()
{
	return _setted;
}
//	대입 연산자
CRgb&	CRgb::operator = (CRgb& rgb)
{
	_red = rgb._red;
	_green = rgb._green;
	_blue = rgb._blue;
	_setted = rgb._setted;

	return *this;
}
//	빨강 색상값을 변경한다
void	CRgb::setRed(int red)
{	
	if (red > 255)
		red = 255;
	if (red < 0)
		red = 0;

	_red = red;
	_setted = true;
}
//	빨강 색상값을 가져온다
int		CRgb::getRed()
{
	return _red;
}
//	초록 색상값을 변경한다
void	CRgb::setGreen(int green)
{	
	if (green > 255)
		green = 255;
	if (green < 0)
		green = 0;

	_green = green;
	_setted = true;
}
//	초록 색상값을 가져온다
int		CRgb::getGreen()
{
	return _green;
}
//	파랑 색상값을 변경한다
void	CRgb::setBlue(int blue)
{	
	if (blue > 255)
		blue = 255;
	if (blue < 0)
		blue = 0;

	_blue = blue;
	_setted = true;
}
//	파랑 색상값을 가져온다
int		CRgb::getBlue()
{
	return _blue;
}
//	RGB 색상값을 모두 변경한다
void	CRgb::setRGB(int red, int green, int blue)
{	
	setRed(red);
	setGreen(green);
	setBlue(blue);
}
//	RGB 색상값을 초기화한다. 한번도 세팅이 안된 걸로 됨
void	CRgb::initialize()
{
	_red = 255;
	_blue = 255;
	_green = 255;
	_setted = false;
}
