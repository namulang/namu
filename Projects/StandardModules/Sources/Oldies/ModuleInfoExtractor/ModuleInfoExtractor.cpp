#include "ModuleInfoExtractor.hpp"

namespace NE
{
	NE_DLL ModuleInfoExtractor::ModuleInfoExtractor()
		: NEModule()
	{

	}

	NE_DLL ModuleInfoExtractor::ModuleInfoExtractor(const ModuleInfoExtractor& source)
		: NEModule(source)
	{

	}

	NE_DLL ModuleInfoExtractor::~ModuleInfoExtractor()
	{

	}

	type_result NE_DLL ModuleInfoExtractor::initialize()
	{
		getKeySet().create(3);
		getKeySet().push(NEIntKey());	//	모듈코드
		getKeySet().push(NEUByteKey());	//	빼낼려는 데이터의 타입
		getKeySet().push(NETStringKey());	//	OUT 빼낸 데이터


		return RESULT_SUCCESS;
	}

	type_result NE_DLL ModuleInfoExtractor::execute()
	{
		//	pre:		
		const NEModuleSet& ms = Kernal::getInstance().getModuleManager().getModuleSet();
		type_int code = getModuleCode();
		const NEModule& m = ms[code];
		if( ! &m)
		{
			ALERT_ERROR("주어진 모듈코드(키#0 : %d)가 잘못되었습니다.\n모듈코드의 범위(0 ~ %d)를 넘은 것은 아닌가요?", code, ms.getLengthLastIndex());
			return RESULT_TYPE_ERROR;
		}
		const NEModule::Header& head = m.getHeader();


		//	post:
		const NETString* rhs = 0;
		switch(getInfoType())
		{
		case INFOTYPE_NAME:			rhs = &head.getName();					break;
		case INFOTYPE_DEVELOPER:	rhs = &head.getDeveloper();				break;
		case INFOTYPE_REVISION:		rhs = &NETString(head.getRevision());	break;
		case INFOTYPE_RELEASE_DATE:	rhs = &head.getReleaseDate();			break;
		case INFOTYPE_VERSION:		rhs = &head.getVersion();				break;
		case INFOTYPE_COMMENT:		rhs = &head.getComment();				break;
		case INFOTYPE_CONTACT:		rhs = &head.getContact();				break;
		
		default:
			ALERT_WARNING("잘못된 InfoType(%d) 입니다.", getInfoType());
		}
		
		getExtracted() = *rhs;
		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &ModuleInfoExtractor::clone() const
	{
		return *(new ModuleInfoExtractor(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &ModuleInfoExtractor::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T("ModuleInfoExtractor");
			_header.getDeveloper() = _T("kniz");
			_header.setRevision(1);
			_header.getComment() = _T("0번. 추출할 모듈의 ScriptCode \n1번. 빼내려는 정보의 종류(0:이름, 1:개발자명, 2:개정번호, 3:배포날짜, 4:버전, 5:코멘트, 6:연락처");
			_header.getVersion()  = _T("0.0.1a");
			_header.getReleaseDate() = _T("2013-10-05");
			_header.getModuleDependencies().create(0);
			_header.setMaxErrorCodeCount(0);
		}

		return _header;
	}
}