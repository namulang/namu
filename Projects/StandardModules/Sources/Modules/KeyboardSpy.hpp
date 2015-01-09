#pragma once

#include "../Includes/Includes.hpp"
#include <Windows.h>

namespace NE
{
	class NE_DLL KeyboardSpy : public NEModule
	{
	public:
		typedef KeyboardSpy ThisClass;
		typedef NEModule SuperClass;

	public:
		class VKey : public NETArgument<NETStringKey>
		{
		public:
			typedef NETArgument<NETStringKey> SuperClass; 

			virtual type_result setValue(const NETString& source)
			{
				type_result result = SuperClass::setValue(source);
				_key_code = getTransitionTable().find(source);
				if(_key_code < 0)
					return KERNAL_ERROR(" : sample = %s, n = %d", source.toCharPointer(), _key_code);

				return result;
			}
			virtual NEObject& clone() const
			{
				return *(new VKey(*this));
			}
			virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
			{
				SuperClass::serialize(saver);

				return saver << _key_code;
			}

			virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
			{
				SuperClass::serialize(loader);

				return loader >> _key_code;
			}

		public:
			type_int getKeyCode() const
			{
				return _key_code;
			}

		private:
			type_int _key_code;

		public:
			static const NETStringSet& getTransitionTable()
			{
				static NETStringSet table(256);
				if (table.getLength() < 250)
				{
					table.push(_T("VK_NULL"));
					table.push(_T("VK_LBUTTON"));
					table.push(_T("VK_RBUTTON"));
					table.push(_T("VK_CANCEL"));
					table.push(_T("VK_MBUTTON"));
					table.push(_T("VK_XBUTTON1"));
					table.push(_T("VK_XBUTTON2"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_BACK"));
					table.push(_T("VK_TAB"));
					table.push(_T("VK_RESERVED"));
					table.push(_T("VK_RESERVED"));
					table.push(_T("VK_CLEAR"));
					table.push(_T("VK_RETURN"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_SHIFT"));
					table.push(_T("VK_CONTROL"));
					table.push(_T("VK_MENU"));
					table.push(_T("VK_PAUSE"));
					table.push(_T("VK_CAPITAL"));
					table.push(_T("VK_HANGEUL"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_JUNJA"));
					table.push(_T("VK_FINAL"));
					table.push(_T("VK_HANJA"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_ESCAPE"));
					table.push(_T("VK_CONVERT"));
					table.push(_T("VK_NONCONVERT"));
					table.push(_T("VK_ACCEPT"));
					table.push(_T("VK_MODECHANGE"));
					table.push(_T("VK_SPACE"));
					table.push(_T("VK_PRIOR"));
					table.push(_T("VK_NEXT"));
					table.push(_T("VK_END"));
					table.push(_T("VK_HOME"));
					table.push(_T("VK_LEFT"));
					table.push(_T("VK_UP"));
					table.push(_T("VK_RIGHT"));
					table.push(_T("VK_DOWN"));
					table.push(_T("VK_SELECT"));
					table.push(_T("VK_PRINT"));
					table.push(_T("VK_EXECUTE"));
					table.push(_T("VK_SNAPSHOT"));
					table.push(_T("VK_INSERT"));
					table.push(_T("VK_DELETE"));
					table.push(_T("VK_HELP"));
					table.push(_T("VK_0"));
					table.push(_T("VK_1"));
					table.push(_T("VK_2"));
					table.push(_T("VK_3"));
					table.push(_T("VK_4"));
					table.push(_T("VK_5"));
					table.push(_T("VK_6"));
					table.push(_T("VK_7"));
					table.push(_T("VK_8"));
					table.push(_T("VK_9"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_A"));
					table.push(_T("VK_B"));
					table.push(_T("VK_C"));
					table.push(_T("VK_D"));
					table.push(_T("VK_E"));
					table.push(_T("VK_F"));
					table.push(_T("VK_G"));
					table.push(_T("VK_H"));
					table.push(_T("VK_I"));
					table.push(_T("VK_J"));
					table.push(_T("VK_K"));
					table.push(_T("VK_L"));
					table.push(_T("VK_M"));
					table.push(_T("VK_N"));
					table.push(_T("VK_O"));
					table.push(_T("VK_P"));
					table.push(_T("VK_Q"));
					table.push(_T("VK_R"));
					table.push(_T("VK_S"));
					table.push(_T("VK_T"));
					table.push(_T("VK_U"));
					table.push(_T("VK_V"));
					table.push(_T("VK_W"));
					table.push(_T("VK_X"));
					table.push(_T("VK_Y"));
					table.push(_T("VK_Z"));
					table.push(_T("VK_LWIN"));
					table.push(_T("VK_RWIN"));
					table.push(_T("VK_APPS"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_SLEEP"));
					table.push(_T("VK_NUMPAD0"));
					table.push(_T("VK_NUMPAD1"));
					table.push(_T("VK_NUMPAD2"));
					table.push(_T("VK_NUMPAD3"));
					table.push(_T("VK_NUMPAD4"));
					table.push(_T("VK_NUMPAD5"));
					table.push(_T("VK_NUMPAD6"));
					table.push(_T("VK_NUMPAD7"));
					table.push(_T("VK_NUMPAD8"));
					table.push(_T("VK_NUMPAD9"));
					table.push(_T("VK_MULTIPLY"));
					table.push(_T("VK_ADD"));
					table.push(_T("VK_SEPARATOR"));
					table.push(_T("VK_SUBTRACT"));
					table.push(_T("VK_DECIMAL"));
					table.push(_T("VK_DIVIDE"));
					table.push(_T("VK_F1"));
					table.push(_T("VK_F2"));
					table.push(_T("VK_F3"));
					table.push(_T("VK_F4"));
					table.push(_T("VK_F5"));
					table.push(_T("VK_F6"));
					table.push(_T("VK_F7"));
					table.push(_T("VK_F8"));
					table.push(_T("VK_F9"));
					table.push(_T("VK_F10"));
					table.push(_T("VK_F11"));
					table.push(_T("VK_F12"));
					table.push(_T("VK_F13"));
					table.push(_T("VK_F14"));
					table.push(_T("VK_F15"));
					table.push(_T("VK_F16"));
					table.push(_T("VK_F17"));
					table.push(_T("VK_F18"));
					table.push(_T("VK_F19"));
					table.push(_T("VK_F20"));
					table.push(_T("VK_F21"));
					table.push(_T("VK_F22"));
					table.push(_T("VK_F23"));
					table.push(_T("VK_F24"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_NUMLOCK"));
					table.push(_T("VK_SCROLL"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_LSHIFT"));
					table.push(_T("VK_RSHIFT"));
					table.push(_T("VK_LCONTROL"));
					table.push(_T("VK_RCONTROL"));
					table.push(_T("VK_LMENU"));
					table.push(_T("VK_RMENU"));
					table.push(_T("VK_BROWSER_BACK"));
					table.push(_T("VK_BROWSER_FORWARD"));
					table.push(_T("VK_BROWSER_REFRESH"));
					table.push(_T("VK_BROWSER_STOP"));
					table.push(_T("VK_BROWSER_SEARCH"));
					table.push(_T("VK_BROWSER_FAVORITES"));
					table.push(_T("VK_BROWSER_HOME"));
					table.push(_T("VK_VOLUME_MUTE"));
					table.push(_T("VK_VOLUME_DOWN"));
					table.push(_T("VK_VOLUME_UP"));
					table.push(_T("VK_MEDIA_NEXT_TRACK"));
					table.push(_T("VK_MEDIA_PREV_TRACK"));
					table.push(_T("VK_MEDIA_STOP"));
					table.push(_T("VK_MEDIA_PLAY_PAUSE"));
					table.push(_T("VK_LAUNCH_MAIL"));
					table.push(_T("VK_LAUNCH_MEDIA_SELECT"));
					table.push(_T("VK_LAUNCH_APP1"));
					table.push(_T("VK_LAUNCH_APP2"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_OEM_1"));
					table.push(_T("VK_OEM_PLUS"));
					table.push(_T("VK_OEM_COMMA"));
					table.push(_T("VK_OEM_MINUS"));
					table.push(_T("VK_OEM_PERIOD"));
					table.push(_T("VK_OEM_2"));
					table.push(_T("VK_OEM_3"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_OEM_4"));
					table.push(_T("VK_OEM_5"));
					table.push(_T("VK_OEM_6"));
					table.push(_T("VK_OEM_7"));
					table.push(_T("VK_OEM_8"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_OEM_102"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_PROCESSKEY"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_PACKET"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_UNDEFINED"));
					table.push(_T("VK_ATTN"));
					table.push(_T("VK_CRSEL"));
					table.push(_T("VK_EXSEL"));
					table.push(_T("VK_EREOF"));
					table.push(_T("VK_PLAY"));
					table.push(_T("VK_ZOOM"));
					table.push(_T("VK_NONAME"));
					table.push(_T("VK_PA1"));
					table.push(_T("VK_OEM_CLEAR"));
					table.push(_T("VK_UNDEFINED"));
				}

				return table;				
			}
		};
		VKey arg_vkey;
		NETArgument<NEIntKey> arg_state;


	protected:
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_vkey);
			tray.push(arg_state);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchModule()
		{
			arg_vkey.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_state.setPurposeLimitation(NEArgumentBase::WRITTEN);

			return RESULT_SUCCESS;
		}

	protected:
		virtual type_result _onExecute()
		{
			type_int real_code = arg_vkey.getKeyCode();

			int state = GetAsyncKeyState(real_code);
			if (state & 0x8000)
			{
				if (state & 0x0001)
					arg_state.setValue(2);	//	PRESSING
				else
					arg_state.setValue(1);	//	DOWN
			}
			else
			{
				if (state & 0x0001)
					arg_state.setValue(-1);	//	UP
				else
					arg_state.setValue(0);	//	NOT INPUTED
			}

			return arg_state.getValue() > 0 ? RESULT_TRUE : RESULT_FALSE;
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;

			if (_instance.isValid() != RESULT_NOTHING)
			{
				_instance.getName() = "KeyboardSpy";
				_instance.getDeveloper() = "kniz";
				_instance.setRevision(1);
				_instance.getReleaseDate() = "2015/01/00";
				_instance.getComment() =
					"지정한 마우스 버튼 및 키보드의 키의 상태(눌렸는지, 눌렀다 떼는 중인지 등)를 State에 저장하며,"
					"그 상태에 맞게 TRUE 혹은 FALSE를 반환합니다.\n"
					"VKey Argument : 검사할 마우스버튼 혹은 키보드 키를 적어줍니다. VK_A, VK_CONTROL, VK_LBUTTON등으로 적어주며,"
					"해당 리스트는 Virtual-Key Codes(http://msdn.microsoft.com/ko-kr/library/windows/desktop/dd375731(v=vs.85).aspx)"
					"를 참고하세요.\n"
					"State : VKey의 상태를 조사하여 Int로 저장합니다. 상태는 총 4가지로 다음과 같습니다.\n"
					"\t-1 : 눌렀다가 막 뗌(= UP)\n"
					"\t0  : 입력 없음\n"
					"\t1  : 막 누르는 찰나(=DOWN)\n"
					"\t2  : 누르는 중\n"
					"따라서 State가 양수이면 누름, 음수이면 누르지 않음으로 판단 할 수도 있으며, State 값이 누름이면 실행 결과로 TRUE를 반환합니다."
					"누르지 않음이면 FALSE를 반환합니다.";

				NETStringSet& args = _instance.getArgumentsComments();
				args.create(2);
				args.push("Virtual Key Code\n 눌렀는지 상태를 조사할 버튼 혹은 키 입니다.\nVK_A, VK_MBUTTON, VK_DOWN 식으로 입력합니다.\n다른 키는 MSDN의 Virtual Key Codes(http://msdn.microsoft.com/ko-kr/library/windows/desktop/dd375731(v=vs.85).aspx)를 참고하세요.");
				args.push("State\nVirtual Key Code의 입력 상태가 저장됩니다.\n-1 : 눌렀다가 뗐음\t\t0: 입력 없음\n1: 막 눌렀음(=DOWN)\t\t2: 누르는 중(PRESSING)");
			}

			return _instance;
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
	};
}