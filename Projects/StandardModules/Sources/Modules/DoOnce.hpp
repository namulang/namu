#pragma once

#include "../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL DoOnce : public NEModule
	{
	public:
		typedef DoOnce ThisClass;
		typedef NEModule SuperClass;

	public:
		NETArgument<NEIntKey>			arg_count;
		NETArgument<NEModuleCodeSetKey> arg_actions;

	protected:
		virtual type_result _onFetchModule()
		{
			arg_count.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_count.setValue(1);
			arg_actions.setPurposeLimitation(NEArgumentBase::READ_BY);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_count);
			tray.push(arg_actions);

			return RESULT_SUCCESS;
		}

	protected:
		virtual type_result _onExecute()
		{	
			if(arg_count.getValue() <= 0)
				return RESULT_SUCCESS | RESULT_ABORT_ACTION;

			arg_count.getKey()--;
			return arg_actions.getValue().execute();
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;

			if(_instance.isValid() != RESULT_NOTHING)
			{
				_instance.getName() = "DoOnce";
				_instance.getDeveloper() = "kniz";
				_instance.setRevision(1);
				_instance.getReleaseDate() = "2015/05/26";
				_instance.getComment() = 
					"특정 프레임 횟수(FrameCount)만큼 NEModuleCodeSet을 수행합니다.\n";
					"단순히 반복문과는 행동이 다릅니다. 예를들어, FrameCount가 3일 경우, 3 Frame(모든 Module이 1번 수행되는 걸 1 프레임이라 합니다) 동안 Action가 수행됩니다.\n"
					"반면에 \"For\" Module을 start index = 0, end index = 2로 한 경우는 매 Frame마다 연속적으로 Actions가 3번 실행되는 결과가 나옵니다.\n";
				NETStringSet& args = _instance.getArgumentsComments();
				args.create(2);
				args.push("FrameCount\n양수일 동안 Actions가 각 Frame에 1번 수행됩니다. Actions가 수행될 때마다 FrameCount가 1 감소합니다.");
				args.push("Actions\nFrameCount가 양수이면 수행됩니다.");
			}

			return _instance;
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
	};
}