#include "Particle.hpp"

namespace 
{
	const float RADIAN_TO_DEGREE_ADJ = 180.0f / D3DX_PI;
	const float DEGREE_TO_RADIAN_ADJ = D3DX_PI / 180.0f;
}
namespace DX9Graphics
{
	D3DXMATRIX Particle::createTranslationMatrix() const
	{
		D3DXMATRIX to_return;
		D3DXMatrixTranslation(&to_return, getTranslationX(), getTranslationY(), getTranslationZ());

		return to_return;
	}
	D3DXMATRIX Particle::createRotationMatrix() const
	{
		D3DXMATRIX to_return_x, to_return_y, to_return_z, to_return;
		D3DXMatrixRotationX(&to_return_x, getRotationX() * DEGREE_TO_RADIAN_ADJ);
		D3DXMatrixRotationY(&to_return_y, getRotationY() * DEGREE_TO_RADIAN_ADJ);
		D3DXMatrixRotationZ(&to_return_z, getRotationZ() * DEGREE_TO_RADIAN_ADJ);

		return to_return = to_return_x * to_return_y * to_return_z;
	}
}