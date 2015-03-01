#pragma once

#include "../../Commons/Templates/TValidator/TValidator.hpp"
#include "../Particle/Particle.hpp"

namespace DX9Graphics
{
	class NE_DLL ParticleVelocity : public TValidator<Particle>
	{
	public:
		typedef ParticleVelocity ThisClass;
		typedef TValidator<Particle> SuperClass;

	public:
		NETArgument<NEFloatKey>	arg_direction_x_angle;
		NETArgument<NEFloatKey>	arg_direction_y_angle;
		NETArgument<NEFloatKey>	arg_direction_z_angle;
		NETArgument<NEFloatKey>	arg_magnitude;

	protected:
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			SuperClass::_onFetchArguments(tray);

			tray.push(arg_direction_x_angle);
			tray.push(arg_direction_y_angle);
			tray.push(arg_direction_z_angle);
			tray.push(arg_magnitude);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchModule()
		{
			SuperClass::_onFetchModule();

			arg_direction_x_angle.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_direction_y_angle.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_direction_z_angle.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_magnitude.setValue(1.0f);
			arg_magnitude.setPurposeLimitation(NEArgumentBase::READ_BY);

			return RESULT_SUCCESS;
		}
		virtual type_result _onExecute()
		{
			type_float	yaw = arg_direction_y_angle.getValue(),
				pitch = arg_direction_x_angle.getValue(),
				roll = arg_direction_z_angle.getValue();

			D3DXMATRIXA16 rmat = EulerTransitor::createRotationMatrix(
				DX9::createQuaternionFrom(yaw, pitch, roll)
				);

			D3DXVECTOR3 delta;
			D3DXVec3TransformNormal(&delta, &D3DXVECTOR3(0, 0, 1), &rmat);
			delta *= arg_magnitude.getValue();

			NEModule* e = 0x00;
			while (e = &arg_validator.getValue().getModule())
			{
				Particle& particle = cast(*e);
				if( ! &particle) continue;

				particle.arg_trans_x.setValue(particle.arg_trans_x.getValue() + delta.x);
				particle.arg_trans_y.setValue(particle.arg_trans_y.getValue() + delta.y);
				particle.arg_trans_z.setValue(particle.arg_trans_z.getValue() + delta.z);
			}			

			return RESULT_SUCCESS;
		}

	public:
		virtual NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;

			if (_header.isValid() != RESULT_NOTHING)
			{
				_header.getName() = _T("ParticleVelocity");
				_header.getDeveloper() = _T("kniz");
				_header.setRevision(1);
				_header.getComment() =
					"Particle들을 특정한 방향으로 Magnitude 만큼 Particle의 X, Y, Z을 이동시킵니다.\n"
					"여기서 특정한 방향은 기준방향에(= 벡터 0, 0, 1)을 X축 회전, Y축 회전, Z축 회전으로 "
					"순차적으로 적용하여 정해집니다.\n";
				"Particle에 속하는 Module은 Camera, Model, AnimatedModel 등이 있습니다.\n"
					"예를들어, 이 Particle들이 가지고 있는 X축 Angle, Y축 Angle, Z축 Angle을 "
					"그대로 이 Module에 Angle에 할당하면, 물체가 향하는 방향으로 나아가게 됩니다.";
				_header.getVersion() = _T("0.0.1a");
				_header.getReleaseDate() = _T("2013-10-05");
				NETStringSet& args = _header.getArgumentsComments();
				args.create(5);
				args.push("Particle(s)\n대상이 되는 Particle Module들입니다.\nCamera, Model, AnimatedModel들이 여기에 속합니다.");
				args.push("Direction Angle X\n이동이 적용될 방향을, 기준방향v(0, 0, 1)에 대한 X축 회전성분입니다.");
				args.push("Direction Angle y\n이동이 적용될 방향을, 기준방향v(0, 0, 1)에 대한 Y축 회전성분입니다.");
				args.push("Direction Angle Z\n이동이 적용될 방향을, 기준방향v(0, 0, 1)에 대한 Z축 회전성분입니다.");
				args.push("Magnitude\n위의 Angle들로 결정된 방향으로 얼마나 이동될지 정합니다.\n즉, 방향단위벡터의 길이 값입니다.");
			}

			return _header;
		}

	public:
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
	};
}