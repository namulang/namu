#include "Camera.hpp"
#include "../DX9/DX9.hpp"
#include "../PerspectiveCamera/PerspectiveCamera.hpp"

namespace DX9Graphics
{
	const NECodeSet& Camera::getModuleScriptCodes()
	{
		NECodeType type(NECodeType::MODULE_SCRIPT);
		static NECodeSet codes(type);

		if(codes.getLength() <= 1)
		{
			codes.create(1);
			codes.push(NEExportable::Identifier("PerspectiveCamera.kniz"));
		}

		return codes;
	}

	type_index Camera::_getLastProgramIndex(NEModuleCodeSet& within)
	{
		type_index to_return = -1;
		for (type_index n=0; n < within.getLength(); n++)
		{
			ShaderProgram& e = DX9::cast<ShaderProgram>(within[n]);
			if (&e			&&
				e.isEnable())

			to_return = n;
		}

		return to_return;
	}


	type_result Camera::render()
	{
		if (!isEnable()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;


		//	main:
		DX9& dx9 = DX9::getInstancedDX();
		LPDIRECT3DDEVICE9 device = &dx9 ? dx9.getDevice() : 0;
		if (!device)
			return ALERT_ERROR("DX9가 바인드 되지 않았습니다.");

		D3DVIEWPORT9 vp = createViewPort();
		device->SetViewport(&vp);
		_dockTransforms();
		/*
		ModuleSet에 담긴 Module이 ShaderProgram의 하위클래스라는 걸
		알 도리가 없음. getType이 지정되지 않기 때문에.
		TypeManager가 추가되기 전까지는 현재는 그냥 Shader로 강제 캐스팅.
		*/
		NEModuleCodeSet& moduleset = arg_shaders.getValue();
		type_index last_program_n = _getLastProgramIndex(moduleset);
		for (int n = 0; n < moduleset.getLength(); n++)
		{
			SuperClass::render();

			ShaderProgram& program = static_cast<ShaderProgram&>(moduleset[n]);
			if(			DX9::camera_index == 0x8001	&&
						! last_program_n			)
				program.arg_final_render_target = ShaderProgram::FINAL_RENDER_TARGET_NEW_OUTPUT;

			else if(	DX9::camera_index & 0x0001	&&
						n == last_program_n			)
				program.arg_final_render_target = ShaderProgram::FINAL_RENDER_TARGET_OUTPUT;

			else if(	DX9::camera_index & 0x8000	&&
						! n							)
				program.arg_final_render_target = ShaderProgram::FINAL_RENDER_TARGET_NEW_BUFFER;

			else
				program.arg_final_render_target = ShaderProgram::FINAL_RENDER_TARGET_PREVIOUS_BUFFER;

			program._render(*this);
		}

		return RESULT_SUCCESS;
	}
}