#include "MessageReceiver.hpp"

namespace NE
{
	NE_DLL MessageReceiver::MessageReceiver()
		: NEModule()
	{

	}

	NE_DLL MessageReceiver::MessageReceiver(const MessageReceiver& source)
		: NEModule(source)
	{

	}

	NE_DLL MessageReceiver::~MessageReceiver()
	{

	}

	type_result NE_DLL MessageReceiver::initialize()
	{
		getKeySet().create(2);
		getKeySet().push( NEModuleCodeSetKey());
		getKeySet().push( NETStringSetKey() );

		return RESULT_SUCCESS;
	}

	type_result NE_DLL MessageReceiver::execute()
	{
		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &MessageReceiver::clone() const
	{
		return *(new MessageReceiver(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &MessageReceiver::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T("MessageReceiver");
			_header.getDeveloper() = _T("kniz");
			_header.setRevision(1);
			_header.getComment() = _T("0번. 메시지(index)에 따라 실행할 Action들(index)\n1번. 메시지의 이름");
			_header.getVersion()  = _T("0.0.1a");
			_header.getReleaseDate() = _T("2013-09-29");
			_header.getModuleDependencies().create(0);
			_header.setMaxErrorCodeCount(0);
		}

		return _header;
	}
}
