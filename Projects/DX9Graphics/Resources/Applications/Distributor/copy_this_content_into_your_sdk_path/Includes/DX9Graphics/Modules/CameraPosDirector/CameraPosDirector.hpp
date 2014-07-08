#pragma once

#include "../CameraSelector/CameraSelector.hpp"

namespace DX9Graphics
{
	class NE_DLL CameraPosDirector : public CameraSelector
	{
	public:
		typedef CameraPosDirector ThisClass;
		typedef CameraSelector SuperClass;

	public:
		const type_float& getFocusX() const
		{
			const NEKey& key = getKeySet()[1];
			if( ! &key || key.getType() != NEType::NEFLOAT_KEY)
			{
				ALERT_ERROR(" : 1번키는 NEFLOATKEY여야 합니다.");
				type_float* nullpoint = 0;
				return *nullpoint;
			}

			return static_cast<const NEFloatKey&>(key).getValue();
		}
		type_float& getFocusX() 
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_float&>(casted->getFocusX());
		}
		const type_float& getFocusY() const
		{
			const NEKey& key = getKeySet()[2];
			if( ! &key || key.getType() != NEType::NEFLOAT_KEY)
			{
				ALERT_ERROR(" : 1번키는 NEFLOATKEY여야 합니다.");
				type_float* nullpoint = 0;
				return *nullpoint;
			}

			return static_cast<const NEFloatKey&>(key).getValue();
		}
		type_float& getFocusY() 
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_float&>(casted->getFocusY());
		}
		const type_float& getFocusZ() const
		{
			const NEKey& key = getKeySet()[3];
			if( ! &key || key.getType() != NEType::NEFLOAT_KEY)
			{
				ALERT_ERROR(" : 1번키는 NEFLOATKEY여야 합니다.");
				type_float* nullpoint = 0;
				return *nullpoint;
			}

			return static_cast<const NEFloatKey&>(key).getValue();
		}
		type_float& getFocusZ() 
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_float&>(casted->getFocusZ());
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;

	public:
		virtual type_result initialize()
		{
			SuperClass::initialize();

			NEKeyCodeSet& keyset = getKeySet();
			keyset.resize(keyset.getLength() + 3);	
			keyset.push(NEFloatKey(0.0f));	//	LOOKAT_X
			keyset.push(NEFloatKey(0.0f));	//	LOOKAT_Y
			keyset.push(NEFloatKey(0.0f));	//	LOOKAT_Z

			return RESULT_SUCCESS;
		}	

	public:
		virtual type_result execute();

	public:
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}

	public:
		D3DXVECTOR3 createFocusVector() const
		{
			return D3DXVECTOR3(getFocusX(), getFocusY(), getFocusZ());
		}
	};
}