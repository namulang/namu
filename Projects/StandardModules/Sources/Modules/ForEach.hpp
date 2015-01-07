#pragma once

#include "../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL ForEach : public NEModule
	{
	public:
		typedef ForEach ThisClass;
		typedef NEModule SuperClass;

	public:
		NETArgument<NEKey>				arg_selector;
		NETArgument<NEModuleCodeSetKey>	arg_actions;		

	protected:
		virtual type_result _onFetchModule()
		{
			arg_actions.setPurposeLimitation(NEArgumentBase::READ_BY);

			return RESULT_SUCCESS;
		}
		virtual type_result _onExecute()
		{
			NEKey& sel_key = arg_selector.getValueKey();
			if( ! sel_key.isSubClassOf(NEType::NENODE_SELECTOR))
			{
				ALERT_WARNING(" : 주어진 arg_selector가 SELECTOR 키 가 아닙니다.\n\t주어진 키의 타입 : %s", sel_key.getTypeName());
				return RESULT_TYPE_WARNING | RESULT_INVALID_DATA;
			}	


			//	main:
			NENodeSelector& minimum_casted = static_cast<NENodeSelector&>(sel_key);
			//		초기상태 기억:	작업이 끝나면 복원해줘야 한다.
			bool origins_peeking_lock = minimum_casted.isPeekingLocked();
			//		루프 시작:
			while(_moveForward(minimum_casted))
				arg_actions.getValue().execute();


			//	post:
			minimum_casted.isPeekingLocked() = origins_peeking_lock;
			return RESULT_SUCCESS;
		}

	private:
		bool _moveForward(NENodeSelector& target)
		{
			target.isPeekingLocked() = true;

			bool is_end_of_searching = false;
			if (target.isSubClassOf(NEType::NEKEY_SELECTOR))
				is_end_of_searching = ! &(static_cast<NEKeySelector&>(target)).getKey();
			else if (target.isSubClassOf(NEType::NEMODULE_SELECTOR))
				is_end_of_searching = ! &(static_cast<NEModuleSelector&>(target)).getModule();
			else
				is_end_of_searching = ! &target.getNode();

			target.isPeekingLocked() = false;

			return is_end_of_searching;
		}

	protected:
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_selector);
			tray.push(arg_actions);

			return RESULT_SUCCESS;
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;

			if (_instance.isValid() != RESULT_NOTHING)
			{
				_instance.getName() = "ForEach";
				_instance.getDeveloper() = "kniz";
				_instance.setRevision(1);
				_instance.getReleaseDate() = "2015/01/07";
				_instance.getComment() =
					"Selector Argument에 넣은 NodeSelector, ModuleSelector, KeySelector중 하나가 "
					"참조하는 객체들마다 Actions Argument를 실행시킵니다."
					"사용법은 다음과 같습니다.\n"
					"\t1. 원하는 Selector에 대한 Key를 하나 만듭니다.\n"
					"\t2. 그 키를 SelectorArgument에 넣습니다.\n"
					"\t3. Actions에 모듈을 만들어, 앞서 만든 SelectorKey를 Argument에 넣어줍니다.";
				NETStringSet& args = _instance.getArgumentsComments();
				args.create(2);
				args.push("Selector\n순환(루프)하게 될 객체를 가리키는 Selector 입니다.\nNodeSelector, ModuleSelector, KeySelector 전부 호환됩니다.");
				args.push("Actions\nSelector로부터 나온 객체 하나마다 여기에 있는 모든 모듈들을 실행합니다.");
			}

			return _instance;
		}

		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
	};
}