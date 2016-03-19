#pragma once

#include "../NETKey/NETKey.hpp"
#define NOMINMAX	//	max 매크로 define 금지
#ifdef max
#	undef max
#endif
#include <limits>

namespace NE
{
	template <typename T>
	class NETArithmeticKey : public NETKey<T>
	{
		NE_DECLARE_CLASS(NETArithmeticKey<T>, NETKey<T>)

	public:
		NETArithmeticKey(const T& source = T(), const NETString& keyname = "");
		NETArithmeticKey(const This& source);
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
	};
}

#include "NETArithmeticKey.inl"