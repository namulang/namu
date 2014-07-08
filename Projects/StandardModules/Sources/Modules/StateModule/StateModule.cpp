#include "StateModule.hpp"

namespace NE
{
	NE_DLL StateModule::StateModule()
		: NEModule()
	{
				
	}

	NE_DLL StateModule::StateModule(const StateModule& source)
		: NEModule(source)
	{
		
	}

	NE_DLL StateModule::~StateModule()
	{

	}
	
	type_result NE_DLL StateModule::initialize()
	{
		getKeySet().create(2);
		getKeySet().push(NEModuleCodeSetKey());
		getKeySet().push(NEIntKey());
		
		return RESULT_SUCCESS;
	}

	type_result NE_DLL StateModule::execute()
	{
		NEModuleCodeSet& actions = getActions();
		type_int state = getState();
		if( state < 0 || state > actions.getLengthLastIndex())
		{
			ALERT_WARNING("인덱스 범위 초과 입니다.");
			return RESULT_TYPE_WARNING;
		}


		//	main:
		//		Enable 업데이트:
		//			왜 바로 actions[state].execute()를 실행하지 않는가?:
		//				이 경우 LocalStack의 RecentModuleCodeSet이 &actions로
		//				변경되지 않기 때문이다. 게다가 LocalStack은 외부에서
		//				접근 할 수 없다. 때문에 이런식으로 사용한다.
		for(int n=0; n < actions.getSize(); n++)			
			actions[n].setEnable(n == state ? true : false);
		return actions.execute();
	}

	NEObject NE_DLL &StateModule::clone() const
	{
		return *(new StateModule(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &StateModule::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T("StateModule");
			_header.getDeveloper() = _T("kniz");
			_header.setRevision(1);
			_header.getComment() = _T("0번: 상태에 따라서 실행하게 될 모듈들(상태가 1이면 1번 인덱스의 모듈만 실행됨)\n1번: 상태 인덱스");
			_header.getVersion()  = _T("0.0.1a");
			_header.getReleaseDate() = _T("2013-10-15");
			_header.getModuleDependencies().create(0);
			_header.setMaxErrorCodeCount(0);
		}

		return _header;
	}
}