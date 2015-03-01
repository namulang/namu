#pragma once

#include "../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL ArgumentTagger : public NEModule
	{
	public:
		typedef ArgumentTagger ThisClass;
		typedef NEModule SuperClass;

	public:
		NETArgument<NEModuleSelector>	arg_module;
		NETArgument<NEIntSetKey>		arg_args_index;
		NETArgument<NEIntKey>			arg_purpose;
		NETArgument<NETStringKey>		arg_keyname;

	protected:
		virtual type_result _onFetchModule()
		{
			arg_args_index.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_purpose.setEnable(false);
			arg_purpose.setPurposeLimitation(NEArgumentBase::READ_OR_WRITTEN);
			arg_keyname.setEnable(false);
			arg_keyname.setPurposeLimitation(NEArgumentBase::READ_OR_WRITTEN);			

			return RESULT_SUCCESS;
		}
		virtual type_result _onExecute()
		{
			NEModuleSelector& ms = arg_module.getValue();
			type_result result = RESULT_SUCCESS;

			while(NEModule* m = &ms.getModule())
			{
				NEArgumentSet& args = m->getArguments();
				const NEIntSet& is = arg_args_index.getValue();
				for (int n = 0; n < is.getLength(); n++)
				{
					NEArgumentBase& arg = args[is[n]];
					if( ! &arg)
					{
						ALERT_WARNING(" : ");
						continue;
					}

					result |= _passPipes(arg);
				}
			}

			return result;
		}
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_module);
			tray.push(arg_args_index);
			tray.push(arg_purpose);
			tray.push(arg_keyname);

			return RESULT_SUCCESS;
		}
		type_result _passPipes(NEArgumentBase& arg)
		{
			type_result result = RESULT_SUCCESS;

			if(arg_purpose.isEnable())
			{
				if(arg_purpose.getPurpose() == NEArgumentBase::READ_BY)
					result |= arg.setPurpose(NEArgumentBase::Purpose(arg_purpose.getValue()));
				else
					result |= arg_purpose.setValue(arg.getPurpose());
			}
			if(arg_keyname.isEnable())
			{
				if(arg_keyname.getPurpose() == NEArgumentBase::READ_BY)
					result |= arg.setKeyName(arg_keyname.getValue());
				else
					result |= arg_keyname.setValue(arg.getKeyName());
			}			

			return result;
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;

			if (_instance.isValid() != RESULT_NOTHING)
			{
				_instance.getName() = "ArgumentTagger";
				_instance.getDeveloper() = "kniz";
				_instance.setRevision(1);
				_instance.getReleaseDate() = "2015/01/05";
				_instance.getComment() =
					"Argument의 속성들을 가져오거나, 변경할 수 있습니다.\n"
					"ModuleSelector로 변경하길 원하는 Argument를 소유한 Module을 가리키고,\n"
					"Argument Indexes로 해당 Module의 Argument Index를 지정하면 됩니다. 복수개의 Argument를 선택할 수 있습니다.\n"
					"Argument의 속성은 다음과 같습니다.\n"
					"\tPurpose:\tArgument의 사용 목적입니다.\n"
					"\tKeyName:\tArgument가 속한 Node의 KeySet 중에서, 어떤 키와 바인딩 되는지 결정하는 값입니다.";

				NETStringSet& args = _instance.getArgumentsComments();
				args.create(4);
				args.push("Target Modules\n변경하고픈 Argument가 속한 모듈을 가리킵니다.");
				args.push("Arugment Index\nTarget Module의 몇번째 Argument를 Tagging 할 것인지 지정합니다. 복수개가 될 수 있습니다.");
				args.push("Argument의 Purpose 값\nInput을 하면 이 값을 읽ㅇ서 Target의 Index에 해당하는 Argument에 넣습니다.\nOutput을 하면 Target's Argument에서 값을 가져와 여기에 넣습니다.");
				args.push("Argument Name");
			}

			return _instance;
		}

		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
	};
}