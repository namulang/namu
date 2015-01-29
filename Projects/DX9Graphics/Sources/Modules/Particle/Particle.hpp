#pragma once

#include "../EulerTransitor/EulerTransitor.hpp"
#include "../../Commons/Interfaces/IRenderable/Renderable.hpp"

namespace DX9Graphics
{
	class NE_DLL Particle : public EulerTransitor, public Renderable
	{
	public:
		typedef EulerTransitor SuperClass;
		typedef Particle ThisClass;

	public:
		NETArgument<NEFloatKey>	arg_trans_x;
		NETArgument<NEFloatKey> arg_trans_y;
		NETArgument<NEFloatKey> arg_trans_z;
		NETArgument<NEFloatKey> arg_rotate_x;
		NETArgument<NEFloatKey> arg_rotate_y;
		NETArgument<NEFloatKey> arg_rotate_z;
		NETArgument<NEFloatKey> arg_scale_x;
		NETArgument<NEFloatKey> arg_scale_y;
		NETArgument<NEFloatKey> arg_scale_z;
		NETArgument<NEUByteKey> arg_red;
		NETArgument<NEUByteKey> arg_green;
		NETArgument<NEUByteKey> arg_blue;
		NETArgument<NEUByteKey> arg_alpha;
		NETArgument<NEByteKey>	arg_source_blend;
		NETArgument<NEByteKey>	arg_dest_blend;

	public:
		ThisClass& operator=(const ThisClass& rhs)
		{
			if (this == &rhs) return *this;

			SuperClass::operator=(rhs);

			arg_trans_x = rhs.arg_trans_x;
			arg_trans_y = rhs.arg_trans_y;
			arg_trans_z = rhs.arg_trans_z;
			arg_rotate_x = rhs.arg_rotate_x;
			arg_rotate_y = rhs.arg_rotate_y;
			arg_rotate_z = rhs.arg_rotate_z;
			arg_scale_x = rhs.arg_scale_x;
			arg_scale_y = rhs.arg_scale_y;
			arg_scale_z = rhs.arg_scale_z;
			arg_red = rhs.arg_red;
			arg_green = rhs.arg_green;
			arg_blue = rhs.arg_blue;
			arg_alpha = rhs.arg_alpha;
			arg_source_blend = rhs.arg_source_blend;
			arg_dest_blend = rhs.arg_dest_blend;

			return *this;
		}

		type_uint createColor() const
		{
			return D3DCOLOR_RGBA(arg_red.getValue(), arg_green.getValue(), arg_blue.getValue(), 
				arg_alpha.getValue());
		}
		D3DXVECTOR3 createTranslationVector() const 
		{ 
			return D3DXVECTOR3(arg_trans_x.getValue(), arg_trans_y.getValue(), arg_trans_z.getValue()); 
		}		
		D3DXVECTOR3 createScalingVector() const 
		{ 
			return D3DXVECTOR3(arg_scale_x.getValue(), arg_scale_y.getValue(), arg_scale_z.getValue()); 
		}
		D3DXMATRIX Particle::createTranslationMatrix() const
		{
			D3DXMATRIX to_return;
			D3DXMatrixTranslation(&to_return, 
				arg_trans_x.getValue(), arg_trans_y.getValue(), arg_trans_z.getValue());

			return to_return;
		}
		D3DXMATRIX createScalingMatrix() const
		{
			D3DXMATRIX to_return;
			D3DXMatrixScaling(&to_return, 
				arg_scale_x.getValue(), arg_scale_y.getValue(), arg_scale_z.getValue());

			return to_return;
		}
		type_result forward(type_float distance)
		{
			return _moveByDelta(D3DXVECTOR3(0, 0, 1), distance);
		}
		type_result stepAside(type_float distance)
		{
			return _moveByDelta(D3DXVECTOR3(1, 0, 0), distance);
		}
		type_result goUp(type_float distance)
		{
			return _moveByDelta(D3DXVECTOR3(0, 1, 0), distance);
		}

	public:
		const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;

			if(_instance.getArgumentsComments().getLength() < 15)
			{
				NETStringSet& args = _instance.getArgumentsComments();
				args.resize(15);
				args.push("TranslationX\n물체가 X 좌표로 얼마나 이동하였는지를 나타냅니다.");
				args.push("TranslationY\n물체가 Y 좌표로 얼마나 이동하였는지를 나타냅니다.");
				args.push("TranslationZ\n물체가 Z 좌표로 얼마나 이동하였는지를 나타냅니다.");

				args.push(SuperClass::getHeader().getArgumentsComments());

				args.push("ScalingX\n물체가 X축으로 크기 배율이 어떻게 되는지 나타냅니다.\n2.0이면 본래 크기의 2배 라는 뜻이 됩니다.");
				args.push("ScalingY\n물체가 Y축으로 크기 배율이 어떻게 되는지 나타냅니다.");
				args.push("ScalingZ\n물체가 Z축으로 크기 배율이 어떻게 되는지 나타냅니다.");
				args.push("Red\n물체가 가지고 있는 빨강색 성분 입니다.(최대255)\n예를들어, Green Blue가 모두 0이고 Red만 255일 경우, 빨강색 성분만 남게 되어\n물체가 빨갛게 됩니다.");
				args.push("Green\n물체가 가지고 있는 초록색 성분 입니다.(최대255)");
				args.push("Blue\n물체가 가지고 있는 파랑색 성분 입니다.(최대255)");
				args.push("Alpha\n물체가 가지고 있는 불투명도 성분 입니다.(최대255)\n0에 가까울 수록 투명해 집니다.");
				args.push("SourceBlending\nSource 블렌딩 방법입니다.\n0을 입력하면 Camera의 Source Blending 설정을 이어받습니다.");
				args.push("DestBlending\nDest 블렌딩 방법입니다.\n0을 입력하면 Camera의 Dest Blending 설정을 이어받습니다.");
			}

			return _instance;
		}

	protected:
		virtual type_result _onFetchModule()
		{
			arg_scale_x.setValue(1.0f);
			arg_scale_y.setValue(1.0f);
			arg_scale_z.setValue(1.0f);
			arg_red.setValue(255);
			arg_green.setValue(255);
			arg_blue.setValue(255);
			arg_alpha.setValue(255);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_trans_x);
			tray.push(arg_trans_y);
			tray.push(arg_trans_z);

			SuperClass::_onFetchArguments(tray);

			tray.push(arg_scale_x);
			tray.push(arg_scale_y);
			tray.push(arg_scale_z);
			tray.push(arg_red);
			tray.push(arg_green);
			tray.push(arg_blue);
			tray.push(arg_alpha);
			tray.push(arg_source_blend);
			tray.push(arg_dest_blend);

			return RESULT_SUCCESS;
		}

	private:
		type_result _moveByDelta(const D3DXVECTOR3& origin_direction, type_float distance)
		{
			D3DXVECTOR3 new_direction = createTransformedVectorByYawPitchRoll(origin_direction);

			arg_trans_x.setValue(arg_trans_x.getValue() + new_direction.x * distance);
			arg_trans_y.setValue(arg_trans_y.getValue() + new_direction.y * distance);
			arg_trans_z.setValue(arg_trans_z.getValue() + new_direction.z * distance);

			return RESULT_SUCCESS;
		}

	public:
		static const NECodeSet& getModuleScriptCodes()
		{
			NECodeType type(NECodeType::MODULE_SCRIPT);
			static NECodeSet codes(type);

			if (codes.getLength() <= 0)
			{
				codes.create(3);
				codes.push(NEExportable::Identifier("Model.kniz"));
				codes.push(NEExportable::Identifier("Camera.kniz"));
				codes.push(NEExportable::Identifier("AnimatedModel.kniz"));
			}

			return codes;
		}
	};
}
