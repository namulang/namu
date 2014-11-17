#include "Window.hpp"
#include "define/define.hpp"

namespace NE
{
	NE_DLL Window::Window()
		: WND()
	{
		
	}

	NE_DLL Window::Window(const Window& source)
		: WND(source)
	{
		_assign(source);
	}

	NE_DLL Window::~Window()
	{
		_release();
	}

	/*
		initialize는 처음 인스턴스가 생성될때 호출된다.
		( * 즉, 모듈 매니져에서 처음으로 발생)

		그 이후로는 복사생성자 -> serialize(loader)만 호출되므로,
		intiailize에 기본값을 할당해놓으면 스크립트파일에서 값을 명시하지 않은 경우에
		자동으로 기본값이 놓여지게 될것이다.
	*/
	type_result NE_DLL Window::initialize()
	{
		//	pre:
		WND::initialize();

		_release();		
		_style = _DEFAULT_WINDOW_STYLE;
		
		return RESULT_SUCCESS;
	}

	type_result NE_DLL Window::execute()
	{	//	pre:
		//		윈도우가 생성되지 않았다면 윈도우를 생성한다.
		if( ! _hwnd)
			_initializeWindow();
		


		//	main:
		/*
			생성한 윈도우로부터 메세지를 하나 빼온다.
		*/
		memset(&_message, 0, sizeof(MSG));
		if( PeekMessage(&_message, NULL, 0U, 0U, PM_REMOVE) )
		{	
			static int count = 0;
			
			//	도착하면 메세지처리
			TranslateMessage(&_message);
			DispatchMessage(&_message);

			_storeMyMessageFromWinProc();
		}	



		//	post:
		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &Window::clone() const
	{
		return *(new Window(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &Window::getHeader() const
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
			_header.setMaxErrorCodeCount(Window::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL Window::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		case FAILED_TO_CREATE_WINDOW_CLASS:
			return _T("윈도우 클래스 생성 실패");

		case FAILED_TO_CREATE_WINDOW:
			return _T("윈도우 생성 실패");

		default:
			return _T("알수 없는 에러");
		}
	}

	/*
		윈도우 모듈은 복잡한 "저장/로드" 구조를 지녀야 한다.

		1. 이는 "로드를 했다고 하더라도" 윈도우가 이미 생성되버린다면, "스타일" 을 적용할수
		없으며.

		2. 윈도우가 생성되지 않은 상태에서 로드를 해버리고 바로 시스템을 재개한다면, "윈도
		우가 생성되지 않은 채로" 구동되기 때문이다.

		즉, 다음과 같은 처리를 해줘야한다.
			1. 윈도우가 생성되었는가?
				예		->	스타일은 이외의 데이터를 읽은 후, 변경을 가해준다.
				아니오	->	기존의 방식처럼 데이터를 읽어서 적용해준다.
	*/
	NEBinaryFileSaver NE_DLL &Window::serialize(NEBinaryFileSaver& saver) const
	{
		//	pre:
		WND::serialize(saver);

		if(_hwnd)
		{
			saver << (bool) true;
			TCHAR buffer[256] = {0, };
			GetWindowText(_hwnd, buffer, 256);
			NETString saved_title = buffer;

			saver << saved_title;
		}
		else
			saver << (bool) false;



		//	post:
		return saver << _style;
	}

	NEBinaryFileLoader NE_DLL &Window::serialize(NEBinaryFileLoader& loader)
	{
		WND::serialize(loader);

		//	main:		
		bool has_file_title_string_when_serialized = false;
		loader >> has_file_title_string_when_serialized;
		if(has_file_title_string_when_serialized)
			loader >> _saved_title;

		return loader >> _style;
	}

	const MSG NE_DLL &Window::getMSG() const
	{
		return _message;
	}

	const WNDCLASS NE_DLL &Window::getWndClass() const
	{
		return _class;
	}

	DWORD NE_DLL Window::getStyle() const
	{
		return _style;
	}

	void Window::_release()
	{
		memset((void*)&_message, 0, sizeof(_message));
		memset((void*)&_class, 0, sizeof(_message));
		_style = 0;
		_saved_title.release();
	}

	/*
		윈도우 생성이 아직 되지 않았다는 가정하에, 각 요소들을 assign 한다.
	*/
	const Window& Window::_assign(const Window& source)
	{
		if(this == &source) return *this;
		if(_hwnd)
		{
			ALERT_WARNING(" : 이미 윈도우가 생성되어 있어서 assign을 중지합니다.")

			return *this;
		}
		


		//	main:
		_style = source._style;
		_saved_title = source._saved_title;
		
		return *this;
	}

	type_result Window::_initializeWindow()
	{
		type_result result = _registerWindowClass();
		if(NEResult::hasError(result))
			ALERT_WARNING(" : 윈도우 클래스 등록 실패")

		result = _createWindow();
		if(NEResult::hasError(result))
		{
			ALERT_ERROR(" : 윈도우 생성 실패")

			return result | RESULT_TYPE_ERROR | FAILED_TO_CREATE_WINDOW;
		}

		_initializeTitle();
		ShowWindow(_hwnd, arg_how_to_show_window.getValue());
		UpdateWindow(_hwnd);

		return RESULT_SUCCESS;
	}

	type_result Window::_registerWindowClass()
	{
		HINSTANCE instance = GetModuleHandle(NULL);

		_class.cbClsExtra = 0;
		_class.cbWndExtra = 0;
		_class.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
		_class.hCursor = NULL;
		_class.hIcon = NULL;
		_class.hInstance = instance;
		_class.lpfnWndProc = WND::_wndProc;
		_class.lpszClassName = _T(_DEFAULT_WINDOW_CLASS_NAME);
		_class.lpszMenuName = NULL;
		_class.style = CS_HREDRAW | CS_VREDRAW;

		if( ! RegisterClass(&_class) )
			return RESULT_TYPE_ERROR;

		return RESULT_SUCCESS;
	}

	type_result Window::_createWindow()
	{
		HINSTANCE instance = GetModuleHandle(NULL);

		if(_hasSavedStatesAssigned())
			_hwnd = CreateWindow(_T(_DEFAULT_WINDOW_CLASS_NAME), 
						_saved_title.toCharPointer(), _style, 
						_saved_x, _saved_y, _saved_width, _saved_height, 
						NULL, (HMENU) NULL, instance, NULL);

		else
			_hwnd = CreateWindow(_T(_DEFAULT_WINDOW_CLASS_NAME), 
						arg_title.getValue().toCharPointer(), _style, 
						arg_x.getValue(), arg_y.getValue(), arg_width.getValue(), 
						arg_height.getValue(),
						NULL, (HMENU) NULL, instance, NULL);
		
		if( ! _hwnd)
			return RESULT_TYPE_ERROR;

		return RESULT_SUCCESS;
	}

	type_result Window::changeTitle(const NETString& title)
	{
		if( ! _hwnd)
		{
			ALERT_ERROR(" : 윈도우 핸들이 없다.")

			return RESULT_TYPE_ERROR;
		}
		if( ! &title)
		{
			ALERT_ERROR(" : 변경할 title이 없다.")

			return RESULT_TYPE_ERROR;
		}

		
		
		//	main:
		if( ! SetWindowText(_hwnd, title.toCharPointer()))	//	error = 0
			return RESULT_TYPE_ERROR;
		


		//	post:		
		return RESULT_SUCCESS;
	}

	void NE_DLL Window::release()
	{
		WND::release();

		return _release();
	}

	type_result Window::_initializeTitle()
	{
		if(_saved_title.getLength() > 0)
			return changeTitle(_saved_title);
		else
			return changeTitle(arg_title.getValue());
	}

	void Window::_storeMyMessageFromWinProc()
	{
		if(_message_from_wnd_proc.hwnd == _hwnd)
		{
			_message.hwnd = _message_from_wnd_proc.hwnd;
			_message.message = _message_from_wnd_proc.message;
			_message.wParam = _message_from_wnd_proc.wParam;
			_message.lParam = _message_from_wnd_proc.lParam;
		}
	}

	type_result Window::_onArgumentsFetched(NEArgumentInterfaceList& tray)
	{
		SuperClass::_onArgumentsFetched(tray);

		arg_title.getDefault() = "이름을 입력하세요.";
		return tray.push(arg_title);
	}

}