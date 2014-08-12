#pragma once

#include "../../Includes/Includes.hpp"

class Planetarium;

class FilterModifier : public Window
{
public:
	FilterModifier(
		type_ushort new_x = 0, type_ushort new_y = 0, type_ushort new_width=0, 
		type_ushort new_height = 0, type_ushort new_fore=LG::LIGHTGRAY, 
		type_ushort new_back = 0, const NEString& new_text = "");

	Planetarium& getPlanetarium();
};