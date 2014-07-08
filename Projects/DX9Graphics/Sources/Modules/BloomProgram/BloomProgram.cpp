#include "BloomProgram.hpp"
#include "define.hpp"
#include "bloom_hlsl.hpp"

namespace DX9Graphics
{
	type_result DX9Graphics::BloomProgram::initialize()
	{
		SuperClass::initialize();

		NEKeyCodeSet& keyset = getKeySet();
		keyset.resize(keyset.getSize() + 1);
		return keyset.push(NEFloatKey(DEFAULT_BLOOM_LEVEL));		
	}

	const NEExportable::ModuleHeader& BloomProgram::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T(_NAME);
			_header.getDeveloper() = _T(_DEVELOPER);
			_header.setRevision(_REVISION);
			_header.getComment() = _T(_COMMENT);
			_header.getVersion()  = _T(_VERSION);
			_header.getReleaseDate() = _T(_DATE);
			_header.getModuleDependencies().create(_DEPENDENCIES_COUNT);
			_header.setMaxErrorCodeCount(1);
		}

		return _header;
	}

	LPCVOID BloomProgram::_onRequestShaderCode(OUT type_int& size_of_binary) const
	{		
		size_of_binary = sizeof(g_main);

		return g_main;
	}
}