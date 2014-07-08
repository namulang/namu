#pragma once

#include "../RayGenerator/RayGenerator.hpp"

namespace DX9Graphics
{
	class NE_DLL RefererTransitorAlongCamera : public RayGenerator
	{
		typedef RefererTransitorAlongCamera ThisClass;
		typedef RayGenerator SuperClass;

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;

	public:
		virtual type_result execute();

	public:
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}		

	private:
		D3DXVECTOR3 _computeIntersectedPoint(D3DXPLANE& plane, RayGenerator::Ray& ray);
		void _computeCombinedMatrix(Referer& referer, Camera& camera, RayGenerator::Ray& ray, DWORD message);
		type_result _transitCamera(RayGenerator::Ray& ray, DWORD message);
	};
}