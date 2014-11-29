#include "WNDDomainManipulator.hpp"
#include "../WND/WND.hpp"
#include "define/define.hpp"

namespace NE
{
	type_result NE_DLL WNDDomainManipulator::_onExecute()
	{	
		NEModuleSelector& selector = arg_window_selector.getValue();

		while(true)
		{	
			WND& wnd = static_cast<WND&>(selector.getModule());
			if( ! &wnd)
				return RESULT_TYPE_ERROR;

			type_byte	hwnd_inserted_indicator	= arg_hwnd_inserted_after.getValue();
			type_int	x						= arg_x.getValue(),
						y						= arg_y.getValue(),
						width					= arg_width.getValue(),
						height					= arg_height.getValue();
			type_uint	flag					= arg_how_to_show_window.getValue();

			HWND hwnd_inserted_after = _convertHwndFromIndicator(hwnd_inserted_indicator);
			
			type_result result = wnd.changeDomain(hwnd_inserted_after, x, y, width, height, flag);
			if(NEResult::hasError(result))
			{
				ALERT_ERROR(" : wnd.changeDomain에서 에러 발생");

				return result | RESULT_TYPE_ERROR | ERROR_HAPPEN_WHILE_CHANGING_DOMAIN_OF_WND;
			}
		}		

		return RESULT_SUCCESS | RESULT_TRUE;
	}

	NEObject NE_DLL &WNDDomainManipulator::clone() const
	{
		return *(new WNDDomainManipulator(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &WNDDomainManipulator::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T( _NAME );
			_header.getDeveloper() = _T( _DEVELOPER );
			_header.setRevision(_REVISION);
			_header.getComment() = _T( _COMMENT );
			_header.getVersion()  = _T( _VERSION );
			_header.getReleaseDate() = _T( _DATE );
			_header.getModuleDependencies().create(_DEPENDENCIES_COUNT);
			_header.setMaxErrorCodeCount(WNDDomainManipulator::ERROR_CODE_END - 1);
			NETStringSet& args = _header.getArgumentsComments();
			args.create(_KEY_NUMBER);
			args.push(_KEY_COMMENT_1);
			args.push(_KEY_COMMENT_2);
			args.push(_KEY_COMMENT_3);
			args.push(_KEY_COMMENT_4);
			args.push(_KEY_COMMENT_5);
			args.push(_KEY_COMMENT_6);
			args.push(_KEY_COMMENT_7);
		}

		return _header;
	}

	LPCTSTR NE_DLL WNDDomainManipulator::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		case ERROR_HAPPEN_WHILE_CHANGING_DOMAIN_OF_WND:
			return _T("WND 객체의 DOMAIN를 바꾸는 동안 에러가 발생했다");

		case INVALID_HWND_INSERTED_INDICATOR:
			return _T("INVALID_HWND_INSERTED_INDICATOR가 잘못되었다");

		default:
			return _T("알수 없는 에러");
		}
	}	

	HWND WNDDomainManipulator::_convertHwndFromIndicator(type_byte indicator)
	{
		HWND hwnd_inserted_after = NULL;
		switch(indicator)
		{
		case 0:		hwnd_inserted_after = HWND_TOP;			break;
		case 1:		hwnd_inserted_after = HWND_BOTTOM;		break;
		case -1:	hwnd_inserted_after = HWND_TOPMOST;		break;
		case -2:	hwnd_inserted_after = HWND_NOTOPMOST;	break;
		default:
			ALERT_ERROR(" : 잘못된 hwnd_inserted_indicator 값\n0으로 고정함")
		}

		return hwnd_inserted_after;
	}

	type_result WNDDomainManipulator::_onFetchArguments(NEArgumentList& tray)
	{
		tray.push(arg_window_selector);

		SuperClass::_onFetchArguments(tray);
		
		return tray.push(arg_hwnd_inserted_after);
	}
}