#pragma once

#include "../Camera/Camera.hpp"

namespace DX9Graphics
{
	class NE_DLL PerspectiveCamera : public Camera
	{
	public:
		typedef Camera SuperClass;
		typedef PerspectiveCamera ThisClass;

	public:
		type_bool& isProjectionMatrixCreatedAutomatically()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_bool&>(consted_this->isProjectionMatrixCreatedAutomatically());
		}
		const type_bool& isProjectionMatrixCreatedAutomatically() const
		{
			const NEKey& somekey = getKeySet()[28];
			if( ! somekey.isSubClassOf(NEType::NEBOOLEAN_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 28번키는 NEFLOAT_KEY여야 합니다.");
				type_bool* nullpoint = 0;
				return *nullpoint;
			}

			const NEBooleanKey& target = static_cast<const NEBooleanKey&>(somekey);
			return target.getValue();
		}
		type_float& getFOVY()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_float&>(consted_this->getFOVY());
		}
		const type_float& getFOVY() const
		{
			const NEKey& somekey = getKeySet()[29];
			if( ! somekey.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 29번키는 NEFLOAT_KEY여야 합니다.");
				type_float* nullpoint = 0;
				return *nullpoint;
			}

			const NEFloatKey& target = static_cast<const NEFloatKey&>(somekey);
			return target.getValue();
		}
		type_float& getAspect()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_float&>(consted_this->getAspect());
		}
		const type_float& getAspect() const
		{
			const NEKey& somekey = getKeySet()[30];
			if( ! somekey.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 30번키는 NEFLOAT_KEY여야 합니다.");
				type_float* nullpoint = 0;
				return *nullpoint;
			}

			const NEFloatKey& target = static_cast<const NEFloatKey&>(somekey);
			return target.getValue();
		}
		type_float& getPerpectiveMinimumZ()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_float&>(consted_this->getPerpectiveMinimumZ());
		}
		const type_float& getPerpectiveMinimumZ() const
		{
			const NEKey& somekey = getKeySet()[31];
			if( ! somekey.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 31번키는 NEFLOAT_KEY여야 합니다.");
				type_float* nullpoint = 0;
				return *nullpoint;
			}

			const NEFloatKey& target = static_cast<const NEFloatKey&>(somekey);
			return target.getValue();
		}
		type_float& getPerspectiveMaximumZ()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_float&>(consted_this->getPerspectiveMaximumZ());
		}
		const type_float& getPerspectiveMaximumZ() const
		{
			const NEKey& somekey = getKeySet()[32];
			if( ! somekey.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 32번키는 NEFLOAT_KEY여야 합니다.");
				type_float* nullpoint = 0;
				return *nullpoint;
			}

			const NEFloatKey& target = static_cast<const NEFloatKey&>(somekey);
			return target.getValue();
		}

	public:
		virtual type_result initialize()
		{
			SuperClass::initialize();

			NEKeyCodeSet& keyset = getKeySet();
			keyset.resize(keyset.getLength() + 5);
			keyset.push(NEBooleanKey(true));		//	28:	isProjectionMatrixCreatedAutomatically
			keyset.push(NEFloatKey(D3DX_PI / 4));	//	29:	FOVY; Field Of View Y
			keyset.push(NEFloatKey(1.0f));			//	30:	aspect; w / h
			keyset.push(NEFloatKey(1.0f));			//	31:	PerspectiveMinimumZ
			keyset.push(NEFloatKey(100.0f));		//	32:	PerspectiveMaximumZ

			return RESULT_SUCCESS;
		}

	public:
		virtual NEExportable::ModuleHeader& getHeader() const;

	public:
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}

	private:
		virtual type_result _updateProjectionMatrix()
		{
			type_float& fovy = getFOVY(),
						aspect = getAspect(),
						min_z = getPerpectiveMinimumZ(),
						max_z = getPerspectiveMaximumZ();

			if(isProjectionMatrixCreatedAutomatically())
				_updateProjectionVariablesAutomatically(fovy, aspect, min_z, max_z);

			D3DXMATRIX projection_matrix;
			D3DXMatrixPerspectiveFovLH(&getProjectionMatrix(), 
				fovy, aspect,
				min_z, max_z);

			return RESULT_SUCCESS;
		}
		type_result _updateProjectionVariablesAutomatically(type_float& fovy, type_float& aspect, 
			type_float& perspective_minimum_z, type_float& perspective_maximum_z)
		{
			D3DVIEWPORT9 maximized = createMaximizedViewPort();
			if(maximized.Height == 0)
				maximized.Height = 1;


			//	main:			
			if(isViewportMaximized())
			{
				aspect = (float) maximized.Width / maximized.Height;
				fovy = 90;
			}
			else
			{
				type_uint vp_h = getViewportHeight();

				aspect = (float) getViewportWidth() / vp_h;
				fovy = 90;
			}


			//	post:
			perspective_minimum_z = 0.1f;
			perspective_maximum_z = 1000.0f;
			return RESULT_SUCCESS;
		}
	};
}