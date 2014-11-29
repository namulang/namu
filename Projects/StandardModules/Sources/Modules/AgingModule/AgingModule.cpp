#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL AgingModule : public NEModule
	{
	public:
		typedef AgingModule ThisClass;
		typedef NEModule SuperClass;

	public:
		NETArgument<NEKeySelector> target;
		NETArgument<NEFloatKey> value;
		NETArgument<NEIntKey> way;

	protected:
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(target);
			tray.push(value);
			tray.push(way);

			return RESULT_SUCCESS;
		}

	protected:
		virtual type_result _onExecute()
		{
			NEKey& binded = target.getConcreteInstance().getBindedKey();
			if(binded.isSubClassOf(NEType::NEKEY_SELECTOR))
				while(NEKey* key = &target.getValue().getValue())
					*key += value.getKey();
			else
				binded += value.getKey();
			
			return RESULT_SUCCESS;
		}
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;

			if(_instance.isValid() != RESULT_NOTHING)
			{
				_instance.getName() = "AgingModule";
				_instance.getDeveloper() = "kniz";
				_instance.setRevision(1);
				_instance.getReleaseDate() = "2013/08/16";
				_instance.getComment() = "지정한 키의 값을 매번 프레임마다 지정한 값으로 변화시킵니다.\n값을 음수로 하면 매순간 지정한 키의 값이 감소되게 할 수 있습니다.";
				NETStringSet& args = _instance.getArgumentsComments();
				args.create(3);
				args.push("변화시킬 키를 지정합니다. Set인 Key는 적용되지 않습니다.");
				args.push("매 프레임마다 변화시킬 값입니다.");
				args.push("변화시키는 방법입니다. 현재는 오직 1차 함수로만 변화되며, 이값은 사용되지 않습니다.\n 예를들어 변화시킬값이 -5이면 매 프레임마다 키에 -5가 더해집니다.");
			}

			return _instance;
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
	};
}