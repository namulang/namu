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
		DXFont() : Resource(), _font(0) {}
		DXFont(const ThisClass& src) : SuperClass(src), _font(0) {}

	public:
		DXFont& operator=(const ThisClass& src)
		{
			if(this == &src) return *this;

			SuperClass::operator=(src);			
			
			return *this;	//	_font는 할당하지 않는다.
		}

	public:
		const NETString& getName() const
		{
			const NEKey& key = getKeySet()[1];
			if( ! &key || ! key.isSubClassOf(NEType::NETSTRING_KEY))
			{
				ALERT_ERROR("1번키는 NETSTRING_KEY입니다.");
				NETString* nullpointer=0;
				return *nullpointer;
			}
			return static_cast<const NETStringKey&>(key).getValue();
		}
		NETString& getName()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<NETString&>(casted->getName());
		}
		const type_ubyte& getCharSet() const
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
		type_ubyte& getCharSet()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_ubyte&>(casted->getCharSet());
		}
		const type_uint& getWidth() const
		{
			const NEKey& key = getKeySet()[3];
			if( ! &key || ! key.isSubClassOf(NEType::NEUINT_KEY))
			{
				ALERT_ERROR("3키는 NEUINT_KEY이어야 합니다.");
				type_uint* pointer=0;
				return *pointer;
			}

			return static_cast<const NEUIntKey&>(key).getValue();
		}
		type_uint& getWidth()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_uint&>(casted->getWidth());
		}
		const type_uint& getHeight() const
		{
			const NEKey& key = getKeySet()[4];
			if( ! &key || ! key.isSubClassOf(NEType::NEUINT_KEY))
			{
				ALERT_ERROR("4키는 NEUINT_KEY이어야 합니다.");
				type_uint* pointer=0;
				return *pointer;
			}

			return static_cast<const NEUIntKey&>(key).getValue();
		}
		type_uint& getHeight()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_uint&>(casted->getHeight());
		}
		const type_uint& getWeight() const
		{
			const NEKey& key = getKeySet()[5];
			if( ! &key || ! key.isSubClassOf(NEType::NEUINT_KEY))
			{
				ALERT_ERROR("5키는 NEUINT_KEY이어야 합니다.");
				type_uint* pointer=0;
				return *pointer;
			}

			return static_cast<const NEUIntKey&>(key).getValue();
		}
		type_uint& getWeight()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_uint&>(casted->getWeight());
		}
		const type_bool& isItalic() const
		{
			const NEKey& key = getKeySet()[6];
			if( ! &key || ! key.isSubClassOf(NEType::NEBOOLEAN_KEY))
			{
				ALERT_ERROR("6키는 NEBOOLEAN_KEY이어야 합니다.");
				type_bool* pointer=0;
				return *pointer;
			}

			return static_cast<const NEBooleanKey&>(key).getValue();
		}
		type_bool& isItalic()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_bool&>(casted->isItalic());
		}
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
		virtual NEExportable::ModuleHeader& getHeader() const;

	public:
		virtual type_result initialize();

	public:
		virtual type_result execute();

	public:
		virtual NEObject& clone() const;

	private:
		LPD3DXFONT _font;

	public:
		static const NECodeSet& getFontCodeSet()
		{
			static NECodeSet _instance;
			
			if(_instance.getSize() <= 0)
			{
				_instance.create(1);
				_instance.setCodeType(NECodeType::SCRIPT);
				_instance.push(ThisClass().getHeader());
			}

			return _instance;
		}
	};
}