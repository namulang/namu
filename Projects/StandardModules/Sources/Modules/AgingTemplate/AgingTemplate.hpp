#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	template <typename T, NEType::Type TYPE>
	class NE_DLL AgingTemplate : public NEModule
	{
	public:
		typedef AgingTemplate<T, TYPE> ThisClass;
		typedef NEModule SuperClass;
		typedef NEKeyTemplate<T, TYPE> KeyClass;

	public:
		NEKeySelector& getKeySelector()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<NEKeySelector&>(casted->getKeySelector());
		}
		const NEKeySelector& getKeySelector() const
		{
			const NEKey& somekey = getKeySet()[0];
			if( ! somekey.isSubClassOf(NEType::NEKEY_SELECTOR))
			{
				ALERT_ERROR("0의 타입은 NEKEY_SELECTOR여야 합니다.");
				const NEKeySelector* nullpoint = 0;
				return *nullpoint;
			}

			const NEKeySelector& target = static_cast<const NEKeySelector&>(somekey);
			return target;
		}
		T& getAgingValue()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<T&>(casted->getAgingValue());
		}
		const T& getAgingValue() const
		{
			const NEKey& somekey = getKeySet()[1];
			if( ! somekey.isSubClassOf(TYPE))
			{
				ALERT_ERROR("1의 타입은 %d여야 합니다.", TYPE);
				const T* nullpoint = 0;
				return *nullpoint;
			}

			const KeyClass& target = static_cast<const KeyClass&>(somekey);
			return target.getValue();
		}
		type_int& getAgingWay()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_int&>(casted->getAgingWay());
		}
		const type_int& getAgingWay() const
		{
			const NEKey& somekey = getKeySet()[2];
			if( ! somekey.isSubClassOf(NEType::NEINT_KEY))
			{
				ALERT_ERROR("2의 타입은 NEINT_KEY여야 합니다.");
				type_int* nullpoint = 0;
				return *nullpoint;
			}

			const NEIntKey& target = static_cast<const NEIntKey&>(somekey);
			return target.getValue();
		}

	public:
		virtual type_result initialize()
		{
			SuperClass::initialize();
			NEKeyCodeSet& keyset = getKeySet();
			keyset.resize(3);
			keyset.push(NEKeySelector());
			keyset.push(KeyClass());
			keyset.push(NEIntKey());

			return RESULT_SUCCESS;
		}
		virtual type_result execute()
		{
			while(NEKey* key = &getKeySelector().getKey())
			{
				if( ! key) continue;

				*key += getKeySet()[1];				
			}
			
			return RESULT_SUCCESS;
		}
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;

			if(_instance.isValid() != RESULT_NOTHING)
			{
				_instance.getName() = "AgingTemplate";
				_instance.getDeveloper() = "kniz";
				_instance.setRevision(1);
				_instance.getReleaseDate() = "2013/08/16";
				_instance.getComment() = "0번: 타겟Key \n1번: +할 값 \n2번: 증가함수";
			}

			return _instance;
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
	};
}