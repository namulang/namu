#include "NEInteger.hpp"
#include "../NETClass/NETClass.hpp"

namespace NE
{
	const NEClassBase& NEInteger::getClass() const
	{
		return getClassStatically();
	}

	const NEInteger::ThisClass& NEInteger::getClassStatically()
	{
		static ThisClass _inner;

		return _inner;
	}

	NEObject& NEInteger::clone() const
	{
		return *(new NEInteger(*this));
	}

	type_result NEInteger::isValid() const
	{
		return RESULT_SUCCESS;
	}
}