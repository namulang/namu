#include "../../NEExportable.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEExportable::ModuleHeader::ModuleHeader()
		: Header()
	{
		release();
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEExportable::ModuleHeader::ModuleHeader(const ModuleHeader& source)
		: Header(source)
	{
		_assign(source);
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEExportable::ModuleHeader::~ModuleHeader()
	{

	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NEExportable::ModuleHeader NE_DLL &NEExportable::ModuleHeader::operator=(const ModuleHeader& source)
	{
		NEExportable::Header::operator=(source);

		return _assign(source);
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEExportable::ModuleHeader::operator==(const ModuleHeader& source) const
	{
		if(this == &source) return true;
		if(NEExportable::Header::operator!=(source)) return false;
		if(_module_dependencies != source._module_dependencies) return false;
		if(_revision_compatibilities != source._revision_compatibilities) return false;
		if(_max_errorcode_count != source._max_errorcode_count) return false;
		if(_arguments_comments != source._arguments_comments) return false;

		return true;
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEExportable::ModuleHeader::operator!=(const ModuleHeader& source) const
	{
		return !(operator==(source));
	}


	
	NETStringSet NE_DLL &NEExportable::ModuleHeader::getModuleDependencies()
	{
		return _module_dependencies;
	}

	const NETStringSet NE_DLL &NEExportable::ModuleHeader::getModuleDependencies() const
	{
		return _module_dependencies;
	}

	NEIntSet NE_DLL &NEExportable::ModuleHeader::getRevisionCompatibilities()
	{
		return _revision_compatibilities;
	}

	const NEIntSet NE_DLL &NEExportable::ModuleHeader::getRevisionCompatibilities() const
	{
		return _revision_compatibilities;
	}

	type_count NE_DLL NEExportable::ModuleHeader::getMaxErrorCodeCount() const
	{
		return _max_errorcode_count;
	}

	void NE_DLL NEExportable::ModuleHeader::setMaxErrorCodeCount(type_count max_error_code)
	{
		_max_errorcode_count = max_error_code;
	}

	NETStringSet& NEExportable::ModuleHeader::getArgumentsComments()
	{
		return _arguments_comments;
	}

	const NETStringSet& NEExportable::ModuleHeader::getArgumentsComments() const
	{
		return _arguments_comments;
	}
	


	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEExportable::ModuleHeader::release()
	{
		NEExportable::Header::release();
		_module_dependencies.release();
		_revision_compatibilities.release();
		_max_errorcode_count = 0;
		_arguments_comments.release();
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NE_DLL NEExportable::ModuleHeader::isValid() const
	{
		type_result result = NEExportable::Header::isValid();
		if(NEResult::hasError(result) == true) return result;
		result = _module_dependencies.isValid();
		if(NEResult::hasError(result) == true) return result;
		result = _revision_compatibilities.isValid();
		if(NEResult::hasError(result) == true) return result;
		if(_max_errorcode_count < 0) return RESULT_TYPE_ERROR | RESULT_INVALID_DATA | RESULT_WRONG_BOUNDARY;
		result = _arguments_comments.isValid();
		if(NEResult::hasError(result)) return result;

		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEObject NE_DLL &NEExportable::ModuleHeader::clone() const
	{
		return *(new ModuleHeader(*this));
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileSaver NE_DLL &NEExportable::ModuleHeader::serialize(NEBinaryFileSaver& saver) const
	{
		NEExportable::Header::serialize(saver);

		return saver << _module_dependencies << _revision_compatibilities << _max_errorcode_count <<  _arguments_comments;
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileLoader NE_DLL &NEExportable::ModuleHeader::serialize(NEBinaryFileLoader& loader)
	{
		NEExportable::Header::serialize(loader);

		return loader >> _module_dependencies >> _revision_compatibilities >> _max_errorcode_count >> _arguments_comments;
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEType::Type NE_DLL NEExportable::ModuleHeader::getType() const
	{
		return NEType::MODULE_HEADER;
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NEExportable::ModuleHeader& NEExportable::ModuleHeader::_assign(const ModuleHeader& source)
	{
		if(this == &source) return *this;

		_module_dependencies = source._module_dependencies;
		_revision_compatibilities = source._revision_compatibilities;
		_max_errorcode_count = source._max_errorcode_count;
		_arguments_comments = source._arguments_comments;

		return *this;
	}
}