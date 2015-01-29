#include "SpriteTexter.hpp"
#include "../DXFont/DXFont.hpp"
#include "../Texture/Texture.hpp"

namespace DX9Graphics
{
	type_result SpriteTexter::render(LPD3DXSPRITE sprite, const Texture& texture)
	{
		if( ! sprite)
			return ALERT_ERROR("스프라이트 바인딩 실패");

		if( ! &texture)
			return ALERT_ERROR("텍스쳐가 잘못되었습니다.");

		DXFont& font = cast(arg_validator.getValue().getModule());
		if( ! &font)
			return RESULT_TYPE_WARNING;
		LPD3DXFONT fnt = font.getFont();
		if( ! fnt)
			return ALERT_ERROR("폰트 바인딩 실패");


		//	main:
		DWORD flag = arg_horizontal_alignment.getValue() | arg_vertical_alignment.getValue();
		fnt->DrawText(sprite, arg_text.getValue().toCharPointer(), -1, & _createFontArea(texture), flag, createColor());

		//	post:
		return RESULT_SUCCESS;
	}

	RECT SpriteTexter::_createFontArea(const Texture& texture)
	{
		type_int	hw = texture.getWidthOfOneFrame() / 2,
					hh = texture.getHeightOfOneFrame() / 2;
		RECT to_return = {-hw, -hh, hw, hh};
		
		return to_return;
	}
}