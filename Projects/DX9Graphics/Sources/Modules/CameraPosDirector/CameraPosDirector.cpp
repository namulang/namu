#include "CameraPosDirector.hpp"
#include "../Camera/Camera.hpp"

namespace DX9Graphics
{
	const NEExportable::ModuleHeader& CameraPosDirector::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T("CameraPosDirector");
			_header.getDeveloper() = _T("kniz");
			_header.setRevision(1);
			_header.getComment() = _T("0번. CameraSelector\n1번. 바라볼 방향 X좌표\n2번. 바라볼 방향 Y좌표\n3번. 바라볼 방향 Z좌표");
			_header.getVersion()  = _T("0.0.1a");
			_header.getReleaseDate() = _T("");
			_header.getModuleDependencies().create(0);
			_header.setMaxErrorCodeCount(1);
		}

		return _header;
	}

	type_result CameraPosDirector::execute()
	{
		NEModuleSelector& sel = getCameraSelector();
		const NECodeSet& cs = Camera::getCameraCodeSet();

		while(NEModule* itr = &sel.getModule())
		{
			if(cs.find(itr->getScriptCode()) != NE_INDEX_ERROR)
			{
				Camera& camera = static_cast<Camera&>(*itr);

				D3DXVECTOR3 pos = camera.createTranslationVector();
				D3DXVECTOR3 look = createFocusVector() - pos, normalized;
				D3DXVec3Normalize(&normalized, &look);				
				camera.setLookVector(normalized);
			}
		}

		return RESULT_SUCCESS;
	}
}