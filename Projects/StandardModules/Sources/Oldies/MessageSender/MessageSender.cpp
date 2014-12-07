#include "MessageSender.hpp"
#include "../MessageReceiver/MessageReceiver.hpp"

namespace NE
{
	NE_DLL MessageSender::MessageSender()
		: NEModule()
	{

	}

	NE_DLL MessageSender::MessageSender(const MessageSender& source)
		: NEModule(source)
	{

	}

	NE_DLL MessageSender::~MessageSender()
	{

	}

	type_result NE_DLL MessageSender::initialize()
	{
		getKeySet().create(2);
		getKeySet().push(NEModuleSelector());
		getKeySet().push(NEUByteKey());

		return RESULT_SUCCESS;
	}

	type_result NE_DLL MessageSender::execute()
	{
		const NECodeSet& cs = MessageReceiver::getReceiverCodeSet();
		while(MessageReceiver* m = static_cast<MessageReceiver*>(&getTargetSelector().getModule()))
		{
			if(cs.find(m->getScriptCode()) == NE_INDEX_ERROR)
				continue;

			m->sendMessage(getMessageIndexToSend());
		}

		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &MessageSender::clone() const
	{
		return *(new MessageSender(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &MessageSender::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T("MessageSender");
			_header.getDeveloper() = _T("kniz");
			_header.setRevision(1);
			_header.getComment() = _T("0번. MessageReceiver\n1번. 전달할 Message");
			_header.getVersion()  = _T("0.0.1a");
			_header.getReleaseDate() = _T("2013-09-29");
			_header.getModuleDependencies().create(0);
			_header.setMaxErrorCodeCount(0);
		}

		return _header;
	}
}
