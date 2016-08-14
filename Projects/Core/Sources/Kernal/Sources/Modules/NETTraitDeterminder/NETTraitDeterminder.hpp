#pragma once

#include "../NEUnknown/NEUnknown.hpp"
#include "../NETypeChecker/NETypeChecker.hpp"

namespace NE
{
	template <typename T>
	class NETTraitDeterminder : public NETypeChecker
	{
		NE_DECLARE_INTERFACE(NETTraitDeterminder, NETypeChecker)
	public:
		typedef NEUnknown Trait;
	};
	template <typename X, template<typename> class Template>
	class NETTraitDeterminder<Template<X>> : public NETypeChecker
	{
		NE_DECLARE_INTERFACE(NETTraitDeterminder<Template<X>>, NETypeChecker)
	public:
		typedef X Trait;
	};
}