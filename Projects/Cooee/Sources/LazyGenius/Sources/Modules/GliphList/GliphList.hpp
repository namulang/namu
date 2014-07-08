#pragma once

#include "../Gliph/Gliph.hpp"

namespace LG
{
	template
	class NE_DLL NEListTemplate<Gliph*, false>;
	
	class NE_DLL GliphList : public NEListTemplate<Gliph*, false>
	{
	public:
		typedef NEListTemplate<Gliph*, false> SuperClass;

		GliphList(Window* new_owner): owner(new_owner) {}
		GliphList(Window* new_owner, const GliphList& rhs)
			: SuperClass(rhs), owner(new_owner) 
		{
			int a = 5;
		}
		virtual type_result setElement(type_index index, const Gliph* const source) {
			Gliph* casted = (Gliph*) source;
			casted->owner = owner;

			return SuperClass::setElement(index, source);
		}
		virtual type_index insert(type_index index, const Gliph* const source) {
			Gliph* casted = (Gliph*) source;
			casted->owner = owner;

			return SuperClass::insert(index, source);
		}

		Window* owner;
	};
}