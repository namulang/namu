#pragma once

#include "../../Includes/Includes.hpp"

namespace DX9Graphics
{
	class Texture;

	class NE_DLL SpriteTexter : public NEModule
	{
	public:
		typedef SpriteTexter ThisClass;
		typedef NEModule SuperClass;

	public:
#include "Alignment.hpp"

	public:		
		const NEModuleSelector& getFontSelector() const
		{
			const NEKey& key = getKeySet()[0];
			if( ! &key || ! key.isSubClassOf(NEType::NEMODULE_SELECTOR))
			{
				ALERT_ERROR("0번키는 NEMODULE_SELECTOR입니다.");
				NEModuleSelector* nullpointer=0;
				return *nullpointer;
			}
			return static_cast<const NEModuleSelector&>(key);
		}
		NEModuleSelector& getFontSelector()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<NEModuleSelector&>(casted->getFontSelector());
		}
		const NETString& getText() const
		{
			const NEKey& key = getKeySet()[1];
			if( ! &key || ! key.isSubClassOf(NEType::NETSTRING_KEY))
			{
				ALERT_ERROR("1키는 NETSTRING_KEY이어야 합니다.");
				NETString* pointer=0;
				return *pointer;
			}

			return static_cast<const NETStringKey&>(key).getValue();
		}
		NETString& getText()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<NETString&>(casted->getText());
		}
		const type_ubyte& getHorizontalAlignment() const
		{
			const NEKey& key = getKeySet()[2];
			if( ! &key || ! key.isSubClassOf(NEType::NEUBYTE_KEY))
			{
				ALERT_ERROR("2키는 NEUBYTE_KEY이어야 합니다.");
				type_ubyte* pointer=0;
				return *pointer;
			}

			return static_cast<const NEUByteKey&>(key).getValue();
		}
		type_ubyte& getHorizontalAlignment()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_ubyte&>(casted->getHorizontalAlignment());
		}
		const type_ubyte& getVerticalAlignment() const
		{
			const NEKey& key = getKeySet()[3];
			if( ! &key || ! key.isSubClassOf(NEType::NEUBYTE_KEY))
			{
				ALERT_ERROR("3키는 NEUBYTE_KEY이어야 합니다.");
				type_ubyte* pointer=0;
				return *pointer;
			}

			return static_cast<const NEUByteKey&>(key).getValue();
		}
		type_ubyte& getVerticalAlignment()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_ubyte&>(casted->getVerticalAlignment());
		}
		const type_ubyte& getColorRed() const
		{
			const NEKey& key = getKeySet()[4];
			if( ! &key || ! key.isSubClassOf(NEType::NEUBYTE_KEY))
			{
				ALERT_ERROR("4키는 NEUBYTE_KEY이어야 합니다.");
				type_ubyte* pointer=0;
				return *pointer;
			}

			return static_cast<const NEUByteKey&>(key).getValue();
		}
		type_ubyte& getColorRed()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_ubyte&>(casted->getColorRed());
		}
		const type_ubyte& getColorGreen() const
		{
			const NEKey& key = getKeySet()[5];
			if( ! &key || ! key.isSubClassOf(NEType::NEUBYTE_KEY))
			{
				ALERT_ERROR("5키는 NEUBYTE_KEY이어야 합니다.");
				type_ubyte* pointer=0;
				return *pointer;
			}

			return static_cast<const NEUByteKey&>(key).getValue();
		}
		type_ubyte& getColorGreen()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_ubyte&>(casted->getColorGreen());
		}
		const type_ubyte& getColorBlue() const
		{
			const NEKey& key = getKeySet()[6];
			if( ! &key || ! key.isSubClassOf(NEType::NEUBYTE_KEY))
			{
				ALERT_ERROR("6키는 NEUBYTE_KEY이어야 합니다.");
				type_ubyte* pointer=0;
				return *pointer;
			}

			return static_cast<const NEUByteKey&>(key).getValue();
		}
		type_ubyte& getColorBlue()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_ubyte&>(casted->getColorBlue());
		}
		const type_ubyte& getColorAlpha() const
		{
			const NEKey& key = getKeySet()[7];
			if( ! &key || ! key.isSubClassOf(NEType::NEUBYTE_KEY))
			{
				ALERT_ERROR("7키는 NEUBYTE_KEY이어야 합니다.");
				type_ubyte* pointer=0;
				return *pointer;
			}

			return static_cast<const NEUByteKey&>(key).getValue();
		}
		type_ubyte& getColorAlpha()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_ubyte&>(casted->getColorAlpha());
		}
		type_uint createColor() const
		{
			return D3DCOLOR_RGBA(getColorRed(), getColorGreen(), getColorBlue(),
				getColorAlpha());
		}

	public:
		virtual NEExportable::ModuleHeader& getHeader() const;

	public:
		virtual type_result initialize();

	public:
		virtual type_result execute();

	public:
		virtual NEObject& clone() const;

	public:
		type_result render(LPD3DXSPRITE sprite, const Texture& texture);

	private:
		type_result _bindFont();
		RECT _createFontArea(const Texture& texture);

	public:
		static const NECodeSet& getScriptCodeSet()
		{
			static NECodeSet _instance;
			
			if(_instance.getSize() <= 0)
			{
				_instance.create(1);
				_instance.setCodeType(NECodeType::SCRIPT);
				_instance.push(SpriteTexter().getHeader());
			}

			return _instance;
		}
	};
}