#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL NodeCopier : public NEModule
	{
	public:
		typedef NodeCopier ThisClass;
		typedef NEModule SuperClass;

	public:
		NodeCopier();
		NodeCopier(const NodeCopier& source);

	public:
		virtual ~NodeCopier();

	public:
		const NENodeSelector& getWhoSelector() const
		{
			const NEKey& key = getKeySet()[0];
			if( ! &key || ! key.isSubClassOf(NEType::NENODE_SELECTOR))
			{
				ALERT_ERROR("0번 키는 NENODE_SELECTOR여야 합니다.");
				NENodeSelector* nullpoint = 0;
				return *nullpoint;
			}

			return static_cast<const NENodeSelector&>(key);
		}
		NENodeSelector& getWhoSelector()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<NENodeSelector&>(casted->getWhoSelector());
		}
		const NEKeySelector& getWhereSelector() const
		{
			const NEKey& key = getKeySet()[1];
			if( ! &key || ! key.isSubClassOf(NEType::NEKEY_SELECTOR))
			{
				ALERT_ERROR("1번 키는 NEKEY_SELECTOR여야 합니다.");
				NEKeySelector* nullpoint = 0;
				return *nullpoint;
			}

			return static_cast<const NEKeySelector&>(key);
		}
		NEKeySelector& getWhereSelector()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<NEKeySelector&>(casted->getWhereSelector());
		}
		const type_ubyte& getCodeType() const
		{
			const NEKey& key = getKeySet()[2];
			if( ! &key || ! key.isSubClassOf(NEType::NEUBYTE_KEY))
			{
				ALERT_ERROR("2번 키는 NEUBYTE_KEY여야 합니다.");
				type_ubyte* nullpoint = 0;
				return *nullpoint;
			}

			return (static_cast<const NEUByteKey&>(key)).getValue();
		}
		type_ubyte& getCodeType()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_ubyte&>(casted->getCodeType());
		}
		const type_int& getCodeValue() const
		{
			const NEKey& key = getKeySet()[3];
			if( ! &key || ! key.isSubClassOf(NEType::NEINT_KEY))
			{
				ALERT_ERROR("3번 키는 NE_INT_KEY여야 합니다.");
				type_int* nullpoint = 0;
				return *nullpoint;
			}

			return (static_cast<const NEIntKey&>(key)).getValue();
		}
		type_int& getCodeValue()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_int&>(casted->getCodeValue());
		}
		const type_int& getIndexToInsert() const
		{
			const NEKey& key = getKeySet()[4];
			if( ! &key || ! key.isSubClassOf(NEType::NEINT_KEY))
			{
				ALERT_ERROR("4번 키는 NE_INT_KEY여야 합니다.");
				type_int* nullpoint = 0;
				return *nullpoint;
			}

			return (static_cast<const NEIntKey&>(key)).getValue();
		}
		type_int& getIndexToInsert()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_int&>(casted->getIndexToInsert());
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
