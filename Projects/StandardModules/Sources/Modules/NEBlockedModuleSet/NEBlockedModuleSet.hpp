#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL NEBlockedModuleSet : public NEModule
	{
	public:
		virtual type_result initialize();

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;

	public:
		virtual type_result execute();	

	public:
		virtual NEObject& clone() const;
	};
}
