#pragma once

#include "../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL StringSpliter : public NEModule
	{
	public:
		typedef StringSpliter ThisClass;
		typedef NEModule SuperClass;

	public:
		NETArgument<NETStringKey>		arg_string;
		NETArgument<NETStringKey>		arg_delimiter;
		NETArgument<NETStringSetKey>	arg_splited;		

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;

			if (_header.isValid() != RESULT_NOTHING)
			{
				_header.getName() = _T("StringSpliter");
				_header.getDeveloper() = _T("kniz");
				_header.setRevision(1);
				_header.getComment() =
					"주어진 String을 Delimiter로 쪼갠 StringSet을 반환합니다.\n";
					"예)	String = \"hello world good!\",\n"
					"		Delimiter = \" \", 일때\n"
					"		StringSet = {\"hello\", \"world\", \"good!\"}";
				_header.getVersion() = _T("0.0.1a");
				_header.getReleaseDate() = _T("2015-7-17");
				_header.getModuleDependencies().create(0);
				_header.setMaxErrorCodeCount(0);
				NETStringSet& args = _header.getArgumentsComments();
				args.create(3);
				args.push("String\n연산이 될 문자열 입니다.\n");
				args.push("Delimiter\nString인자를 잘라낼 기준 문자열 입니다.\n");
				args.push("StringSet\n결과값이 들어갈 Key입니다.");
			}

			return _header;
		}

	protected:
		virtual type_result _onExecute()
		{
			arg_string.getValue().split(arg_delimiter.getValue(), arg_splited.getValue());			

			return RESULT_SUCCESS | RESULT_TRUE;
		}
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_string);
			tray.push(arg_delimiter);
			tray.push(arg_splited);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchModule()
		{
			arg_string.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_delimiter.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_splited.setPurposeLimitation(NEArgumentBase::WRITTEN);

			return RESULT_SUCCESS;
		}

	public:
		virtual NEObject& clone() const
		{
			return *(new StringSpliter(*this));
		}
	};
}