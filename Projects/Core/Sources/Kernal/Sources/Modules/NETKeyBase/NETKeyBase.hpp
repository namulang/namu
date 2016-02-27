#pragma once

#include "../NEKey/NEKey.hpp"

namespace NE
{
	class NE_DLL NETKeyBase : public NEKey
	{
	public:
		typedef NETKeyBase ThisClass;
		typedef NEKey SuperClass;
	public:
		NETKeyBase(const NETString& new_keyname);
		NETKeyBase(const ThisClass& source);

	public:
		virtual ~NETKeyBase();

	public:
		virtual type_result assign(const NEKey& source);
	};
}