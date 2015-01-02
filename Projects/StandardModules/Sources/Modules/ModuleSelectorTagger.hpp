#pragma once

#include "NodeSelectorTagger.hpp"

namespace NE
{
	class NE_DLL ModuleSelectorTagger : public NodeSelectorTagger
	{
	public:
		typedef ModuleSelectorTagger ThisClass;
		typedef NodeSelectorTagger SuperClass;

	public:
		NETArgument<NECodeSetKey>	arg_module_codes;

	protected:
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			SuperClass::_onFetchArguments(tray);

			tray.push(arg_module_codes);
			tray.push(arg_use_module_auto_binding);

			return RESULT_SUCCESS;
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
					result |= m.setModuleCodes(codes);
				else
					result |= arg_module_codes.setValue(n.getModuleCodes(codes.getCodeType()));
			}			

			return result;
		}
		virtual type_result _onExecute()
		{
			type_result result = RESULT_SUCCESS;
			NEKeySelector& ks = arg_targets.getValue();
			while(NEKey* k = &ks.getKey())
			{
				if (k->isSubClassOf(NEType::NENODE_SELECTOR))
					result |= _passPipes(static_cast<NENodeSelector&>(*k));
				if (k->isSubClassOf(NEType::NEMODULE_SELECTOR))
					result |= _passPipes(static_cast<NEModuleSelector&>(*k));
			}			

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

				_instance.getName() = "ModuleSelectorTagger";
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
				NETStringSet args = supers.getArgumentsComments();
				args.resize(3);
				args.pushFront("Targets\n속성을 가져오거나 할당하게될 Module 들입니다.");
			}

			return _instance;
		}
	};
}