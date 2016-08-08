#include "NEIdableObject.hpp"
#include "NETClass.hpp"

namespace NE
{
	const NEClassBase& NEIdableObject::getClassStatically()
	{
		static NETClass<NEIdableObject> inner;

		return inner;
	}
}