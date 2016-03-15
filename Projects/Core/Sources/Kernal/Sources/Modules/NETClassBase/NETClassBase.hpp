#pragma once

#include "../NEClassBase/NEClassBase.hpp"
#include "../NETADTChecker/NETADTChecker.hpp"
#include "../NETSuperClassDeterminder/NETSuperClassDeterminder.hpp"
#include "../NETMetaClassDeterminder/NETMetaClassDeterminder.hpp"
#include "../NETTraitDeterminder/NETTraitDeterminder.hpp"
#include "../NETBuiltInChecker/NETBuiltInChecker.hpp"

namespace NE
{

	template <typename T>
	class NETClassBase : public NEClassBase
	{
	public:
		const type_tchar* getName() const
		{
			return typeid(T).name();
		}
		//    type determind:
		typedef typename NETTraitDeterminder<T>::Trait Trait;
		typedef typename NETMetaClassDeterminder<T>::MetaClass MetaClass;

	public:
		virtual type_bool isHavingMetaClass() const
		{
			return IS_METACLASS_DEFINED;
		}
		virtual type_bool isInterface() const
		{
			return IS_ADT;    //    Can't know because World check whether it's by MetaClass.
		}
		virtual type_bool isTemplate() const
		{
			return IS_TEMPLATE;
		}
		virtual type_bool isBuiltInClass() const
		{
			return IS_BUILT_IN_CLASS;
		}
		virtual const NEClassBase& getTraitClass()
		{
			return getTraitClassStatically();
		}

	public:
		static const NEClassBase& getTraitClassStatically()
		{
			static NETClass<Trait> _inner;

			return _inner;
		}

	public:
		static const type_bool IS_ADT = NETADTChecker<T>::IS_ADT;
		static const type_bool IS_TEMPLATE = NETTemplateChecker<T>::IS_TEMPLATE;
		static const type_bool IS_BUILT_IN_CLASS = NETBuiltInClassChecker<T>::IS_BUILT_IN_CLASS;
		static const type_bool IS_METACLASS_DEFINED = NETMetaClassChecker<T>::IS_METACLASS_DEFINED;
	};

	//    Specialize NETClass for not templating NETClass<Unknown> class reculsively.
	template <>
	class NETClassBase<NEUnknown> : public NEClassBase
	{
	public:
		//    type determind:
		typedef NEUnknown Trait;
		typedef NETUnknownMetaClass<NEUnknown> MetaClass;

		virtual type_bool isHavingMetaClass() const
		{
			return IS_METACLASS_DEFINED;
		}
		virtual type_bool isInterface() const
		{
			return IS_ADT;    //    Can't know because World check whether it's by MetaClass.
		}
		virtual type_bool isTemplate() const
		{
			return IS_TEMPLATE;
		}
		virtual type_bool isBuiltInClass() const
		{
			return IS_BUILT_IN_CLASS;
		}
		virtual const NEClassBase& getTraitClass()
		{
			return getTraitClassStatically();
		}

	public:
		static const NEClassBase& getTraitClassStatically()
		{
			static NETClassBase<NEUnknown> _inner;

			return _inner;
		}

	public:
		static const type_bool IS_ADT = true;
		static const type_bool IS_TEMPLATE = false;
		static const type_bool IS_BUILT_IN_CLASS = true;
		static const type_bool IS_METACLASS_DEFINED = false;
	};
	template <>
	class NETClassBase<NEAdam> : public NEClassBase
	{
	public:
		//    type determind:
		typedef NEUnknown Trait;
		typedef NETUnknownMetaClass<NEAdam> MetaClass;

		virtual type_bool isHavingMetaClass() const
		{
			return IS_METACLASS_DEFINED;
		}
		virtual type_bool isInterface() const
		{
			return IS_ADT;    //    Can't know because World check whether it's by MetaClass.
		}
		virtual type_bool isTemplate() const
		{
			return IS_TEMPLATE;
		}
		virtual type_bool isBuiltInClass() const
		{
			return IS_BUILT_IN_CLASS;
		}
		virtual const NEClassBase& getTraitClass()
		{
			return getTraitClassStatically();
		}

	public:
		static const NEClassBase& getTraitClassStatically()
		{
			static NETClassBase<NEAdam> _inner;

			return _inner;
		}

	public:
		static const type_bool IS_ADT = true;
		static const type_bool IS_TEMPLATE = false;
		static const type_bool IS_BUILT_IN_CLASS = true;
		static const type_bool IS_METACLASS_DEFINED = false;
	};
}