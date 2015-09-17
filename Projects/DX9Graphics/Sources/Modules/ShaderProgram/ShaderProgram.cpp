#include "ShaderProgram.hpp"
#include "../AnimatedModel/AnimatedModel.hpp"
#include "../Camera/Camera.hpp"
#include "RenderTargetVertex.hpp"

namespace DX9Graphics
{
	const NECodeSet& ShaderProgram::getModuleScriptCodes()
	{
		NECodeType type(NECodeType::MODULE_SCRIPT);
		static NECodeSet codes(type);

		if (codes.getLength() <= 1)
		{
			codes.create(3);
			codes.push(NEExportable::Identifier("FixedProgram.kniz"));
			codes.push(NEExportable::Identifier("BloomProgram.kniz"));
			codes.push(NEExportable::Identifier("BlurProgram.kniz"));
		}

		return codes;
	}

	type_int ShaderProgram::getRenderTargetHeight() const
	{
		const DX9& dx9 = DX9::getInstancedDX();
		if (!&dx9)
			return ALERT_ERROR("DX9가 없으므로 Height 구하기 실패");

		LPDIRECT3DDEVICE9 device = dx9.getDevice();
		const DX9::PresentParameters& param = dx9.getPresentParameters();
		return static_cast<type_int>(param.BackBufferHeight * arg_height_rate.getValue());
	}

	type_int ShaderProgram::getRenderTargetWidth() const
	{
		const DX9& dx9 = DX9::getInstancedDX();
		if (!&dx9)
			return ALERT_ERROR("DX9가 없으므로 Width 구하기 실패");

		LPDIRECT3DDEVICE9 device = dx9.getDevice();
		const DX9::PresentParameters& param = dx9.getPresentParameters();
		return static_cast<type_int>(param.BackBufferWidth * arg_width_rate.getValue());
	}

	type_result ShaderProgram::_standByFinalRenderTarget(DX9& dx9, EReadyRenderTarget which)
	{
		if( ! &dx9)
			return KERNAL_ERROR("디바이스가 없으므로 실패");

		LPDIRECT3DDEVICE9 device = dx9.getDevice();
		RenderTargetSet& targets = _getRenderTargetSet(dx9);


		//	main:
		switch(which)
		{
		case READY_RENDER_TARGET_OUTPUT:	
			device->SetRenderTarget(0, _original_surface);
			break;

		case READY_RENDER_TARGET_NEW_BUFFER:
			{
				LPDIRECT3DSURFACE9 new_target = &(targets.getEmptyTarget().getSurface());
				device->SetRenderTarget(0, new_target);
				_clear(device);
			}
			break;

		case READY_RENDER_TARGET_EMPTY_BUFFER:
			{
				LPDIRECT3DSURFACE9 previous = &(targets.getEmptyTarget().getSurface());
				device->SetRenderTarget(0, previous);
			}
			break;

		case READY_RENDER_TARGET_FILLED_BUFFER:
			{
				LPDIRECT3DSURFACE9 previous = &(targets.getFilledTarget().getSurface());
				device->SetRenderTarget(0, previous);
			}
			break;

		default:
			KERNAL_ERROR("잘못된 FINAL RENDER TARGET 값입니다.\n\t값 : %d", arg_final_render_target);				
		}

		return RESULT_SUCCESS;
	}
	
	type_result ShaderProgram::_onRenderModel(LPDIRECT3DDEVICE9 device, Camera& camera, Model& model)
	{
		return model.render();
	}

	type_result ShaderProgram::_initializeShader(LPDIRECT3DDEVICE9 device)
	{
		//	pre:
		ThisClass::releaseResource();

		type_int size_of_binary = 0;
		LPCVOID code = _onRequestShaderCode(size_of_binary);
		if( ! size_of_binary)
			return RESULT_ABORT_ACTION | RESULT_SUCCESS;


		//	main:
		LPD3DXBUFFER error_string = 0;
		HRESULT result = D3DXCreateEffect(device, code, size_of_binary, 
			NULL, NULL, D3DXSHADER_SKIPVALIDATION, NULL, 
			&_effect, &error_string);
		if(FAILED(result))
			KERNAL_ERROR("셰이더 생성에 실패했습니다.\n\t생성 실패 에러 : %d", result);

		if(error_string)
		{
			NETString converted(static_cast<char*>(error_string->GetBufferPointer()));
			KERNAL_WARNING("에러 및 경고 메세지가 있습니다.\n\t경고 : %s", converted.toCharPointer());
			error_string->Release();
			error_string = 0;
			return RESULT_TYPE_WARNING;
		}
		return RESULT_SUCCESS;		
	}

	IDirect3DVertexBuffer9& ShaderProgram::_getRenderTargetVertex(LPDIRECT3DDEVICE9 device)
	{
		static LPDIRECT3DVERTEXBUFFER9 _buffer = 0;
		if( ! device)
		{
			KERNAL_ERROR("디바이스 획득 실패");
			return *_buffer;
		}

		if( ! _buffer)
		{
			if ( FAILED(device->CreateVertexBuffer(	
				4 * sizeof(RenderTargetVertex), 0, RENDER_TARGET_VERTEX_FVF, D3DPOOL_DEFAULT, &_buffer, NULL)))
			{
				KERNAL_ERROR("버텍스 버퍼 생성 실패");
				return *_buffer;
			}				

			//	버텍스 초기화:
			/*		
					이 버텍스는 RenderTarget를 출력하는 용도로만 사용되므로 그 값이
					항상 고정이다.
			*/
			RenderTargetVertex* vertexes;
			_buffer->Lock(0, 4 * sizeof(RenderTargetVertex), (void**) &vertexes, NULL);
			//	버텍스 설정:		
			//		좌하:
			vertexes[0].x	= -1.0f;	vertexes[0].y		= 1.0f;
			vertexes[0].tu	= 0.0f;		vertexes[0].tv		= 0.0f;
			vertexes[0].z	= 0.0f;		vertexes[0].color	= D3DCOLOR_ARGB(255, 255, 255, 255);
			//		좌상:
			vertexes[1].x	= -1.0f;	vertexes[1].y		= -1.0f;
			vertexes[1].tu	= 0.0f;		vertexes[1].tv		= 1.0f;
			vertexes[1].z	= 0.0f;		vertexes[1].color	= D3DCOLOR_ARGB(255, 255, 255, 255);
			//		우하:
			vertexes[2].x	= 1.0f;		vertexes[2].y		= 1.0f;
			vertexes[2].tu	= 1.0f;		vertexes[2].tv		= 0.0f;
			vertexes[2].z	= 0.0f;		vertexes[2].color	= D3DCOLOR_ARGB(255, 255, 255, 255);
			//		우상:
			vertexes[3].x	= 1.0f;		vertexes[3].y		= -1.0f;
			vertexes[3].tu	= 1.0f;		vertexes[3].tv		= 1.0f;
			vertexes[3].z	= 0.0f;		vertexes[3].color	= D3DCOLOR_ARGB(255, 255, 255, 255);
			//	버퍼 풀기:
			_buffer->Unlock();
		}

		return *_buffer;
	}

	type_result ShaderProgram::_renderTargetVertex(LPDIRECT3DDEVICE9 device)
	{
		if( ! device)
			return ALERT_ERROR("디바이스 획득 실패");

		IDirect3DVertexBuffer9& vertexes = _getRenderTargetVertex(device);
		if( ! &vertexes)
			return ALERT_ERROR("렌더타겟용 버텍스 생성에 실패했습니다");


		//	main:
		//device->SetRenderState(D3DRS_ZENABLE, FALSE);
		device->SetFVF(RENDER_TARGET_VERTEX_FVF);
		device->SetStreamSource(0, &vertexes, 0, sizeof(RenderTargetVertex));
		device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);		
		//device->SetRenderState(D3DRS_ZENABLE, TRUE);

		return RESULT_SUCCESS;
	}

	void ShaderProgram::_endFinalRenderTarget(RenderTargetSet& targets)
	{
		if(	arg_final_render_target == FIRST	|| 
			arg_final_render_target == MIDDLE	)
			targets.notifyTargetFilled();
	}
	
	type_result ShaderProgram::initializeResource()
	{
		//	main:
		if(isResourceInitialized()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		DX9& dx9 = DX9::getInstancedDX();
		if( ! &dx9)
			return KERNAL_ERROR("디바이스가 초기화 되지 않았으므로 작업을 취소합니다.");

		LPDIRECT3DDEVICE9 device = dx9.getDevice();	
		if( ! _effect)
		{
			_initializeShader(device);
			_bindHandles();				
		}

		SuperClass::initializeResource();

		return RESULT_SUCCESS;
	}

	type_result ShaderProgram::_onRender(DX9& dx9, Camera& camera)
	{
		if( ! isEnable()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		if( ! &dx9)
			return ALERT_ERROR("DX9 바인딩 실패");

		NEModuleSelector selector;
		selector.NENodeSelector::operator=(camera.arg_targets.getValue());
		selector.setModuleCodes(Model::getModuleScriptCodes());

		LPDIRECT3DDEVICE9 device = dx9.getDevice();

		while(&selector.getModule())
		{
			Model& model = static_cast<Model&>(selector.peekModule());

			_onRenderModel(device, camera, model);
		}		

		return RESULT_SUCCESS;
	}
}