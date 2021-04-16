#include "world.hpp"

namespace wrd
{
#define ME World
	ME::ME() {}
	Instancer& ME::getInstancer() { return _instancer; }
	const Instancer& ME::getInstancer() const { return _instancer; }
	Classer& ME::getClasser() { return _classer; }
	const Classer& ME::getClasser() const { return _classer; }

	Res& ME::init()
	{
		_instancer.init();
		_classer.init();
		return wasgood;
	}

	ME& ME::get()
	{
		static me* inner = NULL;
		if( ! inner)
		{
			inner = ::new me();
			inner->init();
		}

		return *inner;
	}
#undef ME
}

namespace wrd 
{
	int main()
	{
		return 0;
	}
}
