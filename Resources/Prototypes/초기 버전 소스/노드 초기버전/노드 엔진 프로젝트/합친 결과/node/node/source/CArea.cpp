#include "CArea.hpp"
//	±âº» º¹»ç»ı¼ºÀÚ
CArea::CArea() : _x1(0), _y1(0), _x2(0), _y2(0) 
{

}
CArea::CArea(float x1, float y1, float x2, float y2)
: _x1(x1), _y1(y1), _x2(x2), _y2(y2) 
{

}
//	º¹»ç»ı¼ºÀÚ
CArea::CArea(CArea& area)
: _x1(area._x1), _y1(area._y1), _x2(area._x2), _y2(area._y2) 
{

}
//	¼Ò¸êÀÚ:
CArea::~CArea() 
{

}
//	µ¡¼À
CArea	CArea::operator + (CArea& area) 
{ 
	return CArea(	_x1 + area._x1, _y1 + area._y1, _x2 + area._x2, _y2 + area._y2); 
}
CArea&	CArea::operator += (CArea& area) 
{ 
	_x1 += area._x1;
	_y1 += area._y1;
	_x2 += area._x2;
	_y2 += area._y2; 

	return *this;
}
//	»¬¼À
CArea	CArea::operator - (CArea& area) 
{
	return CArea(	_x1 - area._x1, _y1 - area._y1, _x2 - area._x2, _y2 - area._y2); 
}
CArea&	CArea::operator -= (CArea& area) 
{	
	_x1 -= area._x1; 
	_y1 -= area._y1; 
	_x2 -= area._x2; 
	_y2 -= area._y2; 

	return *this;
}
//	°ö¼À
CArea	CArea::operator * (CArea& area) 
{ 
	return CArea(	_x1 * area._x1, _y1 * area._y1, _x2 * area._x2, _y2 * area._y2); 
}
CArea&	CArea::operator *= (CArea& area) 
{	
	_x1 *= area._x1; 
	_y1 *= area._y1; 
	_x2 *= area._x2; 
	_y2 *= area._y2; 

	return *this;
}
//	³ª´°¼À
CArea	CArea::operator / (CArea& area)
{ 
	return CArea(	_x1 / area._x1, _y1 / area._y1, _x2 / area._x2, _y2 / area._y2); 
}
CArea&	CArea::operator /= (CArea& area) 
{	
	_x1 /= area._x1;
	_y1 /= area._y1; 
	_x2 /= area._x2;
	_y2 /= area._y2; 

	return *this;
}	
//	´ëÀÔ¿¬»ê
CArea&	CArea::operator = (CArea& area) 
{ 
	_x1 = area._x1;
	_y1 = area._y1; 
	_x2 = area._x2; 
	_y2 = area._y2; 
	
	return *this; 
}
//	¼­·Î °°Àº°¡
bool	CArea::operator == (CArea& area) 
{ 
	if (	(_x1 == area._x1) &&
			(_y1 == area._y1) &&
			(_x2 == area._x2) &&
			(_y2 == area._y2))
		return true;
	else
		return false;
}