#pragma once

#include "../NEClassBase/NEClassBase.hpp"
#include "../NETTypeChecker/NETTypeChecker.hpp"

namespace NE
{
	template <typename T, template <typename...> MetaClass = typename T::MetaClass>
	class NETClass : public MetaClass<T>
	{
		//	Declarations:
	public:

		//	type checkings:
	public:
		typedef char no;
		typedef short yes;

		//		checkers:
	private:
		template <template<typename> class Y, typename X>
		static yes _isTemplate(Y<X>*);
		static no _isTemplate(...);
	public:
		static const bool IS_TEMPLATE = sizeof(_isTemplate((T*)0)) == sizeof(yes);
		

	private:
		static no _isAdt(...);
		static yes _isAdt(NETInterface<T>*);
	public:
		static const bool IS_ADT = sizeof(_isAdt((typename MetaClass<T>*)0)) == sizeof(yes);
	};
}

#include "NETClass.inl"
#include "Specialization.inl"