#pragma once

#include "../../Includes/Includes.hpp"

namespace MetaWorld
{
	class NE_DLL PanelBinder : public NEModule
	{
	public:
		typedef PanelBinder ThisClass;
		typedef NEModule SuperClass;

	public:
		const NEModuleSelector& getSourceSelector() const
		{
			const NEKey& key = getKeySet()[0];
			if( ! &key || ! key.isSubClassOf(NEType::NEMODULE_SELECTOR))
			{
				ALERT_ERROR("0번 키는 NEMODULE_SELECTOR 여야 합니다.");
				NEModuleSelector* nullptr = 0;
				return *nullptr;
			}

			return static_cast<const NEModuleSelector&>(key);
		}
		NEModuleSelector& getSourceSelector()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<NEModuleSelector&>(casted->getSourceSelector());
		}

	public:
		virtual type_result initialize()
		{
			NEKeyCodeSet& ks = getKeySet();
			ks.create(1);
			ks.push(NEModuleSelector());	//	0:	Panel을 바인딩할 모듈.
			return RESULT_SUCCESS;
		}

	public:
		virtual type_result execute()
		{
			return RESULT_SUCCESS;
		}
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;

			if(_instance.getName().getSize() <= 0)
			{
				_instance.getName() = "PanelBinder";
				_instance.setRevision(1);
				_instance.getDeveloper() = "kniz";
			}

			return _instance;
		}

	public:
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}

	public:
		static const NECodeSet& getScriptCodeSet()
		{
			static NECodeSet _instance;
			if(_instance.getSize() <= 0)
			{
				_instance.create(1);
				_instance.setCodeType(NECodeType::SCRIPT);
				_instance.push(ThisClass().getHeader());
			}

			return _instance;
		}

	};
}