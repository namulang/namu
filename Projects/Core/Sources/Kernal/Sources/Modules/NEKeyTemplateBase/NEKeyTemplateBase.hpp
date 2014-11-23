#pragma once

#include "../NEKey/NEKey.hpp"

namespace NE
{
	class NE_DLL NEKeyTemplateBase : public NEKey
	{
	public:
		typedef NEKeyTemplateBase ThisClass;
		typedef NEKey SuperClass;
	public:
		NEKeyTemplateBase(const NETString& new_keyname);
		NEKeyTemplateBase(const ThisClass& source);

	public:
		virtual ~NEKeyTemplateBase();

	public:
		virtual type_result assign(const NEKey& source);
	};
}