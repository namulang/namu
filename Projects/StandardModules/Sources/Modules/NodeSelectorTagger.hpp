#pragma once

#include "../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL NodeSelectorTagger : public NEModule
	{
	public:
		typedef NodeSelectorTagger ThisClass;
		typedef NEModule SuperClass;

	public:
		NETArgument<NEKeySelector>	arg_targets;
		NETArgumnet<NEIntKey>		arg_manager_type;
		NETArgument<NECodeSetKey>	arg_codes;
		NETArgument<NEIntKey>		arg_countlimit;
		NETArgument<NEBooleanKey>	arg_use_and_operation;
		NETArgument<NEBooleanKey>	arg_use_auto_binding;
		NETArgument<NEIntKey>		arg_initializer_count;

	protected:
		virtual type_result _onFetchModule()
		{
			arg_manager_type.setEnable(false);
			arg_manager_type.setPurposeLimitation(NEArgumentBase::READ_BY_OR_WRITTEN);
			arg_codes.setEnable(false);
			arg_codes.setPurposeLimitation(NEArgumentBase::READ_BY_OR_WRITTEN);
			arg_countlimit.setEnable(false);
			arg_countlimit.setPurposeLimitation(NEArgumentBase::READ_BY_OR_WRITTEN);
			arg_use_and_operation.setEnable(false);
			arg_use_and_operation.setPurposeLimitation(NEArgumentBase::READ_BY_OR_WRITTEN);
			arg_use_auto_binding.setEnable(false);
			arg_use_auto_binding.setPurposeLimitation(NEArgumentBase::READ_BY_OR_WRITTEN);
			arg_initializer_count.setEnable(false);
			arg_initializer_count.setPurposeLimitation(NEArgumentBase::READ_BY);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_targets);
			tray.push(arg_manager_type);
			tray.push(arg_codes);
			tray.push(arg_countlimit);
			tray.push(arg_use_and_operation);
			tray.push(arg_use_auto_binding);
			tray.push(arg_initializer_count);

			return RESULT_SUCCESS;
		}
		type_result _passPipes(NENodeSelector& n)
		{
			type_result result = RESULT_SUCCESS;

			if(arg_manager_type.isEnable())
			{
				if (arg_manager_type.getPurpose() == NEArgumentBase::READ_BY)
					result |= n.setManager(arg_manager_type.getValue());
				else
					result |= arg_manager_type.setValue(n.getManagerType());
			}
			if(arg_codes.isEnable())
			{
				const NECodeSet& codes = arg_codes.getValue();

				if (arg_codes.getPurpose() == NEArgumentBase::READ_BY)
					result |= n.setCodes(codes);
				else
					result |= arg_codes.setValue(n.getCodes(codes.getCodeType()));
			}
			if(arg_countlimit.isEnable())
			{
				if (arg_countlimit.getPurpose() == NEArgumentBase::READ_BY)
					result |= n.setCountLimit(arg_countlimit.getValue());
				else
					result |= arg_countlimit.getValue(n.getCountLimit());
			}
			if(arg_use_and_operation.isEnable())
			{
				if (arg_use_and_operation.getPurpose() == NEArgumentBase::READ_BY)
					result |= n.setUsingAndOperation(arg_use_and_operation.getValue());
				else
					result |= arg_use_and_operation.setValue(n.isUsingAndOperation());
			}
			if(arg_use_auto_binding.isEnable())
			{
				if (arg_use_auto_binding.getPurpose() == NEArgumentBase::READ_BY)
					result |= n.isUsingAutoBinding() = arg_use_auto_binding.getValue());
				else
					result |= arg_use_auto_binding.setValue(n.isUsingAutoBinding());
			}
			type_int initializer_count = arg_initializer_count.getValue();
			if (initializer_count != 0)
			{
				result |= n.initializeReferingPoint();

				if(initializer_count > 0)
					initializer_count--;
			}

			return result;
		}
		virtual type_result _onExecute()
		{
			type_result result = RESULT_SUCCESS;
			NEKeySelector& ks = arg_targets.getValue();
			while (NEKey* k = &ks.getKey())
				if (k->isSubClassOf(NEType::NENODE_SELECTOR))
					result |= _passPipes(static_cast<NENodeSelector&>(*k));				

			return result;
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;

			if (_instance.isValid() != RESULT_NOTHING)
			{
				_instance.getName() = "NamedUnitTagger";
				_instance.getDeveloper() = "kniz";
				_instance.setRevision(1);
				_instance.getReleaseDate() = "2015/01/02";
				_instance.getComment() =
					"\tEnable:\t객체의 활성화 여부.\n"
					"\tCodes:\t객체의 주어진 Code값들";
				NETStringSet& args = _instance.getArgumentsComments();
				args.create(2);
				args.push("Enable 속성\n 활성화 여부입니다. INPUT, OUTPUT 여부에 따라서 값을 가져오거나 할당합니다.");
				args.push("Codes 속성\nSCRIPT, NAME, GROUP과 같은 객체의 코드 값입니다.");
			}

			return _instance;
		}
	};
}