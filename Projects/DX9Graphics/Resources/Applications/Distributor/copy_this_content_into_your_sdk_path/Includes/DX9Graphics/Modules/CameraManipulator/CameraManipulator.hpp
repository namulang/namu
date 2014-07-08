#pragma once

#include "../CameraSelector/CameraSelector.hpp"

namespace DX9Graphics
{
	class NE_DLL CameraManipulator : public CameraSelector
	{
		typedef CameraManipulator ThisClass;
		typedef CameraSelector SuperClass;

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;

	public:
		virtual type_result initialize()
		{
			SuperClass::initialize();
			
			NEKeyCodeSet& keyset = getKeySet();
			keyset.resize(keyset.getLength() + 2);	
			keyset.push(NEByteKey(0));			//	이동 타입
			keyset.push(NEFloatKey(0.0f));		//	정도

			return RESULT_SUCCESS;
		}	

	public:
		virtual type_result execute();

	public:
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
	};
}