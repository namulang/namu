#include "NEExecutableUnit.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEExecutableUnit::NEExecutableUnit()
		: SuperClass()
	{
		
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEExecutableUnit::NEExecutableUnit(const NEExecutableUnit& source)
		: SuperClass(source)
	{
		
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEExecutableUnit::~NEExecutableUnit()
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NEExecutableUnit NE_DLL &NEExecutableUnit::operator=(const NEExecutableUnit& source) 
	{
		if(this == &source) return *this;

		SuperClass::operator=(source);

		return *this;	
	}



	NEType::Type NE_DLL NEExecutableUnit::getType() const
	{
		return NEType::NEEXCUTABLE_UNIT;
	}
}