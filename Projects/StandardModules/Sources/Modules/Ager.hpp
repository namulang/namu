#pragma once

#include "../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL Ager : public NEModule
	{
	public:
		typedef Ager ThisClass;
		typedef NEModule SuperClass;

	public:
		NETArgument<NEFloatKey> arg_target;
		NETArgument<NEFloatKey> arg_value;
		NETArgument<NEIntKey> arg_way;
		NETArgument<NEFloatKey> arg_top_border;
		NETArgument<NEFloatKey> arg_bottom_border;

	protected:
		virtual type_result _onFetchModule()
		{
			arg_top_border.setEnable(false);
			arg_bottom_border.setEnable(false);			

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchArgument(NEArgumentSet& tray)
		{
			tray.push(arg_target);
			tray.push(arg_value);
			tray.push(arg_way);
			tray.push(arg_top_border);
			tray.push(arg_bottom_border);

			return RESULT_SUCCESS;
		}

	protected:
		virtual type_result _onExecute()
		{
			arg_target.setValue(arg_target.getValue() + arg_value.getValue());

			if(	arg_top_border.isEnable()						&&
				arg_target.getValue() > arg_top_border.getValue()	)
				arg_target.setValue(arg_top_border.getValue());
			if (arg_bottom_border.isEnable()					&&
				arg_target.getValue() < arg_bottom_border.getValue())
				arg_target.setValue(arg_bottom_border.getValue());				

			return RESULT_SUCCESS;
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;

			if(_instance.isValid() != RESULT_NOTHING)
			{
				_instance.getName() = "Ager";
				_instance.getDeveloper() = "kniz";
				_instance.setRevision(1);
				_instance.getReleaseDate() = "2013/08/16";
				_instance.getComment() = "지정한 키의 값을 매번 프레임마다 지정한 값으로 변화시킵니다.\n값을 음수로 하면 매순간 지정한 키의 값이 감소되게 할 수 있습니다.";
				NETStringSet& args = _instance.getArgumentsComments();
				args.create(5);
				args.push("Target\nSet인 Key는 적용되지 않습니다.");
				args.push("Delta\n매 프레임마다 Target을 증감시킬 값입니다. 양수를 입력하면 증가가, 음수를 입력하면 감소가 됩니다.");
				args.push("\nDelta를 적용할 Function\n현재는 오직 1차 함수로만 변화되며, 이값은 사용되지 않습니다.\n예를들어 변화시킬값이 -5이면 매 프레임마다 키에 -5가 더해집니다.");
				args.push("상한값\nTarget이 증가될때 이 값보다 커지지 않도록 만듭니다.\ndisabled 되면 동작하지 않습니다.");
				args.push("하한값\nTarget이 감소될때 이 값보다 작지 않도록 만듭니다.\ndisabled되면 동작하지 않습니다.");
			}

			return _instance;
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
	};
}