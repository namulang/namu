#pragma once

#include "../RenderableModule/RenderableModule.hpp"

namespace DX9Graphics
{
	class NE_DLL Particle : public RenderableModule
	{
	public:
		typedef RenderableModule SuperClass;
		typedef Particle ThisClass;

	public:
		type_float& getTranslationX()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_float&>(consted_this->getTranslationX());
		}
		const type_float& getTranslationX() const
		{
			const NEKey& somekey = getKeySet()[0];
			if( ! somekey.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 0번키가 NEFLOAT_KEY여야 합니다.");
				const type_float* nullpoint = 0;
				return *nullpoint;
			}

			const NEFloatKey& target = static_cast<const NEFloatKey&>(somekey);
			return target.getValue();
		}
		type_float& getTranslationY()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_float&>(consted_this->getTranslationY());
		}
		const type_float& getTranslationY() const
		{
			const NEKey& somekey = getKeySet()[1];
			if( ! somekey.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 1번키가 NEFLOAT_KEY여야 합니다.");
				const type_float* nullpoint = 0;
				return *nullpoint;
			}

			const NEFloatKey& target = static_cast<const NEFloatKey&>(somekey);
			return target.getValue();
		}

		type_float& getTranslationZ()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_float&>(consted_this->getTranslationZ());
		}
		const type_float& getTranslationZ() const
		{
			const NEKey& somekey = getKeySet()[2];
			if( ! somekey.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 2번키가 NEFLOAT_KEY여야 합니다.");
				const type_float* nullpoint = 0;
				return *nullpoint;
			}

			const NEFloatKey& target = static_cast<const NEFloatKey&>(somekey);
			return target.getValue();
		}
		type_float& getRotationX()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_float&>(consted_this->getRotationX());
		}
		const type_float& getRotationX() const
		{
			const NEKey& somekey = getKeySet()[3];
			if( ! somekey.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 3번키가 NEFLOAT_KEY여야 합니다.");
				const type_float* nullpoint = 0;
				return *nullpoint;
			}

			const NEFloatKey& target = static_cast<const NEFloatKey&>(somekey);
			return target.getValue();
		}
		type_float& getRotationY()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_float&>(consted_this->getRotationY());
		}
		const type_float& getRotationY() const
		{
			const NEKey& somekey = getKeySet()[4];
			if( ! somekey.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 4번키가 NEFLOAT_KEY여야 합니다.");
				const type_float* nullpoint = 0;
				return *nullpoint;
			}

			const NEFloatKey& target = static_cast<const NEFloatKey&>(somekey);
			return target.getValue();
		}

		type_float& getRotationZ()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_float&>(consted_this->getRotationZ());
		}
		const type_float& getRotationZ() const
		{
			const NEKey& somekey = getKeySet()[5];
			if( ! somekey.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 5번키가 NEFLOAT_KEY여야 합니다.");
				const type_float* nullpoint = 0;
				return *nullpoint;
			}

			const NEFloatKey& target = static_cast<const NEFloatKey&>(somekey);
			return target.getValue();
		}
		type_float& getScalingX()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_float&>(consted_this->getScalingX());
		}
		const type_float& getScalingX() const
		{
			const NEKey& somekey = getKeySet()[6];
			if( ! somekey.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 6번키가 NEFLOAT_KEY여야 합니다.");
				const type_float* nullpoint = 0;
				return *nullpoint;
			}

			const NEFloatKey& target = static_cast<const NEFloatKey&>(somekey);
			return target.getValue();
		}
		type_float& getScalingY()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_float&>(consted_this->getScalingY());
		}
		const type_float& getScalingY() const
		{
			const NEKey& somekey = getKeySet()[7];
			if( ! somekey.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 7번키가 NEFLOAT_KEY여야 합니다.");
				const type_float* nullpoint = 0;
				return *nullpoint;
			}

			const NEFloatKey& target = static_cast<const NEFloatKey&>(somekey);
			return target.getValue();
		}
		type_float& getScalingZ()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_float&>(consted_this->getScalingZ());
		}
		const type_float& getScalingZ() const
		{
			const NEKey& somekey = getKeySet()[8];
			if( ! somekey.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 8번키가 NEFLOAT_KEY여야 합니다.");
				const type_float* nullpoint = 0;
				return *nullpoint;
			}

			const NEFloatKey& target = static_cast<const NEFloatKey&>(somekey);
			return target.getValue();
		}
		type_ubyte& getColorRed()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_ubyte&>(consted_this->getColorRed());
		}
		const type_ubyte& getColorRed() const
		{
			const NEKey& somekey = getKeySet()[9];
			if( ! somekey.isSubClassOf(NEType::NEUBYTE_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 9번키가 NEUBYTE_KEY여야 합니다.");
				const type_ubyte* nullpoint = 0;
				return *nullpoint;
			}

			const NEUByteKey& target = static_cast<const NEUByteKey&>(somekey);
			return target.getValue();
		}
		type_ubyte& getColorGreen()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_ubyte&>(consted_this->getColorGreen());
		}
		const type_ubyte& getColorGreen() const
		{
			const NEKey& somekey = getKeySet()[10];
			if( ! somekey.isSubClassOf(NEType::NEUBYTE_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 10번키가 NEUBYTE_KEY여야 합니다.");
				const type_ubyte* nullpoint = 0;
				return *nullpoint;
			}

			const NEUByteKey& target = static_cast<const NEUByteKey&>(somekey);
			return target.getValue();
		}
		type_ubyte& getColorBlue()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_ubyte&>(consted_this->getColorBlue());
		}
		const type_ubyte& getColorBlue() const
		{
			const NEKey& somekey = getKeySet()[11];
			if( ! somekey.isSubClassOf(NEType::NEUBYTE_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 11번키가 NEUBYTE_KEY여야 합니다.");
				const type_ubyte* nullpoint = 0;
				return *nullpoint;
			}

			const NEUByteKey& target = static_cast<const NEUByteKey&>(somekey);
			return target.getValue();
		}
		type_ubyte& getColorAlpha()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_ubyte&>(consted_this->getColorAlpha());
		}
		const type_ubyte& getColorAlpha() const
		{
			const NEKey& somekey = getKeySet()[12];
			if( ! somekey.isSubClassOf(NEType::NEUBYTE_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 12번키가 NEUBYTE_KEY여야 합니다.");
				const type_ubyte* nullpoint = 0;
				return *nullpoint;
			}

			const NEUByteKey& target = static_cast<const NEUByteKey&>(somekey);
			return target.getValue();
		}
		type_byte& getSourceBlend()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_byte&>(consted_this->getSourceBlend());
		}
		const type_byte& getSourceBlend() const
		{
			const NEKey& somekey = getKeySet()[13];
			if( ! somekey.isSubClassOf(NEType::NEBYTE_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 13번키가 NEBYTE_KEY여야 합니다.");
				const type_byte* nullpoint = 0;
				return *nullpoint;
			}

			return static_cast<const NEByteKey&>(somekey).getValue();
		}
		type_byte& getDestBlend()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_byte&>(consted_this->getDestBlend());
		}
		const type_byte& getDestBlend() const
		{
			const NEKey& somekey = getKeySet()[14];
			if( ! somekey.isSubClassOf(NEType::NEBYTE_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 14번키가 NEBYTE_KEY여야 합니다.");
				const type_byte* nullpoint = 0;
				return *nullpoint;
			}

			return static_cast<const NEByteKey&>(somekey).getValue();
		}
		type_uint createColor() const
		{
			return D3DCOLOR_RGBA(getColorRed(), getColorGreen(), getColorBlue(), 
				getColorAlpha());
		}
		D3DXVECTOR3 createTranslationVector() const { return D3DXVECTOR3(getTranslationX(), getTranslationY(), getTranslationZ()); }		
		D3DXVECTOR3 createScalingVector() const { return D3DXVECTOR3(getScalingX(), getScalingY(), getScalingZ()); }		
		D3DXMATRIX createTranslationMatrix() const;
		D3DXMATRIX createRotationMatrix() const;
		D3DXMATRIX createScalingMatrix() const
		{
			D3DXMATRIX to_return;
			D3DXMatrixScaling(&to_return, getScalingX(), getScalingY(), getScalingZ());

			return to_return;
		}

	public:		
		virtual type_result initialize()
		{
			SuperClass::initialize();

			NEKeyCodeSet& keyset = getKeySet();
			keyset.create(15);
			keyset.push(NEFloatKey(0.0f));				//	0:	TranslationX
			keyset.push(NEFloatKey(0.0f));				//	1:	TranslationY
			keyset.push(NEFloatKey(0.0f));				//	2:	TranslationZ
			keyset.push(NEFloatKey(0.0f));				//	3:	RotationX
			keyset.push(NEFloatKey(0.0f));				//	4:	RotationY
			keyset.push(NEFloatKey(0.0f));				//	5:	RotationZ
			keyset.push(NEFloatKey(1.0f));				//	6:	ScalingX
			keyset.push(NEFloatKey(1.0f));				//	7:	ScalingY
			keyset.push(NEFloatKey(1.0f));				//	8:	ScalingZ
			keyset.push(NEUByteKey(255));				//	9:	ColorRed
			keyset.push(NEUByteKey(255));				//	10:	ColorGreen
			keyset.push(NEUByteKey(255));				//	11:	ColorBlue
			keyset.push(NEUByteKey(255));				//	12:	ColorAlpha
			keyset.push(NEByteKey(NE_DEFAULT));			//	13:	SourceBlend(0 means AUTO - setting from camera)
			keyset.push(NEByteKey(NE_DEFAULT));			//	14:	DestBlend(0 means AUTO - setting from camera)

			return RESULT_SUCCESS;
		}
	};
}