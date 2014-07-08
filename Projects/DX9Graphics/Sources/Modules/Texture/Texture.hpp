#pragma once

#include "../FileResource/FileResource.hpp"

namespace DX9Graphics
{
	class NE_DLL Texture : public FileResource
	{
	public:
		typedef FileResource SuperClass;
		typedef Texture ThisClass;

	public:
		Texture()
			: _texture(0)
		{
			ThisClass::releaseResource();
		}
		~Texture()
		{
			ThisClass::releaseResource();
		}

	public:
		IDirect3DTexture9& getTexture()
		{
			return *_texture;
		}
		const IDirect3DTexture9& getTexture() const
		{
			return *_texture;
		}
		type_ubyte& getTransparentColorRed()
		{
			const ThisClass* consted_this = this;

			return const_cast<type_ubyte&>(consted_this->getTransparentColorRed() );
		}
		const type_ubyte& getTransparentColorRed() const
		{
			const NEKey& somekey = getKeySet()[2];
			if( ! somekey.isSubClassOf(NEType::NEUBYTE_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 2번키가 NEUBYTE_KEY여야 합니다.");
				const type_ubyte* nullpoint = 0;
				return *nullpoint;
			}

			return (static_cast<const NEUByteKey&>(somekey)).getValue();
		}
		type_ubyte& getTransparentColorGreen()
		{
			const ThisClass* consted_this = this;

			return const_cast<type_ubyte&>(consted_this->getTransparentColorGreen() );
		}
		const type_ubyte& getTransparentColorGreen() const
		{
			const NEKey& somekey = getKeySet()[3];
			if( ! somekey.isSubClassOf(NEType::NEUBYTE_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 3번키가 NEUBYTE_KEY여야 합니다.");
				const type_ubyte* nullpoint = 0;
				return *nullpoint;
			}

			return (static_cast<const NEUByteKey&>(somekey)).getValue();
		}
		type_ubyte& getTransparentColorBlue()
		{
			const ThisClass* consted_this = this;

			return const_cast<type_ubyte&>(consted_this->getTransparentColorBlue() );
		}
		const type_ubyte& getTransparentColorBlue() const
		{
			const NEKey& somekey = getKeySet()[4];
			if( ! somekey.isSubClassOf(NEType::NEUBYTE_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 4번키가 NEUBYTE_KEY여야 합니다.");
				const type_ubyte* nullpoint = 0;
				return *nullpoint;
			}

			return (static_cast<const NEUByteKey&>(somekey)).getValue();
		}
		type_ubyte& getTransparentColorAlpha()
		{
			const ThisClass* consted_this = this;

			return const_cast<type_ubyte&>(consted_this->getTransparentColorAlpha() );
		}
		const type_ubyte& getTransparentColorAlpha() const
		{
			const NEKey& somekey = getKeySet()[5];
			if( ! somekey.isSubClassOf(NEType::NEUBYTE_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 5번키가 NEUBYTE_KEY여야 합니다.");
				const type_ubyte* nullpoint = 0;
				return *nullpoint;
			}

			return (static_cast<const NEUByteKey&>(somekey)).getValue();
		}
		type_uint getWidth() const;
		type_uint getHeight() const;
		virtual type_uint getWidthOfOneFrame() const
		{
			return getWidth();
		}
		virtual type_uint getHeightOfOneFrame() const
		{
			return getHeight();
		}
		D3DSURFACE_DESC getTextureDescription() const;		
		type_uint createColorKey() const
		{
			return D3DCOLOR_RGBA(getTransparentColorRed(), getTransparentColorGreen(), 
				getTransparentColorBlue(), getTransparentColorAlpha());
		}

	public:
		virtual RECT createSourceRect() const
		{
			RECT to_return = {
				0,			0, 
				getWidth(), getHeight()
			};

			return to_return;
		}
		virtual type_result releaseResource()
		{
			if(_texture)
				_texture->Release();
			_texture = 0;

			memset(&_texture_description, 0, sizeof(_texture_description));

			return SuperClass::releaseResource();
		}
		virtual type_result initializeResource();
		virtual type_result dock(Model& model);
		virtual type_result initialize()
		{
			SuperClass::initialize();

			NEKeyCodeSet& keyset = getKeySet();
			keyset.resize(keyset.getLength() + 4);
			keyset.push(NEUByteKey(getDefaultColorKeyRed()));	//	2:	ColorKeyRed
			keyset.push(NEUByteKey(getDefaultColorKeyGreen()));	//	3:	ColorKeyGreen
			keyset.push(NEUByteKey(getDefaultColorKeyBlue()));	//	4:	ColorKeyBlue
			keyset.push(NEUByteKey(getDefaultColorKeyAlpha()));	//	5:	ColorKeyAlpha

			return RESULT_SUCCESS;
		}
		virtual type_result execute();
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual void release()
		{
			SuperClass::release();

			ThisClass::releaseResource();
		}
		NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
		{
			SuperClass::serialize(loader);

			ThisClass::releaseResource();

			return loader;
		}
		virtual NEObject& clone() const
		{
			return *(new Texture(*this));
		}
		
	private:
		bool _isTextureSizePowerOf2(D3DXIMAGE_INFO& image_info)
		{
			if( ! _isPowerOf2(image_info.Width)		||
				! _isPowerOf2(image_info.Height)	)
				return false;

			return true;
		}
		bool _isPowerOf2(type_uint size)
		{
			while(1)
			{
				type_uint remainder = size % 2;
				size /= 2;

				if(remainder)
					return false;
				if(size == 1)
					break;
			}

			return true;
		}

	private:
		LPDIRECT3DTEXTURE9 _texture;
		D3DSURFACE_DESC _texture_description;

	public:
		static type_ubyte getDefaultColorKeyRed();
		static type_ubyte getDefaultColorKeyGreen();
		static type_ubyte getDefaultColorKeyBlue();
		static type_ubyte getDefaultColorKeyAlpha();
	};
}