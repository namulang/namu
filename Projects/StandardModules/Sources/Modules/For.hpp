#pragma once

#include "../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL For : public NEModule
	{
	public:
		typedef For ThisClass;
		typedef NEModule SuperClass;

	public:
		NETArgument<NEIntKey>			arg_iterator;
		NETArgument<NEIntKey>			arg_start_index;
		NETArgument<NEIntKey>			arg_end;
		NETArgument<NEModuleCodeSetKey> arg_actions;

	protected:
		virtual type_result _onFetchModule()
		{
			arg_iterator.setPurposeLimitation(NEArgumentBase::WRITTEN);
			arg_start_index.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_end.setValue(1);
			arg_end.setPurposeLimitation(NEArgumentBase::READ_BY);

			return RESULT_SUCCESS;
		}
		virtual type_result _onExecute()
		{
			int n		= arg_start_index.getValue(),
				end_n	= arg_end.getValue();
			for(arg_iterator.setValue(n)	; 
				n < end_n					; 
				arg_iterator.setValue(++n)	)
				arg_actions.getValue().execute();

			return arg_iterator.setValue(0);
		}

	protected:
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_iterator);
			tray.push(arg_start_index);
			tray.push(arg_end);
			tray.push(arg_actions);

			return RESULT_SUCCESS;
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;

			if (_instance.isValid() != RESULT_NOTHING)
			{
				_instance.getName() = "For";
				_instance.getDeveloper() = "kniz";
				_instance.setRevision(1);
				_instance.getReleaseDate() = "2015/01/07";
				_instance.getComment() =
					"Iterator Argument를 Start에서 End 보다 작을때까지(Start ~ End-1까지) 하나씩 증가시켜나가면서, Actions Argument를 실행합니다.\n"
					"C 문법으로 치면 다음과 같습니다.\n"
					"\tfor( int Iterator = Start ; Iterator <= End ; Iterator++)\n"
					"\t\tActions;";
				NETStringSet& args = _instance.getArgumentsComments();
				args.create(4);
				args.push("Iterator\nFor문이 한번 순환(루프)를 돌때마다 1씩 증가합니다.");
				args.push("Start\nIterator의 초기값입니다.");
				args.push("End\nIterator의 값이 이 값보다 작을때까지 순환하게 됩니다.");
				args.push("Actions\n매번 순환할때마다 실행됩니다.");					
			}

			return _instance;
		}

		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
	};
}