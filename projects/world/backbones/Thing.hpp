#pragma once

#include <iostream>
#include "../deps.hpp"

namespace WRD
{
	class Thing
	{
	public:
		Thing() {
			std::cout << "Thing::Thing()\n";
		}
	};
}
