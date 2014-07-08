#pragma once

#include "../DX9Binder/DX9Binder.hpp"
#include "../Renderable/Renderable.hpp"

namespace DX9Graphics
{
	class NE_DLL RenderableModule : public NEModule, public Renderable {};
}