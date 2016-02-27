#pragma once

#include "../NETKey/NETKey.hpp"
#include "../NEString/NEString.hpp"
#include "../NEWString/NEWString.hpp"

namespace NE
{
	template <typename T, NEType::Type type>
	class NETStringKeyize : public NETKey<T, type>
	{
	public:
		typedef NETStringKeyize ThisClass;
		typedef NETKey<T, type> SuperClass;

	public:
		NETStringKeyize(const T& source = T(), const NETString& keyname = "");
		NETStringKeyize(const ThisClass& source);
		NETStringKeyize(const NEKey& source);

	public:
		virtual type_result assign(const NEKey& source);
		virtual bool isEqualTo(const NEKey& source) const;
		virtual type_result add(NEKey& result, const NEKey& operand2) const;
		virtual bool isLower(const NEKey& source) const;

	public:
		virtual NEObject& clone() const;
	};
}

#include "NETStringKeyize.inl"