#include "BufferClearer.hpp"
#include "../DX9/DX9.hpp"

namespace DX9Graphics
{
	NEExportable::ModuleHeader& BufferClearer::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = "BufferClear";
			_header.getDeveloper() = "kniz";
			_header.setRevision(1);
			_header.getComment() = "NodeManager 영역에 있는 DX9를 찾아서, 백버퍼를 지정한 색으로 초기화 합니다.\n반드시 DX9 Module을 NodeManager 영역에 생성 후, 실행해야 합니다.";
			_header.getVersion()  = "0.0.1a";
			_header.getReleaseDate() = "2013-01-29";
			NETStringSet& args = _header.getArgumentsComments();
			args.resize(4);
			args.push("Red\n초기화할 색의 Red 성분입니다.\n최대 255까지 입력가능합니다.");
			args.push("Green\n초기화할 색의 Green 성분입니다.\n최대 255까지 입력가능합니다.");
			args.push("Blue\n초기화할 색의 Blue 성분입니다.\n최대 255까지 입력가능합니다.");
			args.push("How will it be drawn\n화면에 어떻게 그려질지 정합니다.");
		}

		return _header;
	}

	type_result BufferClearer::_onExecute()
	{
		//	main:
		DX9& dx9 = DX9::getInstancedDX();
		if( ! &dx9)
			return ALERT_ERROR(" : 디바이스가 초기화 되지 않았으므로 작업을 취소합니다.");

		LPDIRECT3DDEVICE9 device = dx9.getDevice();
		//		타겟팅:
		type_uint color = D3DCOLOR_XRGB(arg_red.getValue(), arg_green.getValue(), arg_blue.getValue());
		
		if(FAILED(device->Clear(0, NULL, arg_flag.getValue(), color, 1.0f, 0)))
			return ALERT_ERROR(" : 버퍼 클리어 실패");		

		//	post:
		return RESULT_SUCCESS;
	}

	NEObject& BufferClearer::clone() const
	{
		return *(new BufferClearer(*this));
	}
}