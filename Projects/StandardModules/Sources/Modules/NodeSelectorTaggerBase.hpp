#pragma once

#include "../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL NodeSelectorTaggerBase : public NEModule
	{
	public:
		typedef NodeSelectorTaggerBase ThisClass;
		typedef NEModule SuperClass;

	public:
		NETArgument<NEIntKey>		arg_manager_type;
		NETArgument<NECodeSetKey>	arg_codes;
		NETArgument<NEIntKey>		arg_countlimit;
		NETArgument<NEBooleanKey>	arg_use_and_operation;
		NETArgument<NEBooleanKey>	arg_use_auto_binding;
		NETArgument<NEIntKey>		arg_initializer_count;

	protected:
		virtual type_result _onFetchModule()
		{
			arg_manager_type.setEnable(false);
			arg_manager_type.setPurposeLimitation(NEArgumentBase::READ_OR_WRITTEN);
			arg_codes.setEnable(false);
			arg_codes.setPurposeLimitation(NEArgumentBase::READ_OR_WRITTEN);
			arg_countlimit.setEnable(false);
			arg_countlimit.setPurposeLimitation(NEArgumentBase::READ_OR_WRITTEN);
			arg_use_and_operation.setEnable(false);
			arg_use_and_operation.setPurposeLimitation(NEArgumentBase::READ_OR_WRITTEN);
			arg_use_auto_binding.setEnable(false);
			arg_use_auto_binding.setPurposeLimitation(NEArgumentBase::READ_OR_WRITTEN);
			arg_initializer_count.setEnable(false);			
			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
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
					result |= n.setManager(NEType::Type(arg_manager_type.getValue()));
				else
					result |= arg_manager_type.setValue(n.getManagerType());
			}
			if(arg_codes.isEnable())
			{
				const NECodeSet& codes = arg_codes.getValue();

				if (arg_codes.getPurpose() == NEArgumentBase::READ_BY)
					result |= n.setCodes(codes);
				else
					result |= arg_codes.setValue(n.getCodes());
			}
			if(arg_countlimit.isEnable())
			{
				if (arg_countlimit.getPurpose() == NEArgumentBase::READ_BY)
					n.setCountLimit(arg_countlimit.getValue());
				else
					result |= arg_countlimit.setValue(n.getCountLimit());
			}
			if(arg_use_and_operation.isEnable())
			{
				if (arg_use_and_operation.getPurpose() == NEArgumentBase::READ_BY)
					n.setUsingAndOperation(arg_use_and_operation.getValue());
				else
					result |= arg_use_and_operation.setValue(n.isUsingAndOperation());
			}			
			if(arg_use_auto_binding.isEnable())
			{
				if (arg_use_auto_binding.getPurpose() == NEArgumentBase::READ_BY)
					n.isUsingAutoBinding() = arg_use_auto_binding.getValue();
				else
					result |= arg_use_auto_binding.setValue(n.isUsingAutoBinding());
			}
			type_int initializer_count = arg_initializer_count.getValue();
			if (initializer_count != 0)
			{
				result |= n.initializeReferingPoint();

				if(initializer_count > 0)
					arg_initializer_count.getValueKey()--;
			}		

			return result;
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;

			if(_instance.isValid() != RESULT_NOTHING)
			{
				_instance.getName() = "NodeSelectorTaggerBase";
				_instance.getDeveloper() = "kniz";
				_instance.setRevision(1);
				_instance.getReleaseDate() = "2015/01/09";
				_instance.getComment() =
					"- Initializer Count는 지정된 숫자만큼 execute시마다 초기화 시킵니다."
					"-1이면, 숫자제한없이 execute 될때마다 항상 초기화 됩니다."
					"- ManagerType : Selector가 탐색할 Manager의 종류를 말합니다.\n"
					"- Node Codes : Node 탐색에 사용될 Code 입니다."
					"- CountLimit : Node 탐색에 한번에 최대 탐색할 갯수 입니다."
					"- Use AND Operation : 찾은 노드가 Node Codes들에 모두 해당되어야 하는지를 의미합니다.\n";

				NETStringSet& args = _instance.getArgumentsComments();
				args.create(6);
				args.push("ManagerType");
				args.push("Codes for Node Selector");
				args.push("CountLimit for Node Selector");
				args.push("UseAndOperation for Node Selector");
				args.push("UseAutoBinding for Node Selector");
				args.push("InitializerCount");
			}

			return _instance;
		}
	};
}