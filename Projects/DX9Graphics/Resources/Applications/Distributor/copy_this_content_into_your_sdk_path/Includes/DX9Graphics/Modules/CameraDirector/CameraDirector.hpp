#pragma once

#include "../CameraSelector/CameraSelector.hpp"

namespace DX9Graphics
{
	class Camera;
	class Model;

	class NE_DLL CameraDirector : public CameraSelector
	{
	public:
		typedef CameraDirector ThisClass;
		typedef CameraSelector SuperClass;

	public:
		const NEModuleSelector& getTargetSelector() const
		{
			const NEKey& key = getKeySet()[1];
			if( ! &key || key.getType() != NEType::NEMODULE_SELECTOR)
			{
				ALERT_ERROR(" : 1번키는 NEMODULE_SELECTOR여야 합니다.");
				NEModuleSelector* nullpoint = 0;
				return *nullpoint;
			}

			return static_cast<const NEModuleSelector&>(key);
		}
		NEModuleSelector& getTargetSelector() 
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<NEModuleSelector&>(casted->getTargetSelector());
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;

	public:
		virtual type_result initialize()
		{
			SuperClass::initialize();

			NEKeyCodeSet& keyset = getKeySet();
			keyset.resize(keyset.getLength() + 1);	
			keyset.push(NEModuleSelector());	//	TARGET

			return RESULT_SUCCESS;
		}	

	public:
		virtual type_result execute();

	public:
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}	

	private:
		virtual void _onDirect(Camera& camera, Model& model);
	};
}