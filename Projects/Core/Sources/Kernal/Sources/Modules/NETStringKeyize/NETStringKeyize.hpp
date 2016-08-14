#pragma once

#include "../NETKey/NETKey.hpp"
#include "../NEString/NEString.hpp"
#include "../NEWString/NEWString.hpp"

namespace NE
{
	template <typename T>
	class NETStringKeyize : public NETKey<T>
	{
		NE_DECLARE_CLASS(NETStringKeyize<T>, NETKey<T>)

	public:
		NETStringKeyize(const T& source = T(), const NETString& keyname = "");
		NETStringKeyize(const This& source);
		NETStringKeyize(const NEKey& source);

	public:
		virtual type_result assign(const NEKey& source);
		virtual type_bool isEqualTo(const NEKey& source) const;
		virtual type_result add(NEKey& result, const NEKey& operand2) const;
		virtual type_bool isLower(const NEKey& source) const;
	};
}

#include "NETStringKeyize.inl"