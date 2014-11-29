#pragma once

#include "../../Commons/Templates/NEListTemplate/NEListTemplate.hpp"
#include "../../Commons/Units/NEArgumentBase/NEArgumentBase.hpp"

namespace NE
{
	template
	class NE_DLL NEListTemplate<NEArgumentBase*, false>;
	typedef NEListTemplate<NEArgumentBase*> NEArgumentList;
}