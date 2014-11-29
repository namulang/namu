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
		NETArgument<NEFloatKey> target;
		NETArgument<NEFloatKey> value;
		NETArgument<NEIntKey> way;
		NETArgument<NEFloatKey> top_border;
		NETArgument<NEFloatKey> bottom_border;

	protected:
		virtual type_result _onFetchArgument(NEArgumentInterfaceList& tray)
		{
			tray.push(target);
			tray.push(value);
			tray.push(way);
			tray.push(top_border);
			tray.push(bottom_border);

			return RESULT_SUCCESS;
		}

	protected:
		virtual type_result _onExecute()
		{
			target.getValue() += value.getValue();

			if(	top_border.getConcreteInstance().isBinded()	&&
				target.getValue() > top_border.getValue())
				target.getValue() = top_border.getValue();
			if (bottom_border.getConcreteInstance().isBinded() &&
				target.getValue() < bottom_border.getValue())
				target.getValue() = bottom_border.getValue();				

			return RESULT_SUCCESS;
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;

			if(_instance.isValid() != RESULT_NOTHING)
			{
				_instance.getName() = "Aging";
				_instance.getDeveloper() = "kniz";
				_instance.setRevision(1);
				_instance.getReleaseDate() = "2013/08/16";
				_instance.getComment() = "지정한 키의 값을 매번 프레임마다 지정한 값으로 변화시킵니다.\n값을 음수로 하면 매순간 지정한 키의 값이 감소되게 할 수 있습니다.";
				NETStringSet& args = _instance.getArgumentsComments();
				args.create(5);
				args.push("Target\nSet인 Key는 적용되지 않습니다.");
				args.push("Delta\n매 프레임마다 Target을 증감시킬 값입니다. 양수를 입력하면 증가가, 음수를 입력하면 감소가 됩니다.");
				args.push("\nDelta를 적용할 Function\n현재는 오직 1차 함수로만 변화되며, 이값은 사용되지 않습니다.\n예를들어 변화시킬값이 -5이면 매 프레임마다 키에 -5가 더해집니다.");
				args.push("상한값\nTarget이 증가될때 이 값보다 커지지 않도록 만듭니다.\n키를 넣지 않으면 동작하지 않습니다.");
				args.push("하한값\nTarget이 감소될때 이 값보다 작지 않도록 만듭니다.\n키를 넣지 않으면 동작하지 않습니다.");
			}

			return _instance;
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
	};
}