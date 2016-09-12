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

	type_bool NEIteratorBase::operator==(const This& rhs) const
	{
		if(this == &rhs) return true;

		return &get() == &rhs.get();
	}

	type_bool NEIteratorBase::operator!=(const This& rhs) const
	{
		return ! operator==(rhs);
	}

	type_result NEIteratorBase::next()
	{
		return next(1);
	}
}