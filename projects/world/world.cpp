#include "world.hpp"

namespace wrd
{
#define THIS World
	THIS::THIS() {}
	Instancer& THIS::getInstancer() { return _instancer; }
	const Instancer& THIS::getInstancer() const { return _instancer; }
#undef THIS
}

namespace wrd 
{
	int main()
	{
		return 0;
	}
}
