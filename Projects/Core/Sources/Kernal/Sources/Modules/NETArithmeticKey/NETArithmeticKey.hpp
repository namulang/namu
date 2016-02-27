#pragma once

#include "../NEKeyTemplate/NEKeyTemplate.hpp"
#define NOMINMAX	//	max 매크로 define 금지
#ifdef max
#	undef max
#endif
#include <limits>

namespace NE
{
	template <typename T, NEType::Type type>
	class NETArithmeticKey : public NEKeyTemplate<T, type>
	{
	public:
		typedef NETArithmeticKey ThisClass;
		typedef NEKeyTemplate<T, type> SuperClass;

	public:
		NETArithmeticKey(const T& source = T(), const NETString& keyname = "");
		NETArithmeticKey(const ThisClass& source);
		NETArithmeticKey(const NEKey& source);

	public:
		virtual type_result assign(const NEKey& source);
		virtual bool isEqualTo(const NEKey& source) const;
		virtual bool isLower(const NEKey& source) const;
		virtual type_result increase();
		virtual type_result decrease();
		virtual type_result add(NEKey& result, const NEKey& operand2) const;
		virtual type_result multiply(NEKey& result, const NEKey& operand2) const;
		virtual type_result makeReciprocal();
		virtual type_result negate();

	public:
		virtual NEObject& clone() const;
	};
}

#include "NETArithmeticKey.inl"