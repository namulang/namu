#include "Camera.hpp"
#include "../DX9/DX9.hpp"
#include "../PerspectiveCamera/PerspectiveCamera.hpp"

namespace DX9Graphics
{
	const NECodeSet& Camera::getModuleScriptCodes()
	{
		NECodeType type(NECodeType::MODULE_SCRIPT);
		static NECodeSet codes(type);

		if(codes.getLength() <= 1)
		{
			codes.create(1);
			codes.push(NEExportable::Identifier("PerspectiveCamera.kniz"));
		}

		return codes;
	}
}