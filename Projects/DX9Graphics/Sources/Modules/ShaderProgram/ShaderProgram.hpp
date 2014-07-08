#pragma once

#include "../Resource/Resource.hpp"

namespace DX9Graphics
{
	class Model;
	class Camera;

	class NE_DLL ShaderProgram : public Resource
	{
	public:
		typedef Resource SuperClass;
		typedef ShaderProgram ThisClass;

	public:
#include "RenderTarget.hpp"
#include "RenderTargetSet.hpp"
#include "ShaderHandle.hpp"
#include "ShaderHandleSet.hpp"

	public:
		friend class Camera;
		friend class DX9;

	public:
		ShaderProgram()
			: SuperClass(), _effect(0), _original_surface(0)
		{
			
		}
		~ShaderProgram()
		{
			ThisClass::releaseResource();
		}

	public:
		type_float& getWidthRate()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_float&>(casted->getWidthRate());
		}
		const type_float& getWidthRate() const
		{
			const NEKey& key = getKeySet()[1];
			if( ! key.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("1번째키는 NEFLOAT_KEY여야 합니다");
				type_float* nullpoint = 0;
				return *nullpoint;
			}

			const NEFloatKey& target = static_cast<const NEFloatKey&>(key);
			return target.getValue();
		}
		type_float& getHeightRate()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_float&>(casted->getHeightRate());
		}
		const type_float& getHeightRate() const
		{
			const NEKey& key = getKeySet()[2];
			if( ! key.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("2번키는 NEFLOAT_KEY여야 합니다");
				type_float* nullpoint = 0;
				return *nullpoint;
			}

			const NEFloatKey& target = static_cast<const NEFloatKey&>(key);
			return target.getValue();
		}
		type_byte& getFinalRenderTarget()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_byte&>(casted->getFinalRenderTarget());
		}
		const type_byte& getFinalRenderTarget() const
		{
			const NEKey& key = getKeySet()[3];
			if( ! key.isSubClassOf(NEType::NEBYTE_KEY))
			{
				ALERT_ERROR("3번키는 NEBYTE_KEY여야 합니다");
				type_byte* nullpoint = 0;
				return *nullpoint;
			}

			const NEByteKey& target = static_cast<const NEByteKey&>(key);
			return target.getValue();
		}
		ID3DXEffect& getEffect() { return *_effect; }
		const ID3DXEffect& getEffect() const { return *_effect; }
		ShaderHandleSet& getShaderHandleSet() { return _handles; }
		const ShaderHandleSet& getShaderHandleSet() const { return _handles; }
		type_int getRenderTargetWidth() const
		{
			const DX9& dx9 = getBinded();
			if( ! &dx9)
			{
				ALERT_ERROR("DX9가 없으므로 Width 구하기 실패");
				return RESULT_TYPE_ERROR;
			}
			LPDIRECT3DDEVICE9 device = dx9.getDevice();
			const DX9::PresentParameters& param = dx9.getPresentParameters();
			return static_cast<type_int>(param.BackBufferWidth * getWidthRate());
		}
		type_int getRenderTargetHeight() const
		{
			const DX9& dx9 = getBinded();
			if( ! &dx9)
			{
				ALERT_ERROR("DX9가 없으므로 Height 구하기 실패");
				return RESULT_TYPE_ERROR;
			}
			LPDIRECT3DDEVICE9 device = dx9.getDevice();
			const DX9::PresentParameters& param = dx9.getPresentParameters();
			return static_cast<type_int>(param.BackBufferHeight * getHeightRate());
		}		
		LPDIRECT3DSURFACE9 getOriginalSurface() { return _original_surface; }
		const LPDIRECT3DSURFACE9 getOriginalSurface() const { return _original_surface; }

	public:
		virtual type_result initializeResource()
		{
			//	main:
			if(isResourceInitialized()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
			DX9& dx9 = getBinded();
			if( ! &dx9)
			{
				KERNAL_ERROR("디바이스가 초기화 되지 않았으므로 작업을 취소합니다.");
				return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION;
			}
			LPDIRECT3DDEVICE9 device = dx9.getDevice();	
			if( ! _effect)
			{
				_initializeShader(device);
				_bindHandles();				
			}

			SuperClass::initializeResource();

			return RESULT_SUCCESS;
		}
		virtual type_result execute()
		{
			return RESULT_SUCCESS;
		}		
		virtual type_result initialize();
		virtual type_result releaseResource()
		{
			if(_effect)
				_effect->Release();
			_effect = 0;
			_handles.release();

			return SuperClass::releaseResource();
		}
		virtual void release()
		{
			SuperClass::release();

			releaseResource();
		}

	protected:
		virtual type_result _onRender(DX9& dx9, Camera& camera);

	private:
		virtual type_result _render(Camera& camera)
		{
			//	pre:
			DX9& dx9 = getBinded();
			if( ! &dx9) 
			{
				KERNAL_ERROR("DX9 바인딩 실패로 셰이더 프로그램을 렌더링 할 수 없습니다");
				return RESULT_TYPE_ERROR;
			}
			LPDIRECT3DDEVICE9 device = dx9.getDevice();
			if( ! _effect)
				initializeResource();
			//		상태 보존:
			device->GetRenderTarget(0, &_original_surface);		
			//		Matrix:
			D3DXMATRIX old_v, old_p, old_w;
			device->GetTransform(D3DTS_WORLD, &old_w);
			device->GetTransform(D3DTS_VIEW, &old_v);
			device->GetTransform(D3DTS_PROJECTION, &old_p);			

			
			//	main:
			_onRender(dx9, camera);


			//	post:
			device->SetTransform(D3DTS_WORLD, &old_w);
			device->SetTransform(D3DTS_VIEW, &old_v);
			device->SetTransform(D3DTS_PROJECTION, &old_p);
			if(_original_surface)
			{
				device->SetRenderTarget(0, _original_surface);
				_original_surface->Release();
			}
			_original_surface = 0;
			return RESULT_SUCCESS;
		}
		virtual type_result _onRenderModel(LPDIRECT3DDEVICE9 device, Camera& camera, Model& model);
		virtual LPCVOID _onRequestShaderCode(OUT type_int& size_of_binary) const = 0;
		virtual type_result _onSetShaderHandles(ShaderHandleSet& handles) = 0;

	protected:		
		void _clear(LPDIRECT3DDEVICE9 device)
		{
			device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
		}
		void _beginPass(int new_pass, LPDIRECT3DDEVICE9 device, RenderTarget& new_one)
		{
			device->SetRenderTarget(0, &new_one.getSurface());
			_clear(device);
			_effect->BeginPass(new_pass);
		}
		void _endFinalRenderTarget(RenderTargetSet& targets);
		void _endFinalRenderPass(RenderTargetSet& targets)
		{
			_endFinalRenderTarget(targets);
			_effect->EndPass();
		}
		type_result _beginFinalRenderPass(int new_pass, DX9& dx9)
		{
			_standByFinalRenderTarget(dx9);			
			
			_effect->BeginPass(new_pass);

			return RESULT_SUCCESS;
		}
		type_result _renderTargetVertex(LPDIRECT3DDEVICE9 device);
		void _endPassAndNotifyRenderTargetFilled(RenderTargetSet& targets)
		{
			_effect->EndPass();
			targets.notifyTargetFilled();
		}
		
		D3DXMATRIX _getOrthoMatrix()
		{
			D3DXMATRIX _instance;
			D3DXMatrixOrthoLH(&_instance, 2.0f, 2.0f, 0.0f, 1000.0f);
			return _instance;
		}
		type_result _standByFinalRenderTarget(DX9& dx9);

	private:				
		NECodeSet& _getTargetCodeSet() const;
		type_result _initializeShader(LPDIRECT3DDEVICE9 device);		
		type_result _bindHandles()
		{
			if( ! _effect)
			{
				KERNAL_ERROR("Shader가 생성되지 못했으므로 핸들을 바인딩 할 수 없습니다");
				return RESULT_TYPE_ERROR;
			}
			_onSetShaderHandles(_handles);


			//	main:
			for(int n=0; n < _handles.getSize() ;n++)
			{
				ShaderHandle& handle = _handles[n];
				if(handle.isTechniqueHandle())
					handle.getHandle() = _effect->GetTechniqueByName(handle.getName().toCharPointer());
				else
					handle.getHandle() = _effect->GetParameterByName(NULL, handle.getName().toCharPointer());				
			}


			//	post:
			if(NEResult::hasError(_handles.isValid()))
			{
				KERNAL_ERROR("핸들을 받아왔으나, 받아온 핸들이 잘못된것 같습니다");
				return RESULT_TYPE_ERROR;
			}

			return RESULT_SUCCESS;
		}
		type_result _updateBlendingStateToCamerasOne(LPDIRECT3DDEVICE9 device, Camera& camera);

	private:
		LPD3DXEFFECT _effect;
		ShaderHandleSet _handles;
		LPDIRECT3DSURFACE9 _original_surface;

	protected:
		static IDirect3DVertexBuffer9& _getRenderTargetVertex(LPDIRECT3DDEVICE9 device);
		static RenderTargetSet& _getRenderTargetSet(DX9& dx9) 
		{
			static RenderTargetSet _instance;
			if(	_instance.getSize() <= 0	&&	
				&dx9						&&
				dx9.getDevice()				)
			{
				_instance.create(2);
				_instance.push(RenderTarget());
				_instance.push(RenderTarget());
				_instance.initialize(dx9);	
			}

			return _instance; 
		}
	};
}