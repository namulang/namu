#pragma once

#pragma message("NETClassBase.inl - 1")
#include "../NETSuperClassDeterminder/NETSuperClassDeterminder.hpp"
#pragma message("NETClassBase.inl - 2")
#include "../NETMetaClassDeterminder/NETMetaClassDeterminder.hpp"
#pragma message("NETClassBase.inl - 3")
#include "../NETTraitDeterminder/NETTraitDeterminder.hpp"
#pragma message("NETClassBase.inl - 4")
#include "../NEClassBase/NEClassBase.hpp"
#pragma message("NETClassBase.inl - 5")
#include "../NETClassMetaClass/NETClassMetaClass.hpp"
#pragma message("NETClassBase.inl - 6")

namespace NE
{
	///	@class	NETClassBase
	///	@brief	Implemented common method and data among specialized from NETClassBase
	///			class.
	template <typename T>
	class NETClassBase : public NEClassBase
	{
		NE_DECLARE_CLASS_ONLY(NETClassBase, NEClassBase)

	public:
		typedef typename NETTraitDeterminder<T>::Trait Trait;

	public:
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

	public:
		virtual const type_id& getId() const;

	public:
		static const type_bool& isRegisteredStatically();
		static const NEClassBaseList& getSuperClassesStatically();
		static const NEClassBaseList& getChildrenClassesStatically();
		static const NEHeader& getHeaderStatically();
		static const NETString& getNameStatically();
		static const type_id& getIdStatically();
		static type_bool isMetaClassDefinedStatically();
		static type_bool isInstantiableStatically();
		static type_bool isTemplateStatically();
		static type_bool isBuiltInClassStatically();
		static const NEClassBase& getTraitClassStatically();

	private:
		virtual const NEPackagePtr& _getPackage() const;
	};
}