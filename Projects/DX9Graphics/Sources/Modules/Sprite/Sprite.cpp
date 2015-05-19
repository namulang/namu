#include "Sprite.hpp"
#include "../DX9/DX9.hpp"
#include "../Model/Model.hpp"
#include "../Texture/Texture.hpp"
#include "../SpriteTexter/SpriteTexter.hpp"

namespace DX9Graphics
{
	D3DXMATRIX Sprite::adj;
	D3DXMATRIX Sprite::adj_for_font;

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

	type_result Sprite::_initializeSprite()
	{
		//	pre:
		ThisClass::releaseResource();

		DX9& dx9 = DX9::getInstancedDX();
		if( ! &dx9)
			return ALERT_WARNING("아직DX9가Bind 되지않은듯합니다.");

		LPDIRECT3DDEVICE9 device = dx9.getDevice();


		//	post:
		if(FAILED(D3DXCreateSprite(device, &_sprite)))
			return ALERT_WARNING("스프라이트 생성을 실패했습니다.");

		return RESULT_SUCCESS;
	}

	type_result Sprite::_renderSprite(Model& model, Texture& texture, LPDIRECT3DDEVICE9 device)
	{
		//	pre:
		//		보정 매트릭스:
		//			왜 이걸 사용하는가?:
		//				이유는 모르겠으나 D3DXSPRITE를 OBJECTSPACE | NO BILLBOARD로 출력하면 X-AXIS FLIP
		//				되어서 출력된다. 제대로된 원인을 찾지 못해서 RotateX(180degree)로 구해낸 행렬을
		//				World에 곱하는 식으로 땜방하였다.
		//
		//			World에 곱하는 공식:
		//
		//					새로운 Sprite용 행렬 = 보정행렬 * 주어진 World 행렬
		//
		//				보정행렬을 앞에다 곱해야 한다. 뒤에다 곱할 경우, 보정행렬은 부모World행렬 위치에 
		//				놓여지게되므로 보정행렬이 180도 회전해 있기 때문에 주어진World행렬의 Z의 부호가 
		//				반대로 작용하게 된다.
		//
		//			Scaling 보정 매트릭스:
		//				D3DXSPRITE는 내부에서 PLATE (정점 4개의 평면 모델링)의 크기를 주어진 Texture의 px
		//				만큼 주는 것 같다. 예를들어 Sample.bmp의 크기가 50x50이면 화면상에는 작은 그림이지만
		//				Modeling 데이터로써의 50x50은 상당히 큰 물체에 속하게 된다.
		//				이렇게 큰 물체는 깊이감이 줄어들 수 밖에 없으며, 정상적인 깊이감을 주기 위해서는 
		//				프레임당 500정도로 Z값을 움직여야 할 정도로 문제가 심각해진다.
		//				따라서, Model의 Scaling을 1이 아닌 축소값(예를 들면 0.2) 정도로 할당하면 가능하다.
		//
		//			그런데 왜 Scaling 보정 매트릭스가 나오게 되었는가:
		//				하지만 이와 같은 문제는 계층구조에서 문제를 낳게 되는데, 상위 계층의 Scaling이 0.8
		//				일 경우, 공식 (1),
		//					
		//					실제 하위계층 크기(0.64) = 주어진 하위계층 크기(0.8) * 상위계층(0.8)
		//
		//				로, 계층이 깊어지면 깊어질 수록 점점 그 크기가 가속화 되기 때문이다.
		//				이 문제를 해결하기 위한 방법은 크게 3가지가 예상된다.
		//
		//					1. Model에서 Rotate, Trans Scale 중 특정 요소는 하위계층에게 반영되지 않도록
		//					막는 Flag를 제공한다.
		//						:	간단하나, 잘못된 구현방법이다. 추가적으로 Flag가 늘게되며 복잡해진다.
		//
		//					2. 물체X를 계층구조에 넣을때 넣기전의 시각적 상태가 유지되도록, 상위계층의 
		//					크기의 역수를 미리 곱해준다. (위의 예를 들면, 최종적으로 삽입되는 하위계층의 
		//					크기(1.0) = 하위 계층의 크기(0.8) * 상위계층의크기의 역수(1.25). 이렇게 하면,
		//					위의 공식(1)에 대입시, 실제 하위계층의 크기는 넣기전의 크기(0.8)이 나오게 된다.
		//						:	가장 올바른 방법이나, 3가지 방법중 구현이 가장 어렵다.
		//							이를 제대로 구현하려면 NENodeCodeSet에 push 되는 타이밍을 소유자인 Module
		//							이 Catch 할 수 있어야 하기 때문이다. (물론 다른 꼼수를 쓸수도 있겠지만)
		//
		//					3. Plate를 렌더링한다는 것은 대개 위에서 언급한 Scaling 문제를 겪는다는 걸 의미한다.
		//					그렇다면 아예 모든 Plate에 동일한 Scaling 행렬을 곱해버리면 되지 않을까
		//						:	비록 정석은 아니나, 간편하면서도 현재의 요구사항을 나름 충족시킨다.
		//				
		//				따라서, 여기서는 절충안인 3번을 따라서 Scaling 보정행렬을 생성해 곱한다. (보정치를
		//				정하는 방식은 해상도나 텍스쳐의 크기 사람의 주관에 따라서 천차만별이며 기준을 명확히
		//				세우기 곤란한 관계로 임의로 다음의 기준을 세워서 결정하였다.
		//					
		//					1.	카메라와 물체의 거리가 약 5 이며,
		//					2.	카메라의 시점이 정 중앙일때, Prespective로,
		//					3.	fov가 90, aspect 1.333 일때의 크기가 원본과 비슷하게 나오는 값 0.02로 정한다
		//
		//			폰트 보정 매트릭스:
		//				폰트의 경우 Z-Fighting이 검출된다. 이를 막기 위해서 보정매트릭스(Translation(0,0,-0.5))
		//				를 사용하여 Sprite위로 약간 올린다. 폰트 보정매트릭스는 "World보정매트릭스" 뒤에
		//				곱해지게 되므로 최종 공식은 다음과 같다.
		//				
		//						=	World보정행렬 * Font보정행렬 * 주어진World행렬
		//			
		//			문제점:
		//				World보정행렬을 앞에다 곱해줘야 제대로 동작하게 된다.
		//				뒤에다 곱했을때는 스케일이 뻥튀기되는 에러도 사라졌고, 폰트도 제대로 
		//				출력이 되는 것 같다. X축의 양의 방향과 회전방향도 제대로 동작하는 걸로 보인다.

		static type_bool is_adj_initialized = false;
		if( ! is_adj_initialized)
		{
			D3DXMATRIX adjr, adjs;
			D3DXMatrixRotationX(&adjr, D3DX_PI);
			D3DXMatrixScaling(&adjs, 0.02f, 0.02f, 0.02f);
			adj = adjs * adjr;
			D3DXMatrixTranslation(&adj_for_font, 0, 0, -0.5f);
			is_adj_initialized = true;
		}
		if( ! _sprite)
			_initializeSprite();


		DX9& dx9 = DX9::getInstancedDX();

		//	main:
		if(	&_sprite	&& 
			&dx9		)
		{
			D3DXMATRIX e;
			D3DXMatrixIdentity(&e);
			dx9.getDevice()->SetTransform(D3DTS_WORLD, &e);
			_sprite->Begin(D3DXSPRITE_DONOTMODIFY_RENDERSTATE | D3DXSPRITE_OBJECTSPACE);
			//	제대로된 방법을 찾지 못해서 이런식으로 땜방하였다.
			D3DXMATRIX world = /*adj **/ model.getWorldMatrix();
			
			_sprite->SetTransform(&world);
			/*
				Draw의메소드인자설명:
					1	g_pTexture	:	텍스쳐
					2	RECT		:	텍스쳐에서실제로사용할구역. UV좌표가정규화된0~1의값이라면이건텍스쳐자체를의미한다고보면된다.
					3	VECTOR3		:	RECT에서설정한구역에서어느점을텍스쳐의중심점으로삼을것인지를지정한다.
					4	VECTOR3		:	SetTransform에서설정한Translation Vector를지정한다.
					5	DWORD		:	색상값.
			*/
			RECT source_rect = texture.createSourceRect();
			type_uint	width = texture.getWidthOfOneFrame(),
						height = texture.getHeightOfOneFrame();
			D3DXVECTOR3 center_of_texture(width / 2.0f, height / 2.0f, 1.0f),
						world_translation(world._41, world._42, world._43);			

			_sprite->Draw(&texture.getTexture(), &source_rect, &center_of_texture, &world_translation, model.createColor());
			if(model.arg_texter_binder.isEnable())
			{
				SpriteTexter& texter = model.getTexter();
				Texture& texture = model.getTexture();
				if (!&texter ||
					!&texture)
				{
					ALERT_WARNING(" : Texter나 Texture 둘중 하나가 바인딩이 안되어 있습니다.");
					goto POST;	//	same as that break if blockstatements.
				}
					

				world *= adj_for_font;
				_sprite->SetTransform(&world);	//	Texter를 위해서 미리 폰트보정행렬을 Set한다.

				texter.render(_sprite, texture);
			}

		POST:
			_sprite->End();

			/*
				충돌 Volume Sphere는 Scale을 평균을 내어 계산하며, 계층구조를 고려하지 않는다.
			*/
			D3DXMATRIX sphere_scale;
			type_float avg_scale = (model.arg_scale_x.getValue() + model.arg_scale_y.getValue()) / 2.0f;
			D3DXMatrixScaling(&sphere_scale, avg_scale, avg_scale, avg_scale);

			sphere_scale = sphere_scale * model.getWorldMatrix();

			_renderSphere(dx9.getDevice(), sphere_scale);
		}

		return RESULT_SUCCESS;		
	}
}