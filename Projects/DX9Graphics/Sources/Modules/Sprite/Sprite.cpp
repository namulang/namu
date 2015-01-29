#include "Sprite.hpp"
#include "../DX9/DX9.hpp"
#include "../Model/Model.hpp"
#include "../Texture/Texture.hpp"
#include "../SpriteTexter/SpriteTexter.hpp"

namespace DX9Graphics
{
	type_result Sprite::dock(Model& model)
	{
		//	pre:
		if( ! isEnable()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		//		DX9 바인딩:
		DX9& dx9 = DX9::getInstancedDX();
		if( ! &dx9)
			return ALERT_ERROR(" : 디바이스바인딩실패로중지");

		if( ! &model)
			return ALERT_ERROR("모델이 없습니다.");

		Texture& texture = model.getTexture();
		if( ! &texture)		
			return ALERT_WARNING("텍스쳐가 없습니다.");


		//	main:
		LPDIRECT3DDEVICE9 device = dx9.getDevice();		

		return _renderSprite(model, texture, device);
	}
}