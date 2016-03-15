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
	};
	template <typename X, template<typename> class Template>
	class NETTraitDeterminder<Template<X>>
	{
	public:
		typedef X Trait;
	};
}