#pragma once

#include "../../Includes/Includes.hpp"
#include <cmath>

namespace DX9Graphics
{
	class NE_DLL EulerTransitor : public NEModule
	{
	public:
		typedef NEModule SuperClass;
		typedef EulerTransitor ThisClass;

	public:
		static const float RADIAN_TO_DEGREE_ADJ;
		static const float DEGREE_TO_RADIAN_ADJ;

	public:
		NETArgument<NEFloatKey> arg_rotate_x;
		NETArgument<NEFloatKey> arg_rotate_y;
		NETArgument<NEFloatKey> arg_rotate_z;

	protected:
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			SuperClass::_onFetchArguments(tray);

			tray.push(arg_rotate_x);
			tray.push(arg_rotate_y);
			tray.push(arg_rotate_z);

			return RESULT_SUCCESS;
		}
		virtual type_result _onExecute()
		{
			rotation_matrix = createRotationMatrix(
				createQuaternionFrom(arg_rotate_y.getValue(), arg_rotate_x.getValue(), arg_rotate_z.getValue())
				);

			return RESULT_SUCCESS;
		}

	public:
		ThisClass& operator=(const ThisClass& source)
		{
			if (this == &source) return *this;

			SuperClass::operator=(source);

			arg_rotate_x = source.arg_rotate_x;
			arg_rotate_y = source.arg_rotate_y;
			arg_rotate_z = source.arg_rotate_z;

			return *this;
		}

	public:
		D3DXVECTOR3 createTransformedVectorByYawPitchRoll(const D3DXVECTOR3& origin) const;
		D3DXVECTOR3 createYawPitchRoll() const
		{
			return D3DXVECTOR3(arg_rotate_y.getValue(), arg_rotate_x.getValue(), arg_rotate_z.getValue());
		}
		D3DXMATRIX createRotationMatrix() const
		{
			D3DXMATRIX to_return;
			D3DXMatrixRotationYawPitchRoll(&to_return, arg_rotate_y.getValue(), arg_rotate_x.getValue(), arg_rotate_z.getValue());

			return to_return;
		}
		const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;

			if(_instance.getArgumentsComments().getLength() < 3)
			{
				NETStringSet& args = _instance.getArgumentsComments();
				args.resize(3);
				args.push("RotationX\n물체가 X축을 기준으로 얼마나 회전하였는지를 나타냅니다.");
				args.push("RotationY\n물체가 X축을 기준으로 얼마나 회전하였는지를 나타냅니다.");
				args.push("RotationZ\n물체가 X축을 기준으로 얼마나 회전하였는지를 나타냅니다.");			
			}

			return _instance;
		}

	protected:
		D3DXMATRIX rotation_matrix;

	public:
		static D3DXVECTOR3 createYawPitchRollFrom(const D3DXQUATERNION& q)
		{
			float sqw = q.w*q.w;
			float sqx = q.x*q.x;
			float sqy = q.y*q.y;
			float sqz = q.z*q.z;
			D3DXVECTOR3 ret;
			ret.x = asinf(2.0f * (q.w*q.x - q.y*q.z)); // rotation about x-axis
			ret.y = atan2f(2.0f * (q.x*q.z + q.w*q.y), (-sqx - sqy + sqz + sqw)); // rotation about y-axis
			ret.z = atan2f(2.0f * (q.x*q.y + q.w*q.z), (-sqx + sqy - sqz + sqw)); // rotation about z-axis

			return ret;
		}
		static D3DXVECTOR3 createYawPitchRollFrom(const D3DXVECTOR3& direction)
		{
			return createYawPitchRollFrom(createQuaternionFrom(direction));
		}		
		static D3DXQUATERNION createQuaternionFrom(type_float yaw, type_float pitch, type_float roll)
		{
			D3DXQUATERNION to_return;
			D3DXQuaternionRotationYawPitchRoll(&to_return, yaw, pitch, roll);

			return to_return;
		}
		static D3DXQUATERNION createQuaternionFrom(const D3DXVECTOR3& direction)
		{
			D3DXVECTOR3 up(0, 1.0f, 0.0f);
			D3DXVECTOR3 right;
			D3DXVec3Cross(&right, &up, &direction);
			D3DXVec3Cross(&up, &direction, &right);

			D3DXMATRIXA16 mBasis(
				right.x, right.y, right.z, 0.0f,
				up.x, up.y, up.z, 0.0f,
				direction.x, direction.y, direction.z, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);

			D3DXQUATERNION qrot;
			qrot.w = (float)sqrt(1.0f + mBasis._11 + mBasis._22 + mBasis._33) / 2.0f;
			float dfWScale = qrot.w * 4.0f;
			qrot.x = (float)((mBasis._32 - mBasis._23) / dfWScale);
			qrot.y = (float)((mBasis._13 - mBasis._31) / dfWScale);
			qrot.z = (float)((mBasis._21 - mBasis._12) / dfWScale);

			return qrot;
		}
		static D3DXMATRIX createRotationMatrix(const D3DXQUATERNION& quat)
		{
			D3DXMATRIX to_return;
			D3DXMatrixRotationQuaternion(&to_return, &quat);

			return to_return;
		}
		static D3DXVECTOR3 createDirectionVectorFrom(type_float yaw, type_float pitch, type_float roll, const D3DXVECTOR3& cannoncial)
		{
			D3DXMATRIXA16 mat;
			D3DXMatrixRotationQuaternion(&mat, &createQuaternionFrom(yaw, pitch, roll));
			D3DXVECTOR3 to_return;

			D3DXVec3TransformNormal(&to_return, &cannoncial, &mat);
			return to_return;
		}
	};
}