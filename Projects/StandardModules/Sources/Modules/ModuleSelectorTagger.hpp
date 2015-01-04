#pragma once

#include "NodeSelectorTaggerBase.hpp"

namespace NE
{
	class NE_DLL ModuleSelectorTagger : public NodeSelectorTaggerBase
	{
	public:
		typedef ModuleSelectorTagger ThisClass;
		typedef NodeSelectorTaggerBase SuperClass;

	public:
		NETArgument<NEModuleSelector>	arg_target;
		NETArgument<NECodeSetKey>		arg_module_codes;

	protected:
		virtual type_result _onFetchModule()
		{
			SuperClass::_onFetchModule();

			arg_module_codes.setEnable(false);
			arg_module_codes.setPurposeLimitation(NEArgumentBase::READ_OR_WRITTEN);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_target);
			tray.push(arg_module_codes);

			return SuperClass::_onFetchArguments(tray);
		}

	protected:
		using SuperClass::_passPipes;
		type_result _passPipes(NEModuleSelector& m)
		{
			type_result result = RESULT_SUCCESS;

			if(arg_module_codes.isEnable())
			{
				const NECodeSet& codes = arg_module_codes.getValue();

				if (arg_module_codes.getPurpose() == NEArgumentBase::READ_BY)
					m.setModuleCodes(codes);
				else
					result |= arg_module_codes.setValue(m.getModuleCodes());
			}			

			return result;
		}
		virtual type_result _onExecute()
		{
			NEModuleSelector& ms = arg_target.getValue();
			NENodeSelector& ns = ms;

			type_result result = _passPipes(ns);			

			return result |= _passPipes(ms);
		}

	public:
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;

			if(_instance.isValid() != RESULT_NOTHING)
			{
				NEExportable::ModuleHeader supers = SuperClass::getHeader();

				_instance.getName() = "ModuleSelectorTagger";
				_instance.getDeveloper() = "kniz";
				_instance.setRevision(1);
				_instance.getReleaseDate() = "2015/01/02";
				_instance.getComment() =
					"참조한 Module 객체들의 특정 속성값들을 가져오거나(get) 할당할 수 있습니다(set).\n"
					"\tTargets:\t참조할 객체들\n"
					"\tModule Codes:Module 탐색시 사용하게될 Codes\n" +
					supers.getComment();
				//"주어진 객체들의 다음과 같은 속성들에 대해서 값을 가져오거나 할당 할 수 있습니다.\n"
				//"\tEnable:\t객체의 활성화 여부.\n"
				//"\tCodes:\t객체의 주어진 Code값들";					
				NETStringSet& args = _instance.getArgumentsComments();
				const NETStringSet& super_args = supers.getArgumentsComments();

				args.create(super_args.getLength() + 2);
				args.push("Targets\n속성을 가져오거나 할당하게될 Module 들입니다.");
				args.push("Module Codes\nModule 탐색시 사용하게될 Codes 입니다.");
				args.push(super_args);
			}

			return _instance;
		}
	};
}