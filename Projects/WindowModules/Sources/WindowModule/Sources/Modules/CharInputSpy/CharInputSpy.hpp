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
		NEArgumentInterfaceTemplate<NEModuleSelector> arg_window_selector;
		NEArgumentInterfaceTemplate<NETStringKey> arg_sentence;
		NEArgumentInterfaceTemplate<NEUIntKey> arg_max_delay;

	protected:
		virtual type_result _onArgumentsFetched(NEArgumentInterfaceList& tray)
		{
			arg_window_selector.getValue().isUsingAutoBinding() = true;
			arg_max_delay.getDefault().getValue() = 500;
			tray.push(&arg_window_selector);
			tray.push(&arg_sentence);
			return tray.push(&arg_max_delay);
		}

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
				_header.getComment() = "0번 윈도우를 통해서 사용자가 입력받은 글자를 1번에 보관합니다.\n키가 입력될때에만 TRUE를 반환합니다.\nKeyboardSpy가 어떤 키를 눌렀는지를 판단한다면, CharInputSpy는 어떤 글자가 입력되었는지를 판단한다는 데서 차이가 있음을 염두해 두세요.\n\t0번키:	Spying 할 윈도우(\"자동 바인딩\"이 기본값)\n\t1번키: 입력된 글자";
				_header.getReleaseDate() = "2014-01-29";
			}

			return _header;
		}

	public:
		virtual type_result execute();

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