#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL ModuleInfoExtractor : public NEModule
	{
	public:
		typedef ModuleInfoExtractor ThisClass;
		typedef NEModule SuperClass;

	public:
#include "InfoType.hpp"

	public:
		ModuleInfoExtractor();
		ModuleInfoExtractor(const ModuleInfoExtractor& source);

	public:
		virtual ~ModuleInfoExtractor();

	public:
		const type_int& getModuleCode() const
		{
			const NEKey& key = getKeySet()[0];
			if( ! &key || ! key.isSubClassOf(NEType::NEINT_KEY))
			{
				ALERT_ERROR("0번 키는 NE_INT_KEY여야 합니다.");
				type_int* nullpoint = 0;
				return *nullpoint;
			}

			return (static_cast<const NEIntKey&>(key)).getValue();
		}
		type_int& getModuleCode()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_int&>(casted->getModuleCode());
		}
		const type_ubyte& getInfoType() const
		{
			const NEKey& key = getKeySet()[1];
			if( ! &key || ! key.isSubClassOf(NEType::NEUBYTE_KEY))
			{
				ALERT_ERROR("1번 키는 NEUBYTE_KEY여야 합니다.");
				type_ubyte* nullpoint = 0;
				return *nullpoint;
			}

			return (static_cast<const NEUByteKey&>(key)).getValue();
		}
		type_ubyte& getInfoType()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_ubyte&>(casted->getInfoType());
		}
		const NETString& getExtracted() const
		{
			const NEKey& key = getKeySet()[2];
			if( ! &key || ! key.isSubClassOf(NEType::NETSTRING_KEY))
			{
				ALERT_ERROR("2번 키는 NETSTRING_KEY여야 합니다.");
				NETString* nullpoint = 0;
				return *nullpoint;
			}

			return (static_cast<const NETStringKey&>(key)).getValue();
		}
		NETString& getExtracted()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<NETString&>(casted->getExtracted());
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
