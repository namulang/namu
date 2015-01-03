#pragma once

#include "../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL NamedUnitTagger : public NEModule
	{
	public:
		typedef NamedUnitTagger ThisClass;
		typedef NEModule SuperClass;

	public:
		NETArgument<NEBooleanKey>	arg_enable;
		NETArgument<NECodeSetKey>	arg_codes;

	protected:
		virtual type_result _onFetchModule()
		{
			arg_enable.setPurposeLimitation(NEArgumentBase::READ_OR_WRITTEN);
			arg_enable.setEnable(false);
			arg_codes.setPurposeLimitation(NEArgumentBase::READ_OR_WRITTEN);
			arg_codes.setEnable(false);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_enable);
			tray.push(arg_codes);

			return RESULT_SUCCESS;
		}

	protected:
		type_result _onExecute(NENamedUnit& target)
		{
			if(arg_enable.isEnable())
			{
				if(arg_enable.getPurpose() == NEArgumentBase::READ_BY)
					target.setEnable(arg_enable.getValue());
				else
					arg_enable.setValue(target.isEnable());
			}
			if(arg_codes.isEnable())
			{
				const NECodeSet& codes = arg_codes.getValue();

				if (arg_codes.getPurpose() == NEArgumentBase::READ_BY)
					target.setCodes(codes);
				else
					arg_codes.setValue(target.getCodes(codes.getCodeType()));
			}	

			return RESULT_SUCCESS;
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