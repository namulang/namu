#include "NEArgumentBase.hpp"
#include "../Kernal/Kernal.hpp"

namespace NE
{
	bool NEArgumentBase::operator==(const NEArgumentBase& source) const
	{
		return	SuperClass::operator==(source)				&&
				_type_validation == source._type_validation	;
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

		return saver << _type_validation;
	}
	NEBinaryFileLoader& NEArgumentBase::serialize(NEBinaryFileLoader& loader)
	{
		SuperClass::serialize(loader);

		NEType::Type validator = NEType::UNDEFINED;
		loader >> validator;

		return loader;
	}

	NEArgumentBase::NEArgumentBase(NEType::Type type)
		: _type_validation(type)
	{

	}

	NEArgumentBase::NEArgumentBase(const ThisClass& rhs)
		: SuperClass(rhs), _type_validation(rhs._type_validation)
	{

	}

	NEType::Type NEArgumentBase::getTypeToBeBinded() const
	{
		return _type_validation;
	}

	void NEArgumentBase::_release()
	{
		_type_validation = NEType::UNDEFINED;
	}

	NEArgumentBase::~NEArgumentBase()
	{

	}

	NEType::Type NEArgumentBase::getType() const
	{
		return NEType::NEARGUMENT_BASE;
	}

	type_result NEArgumentBase::bind()
	{
		if( ! isNeedingBinding()	||
			isBinded()				)
			return RESULT_SUCCESS | RESULT_ABORT_ACTION;

		return SuperClass::bind();
	}

	bool NEArgumentBase::isValidToBind(const NEObject& to_be_bind) const
	{
		return NEType::isValidHierachy(
			getTypeToBeBinded(), to_be_bind.getType()
		);
	}

	const NEKey& NEArgumentBase::getValueKey() const
	{
		return getBinded();
	}

	NEKey& NEArgumentBase::getValueKey()
	{
		return getBinded();
	}
}