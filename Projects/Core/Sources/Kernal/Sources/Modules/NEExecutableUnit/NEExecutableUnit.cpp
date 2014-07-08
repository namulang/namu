#include "NEExecutableUnit.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEExecutableUnit::NEExecutableUnit()
		: NEUnit()
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEExecutableUnit::NEExecutableUnit(const NEExecutableUnit& source)
		: NEUnit(source)
	{
		_assign(source);
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

		NEUnit::operator=(source);

		return _assign(source);		
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEExecutableUnit::operator==(const NEExecutableUnit& source) const 
	{
		if(this == &source) return true;
		if(_enable != source._enable) return false;

		return true;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEExecutableUnit::operator!=(const NEExecutableUnit& source) const 
	{
		return !(operator==(source));
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEExecutableUnit::isEnable() const
	{
		return _enable;
	}



	void NE_DLL NEExecutableUnit::setEnable(bool enable)
	{
		_enable = enable;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEExecutableUnit::release() 
	{
		NEUnit::release();

		return _release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileSaver NE_DLL &NEExecutableUnit::serialize(NEBinaryFileSaver& saver) const 
	{
		NEUnit::serialize(saver);

		return saver << _enable;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileLoader NE_DLL &NEExecutableUnit::serialize(NEBinaryFileLoader& loader)
	{
		NEUnit::serialize(loader);

		return loader >> _enable;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEExecutableUnit::_release()
	{
		_enable = true;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NEExecutableUnit& NEExecutableUnit::_assign(const NEExecutableUnit& source)
	{
		if(this == &source) return *this;

		_enable = source._enable;

		return *this;
	}

	NEType::Type NE_DLL NEExecutableUnit::getType() const
	{
		return NEType::NEEXCUTABLE_UNIT;
	}
}