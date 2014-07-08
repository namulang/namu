#include "ForSystemModule.hpp"

namespace NE
{
	ForSystemModule::ForSystemModule()
		: NEModule()
	{

	}

	ForSystemModule::ForSystemModule(const ForSystemModule& source)
		: NEModule(source)
	{

	}

	ForSystemModule::~ForSystemModule()
	{

	}

	type_result ForSystemModule::initialize()
	{
		getKeySet().create(2);
		getKeySet().push(NEIntKey());
		getKeySet().push(NEModuleCodeSetKey());

		return RESULT_SUCCESS;
	}

	type_result ForSystemModule::execute()
	{
		type_int& count = getCount();
		NEModuleCodeSet& actions = getActions();
		const NEModuleSet& ms = Kernal::getInstance().getModuleManager().getModuleSet();

		for(int n=0; n < ms.getLength() ;n++)
		{
			count++;
			actions.execute();
		}

		return RESULT_SUCCESS;
	}

	NEObject &ForSystemModule::clone() const
	{
		return *(new ForSystemModule(*this));
	}

	const NEExportable::ModuleHeader &ForSystemModule::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T("ForSystemModule");
			_header.getDeveloper() = _T("kniz");
			_header.setRevision(1);
			_header.getComment() = _T("\0번. OUT 루프를 돈 Count(index가 아님)\n1번. 매 대상마다 실행할 Actions");
			_header.getVersion()  = _T("0.0.1a");
			_header.getReleaseDate() = _T("2013-10-06");
			_header.getModuleDependencies().create(0);
			_header.setMaxErrorCodeCount(0);
		}

		return _header;
	}
}