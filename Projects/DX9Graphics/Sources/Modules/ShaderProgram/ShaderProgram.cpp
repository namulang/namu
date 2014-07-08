#include "ShaderProgram.hpp"
#include "../Model/Model.hpp"
#include "../AnimatedModel/AnimatedModel.hpp"
#include "../Camera/Camera.hpp"
#include "define.hpp"
#include "RenderTargetVertex.hpp"

namespace DX9Graphics
{
	NECodeSet& ShaderProgram::_getTargetCodeSet() const
	{
		static NECodeSet codeset;
		if(codeset.getSize() <= 0)
		{
			NEModuleManager& moduler = Kernal::getInstance().getModuleManager();			
			codeset.create(2);
			codeset.setCodeType(NECodeType::SCRIPT);
			codeset.push(Model().getHeader());
			codeset.push(AnimatedModel().getHeader());
		}

		return codeset;
	}

	type_result ShaderProgram::_onRender(DX9& dx9, Camera& camera)
	{
		if( ! isEnable()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		if( ! &dx9)
		{
			ALERT_ERROR("DX9 바인딩 실패");
			return RESULT_TYPE_ERROR;
		}

		NEModuleSelector selector;
		selector.NENodeSelector::operator=(camera.getTargetSelector());
		selector.setModuleCodeSet(_getTargetCodeSet());
		selector.setModuleType(NECodeType::SCRIPT);

		LPDIRECT3DDEVICE9 device = dx9.getDevice();
		
		if(NEResult::hasError(_standByFinalRenderTarget(dx9))) 
		{
			ALERT_ERROR("최종 렌더타겟이 없습니다");
			return RESULT_TYPE_ERROR;
		}
		device->BeginScene();

		while(&selector.getModule())
		{
			Model& model = static_cast<Model&>(selector.peekModule());

			_updateBlendingStateToCamerasOne(device, camera);

			_onRenderModel(device, camera, model);
		}
		device->EndScene();

		_endFinalRenderTarget(_getRenderTargetSet(dx9));

		return RESULT_SUCCESS;
	}

	type_result ShaderProgram::_standByFinalRenderTarget(DX9& dx9)
	{
		if( ! &dx9)
		{
			KERNAL_ERROR("디바이스가 없으므로 실패");
			return RESULT_TYPE_ERROR;
		}
		LPDIRECT3DDEVICE9 device = dx9.getDevice();
		RenderTargetSet& targets = _getRenderTargetSet(dx9);


		//	main:
		type_byte& option = getFinalRenderTarget();
		switch(option)
		{
		case _FINAL_RENDER_TARGET_OUTPUT:	
			device->SetRenderTarget(0, _original_surface);
			break;

		case _FINAL_RENDER_TARGET_NEW_BUFFER:
			{
				LPDIRECT3DSURFACE9 new_target = &(targets.getEmptyTarget().getSurface());
				device->SetRenderTarget(0, new_target);
				device->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);				
			}			
			break;

		case _FINAL_RENDER_TARGET_PREVIOUS_BUFFER:
			{
				LPDIRECT3DSURFACE9 previous = &(targets.getFilledTarget().getSurface());
				device->SetRenderTarget(0, previous);
			}
			break;

		default:
			KERNAL_ERROR("잘못된 FINAL RENDER TARGET 값입니다.\n\t값 : %d", option);				
		}

		return RESULT_SUCCESS;
	}

	type_result ShaderProgram::initialize()
	{
		SuperClass::initialize();

		NEKeyCodeSet& keyset = getKeySet();
		keyset.resize(keyset.getSize() + 3);
		keyset.push(NEFloatKey(1.0f));	//	1:	WidthRate
		keyset.push(NEFloatKey(1.0f));	//	2:	HeightRate
		keyset.push(NEByteKey(_FINAL_RENDER_TARGET_OUTPUT));		//	3:	FinalRenderTarget(0: 출력 1: 버퍼에 담기-다른 셰이더 프로그램으로 전달 2: 파일에 저장)

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
				4 * sizeof(RenderTargetVertex), 0, _RENDER_TARGET_VERTEX_FVF, D3DPOOL_DEFAULT, &_buffer, NULL)))
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
		{
			ALERT_ERROR("디바이스 획득 실패");
			return RESULT_TYPE_ERROR;
		}
		IDirect3DVertexBuffer9& vertexes = _getRenderTargetVertex(device);
		if( ! &vertexes)
		{
			ALERT_ERROR("렌더타겟용 버텍스 생성에 실패했습니다");
			return RESULT_TYPE_ERROR;
		}


		//	main:
		device->SetFVF(_RENDER_TARGET_VERTEX_FVF);
		device->SetStreamSource(0, &vertexes, 0, sizeof(RenderTargetVertex));
		device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);		

		return RESULT_SUCCESS;
	}

	void ShaderProgram::_endFinalRenderTarget(RenderTargetSet& targets)
	{
		type_byte& option = getFinalRenderTarget();
		if(option == _FINAL_RENDER_TARGET_NEW_BUFFER)
			targets.notifyTargetFilled();
	}

	type_result ShaderProgram::_updateBlendingStateToCamerasOne(LPDIRECT3DDEVICE9 device, Camera& camera)
	{
		device->SetRenderState(D3DRS_SRCBLEND, camera.getSourceBlend());
		device->SetRenderState(D3DRS_DESTBLEND, camera.getDestBlend());
		return RESULT_SUCCESS;
	}
}