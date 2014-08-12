#include "FilterModifier.hpp"

FilterModifier::FilterModifier(
	type_ushort new_x /* = 0 */, type_ushort new_y /* = 0 */, type_ushort new_width/* =0 */, type_ushort new_height /* = 0 */, 
	type_ushort new_fore/* =COLOR::LIGHTGRAY */, type_ushort new_back /* = 0 */, const NEString& new_text /* = "" */)
	: Window(new_x, new_y, new_width, new_height, new_fore, new_back, new_text)
{

}

Planetarium& FilterModifier::getPlanetarium()
{ 
	return (Planetarium&) owner->getCaller();
}