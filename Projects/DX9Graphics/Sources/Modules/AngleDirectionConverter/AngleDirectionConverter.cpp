#include "AngleDirectionConverter.hpp"
#include "../DX9/DX9.hpp"

namespace DX9Graphics
{
	type_result AngleDirectionConverter::_onExecute()
	{
		if (arg_x_angle.getPurpose() == NEArgumentBase::READ_BY)
		{	//	Angle -> Vector
			D3DXVECTOR3 vector = DX9::createDirectionVectorFrom(arg_y_angle.getValue(), arg_x_angle.getValue(), arg_z_angle.getValue(), D3DXVECTOR3(0, 0, 1));

			arg_xpos.setValue(vector.x);
			arg_ypos.setValue(vector.y);
			arg_zpos.setValue(vector.z);
		}
		else
		{	//	Angle <- Vector
			D3DXVECTOR3 angle = DX9::createYawPitchRollFrom(
				D3DXVECTOR3(arg_xpos.getValue(), arg_ypos.getValue(), arg_zpos.getValue())
				);

			arg_x_angle.setValue(angle.x);
			arg_y_angle.setValue(angle.y);
			arg_z_angle.setValue(angle.z);
		}

		return RESULT_SUCCESS;
	}
}