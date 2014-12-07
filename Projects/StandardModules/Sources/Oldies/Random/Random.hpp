#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL Random : public NEModule
	{
	public:
		typedef Random ThisClass;
		typedef NEModule SuperClass;

	public:
		Random();
		Random(const ThisClass& source);

	public:
		virtual ~Random();

	public:
		const NEKeySelector& getTargets() const
		{
			const NEKey& key = getKeySet()[0];
			if( ! &key || ! key.isSubClassOf(NEType::NEKEY_SELECTOR))
			{
				ALERT_ERROR("0번키는 NEKEY_SELECTOR여야 합니다.");
				NEKeySelector* nullpoint = 0;
				return *nullpoint;
			}

			return static_cast<const NEKeySelector&>(key);
		}
		NEKeySelector& getTargets()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<NEKeySelector&>(casted->getTargets());
		}
		const type_int& getMaximum() const
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
		type_int& getMaximum()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_int&>(casted->getMaximum());
		}
		const type_int& getMinimum() const
		{
			const NEKey& key = getKeySet()[2];
			if( ! &key || ! key.isSubClassOf(NEType::NEINT_KEY))
			{
				ALERT_ERROR("2번키는 NEINT_KEY여야 합니다.");
				type_int* nullpoint = 0;
				return *nullpoint;
			}
			return static_cast<const NEIntKey&>(key).getValue();
		}
		type_int& getMinimum()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_int&>(casted->getMinimum());
		}
		const type_float& getRate() const
		{
			const NEKey& key = getKeySet()[3];
			if( ! &key || ! key.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("3번키는 NEFLOAT_KEY여야 합니다.");
				type_float* nullpoint = 0;
				return *nullpoint;
			}
			return static_cast<const NEFloatKey&>(key).getValue();
		}
		type_float& getRate()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_float&>(casted->getRate());
		}

	public:
		virtual type_result initialize();

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;

	public:
		virtual type_result execute();	

	public:
		virtual NEObject& clone() const;

	private:
		type_float _createRandomValue();
	};
}
