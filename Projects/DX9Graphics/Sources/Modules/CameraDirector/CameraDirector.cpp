#include "CameraDirector.hpp"
#include "../Camera/Camera.hpp"
#include "../Model/Model.hpp"

namespace DX9Graphics
{
	const NEExportable::ModuleHeader& CameraDirector::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T("CameraDirector");
			_header.getDeveloper() = _T("kniz");
			_header.setRevision(1);
			_header.getComment() = _T("0번. CameraSelector\n1번. 대상이 되는 물체(1개만 유효)");
			_header.getVersion()  = _T("0.0.1a");
			_header.getReleaseDate() = _T("");
			_header.getModuleDependencies().create(0);
			_header.setMaxErrorCodeCount(1);
		}

		return _header;
	}

	type_result CameraDirector::execute()
	{
		//	pre:
		NEModuleSelector& cam_sel = getCameraSelector(),
						& trg_sel = getTargetSelector();		
		const NECodeSet	& cam_cs = Camera::getCameraCodeSet(),
						& trg_cs = Model::getScriptCodeSet();
		

		//	main:
		while(NEModule* itr = &cam_sel.getModule())
		{
			if(cam_cs.find(itr->getScriptCode()) == NE_INDEX_ERROR)
				continue;
			Camera& camera = static_cast<Camera&>(*itr);

			while(NEModule* trg = &trg_sel.getModule())
			{
				if(trg_cs.find(trg->getScriptCode()) == NE_INDEX_ERROR)
					continue;
				Model& model = static_cast<Model&>(*trg);

				_onDirect(camera, model);

				trg_sel.initializeReferingPoint();
			}
		}
		

		//	post:
		return RESULT_SUCCESS;
	}

	void CameraDirector::_onDirect(Camera& camera, Model& model)
	{
		const D3DXMATRIX& world = model.getWorldMatrix();
		const D3DXVECTOR3& trans = model.createTranslationVector();
		D3DXVECTOR3 transited;
		D3DXVec3TransformCoord(&transited, &trans, &world);

		D3DXVECTOR3 pos = camera.createTranslationVector();
		D3DXVECTOR3 look = transited - pos, normalized;
		D3DXVec3Normalize(&normalized, &look);				
		camera.setLookVector(normalized);
	}

}