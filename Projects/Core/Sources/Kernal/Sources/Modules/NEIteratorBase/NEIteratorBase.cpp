#include "NEIteratorBase.hpp"
#include "../NETClass/NETClass.hpp"

namespace NE
{
	NE_DEFINE_INTERFACE_ONLY(NEIteratorBase)

	NEIteratorBase& NEIteratorBase::operator++()
	{
		next();

		return *this;
	}

	NEIteratorBase& NEIteratorBase::operator+(type_count new_step)
	{
		next(new_step);

		return *this;
	}
}