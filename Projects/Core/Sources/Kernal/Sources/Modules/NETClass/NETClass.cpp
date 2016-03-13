#pragma once

#include "../NEClassBase/NEClassBase.hpp"
#include "../NETInterface/NETInterface.hpp"
#include "../NETConcreteClass/NETConcreteClass.hpp"

namespace NE
{
	class NE_DLL NEInterfaceClass {};	
	class NE_DLL NEConcreteClass {};

	template <typename T, typename MetaClass = T::MetaClass>
	class NETClass : public MetaClass
	{
		//	Declarations:
	public:

		//	type checkings:
		//		typedefs:
	public:
		typedef char no;
		typedef short yes;

		//		checkers:
	private:
		static no _isAdt(...);
		static yes _isAdt(NETInterface<T>*);
	public:
		static const type_bool IS_ADT = sizeof(_isAdt((typename MetaClass*)0)) == sizeof(yes);
		static type_bool isInstantiableStatically();
		virtual type_bool isInstantiable() const;

	private:
		template <template<typename> class Y, typename X>
		static yes _isTemplate(Y<X>*);
		static no _isTemplate(...);
	public:
		static const type_bool IS_TEMPLATE = sizeof(_isTemplate((T*)0)) == sizeof(yes);
		static type_bool isTemplateStatically();
		virtual type_bool isTempate() const;

	private:
		template <typename T>
		static yes _isHavingTrait(typename T::Trait*);
		template <typename T>
		static no _isHavingTrait(...);
	public:
		static const bool IS_HAVING_TRAIT = sizeof(_isHavingTrait<T>(0)) == sizeof(yes);

	private:
		template <bool IS_TRAIT = IS_HAVING_TRAIT>
		class TT
		{
		public:
			typename typedef T::Trait Trait;
		};
		template<>
		class TT<false>
		{
		public:
			typedef T Trait;
		};
	public:
		typedef typename TT<IS_HAVING_TRAIT>::Trait Trait;

	};
}

#include "NETClass.inl"