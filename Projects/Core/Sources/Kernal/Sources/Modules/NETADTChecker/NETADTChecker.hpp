#pragma once

#include "../NETMetaClassChecker/NETMetaClassChecker.hpp"

namespace NE
{
	//    ADT Checker:
	//        if given parameterized type 'T' doesn't have any MetaClass typedef,
	//        This can't check whether it's sort of ADT or not.
	//        Because checking ADT process can't be determined by built-in keywords of
	//        native C++. So, we must implement it by requesting user to add the
	//        supplicant hint about ADT from class author, the MetaClass typedef.
	//
	//        forward declaration:
	
	template <typename T>
	class NETInterface;

	template <typename T, bool IS_METACLASS_DEFINED = NETMetaClassChecker<T>::IS_METACLASS_DEFINED>
	class NETADTChecker : public NETypeChecker
	{
	public:
		static const bool IS_ADT = false;
	};
	//    specialization:
	template <typename T>
	class NETADTChecker<T, true> : public NETypeChecker
	{

	private:
		static yes _isADT(NETInterface<T>*);
		static no _isADT(...);

	public:
		static const type_bool IS_ADT = sizeof(_isADT((typename T::MetaClass*)0)) == sizeof(yes);
	};
}