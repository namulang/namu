#include "NEArgumentBase.hpp"
#include "../../../Modules/Kernal/Kernal.hpp"

namespace NE
{
	bool NEArgumentBase::operator==(const NEArgumentBase& source) const
	{
		return _binder == source._binder;
	}
	bool NEArgumentBase::operator!=(const NEArgumentBase& source) const
	{
		return ! operator==(source);
	}
	NEKeyNameBinder& NEArgumentBase::getBinder() 
	{ 
		return _binder; 
	}
	const NEKeyNameBinder& NEArgumentBase::getBinder() const 
	{ 
		return _binder; 
	}
	type_result NEArgumentBase::isValid() const
	{
		return RESULT_SUCCESS;
	}
	void NEArgumentBase::release() 
	{
		_binder.release();
		_type_validation = NEType::UNDEFINED;
	}
	NEBinaryFileSaver& NEArgumentBase::serialize(NEBinaryFileSaver& saver) const
	{
		return saver << _type_validation << _binder;	//	_binded는 포인터라 저장할 필요가 없으며, _binded로 다시 지정할 수 있다. _default는 모듈개발자로부터 부여된다.
	}
	NEBinaryFileLoader& NEArgumentBase::serialize(NEBinaryFileLoader& loader)
	{
		NEType::Type validator = NEType::UNDEFINED;
		loader >> validator >> _binder;

		if(validator != _type_validation)
			KERNAL_ERROR("Argument의 load중, 타입불일치. data가 어딘가 꼬였네요");			

		return loader;		
	}

	NEArgumentBase::NEArgumentBase(NEType::Type type)
		: _type_validation(type)
	{
		
	}

	NEType::Type NEArgumentBase::getTypeToBeBinded() const
	{
		return _type_validation;
	}

}