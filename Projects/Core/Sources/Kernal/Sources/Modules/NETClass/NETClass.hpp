#pragma once

#include "../NETMetaClassDeterminder/NETMetaClassDeterminder.hpp"
#include "../NETInterface/NETInterface.hpp"
#include "../NETConcreteClass/NETConcreteClass.hpp"
#include "../NETUnknownMetaClass/NETUnknownMetaClass.hpp"
#include "../NETClass/define/ClassMacro.hpp"

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