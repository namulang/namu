#pragma once

#include "../CameraDirector/CameraDirector.hpp"

namespace DX9Graphics
{
	class NE_DLL CameraChaser : public CameraDirector
	{
	public:
		typedef CameraChaser ThisClass;
		typedef CameraDirector SuperClass;

	public:
		const type_float& getDistance() const
		{
			const NEKey& key = getKeySet()[2];
			if( ! &key || key.getType() != NEType::NEFLOAT_KEY)
			{
				ALERT_ERROR(" : 2번키는 NEFLOATKEY여야 합니다.");
				type_float* nullpoint = 0;
				return *nullpoint;
			}

			return static_cast<const NEFloatKey&>(key).getValue();
		}
		type_float& getDistance() 
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_float&>(casted->getDistance());
		}

		const type_float& getDestinationX() const
		{
			const NEKey& key = getKeySet()[3];
			if( ! &key || key.getType() != NEType::NEFLOAT_KEY)
			{
				ALERT_ERROR(" : 3번키는 NEFLOATKEY여야 합니다.");
				type_float* nullpoint = 0;
				return *nullpoint;
			}

			return static_cast<const NEFloatKey&>(key).getValue();
		}
		type_float& getDestinationX() 
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_float&>(casted->getDestinationX());
		}

		const type_float& getDestinationY() const
		{
			const NEKey& key = getKeySet()[4];
			if( ! &key || key.getType() != NEType::NEFLOAT_KEY)
			{
				ALERT_ERROR(" : 3번키는 NEFLOATKEY여야 합니다.");
				type_float* nullpoint = 0;
				return *nullpoint;
			}

			return static_cast<const NEFloatKey&>(key).getValue();
		}
		type_float& getDestinationY() 
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_float&>(casted->getDestinationY());
		}

		const type_float& getDestinationZ() const
		{
			const NEKey& key = getKeySet()[5];
			if( ! &key || key.getType() != NEType::NEFLOAT_KEY)
			{
				ALERT_ERROR(" : 3번키는 NEFLOATKEY여야 합니다.");
				type_float* nullpoint = 0;
				return *nullpoint;
			}

			return static_cast<const NEFloatKey&>(key).getValue();
		}
		type_float& getDestinationZ() 
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_float&>(casted->getDestinationZ());
		}
		
	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;

	public:
		virtual type_result initialize()
		{
			SuperClass::initialize();

			NEKeyCodeSet& keyset = getKeySet();
			keyset.resize(keyset.getLength() + 1);	
			keyset.push(NEFloatKey(5.0f));	//	Distance
			keyset.push(NEFloatKey(0.0f));	//	OUT 목적지X
			keyset.push(NEFloatKey(0.0f));	//	OUT 목적지Y
			keyset.push(NEFloatKey(0.0f));	//	OUT 목적지Z

			return RESULT_SUCCESS;
		}	

	public:
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}

	private:
		void _onDirect(Camera& camera, Model& model);
	};
}