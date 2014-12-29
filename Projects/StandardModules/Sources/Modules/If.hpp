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
		NETArgument<NEIntKey>			arg_logic;
		NETArgument<NEBooleanSetKey>	arg_flags;
		NETArgument<NEModuleCodeSetKey> arg_action;
		NETArgument<NEModuleCodeSetKey> arg_else;

	protected:
		virtual type_result _onFetchModule()
		{
			arg_else.setEnable(false);
			arg_flags.setEnable(false);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_condition);
			tray.push(arg_logic);
			tray.push(arg_flags);
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
			if (modules.isEnable())
				return modules.getValue().execute();

			return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		}
		bool _judgeConditions()
		{
			NEModuleCodeSet& conditions	= arg_condition.getValue();
			NEBooleanSet& flags				= arg_flags.getValue();
			type_int arg_logic				= arg_logic.getValue();
			if(arg_logic == 4) return true;	//	ALWAYS

			for(int n=0; n < conditions.getLength() ;n++)
			{
				type_bool	flag = (flags.isEnable() && n <= flags.getLengthLastIndex()) ?
					flags[n] :
				true;
				type_bool	condition = NEResult::hasTrue(conditions[n].execute());

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
					"Logic이 True가 되면, ACTIONS를 수행하고, FALSE가 되면 ELSES를 수행하나, disabled되면 수행하지 않습니다.\n"
					"Flags[n] == Conditions[n] 한 결과값들을 놓고, Logic에서 최종적으로 TRUE / FALSE를 도출합니다."
					"Logic 총 5종류가 있습니다.\n"
					"\t0: 모두다 참일 때 (AND TRUE)""\t1: 모두다 거짓일때 (AND FALSE)\n"
					"\t2: 하나라도 참일 때 (OR TRUE)""\t3: 하나라도 거짓일때 (OR FALSE)\n"
					"\t4: 항상 (ALWAYS)\n"
					"예를들어, Flags Enable, Flags[0] = TRUE, Flags[1] = FALSE, Condtions[0] = TRUE, conditions[1] = TRUE 이면,\n"
					"\tLogic이 \"AND TRUE\" 일때 Flags[1] != conditions[1] 이므로 Elses 모듈을 수행합니다. 반면 \"OR FALSE\"이면 conditions[1] != Flags[1]이므로 Actions를 수행합니다.\n"
					"참고로 Conditons의 놓여진 Module은, 개발자가 따로 지정 하지 않으면 FALSE가 기본값입니다.\n";
				NETStringSet& args = _instance.getArgumentsComments();
				args.create(5);
				args.push("Conditions\n조건절입니다. 이 모듈들을 수행하고, 그 반환값이 TRUE인지 FALSE인지 확인합니다.");
				args.push("Logic \"Conditions에 있는 모듈의 결과에 따라서 TRUE면 Actions를, FALSE면 ELSES를 수행합니다.\n0 : \"AND TRUE\"   1:\"AND FALSE\"    2:\"OR TRUE\"    3:\"OR FALSE\"    4:\"ALWAYS\"");
				args.push("Flags\nEnable 될때만 동작합니다. 각 Flag는 Conditions의 결과값과 비교연산합니다.\nCondition[n]의 결과가 Flags[n]과 같으면 TRUE가 되고, 이런 값들을 토대로 Logic에서 최종 판단합니다.");
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