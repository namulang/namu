#include "NETStringKeyize.hpp"

namespace NE
{
	template <typename T>
	type_result NETStringKeyize<T>::add(NEKey& result, const NEKey& operand2) const
	{
		This converted;
		converted.assign(operand2);		

		return result.assign(This(getValue() + converted.getValue()));
	}

	template <typename T>
	type_bool NETStringKeyize<T>::isEqualTo(const NEKey& source) const
	{
		if(source.isSubClassOf(*this))
		{
			const This& casted = static_cast<const This&>(source);

			return getValue() == casted.getValue();
		}

		return getValue() == This(source).getValue();
	}

	template <typename T>
	type_bool NETStringKeyize<T>::isLower(const NEKey& source) const
	{
		return false;
	}

	template <>
	type_bool NETStringKeyize<NEString>::isLower(const NEKey& source) const;
	template <>
	type_bool NETStringKeyize<NEWString>::isLower(const NEKey& source) const;

	template <typename T>
	type_result NETStringKeyize<T>::assign(const NEKey& source)
	{
		if ( ! &source) return RESULT_TYPE_ERROR | RESULT_WRONG_PARAMETER | RESULT_WRONG_POINTER_ADDRESSING | RESULT_ABORT_ACTION;
		if (this == &source) return RESULT_SUCCESS | RESULT_ABORT_ACTION | RESULT_ABORT_ACTION;
		if (isSubClassOf(NEType::NENODE_SELECTOR_BASE)) return RESULT_TYPE_ERROR | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION;
		if (!isEqualTypeWith(source)) return RESULT_TYPE_ERROR | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION;

		Super::assign(source);
		_value = static_cast<const NETArithmeticKey<T>&>(source).getValue();

		return RESULT_SUCCESS;
	}
	template <>
	type_result NETStringKeyize<NEString>::assign(const NEKey& source);
	template <>
	type_result NETStringKeyize<NEWString>::assign(const NEKey& source);

	template <typename T>
	NETStringKeyize<T>::NETStringKeyize(const NEKey& source)
		: Super(source)
	{
		assign(source);
	}

	template <typename T>
	NETStringKeyize<T>::NETStringKeyize(const This& source)
		: Super(source)
	{

	}

	template <typename T>
	NETStringKeyize<T>::NETStringKeyize(const T& source /*= T()*/, const NETString& keyname /*= ""*/)
		: Super(source, keyname)
	{

	}
}