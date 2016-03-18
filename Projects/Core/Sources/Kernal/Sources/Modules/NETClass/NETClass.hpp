#pragma once

#include "../NEClassBase/NEClassBase.hpp"
#include "../NETInterface/NETInterface.hpp"
#include "../NETConcreteClass/NETConcreteClass.hpp"
#include "../NETUnknownMetaClass/NETUnknownMetaClass.hpp"

namespace NE
{
	class NE_DLL NEInterfaceClass {};	
	class NE_DLL NEConcreteClass {};

	template <typename T, typename MetaClass = NETMetaClassDeterminder<T>::MetaClass>
	class NETClass : public MetaClass
	{
	public:
		friend class NEClassManager;

	public:
		typedef typename NETClassBase<T>::MetaClass MetaClass;
		typedef typename NETClassBase<T>::Trait Trait;
		using NETClassBase<T>::IS_ADT;
		using NETClassBase<T>::IS_METACLASS_DEFINED;
		using NETClassBase<T>::IS_TEMPLATE;
		using NETClassBase<T>::IS_BUILT_IN_CLASS;
		using NETClassBase<T>::getTraitClassStatically;
		using NETClassBase<T>::getNameStatically;
		using NETClassBase<T>::isRegisteredStatically;
		using NETClassBase<T>::getSuperClassesStatically;
		using NETClassBase<T>::getSubClassesStatically;
	};
}