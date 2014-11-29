#pragma once

#include "../WNDSpy/WNDSpy.hpp"

namespace NE
{
	class NE_DLL CharInputSpy : public WNDSpy
	{
	public:
		typedef CharInputSpy ThisClass;
		typedef WNDSpy SuperClass;

	public:
		NEITArgument<NEModuleSelector> arg_window_selector;
		NEITArgument<NETStringKey> arg_sentence;
		NEITArgument<NEUIntKey> arg_max_delay;

	protected:
		virtual type_result _onFetchArguments(NEArgumentInterfaceList& tray) const
		{
			arg_window_selector.getValue().isUsingAutoBinding() = true;
			arg_max_delay.getDefault() = 500;
			tray.push(&arg_window_selector);
			tray.push(&arg_sentence);
			return tray.push(&arg_max_delay);
		}
		virtual type_result _onExecute();

	public:
		CharInputSpy()
			: WNDSpy(), _delay_start_time(0)
		{
			
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;

			if(_header.isValid() != RESULT_NOTHING)
			{
				_header.getName() = "CharInputSpy";
				_header.getDeveloper() = "kniz";
				_header.setRevision(1);
				_header.getComment() = "텍스트박스 등에 문자를 입력하면 TRUE가 반환됩니다.\nKeyboardSpy가 어떤 키를 눌렀는지를 판단한다면, CharInputSpy는 어떤 글자가 입력되었는지를 판단한다는 데서 차이가 있음을 염두해 두세요.";
				_header.getReleaseDate() = "2014-01-29";
				NETStringSet& args = _header.getArgumentsComments();
				args.create(3);
				args.push("문자 입력을 감시할 윈도우(Window)");
				args.push("[OUT] 입력한 문자를 이곳에 저장합니다.");
				args.push("이 값만큼 감시할때 딜레이를 줍니다.");
			}

			return _header;
		}

	public:
		virtual void release()
		{
			SuperClass::release();

			_delay_start_time = 0;
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
		/*
			왜 _delay_start_time은 serialize 하지 않는가:
				_delay_start_time은 프로그램이 개시후 얼마나 지났는가를 timeGetTime로부터의 
				값으로 저장한다. 그런데 timeGetTime은 우리가 setter할 수 없으므로,
				_delay_start_time을 저장 할 수 없다.
		*/
	private:
		int _delay_start_time;
	};
}