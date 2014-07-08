#include "Picker.hpp"
#include "../Model/Model.hpp"
#include "../AnimatedModel/AnimatedModel.hpp"
#include "../PerspectiveCamera/PerspectiveCamera.hpp"
#include "../Texture/Texture.hpp"
#include "../Sprite/Sprite.hpp"
#include "define.hpp"

namespace DX9Graphics
{
	type_result Picker::execute()
	{
		//	pre:
		if( ! isEnable()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		//		Targetting:
		const NECodeSet	& model_codes = Model::getScriptCodeSet(),
						& camera_codes = Camera::getCameraCodeSet();
		NEModuleSelector& cam_sel = getCameraSelector(),
						& model_sel = getModelSelector();
		static type_code sprite_code = Kernal::getInstance().getModuleManager()
			.getModule(Sprite().getHeader()).getScriptCode();


		//	main:
		Camera* citr = 0;
		while(citr = (Camera*) &cam_sel.getModule())
		{
			if(camera_codes.find(citr->getScriptCode()) == NE_INDEX_ERROR)
				continue;

			Vectors ray = _createRayInWorldCoords(*citr);

			Model* mitr = 0;
			while(mitr = (Model*) &model_sel.getModule())
			{
				if(model_codes.find(mitr->getScriptCode()) == NE_INDEX_ERROR)
					continue;
				NEModule& sprite = mitr->getModelingSelector().getBinder().getBinded();
				Texture& texture = static_cast<Texture&>(mitr->getTextureSelector().getBinder().getBinded());
				if( ! &sprite || sprite.getScriptCode() != sprite_code)
				{
					ALERT_ERROR(" : ¸ðµ¨¿¡ ¹ÙÀÎµùµÈ ModelingÀÌ Sprite°¡ ¾Æ´Õ´Ï´Ù.")
					continue;
				}
				
				
				Vectors quad = _createQuadOfSprite(texture.getWidthOfOneFrame(), texture.getHeightOfOneFrame());
				if(_isRayIntersectedToQuad(quad, ray, mitr->getWorldMatrix()))
				{
					isSomethingPicked().getValue() = true;
					cam_sel.initializeReferingPoint();
					model_sel.initializeReferingPoint();
					return RESULT_TRUE | RESULT_SUCCESS;
				}
			}
		}

		isSomethingPicked().getValue() = false;
		return RESULT_FALSE | RESULT_SUCCESS;
	}

	const NEExportable::ModuleHeader& Picker::getHeader() const
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

	Picker::Vectors Picker::_createRayInWorldCoords(const Camera& camera) const
	{
		//	pre:
		Vectors to_return(2);
		const DX9& dx9 = static_cast<const DX9&>(camera.getDX9Selector().getBinder().getBinded());
		if( ! &dx9)
		{
			ALERT_ERROR(" : DX9 ¹ÙÀÎµù ½ÇÆÐ");
			return to_return;
		}
		HWND hwnd = dx9.getHWND();
		const D3DXMATRIX& p = camera.getProjectionMatrix();
		const D3DXMATRIX& v = camera.getViewMatrix();
		D3DVIEWPORT9 vp = camera.createViewPort();


		//	main:
		POINT cursor;
		GetCursorPos(&cursor);
		ScreenToClient(hwnd, &cursor);		
		//		ProjectionÁÂÇ¥ -> ViewÁÂÇ¥:
		D3DXVECTOR3 ray_in_viewcoords(
			((cursor.x - vp.X)*2.0f / vp.Width - 1.0f - p._31) / p._11,
			-((cursor.y - vp.Y)*2.0f / vp.Height - 1.0f - p._32) / p._22,
			1.0f
		);
		//		ViewÁÂÇ¥ -> WorldÁÂÇ¥:
		D3DXMATRIX invV;
		D3DXMatrixInverse(&invV, 0, &v);
		Vector ray_point(invV._41, invV._42, invV._43),
			ray_direction(
			ray_in_viewcoords.x*invV._11 + ray_in_viewcoords.y*invV._21 + ray_in_viewcoords.z*invV._31,
			ray_in_viewcoords.x*invV._12 + ray_in_viewcoords.y*invV._22 + ray_in_viewcoords.z*invV._32,
			ray_in_viewcoords.x*invV._13 + ray_in_viewcoords.y*invV._23 + ray_in_viewcoords.z*invV._33
		);
		

		
		//	post:		
		to_return.push(ray_point);
		to_return.push(ray_direction);
		return to_return;
	}

	Picker::Vectors Picker::_createQuadOfSprite(type_uint width, type_uint height) const
	{
		typedef Vector VEC;
		Vectors to_return(4);
		type_float	hw = width / 2.0f,
					hh = height / 2.0f;

		to_return.push(VEC(-hw, -hh, 0));
		to_return.push(VEC(hw, -hh, 0));
		to_return.push(VEC(-hw, hh, 0));
		to_return.push(VEC(hw, hh, 0));
		return to_return;
	}

	bool Picker::_isRayIntersectedToQuad(const Vectors& quad, const Vectors& ray, const D3DXMATRIX& world) const
	{
		if(quad.getLength() < 4 || ray.getLength() < 2)
		{
			ALERT_ERROR(" : ray¿Í quadÀÇ °¹¼ö°¡ ºÒÃæºÐÇÕ´Ï´Ù.")
			return false;
		}
		typedef D3DXVECTOR3 VEC;
		VEC v1,v2,v3,v4;


		D3DXVec3TransformCoord(&v1, &quad[0], &world);
		D3DXVec3TransformCoord(&v2, &quad[1], &world);
		D3DXVec3TransformCoord(&v3, &quad[2], &world);
		D3DXVec3TransformCoord(&v4, &quad[3], &world);


		float not_use = 0;
		if(	! D3DXIntersectTri(&v1, &v2, &v3, &ray[0], &ray[1], &not_use, &not_use, &not_use)	&&
			! D3DXIntersectTri(&v2, &v3, &v4, &ray[0], &ray[1], &not_use, &not_use, &not_use)	)
			return false;

		return true;
	}
}