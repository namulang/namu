#pragma once

#include "../../Includes/Includes.hpp"

namespace MetaWorld
{
	class NE_DLL NodeBinder : public NEModule
	{
	public:
		typedef NodeBinder ThisClass;
		typedef NEModule SuperClass;

	public:
		const NENodeSelector& getSourceSelector() const
		{
			const NEKey& key = getKeySet()[0];
			if( ! &key || ! key.isSubClassOf(NEType::NENODE_SELECTOR))
			{
				ALERT_ERROR("0번 키는 NENODE_SELECTOR 여야 합니다.");
				NENodeSelector* nullptr = 0;
				return *nullptr;
			}

			return static_cast<const NENodeSelector&>(key);
		}
		NENodeSelector& getSourceSelector()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<NENodeSelector&>(casted->getSourceSelector());
		}

	public:
		virtual type_result initialize()
		{
			NEKeyCodeSet& ks = getKeySet();
			ks.create(1);
			ks.push(NENodeSelector());	//	0:	ScriptEditor에 있는 원본 노드. NodeVisualizer, WorldVisualizer에 의해서 바인딩된다.
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
				_instance.getName() = "NodeBinder";
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