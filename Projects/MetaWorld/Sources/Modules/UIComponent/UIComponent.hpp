#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	class UIComponent : public DX9Graphics::AnimatedModel
	{
	public:
		typedef UIComponent ThisClass;
		typedef DX9Graphics::AnimatedModel SuperClass;

	public:
		virtual type_result initialize()
		{
			SuperClass::initialize();
			NEKeyCodeSet& kset = getKeySet();
			kset.resize(kset.getSize() + );

			return RESULT_SUCCESS;
		}
	};
}