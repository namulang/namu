#pragma once

#include "../../Commons/Templates/NEListTemplate/NEListTemplate.hpp"
#include "../../Commons/Units/NEArgumentInterfaceBase/NEArgumentInterfaceBase.hpp"

namespace NE
{
	template
	class NE_DLL NEListTemplate<NEArgumentInterfaceBase*, false>;
	typedef NEListTemplate<NEArgumentInterfaceBase*, false> NEArgumentInterfaceList;
}