#pragma once

#include "../Includes/Includes.hpp"

namespace Console
{
	using namespace NE;

	class NE_DLL ConsoleCommand : public NEModule
	{
	public:
		typedef ConsoleCommand ThisClass;
		typedef NEModule SuperClass;

	public:
		NETArgument<NEStringKey>	arg_commandline;

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;

			if (_header.isValid() != RESULT_NOTHING)
			{
				_header.getName() = _T("ConsoleCommand");
				_header.getDeveloper() = _T("kniz");
				_header.setRevision(1);
				_header.getComment() =
					"콘솔명령어를 수행합니다.";
				_header.getVersion() = _T("0.0.1a");
				_header.getReleaseDate() = _T("2015-7-27");
				_header.getModuleDependencies().create(0);
				_header.setMaxErrorCodeCount(0);
				NETStringSet& args = _header.getArgumentsComments();
				args.create(3);
				args.push("Commandline\n수행할 콘솔 명령어\n");
			}

			return _header;
		}

	protected:
		virtual type_result _onExecute()
		{
			system(arg_commandline.getValue().toCharPointer());

			return RESULT_SUCCESS | RESULT_TRUE;
		}
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_commandline);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchModule()
		{
			arg_commandline.setPurposeLimitation(NEArgumentBase::READ_BY);

			return RESULT_SUCCESS;
		}

	public:
		virtual NEObject& clone() const
		{
			return *(new ConsoleCommand(*this));
		}
	};
}