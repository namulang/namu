#include "NEArgumentBase.hpp"
#include "../../../Modules/Kernal/Kernal.hpp"

namespace NE
{
	bool NEArgumentBase::operator==(const NEArgumentBase& source) const
	{
		return	SuperClass::operator==(source)					&&
			_type_validation == source._type_validation		&&
			_is_needing_update == source._is_needing_update;
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

		_is_needing_update = false;

		_type_validation = NEType::UNDEFINED;
	}
	NEBinaryFileSaver& NEArgumentBase::serialize(NEBinaryFileSaver& saver) const
	{
		SuperClass::serialize(saver);

		return saver << _type_validation << _is_needing_update;
	}
	NEBinaryFileLoader& NEArgumentBase::serialize(NEBinaryFileLoader& loader)
	{
		SuperClass::serialize(loader);

		NEType::Type validator = NEType::UNDEFINED;
		loader >> validator >> _is_needing_update;

		return loader;		
	}

	NEArgumentBase::NEArgumentBase(NEType::Type type)
		: _type_validation(type), _is_needing_update(false)
	{

	}

	NEArgumentBase::NEArgumentBase(const ThisClass& rhs)
		: SuperClass(rhs), _type_validation(rhs._type_validation), _is_needing_update(rhs._is_needing_update)
	{

	}

	NEType::Type NEArgumentBase::getTypeToBeBinded() const
	{
		return _type_validation;
	}

	bool NEArgumentBase::isNeedingUpdate() const
	{
		return _is_needing_update;
	}

	void NEArgumentBase::_setNeedingUpdate(bool needing_update)
	{
		_is_needing_update = needing_update;
	}
}