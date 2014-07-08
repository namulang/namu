#pragma once

#include "../RayGenerator/RayGenerator.hpp"

namespace DX9Graphics
{
	class Camera;

	class NE_DLL RefererRotatorAlongCamera : public RayGenerator
	{
		typedef RefererRotatorAlongCamera ThisClass;
		typedef RayGenerator SuperClass;

	public:
		ThisClass()
			: SuperClass()
		{
			_release();
		}
		ThisClass(const ThisClass& source)
			: SuperClass(source)
		{
			_assign(source);
		}

	public:
		const ThisClass& operator=(const ThisClass& source)
		{
			SuperClass::operator=(source);

			return _assign(source);
		}
		bool operator==(const ThisClass& source) const
		{
			if(SuperClass::operator!=(source)) return false;
			if(_z_radian != source._z_radian) return false;

			return true;
		}
		bool operator!=(const ThisClass& source) const
		{
			return ! operator==(source);
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;

	public:
		virtual type_result execute();

	public:
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
		virtual void release()
		{
			SuperClass::release();

			_release();
		}
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
		{
			SuperClass::serialize(loader);

			return loader >> _z_radian;
		}
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
		{
			SuperClass::serialize(saver);

			return saver << _z_radian;
		}

	protected:
		void _computeCombinedMatrix(Referer& referer, Camera& camera);
		void _release()
		{
			_z_radian = 0.0f;
		}
		const ThisClass& _assign(const ThisClass& source)
		{
			if(this == &source) return *this;

			_z_radian = source._z_radian;

			return *this;
		}

	protected:
		float _z_radian;
	};
}