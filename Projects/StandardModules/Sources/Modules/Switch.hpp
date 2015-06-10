#pragma once

#include "../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL Switch : public NEModule
	{
	public:
		typedef Switch ThisClass;
		typedef NEModule SuperClass;

	public:
		NETArgument<NEModuleCodeSetKey> arg_actions;
		NETArgument<NEIntKey>			arg_state;

	protected:
		virtual type_result _onFetchModule()
		{
			arg_actions.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_state.setPurposeLimitation(NEArgumentBase::READ_BY);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_actions);
			tray.push(arg_state);

			return RESULT_SUCCESS;
		}

	protected:
		virtual type_result _onExecute()
		{
			type_index n = arg_state.getValue();
			NEModuleCodeSet& ms = arg_actions.getValue();
			if (n >= ms.getLength())
				return ALERT_WARNING(" : State = %d의 값이 Actions의 최대 길이 = %d보다 같거나 큽니다.", n, ms.getLength());

			return ms[n].execute();
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;

			if (_instance.isValid() != RESULT_NOTHING)
			{
				_instance.getName() = "Switch";
				_instance.getDeveloper() = "kniz";
				_instance.setRevision(1);
				_instance.getReleaseDate() = "2015/06/10";
				_instance.getComment() = "State 값에 해당하는 Actions[n]을 수행합니다. ";
				NETStringSet& args = _instance.getArgumentsComments();
				args.create(5);
				args.push("Actions\nState 값과 일치하는 Actions 배열원소를 실행합니다.");
				args.push("State\switch(State)");
			}

			return _instance;
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
	};
}