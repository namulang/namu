#pragma once

#include "../../Commons/Templates/TValidator/TValidator.hpp"
#include "../DXFont/DXFont.hpp"

namespace DX9Graphics
{
	class Texture;

	class NE_DLL SpriteTexter : public TValidator<DXFont>
	{
	public:
		typedef SpriteTexter ThisClass;
		typedef TValidator<DXFont> SuperClass;

	public:
		enum Alignment
		{
			AV_TOP = DT_TOP,
			AV_CENTER = DT_VCENTER,
			AV_BOTTOM = DT_BOTTOM,
			AH_LEFT = DT_LEFT,
			AH_CENTER = DT_CENTER,
			AH_RIGHT = DT_RIGHT
		};

	public:
		NETArgument<NETStringKey>	arg_text;
		NETArgument<NEUByteKey>		arg_horizontal_alignment;
		NETArgument<NEUByteKey>		arg_vertical_alignment;
		NETArgument<NEUByteKey>		arg_red;
		NETArgument<NEUByteKey>		arg_green;
		NETArgument<NEUByteKey>		arg_blue;
		NETArgument<NEUByteKey>		arg_alpha;

	protected:
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			SuperClass::_onFetchArguments(tray);

			tray.push(arg_text);
			tray.push(arg_horizontal_alignment);
			tray.push(arg_vertical_alignment);
			tray.push(arg_red);
			tray.push(arg_green);
			tray.push(arg_blue);
			tray.push(arg_alpha);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchModule()
		{
			arg_text.setPurposeLimitation(NEArgumentBase::READ_BY);			
			arg_horizontal_alignment.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_vertical_alignment.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_red.setValue(255);
			arg_red.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_green.setValue(255);
			arg_green.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_blue.setValue(255);
			arg_blue.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_alpha.setValue(255);
			arg_alpha.setPurposeLimitation(NEArgumentBase::READ_BY);

			return RESULT_SUCCESS;
		}

		virtual type_result _onExecute()
		{
			return RESULT_SUCCESS;
		}

	public:		
		type_uint createColor() const
		{
			return D3DCOLOR_RGBA(arg_red.getValue(), arg_green.getValue(), arg_blue.getValue(),
				arg_alpha.getValue());
		}

	public:
		virtual NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;

			if (_header.isValid() != RESULT_NOTHING)
			{
				_header.getName() = _T("SpriteTexter");
				_header.getDeveloper() = _T("kniz");
				_header.setRevision(1);
				_header.getComment() =
					"Sprite에 출력될 글 정보를 나타냅니다.\n"
					"출력하게될 문장과, 사용할 폰트 및 정렬과 관련된 데이터를 간직하고 있습니다.\n"
					"이러한 SpriteTexter가 출력되려면 Model Module에서 참조해야 합니다";
				_header.getVersion() = _T("0.0.1a");
				_header.getReleaseDate() = _T("2013-10-05");
				NETStringSet& args = _header.getArgumentsComments();
				args.create(8);
				args.push("사용할 DXFont 모듈");
				args.push("출력할 글");
				args.push("가로 정렬\n0:왼쪽	1:가운데	2:오른쪽");
				args.push("세로 정렬\n0:위		4:가운데	8:아래");
				args.push("빨강 성분\n출력할 글의 빨강 색상값. 0이면 빨강 성분 없으며, 최대값은 255 입니다.");
				args.push("파랑 성분\n출력할 글의 파랑 색상값. 0이면 빨강 성분 없으며, 최대값은 255 입니다.");
				args.push("초록 성분\n출력할 글의 초록 색상값. 0이면 빨강 성분 없으며, 최대값은 255 입니다.");
				args.push("불투명도 성분\n출력할 글의 불투명도. 0이면 투명해 눈에 보이지 않습니다. 최대값은 255 입니다.");
			}

			return _header;
		}

	public:
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}

	public:
		type_result render(LPD3DXSPRITE sprite, const Texture& texture);

	private:
		RECT _createFontArea(const Texture& texture);

	public:
		static const NECodeSet& getModuleScriptCodes()
		{
			NECodeType type(NECodeType::MODULE_SCRIPT);
			static NECodeSet instance(type);

			if(instance.getSize() <= 0)
			{
				instance.create(1);
				instance.push(NEExportable::Identifier("SpriteTexter.kniz"));
			}

			return instance;
		}
	};
}