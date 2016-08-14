#pragma once

#include "../NETMetaClassChecker/NETMetaClassChecker.hpp"
namespace NE
{
	//    MetaClassDeterminder:
	//        Forward    declaration:
	template <typename T>
	class NETUnknownMetaClass;

	template <typename T, type_bool IS_METACLASS_DEFINED = NETMetaClassChecker<T>::IS_METACLASS_DEFINED>
	class NETMetaClassDeterminder : public NETypeChecker
	{
		typedef NETMetaClassDeterminder<T, IS_METACLASS_DEFINED> _This;
		NE_DECLARE_INTERFACE(_This, NETypeChecker)

	public:
		typedef typename T::MetaClass MetaClass;
	};
	//        Specialization:
	template <typename T>
	class NETMetaClassDeterminder<T, false> : public NETypeChecker
	{
		typedef NETMetaClassDeterminder<T, false> _This;
		NE_DECLARE_INTERFACE(_This, NETypeChecker)

	public:
		typedef NETUnknownMetaClass<T> MetaClass;
	};
}