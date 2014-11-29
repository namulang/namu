#include "CharInputSpy.hpp"
#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")

namespace
{
	using namespace NE;
	void _pipeInputToString(NETArgument<NETStringKey>& arg, TCHAR inputed)
	{
		NETString casted = arg.getValue();

		switch(inputed)
		{
		case VK_BACK:	//	백스페이스
			//	문자 삭제하기:
			//		문자를 삭제하기 위해서는 단순히 pop이 아니라 널문자를 만들어 줘야 한다.
			if(casted.getLength() > 0) 
			{
				casted[casted.getLengthLastIndex()] = 0;
				casted.pop();
			}
			arg.setValue(casted);
			break;

		case VK_RETURN:
			if(casted.getLength() == casted.getSize())
				casted.resize(casted.getSize() * 2);
			
			casted += '\n';
			arg.setValue(casted);
			break;

		default:				
			if(casted.getLength() == casted.getSize())
				casted.resize(casted.getSize() * 2);

			casted += inputed;
			arg.setValue(casted);
		}
	}
}

namespace NE
{
	type_result CharInputSpy::_onExecute()
	{
		NEModuleSelector& sel = arg_window_selector.getValue();
		NEModule& m = sel.getModule();
		sel.initializeReferingPoint();
		if( ! &m)	return RESULT_FALSE;
		Window& win = _castToWindow(m);
		if( ! &win) return RESULT_FALSE;
	

		//	main:
		type_uint	end_time = _delay_start_time + arg_max_delay.getValue(),
					cur_time = timeGetTime();
		const MSG& msg = win.getMSG();
		if(	msg.message == WM_CHAR	&& 
			cur_time >= end_time	)
		{
			TCHAR inputed = (TCHAR) msg.wParam;

			_pipeInputToString(arg_sentence, inputed);

			_delay_start_time = cur_time;
			sel.initializeReferingPoint();
			return RESULT_TRUE;	
		}


		//	post:
		return RESULT_FALSE;
	}

	type_result CharInputSpy::_onFetchModule()
	{
		arg_window_selector.getValue().isUsingAutoBinding() = true;

		return arg_max_delay.setDefault(500);
	}

	type_result CharInputSpy::_onFetchArguments(NEArgumentList& tray)
	{
		tray.push(&arg_window_selector);
		tray.push(&arg_sentence);
		return tray.push(&arg_max_delay);
	}

	CharInputSpy::CharInputSpy()
		: WNDSpy(), _delay_start_time(0)
	{

	}

	const NEExportable::ModuleHeader& CharInputSpy::getHeader() const
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

	void CharInputSpy::release()
	{
		SuperClass::release();

		_delay_start_time = 0;
	}

	NEObject& CharInputSpy::clone() const
	{
		return *(new ThisClass(*this));
	}

}	