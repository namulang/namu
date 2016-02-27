#pragma warning(push)
#pragma warning(disable : 4800)
#pragma warning(disable : 4804)
#pragma warning(disable : 4146)	//	unsigned에 -를 사용함
#include "NETArithmeticKey.hpp"
#include "../NEBooleanKey/NEBooleanKey.hpp"
#include "../NEByteKey/NEByteKey.hpp"
#include "../NECharKey/NECharKey.hpp"
#include "../NEUByteKey/NEUByteKey.hpp"
#include "../NEWCharKey/NEWCharKey.hpp"
#include "../NEShortKey/NEShortKey.hpp"
#include "../NEUShortKey/NEUShortKey.hpp"
#include "../NEIntKey/NEIntKey.hpp"
#include "../NEUIntKey/NEUIntKey.hpp"
#include "../NEFloatKey/NEFloatKey.hpp"
#include "../NEDoubleKey/NEDoubleKey.hpp"
#include "../NEInt64Key/NEInt64Key.hpp"
#include "../NEStringKey/NEStringKey.hpp"
#include "../NEWStringKey/NEWStringKey.hpp"

namespace NE
{
	template <>
	type_result NE_DLL NETArithmeticKey<type_bool, NEType::NEBOOLEAN_KEY>::assign(const NEKey& source)
	{
		//	pre:
		if (!&source) return RESULT_TYPE_ERROR;
		if (this == &source) return RESULT_TYPE_ERROR;

		SuperClass::assign(source);

		//	main:
		type_result result = RESULT_SUCCESS;
		switch (source.getType())
		{
		case NEType::NEBOOLEAN_KEY:
			_value = static_cast<const NEBooleanKey&>(source).getValue();
			break;
		case NEType::NECHAR_KEY:
			_value = ((static_cast<const NECharKey&>(source)).getValue() != 0);
			break;
		case NEType::NEBYTE_KEY:
			_value = ((static_cast<const NEByteKey&>(source)).getValue() != 0);
			break;
		case NEType::NEUBYTE_KEY:
			_value = ((static_cast<const NEUByteKey&>(source)).getValue() != 0);
			break;
		case NEType::NEWCHAR_KEY:
			_value = ((static_cast<const NEWCharKey&>(source)).getValue() != 0);
			break;
		case NEType::NESHORT_KEY:
			_value = ((static_cast<const NEShortKey&>(source)).getValue() != 0);
			break;
		case NEType::NEUSHORT_KEY:
			_value = ((static_cast<const NEUShortKey&>(source)).getValue() != 0);
			break;
		case NEType::NEINT_KEY:
			_value = ((static_cast<const NEIntKey&>(source)).getValue() != 0);
			break;
		case NEType::NEUINT_KEY:
			_value = ((static_cast<const NEUIntKey&>(source)).getValue() != 0);
			break;
		case NEType::NEFLOAT_KEY:
			_value = ((static_cast<const NEFloatKey&>(source)).getValue() != 0.0f);
			break;
		case NEType::NEDOUBLE_KEY:
			_value = ((static_cast<const NEDoubleKey&>(source)).getValue() != 0.0);
			break;
		case NEType::NEINT64_KEY:
			_value = ((static_cast<const NEInt64Key&>(source)).getValue() != 0);
			break;
		case NEType::NESTRING_KEY:
			_value = (static_cast<const NEStringKey&>(source)).getValue().toBoolean();
			break;
		case NEType::NEWSTRING_KEY:
			_value = (static_cast<const NEWStringKey&>(source)).getValue().toBoolean();
			break;
		}

		return result;
	}
	template <>
	type_result NE_DLL NETArithmeticKey<type_char, NEType::NECHAR_KEY>::assign(const NEKey& source)
	{
		//	pre:
		if (!&source) return RESULT_TYPE_ERROR;
		if (this == &source) return RESULT_TYPE_ERROR;

		SuperClass::assign(source);

		//	main:
		switch (source.getType())
		{
		case NEType::NEBOOLEAN_KEY:
			_value = (static_cast<const NEBooleanKey&>(source)).getValue();
			break;
		case NEType::NECHAR_KEY:
			_value = static_cast<const NECharKey&>(source).getValue();
			break;
		case NEType::NEBYTE_KEY:
			{
				type_int byte_to_int = (static_cast<const NEByteKey&>(source)).getValue();
				NEString converter(byte_to_int);
				if (converter.getLength() > 0)
					_value = converter[0];
				else
					return RESULT_TYPE_ERROR;
			}
			break;
		case NEType::NEUBYTE_KEY:
			{
				type_int ubyte_to_int = (static_cast<const NEUByteKey&>(source)).getValue();
				NEString converter(ubyte_to_int);
				if (converter.getLength() > 0)
					_value = converter[0];
				else
					return RESULT_TYPE_ERROR;
			}
			break;
		case NEType::NEWCHAR_KEY:
			{
				NEString converter((static_cast<const NEWCharKey&>(source)).getValue());
				if (converter.getLength() > 0)
					_value = converter[0];
				else
					return RESULT_TYPE_ERROR;
			}
			break;
		case NEType::NESHORT_KEY:
			{
				type_int casted = static_cast<type_int>((static_cast<const NEShortKey&>(source)).getValue());
				NEString converter(casted);
				if (converter.getLength() > 0)
					_value = converter[0];
				else
					return RESULT_TYPE_ERROR;
			}
			break;
		case NEType::NEUSHORT_KEY:
			{
				type_int casted = static_cast<type_int>((static_cast<const NEUShortKey&>(source)).getValue());
				NEString converter(casted);
				if (converter.getLength() > 0)
					_value = converter[0];
				else
					return RESULT_TYPE_ERROR;
			}
			break;
		case NEType::NEINT_KEY:
			{
				NEString converter((static_cast<const NEIntKey&>(source)).getValue());
				if (converter.getLength() > 0)
					_value = converter[0];
				else
					return RESULT_TYPE_ERROR;
			}
			break;
		case NEType::NEUINT_KEY:
			{
				type_int uint_to_int = (static_cast<const NEUIntKey&>(source)).getValue();
				NEString converter(uint_to_int);
				if (converter.getLength() > 0)
					_value = converter[0];
				else
					return RESULT_TYPE_ERROR;
			}
			break;
		case NEType::NEFLOAT_KEY:
			{
				NEString converter((static_cast<const NEFloatKey&>(source)).getValue());
				if (converter.getLength() > 0)
					_value = converter[0];
				else
					return RESULT_TYPE_ERROR;
			}
			break;
		case NEType::NEDOUBLE_KEY:
			{
				NEString converter((static_cast<const NEDoubleKey&>(source)).getValue());
				if (converter.getLength() > 0)
					_value = converter[0];
				else
					return RESULT_TYPE_ERROR;
			}
			break;
		case NEType::NEINT64_KEY:
			{
				int casted = static_cast<type_int>((static_cast<const NEInt64Key&>(source)).getValue());
				NEString converter(casted);
				if (converter.getLength() > 0)
					_value = converter[0];
				else
					return RESULT_TYPE_ERROR;
			}
			break;
		case NEType::NESTRING_KEY:
			{
				const NEString& extracted = (static_cast<const NEStringKey&>(source)).getValue();

				if (extracted.getLength() > 0)
					_value = extracted[0];
				else
					return RESULT_TYPE_ERROR;
			}
			break;
		case NEType::NEWSTRING_KEY:
			{
				NEString converted((static_cast<const NEWStringKey&>(source)).getValue());

				if (converted.getLength() > 0)
					_value = converted[0];
				else
					return RESULT_TYPE_ERROR;
			}
			break;
		}

		return RESULT_SUCCESS;
	}
	template <>
	type_result NE_DLL NETArithmeticKey<type_byte, NEType::NEBYTE_KEY>::assign(const NEKey& source)
	{
		//	pre:
		if (!&source) return RESULT_TYPE_ERROR;
		if (this == &source) return RESULT_TYPE_ERROR;

		SuperClass::assign(source);

		//	main:
		switch (source.getType())
		{
		case NEType::NEBOOLEAN_KEY:
			_value = (static_cast<const NEBooleanKey&>(source)).getValue();
			break;
		case NEType::NECHAR_KEY:
			_value = static_cast<type_byte>(NEString(static_cast<const NECharKey&>(source).getValue()).toInt());
			break;
		case NEType::NEBYTE_KEY:
			_value = static_cast<const NEByteKey&>(source).getValue();
			break;
		case NEType::NEUBYTE_KEY:
			_value = static_cast<type_byte>((static_cast<const NEUByteKey&>(source)).getValue());
			break;
		case NEType::NEWCHAR_KEY:
			_value = static_cast<type_byte>(NEWString(static_cast<const NEWCharKey&>(source).getValue()).toInt());
			break;
		case NEType::NESHORT_KEY:
			_value = static_cast<type_byte>((static_cast<const NEShortKey&>(source)).getValue());
			break;
		case NEType::NEUSHORT_KEY:
			_value = static_cast<type_byte>((static_cast<const NEUShortKey&>(source)).getValue());
			break;
		case NEType::NEINT_KEY:
			_value = static_cast<type_byte>((static_cast<const NEIntKey&>(source)).getValue());
			break;
		case NEType::NEUINT_KEY:
			_value = static_cast<type_byte>((static_cast<const NEUIntKey&>(source)).getValue());
			break;
		case NEType::NEFLOAT_KEY:
			_value = static_cast<type_byte>((static_cast<const NEFloatKey&>(source)).getValue());
			break;
		case NEType::NEDOUBLE_KEY:
			_value = static_cast<type_byte>((static_cast<const NEDoubleKey&>(source)).getValue());
			break;
		case NEType::NEINT64_KEY:
			_value = static_cast<type_byte>((static_cast<const NEInt64Key&>(source)).getValue());
			break;
		case NEType::NESTRING_KEY:
			{
				const NEString& extracted = (static_cast<const NEStringKey&>(source)).getValue();

				_value = static_cast<type_byte>(extracted.toInt());
			}
			break;
		case NEType::NEWSTRING_KEY:
			{
				const NEWString& extracted = (static_cast<const NEWStringKey&>(source)).getValue();

				_value = static_cast<type_byte>(extracted.toInt());
			}
			break;
		}

		return RESULT_SUCCESS;
	}
	template <>
	type_result NE_DLL NETArithmeticKey<type_ubyte, NEType::NEUBYTE_KEY>::assign(const NEKey& source)
	{
		//	pre:
		if (!&source) return RESULT_TYPE_ERROR;
		if (this == &source) return RESULT_TYPE_ERROR;

		SuperClass::assign(source);


		//	main:
		switch (source.getType())
		{
		case NEType::NEBOOLEAN_KEY:
			_value = (static_cast<const NEBooleanKey&>(source)).getValue();
			break;
		case NEType::NECHAR_KEY:
			_value = static_cast<type_ubyte>(NEString(static_cast<const NECharKey&>(source).getValue()).toInt());
			break;
		case NEType::NEBYTE_KEY:
			_value = static_cast<type_ubyte>((static_cast<const NEByteKey&>(source)).getValue());
			break;
		case NEType::NEUBYTE_KEY:
			_value = (static_cast<const NEUByteKey&>(source)).getValue();
			break;
		case NEType::NEWCHAR_KEY:
			_value = static_cast<type_ubyte>(NEWString(static_cast<const NEWCharKey&>(source).getValue()).toInt());
			break;
		case NEType::NESHORT_KEY:
			_value = static_cast<type_ubyte>((static_cast<const NEShortKey&>(source)).getValue());
			break;
		case NEType::NEUSHORT_KEY:
			_value = static_cast<type_ubyte>((static_cast<const NEUShortKey&>(source)).getValue());
			break;
		case NEType::NEINT_KEY:
			_value = static_cast<type_ubyte>((static_cast<const NEIntKey&>(source)).getValue());
			break;
		case NEType::NEUINT_KEY:
			_value = static_cast<type_ubyte>((static_cast<const NEUIntKey&>(source)).getValue());
			break;
		case NEType::NEFLOAT_KEY:
			_value = static_cast<type_ubyte>((static_cast<const NEFloatKey&>(source)).getValue());
			break;
		case NEType::NEDOUBLE_KEY:
			_value = static_cast<type_ubyte>((static_cast<const NEDoubleKey&>(source)).getValue());
			break;
		case NEType::NEINT64_KEY:
			_value = static_cast<type_ubyte>((static_cast<const NEInt64Key&>(source)).getValue());
			break;
		case NEType::NESTRING_KEY:
			{
				const NEString& extracted = (static_cast<const NEStringKey&>(source)).getValue();

				_value = static_cast<type_ubyte>(extracted.toInt());
			}
			break;
		case NEType::NEWSTRING_KEY:
			{
				const NEWString& extracted = (static_cast<const NEWStringKey&>(source)).getValue();

				_value = static_cast<type_ubyte>(extracted.toInt());
			}
			break;
		}

		return RESULT_SUCCESS;
	}
	template <>
	type_result NE_DLL NETArithmeticKey<type_wchar, NEType::NEWCHAR_KEY>::assign(const NEKey& source)
	{
		//	pre:
		if (!&source) return RESULT_TYPE_ERROR;
		if (this == &source) return RESULT_TYPE_ERROR;

		SuperClass::assign(source);


		//	main:
		switch (source.getType())
		{
		case NEType::NEBOOLEAN_KEY:
			_value = (static_cast<const NEBooleanKey&>(source)).getValue();
			break;
		case NEType::NECHAR_KEY:
			{
				NEWString converter((static_cast<const NECharKey&>(source)).getValue());
				if (converter.getLength() > 0)
					_value = converter[0];
				else
					return RESULT_TYPE_ERROR;
			}
			break;
		case NEType::NEBYTE_KEY:
			{
				type_int byte_to_int = (static_cast<const NEByteKey&>(source)).getValue();
				NEWString converter(byte_to_int);
				if (converter.getLength() > 0)
					_value = converter[0];
				else
					return RESULT_TYPE_ERROR;
			}
			break;
		case NEType::NEUBYTE_KEY:
			{
				type_int ubyte_to_int = (static_cast<const NEUByteKey&>(source)).getValue();
				NEWString converter(ubyte_to_int);
				if (converter.getLength() > 0)
					_value = converter[0];
				else
					return RESULT_TYPE_ERROR;
			}
			break;
		case NEType::NEWCHAR_KEY:
			_value = (static_cast<const NEWCharKey&>(source)).getValue();
			break;
		case NEType::NESHORT_KEY:
			{
				int casted = static_cast<type_int>((static_cast<const NEShortKey&>(source)).getValue());
				NEWString converter(casted);
				if (converter.getLength() > 0)
					_value = converter[0];
				else
					return RESULT_TYPE_ERROR;
			}
			break;
		case NEType::NEUSHORT_KEY:
			{
				NEWString converter((static_cast<const NEUShortKey&>(source)).getValue());
				if (converter.getLength() > 0)
					_value = converter[0];
				else
					return RESULT_TYPE_ERROR;
			}
			break;
		case NEType::NEINT_KEY:
			{
				NEWString converter((static_cast<const NEIntKey&>(source)).getValue());
				if (converter.getLength() > 0)
					_value = converter[0];
				else
					return RESULT_TYPE_ERROR;
			}
			break;
		case NEType::NEUINT_KEY:
			{
				type_int uint_to_int = (static_cast<const NEUIntKey&>(source)).getValue();
				NEWString converter(uint_to_int);
				if (converter.getLength() > 0)
					_value = converter[0];
				else
					return RESULT_TYPE_ERROR;
			}
			break;
		case NEType::NEFLOAT_KEY:
			{
				NEWString converter((static_cast<const NEFloatKey&>(source)).getValue());
				if (converter.getLength() > 0)
					_value = converter[0];
				else
					return RESULT_TYPE_ERROR;
			}
			break;
		case NEType::NEDOUBLE_KEY:
			{
				NEWString converter((static_cast<const NEDoubleKey&>(source)).getValue());
				if (converter.getLength() > 0)
					_value = converter[0];
				else
					return RESULT_TYPE_ERROR;
			}
			break;
		case NEType::NEINT64_KEY:
			{
				int casted = static_cast<type_int>((static_cast<const NEInt64Key&>(source)).getValue());
				NEWString converter(casted);
				if (converter.getLength() > 0)
					_value = converter[0];
				else
					return RESULT_TYPE_ERROR;
			}
			break;
		case NEType::NESTRING_KEY:
			{
				NEWString converted((static_cast<const NEStringKey&>(source)).getValue());

				if (converted.getLength() > 0)
					_value = converted[0];
				else
					return RESULT_TYPE_ERROR;
			}
			break;
		case NEType::NEWSTRING_KEY:
			{
				const NEWString& extracted = (static_cast<const NEWStringKey&>(source)).getValue();

				if (extracted.getLength() > 0)
					_value = extracted[0];
				else
					return RESULT_TYPE_ERROR;
			}
			break;
		}

		return RESULT_SUCCESS;
	}
	template <>
	type_result NE_DLL NETArithmeticKey<type_short, NEType::NESHORT_KEY>::assign(const NEKey& source)
	{
		//	pre:
		if (!&source) return RESULT_TYPE_ERROR;
		if (this == &source) return RESULT_TYPE_ERROR;

		SuperClass::assign(source);


		//	main:
		switch (source.getType())
		{
		case NEType::NEBOOLEAN_KEY:
			_value = (static_cast<const NEBooleanKey&>(source)).getValue();
			break;
		case NEType::NECHAR_KEY:
			{
				NEString converter((static_cast<const NECharKey&>(source)).getValue());
				_value = static_cast<type_short>(converter.toInt());
			}
			break;
		case NEType::NEBYTE_KEY:
			_value = (static_cast<const NEByteKey&>(source)).getValue();
			break;
		case NEType::NEUBYTE_KEY:
			_value = (static_cast<const NEUByteKey&>(source)).getValue();
			break;
		case NEType::NEWCHAR_KEY:
			{
				NEWString converter((static_cast<const NEWCharKey&>(source)).getValue());
				_value = static_cast<type_short>(converter.toInt());
			}
			break;
		case NEType::NESHORT_KEY:
			_value = (static_cast<const NEShortKey&>(source)).getValue();
			break;
		case NEType::NEINT_KEY:
			_value = static_cast<type_short>((static_cast<const NEIntKey&>(source)).getValue());
			break;
		case NEType::NEUINT_KEY:
			_value = static_cast<type_short>((static_cast<const NEUIntKey&>(source)).getValue());
			break;
		case NEType::NEFLOAT_KEY:
			_value = static_cast<type_short>((static_cast<const NEFloatKey&>(source)).getValue());
			break;
		case NEType::NEDOUBLE_KEY:
			_value = static_cast<type_short>((static_cast<const NEDoubleKey&>(source)).getValue());
			break;
		case NEType::NEINT64_KEY:
			_value = static_cast<type_short>((static_cast<const NEInt64Key&>(source)).getValue());
			break;
		case NEType::NESTRING_KEY:
			_value = static_cast<type_short>((static_cast<const NEStringKey&>(source)).getValue().toInt());
			break;
		case NEType::NEWSTRING_KEY:
			_value = static_cast<type_short>((static_cast<const NEWStringKey&>(source)).getValue().toInt());
			break;
		}

		return RESULT_SUCCESS;
	}
	template <>
	type_result NE_DLL NETArithmeticKey<type_ushort, NEType::NEUSHORT_KEY>::assign(const NEKey& source)
	{
		//	pre:
		if (!&source) return RESULT_TYPE_ERROR;
		if (this == &source) return RESULT_TYPE_ERROR;

		SuperClass::assign(source);


		//	main:
		switch (source.getType())
		{
		case NEType::NEBOOLEAN_KEY:
			_value = (static_cast<const NEBooleanKey&>(source)).getValue();
			break;
		case NEType::NECHAR_KEY:
			{
				NEString converter((static_cast<const NECharKey&>(source)).getValue());
				_value = static_cast<type_ushort>(converter.toInt());
			}
			break;
		case NEType::NEBYTE_KEY:
			_value = static_cast<type_ushort>((static_cast<const NEByteKey&>(source)).getValue());
			break;
		case NEType::NEUBYTE_KEY:
			_value = (static_cast<const NEUByteKey&>(source)).getValue();
			break;
		case NEType::NEWCHAR_KEY:
			{
				NEWString converter((static_cast<const NEWCharKey&>(source)).getValue());
				_value = static_cast<type_ushort>(converter.toInt());
			}
			break;
		case NEType::NESHORT_KEY:
			_value = static_cast<type_ushort>((static_cast<const NEShortKey&>(source)).getValue());
			break;
		case NEType::NEUSHORT_KEY:
			_value = (static_cast<const NEUShortKey&>(source)).getValue();
			break;
		case NEType::NEINT_KEY:
			_value = static_cast<type_ushort>((static_cast<const NEIntKey&>(source)).getValue());
			break;
		case NEType::NEUINT_KEY:
			_value = static_cast<type_ushort>((static_cast<const NEUIntKey&>(source)).getValue());
			break;
		case NEType::NEFLOAT_KEY:
			_value = static_cast<type_ushort>((static_cast<const NEFloatKey&>(source)).getValue());
			break;
		case NEType::NEDOUBLE_KEY:
			_value = static_cast<type_ushort>((static_cast<const NEDoubleKey&>(source)).getValue());
			break;
		case NEType::NEINT64_KEY:
			_value = static_cast<type_ushort>((static_cast<const NEInt64Key&>(source)).getValue());
			break;
		case NEType::NESTRING_KEY:
			_value = static_cast<type_ushort>((static_cast<const NEStringKey&>(source)).getValue().toInt());
			break;
		case NEType::NEWSTRING_KEY:
			_value = static_cast<type_ushort>((static_cast<const NEWStringKey&>(source)).getValue().toInt());
			break;
		}

		return RESULT_SUCCESS;
	}
	template <>
	type_result NE_DLL NETArithmeticKey<type_int, NEType::NEINT_KEY>::assign(const NEKey& source)
	{
		//	pre:
		if (!&source) return RESULT_TYPE_ERROR;
		if (this == &source) return RESULT_TYPE_ERROR;

		SuperClass::assign(source);


		//	main:
		switch (source.getType())
		{
		case NEType::NEBOOLEAN_KEY:
			_value = (static_cast<const NEBooleanKey&>(source)).getValue();
			break;
		case NEType::NECHAR_KEY:
			{
				NEString converter((static_cast<const NECharKey&>(source)).getValue());
				_value = converter.toInt();
			}
			break;
		case NEType::NEBYTE_KEY:
			_value = (static_cast<const NEByteKey&>(source)).getValue();
			break;
		case NEType::NEUBYTE_KEY:
			_value = (static_cast<const NEUByteKey&>(source)).getValue();
			break;
		case NEType::NEWCHAR_KEY:
			{
				NEWString converter((static_cast<const NEWCharKey&>(source)).getValue());
				_value = converter.toInt();
			}
			break;
		case NEType::NESHORT_KEY:
			_value = (static_cast<const NEShortKey&>(source)).getValue();
			break;
		case NEType::NEUSHORT_KEY:
			_value = (static_cast<const NEUShortKey&>(source)).getValue();
			break;
		case NEType::NEINT_KEY:
			_value = (static_cast<const NEIntKey&>(source)).getValue();
			break;
		case NEType::NEUINT_KEY:
			_value = static_cast<type_int>((static_cast<const NEUIntKey&>(source)).getValue());
			break;
		case NEType::NEFLOAT_KEY:
			_value = static_cast<type_int>((static_cast<const NEFloatKey&>(source)).getValue());
			break;
		case NEType::NEDOUBLE_KEY:
			_value = static_cast<type_int>((static_cast<const NEDoubleKey&>(source)).getValue());
			break;
		case NEType::NEINT64_KEY:
			_value = static_cast<type_int>((static_cast<const NEInt64Key&>(source)).getValue());
			break;
		case NEType::NESTRING_KEY:
			_value = (static_cast<const NEStringKey&>(source)).getValue().toInt();
			break;
		case NEType::NEWSTRING_KEY:
			_value = (static_cast<const NEWStringKey&>(source)).getValue().toInt();
			break;
		}

		return RESULT_SUCCESS;
	}
	template <>
	type_result NE_DLL NETArithmeticKey<type_uint, NEType::NEUINT_KEY>::assign(const NEKey& source)
	{
		//	pre:
		if (!&source) return RESULT_TYPE_ERROR;
		if (this == &source) return RESULT_TYPE_ERROR;

		SuperClass::assign(source);


		//	main:
		switch (source.getType())
		{
		case NEType::NEBOOLEAN_KEY:
			_value = (static_cast<const NEBooleanKey&>(source)).getValue();
			break;
		case NEType::NECHAR_KEY:
			{
				NEString converter((static_cast<const NECharKey&>(source)).getValue());
				_value = static_cast<type_uint>(converter.toInt());
			}
			break;
		case NEType::NEBYTE_KEY:
			_value = static_cast<type_uint>((static_cast<const NEByteKey&>(source)).getValue());
			break;
		case NEType::NEUBYTE_KEY:
			_value = (static_cast<const NEUByteKey&>(source)).getValue();
			break;
		case NEType::NEWCHAR_KEY:
			{
				NEWString converter((static_cast<const NEWCharKey&>(source)).getValue());
				_value = static_cast<type_uint>(converter.toInt());
			}
			break;
		case NEType::NESHORT_KEY:
			_value = static_cast<type_uint>((static_cast<const NEShortKey&>(source)).getValue());
			break;
		case NEType::NEUSHORT_KEY:
			_value = (static_cast<const NEUShortKey&>(source)).getValue();
			break;
		case NEType::NEINT_KEY:
			_value = static_cast<type_uint>((static_cast<const NEIntKey&>(source)).getValue());
			break;
		case NEType::NEUINT_KEY:
			_value = (static_cast<const NEUIntKey&>(source)).getValue();
			break;
		case NEType::NEFLOAT_KEY:
			_value = static_cast<type_uint>((static_cast<const NEFloatKey&>(source)).getValue());
			break;
		case NEType::NEDOUBLE_KEY:
			_value = static_cast<type_uint>((static_cast<const NEDoubleKey&>(source)).getValue());
			break;
		case NEType::NEINT64_KEY:
			_value = static_cast<type_uint>((static_cast<const NEInt64Key&>(source)).getValue());
			break;
		case NEType::NESTRING_KEY:
			_value = (static_cast<const NEStringKey&>(source)).getValue().toInt();
			break;
		case NEType::NEWSTRING_KEY:
			_value = (static_cast<const NEWStringKey&>(source)).getValue().toInt();
			break;
		}

		return RESULT_SUCCESS;
	}
	template <>
	type_result NE_DLL NETArithmeticKey<type_float, NEType::NEFLOAT_KEY>::assign(const NEKey& source)
	{
		//	pre:
		if (!&source) return RESULT_TYPE_ERROR;
		if (this == &source) return RESULT_TYPE_ERROR;

		SuperClass::assign(source);


		//	main:
		switch (source.getType())
		{
		case NEType::NEBOOLEAN_KEY:
			_value = (static_cast<const NEBooleanKey&>(source)).getValue();
			break;
		case NEType::NECHAR_KEY:
			{
				NEString converter((static_cast<const NECharKey&>(source)).getValue());
				_value = static_cast<type_float>(converter.toDouble());
			}
			break;
		case NEType::NEBYTE_KEY:
			_value = (static_cast<const NEByteKey&>(source)).getValue();
			break;
		case NEType::NEUBYTE_KEY:
			_value = (static_cast<const NEUByteKey&>(source)).getValue();
			break;
		case NEType::NEWCHAR_KEY:
			{
				NEWString converter((static_cast<const NEWCharKey&>(source)).getValue());
				_value = static_cast<type_float>(converter.toDouble());
			}
			break;
		case NEType::NESHORT_KEY:
			_value = (static_cast<const NEShortKey&>(source)).getValue();
			break;
		case NEType::NEUSHORT_KEY:
			_value = (static_cast<const NEUShortKey&>(source)).getValue();
			break;
		case NEType::NEINT_KEY:
			_value = static_cast<type_float>((static_cast<const NEIntKey&>(source)).getValue());
			break;
		case NEType::NEUINT_KEY:
			_value = static_cast<type_float>((static_cast<const NEUIntKey&>(source)).getValue());
			break;
		case NEType::NEFLOAT_KEY:
			_value = (static_cast<const NEFloatKey&>(source)).getValue();
			break;
		case NEType::NEINT64_KEY:
			_value = static_cast<type_float>((static_cast<const NEInt64Key&>(source)).getValue());
			break;
		case NEType::NEDOUBLE_KEY:
			_value = static_cast<type_float>((static_cast<const NEDoubleKey&>(source)).getValue());
			break;
		case NEType::NESTRING_KEY:
			_value = static_cast<type_float>((static_cast<const NEStringKey&>(source)).getValue().toDouble());
			break;
		case NEType::NEWSTRING_KEY:
			_value = static_cast<type_float>((static_cast<const NEWStringKey&>(source)).getValue().toDouble());
			break;
		}

		return RESULT_SUCCESS;
	}
	template <>
	type_result NE_DLL NETArithmeticKey<type_double, NEType::NEDOUBLE_KEY>::assign(const NEKey& source)
	{
		//	pre:
		if (!&source) return RESULT_TYPE_ERROR;
		if (this == &source) return RESULT_TYPE_ERROR;

		SuperClass::assign(source);


		//	main:
		switch (source.getType())
		{
		case NEType::NEBOOLEAN_KEY:
			_value = (static_cast<const NEBooleanKey&>(source)).getValue();
			break;
		case NEType::NECHAR_KEY:
			{
				NEString converter((static_cast<const NECharKey&>(source)).getValue());
				_value = converter.toDouble();
			}
			break;
		case NEType::NEBYTE_KEY:
			_value = (static_cast<const NEByteKey&>(source)).getValue();
			break;
		case NEType::NEUBYTE_KEY:
			_value = (static_cast<const NEUByteKey&>(source)).getValue();
			break;
		case NEType::NEWCHAR_KEY:
			{
				NEWString converter((static_cast<const NEWCharKey&>(source)).getValue());
				_value = converter.toDouble();
			}
			break;
		case NEType::NESHORT_KEY:
			_value = (static_cast<const NEShortKey&>(source)).getValue();
			break;
		case NEType::NEUSHORT_KEY:
			_value = (static_cast<const NEUShortKey&>(source)).getValue();
			break;
		case NEType::NEINT_KEY:
			_value = (static_cast<const NEIntKey&>(source)).getValue();
			break;
		case NEType::NEUINT_KEY:
			_value = (static_cast<const NEUIntKey&>(source)).getValue();
			break;
		case NEType::NEFLOAT_KEY:
			_value = (static_cast<const NEFloatKey&>(source)).getValue();
			break;
		case NEType::NEDOUBLE_KEY:
			_value = (static_cast<const NEDoubleKey&>(source)).getValue();
			break;
		case NEType::NEINT64_KEY:
			_value = static_cast<type_double>((static_cast<const NEInt64Key&>(source)).getValue());
			break;
		case NEType::NESTRING_KEY:
			_value = (static_cast<const NEStringKey&>(source)).getValue().toDouble();
			break;
		case NEType::NEWSTRING_KEY:
			_value = (static_cast<const NEWStringKey&>(source)).getValue().toDouble();
			break;
		}

		return RESULT_SUCCESS;
	}
	template <>
	type_result NE_DLL NETArithmeticKey<type_int64, NEType::NEINT64_KEY>::assign(const NEKey& source)
	{
		//	pre:
		if (!&source) return RESULT_TYPE_ERROR;
		if (this == &source) return RESULT_TYPE_ERROR;

		SuperClass::assign(source);


		//	main:
		switch (source.getType())
		{
		case NEType::NEBOOLEAN_KEY:
			_value = (static_cast<const NEBooleanKey&>(source)).getValue();
			break;
		case NEType::NECHAR_KEY:
			{
				NEString converter((static_cast<const NECharKey&>(source)).getValue());
				_value = converter.toInt();
			}
			break;
		case NEType::NEBYTE_KEY:
			_value = (static_cast<const NEByteKey&>(source)).getValue();
			break;
		case NEType::NEUBYTE_KEY:
			_value = (static_cast<const NEUByteKey&>(source)).getValue();
			break;
		case NEType::NEWCHAR_KEY:
			{
				NEWString converter((static_cast<const NEWCharKey&>(source)).getValue());
				_value = converter.toInt();
			}
			break;
		case NEType::NESHORT_KEY:
			_value = (static_cast<const NEShortKey&>(source)).getValue();
			break;
		case NEType::NEUSHORT_KEY:
			_value = (static_cast<const NEUShortKey&>(source)).getValue();
			break;
		case NEType::NEINT_KEY:
			_value = (static_cast<const NEIntKey&>(source)).getValue();
			break;
		case NEType::NEUINT_KEY:
			_value = (static_cast<const NEUIntKey&>(source)).getValue();
			break;
		case NEType::NEFLOAT_KEY:
			_value = static_cast<type_int64>((static_cast<const NEFloatKey&>(source)).getValue());
			break;
		case NEType::NEDOUBLE_KEY:
			_value = static_cast<type_int64>((static_cast<const NEDoubleKey&>(source)).getValue());
			break;
		case NEType::NEINT64_KEY:
			_value = (static_cast<const NEInt64Key&>(source)).getValue();
			break;
		case NEType::NESTRING_KEY:
			_value = (static_cast<const NEStringKey&>(source)).getValue().toInt();
			break;
		case NEType::NEWSTRING_KEY:
			_value = (static_cast<const NEWStringKey&>(source)).getValue().toInt();
			break;
		}

		return RESULT_SUCCESS;
	}


	template <>
	type_result NE_DLL NETArithmeticKey<type_bool, NEType::NEBOOLEAN_KEY>::increase()
	{
		_value = !_value;

		return RESULT_SUCCESS;
	}

	template <>
	type_result NE_DLL NETArithmeticKey<type_bool, NEType::NEBOOLEAN_KEY>::decrease()
	{
		_value = !_value;

		return RESULT_SUCCESS;
	}
}
#pragma warning(pop)