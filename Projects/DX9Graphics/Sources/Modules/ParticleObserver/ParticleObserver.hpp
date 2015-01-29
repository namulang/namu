#pragma once

#include "../../Commons/Templates/TValidator/TValidator.hpp"
#include "../Particle/Paritcle.hpp"

namespace DX9Graphics
{
	//	Particle의 Look을 특정 좌표 및 대상으로 향하도록 Angle을 조정한다.
	class NE_DLL ParticleObserver : public TValidator<Particle>
	{
	public:
		typedef SpriteTexter ThisClass;
		typedef TValidator<Particle> SuperClass;

	public:
		NETArgument<NEModuleSelector>	arg_target;
		NETArgument<NEFloatKey>			arg_xpos;
		NETArgument<NEFloatKey>			arg_ypos;
		NETArgument<NEFloatKey>			arg_zpos;		

	protected:
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			SuperClass:_onFetchArguments(tray);

			tray.push(arg_target);
			tray.push(arg_xpos);
			tray.push(arg_ypos);
			tray.push(arg_zpos);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchModule()
		{
			SuperClass::_onFetchModule();

			arg_xpos.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_ypos.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_zpos.setPurposeLimitation(NEArgumentBase::READ_BY);			

			return RESULT_SUCCESS;
		}
		virtual type_result _onExecute()
		{
			//	pre:			
			Particle* target = 0x00;
			if(arg_target.isEnable())
			{
				arg_target.getValue().initializeReferingPoint();
				target = &_cast(arg_target.getValue().getModule());
			}
			D3DXVECTOR3 target_point = _createTargetPoint(*target);


			//	main:
			NEModule* e = 0x00;
			while(e = &arg_validator.getValue()getModule())
			{
				Particle& p = _cast(*e);
				if( ! &p) continue;

				D3DXVECTOR3 direction = _createDirectionVector(*e, *target_point);
				D3DXVec3Normalize(&direction, &direction);

				D3DXVECTOR3 degree = DX9::createYawPitchRollFrom(DX9::createQuaternionFrom(direction));
				p.arg_rotate_x.setValue(degree.x);
				p.arg_rotate_y.setValue(degree.y);
				p.arg_rotate_z.setValue(degree.z);
			}			

			return RESULT_SUCCESS;
		}

	public:
		virtual NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;

			if (_header.isValid() != RESULT_NOTHING)
			{
				_header.getName() = _T("ParticleObserver");
				_header.getDeveloper() = _T("kniz");
				_header.setRevision(1);
				_header.getComment() =
					"주어진 Particle의 RotateX, RotateY, RotateZ degree를 회전시켜서, 다른 Particle이나 특정 좌표로 바라보게 끔 합니다.\n"
					"주의 : Target Argument 를 Disabled 해야 X,Y,Zpos 좌표값을 바라보게 합니다.\n"
					"Source가 되는 Particle이 여러개가 되도록 할 수도 있습니다."
					_header.getVersion() = _T("0.0.1a");
				_header.getReleaseDate() = _T("2015-01-26");
				NETStringSet& args = _header.getArgumentsComments();
				args.create(5);
				args.push("Sources\n대상이 되는 Particle Module들입니다.\nCamera, Model, AnimatedModel들이 여기에 속합니다.");
				args.push("Target\nParicle이 바라보게 하고 싶은 다른 Particle 입니다.\nDisabled 되면 X/Y/Z Pos Arguments로 대신 사용합니다.");
				args.push("X Pos\nParitcle이 바라보게 하고 싶은 지점의 X 좌표입니다.\nTarget이 Disabled 되어야 동작합니다.");
				args.push("Y Pos\nParitcle이 바라보게 하고 싶은 지점의 Y 좌표입니다.\nTarget이 Disabled 되어야 동작합니다.");
				args.push("Z Pos\nParitcle이 바라보게 하고 싶은 지점의 Z 좌표입니다.\nTarget이 Disabled 되어야 동작합니다.");				
			}

			return _header;
		}

	public:
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}

	private:
		D3DXVECTOR3 _createTargetPoint(const Particle& target)
		{
			if(&target)
				return target.createTranslationVector();

			return D3DXVECTOR3(arg_xpos.getValue(), arg_ypos.getValue(), arg_zpos.getValue());
		}
		D3DXVECTOR3 _createDirectionVector(const Particle& me, const D3DXVECTOR3& target) const
		{
			return target - me.createTranslationVector();
		}
	};
}