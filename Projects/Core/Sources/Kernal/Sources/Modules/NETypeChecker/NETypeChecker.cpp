#include "NETypeChecker.hpp"
#include "../NETClass/NETClass.hpp"

namespace NE
{
	NEClassBase& NETypeChecker::getClassStatically()
	{
		static NETClass<This> inner;

		return inner;
	}
}