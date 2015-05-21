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
		friend class VKey;

		class VKey : public NETArgument<NETStringKey>
		{
		public:
			typedef NETArgument<NETStringKey> SuperClass; 

			VKey(KeyboardSpy& owner)
				: _key_code(-1), _owner(owner)
			{

			}

			VKey(const VKey& rhs, KeyboardSpy& owner)
				: SuperClass(rhs), _key_code(-1), _owner(owner)
			{

			}

			virtual type_result setValue(const NETString& source)
			{
				type_result result = SuperClass::setValue(source);				

				_redefine(source);
				_owner.is_key_pressed_before = false;

				return result;
			}
			virtual NEObject& clone() const
			{
				return *(new VKey(*this, _owner));
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
			type_int getKeyCode()
			{
				const NETStringSet& table = getTransitionTable();
				const NETString& source = getValue();
				if(	_key_code == -1							||
					_key_code > table.getLengthLastIndex()	||
					table[_key_code] != source				)
					_redefine(source);

				return _key_code;
			}

		private:
			void _redefine(const NETString& source)
			{
				_key_code = getTransitionTable().find(source);

				if (_key_code < 0)
					KERNAL_ERROR(" : sample = %s, n = %d", source.toCharPointer(), _key_code);
			}

		private:
			type_int _key_code;
			KeyboardSpy& _owner;

		public:
			static const NETStringSet& getTransitionTable()
			{
				static NETStringSet table(256);
				if (table.getLength() < 250)
				{
					table.push(_T("vk_null"));
					table.push(_T("vk_lbutton"));
					table.push(_T("vk_rbutton"));
					table.push(_T("vk_cancel"));
					table.push(_T("vk_mbutton"));
					table.push(_T("vk_xbutton1"));
					table.push(_T("vk_xbutton2"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_back"));
					table.push(_T("vk_tab"));
					table.push(_T("vk_reserved"));
					table.push(_T("vk_reserved"));
					table.push(_T("vk_clear"));
					table.push(_T("vk_return"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_shift"));
					table.push(_T("vk_control"));
					table.push(_T("vk_menu"));
					table.push(_T("vk_pause"));
					table.push(_T("vk_capital"));
					table.push(_T("vk_hangeul"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_junja"));
					table.push(_T("vk_final"));
					table.push(_T("vk_hanja"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_escape"));
					table.push(_T("vk_convert"));
					table.push(_T("vk_nonconvert"));
					table.push(_T("vk_accept"));
					table.push(_T("vk_modechange"));
					table.push(_T("vk_space"));
					table.push(_T("vk_prior"));
					table.push(_T("vk_next"));
					table.push(_T("vk_end"));
					table.push(_T("vk_home"));
					table.push(_T("vk_left"));
					table.push(_T("vk_up"));
					table.push(_T("vk_right"));
					table.push(_T("vk_down"));
					table.push(_T("vk_select"));
					table.push(_T("vk_print"));
					table.push(_T("vk_execute"));
					table.push(_T("vk_snapshot"));
					table.push(_T("vk_insert"));
					table.push(_T("vk_delete"));
					table.push(_T("vk_help"));
					table.push(_T("vk_0"));
					table.push(_T("vk_1"));
					table.push(_T("vk_2"));
					table.push(_T("vk_3"));
					table.push(_T("vk_4"));
					table.push(_T("vk_5"));
					table.push(_T("vk_6"));
					table.push(_T("vk_7"));
					table.push(_T("vk_8"));
					table.push(_T("vk_9"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_a"));
					table.push(_T("vk_b"));
					table.push(_T("vk_c"));
					table.push(_T("vk_d"));
					table.push(_T("vk_e"));
					table.push(_T("vk_f"));
					table.push(_T("vk_g"));
					table.push(_T("vk_h"));
					table.push(_T("vk_i"));
					table.push(_T("vk_j"));
					table.push(_T("vk_k"));
					table.push(_T("vk_l"));
					table.push(_T("vk_m"));
					table.push(_T("vk_n"));
					table.push(_T("vk_o"));
					table.push(_T("vk_p"));
					table.push(_T("vk_q"));
					table.push(_T("vk_r"));
					table.push(_T("vk_s"));
					table.push(_T("vk_t"));
					table.push(_T("vk_u"));
					table.push(_T("vk_v"));
					table.push(_T("vk_w"));
					table.push(_T("vk_x"));
					table.push(_T("vk_y"));
					table.push(_T("vk_z"));
					table.push(_T("vk_lwin"));
					table.push(_T("vk_rwin"));
					table.push(_T("vk_apps"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_sleep"));
					table.push(_T("vk_numpad0"));
					table.push(_T("vk_numpad1"));
					table.push(_T("vk_numpad2"));
					table.push(_T("vk_numpad3"));
					table.push(_T("vk_numpad4"));
					table.push(_T("vk_numpad5"));
					table.push(_T("vk_numpad6"));
					table.push(_T("vk_numpad7"));
					table.push(_T("vk_numpad8"));
					table.push(_T("vk_numpad9"));
					table.push(_T("vk_multiply"));
					table.push(_T("vk_add"));
					table.push(_T("vk_separator"));
					table.push(_T("vk_subtract"));
					table.push(_T("vk_decimal"));
					table.push(_T("vk_divide"));
					table.push(_T("vk_f1"));
					table.push(_T("vk_f2"));
					table.push(_T("vk_f3"));
					table.push(_T("vk_f4"));
					table.push(_T("vk_f5"));
					table.push(_T("vk_f6"));
					table.push(_T("vk_f7"));
					table.push(_T("vk_f8"));
					table.push(_T("vk_f9"));
					table.push(_T("vk_f10"));
					table.push(_T("vk_f11"));
					table.push(_T("vk_f12"));
					table.push(_T("vk_f13"));
					table.push(_T("vk_f14"));
					table.push(_T("vk_f15"));
					table.push(_T("vk_f16"));
					table.push(_T("vk_f17"));
					table.push(_T("vk_f18"));
					table.push(_T("vk_f19"));
					table.push(_T("vk_f20"));
					table.push(_T("vk_f21"));
					table.push(_T("vk_f22"));
					table.push(_T("vk_f23"));
					table.push(_T("vk_f24"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_numlock"));
					table.push(_T("vk_scroll"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_lshift"));
					table.push(_T("vk_rshift"));
					table.push(_T("vk_lcontrol"));
					table.push(_T("vk_rcontrol"));
					table.push(_T("vk_lmenu"));
					table.push(_T("vk_rmenu"));
					table.push(_T("vk_browser_back"));
					table.push(_T("vk_browser_forward"));
					table.push(_T("vk_browser_refresh"));
					table.push(_T("vk_browser_stop"));
					table.push(_T("vk_browser_search"));
					table.push(_T("vk_browser_favorites"));
					table.push(_T("vk_browser_home"));
					table.push(_T("vk_volume_mute"));
					table.push(_T("vk_volume_down"));
					table.push(_T("vk_volume_up"));
					table.push(_T("vk_media_next_track"));
					table.push(_T("vk_media_prev_track"));
					table.push(_T("vk_media_stop"));
					table.push(_T("vk_media_play_pause"));
					table.push(_T("vk_launch_mail"));
					table.push(_T("vk_launch_media_select"));
					table.push(_T("vk_launch_app1"));
					table.push(_T("vk_launch_app2"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_oem_1"));
					table.push(_T("vk_oem_plus"));
					table.push(_T("vk_oem_comma"));
					table.push(_T("vk_oem_minus"));
					table.push(_T("vk_oem_period"));
					table.push(_T("vk_oem_2"));
					table.push(_T("vk_oem_3"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_oem_4"));
					table.push(_T("vk_oem_5"));
					table.push(_T("vk_oem_6"));
					table.push(_T("vk_oem_7"));
					table.push(_T("vk_oem_8"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_oem_102"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_processkey"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_packet"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_undefined"));
					table.push(_T("vk_attn"));
					table.push(_T("vk_crsel"));
					table.push(_T("vk_exsel"));
					table.push(_T("vk_ereof"));
					table.push(_T("vk_play"));
					table.push(_T("vk_zoom"));
					table.push(_T("vk_noname"));
					table.push(_T("vk_pa1"));
					table.push(_T("vk_oem_clear"));
					table.push(_T("vk_undefined"));
				}

				return table;				
			}
		};

		KeyboardSpy() : NEModule(), arg_vkey(*this), is_key_pressed_before(false)
		{

		}
		KeyboardSpy(const KeyboardSpy& rhs)
			: NEModule(rhs), arg_vkey(rhs.arg_vkey, *this), arg_state(rhs.arg_state), is_key_pressed_before(rhs.is_key_pressed_before)
		{

		}

		VKey arg_vkey;
		NETArgument<NEIntKey> arg_state;
		type_bool is_key_pressed_before;


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
			type_int	real_code = arg_vkey.getKeyCode();
			type_bool	key_pressed = (GetAsyncKeyState(real_code) & 0x8000);

			if (key_pressed)
				if (is_key_pressed_before)
					arg_state.setValue(1);	//	누르는 중	PRESSING
				else
					arg_state.setValue(2);	//	막 누름		DOWN
			else
				if (is_key_pressed_before)
					arg_state.setValue(-1);	//	막 뗌		UP
				else
					arg_state.setValue(0);

			is_key_pressed_before = key_pressed;
			return key_pressed ? RESULT_TRUE : RESULT_FALSE;
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
					"\t-1  : 키를 막 뗌(= UP)\n"
					"\t0  : 입력 없음\n"
					"\t1  : 누르는 중(= PRESSING)\n"
					"\t2  : 막 누르는 찰나(= DOWN)\n"
					"따라서 State가 양수이면 누름, 음수이면 누르지 않음으로 판단 할 수도 있으며, State 값이 누름이면 실행 결과로 TRUE를 반환합니다."
					"누르지 않음이면 FALSE를 반환합니다.";

				NETStringSet& args = _instance.getArgumentsComments();
				args.create(2);
				args.push("Virtual Key Code\n 눌렀는지 상태를 조사할 버튼 혹은 키 입니다.\nVK_A, VK_MBUTTON, VK_DOWN 식으로 입력합니다.\n다른 키는 MSDN의 Virtual Key Codes(http://msdn.microsoft.com/ko-kr/library/windows/desktop/dd375731(v=vs.85).aspx)를 참고하세요.");
				args.push("State\nVirtual Key Code의 입력 상태가 저장됩니다.\n-1 : 눌렀다가 뗐음(UP)\t\t0: 입력 없음\n1: 누르는 중(PRESSING)\t\t2: 막 눌렀음(=DOWN)");
			}

			return _instance;
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}

	private:

	};
}
