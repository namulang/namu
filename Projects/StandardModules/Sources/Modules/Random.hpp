#pragma once

#include "../Includes/Includes.hpp"
#include <cstdlib>
#include <ctime>

namespace NE
{
	class NE_DLL Random : public NEModule
	{
	public:
		typedef Random ThisClass;
		typedef NEModule SuperClass;

	public:
		NETArgument<NEFloatKey> arg_output;
		NETArgument<NEFloatKey>	arg_max;
		NETArgument<NEFloatKey>	arg_min;

	protected:
		virtual type_result _onFetchModule()
		{
			srand(static_cast<unsigned int>(time(0)));
			arg_output.setPurposeLimitation(NEArgumentBase::WRITTEN);
			arg_max.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_min.setPurposeLimitation(NEArgumentBase::READ_BY);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_output);
			tray.push(arg_max);
			tray.push(arg_min);

			return RESULT_SUCCESS;
		}

	protected:
		virtual type_result _onExecute()
		{
			//	이 방법은 Max나 Min이 음수일 경우도 동작한다
			type_float	max = arg_max.getValue(),
				min = arg_min.getValue(),
				delta = max - min,
				scale_factor = static_cast<float>(rand()) / RAND_MAX,
				answer = scale_factor * delta;

			arg_output.setValue(answer);

			return answer >= 0 ? RESULT_TRUE : RESULT_FALSE;
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;

			if (_instance.isValid() != RESULT_NOTHING)
			{
				_instance.getName() = "Random";
				_instance.getDeveloper() = "kniz";
				_instance.setRevision(1);
				_instance.getReleaseDate() = "2013-10-15";
				_instance.getComment() = 
					"주어진 두 실수 사이의 임의의 값을 생성하여 반환합니다.\n"
					"생성된 임의의 값이 음수일 경우 FALSE가, 0 또는 양수 일경우 TRUE를 Module 실행결과로 반환합니다.";
				NETStringSet& args = _instance.getArgumentsComments();
				args.create(3);
				args.push("Output\n임의의 값이 생성되어 여기에 저장됩니다.\n당연한 얘기지만, KeySelector나 IntKey를 넣으셔도 됩니다.");
				args.push("Max\n임의의 값이 가질 수 있는 최대값 입니다.");
				args.push("Min\n임의의 값이 가질 수 있는 최소값 입니다.");
			}

			return _instance;
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
	};
}