#include "NEBank.hpp"

namespace NE
{
	typedef NEBank ThisClass;

	NE_DLL NEBank::NEBank()
		: SuperClass()
	{

	}

	NE_DLL NEBank::NEBank(const NECodeType& source)
		: SuperClass(), _type(source)
	{

	}

	NE_DLL NEBank::NEBank(const ThisClass& source)
		: SuperClass(source), _type(source._type)
	{

	}

	ThisClass NE_DLL &ThisClass::operator=(const ThisClass& source)
	{
		if(this == &source) return *this;

		SuperClass::operator=(source);

		return _assign(source);
	}

	bool NE_DLL ThisClass::operator==(const ThisClass& source) const
	{
		if(SuperClass::operator!=(source)) return false;

		return _type == source._type;
	}

	bool NE_DLL ThisClass::operator!=(const ThisClass& source) const
	{
		return ! operator==(source);
	}

	NECodeType NE_DLL &ThisClass::getCodeType()
	{
		return _type;
	}

	const NECodeType NE_DLL &ThisClass::getCodeType() const
	{
		return _type;
	}

	NEObject NE_DLL &ThisClass::clone() const
	{
		return *(new ThisClass(*this));
	}

	void NE_DLL ThisClass::release() 
	{
		SuperClass::release();

		_type.release();
	}

	NEBinaryFileSaver NE_DLL &ThisClass::serialize(NEBinaryFileSaver& saver) const
	{
		SuperClass::serialize(saver);

		return saver << _type;
	}

	NEBinaryFileLoader NE_DLL &ThisClass::serialize(NEBinaryFileLoader& loader)
	{
		SuperClass::serialize(loader);

		return loader >> _type;
	}

	type_result NE_DLL ThisClass::isValid() const
	{
		type_result result = RESULT_SUCCESS;
		if(NEResult::hasError(result = SuperClass::isValid())) return result;

		return _type.isValid();
	}

	NEType::Type NE_DLL ThisClass::getType() const
	{
		return NEType::NEBANK;
	}

	ThisClass NE_DLL &ThisClass::_assign(const ThisClass& source)
	{
		_type = source._type;

		return *this;
	}
}
