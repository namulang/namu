#include "Instancer.hpp"

namespace wrd
{
#define THIS Instancer

	const Block& THIS::operator[](Id id) const { return get(id); }

	const Block& THIS::get(Id id) const
	{
		//TODO:
		return nulr<const Block>();
	}

	Res& THIS::bind(Instance& new1)
	{
		//TODO:
		return wasgood;
	}

	Res& THIS::unbind(Instance& old)
	{
		//TODO:"
		return wasgood;
	}

#undef THIS
}
