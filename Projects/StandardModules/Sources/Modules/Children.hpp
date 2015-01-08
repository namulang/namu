#pragma once

#include "../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL Children : public NEModule
	{
	public:
		typedef Children ThisClass;
		typedef NEModule SuperClass;

	public:
		NETArgument<NENodeCodeSetKey> arg_children;

	protected:
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_children);

			return RESULT_SUCCESS;
		}

	protected:
		virtual type_result _onExecute()
		{
			type_result result = RESULT_SUCCESS;
			if (arg_children.isEnable())
				result = arg_children.getValue().execute();

			return result;
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;

			if (_instance.isValid() != RESULT_NOTHING)
			{
				_instance.getName() = "Children";
				_instance.getDeveloper() = "kniz";
				_instance.setRevision(1);
				_instance.getReleaseDate() = "2013/01/18";
				_instance.getComment() = "주어진 자식 Node들을 가질 수 있게 합니다. execute시, NodeCodeSet을 Children으로써 실행합니다.";
				NETStringSet& args = _instance.getArgumentsComments();
				args.create(1);
				args.push("Children\n자식 Node들입니다.\ndisabled 되면 execute하지 않습니다.");
			}

			return _instance;
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
	};
}