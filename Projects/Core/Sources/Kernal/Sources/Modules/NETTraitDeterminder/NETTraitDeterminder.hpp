#pragma once

#include "../NEUnknown/NEUnknown.hpp"
#include "../NETypeChecker/NETypeChecker.hpp"

namespace NE
{
	template <typename T>
	class NETTraitDeterminder : public NETypeChecker
	{
	public:
		typedef NEUnknown Trait;
		typedef NEUnknown Template;
	};
	template <typename X, template<typename> class _Template>
	class NETTraitDeterminder<Template<X>> : public NETypeChecker
	{
	public:
		typedef X Trait;
		typedef _Template Template;
	};
}