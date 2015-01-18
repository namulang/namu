#include "Camera.hpp"
#include "../DX9/DX9.hpp"
#include "../PerspectiveCamera/PerspectiveCamera.hpp"

namespace DX9Graphics
{
	const NECodeSet& getModuleScriptCodes()
	{
		static NECodeSet codes(NECodeType::MODULE_SCRIPT);		

		if(codes.getLength() <= 1)
		{
			codes.create(1);
			codes.push(NECode("PerspectiveCamera.kniz"));
		}

		return codes;
	}
}