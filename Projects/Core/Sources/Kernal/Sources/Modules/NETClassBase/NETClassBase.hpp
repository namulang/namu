#pragma once

#include "../../Includes/Includes.hpp"
#include "../NETClass/define/ClassMacro.hpp"
#include "../NEClassBase/NEClassBase.hpp"
#include "../NEWString/NEWString.hpp"
#include "../NEString/NEString.hpp"
#include "../NETString/NETString.hpp"
#include "../NEClassBaseList/NEClassBaseList.hpp"
#include "../NETADTChecker/NETADTChecker.hpp"
#include "../NETTemplateChecker/NETTemplateChecker.hpp"
#include "../NETSuperClassDeterminder/NETSuperClassDeterminder.hpp"
#include "../NETMetaClassDeterminder/NETMetaClassDeterminder.hpp"
#include "../NETTraitDeterminder/NETTraitDeterminder.hpp"
#include "../NETDerivedClassChecker/NETDerivedClassChecker.hpp"
#include "../NEUnknown/NEUnknown.hpp"

namespace NE
{
	template <typename T, type_bool IS_DERIVED_OF_MODULE=NETDerivedClassChecker<T, NEModule>::IS_DERIVED_OF>
	class NETClassBase : public NETClassBaseCommon<T>
	{
	public:
		typedef NETClassBase<T> This;
		typedef NEClassBase Super;
		//    type determind:
		typedef typename NETMetaClassDeterminder<T>::MetaClass MetaClass;
		typedef typename NETTraitDeterminder<T>::Trait Trait;
		typedef typename NETSuperClassDeterminder<T>::Super SuperTrait;

	public:
		friend class NEClassManager;

	public:
		virtual type_bool isMetaClassDefined() const;
		virtual type_bool isInstantiable() const;
		virtual type_bool isTemplate() const;
		virtual type_bool isBuiltInClass() const;
		virtual const NEClassBase& getTraitClass() const;
		///	@brief	returns this ClassIdentifer.
		///			As you can inspect codes, this returns the static variable.
		///	@remark	ClassIdentifier's Name attribute doesn't mean ClassName only.
		///			In fact, it consists of "PackageName(which contains this class)::ClassName". 
		///			for instance,
		///				* if NETClassBaseCommon<MyClass>::getName returns "class MyClass" as result of 'typeid(T)',
		///				* and MyClass is distributed within 'MyPackage.dll/so',
		///
		///				NETClassBaseCommon<MyClass>::getIdentifier's Name would be, 
		///					= "MyPackage" + "::" + getName();
		///					= "MyPackage::class MyClass"
		virtual const NEIdentifier& getIdentifier() const;
	protected:
		virtual NEIdentifier& _getIdentifier();

	public:
		static const NEClassBase& getTraitClassStatically();

	public:
		static const type_bool IS_TEMPLATE = NETTemplateChecker<T>::IS_TEMPLATE;
		static const type_bool IS_BUILT_IN_CLASS = NETDerivedClassChecker<T, NEObject>::IS_DERIVED_OF;
		static const type_bool IS_METACLASS_DEFINED = NETMetaClassChecker<T>::IS_METACLASS_DEFINED;
	};
}

#include "NETClassBase.inl"
#include "Specialization.hpp"