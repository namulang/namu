#pragma once

#include "../../Commons/Templates/TValidator/TValidator.hpp"
#include "../Model/Model.hpp"

namespace DX9Graphics
{
	//	Particle의 Look을 특정 좌표 및 대상으로 향하도록 Angle을 조정한다.
	class NE_DLL ModelMediator : public TValidator<Model>
	{
	public:
		typedef ModelMediator ThisClass;
		typedef TValidator<Model> SuperClass;

	public:
		NETArgument<NEModuleSelector>	arg_target;
		NETArgument<NEFloatKey>			arg_distance;
		NETArgument<NEFloatKey>			arg_threshold;

	protected:
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			SuperClass::_onFetchArguments(tray);

			tray.push(arg_target);
			tray.push(arg_distance);
			tray.push(arg_threshold);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchModule()
		{
			SuperClass::_onFetchModule();

			arg_distance.setPurposeLimitation(NEArgumentBase::WRITTEN);
			arg_threshold.setPurposeLimitation(NEArgumentBase::WRITTEN);

			return RESULT_SUCCESS;
		}
		virtual type_result _onExecute();

	public:
		virtual NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;

			if (_header.isValid() != RESULT_NOTHING)
			{
				_header.getName() = _T("ModelMediator");
				_header.getDeveloper() = _T("kniz");
				_header.setRevision(1);
				_header.getComment() =
					"주어진 2 Model 간의 거리와 충돌여부(threshold)를 계산합니다.\n"
					"만약 충돌한 경우, TRUE를 반환합니다.";
				_header.getVersion() = _T("0.0.1a");
				_header.getReleaseDate() = _T("2015-02-12");
				NETStringSet& args = _header.getArgumentsComments();
				args.create(4);
				args.push("Source\n대상이 되는 Model 입니다.\nModel, AnimatedModel들이 여기에 속합니다.");
				args.push("Target\nSource와 거리 / 충돌여부를 판정할 다른 Model 입니다.");
				args.push("Distance\nSource와 Target간의 거리를 계산하여 여기에 기록됩니다.");
				args.push("Threshold(충돌임계값)\n0과 같거나 작으면 충돌한 것입니다.\n양수이면 충돌까지 남은 거리 입니다.");				
			}

			return _header;
		}

	public:
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}

	private:		
		type_float _createDistance(const D3DXVECTOR3& point1, const D3DXVECTOR3& point2)
		{
			return D3DXVec3Length(&(point2 - point1));
		}
	};
}