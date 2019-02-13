#include "world.hpp"

namespace wrd
{
#define THIS World
	THIS::THIS() {}
	Instancer& THIS::getInstancer() { return _instancer; }
	const Instancer& THIS::getInstancer() const { return _instancer; }
	Classer& THIS::getClasser() { return _classer; }
	const Classer& THIS::getClasser() const { return _classer; }

	Res& THIS::init()
	{
		_instancer.init();
		_classer.init();
		return wasgood;
	}

	THIS& THIS::get()
	{
		static This* inner = NULL;
		if( ! inner)
		{
			inner = ::new This();
			inner->init();
		}

		return *inner;
	}
#undef THIS
}

namespace wrd 
{
	int main()
	{
		return 0;
	}
}
