#include "XAudio2Decoder.hpp"
#include "XAudio2WAVEDecoder.hpp"
#include "XAudio2OGGDecoder.hpp"
#include "XAudio2Manager.hpp"
#include "XAudio2Player.hpp"

namespace XA2
{
	const NECodeSet& XAudio2Decoder::getModuleScriptCodes()
	{
		NECodeType type(NECodeType::MODULE_SCRIPT);
		static NECodeSet instance(type);

		if (instance.getSize() <= 0)
		{
			instance.create(2);
			instance.push(XAudio2WAVEDecoder().getHeader());
			instance.push(XAudio2OGGDecoder().getHeader());
		}

		return instance;		
	}
	void XAudio2Decoder::_stopAllRelativePlayers()
	{
		if( ! arg_load_success.getValue()) return;
		static NECodeSet cs(1, NECodeType::ALL);
		if (cs.getLength() <= 0)
			cs.push(NEExportable::Identifier("XAudio2Player.kniz"));

		NEModuleSelector ms;
		ms.setManager(NEType::NENODE_MANAGER);
		ms.setCodes(NECodeType(NECodeType::ALL));
		ms.setModuleCodes(cs);

		while(NEModule* e = &ms.getModule())
		{
			XAudio2Player& pl = static_cast<XAudio2Player&>(*e);
			if(	&pl.getDecoder() == this	&&
				! pl.isStopped()			)
				pl.stop();
		}
	}
}