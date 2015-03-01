#include "Picker.hpp"
#include "../Model/Model.hpp"
#include "../AnimatedModel/AnimatedModel.hpp"
#include "../PerspectiveCamera/PerspectiveCamera.hpp"
#include "../Texture/Texture.hpp"
#include "../Sprite/Sprite.hpp"
#include "../DX9/DX9.hpp"

namespace DX9Graphics
{
	type_result Picker::_onExecute()
	{
		//	pre:
		if (!isEnable()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		//		Targetting:
		const NECodeSet	& model_codes = Model::getModuleScriptCodes(),
			&camera_codes = Camera::getModuleScriptCodes();
		NEModuleSelector& cam_sel = arg_camera.getValue(),
			&model_sel = arg_model.getValue();
		static type_code sprite_code = Kernal::getInstance().getModuleManager()
			.getModule(Sprite().getHeader()).getScriptCode();


		//	main:
		Camera* citr = 0;
		while (citr = (Camera*)&cam_sel.getModule())
		{
			if (camera_codes.find(NECode(citr->getScriptCode(), NECodeType::MODULE_SCRIPT)) == NE_INDEX_ERROR)
				continue;

			Vectors ray = _createRayInWorldCoords(*citr);

			Model* mitr = 0;
			while (mitr = (Model*)&model_sel.getModule())
			{
				if (model_codes.find(NECode(mitr->getScriptCode(), NECodeType::MODULE_SCRIPT)) == NE_INDEX_ERROR)
					continue;

				DockableResource& sprite = mitr->getModeling();
				Texture& texture = mitr->getTexture();
				if (!&sprite || sprite.getScriptCode() != sprite_code)
					return ALERT_ERROR(" : 모델에 바인딩된 Modeling이 Sprite가 아닙니다.")


					Vectors quad = _createQuadOfSprite(texture.getWidthOfOneFrame(), texture.getHeightOfOneFrame());
				if (_isRayIntersectedToQuad(quad, ray, mitr->getWorldMatrix()))
				{
					arg_is_picked.setValue(true);
					cam_sel.initializeReferingPoint();
					model_sel.initializeReferingPoint();
					return RESULT_TRUE | RESULT_SUCCESS;
				}
			}
		}

		arg_is_picked.setValue(false);
		return RESULT_FALSE | RESULT_SUCCESS;
	}

	Picker::Vectors Picker::_createRayInWorldCoords(const Camera& camera) const
	{
		//	pre:
		Vectors to_return(2);
		const DX9& dx9 = DX9::getInstancedDX();
		if( ! &dx9)
			return ALERT_ERROR(" : DX9 바인딩 실패");

		HWND hwnd = dx9.getHWND();
		const D3DXMATRIX& p = camera.getProjectionMatrix();
		const D3DXMATRIX& v = camera.getViewMatrix();
		D3DVIEWPORT9 vp = camera.createViewPort();


		//	main:
		POINT cursor;
		GetCursorPos(&cursor);
		ScreenToClient(hwnd, &cursor);		
		//		Projection좌표 -> View좌표:
		D3DXVECTOR3 ray_in_viewcoords(
			((cursor.x - vp.X)*2.0f / vp.Width - 1.0f - p._31) / p._11,
			-((cursor.y - vp.Y)*2.0f / vp.Height - 1.0f - p._32) / p._22,
			1.0f
			);
		//		View좌표 -> World좌표:
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
			ALERT_ERROR(" : ray와 quad의 갯수가 불충분합니다.");
			return false;
		}

		typedef D3DXVECTOR3 VEC;
		VEC v1,v2,v3,v4;

		D3DXMATRIX real_world = Sprite::adj * world;

		D3DXVec3TransformCoord(&v1, &quad[0], &real_world);
		D3DXVec3TransformCoord(&v2, &quad[1], &real_world);
		D3DXVec3TransformCoord(&v3, &quad[2], &real_world);
		D3DXVec3TransformCoord(&v4, &quad[3], &real_world);

		float not_use = 0;
		if(	! D3DXIntersectTri(&v1, &v2, &v3, &ray[0], &ray[1], &not_use, &not_use, &not_use)	&&
			! D3DXIntersectTri(&v2, &v3, &v4, &ray[0], &ray[1], &not_use, &not_use, &not_use)	)
			return false;

		return true;
	}
}