#include "YourProject.hpp"

namespace NE
{
	NE_DLL YourProject::YourProject()
		: NEModule()
	{
				
	}

	NE_DLL YourProject::YourProject(const YourProject& source)
		: NEModule(source)
	{
		
	}

	NE_DLL YourProject::~YourProject()
	{

	}
	
	type_result NE_DLL YourProject::initialize()
	{
		getKeySet().create(0);
		//getKeySet().push(());
		
		return RESULT_SUCCESS;
	}

	type_result NE_DLL YourProject::execute()
	{
		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &YourProject::clone() const
	{
		return *(new YourProject(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &YourProject::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T("YourProject");
			_header.getDeveloper() = _T("개발자명");
			_header.setRevision(1);
			_header.getComment() = _T("설명");
			_header.getVersion()  = _T("버전");
			_header.getReleaseDate() = _T("배포날짜");
			_header.getModuleDependencies().create(0);
			_header.setMaxErrorCodeCount(0);
		}

		return _header;
	}
}