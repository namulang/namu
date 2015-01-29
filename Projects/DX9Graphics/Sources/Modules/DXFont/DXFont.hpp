#pragma once

#include "../Resource/Resource.hpp"

namespace DX9Graphics
{
	class NE_DLL DXFont : public Resource
	{
	public:
		typedef DXFont ThisClass;
		typedef Resource SuperClass;

	public:
		NETArgument<NETStringKey>	arg_name;
		NETArgument<NEUByteKey>		arg_charset;
		NETArgument<NEUIntKey>		arg_width;
		NETArgument<NEUIntKey>		arg_height;
		NETArgument<NEUIntKey>		arg_weight;
		NETArgument<NEBooleanKey>	arg_italic;

	protected:
		virtual type_result _onFetchModule()
		{
			arg_name.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_charset.setValue(DEFAULT_CHARSET);
			arg_charset.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_width.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_height.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_weight.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_italic.setPurposeLimitation(NEArgumentBase::READ_BY);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_name);
			tray.push(arg_charset);
			tray.push(arg_width);
			tray.push(arg_height);
			tray.push(arg_weight);
			tray.push(arg_italic);

			return RESULT_SUCCESS;
		}
		virtual type_result _onExecute()
		{
			if (!_font)
				return initializeResource();

			return RESULT_SUCCESS;
		}

	public:
		DXFont() : Resource(), _font(0) {}
		DXFont(const ThisClass& src) : SuperClass(src), _font(0)
		{
			_assign(src);
		}

	public:
		DXFont& operator=(const ThisClass& src)
		{
			if(this == &src) return *this;

			SuperClass::operator=(src);			

			return _assign(src);	//	_font는 할당하지 않는다.
		}

	public:		
		const LPD3DXFONT getFont() const { return _font; }
		LPD3DXFONT getFont() { return _font; }

	public:
		virtual type_result initializeResource();
		virtual type_result releaseResource()
		{
			SuperClass::releaseResource();

			if(_font)
				_font->Release();
			_font = 0;
			return RESULT_SUCCESS;
		}

	public:
		virtual NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;

			if (_header.isValid() != RESULT_NOTHING)
			{
				_header.getName() = _T("DXFont");
				_header.getDeveloper() = _T("kniz");
				_header.setRevision(1);
				_header.getComment() = "SpriteTexter Module에서 사용할 Font를 정의합니다.";

				_T("0번. DX9\n1번. 폰트의 이름\n2번. 캐릭터셋(0:ANSI, 1:기본, 129:한글, 128:SHIFT일본, 136:중국BIG5\n3번. 폭\n4번. 높이(보통 폭의 2배)\n5번. 두께(100 ~ 400-보통- ~ 900)\n6번. 이탤릭?");
				_header.getVersion() = _T("0.0.1a");
				_header.getReleaseDate() = _T("2013-10-05");
				NETStringSet& args = _header.getArgumentsComments();
				args.create(6);
				args.push("폰트의 이름");
				args.push("문자 캐릭터셋\n0: ANSI\t1:기본\t129:한글\n128:SHIFT일본\t136:중국BIG5");
				args.push("Width\n문자 한 글자 당 폭");
				args.push("Height\n문자 한글자당 높이를 말합니다. 보통 폭의 2배 입니다.");
				args.push("Weight\n문자의 두께입니다. 400을 기준으로 100이면 얇은 글씨가, 900이면 두꺼운 글씨가 나옵니다.");
				args.push("Italic\n이탤릭으로 출력하는지 정합니다.");
			}

			return _header;
		}

	public:
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}

	private:
		ThisClass& _assign(const ThisClass& source)
		{
			if (this == &source) return *this;

			arg_name = source.arg_name;
			arg_charset = source.arg_charset;
			arg_width = source.arg_width;
			arg_height = source.arg_height;
			arg_weight = source.arg_weight;
			arg_italic = source.arg_italic;

			return *this;
		}

	private:
		LPD3DXFONT _font;

	public:
		static const NECodeSet& getModuleScriptCodes()
		{
			NECodeType type(NECodeType::MODULE_SCRIPT);
			static NECodeSet _instance(type);

			if(_instance.getSize() <= 0)
			{
				_instance.create(1);
				_instance.push(NEExportable::Identifier("DXFont.kniz"));
			}

			return _instance;
		}
	};
}