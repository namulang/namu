#include "TabledTexture.hpp"
#include "define.hpp"
#include "../AnimatedModel/AnimatedModel.hpp"

namespace DX9Graphics
{	
	const NEExportable::ModuleHeader& TabledTexture::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T(_NAME);
			_header.getDeveloper() = _T(_DEVELOPER);
			_header.setRevision(_REVISION);
			_header.getComment() = _T(_COMMENT);
			_header.getVersion()  = _T(_VERSION);
			_header.getReleaseDate() = _T(_DATE);
			_header.getModuleDependencies().create(_DEPENDENCIES_COUNT);
			_header.setMaxErrorCodeCount(1);
		}

		return _header;
	}

	type_result TabledTexture::dock(Model& model)
	{
		static type_code animated_model_code = Kernal::getInstance().getModuleManager()
			.getModule(AnimatedModel().getHeader()).getScriptCode();
		SuperClass::dock(model);
		if(model.getScriptCode() != animated_model_code) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		const AnimatedModel& animated = static_cast<const AnimatedModel&>(model);

		_row_extracted_from_model = animated.getAnimationIndex();
		_column_extracted_from_model = animated.getKeyFrame();
		return RESULT_SUCCESS;
	}
}