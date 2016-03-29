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
#include "../NETBuiltInClassChecker/NETBuiltInClassChecker.hpp"
#include "../NEUnknown/NEUnknown.hpp"

namespace NE
{
	template <typename T>
	class NETClassBase : public NEClassBase
	{
	public:
		typedef NETClassBase<T> This;
		typedef NEClassBase Super;
		//    type determind:
		typedef typename NETMetaClassDeterminder<T>::MetaClass MetaClass;
		typedef typename NETTraitDeterminder<T>::Trait Trait;
		typedef typename NETSuperClassDeterminder<T>::Super SuperTrait;
	
	public:
		virtual type_bool isMetaClassDefined() const;
		virtual type_bool isInstantiable() const;
		virtual type_bool isTemplate() const;
		virtual type_bool isBuiltInClass() const;
		virtual const NEClassBase& getClass() const;
		virtual const type_bool& isRegistered() const;
		virtual const NEClassBase& getTraitClass() const;
		virtual const NETString& getName() const;
		virtual const NEClassBaseList& getSuperClasses() const;
		virtual const NEClassBaseList& getSubClasses() const;

	public:
		static const NEClassBase& getClassStatically();
		static const NEClassBase& getTraitClassStatically();
		static const NETString& getNameStatically();
		static const type_bool& isRegisteredStatically();
		static const NEClassBaseList &getSuperClassesStatically();
		static const NEClassBaseList &getSubClassesStatically();

	protected:
		virtual type_result _setRegistered(type_bool new_is_registered);

	public:
		static const type_bool IS_TEMPLATE = NETTemplateChecker<T>::IS_TEMPLATE;
		static const type_bool IS_BUILT_IN_CLASS = NETBuiltInClassChecker<T>::IS_BUILT_IN_CLASS;
		static const type_bool IS_METACLASS_DEFINED = NETMetaClassChecker<T>::IS_METACLASS_DEFINED;
	};
}

#include "NETClassBase.inl"
#include "Specialization.hpp"