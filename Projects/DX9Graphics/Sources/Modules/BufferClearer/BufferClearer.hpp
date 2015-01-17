#pragma once

#include "../../Includes/Includes.hpp"

namespace DX9Graphics
{
	class NE_DLL BufferClearer : public NEModule
	{
		typedef BufferClearer ThisClass;
		typedef NEModule SuperClass;

	public:
		virtual NEExportable::ModuleHeader& getHeader() const;

	public:
		virtual type_result initialize();

	public:
		virtual type_result execute();

	public:
		virtual NEObject& clone() const;
	};
}