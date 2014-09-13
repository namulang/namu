#include "MessageBox.hpp"
#include "../define/define.hpp"

namespace NE
{
	NE_DLL MessageBox::MessageBox()
		: NEModule()
	{
		
	}

	NE_DLL MessageBox::MessageBox(const MessageBox& source)
		: NEModule(source)
	{
		
	}

	NE_DLL MessageBox::~MessageBox()
	{

	}

	type_result NE_DLL MessageBox::_onExecute()
	{
		NETString	& message	= _message.getValue(),
					& title		= _title.getValue();
		
		::MessageBox(0, message.toCharPointer(), title.toCharPointer(), MB_OK);		
		
		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &MessageBox::clone() const
	{
		return *(new MessageBox(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &MessageBox::getHeader() const
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
			_header.setMaxErrorCodeCount(MessageBox::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL MessageBox::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		default:
			return _T("알수 없는 에러");
		}
	}

	type_result MessageBox::_onArgumentFetched(NEArgumentInterfaceList& tray)
	{
		tray.push(_message);
		tray.push(_title);

		return RESULT_SUCCESS;	
	}
}
