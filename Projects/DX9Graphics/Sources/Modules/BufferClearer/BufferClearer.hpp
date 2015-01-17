#pragma once

#include "../../Includes/Includes.hpp"

namespace DX9Graphics
{
	class NE_DLL BufferClearer : public NEModule
	{
		typedef BufferClearer ThisClass;
		typedef NEModule SuperClass;

	public:
		NETArgument<NEUByteKey>	arg_red;
		NETArgument<NEUByteKey> arg_green;
		NETArgument<NEUByteKey> arg_blue;
		NETArgument<NEUIntKey>	arg_flag;

	public:
		virtual NEExportable::ModuleHeader& getHeader() const;

	protected:
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_red);
			tray.push(arg_green);
			tray.push(arg_blue);
			tray.push(arg_flag);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchModule()
		{
			arg_red.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_red.setValue(0);
			arg_green.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_green.setValue(0);
			arg_blue.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_blue.setValue(0);
			arg_flag.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_flag.setValue(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER);

			return RESULT_SUCCESS;
		}
		virtual type_result _onExecute();

	public:
		virtual NEObject& clone() const;
	};
}