#include "ModelMediator.hpp"
#include "../Sprite/Sprite.hpp"

namespace DX9Graphics
{
	type_result ModelMediator::_onExecute()
	{
		//	pre:			
		arg_target.getValue().initializeReferingPoint();
		arg_validator.getValue().initializeReferingPoint();
		Model	*	he = &cast(arg_target),
				*	me = &cast(arg_validator);
		if (!he || !me) return RESULT_TYPE_WARNING;
		Sprite	&	his_spr = he->getModeling(),
			&	my_spr = me->getModeling();
		if (!&his_spr || !&my_spr) return RESULT_TYPE_WARNING;


		//	main:
		D3DXVECTOR3 his_point = he->createTranslationVector(),
			my_point = me->createTranslationVector();
		type_float	my_avg_scale = (me->arg_scale_x.getValue() + me->arg_scale_y.getValue()) / 2.0f,
			his_avg_scale = (he->arg_scale_x.getValue() + he->arg_scale_y.getValue()) / 2.0f,
			length = _createDistance(his_point, my_point),
			his_radius = his_spr.arg_bounding_sphere_radius.getValue() * his_avg_scale,
			my_radius = my_spr.arg_bounding_sphere_radius.getValue() * my_avg_scale,
			threshold = length - (his_radius + my_radius);
		type_result result = threshold <= 0 ? RESULT_TRUE | RESULT_SUCCESS : RESULT_FALSE | RESULT_SUCCESS;


		//	post:
		arg_distance.setValue(length);
		arg_threshold.setValue(threshold);
		return result;
	}
}
