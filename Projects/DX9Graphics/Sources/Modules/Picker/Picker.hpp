#pragma once

#include "../../Commons/Templates/TValidator/TValidator.hpp"
#include "../Camera/Camera.hpp"

namespace DX9Graphics
{	
	class Model;
	template
	class NE_DLL TValidator<Camera>;

	class NE_DLL Picker : public NEModule
	{
	public:
		typedef NEModule SuperClass;
		typedef Picker ThisClass;

	public:
		NETArgument<NEModuleSelector>	arg_camera;
		NETArgument<NEModuleSelector>	arg_model;
		NETArgument<NEBooleanKey>		arg_is_picked;

	protected:
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_camera);
			tray.push(arg_model);
			tray.push(arg_is_picked);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchModule()
		{
			arg_camera.getValue().NENodeSelector::isUsingAutoBinding() = true;
			arg_camera.getValue().isUsingAutoBinding() = true;
			arg_is_picked.setPurposeLimitation(NEArgumentBase::WRITTEN);

			return RESULT_SUCCESS;
		}

		virtual type_result _onExecute();

	public:
		class Vector : public D3DXVECTOR3
		{
		public:
			Vector() : D3DXVECTOR3() {}
			Vector(type_float x, type_float y, type_float z)
				: D3DXVECTOR3(x, y, z) {}
			NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
			{
				return saver << x << y << z;
			}
			NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
			{
				return loader >> x >> y >> z;
			}
		};
		typedef NEArrayTemplate<Vector> Vectors;

	public:		
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;

			if (_header.isValid() != RESULT_NOTHING)
			{
				_header.getName() = "Picker";
				_header.getDeveloper() = "kniz";
				_header.setRevision(1);
				_header.getComment() = 
					"카메라가 촬영하는 모델들이 마우스에 의해서 Hover 되었는지를 판단합니다.\n"
					"Hover가 되면 is picked가 TRUE로 되며, Module 반환시 TRUE를 반환합니다.";
				_header.getVersion() = "0.0.1a";
				_header.getReleaseDate() = "2013-09-23";
				NETStringSet& args = _header.getArgumentsComments();
				args.create(3);
				args.push("Cameras\n이 카메라가 촬영하는 Model들이 마우스에 Hover 되었는지를 판단합니다.\n참조된 Camera가 여러개일 경우는, 그 여러개 Camera에 대해 모두 조사합니다.");
				args.push("Models\n앞서 지정한 Camera에 의해 촬영되는 Model입니다.\n이 모델이 마우스가 Hover되면 is picked가 true가 됩니다.");
				args.push("Is picked\n앞서 지정한 Camera로, Models 중 하나라도 Hover가 되면 true가 됩니다. 동시에 Module을 종료시 TRUE를 반환합니다.");
			}

			return _header;
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}

	private:
		Vectors _createRayInWorldCoords(const Camera& camera) const;
		Vectors _createQuadOfSprite(type_uint width, type_uint height) const;		
		bool _isRayIntersectedToQuad(const Vectors& quad, const Vectors& ray, const D3DXMATRIX& world) const;
	};
}