#pragma once

#include "../CameraSelector/CameraSelector.hpp"

namespace DX9Graphics
{
	class Camera;
	class Model;

	class NE_DLL Picker : public CameraSelector
	{
	public:
		typedef CameraSelector SuperClass;
		typedef Picker ThisClass;

	public:
		class Vector : public D3DXVECTOR3
		{
		public:
			Vector() : D3DXVECTOR3() {}
			Vector(type_float x, type_float y, type_float z)
				: D3DXVECTOR3(x, y, z) {}
			NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
			{
				return saver << x << y << z;
			}
			NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
			{
				return loader >> x >> y >> z;
			}
		};
		typedef NEArrayTemplate<Vector> Vectors;

	public:
		const NEModuleSelector& getModelSelector() const
		{
			const NEKey& key = getKeySet()[1];
			if( ! &key	||	! key.isSubClassOf(NEType::NEMODULE_SELECTOR))
			{
				ALERT_ERROR("1번째키가 잘못되었습니다. 1번째 키는 NEMODULE_SELECTOR 여야 합니다.");
				NEModuleSelector* nullpoint=0;
				return *nullpoint;
			}

			return static_cast<const NEModuleSelector&>(key);			
		}
		NEModuleSelector& getModelSelector()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<NEModuleSelector&>(casted->getModelSelector());
		}
		const NEBooleanKey& isSomethingPicked() const
		{
			const NEKey& key = getKeySet()[2];
			if( ! &key	||	! key.isSubClassOf(NEType::NEBOOLEAN_KEY))
			{
				ALERT_ERROR("2번째키가 잘못되었습니다. 2번째 키는 NEBOOLEAN_KEY 여야 합니다.");
				NEBooleanKey* nullpoint=0;
				return *nullpoint;
			}

			return static_cast<const NEBooleanKey&>(key);			
		}
		NEBooleanKey& isSomethingPicked()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<NEBooleanKey&>(casted->isSomethingPicked());
		}

	public:
		virtual type_result initialize()
		{
			SuperClass::initialize();

			NEKeyCodeSet& keyset = getKeySet();
			keyset.resize(keyset.getSize() + 2);			
			keyset.push(NEModuleSelector());	//	Model
			return keyset.push(NEBooleanKey());
		}
		virtual type_result execute();
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}

	private:
		Vectors _createRayInWorldCoords(const Camera& camera) const;
		Vectors _createQuadOfSprite(type_uint width, type_uint height) const;		
		bool _isRayIntersectedToQuad(const Vectors& quad, const Vectors& ray, const D3DXMATRIX& world) const;
	};
}