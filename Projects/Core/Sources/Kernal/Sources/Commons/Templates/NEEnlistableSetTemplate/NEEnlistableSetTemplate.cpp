#include "NEEnlistableSetTempate.hpp"

namespace NE
{
	typedef NENamedUnit T;
	typedef NEEnlistableSetTemplate<NENamedUnit> ThisClass;

	NEEnlistableSetTemplate<NENamedUnit>::NEEnlistableSetTemplate(const NECodeType& script_type, const NECodeType& name_type)
		: T(script_type, name_type), _manager(&NEGlobalManagerOffer::getGlobalManager()), _is_enlisted(false)
	{
		//	getGlobalManagerOnCopyConstructor에 관하여:
		//		NEIndexedModuleSet.cpp에 관련 주석을 참고하라
	}
	NEEnlistableSetTemplate<NENamedUnit>::NEEnlistableSetTemplate(const ThisClass& source)
		: T(source), _manager(&NEGlobalManagerOffer::getGlobalManager()), _is_enlisted(false)
	{
		//	getGlobalManagerOnCopyConstructor에 관하여:
		//		NEIndexedModuleSet.cpp에 관련 주석을 참고하라
	}

	const ThisClass& NEEnlistableSetTemplate<NENamedUnit>::operator=(const ThisClass& source)
	{
		/*
		_manager를 복사하지 않도록 하기 위해서 operator=를 정의한다.
		*/
		T::operator=(source);

		return *this;
	}

	NEEnlistableManager& NEEnlistableSetTemplate<NENamedUnit>::getManager()
	{
		return *_manager;
	}
	const NEEnlistableManager& NEEnlistableSetTemplate<NENamedUnit>::getManager() const
	{
		return *_manager;
	}
	bool NEEnlistableSetTemplate<NENamedUnit>::isManaged() const
	{
		return _manager != NE_NULL;
	}
	bool NEEnlistableSetTemplate<NENamedUnit>::isEnlisted() const
	{
		return _is_enlisted;
	}
	NEBinaryFileSaver& NEEnlistableSetTemplate<NENamedUnit>::serialize(NEBinaryFileSaver& saver) const
	{
		SuperClass::serialize(saver);

		return saver << _is_enlisted;
	}
	NEBinaryFileLoader& NEEnlistableSetTemplate<NENamedUnit>::serialize(NEBinaryFileLoader& loader)
	{
		SuperClass::serialize(loader);

		return loader >> _is_enlisted;
	}
	type_result NEEnlistableSetTemplate<NENamedUnit>::_setManager(NEEnlistableManager& manager)
	{
		_manager = &manager;

		return RESULT_SUCCESS;
	}
	type_result NEEnlistableSetTemplate<NENamedUnit>::_setEnlisted(bool enlisted)
	{
		_is_enlisted = enlisted;

		return RESULT_SUCCESS;
	}
}