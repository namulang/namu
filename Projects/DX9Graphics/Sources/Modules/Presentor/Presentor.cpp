#include "Presentor.hpp"
#include "define.hpp"
#include "../DX9/DX9.hpp"

namespace DX9Graphics
{
	const NEExportable::ModuleHeader& Presentor::getHeader() const
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

	type_result Presentor::execute()
	{
		DX9& dx9 = getBinded();
		if( ! &dx9)
		{
			ALERT_ERROR(" : 디바이스가 없으므로 작업을 취소합니다.");
			return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION;
		}
		LPDIRECT3DDEVICE9 device = dx9.getDevice();



		//	post:
		device->Present(0, 0, 0, 0);
		return RESULT_SUCCESS;
	}
}