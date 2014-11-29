
#include "NEArgumentBase.hpp"
#include "../../../Modules/Kernal/Kernal.hpp"
#include "../../../Modules/NEArgumentBaseList/NEArgumentBaseList.hpp"

namespace NE
{
	type_result NEArgumentBase::unbind()
	{
		_setUpdateReservedFlag(false);

		return SuperClass::unbind();
	}
	bool NEArgumentBase::operator==(const NEArgumentBase& source) const
	{
		return	SuperClass::operator==(source)					&&
			_type_validation == source._type_validation		&&
			_is_update_reserved == source._is_update_reserved;
	}
	bool NEArgumentBase::operator!=(const NEArgumentBase& source) const
	{
		return ! operator==(source);
	}
	type_result NEArgumentBase::isValid() const
	{
		return RESULT_SUCCESS;
	}
	bool NEArgumentBase::isNeedingBinding() const
	{
		return	getKeyName().getLength() > 0	&&
			getKeyName()[0] != 0;
	}
	void NEArgumentBase::release() 
	{
		SuperClass::release();

		_release();
	}
	NEBinaryFileSaver& NEArgumentBase::serialize(NEBinaryFileSaver& saver) const
	{
		SuperClass::serialize(saver);

		return saver << _type_validation << _is_update_reserved;
	}
	NEBinaryFileLoader& NEArgumentBase::serialize(NEBinaryFileLoader& loader)
	{
		cancleUpdate();

		SuperClass::serialize(loader);

		NEType::Type validator = NEType::UNDEFINED;
		loader >> validator >> _is_update_reserved;

		return loader;		
	}

	NEArgumentBase::NEArgumentBase(NEType::Type type)
		: _type_validation(type), _is_update_reserved(false)
	{

	}

	NEArgumentBase::NEArgumentBase(const ThisClass& rhs)
		: SuperClass(rhs), _type_validation(rhs._type_validation), _is_update_reserved(rhs._is_update_reserved)
	{

	}

	NEType::Type NEArgumentBase::getTypeToBeBinded() const
	{
		return _type_validation;
	}

	bool NEArgumentBase::isUpdateReserved() const
	{
		return _is_update_reserved;
	}

	void NEArgumentBase::_setUpdateReservedFlag(bool new_state)
	{
		_is_update_reserved = new_state;
	}

	type_result NEArgumentBase::reserveUpdate()
	{
		if (isUpdateReserved()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;

		_setUpdateReservedFlag(true);

		return _getArguments().push(this);
	}

	type_result NEArgumentBase::cancleUpdate()
	{
		if( ! isUpdateReserved()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;		
		_setUpdateReservedFlag(false);

		type_index index = _getArguments().find(this);
		if(index == NE_INDEX_ERROR)	return RESULT_TYPE_WARNING;

		return _getArguments().remove(index);
	}

	NEArgumentBaseList& NEArgumentBase::_getArguments()
	{
		static NEArgumentBaseList list;

		return list;
	}

	void NEArgumentBase::_release()
	{
		cancleUpdate();

		_is_update_reserved = false;

		_type_validation = NEType::UNDEFINED;
	}

	NEArgumentBase::~NEArgumentBase()
	{
		_release();
	}
}