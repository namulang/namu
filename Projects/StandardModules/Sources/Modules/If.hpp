#pragma once

#include "../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL If : public NEModule
	{
	public:
		typedef If ThisClass;
		typedef NEModule SuperClass;

	public:
		NETArgument<NEModuleCodeSetKey> arg_condition;
		NETArgument<NEModuleCodeSetKey> arg_action;
		NETArgument<NEModuleCodeSetKey> arg_else;
		NETArgument<NEBooleanSetKey>	arg_flags;
		NETArgument<NEBooleanKey>		arg_logic;

	protected:
		virtual type_result _onFetchModule()
		{
			arg_else.setEnable(false);

			return RESULT_SUCCESS;
		}
<<<<<<< HEAD
		virtual type_result _onFetchArguments(NEArgumentList& tray)
=======
		virtual type_result _onFetchArgument(NEArgumentSet& tray)
>>>>>>> 7cc208e99f52313036b5accd74a9b207b90d2e65
		{
			tray.push(arg_condition);
			tray.push(arg_flags);
			tray.push(arg_logic);
			tray.push(arg_action);
			tray.push(arg_else);

			return RESULT_SUCCESS;
		}

	protected:
		virtual type_result _onExecute()
		{
			if(_judgeConditions())
				return _executeModules(arg_action);

			return _executeModules(arg_else);
		}
	private:
		type_result _executeModules(NETArgument<NEModuleCodeSetKey>& modules)
		{
			if(arg_condition.isEnable())
				return arg_condition.getValue().execute();

			return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		}
		bool _judgeConditions()
		{
			NEModuleCodeSet& conditions	= arg_condition.getValue();
			NEBooleanSet& flags			= arg_flags.getValue();


			for(int n=0; n < conditions.getLength() ;n++)
			{
				type_bool	flag = n <= flags.getLengthLastIndex() ? flags[n] : true,
					condition = NEResult::hasTrue(conditions[n].execute());

				if( ! arg_logic.getValue())
				{
					if(flag == condition)
						return true;
				}
				else
				{	//	And 연산:
					if(flag != condition)
						return false;
				}
			}

			if(arg_logic.getValue())	
				return false;	//	OR연산에서 전부다 FALSE가 나온다면
			else
				return true;	//	AND연산에서 전부다 TRUE가 나오면
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;

			if(_instance.isValid() != RESULT_NOTHING)
			{
				_instance.getName() = "If";
				_instance.getDeveloper() = "kniz";
				_instance.setRevision(1);
				_instance.getReleaseDate() = "2012/04/14";
				_instance.getComment() = 
					"특정한 Module을 수행하여 그 값이 TRUE인지 FALSE인지에 따라서 각각 다른 모듈을 수행하게 합니다.\n"
					"Flags는 \"Conditions의 특정 인덱스에 위치한 Module의 결과값\"이 Flags의 그 인덱스의 원소와 일치하는 지를 판단합니다.\n"
					"Logic은 Flags와 Conditions를 비교한 값들을 or 혹은 and로 연산합니다.\n"
					"\t예를들어, Flags[0] = TRUE, Flags[1] = FALSE, Condtions[0] = TRUE, conditions[1] = TRUE 이면,\n"
					"\tLogic이 \"or\" 일때 Actions 모듈을 수행합니다. 반면 \"and\"이면 Elses가 enable이 되어있을때 Elses를 수행합니다.\n"
					"참고로 Module의 개발자가 반환값을 지정하지 않을 경우 FALSE가 기본값이며,\n"
					"Flags를 정의하지 않은 경우, TRUE로 여겨집니다.\n";					
				NETStringSet& args = _instance.getArgumentsComments();
				args.create(5);
				args.push("Conditions\n조건절입니다. 이 모듈들을 수행하고, 그 반환값이 TRUE인지 FALSE인지 확인합니다.");
				args.push("Flags\n각 Boolean 인덱스는 Conditions의 원소와 매칭됩니다.\nCondition의 그 Module이 이 Boolean값과 일치하면 TRUE가 됩니다. ");
				args.push("Use \"or\" Operation?\n\"or\"면 임의의 n에 대해 Condtion[n]과 Flags[n]이 값이 일치하는 경우가 있으면 TRUE입니다.\n\"and\"면, 모두 일치해야 TRUE 입니다.");
				args.push("Actions\nLogic이 최종적으로 TRUE일때 수행하는 Module 들입니다.\ndisabled 되면 수행하지 않습니다.");
				args.push("Elses\nLogic이 최종적으로 False일때 수행하는 Module 들입니다.\ndisabled 되면 수행하지 않습니다.");
			}

			return _instance;
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
	};
}