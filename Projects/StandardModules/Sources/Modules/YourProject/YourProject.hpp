#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL YourProject : public NEModule
	{
	public:
		YourProject();
		YourProject(const YourProject& source);

	public:
		virtual ~YourProject();

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
