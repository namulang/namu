#pragma once

#include "../Resource/Resource.hpp"

namespace DX9Graphics
{
	class Model;

	class NE_DLL DockableResource : public Resource
	{
	public:
		typedef Resource SuperClass;
		typedef DockableResource ThisClass;

	public:
		virtual type_result dock(Model& model)
		{
			return RESULT_SUCCESS;
		}

	public:
		static const NECodeSet& getModuleScriptCodes()
		{
			NECodeType type(NECodeType::MODULE_SCRIPT);
			static NECodeSet _instance(type);

			if(_instance.getLength() <= 0)
			{
				_instance.create(2);
				_instance.push(NEExportable::Identifier("Sprite.kniz"));
				_instance.push(NEExportable::Identifier("TabledTexture.kniz"));
			}

			return _instance;
		}
	};
}