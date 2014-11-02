#pragma once

#include "../../Functions/NEResult/NEResult.hpp"
#include "../../Templates/NEListTemplate/NEListTemplate.hpp"

namespace NE
{
	class NEArgumentSet;
	class NEArgumentBase;

	class NEArgumentInterfaceBase
	{
	public:
		friend class NEArgumentSet;

	public:
		virtual NEType::Type getKeyType() const = 0;

	public:
		bool operator==(const NEArgumentInterfaceBase& rhs) const;

	private:
		virtual type_result _onInsertedInArguments(type_index index, NEArgumentSet& rhs) = 0;
		virtual type_result _onBindInstance(NEArgumentBase& concreted) = 0;
	};
}