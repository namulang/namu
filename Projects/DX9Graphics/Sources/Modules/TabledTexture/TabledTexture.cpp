#include "TabledTexture.hpp"
#include "../AnimatedModel/AnimatedModel.hpp"

namespace DX9Graphics
{	
	type_result TabledTexture::dock(Model& model)
	{
		static type_code animated_model_code = Kernal::getInstance().getModuleManager()
			.getModule(AnimatedModel().getHeader()).getScriptCode();

		SuperClass::dock(model);

		if (model.getScriptCode() != animated_model_code) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		const AnimatedModel& animated = static_cast<const AnimatedModel&>(model);

		_row_extracted_from_model = animated.arg_animation_index.getValue();
		_column_extracted_from_model = animated.arg_key_frame.getValue();
		return RESULT_SUCCESS;
	}
}