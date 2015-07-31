#pragma once

#include "../Includes/Includes.hpp"
#include <mmstream.h>
#pragma comment(lib, "winmm.lib")

namespace NE
{
	class NE_DLL Timer : public NEModule
	{
	public:
		typedef Timer ThisClass;
		typedef NEModule SuperClass;

	public:
		NETArgument<NEIntKey> arg_term_ms;

	protected:
		virtual type_result _onFetchModule()
		{
			timeBeginPeriod(1);
			_before = -1;
			arg_term_ms.setPurposeLimitation(NEArgumentBase::READ_OR_WRITTEN);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_term_ms);

			return RESULT_SUCCESS;
		}

	protected:
		virtual type_result _onExecute()
		{
			type_uint new_evaluted = timeGetTime();
			if(arg_term_ms.getPurpose() == NEArgumentBase::WRITTEN)
				return arg_term_ms.setValue(new_evaluted);

			if(_before < 0)
				_before = new_evaluted;

			type_int	term = new_evaluted - _before,
				arg_term = arg_term_ms.getValue();

			if (term > arg_term)
			{
				_before += arg_term;
				return RESULT_TRUE;
			}

			return RESULT_FALSE;
		}

	public:
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
		{
			NEModule::serialize(saver);

			return saver << _before;
		}
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
		{
			NEModule::serialize(loader);

			return loader >> _before;
		}
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;

			if (_instance.isValid() != RESULT_NOTHING)
			{
				_instance.getName() = "Timer";
				_instance.getDeveloper() = "kniz";
				_instance.setRevision(1);
				_instance.getReleaseDate() = "2013-10-15";
				_instance.getComment() =
					"Term인자를 Write, Read로 하냐에 따라서 동작이 틀려집니다.\n"
					"\tREAD로 할때, 주어진 Term(milli second)마다 TRUE를 반환합니다.\n"
					"\tWRITE로 할때, 현재 시간을 1970년 기준으로 milli second로 반환합니다.";
				NETStringSet& args = _instance.getArgumentsComments();
				args.create(1);
				args.push("Term\nREAD시, 이 시간이 지날때마다 Module 실행결과로 TRUE를 반환합니다.\nWRITE시, 현재의 시간을 ms로 반환합니다.\n단위는 밀리세컨드(0.001초) 이기에, 1000을 입력하면 1초가 됩니다.");
			}

			return _instance;
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}

	private:
		type_int _before;
	};
}