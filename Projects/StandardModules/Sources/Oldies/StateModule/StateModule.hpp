#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL StateModule : public NEModule
	{
	public:
		typedef StateModule ThisClass;
		typedef NEModule SuperClass;

	public:
		StateModule();
		StateModule(const ThisClass& source);

	public:
		virtual ~StateModule();

	public:
		const NEModuleCodeSet& getActions() const
		{
			const NEKey& key = getKeySet()[0];
			if( ! &key || ! key.isSubClassOf(NEType::NEMODULE_CODESET_KEY))
			{
				ALERT_ERROR("0번키는 NEMODULE_CODESET_KEY여야 합니다.");
				NEModuleCodeSet* nullpoint = 0;
				return *nullpoint;
			}

			return static_cast<const NEModuleCodeSetKey&>(key).getValue();
		}
		NEModuleCodeSet& getActions()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<NEModuleCodeSet&>(casted->getActions());
		}
		const type_int& getState() const
		{
			const NEKey& key = getKeySet()[1];
			if( ! &key || ! key.isSubClassOf(NEType::NEINT_KEY))
			{
				ALERT_ERROR("1번키는 NEINT_KEY여야 합니다.");
				type_int* nullpoint = 0;
				return *nullpoint;
			}
			return static_cast<const NEIntKey&>(key).getValue();
		}
		type_int& getState()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_int&>(casted->getState());
		}

	public:
		virtual type_result initialize();

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;

	public:
		virtual type_result execute();	

	public:
		virtual NEObject& clone() const;
	};
}
