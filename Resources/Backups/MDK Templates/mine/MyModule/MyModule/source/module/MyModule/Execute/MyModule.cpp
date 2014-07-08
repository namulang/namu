#include "MyModule.hpp"
#include "../define/define.hpp"

#include <iostream>

namespace NE
{
	MyModule::Connector::Connector()
		:	helloworld(NE_NULL)
	{
		
	}

	type_result MyModule::Connector::connect(NEKeySet& keyset)
	{
		if(keyset.getLength() < 0) return RESULT_TYPE_ERROR | RESULT_WRONG_BOUNDARY | RESULT_WRONG_PARAMETER | RESULT_WRONG_POINTER_ADDRESSING;
		if( ! &keyset[0] ) return RESULT_TYPE_ERROR | RESULT_WRONG_POINTER_ADDRESSING | RESULT_WRONG_PARAMETER | RESULT_WRONG_BOUNDARY;

		helloworld = static_cast<NEStringKey*>(&keyset[0]);

		return RESULT_SUCCESS;
	}

	MyModule::MyModule()
		: NEModule()
	{
		initialize();
	}

	MyModule::MyModule(const MyModule& source)
		: NEModule(source)
	{
		connector.connect(keyset);
	}

	MyModule::~MyModule()
	{

	}

	type_result MyModule::initialize()
	{
		keyset.create(_KEY_NUMBER);
		keyset.push(NEStringKey("hello world!"));
		connector.connect(keyset);

		return RESULT_SUCCESS;
	}

	type_result MyModule::execute()
	{
		std::cout << connector.helloworld->value.toCharPointer();

		return RESULT_SUCCESS;
	}

	NEObject* MyModule::clone() const
	{
		return new MyModule(*this);
	}

	const NEExportable::ModuleHeader& MyModule::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.name = _T( _NAME );
			_header.developer = _T( _AUTHOR );
			_header.revision = _REVISION;
			_header.comment = _T( _COMMENT );
			_header.version = _T( _VERSION );
			_header.release_date = _T( _DATE );
			_header.module_dependencies.create(_DEPENDENCIES_COUNT);
			_header.max_errorcode = MyModule::ERROR_CODE_END - 1;
		}

		return _header;
	}

	LPCTSTR MyModule::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		default:
			return _T("알수 없는 에러");
		}
	}
}
