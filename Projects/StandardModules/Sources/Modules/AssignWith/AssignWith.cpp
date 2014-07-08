#include "AssignWith.hpp"
#include "define/define.hpp"

namespace NE
{
	NE_DLL AssignWith::AssignWith()
		: NEModule()
	{

	}

	NE_DLL AssignWith::AssignWith(const AssignWith& source)
		: NEModule(source)
	{

	}

	NE_DLL AssignWith::~AssignWith()
	{

	}

	type_result NE_DLL AssignWith::initialize()
	{
		getKeySet().create(_KEY_NUMBER);
		getKeySet().push( NEKeySelector() );
		getKeySet().push( NEKeySelector() );

		return RESULT_SUCCESS;
	}

	type_result NE_DLL AssignWith::execute()
	{
		//	pre:
		//		타겟팅:
		//			키셀렉터:
		NEKeySelector& operand_source = static_cast<NEKeySelector&>( getKeySet()[0] );
		NEKeySelector& operand_target = static_cast<NEKeySelector&>( getKeySet()[1] );		




		//	main:
		while(NEKey* src = &operand_source.getKey())
			while(NEKey* target_key = &operand_target.getKey())
				*src = *target_key;

		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &AssignWith::clone() const
	{
		return *(new AssignWith(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &AssignWith::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T( _NAME );
			_header.getDeveloper() = _T( _DEVELOPER );
			_header.setRevision(_REVISION);
			_header.getComment() = _T( _COMMENT );
			_header.getVersion()  = _T( _VERSION );
			_header.getReleaseDate() = _T( _DATE );
			_header.getModuleDependencies().create(_DEPENDENCIES_COUNT);
			_header.setMaxErrorCodeCount(AssignWith::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL AssignWith::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		case COULD_NOT_GET_KEY_FROM_SOURCE_SELECTOR:
			return _T("소스키(0번) 어떠한 키도 추출되지 않았습니다");

		default:
			return _T("알수 없는 에러");
		}
	}
}