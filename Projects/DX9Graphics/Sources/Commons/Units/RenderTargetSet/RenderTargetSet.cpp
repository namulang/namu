#include "RenderTargetSet.hpp"
#include "../../../Modules/DX9/DX9.hpp"

namespace DX9Graphics
{
	type_result RenderTargetSet::initialize(DX9& dx9)
	{
		for (int n = 0; n < getSize(); n++)
		{
			RenderTarget& target = getElement(n);
			if (!target.isInitialized())
				target.initialize(dx9);
		}

		return RESULT_SUCCESS;
	}
}