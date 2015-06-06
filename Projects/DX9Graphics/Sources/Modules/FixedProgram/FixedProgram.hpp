#pragma once

#include "../ShaderProgram/ShaderProgram.hpp"
#include "../Sprite/Sprite.hpp"
#include "../TabledTexture/TabledTexture.hpp"

namespace DX9Graphics
{
	class NE_DLL FixedProgram : public ShaderProgram
	{
	public:
		typedef ShaderProgram SuperClass;
		typedef FixedProgram ThisClass;

	public:
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;

			if (_header.isValid() != RESULT_NOTHING)
			{
				_header.getName() = "FixedProgram";
				_header.getDeveloper() = "kniz";
				_header.setRevision(1);
				_header.getComment() =
					"조명이 제거된 고정 파이프라인 Shader프로그램 입니다.\n"
					"가장 기본적인 형태로 물체를 출력합니다.\n"
					"FinalRenderTarget이 PREVIOUS_BUFFER일 때는, 이전 버퍼에 저장된 Surface를 복사하여 다른 버퍼로 옮깁니다.";
				"그 이외의 값을때는 버퍼에 새로 그립니다.";
				_header.getVersion() = "0.0.1a";
				_header.getReleaseDate() = "2013-08-24";
				_header.getArgumentsComments() = SuperClass::getHeader().getArgumentsComments();				
			}

			return _header;
		}

	private:
		virtual type_result _onRender(DX9& dx9, Camera& camera)
		{
			//	pre:
			type_result result = RESULT_SUCCESS;
			switch (arg_final_render_target)
			{
			case ShaderProgram::ONLY_ONE:
				if(NEResult::hasError(_standByFinalRenderTarget(dx9, ShaderProgram::READY_RENDER_TARGET_OUTPUT))) 
					return ALERT_ERROR("최종 렌더타겟이 없습니다");

				result = SuperClass::_onRender(dx9, camera);
				break;

			case ShaderProgram::FIRST:
				if(NEResult::hasError(_standByFinalRenderTarget(dx9, ShaderProgram::READY_RENDER_TARGET_NEW_BUFFER))) 
					return ALERT_ERROR("최종 렌더타겟이 없습니다");

				result = SuperClass::_onRender(dx9, camera);
				_endFinalRenderTarget(_getRenderTargetSet(dx9));
				break;

			case ShaderProgram::MIDDLE:
				if(NEResult::hasError(_standByFinalRenderTarget(dx9, ShaderProgram::READY_RENDER_TARGET_FILLED_BUFFER))) 
					return ALERT_ERROR("최종 렌더타겟이 없습니다");

				result = SuperClass::_onRender(dx9, camera);
				break;

			case ShaderProgram::LAST:
				{
					//	1-Pass:
					arg_final_render_target = ShaderProgram::MIDDLE;
					if(NEResult::hasError(_standByFinalRenderTarget(dx9, ShaderProgram::READY_RENDER_TARGET_FILLED_BUFFER))) 
						return ALERT_ERROR("최종 렌더타겟이 없습니다");
					result = SuperClass::_onRender(dx9, camera);

					//	2-Pass:
					arg_final_render_target = ShaderProgram::LAST;
					if( ! &dx9)
						return ALERT_ERROR("DX9 바인딩 실패. 작업을 중지합니다.");
					LPDIRECT3DDEVICE9 device = dx9.getDevice();
					RenderTargetSet& targets = _getRenderTargetSet(dx9);
					if(targets.getSize() <= 0)
						return ALERT_ERROR("DX9 바인딩 실패로 렌더타겟을 생성하지 못했습니다.");

					//			Matrix치환:
					D3DXMATRIX new_w, new_v, new_p = _getOrthoMatrix();
					D3DXMatrixIdentity(&new_w);
					D3DXMatrixLookAtLH(&new_v, &D3DXVECTOR3(0, 0, -1), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 1, 0));
					device->SetTransform(D3DTS_WORLD, &new_w);
					device->SetTransform(D3DTS_VIEW, &new_v);
					device->SetTransform(D3DTS_PROJECTION, &new_p);

					//	main:
					if(NEResult::hasError(_standByFinalRenderTarget(dx9, ShaderProgram::READY_RENDER_TARGET_OUTPUT)))
						return ALERT_ERROR("최종 렌더타겟이 없습니다");
					device->BeginScene();
					device->SetTexture(0, &targets.getFilledTarget().getTexture());

					device->SetRenderState(D3DRS_ZENABLE, FALSE);					
					_renderTargetVertex(device);
					_endFinalRenderTarget(targets);
					device->SetRenderState(D3DRS_ZENABLE, TRUE);

					//	post:
					device->EndScene();
				}			
				break;
			}

			return result;
		}
		virtual LPCVOID _onRequestShaderCode(OUT type_int& size_of_binary) const { size_of_binary = 0; return 0; }
		virtual type_result _onSetShaderHandles(ShaderHandleSet&) { return RESULT_SUCCESS; }
	};
}