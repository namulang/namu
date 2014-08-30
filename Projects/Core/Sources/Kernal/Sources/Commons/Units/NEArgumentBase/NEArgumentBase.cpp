#include "NEArgumentBase.hpp"
#include "../../../Modules/Kernal/Kernal.hpp"

namespace NE
{
	bool NEArgumentBase::operator==(const NEArgumentBase& source) const
	{
		return	SuperClass::operator==(source)				&&
				_type_validation == source._type_validation;
	}
	bool NEArgumentBase::operator!=(const NEArgumentBase& source) const
	{
		return ! operator==(source);
	}
	type_result NEArgumentBase::isValid() const
	{
		return RESULT_SUCCESS;
	}
	void NEArgumentBase::release() 
	{
		SuperClass::release();

		_type_validation = NEType::UNDEFINED;
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

	NEObject& NEArgumentBase::clone() const
	{
		return *(new ThisClass(*this));
	}

}