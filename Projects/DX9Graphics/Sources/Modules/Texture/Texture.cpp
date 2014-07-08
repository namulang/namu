#include "Texture.hpp"
#include "define.hpp"

namespace DX9Graphics
{
	type_result Texture::dock(Model& model)
	{
		if( ! _texture)
		{
			ALERT_WARNING("텍스쳐가 로드되지 않아서 Dock 할 수 없습니다.");
			return RESULT_TYPE_WARNING;
		}
		DX9& dx9 = getBinded();
		if( ! &dx9)
		{
			ALERT_ERROR("DX9를 바인딩 실패");
			return RESULT_TYPE_ERROR;
		}
		LPDIRECT3DDEVICE9 device = dx9.getDevice();	

		device->SetTexture(0, _texture);

		return RESULT_SUCCESS;
	}

	type_result Texture::execute()
	{
		if( ! isEnable()) return RESULT_SUCCESS;
		if(isResourceInitialized())
			return RESULT_SUCCESS | RESULT_ABORT_ACTION;

		return initializeResource();
	}

	const NEExportable::ModuleHeader& Texture::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T(_NAME);
			_header.getDeveloper() = _T(_DEVELOPER);
			_header.setRevision(_REVISION);
			_header.getComment() = _T(_COMMENT);
			_header.getVersion()  = _T(_VERSION);
			_header.getReleaseDate() = _T(_DATE);
			_header.getModuleDependencies().create(_DEPENDENCIES_COUNT);
			_header.setMaxErrorCodeCount(1);
		}

		return _header;
	}

	type_result Texture::initializeResource()
	{
		DX9& dx9 = getBinded();
		if( ! &dx9)
		{
			ALERT_ERROR("DX9를 바인딩 실패");
			return RESULT_TYPE_ERROR;
		}
		LPDIRECT3DDEVICE9 device = dx9.getDevice();
		ThisClass::releaseResource();
		SuperClass::initializeResource();


		//	main:
		D3DXIMAGE_INFO image_info;
		HRESULT result = D3DXCreateTextureFromFileEx(
			device, getPath().toCharPointer(),
			D3DX_DEFAULT,			D3DX_DEFAULT,	D3DX_DEFAULT,	0,	
			D3DFMT_DXT1,			D3DPOOL_MANAGED,D3DX_DEFAULT,	D3DX_DEFAULT,
			createColorKey(),	&image_info,	NULL,			&_texture);



		//	post:
		//		텍스쳐 크기 검사:
		if( ! _isTextureSizePowerOf2(image_info))
		{
			ALERT_WARNING("텍스쳐가 2의 승수가 아닙니다.\n그대로 끝내기는 뭐하니까 임시방편으로 NON-2-POWER Flag로 처리합니다.\n단, MipMap이 1이므로 성능이 하락될꺼예요:\n\t이미지의 (Width, Height) = (%d, %d)", image_info.Width, image_info.Height);
			
			SuperClass::initializeResource();

			result = D3DXCreateTextureFromFileEx(
				device, getPath().toCharPointer(),
				D3DX_DEFAULT_NONPOW2,	D3DX_DEFAULT_NONPOW2,	1,				0,
				D3DFMT_DXT1,			D3DPOOL_MANAGED,		D3DX_DEFAULT,	D3DX_DEFAULT,
				createColorKey(),	0,						NULL,			&_texture);

			if(FAILED(result))
			{
				ALERT_ERROR("텍스쳐 2의 비승수 로드 실패\n이궁. 임시방편조차 실패했네요. 아마도 그래픽카드가 후져서 지원을 안하나봅니다\n이젠 저도 빼도 박도 못해요ㅜㅜ\n바바~^^");
				return RESULT_TYPE_ERROR;
			}
		}
		if(FAILED(result))
		{
			ALERT_ERROR("텍스쳐 객체 생성실패:\n2의 승수는 아닙니다만, 생성에 실패했습니다.\n\t에러코드 : %x", result);
			return RESULT_TYPE_ERROR;
		}
		//		텍스쳐의 정보 보존:
		_texture->GetLevelDesc(0, &_texture_description);
		return _setResourceRetrieved();
	}

	type_uint Texture::getWidth() const
	{
		if( ! _texture)
		{
			ALERT_WARNING("텍스쳐가 없는데 너비를 알수가 없지요");
			return 0;
		}

		return _texture_description.Width;
	}

	type_uint Texture::getHeight() const
	{
		if( ! _texture)
		{
			ALERT_WARNING("텍스쳐가 없는데 높이를 알수가 없지요");
			return 0;
		}

		return _texture_description.Height;
	}

	D3DSURFACE_DESC Texture::getTextureDescription() const
	{
		return _texture_description;
	}

	type_ubyte Texture::getDefaultColorKeyRed()
	{
		NEINIManager& ini = Kernal::getInstance().getINIManager();
		NETString bucket = _DEFAULT_COLORKEY_RED;
		NEExportable::Identifier me(_NAME, _DEVELOPER, _REVISION);
		if(NEResult::hasError(ini.readModuleIniString(me, _COLORKEY_RED_KEYNAME, bucket)))
			ini.writeModuleIniString(me, _COLORKEY_RED_KEYNAME, bucket);

		return bucket.toInt();
	}

	type_ubyte Texture::getDefaultColorKeyGreen()
	{
		NEINIManager& ini = Kernal::getInstance().getINIManager();
		NETString bucket = _DEFAULT_COLORKEY_GREEN;
		NEExportable::Identifier me(_NAME, _DEVELOPER, _REVISION);
		if(NEResult::hasError(ini.readModuleIniString(me, _COLORKEY_GREEN_KEYNAME, bucket)))
			ini.writeModuleIniString(me, _COLORKEY_GREEN_KEYNAME, bucket);

		return bucket.toInt();
	}

	type_ubyte Texture::getDefaultColorKeyAlpha()
	{
		NEINIManager& ini = Kernal::getInstance().getINIManager();
		NETString bucket = _DEFAULT_COLORKEY_ALPHA;
		NEExportable::Identifier me(_NAME, _DEVELOPER, _REVISION);
		if(NEResult::hasError(ini.readModuleIniString(me, _COLORKEY_ALPHA_KEYNAME, bucket)))
			ini.writeModuleIniString(me, _COLORKEY_ALPHA_KEYNAME, bucket);

		return bucket.toInt();
	}

	type_ubyte Texture::getDefaultColorKeyBlue()
	{
		NEINIManager& ini = Kernal::getInstance().getINIManager();
		NETString bucket = _DEFAULT_COLORKEY_BLUE;
		NEExportable::Identifier me(_NAME, _DEVELOPER, _REVISION);
		if(NEResult::hasError(ini.readModuleIniString(me, _COLORKEY_BLUE_KEYNAME, bucket)))
			ini.writeModuleIniString(me, _COLORKEY_BLUE_KEYNAME, bucket);

		return bucket.toInt();
	}

}