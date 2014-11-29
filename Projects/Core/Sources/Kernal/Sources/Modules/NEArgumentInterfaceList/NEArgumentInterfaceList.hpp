#pragma once

#include "../../Commons/Templates/NEListTemplate/NEListTemplate.hpp"
#include "../../Commons/Units/NEArgumentInterfaceBase/NEArgumentInterfaceBase.hpp"

namespace NE
{
	template
	class NE_DLL NEListTemplate<NEArgumentInterfaceBase*, false>;

	class NE_DLL NEArgumentInterfaceList : public NEListTemplate<NEArgumentInterfaceBase*, false>
	{
	public:
		typedef NEArgumentInterfaceList ThisClass;
		typedef NEListTemplate<NEArgumentInterfaceBase*, false> SuperClass;

	public:
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual NEObject& clone() const;
	};
}