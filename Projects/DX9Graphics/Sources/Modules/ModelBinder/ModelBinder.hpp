#pragma once

#include "../../Commons/Templates/BinderTemplate/BinderTemplate.hpp"
#include "../Model/Model.hpp"

namespace DX9Graphics
{
	template
	class NE_DLL BinderTemplate<Model>;
	typedef BinderTemplate<Model> ModelBinder;
}