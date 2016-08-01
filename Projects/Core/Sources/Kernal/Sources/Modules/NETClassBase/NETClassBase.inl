#pragma once

#include "../NETSuperClassDeterminder/NETSuperClassDeterminder.hpp"
#include "../NETMetaClassDeterminder/NETMetaClassDeterminder.hpp"
#include "../NETTraitDeterminder/NETTraitDeterminder.hpp"
#include "../NEClassBase/NEClassBase.hpp"

namespace NE
{
	///	@class	NETClassBase
	///	@brief	Implemented common method and data among specialized from NETClassBase
	///			class.
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
		virtual const NEClassBase& getClass() const;
		virtual const type_bool& isRegistered() const;
		virtual const NETString& getName() const;
		virtual const NEClassBaseList& getSuperClasses() const;
		virtual const NEClassBaseList& getChildrenClasses() const;
		virtual type_bool isMetaClassDefined() const;
		virtual type_bool isInstantiable() const;
		virtual type_bool isTemplate() const;
		virtual type_bool isBuiltInClass() const;
		virtual const NEClassBase& getTraitClass() const;
		///	@brief	returns this ClassIdentifer.
		///			As you can inspect codes, this returns the static variable.
		virtual const NEHeader& getHeader() const;
		virtual const NEPackage& getPackage() const;

	public:
		static const type_bool& isRegisteredStatically();
		static const NEClassBaseList& getSuperClassesStatically();
		static const NEClassBaseList& getChildrenClassesStatically();
		static const NEHeader& getHeaderStatically();
		static const NEClassBase& getClassStatically();
		static const NETString& getNameStatically();
		static const type_id& getIdStatically();
		static type_bool isMetaClassDefinedStatically();
		static type_bool isInstantiableStatically();
		static type_bool isTemplateStatically();
		static type_bool isBuiltInClassStatically();
		static const NEClassBase& getTraitClassStatically();
	};
}