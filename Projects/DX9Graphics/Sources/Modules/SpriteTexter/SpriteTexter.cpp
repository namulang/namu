#include "SpriteTexter.hpp"
#include "../DXFont/DXFont.hpp"
#include "../Texture/Texture.hpp"

namespace DX9Graphics
{
	NEExportable::ModuleHeader& SpriteTexter::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T("SpriteTexter");
			_header.getDeveloper() = _T("kniz");
			_header.setRevision(1);
			_header.getComment() = _T("0번. 사용할 폰트\n1번. 출력할 문장\n2번. 가로정렬(0:왼쪽, 1:가운데, 2:오른쪽)\n3번. 세로정렬(4:가운데, 8:아래, 0:위)\n4: 빨강 색상값\n5: 초록 색상값 \n6: 파랑 색상값 \n7: Alpha값");
			_header.getVersion()  = _T("0.0.1a");
			_header.getReleaseDate() = _T("2013-10-05");
			_header.getModuleDependencies().create(0);
			_header.setMaxErrorCodeCount(1);
		}

		return _header;
	}

	type_result SpriteTexter::initialize()
	{
		SuperClass::initialize();

		NEKeyCodeSet& keyset = getKeySet();
		keyset.resize(keyset.getLength() + 8);
		keyset.push(NEModuleSelector());		//	0: 사용할 폰트
		keyset.push(NETStringKey());			//	1: 출력할 텍스트
		keyset.push(NEUByteKey());				//	2: 가로 정렬
		keyset.push(NEUByteKey());				//	3: 세로 정렬
		keyset.push(NEUByteKey(255));			//	4: ColorRed
		keyset.push(NEUByteKey(255));			//	5: ColorGreen
		keyset.push(NEUByteKey(255));			//	6: ColorBlue
		keyset.push(NEUByteKey(255));			//	7: ColorAlpha

		return RESULT_SUCCESS;
	}

	type_result SpriteTexter::execute()
	{		
		if( ! getFontSelector().getBinder().isBinded())
			_bindFont();
		return RESULT_SUCCESS;
	}

	NEObject& SpriteTexter::clone() const
	{
		return *(new SpriteTexter(*this));
	}

	type_result SpriteTexter::render(LPD3DXSPRITE sprite, const Texture& texture)
	{
		if( ! sprite)
		{
			ALERT_ERROR("스프라이트 바인딩 실패");
			return RESULT_TYPE_ERROR;
		}
		if( ! &texture)
		{
			ALERT_ERROR("텍스쳐가 잘못되었습니다.")
			return RESULT_TYPE_ERROR;
		}
		NEModuleBinder& binder = getFontSelector().getBinder();
		if( ! binder.isBinded())
			return RESULT_TYPE_WARNING;

		LPD3DXFONT fnt = ((DXFont&) binder.getBinded()).getFont();
		if( ! fnt)
		{
			ALERT_ERROR("폰트 바인딩 실패");
			return RESULT_TYPE_ERROR;
		}
		
		
		//	main:
		DWORD flag = getHorizontalAlignment() | getVerticalAlignment();
		fnt->DrawText(sprite, getText().toCharPointer(), -1, &_createFontArea(texture), flag, createColor());
		
		//	post:
		return RESULT_SUCCESS;
	}

	type_result SpriteTexter::_bindFont()
	{
		NEModuleSelector& sel = getFontSelector();
		while(NEModule* itr = &sel.getModule())
		{
			static type_code code = Kernal::getInstance().getModuleManager()
				.getModule(DXFont().getHeader()).getScriptCode();
			if(itr->getScriptCode() == code)
			{
				sel.bind();
				sel.initializeReferingPoint();
				return RESULT_SUCCESS;
			}
		}

		ALERT_WARNING("폰트 바인딩 실패");
		return RESULT_TYPE_WARNING;
	}

	RECT SpriteTexter::_createFontArea(const Texture& texture)
	{
		type_int	hw = texture.getWidthOfOneFrame() / 2,
					hh = texture.getHeightOfOneFrame() / 2;
		RECT to_return = {-hw, -hh, hw, hh};
		
		return to_return;
	}

}