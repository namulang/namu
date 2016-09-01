#pragma once

#include "../NEKey/NEKey.hpp"

namespace NE
{
	class NE_DLL NETKeyBase : public NEKey
	{
		NE_DECLARE_INTERFACE(NETKeyBase, NEKey)

	public:
		NETKeyBase(const NETString& new_keyname);
		NETKeyBase(const This& source);

	public:
		virtual ~NETKeyBase();

	public:
		virtual type_result assign(const NEKey& source);
	};
}