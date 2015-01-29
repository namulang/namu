#include "RenderTarget.hpp"
#include "../../../Modules/DX9/DX9.hpp"

static const type_float _DEFAULT_WIDTH_RATE	 = 0.5;
static const type_float _DEFAULT_HEIGHT_RATE = 0.5;

namespace DX9Graphics
{
	type_result RenderTarget::_initializeTexture(DX9& dx9, type_float width_rate, type_float height_rate)
	{
		LPDIRECT3DDEVICE9 device = dx9.getDevice();
		if( ! device)
			return KERNAL_ERROR("디바이스가 없으므로 렌더타켓의 텍스쳐를 생성할 수 없습니다.");

		const DX9::PresentParameters& param = dx9.getPresentParameters();
		type_uint	render_target_w = static_cast<type_uint>(param.BackBufferWidth * width_rate),
			render_target_h = static_cast<type_uint>(param.BackBufferHeight * height_rate);

		HRESULT result = device->CreateTexture( render_target_w, render_target_h, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &_texture, NULL);				
		if(FAILED(result))
			return KERNAL_ERROR("렌더타겟 텍스쳐 생성 실패! \n\t결과 코드: %x", result);

		return RESULT_SUCCESS;
	}


	type_result RenderTarget::_initializeSurface()
	{
		if( ! _texture)
			return KERNAL_ERROR("텍스쳐가 생성 실패했으므로, 서페이스를 생성할 수 없습니다.");

		_texture->GetSurfaceLevel(0, &_surface);

		return RESULT_SUCCESS;
	}

	type_result RenderTarget::_writeDefaultWidthHeightRatesToINI()
	{
		NEINIManager& ini = Kernal::getInstance().getINIManager();

		ini.write("RenderTarget", "WidthRate", _DEFAULT_WIDTH_RATE);
		ini.write("RenderTarget", "HeightRate", _DEFAULT_HEIGHT_RATE);

		return RESULT_SUCCESS;
	}

	const NEFloatSet& RenderTarget::_getWidthHeightRates()
	{
		static NEFloatSet _instance;
		if(_instance.getSize() <= 0)
		{
			type_float	width_rate = _readRateFromINI("WidthRate"),
				height_rate = _readRateFromINI("HeightRate");

			if(	width_rate <= 0.0	&&
				height_rate <= 0.0	)
			{
				width_rate = _DEFAULT_WIDTH_RATE;
				height_rate = _DEFAULT_HEIGHT_RATE;
				_writeDefaultWidthHeightRatesToINI();
			}

			_instance.create(2);
			_instance.push(width_rate);
			_instance.push(height_rate);
		}		

		return _instance;
	}
}