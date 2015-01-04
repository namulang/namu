#pragma once

#include "NamedUnitTagger.hpp"

namespace NE
{
	class NE_DLL ModuleTagger : public NamedUnitTagger
	{
	public:
		typedef ModuleTagger ThisClass;
		typedef NamedUnitTagger SuperClass;

	public:
		NETArgument<NEModuleSelector>	arg_targets;

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
			NEModuleSelector& ns = arg_targets.getValue();
			while(NEModule* n = &ns.getModule())
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

			if (!is_triggered_once)
			{
				is_triggered_once = true;
				NEExportable::ModuleHeader supers = SuperClass::getHeader();

				_instance.getName() = "ModuleTagger";
				_instance.getDeveloper() = "kniz";
				_instance.setRevision(1);
				_instance.getReleaseDate() = "2015/01/02";
				_instance.getComment() =
					"참조한 Module 객체들의 특정 속성값들을 가져오거나(get) 할당할 수 있습니다(set).\n"
					"\tTargets:\t참조할 객체들\n" +
					supers.getComment();
				//"주어진 객체들의 다음과 같은 속성들에 대해서 값을 가져오거나 할당 할 수 있습니다.\n"
				//"\tEnable:\t객체의 활성화 여부.\n"
				//"\tCodes:\t객체의 주어진 Code값들";					
				NETStringSet& args = _instance.getArgumentsComments();
				const NETStringSet& super = supers.getArgumentsComments();
				args.create(super.getLength() + 1);
				args.push("Targets\n속성을 가져오거나 할당하게될 Module 들입니다.");
				args.push(supers);
			}

			return _instance;
		}
	};
}