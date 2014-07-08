#pragma once

#include "../ShaderProgram/ShaderProgram.hpp"

namespace DX9Graphics
{
	class NE_DLL MosaicProgram : public ShaderProgram
	{
	public:
		typedef MosaicProgram ThisClass;
		typedef ShaderProgram SuperClass;

	public:
		friend class DX9;

	public:
		type_uint& getMosaicPrecision()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_uint&>(casted->getMosaicPrecision());
		}
		const type_uint& getMosaicPrecision() const
		{
			const NEKey& key = getKeySet()[4];
			if( ! key.isSubClassOf(NEType::NEUINT_KEY))
			{
				ALERT_ERROR("4번키는 NEUINT_KEY여야 합니다");
				type_uint* nullpoint = 0;
				return *nullpoint;
			}

			const NEUIntKey& target = static_cast<const NEUIntKey&>(key);
			return target.getValue();
		}

	public:
		virtual type_result initialize()
		{
			SuperClass::initialize();

			NEKeyCodeSet& keyset = getKeySet();
			keyset.resize(keyset.getSize() + 1);			
			return keyset.push(NEUIntKey(30));
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
		virtual const NEExportable::ModuleHeader& getHeader() const;

	private:
		virtual type_result _onRender(DX9& dx9, Camera& camera)
		{
			if( ! isEnable()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;		


			//	main:
			//		준비:
			LPDIRECT3DDEVICE9 device = dx9.getDevice();
			//		핸들로 값 전달:
			_updateMosaicPrecision();	//	텍스쳐크기가 곧 Blur레벨이 된다.
			RenderTargetSet& targets = _getRenderTargetSet(dx9);
			ShaderHandleSet& handles = getShaderHandleSet();
			if(targets.getSize() <= 0)
			{
				ALERT_ERROR("DX9 바인딩 실패로 렌더타겟을 생성하지 못했습니다.");
				return RESULT_TYPE_ERROR;
			}
			//			Matrix치환:
			D3DXMATRIX new_w, new_v, new_p = _getOrthoMatrix();
			D3DXMatrixIdentity(&new_w);
			D3DXMatrixLookAtLH(&new_v, &D3DXVECTOR3(0, 0, -1), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 1, 0));
			device->SetTransform(D3DTS_WORLD, &new_w);
			device->SetTransform(D3DTS_VIEW, &new_v);
			device->SetTransform(D3DTS_PROJECTION, &new_p);
			//			임시 렌더타겟 준비:
			ID3DXEffect& effect = getEffect();


			//	main:
			//			셰이더 준비:
			device->BeginScene();
			effect.SetTechnique(handles[0].getHandle());
			effect.Begin(NULL, 0);
			//		0패스: 모자이크
			_beginFinalRenderPass(0, dx9);
			device->SetTexture(0, &targets.getFilledTarget().getTexture());
			_renderTargetVertex(device);
			_endFinalRenderPass(targets);


			//	post:
			//		복구:
			effect.End();
			device->EndScene();
			return RESULT_SUCCESS;
		}
		virtual LPCVOID _onRequestShaderCode(OUT type_int& size_of_binary) const;
		virtual type_result _onSetShaderHandles(ShaderHandleSet& handles)
		{
			handles.release();
			handles.create(2);
			handles.push(ShaderHandle(_T("Tech"), true));			
			handles.push(ShaderHandle(_T("mosaic_precision")));	//	모자이크 정밀도.		

			return RESULT_SUCCESS;
		}

	private:		
		type_result _updateMosaicPrecision()
		{
			type_uint& precision = getMosaicPrecision();
			if( ! &getEffect())
			{
				ALERT_ERROR("이펙트가 초기화 되어있지 않아서 핸들로 값을 넘길 수 없습니다.");
				return RESULT_TYPE_ERROR;
			}
			ShaderHandle& handle = getShaderHandleSet()[1];
			if( ! &handle || handle.isTechniqueHandle())
			{
				ALERT_ERROR("잘못된 핸들값입니다.");
				return RESULT_TYPE_ERROR;
			}

			getEffect().SetInt(handle.getHandle(), static_cast<type_int>(precision));
			
			return RESULT_SUCCESS;
		}
	};
}