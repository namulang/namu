#include "DXFont.hpp"
#include "../DX9/DX9.hpp"

namespace DX9Graphics
{
	type_result DXFont::initializeResource()
	{
		DX9& dx9 = DX9::getInstancedDX();
		LPDIRECT3DDEVICE9 dev = &dx9 ? dx9.getDevice() : 0;
		if( ! dev)
			return ALERT_ERROR("dx9 바인딩 실패로 중지");


		//	main:
		if (!_font)
		{
			D3DXFONT_DESC desc;
			_tcscpy_s(desc.FaceName, LF_FACESIZE, arg_name.getValue().toCharPointer());
			desc.CharSet = arg_charset.getValue();
			desc.Width = arg_width.getValue();
			desc.Height = arg_height.getValue();
			desc.Weight = arg_weight.getValue();
			desc.Quality = DEFAULT_QUALITY;
			desc.MipLevels = 1;
			desc.Italic = arg_italic.getValue() ? 1 : 0;
			desc.OutputPrecision = OUT_DEFAULT_PRECIS;
			desc.PitchAndFamily = FF_DONTCARE;

			D3DXCreateFontIndirect(dev, &desc, &_font);

			return SuperClass::initializeResource();
		}

		return RESULT_SUCCESS;
	}
}