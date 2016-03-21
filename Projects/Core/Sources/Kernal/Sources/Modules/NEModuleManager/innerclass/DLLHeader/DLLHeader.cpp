#include "../../NEModuleManager.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEModuleManager::DLLHeader::DLLHeader()
		: Super(), _instance(NE_NULL)
	{
		release();
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEModuleManager::DLLHeader::DLLHeader(const This& source)
		: Super(source)
	{
		_assign(source);
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEModuleManager::DLLHeader::~DLLHeader()
	{
		release();
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NEModuleManager::DLLHeader NE_DLL &NEModuleManager::DLLHeader::operator=(const This& source)
	{
		return _assign(source);
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEModuleManager::DLLHeader::operator==(const This& source) const
	{
		if(this == &source) return true;
		if(_path != source._path) return false;
		if(_instance != source._instance) return false;
		if(_entrypoint != source._entrypoint) return false;

		return true;
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEModuleManager::DLLHeader::operator!=(const This& source) const
	{
		return !(operator==(source));
	}


	NETString NE_DLL &NEModuleManager::DLLHeader::getPath()
	{
		return _path;
	}

	const NETString NE_DLL &NEModuleManager::DLLHeader::getPath() const
	{
		return _path;
	}

	HINSTANCE NE_DLL &NEModuleManager::DLLHeader::getInstance()
	{
		return _instance;
	}

	const HINSTANCE NE_DLL &NEModuleManager::DLLHeader::getInstance() const
	{
		return _instance;
	}

	NEModuleManager::EntryPoint NE_DLL &NEModuleManager::DLLHeader::getEntryPoint()
	{
		return _entrypoint;
	}

	const NEModuleManager::EntryPoint NE_DLL &NEModuleManager::DLLHeader::getEntryPoint() const
	{
		return _entrypoint;
	}

		

	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEModuleManager::DLLHeader::release()
	{
		_path.release();
		if(_instance)
			FreeLibrary(_instance);
		_instance = NE_NULL;
		_entrypoint = NE_NULL;
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileSaver NE_DLL &NEModuleManager::DLLHeader::serialize(NEBinaryFileSaver& saver) const
	{
		//	아무것도 하지 않는다.
		return saver;
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileLoader NE_DLL &NEModuleManager::DLLHeader::serialize(NEBinaryFileLoader& loader)
	{
		//	아무것도 하지 않는다.
		return loader;
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NE_DLL NEModuleManager::DLLHeader::isValid() const
	{
		type_result result = _path.isValid();
		if(NEResult::hasError(result) == true) return result;
		if(_instance == NE_NULL) return RESULT_TYPE_ERROR | RESULT_WRONG_POINTER_ADDRESSING;
		if(_entrypoint == NE_NULL) return RESULT_TYPE_ERROR | RESULT_WRONG_POINTER_ADDRESSING;

		return true;
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NEModuleManager::DLLHeader& NEModuleManager::DLLHeader::_assign(const This& source)
	{
		if(this == &source) return *this;

		_path = source._path;
		_instance = source._instance;
		_entrypoint = source._entrypoint;

		return *this;
	}


	bool NEModuleManager::DLLHeader::isLoaded() const
	{
		return _entrypoint != NE_NULL;
	}


	const NEClassBase& NEModuleManager::DLLHeader::getClass() const
	{
		return getClassStatically();
	}

	const NEClassBase& NEModuleManager::DLLHeader::getClassStatically()
	{
		static NETClass<This> _inner;

		return _inner;
	}
}