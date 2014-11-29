#pragma once

#include "../../Functions/NEResult/NEResult.hpp"
#include "../../Templates/NEListTemplate/NEListTemplate.hpp"

namespace NE
{
	class NEArgumentSet;
	class NEArgumentBase;
	class NEKey;

	class NE_DLL NEArgumentInterfaceBase : public NEObject
	{
	public:
		friend class NEArgumentSet;
		typedef NEObject SuperClass;

	public:
		virtual NEType::Type getKeyType() const = 0;
		virtual bool isValidToBind(const NEArgumentBase& arg) const;
		virtual NEKey& getDefaultKey() = 0;
		virtual const NEKey& getDefaultKey() const = 0;

	public:
		bool operator==(const NEArgumentInterfaceBase& rhs) const;

	public:
		virtual type_result isValid() const;

	private:
		virtual type_result _onInsertedInArguments(type_index index, NEArgumentSet& rhs) = 0;
		virtual type_result _onBindInstance(NEArgumentBase& concreted) = 0;
	};
}