#pragma once

#include "../WNDSpy.hpp"

namespace NE
{
	class NE_DLL MouseSpy : public WNDSpy
	{
	public:
		NETArgument<NEModuleSelector> arg_window_selector;
		NETArgument<NEIntKey> arg_notification_type;
		NETArgument<NEIntKey> arg_out_cursor_x;
		NETArgument<NEIntKey> arg_out_cursor_y;

	protected:
		virtual type_result _onFetchArguments(NEArgumentList& tray);
		virtual type_result _onFetchModule();
		virtual type_result _onExecute();

	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;

	public:
		virtual NEObject& clone() const;
	};
}