#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL KeyboardSpy : public NEModule
	{
	public:
		virtual type_result initialize()
		{
			getKeySet().create(2);
			getKeySet().push(NEIntKey('A'));
			getKeySet().push(NEByteKey(0));

			return RESULT_SUCCESS;
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;

			if(_header.isValid() != RESULT_NOTHING)
			{
				_header.getName() = _T( "KeyboardSpy" );
				_header.getDeveloper() = _T( "kniz" );
				_header.setRevision(1);
				_header.getComment() = _T( "0번. spying 할 키 타입\n1번. 키의 상태(0=떼어짐,1=눌러짐(PRESSING),2=처음눌러졌을때만(DOWN), 3=떼어졌을때(UP))" );
				_header.getVersion()  = _T( "0.0.1a" );
				_header.getReleaseDate() = _T( "" );
				_header.getModuleDependencies().create(0);
				_header.setMaxErrorCodeCount(1);
			}

			return _header;
		}

	public:
		virtual type_result execute()
		{
			NEKeyCodeSet& keyset = getKeySet();
			type_int type = static_cast<NEIntKey&>(keyset[0]).getValue();
			type_byte status = static_cast<NEByteKey&>(keyset[1]).getValue();

			//	main:
			type_short spied = GetAsyncKeyState(type);
			bool result = false;
			switch(status)
			{
			case 0:
				result = spied == 0x0000;
				break;
			case 1:
				result = (spied & 0x8001) > 0;
				break;
			case 2:
				result = (spied & 0x8000) > 0;
				break;
			case 3:
				result = (spied & 0x0001) > 0;
				break;
			default:
				ALERT_ERROR(" : 잘못된 상태 값입니다.\n\t상태값: %d", status);
				return RESULT_FALSE | RESULT_TYPE_ERROR;
			}



			if(result)
				return RESULT_SUCCESS | RESULT_TRUE;
			else
				return RESULT_SUCCESS | RESULT_FALSE;
		}

	public:
		virtual NEObject& clone() const
		{
			return *(new KeyboardSpy(*this));
		}
	};
}
