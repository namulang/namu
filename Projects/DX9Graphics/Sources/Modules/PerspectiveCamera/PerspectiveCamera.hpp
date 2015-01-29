#pragma once

#include "../Camera/Camera.hpp"

namespace DX9Graphics
{
	class NE_DLL PerspectiveCamera : public Camera
	{
	public:
		typedef Camera SuperClass;
		typedef PerspectiveCamera ThisClass;

	public:
		NETArgument<NEFloatKey> arg_fovy;		//	Field Of View
		NETArgument<NEFloatKey> arg_aspect;		//	Width / Height
		NETArgument<NEFloatKey> arg_minimum_z;	//	near z
		NETArgument<NEFloatKey> arg_maximum_z;	//	far_z		

	protected:
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			SuperClass::_onFetchArguments(tray);

			tray.push(arg_fovy);
			tray.push(arg_aspect);
			tray.push(arg_minimum_z);
			tray.push(arg_maximum_z);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchModule()		
		{
			arg_fovy.setValue(90);
			arg_fovy.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_fovy.setEnable(false);
			arg_aspect.setValue(640.0f / 480.0f);
			arg_aspect.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_minimum_z.setValue(0.1f);
			arg_minimum_z.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_maximum_z.setValue(1000.0f);
			arg_maximum_z.setPurposeLimitation(NEArgumentBase::READ_BY);

			return RESULT_SUCCESS;
		}

	public:
		virtual NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;

			if (_header.isValid() != RESULT_NOTHING)
			{
				const NEExportable::ModuleHeader& supers = SuperClass::getHeader();

				_header.getName() = "PerpectiveCamera";
				_header.getDeveloper() = "kniz";
				_header.setRevision(1);
				_header.getComment() = supers.getComment() +
					"이 카메라는 원근법을 적용하여 그려내는 카메라입니다.";
				_header.getVersion() = "0.0.1a";
				_header.getReleaseDate() = "2013-08-10";
				NETStringSet& args = _header.getArgumentsComments();
				args = supers.getArgumentsComments();
				args.resize(4);
				args.push("Field Of View Y(FOVy : 시야각)\n카메라가 보는 방향으로 위아래 몇 도 만큼 영상에 포함되는 가를 결정합니다. 높을 수록 더 많은 영역을 그리게 됩니다.\nDisabled시, 자동으로 설정합니다.");
				args.push("Aspect(종횡비)\nFOVy 값으로 정해진 높이에 대해서 너비를 곱해 결정합니다.\n1.0이면 FOVy로 결정된 높이와 너비가 같다는 뜻입니다.\n2.0이면 너비가 높이보다 2배 큽니다.");
				args.push("Near Z\n물체와 카메라의 거리가 이 값보다 작은 경우는 그리지 않습니다.");
				args.push("Far Z\n물체와 카메라의 거리가 이 값보다 큰 경우는 그리지 않습니다.");
			}

			return _header;
		}

	public:
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}

	private:
		virtual type_result _updateProjectionMatrix()
		{
			type_float	fovy = arg_fovy.getValue(),
				aspect = arg_aspect.getValue(),
				min_z = arg_minimum_z.getValue(),
				max_z = arg_maximum_z.getValue();

			if( ! arg_fovy.isEnable())
				_updateProjectionVariablesAutomatically();

			D3DXMATRIX projection_matrix;
			D3DXMatrixPerspectiveFovLH(&getProjectionMatrix(), 
				fovy, aspect,
				min_z, max_z);

			return RESULT_SUCCESS;
		}
		type_result _updateProjectionVariablesAutomatically()
		{
			D3DVIEWPORT9 maximized = createMaximizedViewPort();
			if(maximized.Height == 0)
				maximized.Height = 1;


			//	main:			
			if( ! arg_viewport_x.isEnable())	//	when use maximized viewport,
			{
				arg_aspect.setValue((float)maximized.Width / maximized.Height);
				arg_fovy.setValue(90);
			}
			else
			{
				type_uint vp_h = arg_viewport_height.getValue();

				arg_aspect.setValue((float) arg_viewport_width.getValue() / vp_h);
				arg_fovy.setValue(90);
			}


			//	post:
			arg_minimum_z.setValue(0.1f);
			arg_maximum_z.setValue(1000.0f);
			return RESULT_SUCCESS;
		}
	};
}