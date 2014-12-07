#include "NEStringKeyTemplate.hpp"

namespace NE
{
	template <typename T, NEType::Type type>
	type_result NEStringKeyTemplate<T, type>::add(NEKey& result, const NEKey& operand2) const
	{
		ThisClass converted;
		converted.assign(operand2);		

		return result.assign(ThisClass(getValue() + converted.getValue()));
	}

	template <typename T, NEType::Type type>
	bool NEStringKeyTemplate<T, type>::isEqualTo(const NEKey& source) const
	{
		if(source.isSubClassOf(*this))
		{
			const ThisClass& casted = static_cast<const ThisClass&>(source);

			return getValue() == casted.getValue();
		}

		return getValue() == ThisClass(source).getValue();
	}

	template <typename T, NEType::Type type>
	bool NEStringKeyTemplate<T, type>::isLower(const NEKey& source) const
	{
		return false;
	}

	template <>
	bool NEStringKeyTemplate<NEString, NEType::NESTRING_KEY>::isLower(const NEKey& source) const;
	template <>
	bool NEStringKeyTemplate<NEWString, NEType::NEWSTRING_KEY>::isLower(const NEKey& source) const;

	template <typename T, NEType::Type type>
	type_result NEStringKeyTemplate<T, type>::assign(const NEKey& source)
	{
		if ( ! &source) return RESULT_TYPE_ERROR | RESULT_WRONG_PARAMETER | RESULT_WRONG_POINTER_ADDRESSING | RESULT_ABORT_ACTION;
		if (this == &source) return RESULT_SUCCESS | RESULT_ABORT_ACTION | RESULT_ABORT_ACTION;
		if (isSubClassOf(NEType::NENODE_SELECTOR_BASE)) return RESULT_TYPE_ERROR | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION;
		if (!isEqualTypeWith(source)) return RESULT_TYPE_ERROR | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION;

		SuperClass::assign(source);
		_value = static_cast<const NETArithmeticKey<T, type>&>(source).getValue();

		return RESULT_SUCCESS;
	}
	template <>
	type_result NEStringKeyTemplate<NEString, NEType::NESTRING_KEY>::assign(const NEKey& source);
	template <>
	type_result NEStringKeyTemplate<NEWString, NEType::NEWSTRING_KEY>::assign(const NEKey& source);

	template <typename T, NEType::Type type>
	NEStringKeyTemplate<T, type>::NEStringKeyTemplate(const NEKey& source)
		: SuperClass(source)
	{
		assign(source);
	}

	template <typename T, NEType::Type type>
	NEStringKeyTemplate<T, type>::NEStringKeyTemplate(const ThisClass& source)
		: SuperClass(source)
	{

	}

	template <typename T, NEType::Type type>
	NEStringKeyTemplate<T, type>::NEStringKeyTemplate(const T& source /*= T()*/, const NETString& keyname /*= ""*/)
		: SuperClass(source, keyname)
	{

	}

	template <typename T, NEType::Type type>
	NEObject& NE::NEStringKeyTemplate<T, type>::clone() const
	{
		return *(new ThisClass(*this));
	}
}