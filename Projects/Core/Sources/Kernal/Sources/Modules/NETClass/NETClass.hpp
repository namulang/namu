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
		using NETClassBase<T>::IS_METACLASS_DEFINED;
		using NETClassBase<T>::IS_TEMPLATE;
		using NETClassBase<T>::IS_BUILT_IN_CLASS;
		using NETClassBase<T>::getTraitClassStatically;
		using NETClassBase<T>::getNameStatically;
		using NETClassBase<T>::isRegisteredStatically;		

	public:
		//	Why this static variable was defined into NETClass, while the others are 
		//	NETClassBase?:
		//		NETADTChecker<T> checks given type T is a kind of ADT or not by lett
		//		ing compiler cast T::MetaClass to NETInterface<T> implicly at compil
		//		e time.
		//		But, unfortunatly, NETInterface<T> is a derived one of NETClassBase,
		//		if NETClassBase has NETADTChecker<T> like as other checkers, this m
		//		akes templating class reclusively. 
		//
		//			NETClassBase -> NETADTChecker -> NETInterface -> NETClassBase		
		static const type_bool IS_ADT = NETADTChecker<T>::IS_ADT;
	};
}