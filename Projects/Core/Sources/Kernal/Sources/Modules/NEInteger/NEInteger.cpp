#include "NEInteger.hpp"
#include "../NETClass/NETClass.cpp"

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
}