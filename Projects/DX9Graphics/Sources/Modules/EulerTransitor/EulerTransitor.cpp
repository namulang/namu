#include "EulerTransitor.hpp"
#include "../DX9/DX9.hpp"

namespace DX9Graphics
{
	const float EulerTransitor::RADIAN_TO_DEGREE_ADJ = 180.0f / D3DX_PI;
	const float EulerTransitor::DEGREE_TO_RADIAN_ADJ = D3DX_PI / 180.0f;

	D3DXVECTOR3 EulerTransitor::createTransformedVectorByYawPitchRoll(const D3DXVECTOR3& origin) const
	{
		D3DXVECTOR3 angles = createYawPitchRoll();
		return DX9::createDirectionVectorFrom(angles.y, angles.x, angles.z, origin);
	}
}