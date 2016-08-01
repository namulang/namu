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
		virtual const NEClassBaseList& getSubClasses() const;
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
		///				* if NETClassBase<MyClass>::getName returns "class MyClass" as result of 'typeid(T)',
		///				* and MyClass is distributed within 'MyPackage.dll/so',
		///
		///				NETClassBase<MyClass>::getIdentifier's Name would be, 
		///					= "MyPackage" + "::" + getName();
		///					= "MyPackage::class MyClass"
		virtual const NEIdentifier& getIdentifier() const;
	protected:
		virtual type_result _setRegistered(type_bool new_is_registered);

	public:
		static const type_bool& isRegisteredStatically();
		static const NEClassBaseList& getSuperClassesStatically();
		static const NEClassBaseList& getSubClassesStatically();
		static const NEIdentifier& getIdentifierStatically();
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