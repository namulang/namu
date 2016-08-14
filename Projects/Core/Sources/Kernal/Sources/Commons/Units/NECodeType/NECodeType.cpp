#include "NECodeType.hpp"

namespace NE
{
	NE_DLL NECodeType::NECodeType()
		: SuperClass(), _is_type_fixed(false)
	{
		ThisClass::release();
	}

	NE_DLL NECodeType::NECodeType(CodeType new_codetype)
		: SuperClass(), _codetype(new_codetype), _is_type_fixed(false)
	{
		if(new_codetype != NECodeType::UNDEFINED)
			_is_type_fixed = true;
	}

	NE_DLL NECodeType::NECodeType(CodeType new_codetype, type_bool is_type_fixed)
		: SuperClass(), _codetype(new_codetype), _is_type_fixed(is_type_fixed)
	{

	}

	NE_DLL NECodeType::NECodeType(const ThisClass& rhs)
		: SuperClass(rhs), _codetype(rhs._codetype), _is_type_fixed(rhs._is_type_fixed)
	{
		
	}

	NECodeType NE_DLL &NECodeType::operator=(const ThisClass& source)
	{
		if (this == &source) return *this;

		return _assign(source);
	}

	type_bool NE_DLL NECodeType::operator==(const ThisClass& source) const
	{
		return	_codetype == source._codetype;
				//_is_type_fixed == source._is_type_fixed	;
	}

	type_bool NECodeType::operator==(const NECodeType::CodeType source) const
	{
		return _codetype == source;
	}

	NECodeType::CodeType NE_DLL NECodeType::getCodeType() const 
	{
		return _codetype;
	}

	type_result NE_DLL NECodeType::setCodeType(CodeType new_one) 
	{
		if(	new_one == UNDEFINED						||
			(isTypeFixed() && _codetype != UNDEFINED)	)
			return RESULT_SUCCESS | RESULT_ABORT_ACTION;

		_codetype = new_one;
		return RESULT_SUCCESS;
	}

	type_bool NE_DLL NECodeType::isTypeFixed() const
	{
		return _is_type_fixed;
	}

	void NE_DLL NECodeType::release() {
		if( ! _is_type_fixed)
			_codetype = UNDEFINED;
	}

	type_result NE_DLL NECodeType::isValid() const
	{
		if(	_codetype <= CODETYPE_START ||
			_codetype >= CODETYPE_END	)
			return RESULT_TYPE_WARNING;

		return RESULT_SUCCESS;
	}

	NEBinaryFileSaver NE_DLL &NECodeType::serialize(NEBinaryFileSaver& saver) const
	{
		return saver << static_cast<type_int>(_codetype) << _is_type_fixed;
	}

	NEBinaryFileLoader NE_DLL &NECodeType::serialize(NEBinaryFileLoader& loader)
	{
		type_int buffer = 0;
		loader >> buffer;
		_codetype = CodeType(buffer);

		return loader >> _is_type_fixed;
	}

	NECodeType NE_DLL &NECodeType::_assign(const ThisClass& source)
	{
		setCodeType(source._codetype);

		return *this;
	}

	type_bool NE_DLL NECodeType::isAcceptableType(const NECodeType& source) const
	{
		return  ! isTypeFixed()			||
				! source.isTypeFixed()	||
				operator==(source)		;
	}

	type_bool NECodeType::operator!=(const ThisClass& source) const
	{
		return ! operator==(source);
	}

	type_bool NECodeType::operator!=(const NECodeType::CodeType source) const
	{
		return ! operator==(source);
	}

	type_bool NECodeType::operator<(const NECodeType::CodeType source) const
	{
		return _codetype < source;
	}

	type_bool NECodeType::operator<(const ThisClass& source) const
	{
		return _codetype < source._codetype;
	}

	type_bool NECodeType::operator<=(const NECodeType::CodeType source) const
	{
		return _codetype <= source;
	}

	type_bool NECodeType::operator<=(const ThisClass& source) const
	{
		return _codetype <= source._codetype;
	}

	type_bool NECodeType::operator>(const NECodeType::CodeType source) const
	{
		return _codetype > source;
	}

	type_bool NECodeType::operator>(const ThisClass& source) const
	{
		return _codetype > source._codetype;
	}

	type_bool NECodeType::operator>=(const NECodeType::CodeType source) const
	{
		return _codetype >= source;
	}

	type_bool NECodeType::operator>=(const ThisClass& source) const
	{
		return _codetype >= source._codetype;
	}
}