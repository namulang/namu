#pragma once

#include "../../Includes/Includes.hpp"

class Running : public LG::Gliph
{
public:
	Running()
		: LG::Gliph(0, 20, 11, 40, 4, WHITE, LIGHTRED, "\n\t실행중 . . . \n\t중단은 Cancel키(default : ESC)") {}	
};