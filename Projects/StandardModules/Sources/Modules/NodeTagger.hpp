#pragma once

#include "NamedUnitTagger.hpp"

namespace NE
{
	class NE_DLL NodeTagger : public NamedUnitTagger
	{
	public:
		typedef NodeTagger ThisClass;
		typedef NamedUnitTagger SuperClass;

	public:
		NETArgument<NENodeSelector>	arg_targets;

	protected:
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_targets);

			return SuperClass::_onFetchArguments(tray);
		}

	protected:
		using SuperClass::_onExecute;
		virtual type_result _onExecute()
		{
			type_result result = RESULT_SUCCESS;
			NENodeSelector& ns = arg_targets.getValue();
			while(NENode* n = &ns.getNode())
				result |= _onExecute(*n);

			return result;
		}

	public:
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;
			static bool is_triggered_once = false;

			if( ! is_triggered_once)
			{
				is_triggered_once = true;
				NEExportable::ModuleHeader supers = SuperClass::getHeader();

				_instance.getName() = "NodeTagger";
				_instance.getDeveloper() = "kniz";
				_instance.setRevision(1);
				_instance.getReleaseDate() = "2015/01/02";
				_instance.getComment() =
					"참조한 Node 객체들의 특정 속성값들을 가져오거나(get) 할당할 수 있습니다(set).\n"
					"\tTargets:\t참조할 객체들\n" +
					supers.getComment();
				//"주어진 객체들의 다음과 같은 속성들에 대해서 값을 가져오거나 할당 할 수 있습니다.\n"
				//"\tEnable:\t객체의 활성화 여부.\n"
				//"\tCodes:\t객체의 주어진 Code값들";					
				NETStringSet args = supers.getArgumentsComments();
				args.resize(args.getLength() + 1);
				args.pushFront("Targets\n속성을 가져오거나 할당하게될 Node 들입니다.");
			}

			return _instance;
		}
	};
}