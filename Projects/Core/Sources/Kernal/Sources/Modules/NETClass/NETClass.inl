#pragma once

#pragma message("NETClass.inl - 1")
#include "../NETMetaClassDeterminder/NETMetaClassDeterminder.hpp"
#pragma message("NETClass.inl - 2")
#include "../NETInterface/NETInterface.inl"
#pragma message("NETClass.inl - 3")
#include "../NETConcreteClass/NETConcreteClass.inl"
#pragma message("NETClass.inl - 4")
#include "../NETUnknownMetaClass/NETUnknownMetaClass.inl"
#pragma message("NETClass.inl - 5")
#include "../NETClass/define/ClassMacro.hpp"
#pragma message("NETClass.inl - 6")
namespace NE
{
	template <typename T, typename MetaClass = NETMetaClassDeterminder<T>::MetaClass>
	class NETClass : public MetaClass
	{
	public:
		friend class NEClassManager;

	public:
		typedef typename NETClassBase<T>::MetaClass MetaClass;
		typedef typename NETClassBase<T>::Trait Trait;
		using NETClassBase<T>::isRegisteredStatically;	
		using NETClassBase<T>::getSuperClassesStatically;
		using NETClassBase<T>::getIdentifierStatically;
		using NETClassBase<T>::getClassStatically;
		using NETClassBase<T>::getNameStatically;
		using NETClassBase<T>::getIdStatically;
		using NETClassBase<T>::isMetaClassDefinedStatically;
		using NETClassBase<T>::isInstantiableStatically;
		using NETClassBase<T>::isTemplateStatically;
		using NETClassBase<T>::isBuiltInClassStatically;
		using NETClassBase<T>::getTraitClassStatically;
	};
}

#pragma message("NETClass.inl - 7")