#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL MessageSender : public NEModule
	{
	public:
		typedef MessageSender ThisClass;
		typedef NEModule SuperClass;

	public:
		MessageSender();
		MessageSender(const MessageSender& source);

	public:
		virtual ~MessageSender();

	public:
		const NEModuleSelector& getTargetSelector() const
		{
			const NEKey& key = getKeySet()[0];
			if( ! &key || key.getType() != NEType::NENODE_SELECTOR)
			{
				ALERT_ERROR("0번키의 타입이 NENODE_SELECTOR여야 합니다.");
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
		const type_ubyte& getMessageIndexToSend() const
		{
			const NEKey& key = getKeySet()[1];
			if( ! &key || key.getType() != NEType::NEUBYTE_KEY)
			{
				ALERT_ERROR("1번키의 타입이 NEUBYTE_KEY여야 합니다.");
				type_ubyte* nullpoint = 0;
				return *nullpoint;
			}

			return (static_cast<const NEUByteKey&>(key)).getValue();
		}
		type_ubyte& getMessageIndexToSend()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_ubyte&>(casted->getMessageIndexToSend());
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
