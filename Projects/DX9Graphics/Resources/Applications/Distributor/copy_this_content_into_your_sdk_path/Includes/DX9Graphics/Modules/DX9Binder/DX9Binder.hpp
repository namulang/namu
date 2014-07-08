#pragma once

#include "../../Commons/Templates/BinderTemplate/BinderTemplate.hpp"
#include "../DX9/DX9.hpp"

namespace DX9Graphics
{
	template
	class NE_DLL BinderTemplate<DX9>;
	typedef BinderTemplate<DX9> DX9Binder;
}