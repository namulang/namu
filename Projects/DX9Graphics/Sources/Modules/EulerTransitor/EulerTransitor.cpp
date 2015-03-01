#include "EulerTransitor.hpp"
#include "../DX9/DX9.hpp"

namespace DX9Graphics
{
	D3DXVECTOR3 EulerTransitor::createTransformedVectorByYawPitchRoll(const D3DXVECTOR3& origin) const
	{
		D3DXVECTOR3 angles = createYawPitchRoll();
		return DX9::createDirectionVectorFrom(angles.y, angles.x, angles.z, origin);
	}

	D3DXVECTOR3 EulerTransitor::createYawPitchRoll() const
	{
		return D3DXVECTOR3(arg_rotate_x.getValue(), arg_rotate_y.getValue(), arg_rotate_z.getValue());
	}

	D3DXMATRIX EulerTransitor::createRotationMatrix() const
	{
		D3DXMATRIX to_return;
		D3DXMatrixRotationYawPitchRoll(&to_return, 
			DX9::toRadian(arg_rotate_y.getValue()), DX9::toRadian(arg_rotate_x.getValue()), DX9::toRadian(arg_rotate_z.getValue())
			);

		return to_return;
	}

	D3DXQUATERNION EulerTransitor::createQuaternionFrom(type_float yaw_degree, type_float pitch_degree, type_float roll_degree)
	{
		D3DXQUATERNION to_return;
		D3DXQuaternionRotationYawPitchRoll(&to_return, 
			DX9::toRadian(yaw_degree), DX9::toRadian(pitch_degree), DX9::toRadian(roll_degree)
			);

		return to_return;
	}
}