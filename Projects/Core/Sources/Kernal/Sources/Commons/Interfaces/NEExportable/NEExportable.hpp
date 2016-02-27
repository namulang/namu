#pragma once

#include "../NEInitializable/NEInitializable.hpp"
#include "../../../Includes/IncludeStringCollectors.hpp"
#include "../../../Modules/NEIntSet/NEIntSet.hpp"

namespace NE
{
	class NE_DLL NEExportable : public NEInitializable
	{
	public:
		#include "innerclass/Identifier/Identifier.hpp"
		#include "innerclass/Header/Header.hpp"
		#include "innerclass/ModuleHeader/ModuleHeader.hpp"

	public:
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;
		virtual const NEExportable::ModuleHeader& getHeader() const = 0;
	};
}
