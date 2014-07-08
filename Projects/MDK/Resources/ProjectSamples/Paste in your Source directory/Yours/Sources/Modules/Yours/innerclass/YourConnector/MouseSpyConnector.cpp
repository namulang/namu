#include "../../MouseSpy.hpp"
#include "../../define/define.hpp"

namespace NE
{
	NE_DLL MouseSpy::MouseSpyConnector::MouseSpyConnector()
	{
		_release();
	}

	NE_DLL MouseSpy::MouseSpyConnector::~MouseSpyConnector()
	{
		
	}

	type_result NE_DLL MouseSpy::MouseSpyConnector::connect(NEKeySet& keyset)
	{
		//	pre:
		if( ! &keyset)
		{
			//ALERT_ERROR(" : 주어진 키셋이 널입니다.")

			return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION;
		}
		if(keyset.getLength() <= 0)
		{
			//ALERT_ERROR(" : 주어진 키셋에 키가 하나도 없습니다. 연결이 불가능합니다.")

			return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION;
		}



		//	main:
		_cursor_x = static_cast<NEIntKey*>( &(keyset[2]) );
		_cursor_y = static_cast<NEIntKey*>( &(keyset[3]) );

		return RESULT_SUCCESS;
	}

	NEIntKey NE_DLL &MouseSpy::MouseSpyConnector::getCursorX()
	{
		return *_cursor_x;
	}

	const NEIntKey NE_DLL &MouseSpy::MouseSpyConnector::getCursorX() const
	{
		return *_cursor_x;
	}

	NEIntKey NE_DLL &MouseSpy::MouseSpyConnector::getCursorY() 
	{
		return *_cursor_y;
	}

	const NEIntKey NE_DLL &MouseSpy::MouseSpyConnector::getCursorY() const
	{
		return *_cursor_y;
	}
	
	void MouseSpy::MouseSpyConnector::_release()
	{
		_cursor_x = NE_NULL;
		_cursor_y = NE_NULL;
	}
}